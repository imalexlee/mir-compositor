# Simple Mir Compositor

This is a compositor writen using Mir (through MirAL) which allows the user to define various
customization options. Commands are also exposed for accessing applications.

## Prerequisites

- CMake 3.15+
- C++ compiler supporting >= C++20

## Installation

```shell
mkdir build && cd build
cmake ..
cmake --build .
```

## Running

```shell
# in build directory

#run main project
./mir-compositor
#or
WAYLAND_DISPLAY=wayland-99 ./mir_compositor

#run tests
./TEST
```

## Configuration Options

```shell
--startup-app <app_name> # launches a given app at startup
--startup-app-shell <app_name> # launches a given app at startup with privileged wayland extensions
--terminal <terminal_name> # set desired terminal to be launched when terminal shortcut is pressed (default is gnome-terminal)
--browser <browser_name> # set desired browser to be launched when browser shortcut is pressed (default is firefox)
```

## Shortcuts

- **CTRL + ALT + SHIFT + T** To open terminal
- **CTRL + ALT + SHIFT + B** To open browser
