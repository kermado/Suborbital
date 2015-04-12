from suborbital import PythonEvent

class EntityDiedEvent(PythonEvent):

    def __init__(self, name):
        PythonEvent.__init__(self)
        self.entity_name = name