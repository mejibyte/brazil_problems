while true
  print "a, b = "
  a, b = gets.chomp.split.map(&:to_i)

  m = (a + b) / 2
  puts "[#{a}, #{m}] = Runtime Error"
  puts "[#{m + 1}, #{b}] = Time Limit"
  puts
end
