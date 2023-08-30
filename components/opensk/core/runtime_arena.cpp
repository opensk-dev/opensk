# include <core/runtime_arena.hpp>
# include <core/exceptions.hpp>

# include <tracy/Tracy.hpp>
# include <spdlog/spdlog.h>

namespace sk {

RuntimeArena::ControlBlock::ControlBlock(const std::function<void()>& working_loop)
    : is_working(true),
      working_thread(working_loop) {}

bool RuntimeArena::ControlBlock::on_fire() const {
    return !tasks_queue.empty() || is_working.load();
}

RuntimeArena::RuntimeArena() {
    auto delegate = [this]() {
        working_loop();
    };
    control_block_ptr_ = std::make_unique<ControlBlock>(delegate);
}

RuntimeArena::RuntimeArena(const RuntimeArena::Managed& managed) {
    control_block_ptr_ = std::make_unique<ControlBlock>(managed);
}

sk::RuntimeArena::~RuntimeArena() {
    stop();
}

void sk::RuntimeArena::push_task(Task* const task) {
    if (task == nullptr) {
        return;
    }
    control_block_ptr_->tasks_queue.push(task);
}

void sk::RuntimeArena::working_loop() {
    ZoneScopedNC("Runtime arena working loop", tracy::Color::Aqua);
    Task* task = nullptr;
    auto& tasks_queue = control_block_ptr_->tasks_queue;
    while (control_block_ptr_->on_fire()) {
        tasks_queue.pop(task);
        if (task != nullptr) {
            task->execute();
        }
    }
}

void RuntimeArena::start() {
    if (control_block_ptr_->is_working.load()) {
        return;
    }
    std::lock_guard lock(control_block_ptr_->mtx);
    control_block_ptr_->is_working.store(true);
    control_block_ptr_->working_thread.emplace(
        [this]() {
            working_loop();
        });
}

void RuntimeArena::stop() {
    if (control_block_ptr_->is_working.load()) {
        std::unique_lock lock(control_block_ptr_->mtx);
        control_block_ptr_->is_working.store(false);
        control_block_ptr_->tasks_queue.push(nullptr);
        if (control_block_ptr_->working_thread.has_value()) {
            lock.unlock();
            control_block_ptr_->working_thread->join();
        }
    }
}

void RuntimeArena::capture() {
    if (control_block_ptr_->is_working.load()) {
        return;
    };
    control_block_ptr_->is_working.store(true);
    working_loop();
}

} // sk