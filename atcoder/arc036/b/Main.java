import java.util.*;
import java.math.*;
 
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    int previousHeight = s.nextInt();
    int upCounter = 0;
    int downCounter = 0;
    int maxMountain = 0;
    for (int i = 1; i < n; i++) {
      int height = s.nextInt();
      if (height > previousHeight) {
        if (downCounter > 0) {
          maxMountain = Math.max(maxMountain, upCounter + downCounter);
          upCounter = 1;
          downCounter = 0;
        } else {
          upCounter++;
        }
      } else if (height < previousHeight) {
        downCounter++;
      } else {
        throw new RuntimeException("Unexpected");
      }
      previousHeight = height;
    }
    maxMountain = Math.max(maxMountain, upCounter + downCounter);
    System.out.println(maxMountain + 1);
  }
}
