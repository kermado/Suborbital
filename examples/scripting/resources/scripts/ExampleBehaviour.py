from suborbital import PythonBehaviour

class ExampleBehaviour(PythonBehaviour):

    def __init__(self):
        PythonBehaviour.__init__(self)
        print("ExampleBehaviour::ExampleBehaviour()")

    def __del__(self):
        print("ExampleBehaviour::~ExampleBehaviour()")

    def create(self):
        example = self.entity.attribute("ExampleAttribute")
        example.value("awesome!")
        example.log()

        self.died_subscription = self.entity.subscribe("EntityDiedEvent", self.on_entity_died)

    def update(self, dt):
        health = self.entity.attribute("HealthAttribute")
        health.decrease(10)
        print("Health = " + str(health.value()))

    def on_entity_died(self, event):
        print(event)
        print(self.entity.name().upper() + " has gone to a better place".upper())