def random_point
  x = rand(10) * (rand(2) == 0 ? +1 : -1)
  y = rand(10) * (rand(2) == 0 ? +1 : -1)
  r = rand(10) + 1
  [x, y, r]
end

k = 1
puts k


k.times do
  p1 = random_point
  p2 = random_point
  puts p1.join(" ")
  puts p2.join(" ")
end