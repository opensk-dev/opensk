#include <menu/menu.hpp>

namespace sk::menu {

void Menu::update(sk::menu::traits::point_type cursor_position) {
    rtree_.query();
}

} // namespace sk::menu