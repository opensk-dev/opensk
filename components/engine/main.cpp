# include <read_options.hpp>

int main(int argc, const char* argv[]) {
    auto options = sk::read_options(argc, argv);
    if (!options) return 0;

    std::cout << options->data_path << '\n';
    std::cout << options->settings_path << '\n';
    std::cout << options->saves_path << '\n';

    return 0;
}
