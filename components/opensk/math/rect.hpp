# ifndef SK_MATH_RECT_HPP_
# define SK_MATH_RECT_HPP_

# include <math/point.hpp>

# include <concepts>
# include <type_traits>
#include <utility>

namespace sk::math {

template<
    class RectInnerRepresentationType,
    class T, class DiffT
>
concept RectInnerRepresentation = requires(
    RectInnerRepresentationType representation,
    const RectInnerRepresentationType const_representation,
    T t, DiffT diff
) {
    requires std::signed_integral<T>;
    { t - t } -> std::convertible_to<DiffT>;

    requires std::is_standard_layout_v<RectInnerRepresentationType>;

    // setters
    { representation.set_x0(t) } -> std::same_as<void>;
    { representation.set_y0(t) } -> std::same_as<void>;
    { representation.set_x1(t) } -> std::same_as<void>;
    { representation.set_y1(t) } -> std::same_as<void>;

    { representation.set_width(diff) } -> std::same_as<void>;
    { representation.set_height(diff) } -> std::same_as<void>;

    // getters
    { const_representation.get_x0() } -> std::same_as<T>;
    { const_representation.get_y0() } -> std::same_as<T>;
    { const_representation.get_x1() } -> std::same_as<T>;
    { const_representation.get_y1() } -> std::same_as<T>;

    { const_representation.get_width() } -> std::same_as<DiffT>;
    { const_representation.get_height() } -> std::same_as<DiffT>;
};

namespace detail {

template<
    std::signed_integral T,
    std::integral DiffT
>
struct RectTraits {
    using reference_type = std::add_lvalue_reference_t<T>;
    using const_reference_type = std::add_const_t<reference_type>;

    using point_type = sk::math::Point<T>;
    using size_type = std::pair<T, T>;
};

template<
    std::signed_integral T,
    std::integral DiffT
>
class PointPointInnerRepresentation {
private:
    using traits = RectTraits<T, DiffT>;

    traits::point_type point0_;
    traits::point_type point1_;

public:
    PointPointInnerRepresentation(
        traits::point_type point0,
        traits::point_type point1
    ) : point0_(std::move(point0)),
        point1_(std::move(point1)) {}

    // setters

    void set_x0(T x0) {
        point0_.x() = x0;
    }

    void set_y0(T y0) {
        point0_.y() = y0;
    }

    void set_x1(T x1) {
        point1_.x() = x1;
    }

    void set_y1(T y1) {
        point1_.y() = y1;
    }

    void set_width(DiffT width) {
        point1_.x() = point0_.x() + width;
    }

    void set_height(DiffT height) {
        point1_.y() = point0_.y() + height;
    }

    // getters

    [[nodiscard]] T get_x0() const {
        return point0_.x();
    }

    [[nodiscard]] T get_y0() const {
        return point0_.y();
    }

    [[nodiscard]] T get_x1() const {
        return point1_.x();
    }

    [[nodiscard]] T get_y1() const {
        return point1_.y();
    }

    [[nodiscard]] DiffT get_width() const {
        return point1_.x() - point0_.x();
    }

    [[nodiscard]] DiffT get_height() const {
        return point1_.y() - point0_.y();
    }
};

template<
    std::signed_integral T,
    std::integral DiffT
>
class PointSizeInnerRepresentation {
private:
    using traits = RectTraits<T, DiffT>;

    traits::point_type point_;
    traits::size_type size_;

public:
    PointSizeInnerRepresentation(
        traits::point_type point,
        traits::size_type size
    ) : point_(std::move(point)),
        size_(std::move(size)) {}

    // setters

    void set_x0(T x0) {
        size_.first += point_.x() - x0;
        point_.x() = x0;
    }

    void set_y0(T y0) {
        size_.second += point_.y() - y0;
        point_.y() = y0;
    }

    void set_x1(T x1) {
        size_.first = x1 - point_.x();
    }

    void set_y1(T y1) {
        size_.second = y1 - point_.y();
    }

    void set_width(DiffT width) {
        size_.first = width;
    }

    void set_height(DiffT height) {
        size_.second = height;
    }

    // getters

    [[nodiscard]] T get_x0() const {
        return point_.x();
    }

    [[nodiscard]] T get_y0() const {
        return point_.y();
    }

    [[nodiscard]] T get_x1() const {
        return point_.x() + size_.first;
    }

    [[nodiscard]] T get_y1() const {
        return point_.y() + size_.second;
    }

    [[nodiscard]] DiffT get_width() const {
        return size_.first;
    }

