from suborbital import PythonScene

class MyScene(PythonScene):

    def __init__(self):
        PythonScene.__init__(self)

    def create(self):
        print("Hello World")

    def update(self, dt):
        pass

    def suspend(self):
        pass

    def resume(self):
        pass