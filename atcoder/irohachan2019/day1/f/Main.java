import java.util.*;
public class Main {
  private static List<Long> split(long n) {
    List<Long> array = new ArrayList<Long>();
    for (long p = 2; p <= 70000; p++) {
      while (n % p == 0) {
        array.add(p);
        n /= p;
      }
    }
    if (n > 1) {
      array.add(n);
    }
    return array;
  }
  
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    
    long n = s.nextLong();
    int k = s.nextInt();
    
    List<Long> array = split(n);
//    System.err.println(array.size());
    if (array.size() < k) {
      System.out.println(-1);
      return;
    }
    
    for (int i = 0; i < k-1; i++) {
      System.out.print(array.get(i));
      System.out.print(" ");
    }
    long mul = 1;
    for (int i = k - 1; i < array.size(); i++) {
      mul *= array.get(i);
    }
    System.out.println(mul);
  }
}
