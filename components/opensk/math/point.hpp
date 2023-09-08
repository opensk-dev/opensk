# ifndef SK_MATH_POINT_HPP_
# define SK_MATH_POINT_HPP_

# include <utility>
# include <concepts>

namespace sk::math {

template<std::signed_integral T>
class Point {
public:
    using reference_t = std::add_lvalue_reference_t<T>;
    using const_reference_t = std::add_const_t<reference_t>;

    Point() = default;
    ~Point() = default;

    Point(T x, T y)
        : data_(x, y) {}

    Point(const Point&) = default;
    Point& operator=(const Point&) = default;

    Point(Point&&) noexcept = default;
    Point& operator=(Point&&) noexcept = default;

    [[nodiscard]] reference_t x() {
        return data_.first;
    }

    [[nodiscard]] T x() const {
        return data_.first;
    }

    [[nodiscard]] reference_t y() {
        return data_.second;
    }

    [[nodiscard]] T y() const {
        return data_.second;
    }

private:
    std::pair<T, T> data_{};
};

} // sk::math

# endif // SK_MATH_POINT_HPP_
