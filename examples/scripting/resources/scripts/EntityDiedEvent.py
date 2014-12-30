from suborbital import *

class EntityDiedEvent(PythonEvent):

    def __init__(self):
        PythonEvent.__init__(self)
        print("EntityDiedEvent::EntityDiedEvent()")

    def __del__(self):
        print("EntityDiedEvent::~EntityDiedEvent()")