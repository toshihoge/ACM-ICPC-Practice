import java.util.*;

public class Main {
  private static final int MINUS_INF = -(1<<28);

  private static int getIndex(char b, char[] c) {
    for (int i = 0; i < c.length; i++) {
      if (b == c[i]) {
        return i;
      }
    }
    throw new RuntimeException("Unexpected");
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    int m = s.nextInt();
    int y = s.nextInt();
    int z = s.nextInt();
    char[] c = new char[m];
    int[] p = new int[m];
    for (int i = 0; i < m; i++) {
      c[i] = s.next().charAt(0);
      p[i] = s.nextInt();
    }
    String bs = s.next();

    int[][] dptable = new int[m][1<<m];
    int[][] dptableNext = new int[m][1<<m];
    for (int i = 0; i < m; i++) {
      Arrays.fill(dptable[i], MINUS_INF);
      Arrays.fill(dptableNext[i], MINUS_INF);
    }
    for (char b : bs.toCharArray()) {
      int bIndex = getIndex(b, c);
      for (int i = 0; i < m; i++) {
        for (int j = 0; j < (1 << m); j++) {
          if (dptable[i][j] != MINUS_INF) {
            int nextI = bIndex;
            int nextJ = j | (1 << bIndex);
            int nextScore = dptable[i][j] + p[bIndex];
            if (i == bIndex) {
              nextScore += y;
            }
            if (nextJ == ((1 << m) - 1) && j != ((1 << m) - 1)) {
              nextScore += z;
            }
            dptableNext[nextI][nextJ] = Math.max(dptableNext[nextI][nextJ], nextScore);
          }
        }
      }
      if (m == 1) {
        dptableNext[bIndex][1 << bIndex] = Math.max(dptableNext[bIndex][1 << bIndex], p[bIndex] + z);
      } else {
        dptableNext[bIndex][1 << bIndex] = Math.max(dptableNext[bIndex][1 << bIndex], p[bIndex]);
      }
      for (int i = 0; i < m; i++) {
        for (int j = 0; j < (1 << m); j++) {
          dptable[i][j] = dptableNext[i][j];
        }
      }
    }
    int maxScore = 0;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < (1 << m); j++) {
        maxScore = Math.max(maxScore, dptable[i][j]);
      }
    }
    System.out.println(maxScore);
  }
}
