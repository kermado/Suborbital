from suborbital import PythonScene

class ExampleScene(PythonScene):

    def __init__(self):
        PythonScene.__init__(self)
        print("ExampleScene::ExampleScene()")

    def __del__(self):
        print("ExampleScene::~ExampleScene()")

    def create(self):
        example_system = self.create_system("ExampleSystem")

        entity = self.create_entity("Player 1")
        entity.create_attribute("ExampleAttribute")
        entity.create_attribute("HealthAttribute")
        entity.create_behaviour("ExampleBehaviour")

    def update(self, dt):
        pass

    def suspend(self):
        pass

    def resume(self):
        pass