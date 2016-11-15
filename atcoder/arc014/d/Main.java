import java.util.*;

public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int all = s.nextInt();
    int n = s.nextInt();
    int m = s.nextInt();
    long[] ls = new long[n];
    for (int i = 0; i < n; i++) {
      ls[i] = Long.parseLong(s.next());
    }

    long topBlock = ls[0] - 1;
    long bottomBlock = all - ls[n-1];
    long[] diffs = new long[n-1];
    for (int i = 1; i < n; i++) {
      diffs[i-1] = 2*(ls[i] - ls[i-1] - 1);
    }
    Arrays.sort(diffs);
    long[] diffSum = new long[n];
    diffSum[0] = 0;
    for (int i = 1; i < n; i++) {
      diffSum[i] = diffSum[i-1] + diffs[i-1]/2;
    }

    for (int i = 0; i < m; i++) {
      long x = Long.parseLong(s.next());
      long y = Long.parseLong(s.next());

      long sum = n;
      sum += Math.min(x, topBlock);
      sum += Math.min(y, bottomBlock);
      int negativeInsertionIndex = Arrays.binarySearch(diffs, 2*(x+y)+1);
      if (negativeInsertionIndex >= 0) {
        throw new RuntimeException("positive");
      }
      int insertionIndex = -(negativeInsertionIndex + 1);
      sum += diffSum[insertionIndex];
      sum += (long)(n - 1 - insertionIndex) * (x + y);
      System.out.println(sum);
    }
  }
}
