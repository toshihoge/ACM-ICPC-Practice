import java.util.*;

public class Main {
  static int[] box;
  static int[] item;

  private static int getCount(int a, int b, int c) {
    return (box[0] / item[a]) * (box[1] / item[b]) * (box[2] / item[c]);
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    box = new int[3];
    item = new int[3];
    for (int i = 0; i < 3; i++) {
      box[i] = s.nextInt();
    }
    for (int i = 0; i < 3; i++) {
      item[i] = s.nextInt();
    }
    int max = 0;
    max = Math.max(max, getCount(0, 1, 2));
    max = Math.max(max, getCount(0, 2, 1));
    max = Math.max(max, getCount(1, 0, 2));
    max = Math.max(max, getCount(1, 2, 0));
    max = Math.max(max, getCount(2, 0, 1));
    max = Math.max(max, getCount(2, 1, 0));
    System.out.println(max);
  }
}
