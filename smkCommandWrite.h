#pragma once

#include "smkCommandBase.h"

#include <itkImageIOBase.h>

namespace smk {
namespace Command {

class Write : public Base
{

    std::string m_input;
    std::string m_output;
    std::string m_component;
    itk::ImageIOBase::Pointer m_IO;

    virtual std::string _doc();
    virtual int _execute(std::map<std::string, docopt::value> args);

    template <typename ComponentType>
    void _retreive_nb_dimension();

    template <typename ComponentType, int Dimension>
    void _write();
};

} // EON Command
} // EON smk

#include "smkCommandWrite.hpp"
