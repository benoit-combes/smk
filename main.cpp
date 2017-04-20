#include "docopt.h"

#include <iostream>

#include "smkCommandInfo.h"
#include "smkCommandMath.h"
#include "smkCommandWrite.h"

int main(int argc, const char** argv) {
    int return_code = EXIT_FAILURE;

    const char USAGE[] =
            R"(Usage: smk [-help] [--version] <command> [<args>...]

            Options:
            -h --help     Show this screen.
            -v --version     Show version.


            smk is a basic set of tools for medical images manipulation.

            The image files format supported are the one readable with the ITK library,"
            see https://itk.org/Wiki/ITK/File_Formats for more details.


            The available commands are:"
            info:           Provide basic informations on an images
            math:           Perform mathematic operation: +, -, *, /...
            write           Write a new image from a given input, allow to change file format,
                            compoenent type, geometry, etc.
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

    smk::Command::Base* cmd;
    std::string command = args["<command>"].asString();
    if(command == "info") {
        cmd = new smk::Command::Info;
    } else if(command == "math") {
        cmd = new smk::Command::Math;
    } else if(command == "write") {
        cmd = new smk::Command::Write;
    } else {
        std::cout << "smk: '" << command << "' is not a smk command. See 'smk --help'."
                  <<std::endl;
        return EXIT_FAILURE;
    }
    return_code = cmd->execute(std_args,
                               smk_version,
                               option_first);
    delete cmd;

    return return_code;
}
