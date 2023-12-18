#ifndef SK_CORE_SETTINGS_HPP
#define SK_CORE_SETTINGS_HPP

#include <boost/property_tree/ptree.hpp>

#include <filesystem>

namespace sk {

class Settings {
  public:
    explicit Settings(std::filesystem::path settings_folder_path);

    ~Settings() = default;

    Settings(Settings const& other) = delete;

    Settings& operator=(Settings const& other) = delete;

    Settings(Settings&& other) noexcept = default;

    Settings& operator=(Settings&& other) noexcept = default;

    void load(std::filesystem::path const& file_path, std::string const& subtree_path);

    template<class T>
    T get(std::string const& path) {
        return settings_.get<T>(path);
    }

  private:
    std::filesystem::path settings_folder_path_;
    boost::property_tree::ptree settings_{};
};
}// namespace sk

#endif// SK_CORE_SETTINGS_HPP
