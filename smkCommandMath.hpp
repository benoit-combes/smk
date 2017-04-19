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
    const char USAGE[] =
            R"(Usage: smk math [--type=<type] <output> = <input_1> <operator> <input_2>

            Options:
            --type=<type>  type of the output [default: FLOAT].

            Perform basic mathematical operation between the image given as input and an operand."
            Give a numeric constant as the operand is the same as give an image filled with the constant.
            Available operators are:

            - '+' pixel wise addition of tow images
            - '-' pixel wise substraction of tow images
            - '*' pixel wise multiplication of tow images
            - '/' pixel wise division of tow images
            - '^' Compute the powers of tow images"

            The option type let you decide the component type of the output image."
            "Available types are:"

            - 'UCHAR'
            - 'CHAR'
            - 'UINT'
            - 'INT'
            - 'SHORT'
            - 'USHORT'
            - 'LONG'
            - 'ULONG'
            - 'FLOAT'
            - 'DOUBLE'

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
    m_type = args["--type"].asString();
    if(m_type != "UCHAR" &&
            m_type != "CHAR" &&
            m_type != "UINT" &&
            m_type != "INT" &&
            m_type != "SHORT" &&
            m_type != "USHORT" &&
            m_type != "LONG" &&
            m_type != "ULONG" &&
            m_type != "FLOAT" &&
            m_type != "DOUBLE"){
        std::cerr << "Option --type: '" << m_operator << "' is invalid."<< std::endl;
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
        if(m_type == "UCHAR"){
            typedef itk::Image<unsigned char, Dimension> OutputType;
            _create_filter<InputType, OutputType>();
        } else if (m_type == "CHAR") {
            typedef itk::Image<char, Dimension> OutputType;
            _create_filter<InputType, OutputType>();
        } else if (m_type == "UINT") {
            typedef itk::Image<unsigned int, Dimension> OutputType;
            _create_filter<InputType, OutputType>();
        } else if (m_type == "INT") {
            typedef itk::Image<int, Dimension> OutputType;
            _create_filter<InputType, OutputType>();
        } else if (m_type == "USHORT") {
            typedef itk::Image<unsigned short, Dimension> OutputType;
            _create_filter<InputType, OutputType>();
        } else if (m_type == "SHORT") {
            typedef itk::Image<short, Dimension> OutputType;
            _create_filter<InputType, OutputType>();
        } else if (m_type == "ULONG") {
            typedef itk::Image<unsigned long, Dimension> OutputType;
            _create_filter<InputType, OutputType>();
        } else if (m_type == "LONG") {
            typedef itk::Image<long, Dimension> OutputType;
            _create_filter<InputType, OutputType>();
        } else if (m_type == "FLOAT") {
            typedef itk::Image<float, Dimension> OutputType;
            _create_filter<InputType, OutputType>();
        } else if (m_type == "DOUBLE") {
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
