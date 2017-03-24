#pragma once

#include "smkCommandBase.h"

#include <itkImageIOBase.h>

namespace smk {
namespace Command {

class Info : public Base {

    std::string m_filename;
    itk::ImageIOBase::Pointer m_IO;

    virtual std::string _doc();
    virtual int _execute(std::map<std::string, docopt::value> args);

    template <class ComponentType>
    void _retreive_nb_dimension();

    template <class ComponentType, int dimension>
    void _retreive_nb_component();

    template <class ImageType>
    void _print_info();

};

} // EON Command
} // EON smk

#include "smkCommandInfo.hpp"
