#include <core/engine.hpp>
#include <frames/main_menu/frame.hpp>

#include <spdlog/spdlog.h>

namespace sk {

void MainMenuFrame::initialize() {
    Frame::initialize();
    spdlog::info("initialize main menu");
}

void MainMenuFrame::finalize() {
    Frame::finalize();
    spdlog::info("finalize main menu");
}

void MainMenuFrame::on_enable() {
    Frame::on_enable();
    spdlog::info("enable main menu");
    auto& runtime = get_engine().get_runtime();
    runtime.push_task(Runtime::ArenasEnum::main, &hello_task_);
    runtime.abort();
}

void MainMenuFrame::on_disable() {
    Frame::on_disable();
    spdlog::info("disable main menu");
}
} // namespace sk
