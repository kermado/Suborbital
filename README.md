# Suborbital component-oriented entity framework

## Overview

**Please note that this project is currently under development and is not ready for production.**

Suborbital is a lightweight component-oriented entity framework for games, written in C++11. It is heavily inspired by both the Unity game engine and a presentation given by [Marcin Chady][1] at GDC Canada in 2009. The concept differs slightly from Entity Component Systems (ECS), such as that used by [Artemis][2].

The framework includes bindings for Python scripting, which are generated using [SWIG][3]. Components can be defined in both C++ source files or python scripts. It is possible to expose components implemented in C++ to Python but the converse is not currently possible.

[1]: http://www.gdcvault.com/play/1911/
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

## Getting started

You will find some basic sample programs inside of the `examples` directory.

### Defining attributes

Attributes can be easily defined in Python scripts. Provided below is a minimal complete example:

```python
from suborbital import PythonAttribute

class SomeAttribute(PythonAttribute):
    def __init__(self):
        PythonAttribute.__init__(self)
    def create(self):
        pass
```

Note that `self.entity` is null inside of the constructor. The parent entity is injected into the attribute after construction but before `create`. You should place any initialization code that requires accessing the entity that the component is attached to inside of `create`. 

### Defining behaviours

Behaviours can easily be similarly defined in Python scripts. Provided below is a minimal complete example:

```python
from suborbital import PythonBehaviour

class SomeBehaviour(PythonBehaviour):
    def __init__(self):
        PythonBehaviour.__init__(self)
    def create(self):
        pass
    def update(self, dt):
        pass
```

Entity game logic should be executed from the `update` function. This function is called once per state update. Behaviours can write and read to and from attributes. For example:

```python
class MoveBehaviour(PythonBehaviour):
    [...]
    def create(self):
        self.transform = self.entity.attribute(TransformAttribute)
    def update(self, dt):
        self.transform.translate(0, 0, 1)
    [...]
```

### Defining events

Events are the last of the basic building blocks that can be defined in Python scripts. Provided below is a minimal complete example:

```python
from suborbital import PythonEvent

class ExampleEvent(PythonEvent):
    def __init__(self):
        PythonEvent.__init__(self)

```

Attributes and behaviours can both publish and subscribe for events. For example:

```python
class HealthAttribute(PythonAttribute):
    [...]
    def reset(self):
        self.health = 100
    def decrement(self, amount):
        self.health -= amount
        if self.health <= 0:
            self.entity.publish(EntityDiedEvent())
    [...]

class RespawnBehaviour(PythonBehaviour):
    [...]
    def create(self):
        self.transform = self.entity.attribute(TransformAttribute)
        self.health = self.entity.attribute(HealthAttribute)
        self.subscription = self.entity.subscribe(EntityDiedEvent, self.on_entity_died)
    def on_entity_died(self, event):
        self.transform.position(0, 0, 0)
        self.health.reset()
    [...]
```

You can `publish` and `subscribe` for events at both the `Scene` and `Entity` levels. It is also possible to `broadcast` events downwards from the scene to all entities and their descendants, or from a particular entity downwards to any descendant entities.

### Adding components to entities

You can add both Python and C++ defined components to entities:

```cpp
some_entity->create_attribute("SomeAttribute"); // Add a Python defined attribute
some_entity->create_attribute<SomeAttribute>(); // Add a C++ defined attribute
some_entity->create_behaviour("SomeBehaviour"); // Add a Python defined behaviour
some_entity->create_behaviour<SomeBehaviour>(); // Add a C++ defined behaviour
```

Or, for example, from inside of a Python script:

```python

some_entity.create_attribute(SomePythonDefinedAttribute) # Add a Python defined attribute
some_entity.create_attribute(SomeCppDefinedAttribute)    # Add a C++ defined attribute that has been exposed to Python
some_entity.create_behaviour(SomePythonDefinedBehaviour) # Add a Python defined behaviour
some_entity.create_behaviour(SomeCppDefinedBehaviour)    # Add a C++ defined behaviour that has been exposed to Python

```

Note the any C++ defined components must be exposed to Python before it is possible to add them to entities.

### Scenes: Tying it all together

Scenes are the basic container inside of which entities live. All entities must be created within either a scene or another entity. It is possible to define scenes in Python scripts:

```python
class ExampleScene(PythonScene):
    def __init__(self):
        PythonScene.__init__(self)
        entity = self.create_entity("Player")
        entity.create_attribute(HealthAttribute)
        entity.create_behaviour(RespawnBehaviour)
        
    def update(self, dt):
        pass
        
    def suspend(self):
        pass
        
    def resume(self):
        pass
```

The `update` function is called before updating all of the entities in the scene. The `suspend` and `resume` functions are called when a scene becomes inactive and active respectively. This occurs when scenes are pushed onto the scene stack or popped off of the scene stack.

### Exposing C++ defined types to Python

See `examples/scripting`.

## Authors

 * Omar Kermad

## License (MIT)

Copyright (C) 2014
Omar Kermad

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
