# toyCMS

### Steps to run simulation

1. Check if you have dependencies listed in `CMakeLists.txt`. If not, edit it to match your system.
2. In terminal:
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```
3. To run simulation using Particle Gun:
     ```bash
        ./sim
4. To run simulation using hepMC file:
     ```bash
        ./sim -f fileName.hepmc
5. To add or remove detector elements control the boolean in construction.hh
6. Particle Gun can be changed in generator.cc
7. Output file defined in RunAction.cc
8. Keep hepmc and analysis files in the build directory.
