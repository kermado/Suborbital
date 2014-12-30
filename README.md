# Suborbital component-oriented entity framework

## Overview

**Please note that this project is currently under development and is not ready for production.**

Suborbital is a lightweight component-oriented entity framework for games, written in c++11. It is heavily inspired by both the Unity game engine and a presentation given by [Marcin Chady][1] at GDC Canada in 2009. The concept differs slightly from Entity Component Systems (ECS), such as that used by [Artemis][2]. The framework includes bindings for Python scripting, which are generated using [SWIG][3]. Components can be defined in either c++ source files or python scripts.

[1]: www.gdcvault.com/play/1911/
[2]: http://gamadu.com/artemis/index.html
[3]: http://www.swig.org/

## Requirements

 * [Python](https://www.python.org/)
 * [Swig](http://www.swig.org/) 

## Building

Use CMake to generate makefiles or platform-specific IDE projects. Unix (Linux and Mac OS X) users can compile and install the library as follows:

```
mkdir build
cd build
cmake ..
make
```

Windows users can use CMake to generate a Visual Studio project.

## Getting started

You will find some basic sample programs inside of the `examples` directory.

### Defining attributes

Attributes can be easily defined in Python scripts. Provided below is a minimal complete example:

```
from suborbital import *

class ExampleAttribute(PythonAttribute):
    def __init__(self):
        PythonAttribute.__init__(self)
    def create(self):
        pass
```

Note that `self.entity()` is null inside of the constructor. The parent entity is injected into the attribute after construction but before `create`. You should place any initialization that requires accessing the parent entity inside of `create`. 

### Defining behaviours

Like attributes, behaviours can easily be defined in Python scripts. Provided below is a minimal complete example:

```
from suborbital import *

class ExampleBehaviour(PythonBehaviour):
    def __init__(self):
        PythonBehaviour.__init__(self)
    def create(self):
        pass
    def update(self, dt):
        pass
```

Entity game logic should be executed from the `update` function. This function is called once per state update. Behaviours can write and read to and from attributes. For example:

```
class MoveBehaviour(PythonBehaviour):
    [...]
    def create(self):
        self.transform = self.entity().attribute("TransformAttribute")
    def update(self, dt):
        self.transform.translate(0, 0, 1)
    [...]
```

### Adding components to entities

You can add both Python and c++ defined components to entities:

```
Entity player("Player");
player.create_attribute("ExampleAttribute"); // Add a Python defined attribute
player.create_attribute<ExampleAttribute>(); // Add a c++ defined attribute
player.create_behaviour("MoveBehaviour"); // Add a Python defined behaviour
player.create_behaviour<MoveBehaviour>(); // Add a c++ defined behaviour
```

## Authors

 * Omar Kermad

## License (MIT)

Copyright (C) 2014
Omar Kermad

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/kermado/suborbital/trend.png)](https://bitdeli.com/free "Bitdeli Badge")

