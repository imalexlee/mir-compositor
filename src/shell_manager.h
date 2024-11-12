#ifndef SHELLMANAGER_H
#define SHELLMANAGER_H

#include <span>
#include <vector>
#include <miral/runner.h>
#include <miral/wayland_extensions.h>

using namespace miral;

class ShellManager {
public:
 /**
  * @brief           Adds a new shell application PID to the ShellManager
  * @param new_pid   The new PID to add
  */
 void register_shell_app(pid_t new_pid);

 /**
  * @brief     Informs whether the given process ID is a shell application
  * @param pid A PID to check for
  * @return    A boolean regarding whether the PID is a shell application
  */
 [[nodiscard]] bool is_shell_app(pid_t pid);

 /**
  * @brief            Enables a given list of protocols to enable if shell extensions needed
  * @param extensions Wayland Extensions used for enabling these protocols
  * @param protocols  The protocols to enable
  */
 void enable_shell_extensions(WaylandExtensions &extensions,
                              std::span<char const *const> protocols);

private:
 std::vector<pid_t> shell_pids;
};
#endif //SHELLMANAGER_H
