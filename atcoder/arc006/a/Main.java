import java.util.*;
 
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    HashSet<Integer> eSet = new HashSet<Integer>();
    for (int i = 0; i < 6; i++) {
      int e = s.nextInt();
      eSet.add(e);
    }
    int b = s.nextInt();
 
    int eCounter = 0;
    boolean hasB = false;
    for (int i = 0; i < 6; i++) {
      int number = s.nextInt();
      if (eSet.contains(number)) {
        eCounter++;
      }
      hasB |= number == b;
    }
 
    switch(eCounter) {
      case 6:
        System.out.println(1);
        return;
      case 5:
        if (hasB) {
          System.out.println(2);
        } else {
          System.out.println(3);
        }
        return;
      case 4:
        System.out.println(4);
        return;
      case 3:
        System.out.println(5);
        return;
      default:
        System.out.println(0);
        return;
    }
  }
}