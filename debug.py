from serial import Serial
from turtle import Turtle, setworldcoordinates

MAX = 65535

t = Turtle()

class Touch:
	def __init__(self):
		self.s = Serial('/dev/ttyACM0', 115200)

	def get_touch(self):
		while True:
			try:
				evt = [int(i.split('=', 2)[1].strip()) for i in self.s.readline().decode('utf-8').split(' ') if len(i) >= 3]

				if len(evt) == 3 and evt[2] < 100000:
					return evt
			except Exception as e:
				print(e)
				pass

class Calibrator:
	def run(self, touch):
		minX = MAX
		maxX = 0
		minY = MAX
		maxY = 0

		while True:
			X, Y, pressure = touch.get_touch()

			if X < minX:
				minX = X
			if X > maxX:
				maxX = X

			if Y < minY:
				minY = Y
			if Y > maxY:
				maxY = Y

			print("int minX = {}, maxX = {};".format(minX, maxX))
			print("int minY = {}, maxY = {};".format(minY, maxY))
			print("")

class Render:
	def run(self, touch):
		RESOLUTION_X = 180
		RESOLUTION_Y = 230
		MAX = 65535

		setworldcoordinates(-1, -1, RESOLUTION_X, RESOLUTION_Y)
		t.speed(0)

		minX = 15078; maxX = 36855;
		minY = 18613; maxY = 51230;


		def m(val, fa, fb, res):
			if val > fb:
				val = fb

			val -= fa

			if val < 0:
				val = 0

			return val / (fb - fa) * res

		while True:
			X, Y, pressure = touch.get_touch()
			if pressure > 100000:
        			continue


			x = RESOLUTION_X - m(X, minX, maxX, RESOLUTION_X)
			y = RESOLUTION_Y - m(Y, minY, maxY, RESOLUTION_Y)

			t.pendown()
			t.goto(x, y)
			print(X, Y, x, y, pressure)


touch = Touch()
#Calibrator().run(touch)
Render().run(touch)
