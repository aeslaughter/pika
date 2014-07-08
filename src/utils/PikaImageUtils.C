
// Pika includes
#include "PikaImageUtils.h"

// Moose includes
#include "MooseError.h"

vtkImageData *
PikaImageUtils::readImage(std::string file_name)
{
  if (MooseUtils::hasExtension(file_name, "png"))
    return readImageHelper<vtkPNGReader>(file_name);

  else if (MooseUtils::hasExtension(file_name, "bmp"))
    return readImageHelper<vtkBMPReader>(file_name);

  else
    mooseError("Un-able to read the image " << file_name);

  //return NULL;
}
