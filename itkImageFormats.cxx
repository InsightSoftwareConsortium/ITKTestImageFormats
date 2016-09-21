#include <itkImage.h>
#include <itkImageFileWriter.h>
#include <itkImageFileReader.h>
#include <itkRGBAPixel.h>
#include <itkRGBPixel.h>
#include <itkOffset.h>
#include <itkVector.h>
#include <itkSymmetricSecondRankTensor.h>
#include <itkCovariantVector.h>
#include <itkDiffusionTensor3D.h>
#include <itkFixedArray.h>
#include <itkMatrix.h>
#include <itkTestingComparisonImageFilter.h>
#include <itkImageRegionIterator.h>
#include <itkImageIOFactory.h>
#include <itkImageIOBase.h>

#include <algorithm>

#include "itkImageFormatsCLP.h"

template<typename PixelType, unsigned int Dimension>
void CreateAndSaveImage(std::string filename,
                        const char* componentTypeName,
                        const char* pixelTypeName
                       )
{
  std::string ioReaderName;
  std::string ioWriterName;
      std::cout << filename << ", " << ioWriterName << ", " << ioReaderName << ", " << Dimension << ", " << componentTypeName << ", " << pixelTypeName << ", before" << std::endl;
  try
  {
    typedef itk::Image<PixelType, Dimension> ImageType;
    typename ImageType::Pointer image = ImageType::New();
    typename ImageType::SizeType size;
    size.Fill(10);
    image->SetRegions(size);
    image->Allocate();
    image->SetRegions(size);
    // No initialization
    //image->FillBuffer(itk::NumericTraits<PixelType>::Zero);
    typedef itk::ImageFileWriter<ImageType> WriterType;
    typename WriterType::Pointer writer = WriterType::New();
    writer->SetFileName(filename);
    writer->SetInput(image);
    writer->Update();
    ioWriterName = writer->GetImageIO()->GetNameOfClass();
    itk::ImageIOBase::Pointer io = itk::ImageIOFactory::CreateImageIO(filename.c_str(), itk::ImageIOFactory::ReadMode);
    if (io.IsNull())
    {
      std::cout << filename << ", " << ioWriterName << ", " << ioReaderName << ", " << Dimension << ", " << componentTypeName << ", " << pixelTypeName << ", No reader" << std::endl;
      return;
    }
    ioReaderName = io->GetNameOfClass();
    typedef itk::ImageFileReader<ImageType> ReaderType;
    typename ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName(filename);
    reader->Update();
    typedef itk::ImageRegionIterator<ImageType> IteratorType;
    IteratorType it(image, image->GetLargestPossibleRegion());
    IteratorType it_reader(reader->GetOutput(), reader->GetOutput()->GetLargestPossibleRegion());
    for( it.GoToBegin(), it_reader.GoToBegin(); !it.IsAtEnd(); ++it, ++it_reader)
    {
      if(it.Get() != it_reader.Get())
      {
        std::cout << filename << ", " << ioWriterName << ", " << ioReaderName << ", " << Dimension << ", " << componentTypeName << ", " << pixelTypeName << ", No reader" << std::endl;
        return;
      }
    }
  }
  catch(itk::ExceptionObject& err)
  {
    std::string err_string = err.GetDescription();
    std::replace(err_string.begin(), err_string.end(), '\n', ' ');
    std::cout << filename << ", " << ", " << ioWriterName << ", " << ioReaderName << ", " << Dimension << ", " << componentTypeName << ", " << pixelTypeName << ", " << err_string << std::endl;
    return;
  }
  catch(...)
  {
    std::cout << filename << ", " << ioWriterName << ", " << ioReaderName << ", " << Dimension << ", " << componentTypeName << ", " << pixelTypeName << ", Other Exception" << std::endl;
    return;
  }
  std::cout << filename << ", " << ioWriterName << ", " << ioReaderName << ", " << Dimension << ", " << componentTypeName << ", " << pixelTypeName << ", Success" << std::endl;
}

