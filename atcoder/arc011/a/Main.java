import java.util.*;

public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int m = s.nextInt();
    int n = s.nextInt();
    int recycleBuffer = s.nextInt();
    int sum = 0;
    sum += recycleBuffer;
    while (recycleBuffer >= m) {
      int recycled = (recycleBuffer / m) * n;
      recycleBuffer %= m;
      sum += recycled;
      recycleBuffer += recycled;
    }
    System.out.println(sum);
  }
}
