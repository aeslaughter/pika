
// VTK includes
#include "vtkSmartPointer.h"
#include "vtkImageReader2.h"
#include "vtkBMPReader.h"
#include "vtkPNGReader.h"
#include "vtkImageData.h"

// MOOSE includes
#include "MooseUtils.h"

namespace PikaImageUtils
{

class PikaImage
{
public:
  PikaImage(const std::string & file_name);

  vtkImageData * data();

private:

  vtkSmartPointer<vtkImageReader2> _reader;

  //vtkImageData * _data;

  template<typename T>
  vtkSmartPointer<T> readImageHelper(std::string file_name);

};


template<typename T>
vtkSmartPointer<T>
PikaImage::readImageHelper(std::string file_name)
{
  vtkSmartPointer<T> reader = vtkSmartPointer<T>::New();
  reader->SetFileName(file_name.c_str());
  reader->Update();
//  _data = reader->GetOutput();
  return reader;
}


} // namespace PikaImageUitls
