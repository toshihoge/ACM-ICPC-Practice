import java.util.*;
import java.math.*;
 
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int na = s.nextInt();
    int nb = s.nextInt();
    int[] a = new int[na];
    int[] b = new int[nb];
    for (int i = 0; i < na; i++) {
      a[i] = s.nextInt();
    }
    for (int i = 0; i < nb; i++) {
      b[i] = s.nextInt();
    }
    Arrays.sort(a);
    Arrays.sort(b);
    int andCounter = 0;
    int orCounter = 0;
    int aIndex = 0;
    int bIndex = 0;
    while(aIndex < a.length && bIndex < b.length) {
      if (a[aIndex] < b[bIndex]) {
        orCounter++;
        aIndex++;
      } else if (a[aIndex] > b[bIndex]) {
        orCounter++;
        bIndex++;
      } else {
        andCounter++;
        orCounter++;
        aIndex++;
        bIndex++;
      }
    }
    if (aIndex < a.length) {
      orCounter += a.length - aIndex;
    }
    if (bIndex < b.length) {
      orCounter += b.length - bIndex;
    }
    System.out.println((double)andCounter / orCounter);
  }
}
