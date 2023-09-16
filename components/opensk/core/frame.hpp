#ifndef SK_CORE_FRAME_HPP_
#define SK_CORE_FRAME_HPP_

#include <exception>

namespace sk {

class Engine;

class FrameHolder;

class Frame {
    friend FrameHolder;

  public:
    Frame() = default;
    virtual ~Frame() noexcept(false);

    Frame(Frame&& other) noexcept = default;
    Frame& operator=(Frame&& other) noexcept = default;

    virtual void initialize();
    virtual void finalize();

    virtual void on_enable();
    virtual void on_disable();

    [[nodiscard]] bool is_initialized() const;
    [[nodiscard]] bool is_enabled() const;

  protected:
    static Engine& get_engine();

  private:
    inline static Engine* engine_ptr_ = nullptr;
    bool is_initialized_ = false;
    bool is_enabled_ = false;
};

class FrameHolder {
    friend Engine;

  public:
    FrameHolder() = default;
    ~FrameHolder();

    FrameHolder(FrameHolder const& other) = delete;
    FrameHolder& operator=(FrameHolder const& other) = delete;

    FrameHolder(FrameHolder&& other) noexcept;
    FrameHolder& operator=(FrameHolder&& other) noexcept;

    explicit FrameHolder(Frame* frame);
    FrameHolder& operator=(Frame* frame);

    Frame* get();

  protected:
    static void set_engine_ptr(Engine* engine_ptr);

  private:
    Frame* frame_ptr_ = nullptr;
};

} // namespace sk

#endif // SK_CORE_FRAME_HPP_
