public class PancakeSort {

  public static void swap(int[] array, int i, int j) {
    int tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
  }

  public static void reverseArray(int[] array, int k) {
    for (int i = 0; i < k / 2; i++) {
      swap(array, i, k - i - 1);
    }
  }

  public static void sort(int[] array, int length) {
    if (length <= 1) {
      return;
    }
    int maxValue = array[0];
    int maxValueIndex = 0;
    for (int i = 0; i < length; i++) {
      if (array[i] > maxValue) {
        maxValue = array[i];
        maxValueIndex = i;
      }
    }

    reverseArray(array, maxValueIndex + 1);
    reverseArray(array, length);
    sort(array, length - 1);
  }

  public static void main(String[] args) {
    int[] array = {3,5,1,2,6,4};
    sort(array, array.length);
    System.out.println(java.util.Arrays.toString(array));
  }
}