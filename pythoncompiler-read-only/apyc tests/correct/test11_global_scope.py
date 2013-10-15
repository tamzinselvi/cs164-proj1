i = 3

class class1:
	j = i
	i = 4
	k = i
	
	def method1(self):
		i = 5
		print i
		
	def method2(self):
		print i
		
def func1():
	i = 6
	print i
	
print i
a = class1()
a.method1()
print i
a.method2()
print i
func1()
print i
print "----"
print a.j
print a.k
