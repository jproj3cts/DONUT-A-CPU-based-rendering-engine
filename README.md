# CPU-based-rendering-engine

>>>Work in Progress.

This engine is capable of rendering any 3D shape you can produce a parametric function for and from any distance or angle. The gif below demos this for a klein bottle. 

![klein bottle]( media/klein.gif)

I adapted this from the code written by Andy Sloane, the original can be found here: https://www.a1k0n.net/2011/07/20/donut-math.html.

The original was written as an obfuscated c program, so was more about form than function. Still it was very elegant in its function.

To compile for yourself, simply run:
```
g++ donut.c -o donut -lgdi32 
```
after cd-ing into the same directory as the donut.c file.

## Planned Improvements

  1. Add a buffer to load in pixels all at once after rendering (this will stop the flicker seen at the moment).
  2. Add user input processing to allow the camera to be moved around in real time.
