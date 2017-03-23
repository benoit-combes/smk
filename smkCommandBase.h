#pragma once

#include <docopt.h>

#include <vector>

namespace smk {
namespace Command {
/**
 * @brief Base class for Command object
 *
 * Overload '_doc()' to return the help message that must be print for
 * your command. The help message must fullfill the docopt requirements,
 * see: https://github.com/docopt/docopt.cpp#help-message-format
 *
 * Overload '_execute(std::map<std::string, docopt::value> args)' to execute,
 * the piece of code you want to be executed by your command. You can
 * access the commanf line arguments via the args parameter thanks to docopt
 * for examples:
 *
 *      'args.["<parameter_foo>"].asString()' for a string.
 *      'args.["--option_bar"].asStringList()' for an option that accept multiple values.'
 *
 * see
 *
 */
class Base
{
public:
    Base(){}
    virtual ~Base(){}

    void execute(std::vector<std::string> const& argv,
                 std::string version,
                 bool option_first);

protected:
    virtual std::string _doc() = 0;
    virtual void _execute(std::map<std::string, docopt::value> args) = 0;
};

}// EON Command
}// EON smk
