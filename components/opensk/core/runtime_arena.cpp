#include <core/runtime_arena.hpp>

#include <spdlog/spdlog.h>
#include <tracy/Tracy.hpp>

namespace sk {

RuntimeArena::Control::Control(std::function<void()> const& working_loop) : is_working(true),
    working_thread(working_loop) {
}

bool RuntimeArena::Control::on_fire() const {
    return !tasks_queue.empty() || (is_working.load() && !is_should_exit.load());
}

RuntimeArena::RuntimeArena() {
    auto delegate = [this]() {
        working_loop();
    };
    control_ptr_ = std::make_unique<Control>(delegate);
}

RuntimeArena::RuntimeArena(RuntimeArena::Managed const& managed) {
    control_ptr_ = std::make_unique<Control>(managed);
}

sk::RuntimeArena::~RuntimeArena() {
    stop();
}

void sk::RuntimeArena::push_task(Task* const task) {
    if (task == nullptr) {
        return;
    }
    control_ptr_->tasks_queue.push(task);
}

void sk::RuntimeArena::working_loop() {
    ZoneScopedNC("Runtime arena working loop", tracy::Color::Aqua);
    auto& control = *control_ptr_;
    Task* task = nullptr;
    while (control.on_fire()) {
        control.tasks_queue.pop(task);
        if (task != nullptr) {
            task->execute();
        }
    }
    control.is_should_exit = false;
    control.is_working = false;
}

void RuntimeArena::start() {
    auto& control = *control_ptr_;
    if (control.is_working.load()) {
        return;
    }
    std::lock_guard lock(control.mtx);
    control.is_working = true;
    control.working_thread.emplace([this]() {
        working_loop();
    });
}

void RuntimeArena::stop() {
    auto& control = *control_ptr_;
    if (control.is_working.load()) {
        std::unique_lock lock(control.mtx);
        control.is_working = false;
        control.tasks_queue.push(nullptr);
        if (control.working_thread.has_value()) {
            lock.unlock();
            control.working_thread->join();
        }
    }
}

void RuntimeArena::capture() {
    auto& control = *control_ptr_;
    if (control.is_working.load()) {
        return;
    };
    control.is_working = true;
    working_loop();
}

void RuntimeArena::stop_in_future() {
    auto& control = *control_ptr_;
    if (control.is_working.load()) {
        stop();
    } else {
        control.is_should_exit = true;
    }
}

}// namespace sk