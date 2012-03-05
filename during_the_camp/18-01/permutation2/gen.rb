n = 100_000
q = 100_000
puts "#{n} #{q}"
puts (1..n).to_a.sample(n).join(" ")
q.times do
  if (rand(2) == 0)
    x, y = rand(n) + 1, rand(n) + 1
    k, l = rand(n) + 1, rand(n) + 1
    x, y = y, x if y < x
    k, l = l, k if l < k
    x, y = 1, n
    k, l = n - 1, n
    puts "GET #{x} #{y} #{k} #{l}"
  else
    x = rand(n) + 1
    y = rand(n) + 1
    puts "SET #{x} #{y}"
  end
end
  