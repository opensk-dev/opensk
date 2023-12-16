#include <core/settings.hpp>

#include <boost/property_tree/ini_parser.hpp>

#include <utility>

namespace sk {

Settings::Settings(std::filesystem::path settings_folder_path) : settings_folder_path_(
    std::move(settings_folder_path)) {
}

void Settings::load(std::filesystem::path const& file_name, std::string const& subtree_path) {
    boost::property_tree::ptree subtree{};
    auto file_path = settings_folder_path_ / file_name;
    boost::property_tree::read_ini(file_path.string(), subtree);
    settings_.add_child(subtree_path, subtree);
}

} // namespace sk
