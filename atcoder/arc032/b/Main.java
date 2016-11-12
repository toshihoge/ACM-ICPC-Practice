import java.util.*;

class Node {
  Node parent;
  int rank;

  Node() {
    parent = null;
    rank = 0;
  }

  public Node getRoot() {
    if (parent == null) {
      return this;
    }
    parent = parent.getRoot();
    return parent;
  }

  public static boolean merge(Node a, Node b) {
    Node aRoot = a.getRoot();
    Node bRoot = b.getRoot();
    if (aRoot.rank < bRoot.rank) {
      aRoot.parent = bRoot;
      return true;
    } else if (bRoot.rank < aRoot.rank) {
      bRoot.parent = aRoot;
      return true;
    } else if (aRoot != bRoot) {
      aRoot.parent = bRoot;
      bRoot.rank++;
      return true;
    }
    return false;
  }
}

public class Main {

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    int m = s.nextInt();

    Node[] nodes = new Node[n+1];
    for (int i = 1; i <= n; i++) {
      nodes[i] = new Node();
    }

    for (int i = 0; i < m; i++) {
      int a = Integer.parseInt(s.next());
      int b = Integer.parseInt(s.next());
      Node.merge(nodes[a], nodes[b]);
    }

    int count = 0;
    for (int i = 2; i <= n; i++) {
      if (Node.merge(nodes[1], nodes[i])) {
        count++;
      }
    }
    System.out.println(count);
  }
}
