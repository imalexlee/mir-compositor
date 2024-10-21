#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <miral/runner.h>
#include <miral/configuration_option.h>
#include <miral/toolkit_event.h>
#include <miral/internal_client.h>


struct BackgroundWriter {
    BackgroundWriter(wl_display *display, uint8_t *bottom_colour, uint8_t *top_colour);


    void draw_screen();

    wl_display *display;

    uint8_t *bottom_colour;
    uint8_t *top_colour;
};

class Background {
public:
    void operator()(wl_display *display);

    void operator()(std::weak_ptr<mir::scene::Session> const &session);

    void operator()(std::string const &option);

    std::shared_ptr<mir::scene::Session> session() const;

    void stop();

    void bottom(std::string const &option);

    void top(std::string const &option);

private:
    std::mutex mutable mutex{};
    std::weak_ptr<mir::scene::Session> weak_session{};

    uint8_t bottom_colour[4] = {0x0a, 0x24, 0x77, 0xFF};
    uint8_t top_colour[4] = {0x00, 0x00, 0x00, 0xFF};

    std::shared_ptr<BackgroundWriter> writer{};
};

#endif //BACKGROUND_H
