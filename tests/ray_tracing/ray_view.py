"""
python /Users/slauae/projects/pika/tests/ray_tracing/ray_view.py
"""

import vtk
import chigger

camera = vtk.vtkCamera()
camera.SetViewUp(0.0000, 1.0000, 0.0000)
camera.SetPosition(2.5544, 0.4976, 5.8028)
camera.SetFocalPoint(2.5544, 0.4976, 0.0000)

ray_reader = chigger.exodus.ExodusReader(u'ray_out.e')
ray_result = chigger.exodus.ExodusResult(ray_reader)
ray_result.setOptions(edge_color=[0, 0, 0], camera=camera)

vol_reader = chigger.exodus.ExodusReader(u'optics_out.e')
vol_result = chigger.exodus.ExodusResult(vol_reader)
vol_result.setOptions(variable='phase', cmap='viridis', edges=True, edge_color=[1,1,1], camera=camera)

window = chigger.RenderWindow(vol_result, ray_result)
timer = chigger.base.ChiggerTimer(window, terminate=True)
window.setOptions()
window.write('test.png')
window.start(timer=timer)
