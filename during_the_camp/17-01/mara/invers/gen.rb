
a = []
#262144.times do
#  a << 0
#end

(262144 - 1).downto(0) do |i|
  a << i
end

puts a.join(" ")