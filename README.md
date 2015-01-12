# cpp-whatisthisgame

This is a copy of my game
[whatisthisgame](http://github.com/crockeo/whatisthisgame) written in C++
instead of Haskell.

### Building

Assuming you have CMake installed (with the minimum version of 2.8):

```bash
$ cmake .
$ make
$ ./build/bin/whatisthisgame
```

### TODOs

* Making the render function render the vertices inputted.
* Move the render function from the `other` shader program to the `game2d`
  shader program.
* Make the shader loading (for the fragment output) more dynamic.

### License

Refer to the `LICENSE` file for licensing information.
