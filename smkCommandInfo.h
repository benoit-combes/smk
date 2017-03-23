#include "smkCommandBase.h"

namespace smk {
namespace Command {

class Info : public Base {

    std::string m_filename;

    virtual std::string _doc();
    virtual void _execute(std::map<std::string, docopt::value> args);
};

} // EON Command
} // EON smk
