from suborbital import PythonAttribute
from EntityDiedEvent import EntityDiedEvent

class HealthAttribute(PythonAttribute):

    def __init__(self):
        PythonAttribute.__init__(self)

    def create(self):
        self.health = 100

    def reset(self):
        self.health = 100

    def value(self):
        return self.health

    def decrease(self, amount):
        self.health -= amount
        if self.health <= 0:
            self.health = 0
            self.entity.destroy()
            self.entity.scene.publish(EntityDiedEvent(self.entity.name))

    def increase(self, amount):
        self.health += amount
        if self.health > 100:
            self.health = 100