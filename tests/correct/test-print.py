class Test:
  def write(self, text):
    print text

x = Test()
print
print "Line1"
print "Line2",
print "Line2a", "Line2b"
print "Line3a", "Line3b",
print >> x
print >> x, "Line4"
print >> x, "Line5",
print "End"
