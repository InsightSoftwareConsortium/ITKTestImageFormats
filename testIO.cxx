#include <itkImageIOFactory.h>
#include <itkImageIOBase.h>

int main(int argc, char* argv[])
{
  if( argc !=2 )
  {
    std::cerr<<"Usage: " << argv[0] << " filename"<<std::endl;
    return 1;
  }
  std::cout<< "File name: " << argv[1] << std::endl;
  itk::ImageIOBase *io = itk::ImageIOFactory::CreateImageIO(argv[1], itk::ImageIOFactory::ReadMode);
  std::cout<<"IO name: " << io->GetNameOfClass()<<std::endl;
  return 0;
}
