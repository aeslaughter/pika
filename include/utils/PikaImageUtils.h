
// VTK includes
#include "vtkSmartPointer.h"
#include "vtkBMPReader.h"
#include "vtkPNGReader.h"
#include "vtkImageData.h"

// MOOSE includes
#include "MooseUtils.h"

namespace PikaImageUtils
{

template<typename T>
vtkImageData * readImageHelper(std::string file_name)
{
  vtkSmartPointer<T> reader = vtkSmartPointer<T>::New();
  reader->SetFileName(file_name.c_str());
  reader->Update();
  return reader->GetOutput();
}

vtkImageData * readImage(std::string file_name);

} // namespace PikaImageUitls
