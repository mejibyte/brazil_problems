n = 1e5.to_i
m = 1e5.to_i
puts "#{n} #{m}"
p = (1..n).to_a.sample(n)
puts p.join(" ")
m.times do
  x = rand(n) + 1
  y = rand(n) + 1
  x, y = y, x if y < x
  p = rand(n) + 1
  q = rand(n) + 1
  p, q = q, p if q < p
  puts "#{x} #{y} #{p} #{q}"
end
