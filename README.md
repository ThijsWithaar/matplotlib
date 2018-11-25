C++ Wrapers around python's matplotlib

Embeds the python interpreter, so it's heavy handed.
Usefull if plots have to be generated as part of a build process

Based on:
https://github.com/lava/matplotlib-cpp

Differences:
This one is not header-only, Cmake scripts are provided
This one uses pybind11, to reduce the amount of plumbing code.

