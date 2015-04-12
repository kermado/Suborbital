from suborbital import PythonBehaviour
import HealthAttribute
import random

class AttackRandomEnemyBehaviour(PythonBehaviour):

    def __init__(self):
        PythonBehaviour.__init__(self)

    def create(self):
        pass

    def update(self, dt):
        entities = self.entity.scene.entities.all
        if entities.size > 1:
            target = self.random_element_from_set(entities)
            while target == self.entity:
                target = self.random_element_from_set(entities)
            if target.alive:
                damage_to_inflict = random.random() * 10
                target.attribute(HealthAttribute).decrease(damage_to_inflict)

    def random_element_from_set(self, set):
        iterator = set.begin + random.randint(0, set.size - 1)
        return iterator.value()