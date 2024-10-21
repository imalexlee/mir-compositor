#include "background.h"

#include <cstring>

#include "miral/window.h"
#include <wayland-client-core.h>
#include <wayland-client.h>
#include <string>
#include <sstream>
#include <mir/fd.h>
#include <poll.h>
#include <filesystem>
#include <sys/eventfd.h>
#include <miral/display_configuration.h>

void render_gradient(int32_t width, int32_t height, unsigned char *row_, uint8_t const *bottom_colour,
                     uint8_t const *top_colour) {
    auto row = row_;
    for (int j = 0; j < height; j++) {
        auto *pixel = (uint32_t *) row;
        uint8_t pattern_[4];
        for (auto i = 0; i != 3; ++i)
            pattern_[i] = (j * bottom_colour[i] + (height - j) * top_colour[i]) / height;
        pattern_[3] = 0xff;

        for (int i = 0; i < width; i++)
            memcpy(pixel + i, pattern_, sizeof pixel[i]);

        row += 4 * width;
    }
}

/*
struct Background::Self {
    Self(wl_display *display, uint8_t *bottom_colour, uint8_t *top_colour);

    void draw_screen(SurfaceInfo &info) const;

    uint8_t *const bottom_colour;
    uint8_t *const top_colour;
};
*/

mir::Fd flush_signal{eventfd(0, EFD_SEMAPHORE)};
mir::Fd shutdown_signal{eventfd(0, EFD_CLOEXEC)};


void run(wl_display *display) {
    enum FdIndices {
        display_fd = 0,
        flush,
        shutdown,
        indices
    };

    pollfd fds[indices] =
    {
        {wl_display_get_fd(display), POLLIN, 0},
        {flush_signal, POLLIN, 0},
        {shutdown_signal, POLLIN, 0},
    };

    while (!(fds[shutdown].revents & (POLLIN | POLLERR))) {
        while (wl_display_prepare_read(display) != 0) {
            if (wl_display_dispatch_pending(display) == -1) {
                throw std::system_error{
                    errno, std::system_category(), "Failed to dispatch Wayland events"
                };
            }
        }

        if (poll(fds, indices, -1) == -1) {
            wl_display_cancel_read(display);
            throw std::system_error{errno, std::system_category(), "Failed to wait for event"};
        }

        if (fds[display_fd].revents & (POLLIN | POLLERR)) {
            if (wl_display_read_events(display)) {
                throw std::system_error{errno, std::system_category(), "Failed to read Wayland events"};
            }
        } else {
            wl_display_cancel_read(display);
        }

        if (fds[flush].revents & (POLLIN | POLLERR)) {
            eventfd_t foo;
            eventfd_read(flush_signal, &foo);
            wl_display_flush(display);
        }
    }
}

BackgroundWriter::BackgroundWriter(wl_display *display, uint8_t *bottom_colour, uint8_t *top_colour): display{display},
    bottom_colour{bottom_colour}, top_colour{top_colour} {
    wl_display_roundtrip(display);
    wl_display_roundtrip(display);
}


void Background::operator()(wl_display *display) {
    auto client = std::make_shared<BackgroundWriter>(display, bottom_colour, top_colour); {
        std::lock_guard lock{mutex};
        writer = client;
    }
    run(display);

    std::lock_guard lock{mutex};
    client.reset();
}

void Background::operator()(std::weak_ptr<mir::scene::Session> const &session) {
    std::lock_guard lock{mutex};
    weak_session = session;
}

void Background::operator()(std::string const &option) {
}


std::shared_ptr<mir::scene::Session> Background::session() const {
    std::lock_guard lock{mutex};
    return weak_session.lock();
}


void Background::stop() {
    std::lock_guard lock{mutex};
}

void Background::bottom(std::string const &option) {
    uint32_t value;
    std::stringstream interpreter{option};

    if (interpreter >> std::hex >> value) {
        bottom_colour[0] = value & 0xff;
        bottom_colour[1] = (value >> 8) & 0xff;
        bottom_colour[2] = (value >> 16) & 0xff;
    }
}

void Background::top(std::string const &option) {
    uint32_t value;
    std::stringstream interpreter{option};

    if (interpreter >> std::hex >> value) {
        top_colour[0] = value & 0xff;
        top_colour[1] = (value >> 8) & 0xff;
        top_colour[2] = (value >> 16) & 0xff;
    }
}

