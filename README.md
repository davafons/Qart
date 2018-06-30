# QArt

_"Quadtree generated images"_

This program is a visualization of an __"image compression"__ algorithm based on the use of __Quadtrees__. 

This algorithm divides the image into __squares (or rectangles)__. Starting with a square of the same size of the image, it calculates:
* The __average color__: Adding up each R, G, B and A component separately for each pixel, and dividing by the total amount of pixels in the square.
* The __error__: Difference between the averaged color and the R, G, B, A component for each pixel.

Then, the algorithm will find the square with the __highest error__ (The least refined). Such square will be divided into __four sub-square__, halving its size, and again, calculating the average color and error of each sub-square.

The algorithm will be __repeated N times__ until all the squares have an error of __0__.

## Release

Precompiled versions for Windows and Linux
* [Qart 1.0.0 Linux](https://github.com/Dibad/Qart/releases/download/v1.0.0/Qart-1.0.0-linux.tar.gz)
* [Qart 1.0.0 Windows](https://github.com/Dibad/Qart/releases/download/v1.0.0/Qart-1.0.0-win32.zip)

## Build

* ### On Linux

Take note that SDL2 and SDL2_image dependencies must be installed first by running the following commands:
```
$ sudo apt-get install libsdl2-dev
$ sudo apt-get install libsdl2-image-dev
```
Clone the repo and make.
```
$ git clone https://github.com/Dibad/Qart
$ cd Qart
$ make
```


## Examples
View of the iterative process with every quadtree outlined (Stopped after 4029 iterations, with 12088 squares created).
![Cat](https://i.imgur.com/5mDiqZB.gif)<p>
And a view of the same process but without outlines.
![Cat2](https://i.imgur.com/MIi4Gxr.gif)

## Acknowledgments

This project idea was shared by [Michael Fogleman](https://github.com/fogleman), so please check his fantastic implementation in Python. [Link to his repository](https://github.com/fogleman/Quads)
