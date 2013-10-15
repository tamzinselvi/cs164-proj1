class class1(object):

	i = 3
	
	def func1(self):
		i = 4
		print i
		
	def func2(self):
		i = "Hola!"
		print i
	
	def funcPrint(self):
		print self.i

obj = class1()
obj.func1()
obj.funcPrint()
