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
should not crash.

Note: Due to the large number of templates, it is slow to
compile and creates a very large executable file.

Copyright
---------

The Insight Software Consortium (http://www.insightsoftwareconsortium.org)
holds the copyright of this software. This is a non-profit entity that
promotes the use of ITK for educational and research purposes. See LICENSE
for details.