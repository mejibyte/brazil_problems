n = 100_000
m = 100_000
puts "#{n} {m}"
m.times do |i|
  l = rand(n) + 1
  r = rand(n) + 1
  l, r = r, l if r < l
  puts "#{r} #{l}"
end