# A* Path-Finding Algorithm

A* is a popular path-finding algorithm for a grid based world. My implementation is in C++, but it's potential is in any language. 

```c++
Vector2D.h && Vector2D.cpp are the files that hold the simple vector class; which holds a few manipulative functions, as well as 2D directions (x, y)
```

```c++
Old.cpp is junk
```

```c++
Heuristic.cpp && Heuristic.h calculate the Heuristic value in the algorithm
```
If you don't know what a heuristic is; it's basically a guess at the remaining distance to the end point.
I came up with two different methods of achieving the same result. One using a recursive design, and the other with simple math. I'll have to clean this file up greatly.

```c++
Main.cpp
```

This is the gold plot. Lots and lots and lots of For loops, structs; and a whole bunch of awesome things.
I'm in the process of commenting each section, and cleaning it up nicely. Right now i'm just making it "work".