# rise
Prototype robot for quickly creating simple, destroyable representations of 3D-modelled parts, made from small iron cubes
Based on mechanical system of RepRap 3D printers;
Pictures of CAD (without motors) and produced prototype in "issues" tab

Operating principle:
1) CAD models are transformed, processed and sent as code containing 16x8x8 matrix information to arduino
2) arduino controls
  a) pushing cylinders, which kick metal cubes down guiding columns of guiding matrix (grey block in CAD pictures)
  b) stepper motors, which move cube dispenser along guiding matrix
