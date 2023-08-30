# include <options.hpp>
# include <config.hpp>

# include <boost/program_options.hpp>

# include <spdlog/spdlog.h>
# include <tracy/Tracy.hpp>

# include <iostream>
# include <fstream>
# include <format>

std::optional<sk::ConfigureOptions> sk::read_options(int argc, const char* argv[]) noexcept {
    namespace po = boost::program_options;
    using std::filesystem::path;

    ZoneScopedNC("read options", tracy::Color::Blue);

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
            std::cout << std::format("unrecognised command line option {}\n", ex.get_option_name());
            return {};
        } catch (const std::exception& ex) {
            spdlog::error("parse command line exception: {}", ex.what());
            return {};
        }

        if (command_line_variables.count("help")) {
            allowed_options_desc.print(std::cout);
            return {};
        }

        if (command_line_variables.count("version")) {
            std::cout << std::format("opensk version {}\n", sk::config::version_string());
            return {};
        }
    }

    sk::ConfigureOptions configure_options{};

    {   // handle config file
        auto config_file = std::ifstream(config_file_path);
        if (!config_file) {
            spdlog::error("couldn't open config file");
            return {};
        }

        po::variables_map configure_variables{};

        try {
            po::parsed_options configure_parsed_options = po::parse_config_file(config_file, configure_options_desc);
            po::store(configure_parsed_options, configure_variables);
            po::notify(configure_variables);
        } catch (const po::error_with_option_name& ex) {
            std::cout << std::format("unrecognised configure option {}\n", ex.get_option_name());
            return {};
        } catch (const std::exception& ex) {
            spdlog::error("parse config file exception: {}", ex.what());
            return {};
        }

        auto try_get_option =
            [&configure_variables](auto& option_place, const char* option_name) {
                try {
                    option_place = std::move(configure_variables.at(option_name).as<decltype(option_place)>());
                } catch (const std::out_of_range& ex) {
                    std::cout << std::format("config parameter '{}' not set\n", option_name);
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