template<typename PixelType, unsigned int Dimension>
void CreateAndSaveImageScalars(std::string filename,
                               const char* componentTypeName,
                               const char* pixelTypeName
                              )
{
  std::string ioReaderName;
  std::string ioWriterName;
      std::cout << filename << ", " << ioWriterName << ", " << ioReaderName << ", " << Dimension << ", " << componentTypeName << ", " << pixelTypeName << ", before" << std::endl;
  try
  {
    typedef itk::Image<PixelType, Dimension> ImageType;
    typename ImageType::Pointer image = ImageType::New();
    typename ImageType::SizeType size;
    size.Fill(10);
    image->SetRegions(size);
    image->Allocate();
    image->SetRegions(size);
    image->FillBuffer(itk::NumericTraits<PixelType>::Zero);
    typedef itk::ImageFileWriter<ImageType> WriterType;
    typename WriterType::Pointer writer = WriterType::New();
    writer->SetFileName(filename);
    writer->SetInput(image);
    writer->Update();
std::cout<<"after writer update()"<<std::endl;
    ioWriterName = writer->GetImageIO()->GetNameOfClass();
    itk::ImageIOBase::Pointer io = itk::ImageIOFactory::CreateImageIO(filename.c_str(), itk::ImageIOFactory::ReadMode);
    if (io.IsNull())
    {
      std::cout << filename << ", " << ioWriterName << ", " << ioReaderName << ", " << Dimension << ", " << componentTypeName << ", " << pixelTypeName << ", No reader" << std::endl;
      return;
    }
    ioReaderName = io->GetNameOfClass();
std::cout<<"after io getnameofclass()"<<std::endl;
    typedef itk::ImageFileReader<ImageType> ReaderType;
    typename ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName(filename);
    reader->Update();
std::cout<<"after reader update()"<<std::endl;
    typedef itk::Testing::ComparisonImageFilter< ImageType, ImageType > CompareType;
    typename CompareType::Pointer compare = CompareType::New();
    compare->SetValidInput(image);
    compare->SetTestInput(reader->GetOutput());
    compare->SetToleranceRadius(0);
    compare->Update();
std::cout<<"after compare update()"<<std::endl;
    const unsigned long numberOfPixelsWithDifferences =
                        compare->GetNumberOfPixelsWithDifferences();
    if(numberOfPixelsWithDifferences > 0)
    {
      std::cout << filename << ", " << ioWriterName << ", " << ioReaderName << ", " << Dimension << ", " << componentTypeName << ", " << pixelTypeName << ", Failure" << std::endl;
      return;
    }
  }
  catch(itk::ExceptionObject& err)
  {
    std::string err_string = err.GetDescription();
    std::replace(err_string.begin(), err_string.end(), '\n', ' ');
    std::cout<<filename<< ", " << ", " << ioWriterName << ", " << ioReaderName << ", " << Dimension <<", "<< componentTypeName << ", "<< pixelTypeName << ", " << err_string <<std::endl;
    return;
  }
  catch(...)
  {
    std::cout << filename << ", " << ioWriterName << ", " << ioReaderName << ", " << Dimension << ", " << componentTypeName << ", " << pixelTypeName << ", Other Exception" << std::endl;
    return;
  }
  std::cout << filename << ", " << ioWriterName << ", " << ioReaderName << ", " << Dimension << ", " << componentTypeName << ", " << pixelTypeName << ", Success" << std::endl;
}


