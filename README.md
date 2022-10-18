# DONUT-A-CPU-based-rendering-engine

D.O.N.U.T. (Diligently Optimised reNdering Useful Techniques), or - more gramatically - UDONT, is an engine is capable of rendering any 3D shape you can parameterize from any distance or viewing angle. The video below demos this for a klein bottle. 

https://user-images.githubusercontent.com/114860885/196288825-5b2e7a50-eee7-4fd6-adde-f124875d1ea0.mp4


I adapted this from the code written by Andy Sloane, the original can be found here: https://www.a1k0n.net/2011/07/20/donut-math.html.

To compile for yourself, simply run:
```
gcc donut.c -o donut -lgdi32 
```
after cd-ing into the same directory as the donut.c file.

>>> Note: this application currently only works on windows.

## Planned Improvements
  1. Add user input processing to allow the camera to be moved around in real time.
