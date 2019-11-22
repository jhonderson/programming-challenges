public class MergeSort {

  public static void sort(int[] array, int start, int end) {

    if (end - start < 1) {
      return;
    }

    int middleIndex = (start + end) / 2;
    sort(array, start, middleIndex);
    sort(array, middleIndex + 1, end);

    merge(array, start, middleIndex, end);
  }

  public static void merge(int[] array, int start, int middle, int end) {
    int n1 = middle - start + 1;
    int n2 = end - middle;
    /* Create temp arrays */
    int L[] = new int [n1]; 
    int R[] = new int [n2]; 

    /*Copy data to temp arrays*/
    for (int i=0; i<n1; ++i) 
        L[i] = array[start + i]; 
    for (int j=0; j<n2; ++j) 
        R[j] = array[middle + 1+ j]; 

    int i = 0, j = 0;
    int k = start;
    while (i < n1 && j < n2) {
      if (L[i] <= R[j]) {
        array[k] = L[i++];
      } else {
        array[k] = R[j++];
      }
      k++;
    }
    while (i < n1) {
      array[k++] = L[i++];
    }
    while (j < n2) {
      array[k++] = R[j++];
    }
  }

  public static void main(String[] args) {
    int[] array = {3,5,1,2,6,4, -10, 50, 40, -52, 6, 8, 4, 5, 1, 2, 9, 10, 100, 1532, -565};
    sort(array, 0, array.length - 1);
    System.out.println(java.util.Arrays.toString(array));
  }
}