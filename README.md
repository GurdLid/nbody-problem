# N-Body Problem

Simple demonstration of the N-Body problem with the 3 inner most planets in the Milky Way, along with Earth's moon and the Sun. 
## Description

The N-Body problem can be represented as a system of Initial Value Problems (IVPs), which can then be solved using a number of Ordinary Differential Equation (ODE) solvers. The intital solver used here is the symplectic Euler method.


## Getting Started

### Dependencies
[Premake5](https://premake.github.io/download/) is required to build the project.  
Dependencies are all within the repository. These are:
* GLFW 
* Glad
* ImGui

### Building program

For Windows:
* Simply run the "Win-Premake.bat" file 
* Open the "5BodySim.sln" file in Visual Studio  

For Linux:
* Open Terminal and enter the following commands in the project directory:
```
premake5 gmake
make -j$(nproc)
```

## Notes
The current state of the project implements a static simulation using all 5 celestial bodies. A dynamic simulation in accordance with the checkboxes is upcoming.


## License

This project is licensed under the Apache 2.0 License - see the LICENSE.md file for details

## Acknowledgments

The following two repositories for file layout inspiration and some premake settings.
* [TheCherno-OpenGL](https://github.com/TheCherno/OpenGL)
* [OpenGL-Boilerplate](https://github.com/HectorPeeters/opengl_premake_boilerplate)

