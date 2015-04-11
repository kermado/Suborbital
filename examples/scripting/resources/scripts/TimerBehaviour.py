from suborbital import PythonBehaviour

class TimerBehaviour(PythonBehaviour):

    def __init__(self):
        PythonBehaviour.__init__(self)
        self.elapsed = 0.0

    def create(self):
        pass

    def update(self, dt):
        self.elapsed += dt
        print(str(self.elapsed) + " seconds have elapsed")