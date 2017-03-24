#pragma once

#include <itkImageIOBase.h>
#include <itkExceptionObject.h>
#include <itkImage.h>
#include <itkVectorImage.h>
#include <itkVector.h>
/**
  * Retrieve the type of the components of one image from an itk::ImageIOBase,
  * then call a given function templated on that type.
  *
  * IO          -> An itk::ImageIOBase setted for your image file.
  * function    -> The name of the function to call: function<ComponentType>(args, args...)
  * args...     -> A list of arguments to pass to the function.
  */
#define SMK_RETRIEVE_COMPONENT_TYPE(IO, function, ...) \
switch (IO->GetComponentType())\
{\
    case itk::ImageIOBase::UCHAR:\
        std::cerr << "Component type detected is 'UCHAR', smk only use 'char', overflow may happen" << std::endl;\
    case itk::ImageIOBase::CHAR:\
        function<char>(__VA_ARGS__);\
        break;\
    case itk::ImageIOBase::UINT:\
        std::cerr << "Component type detected is 'UINT', smk only use 'unsigned short'.\n"\
                     "Undetermine behavor may happen." << std::endl;\
    case itk::ImageIOBase::USHORT:\
        function<unsigned short>(__VA_ARGS__);\
        break;\
    case itk::ImageIOBase::INT:\
        std::cerr << "Component type detected is 'INT', smk only use 'short'."\
                     "Undetermine behavor may happen" << std::endl;\
    case itk::ImageIOBase::SHORT:\
        function<short>(__VA_ARGS__);\
        break;\
    case itk::ImageIOBase::FLOAT:\
        function<float>(__VA_ARGS__);\
        break;\
    case itk::ImageIOBase::DOUBLE:\
        function<double>(__VA_ARGS__);\
        break;\
    default:\
        std::string msg = "Component type not supported: " + itk::ImageIOBase::GetComponentTypeAsString(IO->GetComponentType());\
        itk::ExceptionObject excp(__FILE__, __LINE__, msg,ITK_LOCATION);\
        throw excp;\
}

/**
  * Retrieve the number dimension of one image from an itk::ImageIOBase,
  * then call a given function templated on that a Component type and the found number of dimension.
  *
  * IO              -> An itk::ImageIOBase setted for your image file.
  * ComponentType   -> The type used to templatized the function to call.
  * function        -> The name of the function to call.
  *                    function<ComponentType Dimensions>(args, args...)
  * args...         -> A list of arguments to pass to the function.
  */
#define SMK_RETRIEVE_NUMBER_OF_DIMENSIONS(IO, ComponentType, function, ...) \
switch (IO->GetNumberOfDimensions())\
{\
    case 3:\
        function<ComponentType, 3>(__VA_ARGS__);\
        break;\
    case 4:\
        function<ComponentType, 4>(__VA_ARGS__);\
        break;\
    default:\
        std::string msg = "Number of type not dimension: " + std::to_string(IO->GetNumberOfDimensions());\
        itk::ExceptionObject excp(__FILE__, __LINE__, msg, ITK_LOCATION);\
        throw excp;\
}


/**
  * Check if one image is a Scalar image or not from an itk::ImageIOBase,
  * then call a given function templated on either a itk::Image or itk::VectorImage
  *
  * IO              -> An itk::ImageIOBase setted for your image file.
  * ComponentType   -> The type used to templatized the function to call.
  * Dimension       -> The number of dimension on used to templatized the function yo call.
  * function        -> The name of the function to call.
  *                    function<itk::Image<ComponentType, Dimension> >(args, args...)
  *                     or
  *                    function<itk::VectorImage<ComponentType, Dimension> >(args, args...)
  * args...         -> A list of arguments to pass to the function
  */
#define SMK_CHECK_IF_COMPONENTS_ARE_VECTORS(IO, ComponentType, Dimension, function, ...) \
switch (IO->GetNumberOfComponents())\
{\
case 0:\
    {\
        std::string msg = "Number of Component not supported: 0";\
        itk::ExceptionObject excp(__FILE__, __LINE__, msg, ITK_LOCATION);\
        throw excp;\
        break;\
    }\
case 1:\
    {\
        typedef itk::Image<ComponentType, Dimension> ImageType;\
        function<ImageType>(__VA_ARGS__);\
        break;\
    }\
default:\
    {\
        typedef itk::VectorImage<ComponentType, Dimension> VectorImageType;\
        function<VectorImageType>(__VA_ARGS__);\
    }\
}

/**
  * Retrieve the number of components of one image from an itk::ImageIOBase,
  * then call a given function templated on a vector image of the right size.
  *
  * IO              -> An itk::ImageIOBase setted for your image file.
  * ComponentType   -> The type used to templatized the function to call.
  * Dimension       -> The number of dimension on used to templatized the function yo call.
  * function        -> The name of the function to call.
  *                    function<itk::Image<ik::Vector<ComponentType, ComponentSize>, Dimension> >(args, args...)
  * args...         -> A list of arguments to pass to the function
  */
#define SMK_RETRIEVE_NUMBER_OF_COMPONENTS(IO, ComponentType, dimension, function, ...) \
switch (IO->GetNumberOfComponents())\
{\
case 1:\
    function<itk::Image<ComponentType, dimension> >(__VA_ARGS__);\
    break;\
case 3:\
    function<itk::Image<itk::Vector<ComponentType, 3>, 1> >(__VA_ARGS__);\
case 6:\
    function<itk::Image<itk::Vector<ComponentType, 6>, 1> >(__VA_ARGS__);\
default:\
    std::string msg = "Number of Component not supported: " + std::to_string(IO->GetNumberOfComponents());\
    itk::ExceptionObject excp(__FILE__, __LINE__, msg, ITK_LOCATION);\
    throw excp;\
}
