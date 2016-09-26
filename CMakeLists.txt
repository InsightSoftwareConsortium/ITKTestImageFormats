cmake_minimum_required(VERSION 3.5)
project(ITKTestImageFormats)


find_package(SlicerExecutionModel REQUIRED)
include(${SlicerExecutionModel_USE_FILE})
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

SEMMacroBuildCLI(
  NAME ITKTestImageFormats
  TARGET_LIBRARIES
    ${ITK_LIBRARIES}
  )

target_compile_features(ITKTestImageFormatsLib PUBLIC cxx_generalized_initializers)
target_compile_features(ITKTestImageFormats PUBLIC cxx_generalized_initializers)
