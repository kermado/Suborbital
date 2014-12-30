from suborbital import *

class ExampleBehaviour(PythonBehaviour):

    def __init__(self):
        PythonBehaviour.__init__(self)
        print("ExampleBehaviour::ExampleBehaviour()")

    def __del__(self):
        print("ExampleBehaviour::~ExampleBehaviour()")

    def create(self):
        example = self.entity().attribute("ExampleAttribute")
        example.value("awesome!")
        example.log()
        self.entityDiedSubscription = self.entity().subscribe("EntityDiedEvent", self.onEntityDied)

    def update(self, dt):
        e = self.entity()
        health = e.attribute("HealthAttribute")
        health.decrease(10)
        print("Health = " + str(health.value()))

    def onEntityDied(self, event):
        print(self.entity().name().upper() + " has gone to a better place".upper())
