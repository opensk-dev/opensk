# include <read_options.hpp>

int main(int argc, const char* argv[]) {
    auto options = sk::read_options(argc, argv);
    if (!options) return 0;

    return 0;
}