template<typename ComponentType, unsigned int Dimension>
void SelectPixelType(const char* filename,
                     std::vector<itk::ImageIOBase::IOPixelType> pixel,
                     const char* componentTypeName
                    )
{
  for( size_t ii = 0 ; ii < pixel.size() ; ii++)
  {
    if(pixel[ii]==itk::ImageIOBase::IOPixelType::SCALAR)
    {
      CreateAndSaveImageScalars<ComponentType, Dimension>(filename, componentTypeName, "Scalar");
    }
    else if(pixel[ii]==itk::ImageIOBase::IOPixelType::RGBA)
    {
      CreateAndSaveImage<itk::RGBAPixel<ComponentType>, Dimension>(filename, componentTypeName, "RGBA");
    }
    else if(pixel[ii]==itk::ImageIOBase::IOPixelType::RGB)
    {
      CreateAndSaveImage<itk::RGBPixel<ComponentType>, Dimension>(filename, componentTypeName, "RGB");
    }
    else if(pixel[ii]==itk::ImageIOBase::IOPixelType::OFFSET)
    {
      CreateAndSaveImage<itk::Offset<3>, Dimension>(filename, componentTypeName, "Offset");
    }
//    else if(pixel[ii]==itk::ImageIOBase::IOPixelType::VECTOR)
//    {
//      CreateAndSaveImage<itk::Vector<ComponentType,3>, Dimension>(filename, componentTypeName, "Vector");
//    }
//    else if(pixel[ii]==itk::ImageIOBase::IOPixelType::POINT)
//    {
//      CreateAndSaveImage<itk::Point<ComponentType,3>, Dimension>(filename, componentTypeName, "Point");
//    }
//    else if(pixel[ii]==itk::ImageIOBase::IOPixelType::COVARIANTVECTOR)
//    {
//      CreateAndSaveImage<itk::CovariantVector<ComponentType,3>, Dimension>(filename, componentTypeName, "CovariantVector");
//    }
//    else if(pixel[ii]==itk::ImageIOBase::IOPixelType::SYMMETRICSECONDRANKTENSOR)
//    {
//      CreateAndSaveImage<itk::SymmetricSecondRankTensor<ComponentType,3>, Dimension>(filename, componentTypeName, "SymmetricSecondRankTensor");
//    }
//    else if(pixel[ii]==itk::ImageIOBase::IOPixelType::DIFFUSIONTENSOR3D)
//    {
//      CreateAndSaveImage<itk::DiffusionTensor3D<ComponentType>, Dimension>(filename, componentTypeName, "DiffusionTensor3D");
//    }
//    else if(pixel[ii]==itk::ImageIOBase::IOPixelType::COMPLEX)
//    {
//      CreateAndSaveImage<std::complex<ComponentType>, Dimension>(filename, componentTypeName, "Complex");
//    }
//    else if(pixel[ii]==itk::ImageIOBase::IOPixelType::FIXEDARRAY)
//    {
//      CreateAndSaveImage<itk::FixedArray<ComponentType,3>, Dimension>(filename, componentTypeName, "FixedArray");
//    }
//    else if(pixel[ii]==itk::ImageIOBase::IOPixelType::MATRIX)
//    {
//      CreateAndSaveImage<itk::Matrix<ComponentType,3,3>, Dimension>(filename, componentTypeName, "Matrix");
//    }
////    else if(pixel[ii]==itk::ImageIOBase::IOPixelType::UNKNOWNPIXELTYPE)
////    {
////      CreateAndSaveImage<std::vector<ComponentType>, Dimension>(filename, componentTypeName, "std::vector/unknown");
////    }
  }
}

