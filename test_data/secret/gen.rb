require 'securerandom'

class Helper
  def self.assert(something)
    raise "Assertion failed" unless something
  end
  
  def self.random_string(length)
    s = SecureRandom.base64(length * 3 / 4 + 2).downcase
    s.tr!("0123456789+/=", "abcdefghijklm")
    assert s.size >= length
    assert s[0...length].length == length
    s[0...length]
  end
end

def handwritten
  %w(
  unicamp
  brazil
  abcdba
  neversayeven
  neveroddoreven
  listentothesilence
  a
  ab
  aa
  aaaax
  xaaayax
  aaaaaaaxxxxa
  abaaba
  aaba
  xyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyz
  xyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyx
  xyyyyxyyyyz
  abcdefghijklmnopqrstubavwxyz
  abcdefghijklmnopqrstuvwxyz
  dabalaarrozalazorraelabad
  )
end

def small_random
  words = []
  def f(len, s = "")
    if len == 0
      return [s]
    else
      ans = []
      ['a', 'b', 'c', 'd'].each do |add|
        ans += f(len - 1, s + add)
      end
      ans
    end
  end
  f(8).sample(80)
end

def medium_random
  words = []
  20.times do
    len = rand(1001) + 50
    words << Helper.random_string(len)
  end
  words
end


def same_character(n)
  s = ('b'...'t').to_a.sample * n
  [s]
end

def same_character_except_one(n)
  c = ('b'...'t').to_a.sample
  s = c * n
  s[rand(s.size)] = (c.ord + 1).chr
  [s]  
end

def random_palindrome(n)
  s = Helper.random_string(n / 2)
  [s + s.reverse]
end

def hidden_pattern(len)
  pattern = "awesome"
  n = len - 2 * pattern.size - 1
  first = rand(n / 2) + 1
  second = n - first
  s = pattern.reverse + ("p" * first) + "x" + pattern + ("q" * second)
  Helper.assert s.length < 10 ** 6
  Helper.assert s.length == len
  [s]
end


def generate
  words = []
  words += handwritten
  words += small_random
  words += medium_random
  [10, 20, 50, 100, 500, 1000].each do |n|
    words += random_palindrome(n)
    words += same_character(n)
    words += same_character_except_one(n)
  end
  [50, 100, 500, 1000].each do |n|
    words += hidden_pattern(n)
  end
  
  [500_000, 999_998].each do |n|
    words += random_palindrome(n)
    words += hidden_pattern(n)
  end
  
  words += [Helper.random_string(999_999)]

  puts words.size
  puts words.join("\n")
end

generate