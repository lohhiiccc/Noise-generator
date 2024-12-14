# perlin noise experimentations
This is a simple project to experiment with perlin noise. The project is written in c++ using X11 for the windowing system.
There are 5 different way to generate iamges using perlin noise built-in the project:

 - cloud effects using 2 superposed perlin noise
 - graph representation of perlin noise in 2D
 - marble effect
 - wood effect
 - one effect that I don't know how to describe

 ## usage:
```bash
# clone:
git clone https://github.com/lohhiiccc/Noise-generator
# compile:
make
# run:
./perlin
```

## how to use it:
- press space bar to change the effect
- press escape to quit the program
## dependencies:
 - X11
 - g++
 - make

## how it works:
The project is divided in 3 main parts:
 - the noise generation
   - cache pseudo-random gradient vectors based on seed
   - cut the image in a grid of cells
   - for each cell, generate a pseudo-random gradient vector
   - for each pixel in the cell, calculate the distance to the 4 corners of the cell and interpolate the gradient vectors
 - the image generation
   - image are basically 2D array of uint32_t
 - the x11 windowing system
   - open a connection to the X server
   - get a default root window
   - define window properties
   - create the main window
   - event handling
     - key press event
       - quit the program with escape key
       - change the effect with space bar
     - close window event
   

## How to add effects:
- create effect function in effects folder
- follow the same pointer function signature as the other effects ```int (*name)(uint32_t *image, bool &needUpdate)```
- add the effect in the ```main.cpp``` file by adding the function pointer in the vector of function pointers ```window.load_render(<new_effect_name>);```
- make again the project !

## some visual examples:
### cloud effect:
![cloud effect](https://github.com/lohhiiccc/Noise-generator/asset/cloud-perlin_noise.GIF)

### graph representation:
![graph representation](https://github.com/lohhiiccc/Noise-generator/asset/graph-perlin_noise.GIF)

### marble effect:
![marble effect](https://github.com/lohhiiccc/Noise-generator/asset/marble-perlin_noise.GIF)

### wood effect:
![wood effect](https://github.com/lohhiiccc/Noise-generator/asset/wood-perlin_noise.GIF)

### unknown effect:
![unknown effect](https://github.com/lohhiiccc/Noise-generator/asset/randoThings-perlin_noise.GIF)


# author:
 - @lohhiiccc

this is my first project with X11, i may have done some things wrong, feel free to tell me how to improve it.