import java.util.*;
import java.math.*;

public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    int m = s.nextInt();
    int[][] count = new int[2][26];
    for (int i = 0; i < 2; i++) {
      String input = s.next();
      for (int j = 0; j < input.length(); j++) {
        count[i][input.charAt(j) - 'A']++;
      }
    }

    int boxes = 0;
    for (int i = 0; i < 26; i++) {
      int c0 = count[0][i];
      int c1 = count[1][i];
      if (c0 > 0) {
        if (c1 > 0) {
          boxes = Math.max(boxes, c0 / c1 + (c0 % c1 > 0 ? 1 : 0));
        } else {
          System.out.println(-1);
          return;
        }
      }
    }
    System.out.println(boxes);
  }
}
