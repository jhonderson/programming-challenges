public class InsertionSort {

  public static void sort(int[] array) {
    for (int i = 1; i < array.length; i++) {
      int insertionElement = array[i];
      int j = i - 1;
      while (j >= 0 && insertionElement < array[j]) {
        array[j + 1] = array[j];
        j--;
      }
      array[j + 1] = insertionElement;
    }
  }

  public static void main(String[] args) {
    int[] array = {3,5,1,2,6,4};
    sort(array);
    System.out.println(java.util.Arrays.toString(array));
  }
}