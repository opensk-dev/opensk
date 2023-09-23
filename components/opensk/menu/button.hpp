#ifndef SK_MENU_BUTTON_HPP_
#define SK_MENU_BUTTON_HPP_

#include <menu/traits.hpp>

#include <functional>
#include <utility>

namespace sk::menu {

class Menu;

class Button : public sk::menu::traits::box_type {
    friend Menu;

  public:
    using callback_type = std::function<void()>;
    using box_type = sk::menu::traits::box_type;

    Button(box_type box, callback_type callback)
        : box_type(box), callback_(std::move(callback)) {}

  protected:
    callback_type callback_{};
};

} // namespace sk::menu

namespace boost::geometry::traits {

template<>
struct tag<sk::menu::Button> {
    using type = box_tag;
};

template<>
struct point_type<sk::menu::Button> {
    using type = sk::menu::traits::point_type;
};

template<std::size_t Dimension>
struct indexed_access<sk::menu::Button, min_corner, Dimension> {
    using coordinate_type = typename geometry::coordinate_type<sk::menu::traits::point_type>::type;

    static constexpr coordinate_type get(sk::menu::Button const& button) {
        return geometry::get<Dimension>(button.min_corner());
    }

    static void set(sk::menu::Button& button, coordinate_type const& value) {
        geometry::set<Dimension>(button.min_corner(), value);
    }
};

template<std::size_t Dimension>
struct indexed_access<sk::menu::Button, max_corner, Dimension> {
    using coordinate_type = typename geometry::coordinate_type<sk::menu::traits::point_type>::type;

    static constexpr coordinate_type get(sk::menu::Button const& button) {
        return geometry::get<Dimension>(button.max_corner());
    }

    static void set(sk::menu::Button const& button, coordinate_type const& value) {
        geometry::set<Dimension>(button.max_corner(), value);
    }
};

template<>
struct make<sk::menu::Button> {
    using button_type = sk::menu::Button;

    static const bool is_specialized = true;

    static button_type apply(sk::menu::traits::box_type shape, button_type::callback_type callback) {
        return {shape, std::move(callback)};
    }
};

} // namespace boost::geometry::traits

#endif // SK_MENU_BUTTON_HPP_
