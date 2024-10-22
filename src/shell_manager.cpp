#include "shell_manager.h"

#include <miral/minimal_window_manager.h>
#include <mir/logging/file_logger.h>
#include <mir/logging/multi_logger.h>


void ShellManager::register_shell_app(pid_t new_pid) {
    shell_pids.push_back(new_pid);
}

bool ShellManager::is_shell_app(pid_t pid) {
    const bool found_pid = std::ranges::find(shell_pids, pid) != shell_pids.end();
    return found_pid;
}

void ShellManager::enable_shell_extensions(WaylandExtensions &extensions,
                                           std::span<char const *const> protocols) {
    for (auto const &protocol: protocols) {
        extensions.conditionally_enable(protocol, [&](WaylandExtensions::EnableInfo const &info) {
                                            const pid_t app_pid = pid_of(info.app());
                                            return is_shell_app(app_pid) || info.user_preference().value_or(true);
                                        }
        );
    }
}
