#include "smkCommandInfo.h"

#include <iostream>

namespace smk {
namespace Command {

std::string Info::_doc()
{
    const char USAGE[] =
            R"(Usage: smk info <filename>

            Provide basic informations on the given image
            )";
    return USAGE;
}

void Info::_execute(std::map<std::string, docopt::value> args)
{
    m_filename = args["<filename>"];
}

} // EON Command
} // EON smk
