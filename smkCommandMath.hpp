#pragma once

#include "smkCommandMath.h"

#include "smkImageTypeHelpers.h"
#include "smkIO.h"

#include <itkAddImageFilter.h>
#include <itkSubtractImageFilter.h>
#include <itkDivideImageFilter.h>
#include <itkMultiplyImageFilter.h>
#include <itkPowImageFilter.h>

namespace smk {
namespace Command {

std::string Math::_doc()
{
    const char USAGE[] =R"(
Usage:
    smk math [options] <output> = <input_1> <operator> <input_2>

Options:
    -c <type>, --component_type <type>       Component type of the output [default: FLOAT].


#######################################################################################

Perform basic mathematical operation between the image given as input and an operand.
Give a numeric constant as the operand is the same as give an image filled with the constant.
Available operators are:

    - '+' pixel wise addition of tow images
    - '-' pixel wise substraction of tow images
    - '*' pixel wise multiplication of tow images
    - '/' pixel wise division of tow images
    - '^' Compute the powers of tow images

Example: '>>> smk math I3.nrrd = I1.nrrd + I2.nrrd'
Compute the sum of I1 and I2 images.

The option type let you decide the component type of the output image.
Available types are:

    C++ TYPE            VALUE
    ----------------------------------
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

int Math::_execute(std::map<std::__cxx11::string, docopt::value> args)
{
    m_out = args["<output>"].asString();
    m_input1 = args["<input_1>"].asString();
    m_operator = args["<operator>"].asString();
    if(m_operator != "+" &&
            m_operator != "-" &&
            m_operator != "*" &&
            m_operator != "/" &&
            m_operator != "^" ){
        std::cerr << "Operator: '" << m_operator << "' is invalid."<< std::endl;
        return EXIT_FAILURE;
    }
    m_component = args["--component_type"].asString();
    if(m_component != "UCHAR" &&
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

    if(args["<input_2>"].isLong()) {
        m_constant = args["<input_2>"].asLong();
    } else {
        m_input2 = args["<input_2>"].asString();
    }

    // Find out the type of the image in file
    m_IO = IO::create_IO(m_input1);

    if(!m_IO){
        std::cerr << "Itk could not find suitable IO factory for the input" << std::endl;
        return EXIT_FAILURE;
    }

    try {
        SMK_RETRIEVE_NUMBER_OF_DIMENSIONS(m_IO, double, _check_if_components_are_vectors)
    }
    catch ( itk::ExceptionObject & err ) {
        std::cerr << "smk cannot show image information, be sure to use valid arguments..." << std::endl;
        std::cerr << err << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}



template <typename ComponentType, int Dimension>
void Math::_check_if_components_are_vectors()
{
    switch (m_IO->GetNumberOfComponents())
    {
    case 1:
    {
        typedef itk::Image<ComponentType, Dimension> InputType;
        if(m_component == "UCHAR"){
            typedef itk::Image<unsigned char, Dimension> OutputType;
            _create_filter<InputType, OutputType>();
        } else if (m_component == "CHAR") {
            typedef itk::Image<char, Dimension> OutputType;
            _create_filter<InputType, OutputType>();
        } else if (m_component == "UINT") {
            typedef itk::Image<unsigned int, Dimension> OutputType;
            _create_filter<InputType, OutputType>();
        } else if (m_component == "INT") {
            typedef itk::Image<int, Dimension> OutputType;
            _create_filter<InputType, OutputType>();
        } else if (m_component == "USHORT") {
            typedef itk::Image<unsigned short, Dimension> OutputType;
            _create_filter<InputType, OutputType>();
        } else if (m_component == "SHORT") {
            typedef itk::Image<short, Dimension> OutputType;
            _create_filter<InputType, OutputType>();
        } else if (m_component == "ULONG") {
            typedef itk::Image<unsigned long, Dimension> OutputType;
            _create_filter<InputType, OutputType>();
        } else if (m_component == "LONG") {
            typedef itk::Image<long, Dimension> OutputType;
            _create_filter<InputType, OutputType>();
        } else if (m_component == "FLOAT") {
            typedef itk::Image<float, Dimension> OutputType;
            _create_filter<InputType, OutputType>();
        } else if (m_component == "DOUBLE") {
            typedef itk::Image<double, Dimension> OutputType;
            _create_filter<InputType, OutputType>();
        }
        break;
    }
    default:
    {
    }
    }// End of switch.
}

template <typename InputType, typename OutputType>
void Math::_create_filter()
{
    if(m_operator == "+") {
        typedef itk::AddImageFilter<InputType, InputType, OutputType> FilterType;
        typename FilterType::Pointer filter = FilterType::New();
        _compute_output<FilterType>(filter);
    } else if (m_operator == "-") {
        typedef itk::SubtractImageFilter<InputType, InputType, OutputType> FilterType;
        typename FilterType::Pointer filter = FilterType::New();
        _compute_output<FilterType>(filter);
    } else if (m_operator == "*") {
        typedef itk::MultiplyImageFilter<InputType, InputType, OutputType> FilterType;
        typename FilterType::Pointer filter = FilterType::New();
        _compute_output<FilterType>(filter);
    } else if (m_operator == "/") {
        typedef itk::DivideImageFilter<InputType, InputType, OutputType> FilterType;
        typename FilterType::Pointer filter = FilterType::New();
        _compute_output<FilterType>(filter);
    } else if (m_operator == "^") {
        typedef itk::PowImageFilter<InputType, InputType, OutputType> FilterType;
        typename FilterType::Pointer filter = FilterType::New();
        _compute_output<FilterType>(filter);
    }
}

template <typename FilterType>
void Math::_compute_output(FilterType* filter)
{
        filter->SetInput1(smk::IO::read<typename  FilterType::Input1ImageType>(m_input1));
        if(m_input2 == std::string()) {
            std::cout << "pouette" << std::endl;
        } else {
            filter->SetInput2(smk::IO::read<typename  FilterType::Input2ImageType>(m_input2));
        }
        filter->Update();
        smk::IO::write<typename  FilterType::OutputImageType>(m_out, filter->GetOutput());
}

} // EON Command
} // EON smk
