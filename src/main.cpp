#include <span>
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
#include "shell_manager.h"

using namespace miral;
using namespace miral::toolkit;

int main(int argc, char const *argv[]) {
    MirRunner runner{argc, argv};

    /*
     * 1. Allow clients to receive unobstructed pointer events
     * 2. Describe output regions in desktop-oriented way
     * 3. Enable XDG-shell for the ability to create surface handles for graphical applications
     *      EX. Vulkan applications can retrieve rendering surfaces through Wayland by using
     *      vkCreateWaylandSurfaceKHR(...). This is only possible if XDG-shell is enabled.
     */
    WaylandExtensions extensions{};
    for (auto const &protocol: {
             WaylandExtensions::zxdg_output_manager_v1,
             "zwp_relative_pointer_manager_v1",
             "xdg_wm_base"
         }) {
        extensions.conditionally_enable(protocol, [&](WaylandExtensions::EnableInfo const &info) {
            return info.user_preference().value_or(true);
        });
    }

    ExternalClientLauncher ext_client_launcher{};

    // Run non-privileged startup applications callback
    const std::function run_startup_apps = [&](std::vector<std::string> const &apps) {
        for (auto const &app: apps) {
            ext_client_launcher.launch(std::vector{app});
        }
    };

    /*
     * Runs a desired terminal after CTRL+ALT+t is pressed.
     * Uses gnome-terminal as the default terminal
     */
    std::string selected_terminal{};
    const std::function run_desired_terminal = [&](std::string const &term) {
        if (term.empty()) {
            return;
        }
        selected_terminal = term;
    };

    /*
     * Runs a desired browser after CTRL+ALT+b is pressed.
     * Uses firefox as the default browser
     */
    std::string selected_browser{};
    const std::function run_desired_browser = [&](std::string const &browser) {
        if (browser.empty()) {
            return;
        }
        selected_browser = browser;
    };

    const std::array privileged_protocols = {
        WaylandExtensions::zwlr_foreign_toplevel_manager_v1,
        WaylandExtensions::zwp_input_method_manager_v2,
        WaylandExtensions::zwlr_virtual_pointer_manager_v1,
    };

    /*
     * Enable privileged Wayland features if there are shell aps in the current PID list
     * Additionally enables privileged features if user overrode selection in user_preferences
     */
    ShellManager shell_manager{};
    const std::function run_startup_apps_shell = [&](std::vector<std::string> const &shell_apps) {
        for (auto const &app: shell_apps) {
            const pid_t pid = ext_client_launcher.launch(ExternalClientLauncher::split_command(app));
            shell_manager.register_shell_app(pid);
            shell_manager.enable_shell_extensions(extensions, privileged_protocols);
        }
    };


    // Defines available keyboard shortcuts for various apps.
    const std::function keyboard_shortcuts = [&](MirEvent const *event) {
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
        MirKeyboardEvent const *keyboard_event = mir_input_event_get_keyboard_event(input_event);
        if (mir_keyboard_event_action(keyboard_event) != mir_keyboard_action_down) {
            return false;
        }

        // Must begin commands with CTRL+ALT
        const MirInputEventModifiers mods = mir_keyboard_event_modifiers(keyboard_event);
        if (!(mods & mir_input_event_modifier_alt) || !(mods & mir_input_event_modifier_ctrl)) {
            return false;
        }

        switch (mir_keyboard_event_keysym(keyboard_event)) {
            // Launch desired terminal
            case XKB_KEY_T:
                std::ignore = ext_client_launcher.launch({selected_terminal});
                return false;
            // Launch desired browser
            case XKB_KEY_B:
                std::ignore = ext_client_launcher.launch({selected_browser});
                return false;

            default:
                return false;
        };
    };

    return runner.run_with(
        {
            set_window_management_policy<MinimalWindowManager>(),
            ext_client_launcher,
            extensions,
            ConfigurationOption{
                run_startup_apps, "startup-app",
                "App to run at startup"
            },
            ConfigurationOption{
                run_desired_browser, "browser",
                "Browser to launch after pressing CTRL+ALT+B (defaults to Firefox)", "firefox"
            },
            ConfigurationOption{
                run_desired_terminal, "terminal",
                "Terminal to launch after pressing CTRL+ALT+T (defaults to gnome-terminal)", "gnome-terminal"
            },
            ConfigurationOption{
                run_startup_apps_shell, "startup-app-shell",
                "App to run at startup which is granted privileged features"
            },
            Keymap{},
            AppendEventFilter{keyboard_shortcuts},
        });
}
