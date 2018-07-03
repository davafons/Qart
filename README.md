# QArt

_"Quad-generated images"_

This program shows a visualization of an __"image compression"__ algorithm.

This algorithm divides the image into __squares (or rectangles)__. Starting with a square of the same size of the image, it calculates:
* The __average color__: Adding up each R, G, B and A component separately for each pixel, and dividing by the total amount of pixels in the square.
* The __error__: Difference between the averaged color and the R, G, B, A component for each pixel.

Then, the algorithm will find the square with the __highest error__ (The least refined). Such square will be divided into __four sub-squares__, halving its size, and again, calculating the average color and error of each sub-square.

The algorithm will be __repeated N times__ until all the squares have an error of __0__.

### Quadtrees vs Ordered Sets

This algorithm can be implemented by using both a __Quadtree__ structure (as it was first implemented), or an __Ordered Sets__ (as it is implemented on master branch). The differences are in the insertion and search times:
* __Finding the rectangle with the highest error__: The __Quadtree__ has to iterate through every child, what requires __N iterations__ (and not __log(N)__ as could be expected from a tree). The __Ordered Set__, since its _ordered_, the lastest element in the structure will be the desired rect, is __constant__.
* __Inserting the sub-rectangles in the structure:__ The __Quadtree__ only needs to insert the sub-squares as leafs, what is __constant__, but the __Ordered Set__ needs to insert AND sort every sub-rectangle by its error, and it takes __4*log(N) iterations__.

## Release

Precompiled versions for Windows and Linux
* [Qart 1.1.0 Linux](https://github.com/Dibad/Qart/releases/download/v1.1.0/Qart-1.1.0-linux.tar.gz)
* [Qart 1.1.0 Windows](https://github.com/Dibad/Qart/releases/download/v1.1.0/Qart-1.1.0-win32.zip)

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
