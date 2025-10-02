# toyCMS

### Steps to run simulation

1. In terminal:
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```
2. To run simulation:
     ```bash
        ./sim
3. To add or remove detector elements control the boolean in construction.hh
4. Particle Gun can be changed in generator.cc
5. Output file defined in RunAction.cc
6. Path to .hepmc file defined in sim.cc
