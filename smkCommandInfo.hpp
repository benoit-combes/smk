#pragma once

#include "smkCommandInfo.h"

#include "smkImageTypeHelpers.h"
#include "smkIO.h"

#include <itkImageIOFactory.h>

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

int Info::_execute(std::map<std::string, docopt::value> args)
{
    m_filename = args["<filename>"].asString();
    // Find out the type of the image in file
    m_IO = IO::create_IO(m_filename);

    if(!m_IO){
        std::cerr << "Itk could not find suitable IO factory for the input" << std::endl;
        return EXIT_FAILURE;
    }
    try
    {
        SMK_RETRIEVE_COMPONENT_TYPE(m_IO, _retreive_nb_dimension)
    }
    catch ( itk::ExceptionObject & err )
    {
        std::cerr << "smk cannot show image information, be sure to use valid arguments..." << std::endl;
        std::cerr << err << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

template <class ComponentType>
void Info::_retreive_nb_dimension()
{
    SMK_RETRIEVE_NUMBER_OF_DIMENSIONS(m_IO, ComponentType, _retreive_nb_component)
}

template <class ComponentType, int dimension>
void Info::_retreive_nb_component()
{
    SMK_RETRIEVE_NUMBER_OF_COMPONENTS(m_IO, ComponentType, dimension, _print_info)
}

template <class ImageType>
void Info::_print_info()
{
    std::cout << IO::read<ImageType>(m_filename);
}

} // EON Command
} // EON smk
