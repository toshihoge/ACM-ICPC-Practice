import java.util.*;

class Node implements Comparable<Node> {
  int i, j, cost;
  Node(int i, int j, int cost) {
    this.i = i;
    this.j = j;
    this.cost = cost;
  }

  public int compareTo(Node node) {
    return this.cost - node.cost;
  }
}

public class Main {
  private static final int BLOCK = 1<<30;

  private static final int[] DI = new int[]{1, 0, -1, 0};
  private static final int[] DJ = new int[]{0, 1, 0, -1};

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int h = s.nextInt();
    int w = s.nextInt();
    boolean[][] block = new boolean[h+2][w+2];
    for (int i = 0; i < h+2; i++) {
      block[i][0] = true;
      block[i][w+1] = true;
    }
    for (int j = 0; j < w+2; j++) {
      block[0][j] = true;
      block[h+1][j] = true;
    }
    int si = -1;
    int sj = -1;
    int gi = -1;
    int gj = -1;
    for (int i = 1; i <= h; i++) {
      String line = s.next();
      for (int j = 1; j <= w; j++) {
        switch (line.charAt(j-1)) {
          case 's':
            si = i;
            sj = j;
            break;
          case 'g':
            gi = i;
            gj = j;
            break;
          case '#':
            block[i][j] = true;
            break;
        }
      }
    }
    boolean[][] visited = new boolean[h+2][w+2];
    for (int i = 0; i < h+2; i++) {
      for (int j = 0; j < w+2; j++) {
        visited[i][j] = true;
      }
    }
    for (int i = 1; i <= h; i++) {
      for (int j = 1; j <= w; j++) {
        visited[i][j] = false;
      }
    }


    PriorityQueue<Node> queue = new PriorityQueue<Node>();
    queue.add(new Node(si, sj, 0));
    while (!queue.isEmpty()) {
      Node node = queue.poll();
      if (visited[node.i][node.j]) {
        continue;
      }
      visited[node.i][node.j] = true;
      if (node.i == gi && node.j == gj) {
        System.out.println("YES");
        return;
      }
      for (int k = 0; k < 4; k++) {
        int nextI = node.i + DI[k];
        int nextJ = node.j + DJ[k];
        int nextCost = node.cost + (block[nextI][nextJ] ? 1 : 0);
        if (visited[nextI][nextJ] || nextCost > 2) {
          continue;
        }
        queue.add(new Node(nextI, nextJ, nextCost));
      }
    }
    System.out.println("NO");
  }
}
