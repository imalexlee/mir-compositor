#include <miral/runner.h>
#include <miral/minimal_window_manager.h>
#include <miral/set_window_management_policy.h>
#include <miral/configuration_option.h>
#include <miral/external_client.h>
#include <miral/append_event_filter.h>
#include <miral/toolkit_event.h>

using namespace miral;
using namespace miral::toolkit;

int main(int argc, char const *argv[]) {
    MirRunner runner{argc, argv};
    ExternalClientLauncher client_launcher{};

    const std::function run_startup_apps = [&](std::vector<std::string> const &apps) {
        for (auto const &app: apps) {
            client_launcher.launch(std::vector{app});
        }
    };
    std::string terminal_cmd{"gnome-terminal"};

    auto const builtin_keybinds = [&](MirEvent const *event) {
        // Skip non-input events
        if (mir_event_get_type(event) != mir_event_type_input)
            return false;

        // Skip non-key input events
        MirInputEvent const *input_event = mir_event_get_input_event(event);
        if (mir_input_event_get_type(input_event) != mir_input_event_type_key)
            return false;

        // Skip anything but down presses
        MirKeyboardEvent const *kev = mir_input_event_get_keyboard_event(input_event);
        if (mir_keyboard_event_action(kev) != mir_keyboard_action_down)
            return false;

        // CTRL   ALT must be pressed
        const MirInputEventModifiers mods = mir_keyboard_event_modifiers(kev);
        if (!(mods & mir_input_event_modifier_alt) || !(mods & mir_input_event_modifier_ctrl))
            return false;

        switch (mir_keyboard_event_keysym(kev)) {
            // Exit program
            case XKB_KEY_Escape:
                runner.stop();
                return true;

            // Launch terminal
            case XKB_KEY_t:
            case XKB_KEY_T:
                std::ignore = client_launcher.launch({terminal_cmd});
                return false;

            // Do nothing
            default:
                return false;
        };
    };
    return runner.run_with(
        {
            set_window_management_policy<MinimalWindowManager>(),
            client_launcher,
            ConfigurationOption{
                run_startup_apps, "startup-app", "App to run at startup (can be specified multiple times)"
            },
            AppendEventFilter{builtin_keybinds}

        });
}
