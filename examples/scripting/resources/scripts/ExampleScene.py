from suborbital import PythonScene
from scripting import ExampleAttribute
from HealthAttribute import HealthAttribute
from AttackRandomEnemyBehaviour import AttackRandomEnemyBehaviour
from EntityDiedEvent import EntityDiedEvent
import random

class ExampleScene(PythonScene):

    def __init__(self):
        PythonScene.__init__(self)

    def create(self):
        self.subscription = self.subscribe(EntityDiedEvent, self.on_entity_died)
        for i in range(0, 10):
            entity = self.create_entity("Player " + str(i + 1))
            entity.create_attribute(HealthAttribute)
            entity.create_behaviour(AttackRandomEnemyBehaviour)

    def update(self, dt):
        pass

    def suspend(self):
        pass

    def resume(self):
        pass

    def on_entity_died(self, event):
        print(event.entity_name + " was " + random.choice(["killed", "obliterated", "annihilated", "exterminated",
            "neutralized", "liquidated", "murdered", "executed", "assassinated", "eradicated", "eliminated"]))
        entities = self.entities.all
        if entities.size <= 1:
            victor = entities.begin.value()
            print("-----------------------------------")
            print(victor.name + " was victorious!")
            print("-----------------------------------")