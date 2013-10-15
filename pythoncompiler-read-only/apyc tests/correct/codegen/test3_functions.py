def func1():
	print "Dentro de func1()"
	
def func2(x::Int, y::Int):
	print "Dentro de func2(), no usamos los parametros"
	
def func3():
	return 5
	
def func4(z::Int):
	return z * z
	
def fac(n::Int):
	if n == 1:
		return 1
	
	if n < 0:
		print "El factorial de un numero negativo no esta definido"
		return -1
	
	factAnterior::Int = fac(n - 1)
	return n * factAnterior # n * fac(n - 1) no pasa el semant

def main():
	func1()
	func2(3, 4)
	print "El valor de retorno de la func3() es: ", func3()
	print "4^2 es: ", func4(4)
	print "El factorial de 10 es: ", fac(10)
