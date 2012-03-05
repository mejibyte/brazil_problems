50.times do |i|
  puts "Test #{i}..."
  system "ruby gen.rb > rand.in"
  system "./permutation2 < rand.in > fast.out"
  system "./bruteforce < rand.in > slow.out"
  system "diff fast.out slow.out"
  if not $?.success?
    exit 0
  end
end