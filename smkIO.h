#pragma once

#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkExtractImageFilter.h>

namespace smk {
namespace IO {

itk::ImageIOBase::Pointer
create_IO(std::string filename)
{
    itk::ImageIOBase::Pointer io;
    // Find out the type of the image in file
    io = itk::ImageIOFactory::CreateImageIO(filename.c_str(),
                                            itk::ImageIOFactory::ReadMode);

    // Now that we found the appropriate ImageIO class, ask it to read the meta data from the image file.
    io->SetFileName(filename);
    io->ReadImageInformation();

    return io;
}

template <class ImageType>
typename itk::SmartPointer<ImageType>
read(std::string filename) {
    typedef itk::ImageFileReader<ImageType> ReaderType;
    typename ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName(filename);

    typename itk::SmartPointer<ImageType> img;

    reader->Update();

    img = reader->GetOutput();
    return img;
}

template <class OutputImageType>
void
write(std::string filename, OutputImageType* img) {
    typedef itk::ImageFileWriter<OutputImageType> WriterType;
    typename WriterType::Pointer writer = WriterType::New();
    writer->SetUseCompression(true);
    writer->SetFileName(filename);
    writer->SetInput(img);

    writer->Update();
}

}// EON IO
}// EON smk
