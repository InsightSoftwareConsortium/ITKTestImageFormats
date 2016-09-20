cmake_minimum_required(VERSION 3.5)
project(itkImageFormats)

set(ListComponents}
    ITKCommon

          ITKIOImageBase
      ITKIOBMP
      ITKIOJPEG
      ITKIONRRD
      ITKIOTIFF
      ITKIOMeta
      ITKIOPNG
      ITKIONIFTI
      ITKIOGIPL
    
    ITKImageCompare
    ITKImageIntensity

)

find_package(SlicerExecutionModel REQUIRED)
include(${SlicerExecutionModel_USE_FILE})
find_package(ITK COMPONENTS ${ListComponents} REQUIRED)
include(${ITK_USE_FILE})

SEMMacroBuildCLI(
  NAME itkImageFormats
  TARGET_LIBRARIES
    ${ITK_LIBRARIES}
  )

target_compile_features(itkImageFormatsLib PUBLIC cxx_generalized_initializers)
target_compile_features(itkImageFormats PUBLIC cxx_generalized_initializers)

add_executable(testIO testIO.cxx)
target_link_libraries(testIO ${ITK_LIBRARIES})
