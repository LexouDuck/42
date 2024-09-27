# rtv1

This is a simple interactive raytracer 3D display engine

### format

You can find test files in the `./tests` folder, they have a `.rt` extension.
Each file is a scene which can hold several objects and lights.
For each object, you must specify the color, position, dimensions, and rotation.

### controls

- mouse scroll wheel : zoom
- mouse right click + drag : rotate camera around anchor point
- mouse left click + drag : camera panning (move anchor up/down/left/right)
- mouse middle click + drag vertical : camera advance (move anchor point forwards/backwards)
- mouse middle click + drag horizontal : camera tilt up-vector (dutch angle)
- keyboard `←`/`→`: move along X axis
- keyboard `↑`/`↓`: move along Y axis
- keyboard `PGUP`/`PGDN`: move along Z axis
- keyboard `DELETE` : toggle rendering diffuse light
- keyboard `HOME` : toggle rendering shadows
- keyboard `END` : toggle rendering specular highlights
