import java.util.*;

public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    
    int n = s.nextInt();
    int x = s.nextInt();
    int y = s.nextInt();
    int[] a = new int[n];
    for (int i = 0; i < n; i++) {
      a[i] = s.nextInt();
    }
    Arrays.sort(a);
    for (int i = 0; i < n; i+=2) {
      x += a[i + 1];
      y += a[i];
    }
    
    if (x > y) {
      System.out.println("Takahashi");
    } else if (x < y) {
      System.out.println("Aoki");
    } else {
      System.out.println("Draw");
    }
  }
}
