from suborbital import *

class ExampleBehaviour(PythonBehaviour):
    def __init__(self):
        PythonBehaviour.__init__(self)
        print("ExampleBehaviour::ExampleBehaviour()")
    def __del__(self):
        print("ExampleBehaviour::~ExampleBehaviour()")
    def create(self):
        e = self.entity()
        example = e.attribute("ExampleAttribute")
        example.value("awesome!")
        example.log()
    def update(self, dt):
        e = self.entity()
        health = e.attribute("HealthAttribute")
        health.decrease(10)
        print("Health = " + str(health.value()))
