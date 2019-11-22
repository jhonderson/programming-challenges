public class QuickSort {

  public static void sort(int[] array, int start, int end) {

    if (end - start < 1) {
      return;
    }

    int pivotIndex = choosePivotIndex(start, end);
    swap(array, pivotIndex, end);
    int pivot = array[end];

    int i = start;
    for (int j = start; j < end; j++) {
      if (array[j] <= pivot) {
        if (j > i) {
          swap(array, i, j);
        }
        i++;
      }
    }

    swap(array, i, end);
    sort(array, start, i - 1);
    sort(array, i + 1, end);
  }

  public static void swap(int[] array, int i, int j) {
    int tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
  }

  public static int choosePivotIndex(int start, int end) {
    int maxIndex = end - start + 1;
    return new java.util.Random().nextInt(maxIndex) + start;
  }

  public static void main(String[] args) {
    int[] array = {3,5,1,2,6,4, -10, 50, 40, -52, 6, 8, 4, 5, 1, 2, 9, 10, 100, 1532, -565};
    sort(array, 0, array.length - 1);
    System.out.println(java.util.Arrays.toString(array));
  }
}