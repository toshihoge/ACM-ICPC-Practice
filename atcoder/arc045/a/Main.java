import java.util.*;
import java.math.*;
 
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    HashMap<String, String> map = new HashMap<String, String>();
    map.put("Left", "<");
    map.put("Right", ">");
    map.put("AtCoder", "A");
    System.out.print(map.get(s.next()));
    while(s.hasNext()) {
      System.out.print(" ");
      System.out.print(map.get(s.next()));
    }
    System.out.println();
  }
}
