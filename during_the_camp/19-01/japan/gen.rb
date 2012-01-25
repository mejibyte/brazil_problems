next_id = Dir.glob("in.*").select { |f| f =~ /in\.[0-9]+/ }.map { |i| i.split(".")[1].to_i }.max + 1
1.upto(41) do |i|
  STDOUT.puts "generating in.#{i}..."
  File.open("in.#{next_id}", "w") do |f|
    f.puts 11
    f.puts (2..42).to_a.sample(11).join(" ")
  end
  next_id += 1
end

