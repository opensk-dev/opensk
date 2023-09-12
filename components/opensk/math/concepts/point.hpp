# ifndef SK_MATH_CONCEPTS_POINT_HPP_
# define SK_MATH_CONCEPTS_POINT_HPP_

# include <concepts>

namespace sk::math {

template<
    class T,
    template<std::signed_integral=T> class PointType
>
concept PointConcept = requires(PointType<> point) {
    { point.x() } -> std::same_as<std::add_lvalue_reference<T>>;
    { point.y() } -> std::same_as<std::add_lvalue_reference<T>>;
};

} // sk::math

# endif // SK_MATH_CONCEPTS_POINT_HPP_
