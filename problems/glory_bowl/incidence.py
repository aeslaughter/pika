"""
python /Users/slauae/projects/pika/problems/glory_bowl/incidence.py
"""

import vtk
import chigger

camera = vtk.vtkCamera()
camera.SetViewUp(-0.0553502928, 0.3394174291, 0.9390059392)
camera.SetPosition(505486.1755259125, 4815093.4675858906, 3281.0416862892)
camera.SetFocalPoint(504697.6296582069, 4816748.0223565381, 2636.4973379626)

reader = chigger.exodus.ExodusReader('solar_out.e')
reader.setOptions(block=['0'])

result = chigger.exodus.ExodusResult(reader)
result.setOptions(edge_color=[0, 0, 0], cmap='inferno', variable='solar_incidence', block=['0'], min=90.0, max=180.0, local_range=True, camera=camera)

cbar = chigger.exodus.ExodusColorBar(result)
cbar.setOptions(colorbar_origin=(0.8, 0.25, 0.0))
cbar.setOptions('primary', lim=[90.0, 180.0], font_color=[0,0,0], title='Solar Incidence (degress)')

window = chigger.RenderWindow(result, cbar, background=[1,1,1])
window.update()
window.resetCameraClippingRange()
#window.start()

for i, t in enumerate(reader.getTimes()):
    reader.setOptions(timestep=i)
    window.write('output/incidence_{:03d}.png'.format(i))

chigger.utils.img2mov('output/incidence_*.png', 'incidence.mp4', duration=60)
