class BullshitWorkaround:
  def a():
    return [1,2,3,4,5,6,7,8,9,10]

  def b():
    return 4

  def c():
    return 7

BullshitWorkaround.a()[1:4]
BullshitWorkaround.a()[:3]
BullshitWorkaround.a()[BullshitWorkaround.b():BullshitWorkaround.c()]
BullshitWorkaround.a()[1+3:]
BullshitWorkaround.a()[1*4:999-993]

