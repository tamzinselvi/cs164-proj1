class Test:
  def __getitem__(self, index):
    return index

A = 1
B = 2**4 + 8 % 3
a = [0,1,2]

x = Test()
print x[A,B,"hello"]
print x[A,92-1,a[0]]
