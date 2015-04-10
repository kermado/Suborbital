from suborbital import PythonScene
from scripting import ExampleAttribute
import HealthAttribute
import AttackRandomEnemyBehaviour

class ExampleScene(PythonScene):

    def __init__(self):
        PythonScene.__init__(self)
        print("ExampleScene::ExampleScene()")

    def __del__(self):
        print("ExampleScene::~ExampleScene()")

    def create(self):
        for i in range(0, 5):
            entity = self.create_entity("Player " + str(i + 1))
            entity.create_attribute(HealthAttribute)
            entity.create_behaviour(AttackRandomEnemyBehaviour)

    def update(self, dt):
        pass

    def suspend(self):
        pass

    def resume(self):
        pass