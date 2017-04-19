#pragma once

#include "smkCommandInfo.h"

#include "smkImageTypeHelpers.h"
#include "smkIO.h"

#include <itkImageIOFactory.h>

#include <iomanip>

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
    try {
        SMK_RETRIEVE_COMPONENT_TYPE(m_IO, _retreive_nb_dimension)
    }
    catch ( itk::ExceptionObject & err ) {
        std::cerr << "smk cannot show image information, be sure to use valid arguments..." << std::endl;
        std::cerr << err << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

template <typename ComponentType>
void Info::_retreive_nb_dimension()
{
    SMK_RETRIEVE_NUMBER_OF_DIMENSIONS(m_IO, ComponentType, _retreive_nb_component)
}

template <typename ComponentType, int dimension>
void Info::_retreive_nb_component()
{
    SMK_RETRIEVE_NUMBER_OF_COMPONENTS(m_IO, ComponentType, dimension, _print_info)
}

template <typename ImageType>
void Info::_print_info()
{
    typename ImageType::Pointer img = IO::read<ImageType>(m_filename);
    typename ImageType::RegionType extent = img->GetLargestPossibleRegion();
    unsigned int dim = extent.GetImageDimension();
    std::string t_mark = "##############################\n### - ";
    std::string u_mark = "";

    std::cout << t_mark << "Dimension:" << u_mark << std::endl << dim << std::endl << std::endl;

    std::cout << t_mark << "Index:" << u_mark  << std::endl << extent.GetIndex() << std::endl << std::endl;

    std::cout << t_mark << "Size:" << u_mark  << std::endl << extent.GetSize() << std::endl << std::endl;

    std::cout << t_mark << "Spacing:" << u_mark  << std::endl << img->GetSpacing() << std::endl << std::endl;

    std::cout << t_mark << "Origin:" << u_mark  << std::endl << img->GetOrigin() << std::endl << std::endl;

    typename ImageType::DirectionType dir = img->GetDirection();
    std::cout << t_mark << "Direction:" << u_mark  << std::endl;

    for (unsigned int i = 0; i < dim; ++i) {
        std::cout << "|" << dir[i][0];
        for (unsigned int j = 1; j < dim; ++j)
            std::cout << std::setw(8) << dir[i][j];
        std::cout << "|" << std::endl;
    }
    std::cout << std::endl;

    typename ImageType::DirectionType invdir = img->GetInverseDirection();
    std::cout << t_mark << "Inverse Direction: " << u_mark  << std::endl;

    for (unsigned int i = 0; i < dim; ++i) {
        std::cout << "|" << invdir[i][0];
        for (unsigned int j = 1; j < dim; ++j)
            std::cout << std::setw(10) << invdir[i][j];
        std::cout << "|" << std::endl;
    }
}

} // EON Command
} // EON smk
