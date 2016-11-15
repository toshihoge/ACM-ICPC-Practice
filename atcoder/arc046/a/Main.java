import java.util.*;
import java.math.*;
 
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt() - 1;
    ArrayList<Integer> table = new ArrayList<Integer>();
    for (int i = 1; i < 10; i++) {
      for (int j = 1; j <= 9; j++) {
        int number = 0;
        for (int k = 0; k < i; k++) {
          number *= 10;
          number += j;
        }
        table.add(number);
      }
    }
    System.out.println(table.get(n));
  }
}
