import java.util.*;
import java.math.*;
 
public class Main {
  private static boolean isPrime(int n) {
    switch(n) {
      case 1:
        return false;
      case 2:
      case 3:
      case 5:
        return true;
    }
    if (n % 3 == 0) {
      return false;
    }
    switch (n % 10) {
      case 1:
      case 3:
      case 7:
      case 9:
        return true;
    }
    return false;
  }
 
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    System.out.println(isPrime(s.nextInt()) ? "Prime" : "Not Prime");
  }
}
