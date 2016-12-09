from PIL import Image

length = 128
width = 128

def init_pixel_data(pixel_data, length, width, color = (0,0,0)):
	for i in xrange(length):
		for j in xrange(width):
			# img.putpixel((i, j), )		
			pixel_data.append( color )



def draw_line(x1, x2, y1, y2, width, pixel_data):
	dx = x2 - x1
	dy = y2 - y1

	ux = 1 if  x2 > x1 else -1
	uy = 1 if y2 > y1 else -1

	x = x1
	y = y1
	eps = 0
	dx = abs(dx)
	dy = abs(dy)

	if dx > dy:
		for i in xrange(x1, x2, ux):
			draw_point(y, i, pixel_data, width)

			eps += dy

			if eps * 2>= dx:
				y += uy
				eps -= dx
	else:
		for i in xrange(y1, y2, uy):
			draw_point(i, x, pixel_data, width)

			eps += dx

			if eps * 2 >= dy:
				x += ux
				eps -= dy


def draw_line_float(x1, x2, y1, y2, width, pixel_data):
	ux = 1 if  x2 > x1 else -1
	uy = 1 if y2 > y1 else -1

	dx = x2 - x1
	dy = y2 - y1

	
	dx = abs(dx)
	dy = abs(dy)
	
	if dx > dy:
		m = float(dy)/dx
		counter = 0
		for x in xrange(x1, x2, ux):
			y = int(round(y1 + counter * m * uy))
			draw_point(y, x, pixel_data, width)
			counter += 1
	else:
		m = float(dx)/dy
		counter = 0
		for y in xrange(y1, y2, uy):
			x = int(round(x1 + counter * m * ux))
			draw_point(y, x, pixel_data, width)
			counter += 1


def draw_point(x, y, pixel_data, width, radius = 1):
	pixel_data[(length - y)*width + (width - x)] = (255,255,255)




if __name__ == '__main__':
	img = Image.new('RGB', (length,width))

	pixel_data = []

	init_pixel_data(pixel_data, length, width)

	# draw_point(100, 50, pixel_data, width)

	import time
	t = time.time()

	for i in xrange(10000):
		draw_line_float(60, 30, 120, 10, width, pixel_data)

	print 'float time:', time.time() - t
	t = time.time()


	for i in xrange(10000):
		draw_line(60, 30, 120, 10, width, pixel_data)

	print 'int time:', time.time() - t
	t = time.time()


	img.putdata( pixel_data )

	img.show()










