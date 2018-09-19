"""
python /Users/slauae/projects/pika/problems/photon/view.py
"""

import vtk
import chigger
import mooseutils

camera = vtk.vtkCamera()
camera.SetViewUp(0.0000, 1.0000, 0.0000)
camera.SetPosition(0.5000, 5.0000, 19.4149)
camera.SetFocalPoint(0.5000, 5.0000, 0.0000)

reader = chigger.exodus.ExodusReader(u'photon_diffusion_out.e')
reader.setOptions(variables=['u'])

result = chigger.exodus.ExodusResult(reader, viewport=[0, 0, 0.25, 1], cmap='viridis')

data = mooseutils.VectorPostprocessorReader('/Users/slauae/projects/pika/problems/photon/photon_diffusion_out_vertical_*.csv')
y = data('y')
x = data('u')

c = 2.28e8
h = 6.626070040e-34
l = 500e-9
energy = x/(h*c/l)

line = chigger.graphs.Line(x=list(energy), y=list(y), corner='left-bottom', label='k', color=[1,1,1])

graph = chigger.graphs.Graph(line, legend={'visible':False}, viewport=[0.25, 0, 1, 1,])
#graph.setOptions('xaxis', title='X-Axis')
#graph.setOptions('yaxis', title='y-Axis')

window = chigger.RenderWindow(result, graph)
window.start()
