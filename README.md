# C++ Wrapers around python's matplotlib

Embeds the python interpreter, so it's heavy handed.
Usefull if plots have to be generated as part of a build process.
It's based on [matplotlib-cpp](https://github.com/lava/matplotlib-cpp).

Differences:

* This one is not header-only, Cmake scripts are provided
* This one uses [pybind11](https://github.com/pybind/pybind11), to reduce the amount of plumbing code.
* This one has an explicit object to keep the livetime of the python interpreter.

Minimal example:

```
#include <matplotlib.h>

int main()
{
    Eigen::ArrayXd x = Eigen::ArrayXd::LinSpaced(20, 0, 4);
    Eigen::ArrayXd y = x.sin();

    MatplotLib p;
	p.figure();
	p.plot(x, y);
}
```
