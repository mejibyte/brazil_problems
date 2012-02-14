100.times do |i|
  puts "Test ##{i}..."
  system "ruby gen.rb > rand.in"
  
  system "./next.2 < rand.in > rand.out.2"
  system "./next.3 < rand.in > rand.out.3"
  
  system "diff rand.out.2 rand.out.3"
  system "rm rand.out.2 rand.out.3"
  
  if not $?.success?
    break
  end
end