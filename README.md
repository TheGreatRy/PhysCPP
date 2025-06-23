# Physics Engine C++
A physics based engine that builds upon the raylib library and utilizes the raygui library. This is ALTERED code of the raylib library and includes the initial setup as well as original code in \src

## Features
This physics engine allows the creation of various body types with different parameters. It also allows spring creation between bodies with adjustable properties and reflect physics-based movement. Users are allowed to reset the scene, start and pause the simulation, and hide/unhide the settings window. There are individual settings for each body as well as global settings that can be applied

### Keyboard and Mouse Inputs
- Hide/Unhide Settings: TAB
- Create Body: Left Click
- Create Spring: Right Click on the two bodies you want to create a spring between
- Close Simulation Window: ESC

### Core Simulation
- Implements three types of physical bodies:
  - Static: Does not move under simulation forces.
  - Kinematic: Moves with predefined velocity, not influenced by physics.
  - Dynamic: Fully simulated, reacts to forces, gravity, collisions.
- Allows configuration of the following per-object parameters:
  - Mass
  - Size
  - Damping
  - Gravity Scale
  - Restitution (Bounciness)

### Spring System
- Implements spring constraints between objects.
- Each spring supports:
  - Stiffness (spring constant)
  - Damping

### GUI Features
- The GUI includes the ability to:
  - Add objects of each body type.
  - Configure parameters of individual bodies.
  - Create springs between selected bodies.
  - Adjust global simulation parameters:
    - Global gravity
    - Gravitational force
    - Spring stiffness multiplier
  - Control simulation flow:
    - Start/Stop Simulation
    - Reset Simulation (clears all objects and springs)
