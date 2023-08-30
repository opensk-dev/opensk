# include <frames/main_menu/hello_task.hpp>

# include <spdlog/spdlog.h>

void sk::HelloTask::execute() {
    spdlog::info("hello, multithreading world!");
}
