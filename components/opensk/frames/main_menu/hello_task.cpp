#include <frames/main_menu/hello_task.hpp>

#include <spdlog/spdlog.h>
#include <tracy/Tracy.hpp>

#include <thread>

void sk::HelloTask::execute() {
    ZoneScopedNC("Hello, World! task", tracy::Color::Yellow);
    spdlog::info("hello, multithreading world!");
    using namespace std::chrono_literals;
    for (int i = 0; i < 100; ++i) {
        spdlog::info("that's {} iteration", i);
        std::this_thread::sleep_for(100ms);
        FrameMarkNamed("Hi loop!");
    }
}
