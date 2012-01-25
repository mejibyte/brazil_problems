Dir.glob("in.*") do |f|
  puts "Running with #{f}..."
  
  before = Time.now
  system("./japan.3 < #{f} > /dev/null")
  andy = Time.now - before
  
  before = Time.now
  system("./roypalacios < #{f} > /dev/null")
  roy = Time.now - before
  
  puts "Andy: #{andy}, Roy: #{roy}, #{roy < andy ? "Roy < Andy" : "Roy >= Andy"}. Difference: #{roy - andy}"
end