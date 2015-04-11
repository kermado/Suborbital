from suborbital import PythonBehaviour
from scripting import ExampleAttribute
import HealthAttribute

class ExampleBehaviour(PythonBehaviour):

    def __init__(self):
        PythonBehaviour.__init__(self)

    def create(self):
        self.example = self.entity.attribute(ExampleAttribute)
        self.example.value("You can even write your components in c++ and interface with them from Python!")
        self.example.log()

        self.health = self.entity.attribute(HealthAttribute)
        self.died_subscription = self.entity.subscribe("EntityDiedEvent", self.on_entity_died)

    def update(self, dt):
        self.health.decrease(10)
        print("Health = " + str(self.health.value()))

    def on_entity_died(self, event):
        print(self.entity.name().upper() + " has gone to a better place".upper())
        self.health.reset()