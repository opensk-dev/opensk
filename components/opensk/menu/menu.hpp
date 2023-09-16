#ifndef SK_MENU_HPP_
#define SK_MENU_HPP_

#include <menu/button.hpp>
#include <menu/traits.hpp>

#include <boost/geometry/index/rtree.hpp>

namespace sk::menu {

class Menu {
  public:
    Menu() = default;
    ~Menu() = default;

    Menu(Menu const& other) = default;
    Menu& operator=(Menu const& other) = default;

    Menu(Menu&& other) noexcept = default;
    Menu& operator=(Menu&& other) noexcept = default;

  private:
    boost::geometry::index::rtree<
        sk::menu::Button,
        boost::geometry::index::rstar<16>
    > rtree_{};
};

} // namespace sk::menu

#endif // SK_MENU_HPP_
