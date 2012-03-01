100.times do |i|
  puts "Random test #{i}..."
  system "ruby gen.rb > rand.in"
  system "./permutation < rand.in > fast.out"
  system "./bruteforce < rand.in > slow.out"
  system "diff slow.out fast.out"
  break if not $?.success?
end