    [[nodiscard]] DiffT get_height() const {
        return size_.second;
    }
};

} // detail

template<
    std::signed_integral T,
    std::integral DiffT,
    RectInnerRepresentation<T, DiffT> InnerRepresentationType
>
class RectImpl {
private:
    InnerRepresentationType representation_;
    /*
     *  point_point:
     *      *------* <---- up_right (x1, y1)
     *      | rect |
     *      *------*
     *      ^------------- down_left (x0, y0)
     *
     *  point_size:
     *      *------* <---- up_right (x0 + width, y0 + height)
     *      | rect |
     *      *------*
     *      ^------------- down_left (x0, y0)
     */
public:
    template<class... Args>
    RectImpl(Args&& ... args)
        : representation_(std::forward<Args>(args)...) {}

public:
    class X0Provider {
    public:
        explicit X0Provider(InnerRepresentationType& ref)
            : ref_(ref) {}

        operator T() const {
            return ref_.get_x0();
        }

        X0Provider& operator=(T x0) {
            ref_.set_x0(x0);
            return *this;
        }

    private:
        InnerRepresentationType& ref_;
    };

    [[nodiscard]] X0Provider x0() {
        return X0Provider(representation_);
    }

    [[nodiscard]] X0Provider x0() const {
        return X0Provider(representation_);
    }

    class Y0Provider {
    public:
        explicit Y0Provider(InnerRepresentationType& ref)
            : ref_(ref) {}

        operator T() const {
            return ref_.get_y0();
        }

        Y0Provider& operator=(T y0) {
            ref_.set_y0(y0);
            return *this;
        }

    private:
        InnerRepresentationType& ref_;
    };

    [[nodiscard]] Y0Provider y0() {
        return Y0Provider(representation_);
    }

    [[nodiscard]] Y0Provider y0() const {
        return Y0Provider(representation_);
    }

    class X1Provider {
    public:
        explicit X1Provider(InnerRepresentationType& ref)
            : ref_(ref) {}

        operator T() const {
            return ref_.get_x1();
        }

        X1Provider& operator=(T x1) {
            ref_.set_x1(x1);
            return *this;
        }

    private:
        InnerRepresentationType& ref_;
    };

    [[nodiscard]] X1Provider x1() {
        return X1Provider(representation_);
    }

    [[nodiscard]] X1Provider x1() const {
        return X1Provider(representation_);
    }

    class Y1Provider {
    public:
        explicit Y1Provider(InnerRepresentationType& ref)
            : ref_(ref) {}

        operator T() const {
            return ref_.get_y1();
        }

        Y1Provider& operator=(T y1) {
            ref_.set_y1(y1);
            return *this;
        }

    private:
        InnerRepresentationType& ref_;
    };

    [[nodiscard]] Y1Provider y1() {
        return Y1Provider(representation_);
    }

    [[nodiscard]] Y1Provider y1() const {
        return Y1Provider(representation_);
    }

    class WidthProvider {
    public:
        explicit WidthProvider(InnerRepresentationType& ref)
            : ref_(ref) {}

        operator DiffT() const {
            return ref_.get_width();
        }

        WidthProvider& operator=(DiffT width) {
            ref_.set_width(width);
            return *this;
        }

    private:
        InnerRepresentationType& ref_;
    };

    [[nodiscard]] WidthProvider width() {
        return WidthProvider(representation_);
    }

    [[nodiscard]] WidthProvider width() const {
        return WidthProvider(representation_);
    }

    class HeightProvider {
    public:
        explicit HeightProvider(InnerRepresentationType& ref)
            : ref_(ref) {}

        operator DiffT() const {
            return ref_.get_height();
        }

        HeightProvider& operator=(DiffT height) {
            ref_.set_height(height);
            return *this;
        }

    private:
        InnerRepresentationType& ref_;
    };

    [[nodiscard]] HeightProvider height() {
        return HeightProvider(representation_);
    }

    [[nodiscard]] HeightProvider height() const {
        return HeightProvider(representation_);
    }
};

enum class RectType {
    point_point,
    point_size,
};

template<
    RectType type,
    std::signed_integral T = std::int32_t,
    std::integral DiffT = T
>
class Rect {};

template<>
class Rect<RectType::point_point>
    : public RectImpl<
        std::int32_t, std::int32_t,
        detail::PointPointInnerRepresentation<std::int32_t, std::int32_t>
    > {
private:
    using Base = RectImpl<
        std::int32_t, std::int32_t,
        detail::PointPointInnerRepresentation<std::int32_t, std::int32_t>>;
    using traits = detail::RectTraits<std::int32_t, std::int32_t>;
public:
    Rect(traits::point_type point0, traits::point_type point1)
        : Base(std::move(point0), std::move(point1)) {}
};

template<>
class Rect<RectType::point_size>
    : public RectImpl<
        std::int32_t, std::int32_t,
        detail::PointSizeInnerRepresentation<std::int32_t, std::int32_t>
    > {
private:
    using Base = RectImpl<
        std::int32_t, std::int32_t,
        detail::PointSizeInnerRepresentation<std::int32_t, std::int32_t>>;
    using traits = detail::RectTraits<std::int32_t, std::int32_t>;
public:
    Rect(traits::point_type point, traits::size_type size)
        : Base(std::move(point), std::move(size)) {}
};

} // sk::math

# endif // SK_MATH_RECT_HPP_
