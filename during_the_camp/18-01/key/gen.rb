n = m = 131072

puts "#{n} #{m}"
n.times do |i|
  at = rand(m - 1) + 2
  print "#{at} "
end
puts