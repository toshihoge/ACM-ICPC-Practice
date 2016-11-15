import java.util.*;
import java.math.*;
 
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    int r = s.nextInt();
    boolean[] painted = new boolean[n];
    char[] cs = s.next().toCharArray();
    int rightMostUnpainted = -1;
    for (int i = 0; i < n; i++) {
      painted[i] = (cs[i] == 'o');
      if (!painted[i]) {
        rightMostUnpainted = i;
      }
    }
    if (rightMostUnpainted < 0) {
      System.out.println(0);
      return;
    }
    int cost = 0;
    if (rightMostUnpainted - r + 1 > 0) {
      cost = rightMostUnpainted - r + 1;
    }
    while(rightMostUnpainted >= 0) {
      rightMostUnpainted = rightMostUnpainted - r + 1;
      cost++;
      rightMostUnpainted--;
      while(rightMostUnpainted >= 0 && painted[rightMostUnpainted]) {
        rightMostUnpainted--;
      }
    }
    System.out.println(cost);
  }
}
