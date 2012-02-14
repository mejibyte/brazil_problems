def random_big_case
  n = 50_000
  m = rand(50_000) + 1

  a = []
  n.times { a << rand(10**6 - m) + m }
  a.sort_by! { |x| -x }

  puts "#{n} #{m}"
  puts a.join(" ")
end

def big_equal_case
  n = 50_000
  m = 1
  
  a = []
  n.times { a << 500_000 }
  puts "#{n} #{m}"
  puts a.join(" ")  
end

big_equal_case