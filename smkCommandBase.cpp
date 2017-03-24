#include "smkCommandBase.h"

namespace smk {
namespace Command {

int Base::execute(std::vector<std::string> const& argv,
                   std::string version,
                   bool option_first)
{
    std::map<std::string, docopt::value> args
            = docopt::docopt(this->_doc(),
                             argv,
                             true,          // show help
                             version,
                             option_first);
    return this->_execute(args);
}

} // EON Command
} // EON smk
