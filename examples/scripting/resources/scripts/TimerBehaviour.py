from suborbital import PythonBehaviour

class TimerBehaviour(PythonBehaviour):
    def __init__(self):
        PythonBehaviour.__init__(self)
        self.time_elapsed = 0.0
        print("Timer::Timer()")
    def __del__(self):
        print("Timer::~Timer()")
    def create(self):
        print("Timer::create()")
    def update(self, dt):
        self.time_elapsed += dt
        print(str(self.time_elapsed) + " seconds have elapsed")