template<unsigned int Dimension>
void SelectComponentType(const char* filename,
                         std::vector<itk::ImageIOBase::IOPixelType> pixel,
                         std::vector<itk::ImageIOBase::IOComponentType> components
                        )
{
  for( size_t ii = 0 ; ii < components.size() ; ii++)
  {
//    if(components[ii]==itk::ImageIOBase::IOComponentType::UCHAR)
//    {
//      SelectPixelType<unsigned char, Dimension>(filename, pixel, "uchar");
//    }
//    else if(components[ii]==itk::ImageIOBase::IOComponentType::CHAR)
//    {
//      SelectPixelType<char, Dimension>(filename, pixel, "char");
//    }
//    else if(components[ii]==itk::ImageIOBase::IOComponentType::SHORT)
//    {
//      SelectPixelType<short, Dimension>(filename, pixel, "short");
//    }
//    else if(components[ii]==itk::ImageIOBase::IOComponentType::USHORT)
//    {
//      SelectPixelType<unsigned short, Dimension>(filename, pixel, "ushort");
//    }
//    else if(components[ii]==itk::ImageIOBase::IOComponentType::UINT)
//    {
//      SelectPixelType<unsigned int, Dimension>(filename, pixel, "uint");
//    }
//    else if(components[ii]==itk::ImageIOBase::IOComponentType::INT)
//    {
//      SelectPixelType<int, Dimension>(filename, pixel, "int");
//    }
//    else if(components[ii]==itk::ImageIOBase::IOComponentType::ULONG)
//    {
//      SelectPixelType<unsigned long, Dimension>(filename, pixel, "ulong");
//    }
//    else if(components[ii]==itk::ImageIOBase::IOComponentType::LONG)
//    {
//      SelectPixelType<long, Dimension>(filename, pixel, "long");
//    }
    if(components[ii]==itk::ImageIOBase::IOComponentType::FLOAT)
    {
      SelectPixelType<float, Dimension>(filename, pixel, "float");
    }
    else if(components[ii]==itk::ImageIOBase::IOComponentType::DOUBLE)
    {
      SelectPixelType<double, Dimension>(filename, pixel, "double");
    }
//    else if(components[ii]==itk::ImageIOBase::IOComponentType::UNKNOWNCOMPONENTTYPE)
//    {
//      SelectPixelType<bool, Dimension>(filename, pixel, "bool/unknown");
//    }
  }
}

void SelectDimension(const char* extension,
                     std::vector<int> dim,
                     std::vector<itk::ImageIOBase::IOPixelType> pixel,
                     std::vector<itk::ImageIOBase::IOComponentType> components
                    )
{
  std::string filename = std::string("test")+extension;
  for(size_t ii = 0 ; ii < dim.size() ; ii++)
  {
    if( dim[ii] == 1)
    {
      SelectComponentType<1>(filename.c_str(), pixel, components);
    }
//    if( dim[ii] == 2)
//    {
//      SelectComponentType<2>(filename.c_str(), pixel, components);
//    }
//    else if(dim[ii] == 3)
//    {
//      SelectComponentType<3>(filename.c_str(), pixel, components);
//    }
//    else if(dim[ii] ==4)
//    {
//      SelectComponentType<4>(filename.c_str(), pixel, components);
//    }
//    else if(dim[ii]==5)
//    {
//      SelectComponentType<5>(filename.c_str(), pixel, components);
//    }
    if(dim[ii] == 6)
    {
      SelectComponentType<6>(filename.c_str(), pixel, components);
    }
  }
}

