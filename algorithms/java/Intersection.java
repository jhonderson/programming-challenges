public class Intersection {

  public static int[] findIntersectionOnSortedArrays(int[] a, int[] b) {
    int i = 0;
    int j = 0;
    java.util.List<Integer> intersectionList = new java.util.ArrayList<>();
    while(i < a.length && j < b.length) {
      if (a[i] == b[j]) {
        intersectionList.add(a[i]);
        i++;
        j++;
      } else if (a[i] < b[j]) {
        i++;
      } else {
        j++;
      }
    }
    System.out.println(i + j);
    int[] intersection = new int[intersectionList.size()];
    for (int idx = 0; idx < intersectionList.size(); idx++) {
      intersection[idx] = intersectionList.get(idx);
    }
    return intersection;
  }

  public static void main (String[] args) {
    int[] a = {1,3,5,7,9};
    int[] b = {2,4,6,8,10};
    System.out.println(java.util.Arrays.toString(findIntersectionOnSortedArrays(a, b)));
  }
}