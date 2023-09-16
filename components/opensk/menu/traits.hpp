#ifndef SK_MENU_TRAITS_HPP_
#define SK_MENU_TRAITS_HPP_

#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

namespace sk::menu {

struct traits {
    using point_type = boost::geometry::model::d2::point_xy<int>;
    using box_type = boost::geometry::model::box<point_type>;
};

} // namespace sk::menu

#endif // SK_MENU_TRAITS_HPP_
