#include <phys/cpu_dispatcher.hpp>

#include <physx/task/PxTask.h>

#include <tracy/Tracy.hpp>

namespace sk {

PhysicsCpuDispatcher::PhysicsCpuDispatcher(tbb::task_arena& task_arena) : task_arena_(task_arena) {
    task_arena_.initialize();
}

void PhysicsCpuDispatcher::submitTask(physx::PxBaseTask& task) {
    task_arena_.enqueue([&task]() {
        ZoneScopedNC("PhysX task execution", tracy::Color::MediumSpringGreen);
        task.run();
        task.release();
    });
}

std::uint32_t PhysicsCpuDispatcher::getWorkerCount() const {
    return static_cast<std::uint32_t>(task_arena_.max_concurrency());
}

} // namespace sk
