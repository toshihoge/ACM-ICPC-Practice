import java.util.*;
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    
    String word = s.next();
    int k = s.nextInt();
    k = k % word.length();
    System.out.println(word.substring(k) + word.substring(0, k));
  }
}
