def sort_and_count_inversions(p_array)
  array_length = p_array.length
  if array_length < 2
    return p_array, 0
  else
    middle_pos = array_length/2
    part_a, inversions_in_part_a = sort_and_count_inversions(p_array[0...middle_pos])
    part_b, inversions_in_part_b = sort_and_count_inversions(p_array[middle_pos..-1])
    array_sorted, spit_inversions = merge_sort_and_count_inversions(part_a, part_b)
    return array_sorted, inversions_in_part_a + inversions_in_part_b + spit_inversions
  end
end

def merge_sort_and_count_inversions(p_part_a, p_part_b)
  array_length = p_part_a.length + p_part_b.length
  array_sorted = Array.new(array_length)

  split_inversions = 0
  i = 0
  j = 0
  for k in 0...array_length
    if p_part_a[i].nil?
      array_sorted[k] = p_part_b[j]
      j += 1
    elsif p_part_b[j].nil?
      array_sorted[k] = p_part_a[i]
      i += 1
    elsif p_part_a[i] <= p_part_b[j]
      array_sorted[k] = p_part_a[i]
      i += 1
    else
      array_sorted[k] = p_part_b[j]
      j += 1
      split_inversions += (p_part_a.length - i)
    end
  end
  return array_sorted, split_inversions
end

def read_file_and_count_inversions(p_file_path)
  array_of_integer = []
  File.open(p_file_path, "r") do |f|
    f.each_line do |line|
      array_of_integer << Integer(line)
    end
  end
  array_sorted, inversions_count = sort_and_count_inversions(array_of_integer)
  puts inversions_count
end

read_file_and_count_inversions("/home/jhon/workspace/text_files/IntegerArray.txt")

=begin
array_sorted, inversions_count = sort_and_count_inversions([3, 4, 6, 1, 2, 5])
puts inversions_count
print array_sorted
array_sorted, inversions_count = sort_and_count_inversions([3, 2, 1, 4])
puts inversions_count
print array_sorted
=end