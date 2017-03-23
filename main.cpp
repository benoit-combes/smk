#include "docopt.h"

#include <iostream>

int main(int argc, const char** argv) {

    const char USAGE[] =
    R"(Usage: smk [-help] [--version] <command> [<args>...]

        Options:
          -h --help     Show this screen.
          -v --version     Show version.


        smk in a basic set of tools for medical images manipulation.

        The image files format supported are the one readable with the ITK library,"
        see https://itk.org/Wiki/ITK/File_Formats for more details.


        The available commands are:"
            info:           Provide basic informations on an images
    )";
    std::vector<std::string> const& std_args = {argv + 1, argv + argc};
    bool show_help = true;
    std::string smk_version= std::string("smk version ") + smk_VERSION;
    bool option_first;

    std::map<std::string, docopt::value> args
            = docopt::docopt(USAGE,
                             std_args,
                             show_help,
                             smk_version,
                             option_first);

    std::string command = args["<command>"].asString();
    if(command == "info") {

    }
    else {
        std::cout << "smk: '" << command << "' is not a smk command. See 'smk --help'."
                  <<std::endl;
    }

    return EXIT_SUCCESS;
}
