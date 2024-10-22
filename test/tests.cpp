// shell_manager_tests.cpp
#include <cassert>
#include <iostream>

#include "../src/shell_manager.h"
#include <vector>
#include <miral/miral/wayland_extensions.h>

void test_register_shell_app() {
    std::cout << "TESTING REGISTER SHELL APP: ";
    ShellManager shell_manager;

    // Test registering a new app
    shell_manager.register_shell_app(1234);
    assert(shell_manager.is_shell_app(1234));

    // Test registering another app
    shell_manager.register_shell_app(5678);
    assert(shell_manager.is_shell_app(5678));

    // Test registering the same app again
    shell_manager.register_shell_app(1234);
    assert(shell_manager.is_shell_app(1234));
    std::cout << "PASSED\n";
}

void test_is_shell_app() {
    std::cout << "TESTING IS SHELL APP: ";
    ShellManager shell_manager;

    // Test with unregistered app
    assert(!shell_manager.is_shell_app(9999));

    // Test with registered app
    shell_manager.register_shell_app(1111);
    assert(shell_manager.is_shell_app(1111));

    // Test with registered app again
    assert(shell_manager.is_shell_app(1111));
    std::cout << "PASSED\n";
}

void test_enable_shell_extensions() {
    std::cout << "TESTING ENABLE_ SHELL EXTENSION: ";
    ShellManager shell_manager;
    WaylandExtensions extensions;

    std::vector protocols = {
        WaylandExtensions::zxdg_output_manager_v1, WaylandExtensions::zwlr_screencopy_manager_v1
    };
    shell_manager.enable_shell_extensions(extensions, protocols);

    assert(extensions.supported().contains(protocols[0]));
    assert(extensions.supported().contains(protocols[1]));
    std::cout << "PASSED\n";
}

int main(int argc, char **argv) {
    test_is_shell_app();
    test_register_shell_app();
    test_enable_shell_extensions();
    std::cout << "ALL TESTS PASSED" << std::endl;
}
