from suborbital import PythonEvent

class EntityDiedEvent(PythonEvent):

    def __init__(self):
        PythonEvent.__init__(self)