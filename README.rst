===================
ITKTestImageFormats
===================

About
-----

This projects helps testing ITK's IO implementations. It
has been written to verify that all ITK's IO work correctly.

The executable created by this project tries to create
ITK images with all possible pixel types and component types
for images of dimensions between 1 and 6.
This program reports whether reading or writing images
of each type was successful. If an IO does not support
certain pixel types or component types, it should throw
an itk::Exception. The report is printed in the form
of a CSV file. For readability purposes, the user may want
to redirect the output printed on the screen into a file.
If all IOs are implemented correctly, this program
should not crash. It does not mean that all IOs will
be successful at reading and writing all formats.

Note: Due to the large number of templates, it is slow to
compile and creates a very large executable file.

Typical Output
--------------

::

  itk::ImageIOBase::IOPixelType:: UNKNOWNPIXELTYPE: Not tested
  itk::ImageIOBase::IOComponentType::UNKNOWNCOMPONENTTYPE: Not tested
  List extensions: .nia,.nii,.nii.gz,.hdr,.img,.img.gz,.nrrd,.nhdr,.jpg,.JPG,.jpeg,.JPEG,.bmp,.BMP,.tif,.TIF,.tiff,.TIFF,.lsm,.LSM,.tif,.TIF,.tiff,.TIFF,.vtk,.pic,.mha,.mhd,.mrc,.rec,
  Function, Filename, IOName, Dimension, Component, Pixel, Result
  CreateAndSaveImageScalars, test.nia, , , 1, uchar, Scalar, Start
  CreateAndSaveImageScalars, test.nia, NiftiImageIO, , 1, uchar, Scalar, No reader
  CreateAndSaveImage, test.nia, , , 1, uchar, RGBA, Start
  CreateAndSaveImage, test.nia, NiftiImageIO, , 1, uchar, RGBA, No reader
  CreateAndSaveImage, test.nia, , , 1, uchar, RGB, Start
  CreateAndSaveImage, test.nia, NiftiImageIO, , 1, uchar, RGB, No reader
  CreateAndSaveImage, test.nia, , , 1, uchar, Offset, Start
  CreateAndSaveImage, test.nia, , , 1, uchar, Offset, itk::ERROR: NiftiImageIO(0x2a3b180): Can not process this pixel type for writing into nifti
  CreateAndSaveImage, test.nia, , , 1, uchar, Vector, Start
  CreateAndSaveImage, test.nia, NiftiImageIO, , 1, uchar, Vector, No reader
  CreateAndSaveImage, test.nia, , , 1, uchar, CovariantVector, Start
  CreateAndSaveImage, test.nia, , , 1, uchar, CovariantVector, itk::ERROR: NiftiImageIO(0x2a3b180): Can not process this pixel type for writing into nifti
  CreateAndSaveImage, test.nia, , , 1, uchar, SymmetricSecondRankTensor, Start
  CreateAndSaveImage, test.nia, NiftiImageIO, , 1, uchar, SymmetricSecondRankTensor, No reader
  CreateAndSaveImage, test.nia, , , 1, uchar, DiffusionTensor3D, Start
  CreateAndSaveImage, test.nia, NiftiImageIO, , 1, uchar, DiffusionTensor3D, No reader
  CreateAndSaveImage, test.nia, , , 1, uchar, Complex, Start
  CreateAndSaveImage, test.nia, , , 1, uchar, Complex, itk::ERROR: NiftiImageIO(0x2a36780): Only float or double precision complex type supported
  CreateAndSaveImage, test.nia, , , 1, uchar, FixedArray, Start
  CreateAndSaveImage, test.nia, , , 1, uchar, FixedArray, itk::ERROR: NiftiImageIO(0x2a3b180): Can not process this pixel type for writing into nifti
  CreateAndSaveImage, test.nia, , , 1, uchar, Matrix, Start
  CreateAndSaveImage, test.nia, , , 1, uchar, Matrix, itk::ERROR: NiftiImageIO(0x2a3c3e0): Can not process this pixel type for writing into nifti
  CreateAndSaveImage, test.nia, , , 1, uchar, Point, Start
  CreateAndSaveImage, test.nia, , , 1, uchar, Point, itk::ERROR: NiftiImageIO(0x2a3b180): More than one component per pixel not supported

Sucessful reader and writer
---------------------------
::

  CreateAndSaveImage, test.nii, NiftiImageIO, NiftiImageIO, 2, uchar, Vector, Success

Copyright
---------

The Insight Software Consortium (http://www.insightsoftwareconsortium.org)
holds the copyright of this software. This is a non-profit entity that
promotes the use of ITK for educational and research purposes. See LICENSE
for details.

Blah blah
