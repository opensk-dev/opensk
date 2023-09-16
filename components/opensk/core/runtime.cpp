#include <core/exceptions.hpp>
#include <core/runtime.hpp>

#include <thread>

namespace sk {

Runtime::Runtime(std::uint32_t concurrency) {
    if (concurrency == 0) {
        concurrency = std::thread::hardware_concurrency();
    }
    if (concurrency < 4) {
        throw sk::exceptions::UnsupportedHardwareConstraint("Low CPU concurrency");
    }
}

void Runtime::push_task(Runtime::ArenasEnum arena, Task* task) {
    switch (arena) {
    case ArenasEnum::main: {
        main_arena_.push_task(task);
        break;
    }
    }
}

void Runtime::abort() {
    main_arena_.stop_in_future();
}

RuntimeArena& Runtime::get_main_arena() {
    return main_arena_;
}

}// namespace sk