def main():
	x::Int = 80
	y::Int = -6
	if -100 <= x <= 100 and -10 * 10 <= y <= 100:
		if x < y:
			z::Int = y - x
		else:
			z::Int = x - y
		print "El valor de x es: ", x
		print "El valor de y es: ", y
		print "La diferencia es: ", z
	else:
		print "Operandos fuera de rango."
