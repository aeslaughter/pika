
// Pika includes
#include "PikaImageUtils.h"

// Moose includes
#include "MooseError.h"

namespace PikaImageUtils
{


PikaImage::PikaImage(const std::string & file_name)
{
  if (MooseUtils::hasExtension(file_name, "png"))

    _reader = vtkSmartPointer<vtkImageReader2>::Take(vtkPNGReader::SafeDownCast(readImageHelper<vtkPNGReader>(file_name)));


  //else if (MooseUtils::hasExtension(file_name, "bmp"))
  //  _reader = readImageHelper<vtkBMPReader>(file_name);

  else
    mooseError("Unable to read the image " << file_name);

}

vtkImageData *
PikaImage::data()
{
  return _reader->GetOutput();

}

} // namespace PikaImageUtils
