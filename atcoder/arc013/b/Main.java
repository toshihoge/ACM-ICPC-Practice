import java.util.*;

public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int c = s.nextInt();
    int[] maxD = new int[3];
    for (int i = 0; i < c; i++) {
      int[] d = new int[3];
      for (int j = 0; j < 3; j++) {
        d[j] = s.nextInt();
      }
      Arrays.sort(d);
      for (int j = 0; j < 3; j++) {
        maxD[j] = Math.max(maxD[j], d[j]);
      }
    }
    System.out.println(maxD[0] * maxD[1] * maxD[2]);
  }
}
