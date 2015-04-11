from suborbital import PythonAttribute

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

    def increase(self, amount):
        self.health += amount
        if self.health > 100:
            self.health = 100