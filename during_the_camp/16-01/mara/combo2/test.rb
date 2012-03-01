1.upto(15) do |n|
  1.upto(n) do |k|
    puts "Testing with #{n} and #{k}..."
    system "echo #{n} #{k} > t.in"
    system "./combo2 < t.in > t.out"
    system "ruby check.rb t.in t.out"
  end
end