# include <core/frame.hpp>
# include <core/exceptions.hpp>
# include <config.hpp>

namespace sk {

Frame::~Frame() noexcept(false) {
    if (is_initialized_) {
        throw sk::exceptions::FrameBadAccess("Couldn't destroy - non finalized");
    }
}

Engine& Frame::get_engine() {
    if (engine_ptr_ == nullptr) {
        throw sk::exceptions::FrameBadAccess("Couldn't return engine ptr - not set");
    }
    return *engine_ptr_;
}

void Frame::initialize() {
    if (is_initialized_) {
        sk::throw_pedantic(sk::exceptions::FrameBadAccess("Couldn't initialize - already initialized"));
        return;
    }
    is_initialized_ = true;
}

void Frame::finalize() {
    if (!is_initialized_) {
        sk::throw_pedantic(sk::exceptions::FrameBadAccess("Couldn't finalize - not initialized"));
        return;
    }
    if (is_enabled_) {
        sk::throw_pedantic(sk::exceptions::FrameBadAccess("Couldn't finalize - not disabled"));
        this->on_disable();
    }
    is_initialized_ = false;
}

void Frame::on_enable() {
    if (!is_initialized_) {
        sk::throw_pedantic(sk::exceptions::FrameBadAccess("Couldn't enable - not initialized"));
        this->initialize();
    }
    if (is_enabled_) {
        sk::throw_pedantic(sk::exceptions::FrameBadAccess("Couldn't enable - already enabled"));
        return;
    }
    is_enabled_ = true;
}

void Frame::on_disable() {
    if (!is_enabled_) {
        sk::throw_pedantic(sk::exceptions::FrameBadAccess("Couldn't disable - not enabled"));
        return;
    }
    is_enabled_ = false;
}

bool Frame::is_initialized() const {
    return is_initialized_;
}

bool Frame::is_enabled() const {
    return is_enabled_;
}

FrameHolder::FrameHolder(Frame* frame)
    : frame_ptr_(frame) {
    if (frame != nullptr) {
        frame->on_enable();
    }
}

FrameHolder& FrameHolder::operator=(Frame* frame) {
    if (frame != frame_ptr_) {
        if (frame_ptr_ != nullptr) {
            frame_ptr_->on_disable();
        }
        if (frame != nullptr) {
            frame->on_enable();
        }
        frame_ptr_ = frame;
    }
    return *this;
}

FrameHolder::~FrameHolder() {
    if (frame_ptr_ != nullptr) {
        frame_ptr_->on_disable();
    }
}

FrameHolder::FrameHolder(FrameHolder&& other) noexcept {
    frame_ptr_ = other.frame_ptr_;
    other.frame_ptr_ = nullptr;
}

FrameHolder& FrameHolder::operator=(FrameHolder&& other) noexcept {
    frame_ptr_ = other.frame_ptr_;
    other.frame_ptr_ = nullptr;
    return *this;
}

void FrameHolder::set_engine_ptr(Engine* engine_ptr) {
    Frame::engine_ptr_ = engine_ptr;
}

Frame* FrameHolder::get() {
    return frame_ptr_;
}

} // sk