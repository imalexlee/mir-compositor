#include <miral/runner.h>
#include <miral/minimal_window_manager.h>
#include <miral/set_window_management_policy.h>
#include <miral/configuration_option.h>
#include <miral/external_client.h>
#include <miral/append_event_filter.h>
#include <miral/toolkit_event.h>
#include <miral/keymap.h>
#include <miral/canonical_window_manager.h>
#include <miral/wayland_extensions.h>
#include <miral/window.h>


using namespace miral;
using namespace miral::toolkit;

struct ShellManager {
    std::vector<pid_t> shell_pids;
    // todo: add function to filter pid's
    // todo: apply new extensions if found
};

int main(int argc, char const *argv[]) {
    MirRunner runner{argc, argv};

    /*
     * 1. Enable relative pointer manager for unique cursor when hovering over Mir compositor
     * 2. Enable XDG-shell for the ability to create surface handles for graphical applications.
     *      EX. Vulkan applications can retrieve rendering surfaces through Wayland by using
     *      vkCreateWaylandSurfaceKHR(...). This is only possible if XDG-shell is enabled.
     */
    WaylandExtensions extensions{};
    for (auto const &protocol: {
             WaylandExtensions::zxdg_output_manager_v1,
             "zwp_relative_pointer_manager_v1",
             "zwp_pointer_constraints_v1",
             "xdg_wm_base"
         }) {
        extensions.conditionally_enable(protocol, [&](WaylandExtensions::EnableInfo const &info) {
            return info.user_preference().value_or(true);
        });
    }

    ExternalClientLauncher client_launcher{};
    const std::function run_startup_apps = [&](std::vector<std::string> const &apps) {
        for (auto const &app: apps) {
            client_launcher.launch(std::vector{app});
        }
    };

    // Uses gnome-terminal as the default terminal
    std::string selected_terminal{};
    const std::function run_desired_terminal = [&](std::string const &term) {
        if (!term.empty()) {
            selected_terminal = term;
        }
    };

    // Uses Firefox as the default browser
    std::string selected_browser{};
    const std::function run_desired_browser = [&](std::string const &browser) {
        if (!browser.empty()) {
            selected_browser = browser;
        }
    };

    const std::function handle_move = [&](MirEvent const *event) {
        if (mir_event_get_type(event) == mir_event_type_resize) {
            runner.stop();
            return false;
        }
        printf("event_type: %d\n", mir_event_get_type(event));
        printf("HELLO\n");
        return false;
    };

    const std::function shortcuts = [&](MirEvent const *event) {
        // Must be input events
        if (mir_event_get_type(event) != mir_event_type_input) {
            return false;
        }

        // Must be keyboard events
        MirInputEvent const *input_event = mir_event_get_input_event(event);
        if (mir_input_event_get_type(input_event) != mir_input_event_type_key) {
            return false;
        }

        // Must be down press events
        MirKeyboardEvent const *kev = mir_input_event_get_keyboard_event(input_event);
        if (mir_keyboard_event_action(kev) != mir_keyboard_action_down) {
            return false;
        }

        // Must begin commands with CTRL+ALT
        const MirInputEventModifiers mods = mir_keyboard_event_modifiers(kev);
        if (!(mods & mir_input_event_modifier_alt) || !(mods & mir_input_event_modifier_ctrl)) {
            return false;
        }

        switch (mir_keyboard_event_keysym(kev)) {
            // Exit window manager
            case XKB_KEY_Escape:
                runner.stop();
                return true;

            // Launch desired terminal
            case XKB_KEY_t:
            case XKB_KEY_T:
                std::ignore = client_launcher.launch({selected_terminal});
                return false;
            case XKB_KEY_b:
            case XKB_KEY_B:
                std::ignore = client_launcher.launch({selected_browser});
                return false;

            default:
                return false;
        };
    };


    return runner.run_with(
        {
            set_window_management_policy<MinimalWindowManager>(),
            client_launcher,
            extensions,
            Keymap{},
            ConfigurationOption{
                run_startup_apps, "startup-app", "App to run at startup"
            },
            ConfigurationOption{
                run_desired_terminal, "terminal",
                "Terminal to launch after pressing CTRL+ALT+t (defaults to gnome-terminal)", "gnome-terminal"
            },
            ConfigurationOption{
                run_desired_browser, "browser",
                "Browser to launch after pressing CTRL+ALT+b (defaults to Firefox)", "firefox"
            },
            AppendEventFilter{handle_move},

            AppendEventFilter{shortcuts},
        }

    );
}
