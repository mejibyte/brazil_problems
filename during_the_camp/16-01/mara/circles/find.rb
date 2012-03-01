n = 100
n.times do |i|
  puts "Test ##{i}..."
  system "ruby gen.rb > rand.in"
  system "./circles < rand.in > mine.out"
  system "./ana < rand.in > anas.out"
  system "diff mine.out anas.out"
  break unless $?.success?
end