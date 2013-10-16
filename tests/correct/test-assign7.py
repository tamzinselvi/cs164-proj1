# Assign to target list (3).

L = 1, 2, (3, 4),

(a, b, c) = L
print a, b, c

a = b = c = 0

(b, a, cd) = L
(c, d) = cd
print a, b, c, d

a, b, c = L
print a, b, c

b, a, cd = L
c, d = cd
print a, b, c, d

[a, b, c] = L
print a, b, c

[b, a, cd] = L
c, d = cd
print a, b, c, d
