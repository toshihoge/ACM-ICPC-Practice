import java.util.*;

class Position {
  int edgeId;
  int lastEdgeCost;
  
  Position(int edgeId, int lastEdgeCost) {
    this.edgeId = edgeId;
    this.lastEdgeCost = lastEdgeCost;
  }
  
  public int hashCode() {
    return (edgeId << 16) | lastEdgeCost;
  }
  
  public boolean equals(Object object) {
    Position position = (Position)object;
    return this.edgeId == position.edgeId && this.lastEdgeCost == position.lastEdgeCost;
  }
}

class Node implements Comparable<Node> {
  Position position;
  int count;
  
  Node(Position position, int count) {
    this.position = position;
    this.count = count;
  }
  
  public int compareTo(Node node) {
    return this.count - node.count;
  }
}

public class  Main {
  private static int solve(int n, int m, int k, int[] a, int[] b, int[] c) {
    ArrayList<ArrayList<Position>> edges = new ArrayList<ArrayList<Position>>();
    for (int i = 0; i <= n; i++) {
      edges.add(new ArrayList<>());
    }
    for (int i = 0; i < m; i++) {
      edges.get(a[i]).add(new Position(b[i], c[i]));
      edges.get(b[i]).add(new Position(a[i], c[i]));
    }
    
    PriorityQueue<Node> queue = new PriorityQueue<>();
    HashSet<Position> visited = new HashSet<>();
    for (Position edge : edges.get(1)) {
      queue.add(new Node(edge, 0));
    }
    while (!queue.isEmpty()) {
      Node node = queue.poll();
      if (node.position.edgeId == n) {
        return (node.count + 1) * k;
      }
      if (visited.contains(node.position)) {
        continue;
      }
      visited.add(node.position);
      for (Position nextPosition : edges.get(node.position.edgeId)) {
        if (visited.contains(nextPosition)) {
          continue;
        }
        queue.add(
          new Node(
            nextPosition,
            node.count + (node.position.lastEdgeCost != nextPosition.lastEdgeCost ? 1 : 0)));
      }
    }
    return -1;
  }
  
  
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    
    int n = s.nextInt();
    int m = s.nextInt();
    int k = s.nextInt();
    int[] a = new int[m];
    int[] b = new int[m];
    int[] c = new int[m];
    for (int i = 0; i < m; i++) {
      a[i] = s.nextInt();
      b[i] = s.nextInt();
      c[i] = s.nextInt();
    }
    System.out.println(solve(n, m, k, a, b, c));
    
  } 
}
