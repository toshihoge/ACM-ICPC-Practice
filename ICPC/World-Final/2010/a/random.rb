#!/usr/bin/ruby
N = 10000
a = rand(8)+1
m = 2
x1 = rand(8)+1
x2 = rand(8)+1
p = [x1, x2].min()
q = [x1, x2].max()
y1 = rand(N)
y2 = rand(N)
r = [y1, y2].min()
s = [y1, y2].max()
puts "%d %d %d %d %d %d" % [a, m, p, q, r, s]
puts "0 0 0 0 0 0"

