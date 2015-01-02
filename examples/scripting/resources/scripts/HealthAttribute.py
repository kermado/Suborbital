from suborbital import PythonAttribute
from EntityDiedEvent import EntityDiedEvent

class HealthAttribute(PythonAttribute):

    def __init__(self):
        PythonAttribute.__init__(self)
        print("HealthAttribute::HealthAttribute()")

    def __del__(self):
        print("HealthAttribute::~HealthAttribute()")

    def create(self):
        self.health = 100

    def value(self):
        return self.health

    def decrease(self, amount):
        self.health -= amount
        if self.health <= 0:
            self.health = 0
            self.entity().publish("EntityDiedEvent", EntityDiedEvent())

    def increase(self, amount):
        self.health += amount
        if self.health > 100:
            self.health = 100