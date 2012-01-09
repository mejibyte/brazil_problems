class Helper
  def self.assert(something)
    raise "Assertion failed" unless something
  end
end

def handwritten
  floors = [
   %w(2 4 5 8),
   %w(10),
   %w(20 24 25 26),
   %w(1 2),
   %w(1 1000000000),
   %w(1 2 3),
   %w(1 3 4),
   %w(1000000000),
   %w(1 10),
   %w(2),
   %w(1 2 4),
   %w(1 2 4 5 7 8),
   %w(1 3 6 9 12 15 18 21),
   %w(1 2 3 5 8 13 21),
   %w(1 2 3 4 5 6 7 8 9 11),
  ]
end

def already_ready_to_dance(len, first = 1)
  a = (first...(first + len)).to_a
  [a]
end

def random_line(len, max_element)
  a = []
  used = {}
  len.times do
    x = rand(max_element) + 1
    while used[x]
      x = rand(max_element) + 1
    end
    used[x] = true
    a << x
  end
  [a.sort]
end

def print_case(array)
  puts array.size
  puts array.join(" ")
end

def generate
  cases = []
  cases += handwritten
  [5, 10, 100].each do |n|
    cases += already_ready_to_dance(n)
    cases += already_ready_to_dance(n, rand(5000) + 500)
  end
  
  [2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 20, 50, 1000].each do |n|
    cases += random_line(n, 1_000)
    cases += random_line(n, 2_000)
  end
  
  [2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 25, 50, 1000, 2500, 5000].each do |n|
    cases += random_line(n, 10_000)
    cases += random_line(n, 100_000)
    cases += random_line(n, 1_000_000)
    cases += random_line(n, 1_000_000_000)
  end

  cases += random_line(1_000_000, 1_000_000_000)

  cases.each do |single_case|
    print_case(single_case)
  end
  puts "0"
end

generate