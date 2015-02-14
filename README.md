# cpp-whatisthisgame

This is a copy of my game
[whatisthisgame](http://github.com/crockeo/whatisthisgame) written in C++
instead of Haskell.

This branch (`clibgame`) is a re-implementation of this project translating some
of the features over to code in my
[clibgame](http://github.com/crockeo/clibgame) project.

### Building

You need CMake version `>= 2.8` for building.

Before you build this project you're going to need to install the libraries for
[clibgame](http://github.com/crockeo/clibgame). If you go over there and follow
the install instructions, you should be set for this portion.

```bash
$ cmake .
$ make
$ ./build/bin/whatisthisgame
```

### TODOs

* Making the render function render the vertices inputted. **DONE**
* Move the render function from the `other` shader program to the `game2d`
  shader program. **DONE**
* Make the shader loading (for the fragment output) more dynamic. **DONE**
* Make layering work. **DONE**

### License

Refer to the `LICENSE` file for licensing information.
