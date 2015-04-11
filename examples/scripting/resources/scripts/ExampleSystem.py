from suborbital import PythonSystem

class ExampleSystem(PythonSystem):

    def __init__(self):
        PythonSystem.__init__(self)

    def create(self):
        self.entities = self.scene().entities().all()

    def process(self, dt):
        print("Processing " + str(self.entities.size()) + " entities")

        for entity in self.entities:
            print("Processing Entity(" + entity.name() + ")")
