# ifndef SK_READ_OPTIONS_HPP_
# define SK_READ_OPTIONS_HPP_

# include <boost/program_options.hpp>

# include <iostream>
# include <optional>
# include <fstream>
# include <filesystem>

namespace sk {

struct ConfigureOptions {
    std::filesystem::path data_path;
    std::filesystem::path settings_path;
    std::filesystem::path saves_path;
};

std::optional<ConfigureOptions> read_options(int argc, const char* argv[]) noexcept {
    namespace po = boost::program_options;
    using std::filesystem::path;

    path config_file_path{};
    auto* config_option_val = po::value<path>(&config_file_path)->default_value("opensk.conf");

    // setup options descriptions
    auto command_line_options_desc = po::options_description("Command line options");
    command_line_options_desc.add_options()
        ("help,h", "display this help message")
        ("version,v", "display version string")
        ("config", config_option_val, "Path to config file");

    auto configure_options_desc = po::options_description("Configuration");
    configure_options_desc.add_options()
        ("data-path", po::value<path>(), "Path to data folder")
        ("settings-path", po::value<path>(), "Path to settings folder")
        ("saves-path", po::value<path>(), "Path to folder contained saves");

    auto allowed_options_desc = po::options_description("Allowed options");
    allowed_options_desc.add(command_line_options_desc).add(configure_options_desc);

    {   // handle command line
        po::variables_map command_line_variables{};

        try {
            auto command_line_parsed_options = po::parse_command_line(argc, argv, command_line_options_desc);
            po::store(command_line_parsed_options, command_line_variables);
            po::notify(command_line_variables);
        } catch (const po::error_with_option_name& ex) {
            std::cout << "unrecognised command line option " << ex.get_option_name() << '\n';
            return {};
        } catch (const std::exception& ex) {
            std::cout << ex.what() << '\n';
            return {};
        }

        if (command_line_variables.count("help")) {
            allowed_options_desc.print(std::cout);
            return {};
        }

        if (command_line_variables.count("version")) {
            // TODO: configure version with cmake
            std::cout << "opensk version 0.0" << '\n';
            return {};
        }
    }

    ConfigureOptions configure_options{};

    {   // handle config file
        auto config_file = std::ifstream(config_file_path);
        if (!config_file) {
            std::cout << "couldn't open config file\n";
            return {};
        }

        po::variables_map configure_variables{};

        try {
            po::parsed_options configure_parsed_options = po::parse_config_file(config_file, configure_options_desc);
            po::store(configure_parsed_options, configure_variables);
            po::notify(configure_variables);
        } catch (const po::error_with_option_name& ex) {
            std::cout << "unrecognised configure option " << ex.get_option_name() << '\n';
            return {};
        } catch (const std::exception& ex) {
            std::cout << ex.what() << '\n';
            return {};
        }

        auto try_get_option =
            [&configure_variables](auto& option_place, const char* option_name) {
                try {
                    option_place = std::move(configure_variables.at(option_name).as<decltype(option_place)>());
                } catch (const std::out_of_range& ex) {
                    std::cout << "config parameter \"" << option_name << "\" not set\n";
                    throw ex; // our work done. finish program;
                }
            };

        try {
            try_get_option(configure_options.data_path, "data-path");
            try_get_option(configure_options.settings_path, "settings-path");
            try_get_option(configure_options.saves_path, "saves-path");
        } catch (const std::exception& ex) {
            return {};
        }
    }

    return configure_options;
}

}

# endif // SK_READ_OPTIONS_HPP_
