import java.util.*;
import java.math.*;
 
class Separator implements Comparable<Separator> {
  int index;
  int position;
  int last;
  boolean begin;
 
  Separator(int index, int position, int last, boolean begin) {
    this.index = index;
    this.position = position;
    this.last = last;
    this.begin = begin;
  }
 
  public int compareTo(Separator separator) {
    return this.position - separator.position;
  }
}
 
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    int m = s.nextInt();
    ArrayList<Separator> separators = new ArrayList<Separator>();
    for (int i = 1; i <= m; i++) {
      int a = Integer.parseInt(s.next()) - 1;
      int b = Integer.parseInt(s.next());
      separators.add(new Separator(i, a, b, true));
      separators.add(new Separator(i, b, b, false));
    }
    Collections.sort(separators);
 
//    HashSet<Integer> indexes = new HashSet<Integer>();
    HashSet<Integer> oneOperators = new HashSet<Integer>();
    int position = 0;
    int lastPosition = 0;
    int lastIndex = 0;
    int depth = 0;
    for (Separator separator : separators) {
      int nextPosition = separator.position;
      if (position != nextPosition) {
        if (depth == 1) {
          oneOperators.add(lastIndex);
        }
      }
      position = nextPosition;
      if (separator.begin) {
        depth++;
        if (lastPosition < separator.last) {
          lastPosition = separator.last;
          lastIndex = separator.index;
        }
      } else {
        depth--;
      }
    }
    System.out.println(m - oneOperators.size());
    for (int i = 1; i <= m; i++) {
      if (oneOperators.contains(i)) {
        continue;
      }
      System.out.println(i);
    }
  }
}
