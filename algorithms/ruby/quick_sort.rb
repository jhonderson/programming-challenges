def find_index_of_median_pivot(p_array, p_left_index, p_right_index)
  array_length = p_right_index - p_left_index + 1
  if array_length < 3
    return p_left_index
  else
    first_value = p_array[p_left_index]
    last_value = p_array[p_right_index]
    index_of_middle_value = p_left_index
    if array_length % 2 == 0
      index_of_middle_value += (array_length / 2) - 1
    else
      index_of_middle_value += (array_length - 1) / 2
    end
    middle_value = p_array[index_of_middle_value]

    if (last_value <= first_value && first_value <= middle_value) || (middle_value <= first_value && first_value <= last_value)
      return p_left_index
    elsif (first_value <= last_value && last_value <= middle_value) || (middle_value <= last_value && last_value <= first_value)
      return p_right_index
    elsif (first_value <= middle_value && middle_value <= last_value) || (last_value <= middle_value && middle_value <= first_value)
      return index_of_middle_value
    else
      return p_left_index
    end
  end
end

def swap(p_array, p_i, p_j)
  temp_val = p_array[p_i]
  p_array[p_i] = p_array[p_j]
  p_array[p_j] = temp_val
end

def quick_sort_partition(p_array, p_left_index, p_right_index, p_pivot_index)
  swap(p_array, p_left_index, p_pivot_index)
  pivot = p_array[p_left_index]
  i = p_left_index + 1
  for j in ((p_left_index + 1)..p_right_index)
    if p_array[j] < pivot
      swap(p_array, j, i)
      i += 1
    end
  end
  swap(p_array, p_left_index, i - 1)
  return i - 1
end

def apply_quick_sort_and_count_comparisons(p_array, p_left_index, p_right_index)
  array_length = p_right_index - p_left_index + 1
  comparisons_counter = 0
  if array_length < 2
    return 0
  else
    # First version:
    # pivot_index = p_left_index
    # output 162085

    # Second version:
    # pivot_index = p_right_index
    # output 164123

    # Third version:
    pivot_index = find_index_of_median_pivot(p_array, p_left_index, p_right_index)
    # output 138382

    pivot_final_position = quick_sort_partition(p_array, p_left_index, p_right_index, pivot_index)
    comparisons_counter += (array_length - 1)
    comparisons_counter += apply_quick_sort_and_count_comparisons(p_array, p_left_index, pivot_final_position - 1)
    comparisons_counter += apply_quick_sort_and_count_comparisons(p_array, pivot_final_position + 1, p_right_index)
  end

  return comparisons_counter
end

def read_file_and_apply_quick_sort(p_file_path)
  array_of_integer = []
  File.open(p_file_path, "r") do |f|
    f.each_line do |line|
      array_of_integer << Integer(line)
    end
  end
  count_comparisons = apply_quick_sort_and_count_comparisons(array_of_integer, 0, array_of_integer.length - 1)
  return count_comparisons
end

=begin

file_name = "/home/jhon/workspace/text_files/10.txt"
count_comparisons = read_file_and_apply_quick_sort(file_name)
puts "for #{file_name}, comparisons: #{count_comparisons}"

file_name = "/home/jhon/workspace/text_files/100.txt"
count_comparisons = read_file_and_apply_quick_sort(file_name)
puts "for #{file_name}, comparisons: #{count_comparisons}"

file_name = "/home/jhon/workspace/text_files/1000.txt"
count_comparisons = read_file_and_apply_quick_sort(file_name)
puts "for #{file_name}, comparisons: #{count_comparisons}"

=end

file_name = "/home/jhon/workspace/text_files/QuickSort.txt"
count_comparisons = read_file_and_apply_quick_sort(file_name)
puts "for #{file_name}, comparisons: #{count_comparisons}"