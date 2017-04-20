#pragma once

#include "smkCommandWrite.h"

#include "smkImageTypeHelpers.h"
#include "smkIO.h"

#include <itkImageIOFactory.h>

namespace smk {
namespace Command {

std::string Write::_doc()
{
    const char USAGE[] = R"(
Usage:
    smk write [options] <input_filename> <output_filename>

Options:
    -c <type>, --component_type <type>       Component type of the output [default: INPUT].


#######################################################################################

Write a new image from the image given as input default behavior is just copy
of the input.

The file format of the output is determined by the extension used for its filename.
(Recomanded: Nrrd format - .nrrd)

Available file foramts are:

    FORMAT              EXTENSION
    ----------------------------------------------------------------
    * Nrrd              '.nrrd, .nhdr'
    Bitmap              '.bmp'
    Bio-rad PIC         '.pic'
    DICOM               '.dcm, .DCM'
    GIPL                '.gilp[.gz]'
    Jpeg                '.jpeg, .JPEG, .jpg, .JPG'
    LSM                 '.lsm, .LSM'
    MRC                 '.mrc, .rec'
    Meta image file     '.mha, .mhd'
    Nifti               '.nii[.gz], .hdr[.gz], .img[.gz], .nia[.gz]'
    PNG                 '.png, .PNG'
    Stimulate           '.spr'
    TIFF                '.tiff, .TIFF, .tif, .TIF'
    VTK                 '.vtk'

More details on: https://itk.org/Wiki/ITK/File_Formats

The option --component_type let you decide the component type of the output image.
Available types are:

    C++ TYPE            VALUE
    --------------------------------------
    * Same as Input     'INPUT'
    unsigned char       'UCHAR'
    char                'CHAR'
    unsigned int        'UINT'
    int                 'INT'
    short               'SHORT'
    unsigned short      'USHORT'
    long                'LONG'
    unsigned long       'ULONG'
    float               'FLOAT'
    double              'DOUBLE'
)";
    return USAGE;
}

int Write::_execute(std::map<std::string, docopt::value> args)
{
    m_input = args["<input_filename>"].asString();
    m_output = args["<output_filename>"].asString();
    m_IO = IO::create_IO(m_input);

    m_component = args["--component_type"].asString();
    if(m_component != "INPUT" &&
            m_component != "UCHAR" &&
            m_component != "CHAR" &&
            m_component != "UINT" &&
            m_component != "INT" &&
            m_component != "SHORT" &&
            m_component != "USHORT" &&
            m_component != "LONG" &&
            m_component != "ULONG" &&
            m_component != "FLOAT" &&
            m_component != "DOUBLE"){
        std::cerr << "Option --component_type: '" << m_component << "' is invalid."<< std::endl;
        return EXIT_FAILURE;
    }

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

template <typename ComponentType>
void Write::_retreive_nb_dimension()
{
    SMK_RETRIEVE_NUMBER_OF_DIMENSIONS(m_IO, ComponentType, _write)
}


template <typename ComponentType, int Dimension>
void Write::_write()
{
    std::cout << std::endl;
    typedef itk::VectorImage<ComponentType, Dimension> InputType;

    if(m_component == "INPUT"){
        typedef itk::Image<ComponentType, Dimension> OutputType;
        smk::IO::write<OutputType>(m_output, smk::IO::read<OutputType>(m_input));
    } else if(m_component == "UCHAR"){
        typedef itk::Image<unsigned char, Dimension> OutputType;
        smk::IO::write<OutputType>(m_output, smk::IO::read<OutputType>(m_input));
    } else if (m_component == "CHAR") {
        typedef itk::Image<char, Dimension> OutputType;
        smk::IO::write<OutputType>(m_output, smk::IO::read<OutputType>(m_input));
    } else if (m_component == "UINT") {
        typedef itk::Image<unsigned int, Dimension> OutputType;
        smk::IO::write<OutputType>(m_output, smk::IO::read<OutputType>(m_input));
    } else if (m_component == "INT") {
        typedef itk::Image<int, Dimension> OutputType;
        smk::IO::write<OutputType>(m_output, smk::IO::read<OutputType>(m_input));
    } else if (m_component == "USHORT") {
        typedef itk::Image<unsigned short, Dimension> OutputType;
        smk::IO::write<OutputType>(m_output, smk::IO::read<OutputType>(m_input));
    } else if (m_component == "SHORT") {
        typedef itk::Image<short, Dimension> OutputType;
        smk::IO::write<OutputType>(m_output, smk::IO::read<OutputType>(m_input));
    } else if (m_component == "ULONG") {
        typedef itk::Image<unsigned long, Dimension> OutputType;
        smk::IO::write<OutputType>(m_output, smk::IO::read<OutputType>(m_input));
    } else if (m_component == "LONG") {
        typedef itk::Image<long, Dimension> OutputType;
        smk::IO::write<OutputType>(m_output, smk::IO::read<OutputType>(m_input));
    } else if (m_component == "FLOAT") {
        typedef itk::Image<float, Dimension> OutputType;
        smk::IO::write<OutputType>(m_output, smk::IO::read<OutputType>(m_input));
    } else if (m_component == "DOUBLE") {
        typedef itk::Image<double, Dimension> OutputType;
        smk::IO::write<OutputType>(m_output, smk::IO::read<OutputType>(m_input));
    }
}

} // EON Command
} // EON smk
