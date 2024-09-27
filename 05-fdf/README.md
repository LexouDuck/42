# fdf

This is a simple program to view wireframe renderings of heightmaps

### format

You can find test files in the `./tests` folder.
These are just simple height maps, i.e. matrices where each number represent altitude of a vertex.

### controls

- mouse scroll wheel : zoom
- mouse right click + drag : rotate camera around anchor point
- mouse left click + drag : camera panning (move anchor up/down/left/right)
- mouse middle click + drag vertical : camera advance (move anchor point forwards/backwards)
- mouse middle click + drag horizontal : camera tilt up-vector (dutch angle)
- keyboard `←`/`→`: move along X axis
- keyboard `↑`/`↓`: move along Y axis
- keyboard `PGUP`/`PGDN`: move along Z axis
- keyboard `DELETE` : toggle rendering color/white
- keyboard `HOME` : toggle rendering wireframe/vertices
- keyboard `END` : toggle rendering perspective/orthgraphic
