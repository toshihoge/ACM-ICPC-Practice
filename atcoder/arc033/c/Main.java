import java.util.*;
import java.math.*;
 
class SegmentTree {
  private static final int MAX_DEPTH = 18;
 
  int[][] table;
  SegmentTree() {
    table = new int[MAX_DEPTH + 1][];
    for (int i = 0; i <= MAX_DEPTH; i++) {
      table[i] = new int[1 << (MAX_DEPTH - i)];
    }
  }
 
  public void insert(int index) {
    for (int depth = 0; depth <= MAX_DEPTH; depth++, index /= 2) {
      table[depth][index]++;
    }
  }
 
  public int remove(int rank) {
    int value = 0;
    for (int depth = MAX_DEPTH; depth >= 0; depth--) {
      value *= 2;
      if (rank > table[depth][value]) {
        rank -= table[depth][value];
        value++;
        table[depth][value]--;
      } else {
        table[depth][value]--;
      }
    }
    return value;
  }
}
 
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    SegmentTree segmentTree = new SegmentTree();
 
    int q = s.nextInt();
    for (int i = 0; i < q; i++) {
      int type = Integer.parseInt(s.next());
      int x = Integer.parseInt(s.next());
      if (type == 1) {
        segmentTree.insert(x);
      } else {
        System.out.println(segmentTree.remove(x));
      }
    }
  }
}
