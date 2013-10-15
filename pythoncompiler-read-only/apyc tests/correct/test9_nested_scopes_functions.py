def func1():
	i = 3
	def func2():
		i = 4
		
		def func3():
			i = 5
			print i
		
		func3()
		print i
	
	func2()	
	print i

func1()
