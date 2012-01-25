
lines = []
while s = STDIN.gets
  lines << s.chomp
end

n = lines.first.size


if lines.uniq.size != 3 ** n
  puts "Some numbers are missing!"
end

i = 0
while i + 1 < lines.size
  
  s = lines[i]
  t = lines[i + 1]
  
  #puts "s = #{s}"
  #puts "t = #{t}"
  
  s.size.times do |j|
    if s.split("")[j] == t.split("")[j]
      puts "Element #{j} of s = #{s} and t = #{t} is equal"
    end
  end
  
  i += 1
end