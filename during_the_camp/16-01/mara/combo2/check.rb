def choose(n, k)
  ans = 1
  1.upto(n) { |i| ans *= i }
  1.upto(k) { |i| ans /= i }
  1.upto(n - k) { |i| ans /= i }
  ans
end

def wrong_answer(msg)
  puts "Wrong Answer: #{msg}"
  exit -1
end

if ARGV.size < 2
  puts "Usage: ruby #{__FILE__} input team-output"
  exit -1
end

in_file = ARGV[0]
out_file = ARGV[1]

n, k = File.read(in_file).split.map(&:to_i)

lines = File.readlines(out_file)
if lines.size != choose(n, k)
  wrong_answer("Expected #{choose(n, k)} lines but got #{lines.size}")
end

seen = {}
lines.each do |line|
  line.split.map(&:to_i).each do |i|
    wrong_answer("Got #{i}, which is out of range") if i < 1 or i > n
  end
  
  wrong_answer("Duplicate line '#{line}'") if seen[line]
  wrong_answer("Line '#{line}' has #{line.size} elements instead of K = #{k}") if line.split.size != k
  seen[line] = true
end

1.upto(lines.size - 1) do |i|
  a = lines[i - 1].split.map(&:to_i)
  b = lines[i].split.map(&:to_i)
  
  diff = a - b
  wrong_answer("Consecutive lines '#{a}' and '#{b}' differ in more that one element") if diff.size != 1
  diff = b - a
  wrong_answer("Consecutive lines '#{a}' and '#{b}' differ in more that one element") if diff.size != 1
  
end