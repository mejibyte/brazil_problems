n = 10_000
a = rand(10_000) + 1

puts "#{n} #{a}"
n.times do
  sign = rand(2) == 0 ? +1 : -1
  puts sign
end