int main(int argc, char* argv[])
{
  PARSE_ARGS;
  if(!onlyExtensions.empty() && !skipExtensions.empty())
  {
    std::cerr << "You can specify only one of the two following options: onlyExtensions, skipExtensions" << std::endl;
    return 1;
  }
  if(!onlyDimensions.empty() && !skipDimensions.empty())
  {
    std::cerr << "You can specify only one of the two following options: onlyDimensions, skipDimensions" << std::endl;
    return 1;
  }
  std::vector<int> dim;
  if(onlyDimensions.empty() )
  {
    dim = {1, 2, 3, 4, 5, 6};
  }
  else
  {
    dim = onlyDimensions;
  }
  for(size_t ii = 0 ; ii < skipDimensions.size(); ii++)
  {
    if( std::find(dim.begin(), dim.end(), skipDimensions[ii]) != dim.end())
    {
      dim.erase(std::remove(dim.begin(), dim.end(), skipDimensions[ii]), dim.end());
    }
  }
  std::vector<itk::ImageIOBase::IOPixelType> pixel = { itk::ImageIOBase::IOPixelType:: UNKNOWNPIXELTYPE, itk::ImageIOBase::IOPixelType::SCALAR, itk::ImageIOBase::IOPixelType::RGBA, itk::ImageIOBase::IOPixelType::RGB, itk::ImageIOBase::IOPixelType::OFFSET, itk::ImageIOBase::IOPixelType::VECTOR, itk::ImageIOBase::IOPixelType::COVARIANTVECTOR, itk::ImageIOBase::IOPixelType::SYMMETRICSECONDRANKTENSOR, itk::ImageIOBase::IOPixelType::DIFFUSIONTENSOR3D, itk::ImageIOBase::IOPixelType::COMPLEX, itk::ImageIOBase::IOPixelType::FIXEDARRAY, itk::ImageIOBase::IOPixelType::MATRIX, itk::ImageIOBase::IOPixelType::POINT};
  std::vector<itk::ImageIOBase::IOComponentType> components = {itk::ImageIOBase::IOComponentType::UNKNOWNCOMPONENTTYPE, itk::ImageIOBase::IOComponentType::UCHAR, itk::ImageIOBase::IOComponentType::FLOAT,  itk::ImageIOBase::IOComponentType::CHAR, itk::ImageIOBase::IOComponentType::USHORT, itk::ImageIOBase::IOComponentType::SHORT, itk::ImageIOBase::IOComponentType::UINT, itk::ImageIOBase::IOComponentType::INT, itk::ImageIOBase::IOComponentType::ULONG, itk::ImageIOBase::IOComponentType::LONG, itk::ImageIOBase::IOComponentType::DOUBLE};

  std::list< itk::LightObject::Pointer > allobjects = itk::ObjectFactoryBase::CreateAllInstance("itkImageIOBase");
  itk::ImageIOBase::ArrayOfExtensionsType listExtensions;
  if (allobjects.size() > 0)
  {
    for( std::list< itk::LightObject::Pointer >::iterator i = allobjects.begin(); i != allobjects.end(); ++i )
    {
      itk::ImageIOBase *io = dynamic_cast< itk::ImageIOBase * >( i->GetPointer() );
      if( std::find(skipIOs.begin(), skipIOs.end(), io->GetNameOfClass()) == skipIOs.end())
      {
        itk::ImageIOBase::ArrayOfExtensionsType currentExtensions = io->GetSupportedWriteExtensions();
        for(size_t ii = 0 ; ii < currentExtensions.size(); ii++)
        {
          if( std::find(skipExtensions.begin(), skipExtensions.end(), currentExtensions[ii]) ==  skipExtensions.end())
          {
            if( onlyExtensions.empty() )
            {
              listExtensions.push_back(currentExtensions[ii]);
            }
            else
            {
              if( std::find(onlyExtensions.begin(), onlyExtensions.end(), currentExtensions[ii]) !=  onlyExtensions.end())
              {
                listExtensions.push_back(currentExtensions[ii]);
              }
            }
          }
        }
      }
    }
  }
  else
  {
    std::cerr << "  There are no registered IO factories." << std::endl;
    std::cerr << "  Please visit https://www.itk.org/Wiki/ITK/FAQ#NoFactoryException to diagnose the problem." << std::endl;
    return 1;
  }
  if(listExtensions.empty())
  {
    std::cerr<<"No supported extension found"<<std::endl;
    return 1;
  }
  std::cout<< "List extensions: ";
  for( size_t ii = 0 ; ii < listExtensions.size(); ii++)
  {
    std::cout<<listExtensions[ii] << ",";
  }
  std::cout<<std::endl;
  std::cout<<"Filename, IOName, Dimension, Component, Pixel, Result"<<std::endl;
  for(size_t ii = 0; ii < listExtensions.size(); ii++)
  {
    SelectDimension(listExtensions[ii].c_str(), dim, pixel, components );
  }
  return 0;
}
