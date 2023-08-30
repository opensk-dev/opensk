# ifndef SK_CORE_SETTINGS_HPP_
# define SK_CORE_SETTINGS_HPP_

# include <boost/property_tree/ptree.hpp>

# include <filesystem>

namespace sk {

class Settings {
public:
    explicit Settings(std::filesystem::path settings_folder_path);
    ~Settings() = default;

    Settings(const Settings& other) = delete;
    Settings& operator=(const Settings& other) = delete;

    Settings(Settings&& other) noexcept = default;
    Settings& operator=(Settings&& other) noexcept = default;

    void load(const std::filesystem::path& file_path, const std::string& subtree_path);

    template<class T>
    T get(const std::string& path) {
        return settings_.get<T>(path);
    }

private:
    std::filesystem::path settings_folder_path_;
    boost::property_tree::ptree settings_{};
};

} // sk

# endif // SK_CORE_SETTINGS_HPP_
