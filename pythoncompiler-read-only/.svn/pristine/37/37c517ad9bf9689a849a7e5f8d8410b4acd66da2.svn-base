def ackermann(m::Int, n::Int):
	if m == 0:
		return n + 1
	if m > 0 and n == 0:
		return ackermann(m - 1, 1)
	if m > 0 and n > 0:
		return ackermann(m - 1, ackermann(m, n - 1))
	
	return -1 # No está definida para n < 0 o m < 0

def main():
	n::Int = 1
	m::Int = 4
	print "La funcion de Ackermann para n = ", n, " y m = ", m, " en la sucesion da: ", ackermann(m, n) 
