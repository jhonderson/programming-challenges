def merge_sort(p_array)
  array_length = p_array.length
  if array_length < 2
    return p_array
  else
    middle_pos = array_length/2
    part_a = merge_sort(p_array[0...middle_pos])
    part_b = merge_sort(p_array[middle_pos..-1])
    array_sorted = Array.new(array_length)

    i = 0
    j = 0
    for k in 0...array_length
      if part_a[i].nil?
        array_sorted[k] = part_b[j]
        j += 1
      elsif part_b[j].nil?
        array_sorted[k] = part_a[i]
        i += 1
      elsif part_a[i] <= part_b[j]
        array_sorted[k] = part_a[i]
        i += 1
      else
        array_sorted[k] = part_b[j]
        j += 1
      end
    end
    return array_sorted
  end
end

print merge_sort([9,0,6,2,5,1,4,3,8,7])
print merge_sort([9,0,6,2,5,1,4,3,8])