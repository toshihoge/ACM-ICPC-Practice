import java.util.*;

public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    String line = s.next();
    int n = line.length();
    boolean[] watchable = new boolean[n];
    for (int i = 0; i < n; i++) {
      watchable[i] = line.charAt(i) == 'o';
    }

    int minTv = n;
    for (int i = 0; i < (1<<n); i++) {
      boolean[] watchableMultiTvs = new boolean[3*n];
      int tvCount = 0;
      for (int j = 0; j < n; j++) {
        if ((i & (1 << j)) != 0) {
          tvCount++;
          for (int k = 0; k < n; k++) {
            watchableMultiTvs[k+j] |= watchable[k];
            watchableMultiTvs[k+j+n] |= watchable[k];
          }
        }
      }
      boolean alwaysWatchable = true;
      for (int j = n; j < 2*n; j++) {
        alwaysWatchable &= watchableMultiTvs[j];
      }
      if (alwaysWatchable) {
        minTv = Math.min(minTv, tvCount);
      }
    }
    System.out.println(minTv);
  }
}
