import java.util.*;

class MaximumBipartiteMatchingSolver {
  private int maxSrc;
  private int maxDst;
  private HashSet<Integer> edges;

  public MaximumBipartiteMatchingSolver() {
    maxSrc = 1;
    maxDst = 1;
    edges = new HashSet<Integer>();
  }

  private int makeEdge(int src, int dst) {
    return (src << 16) | dst;
  }

  public void addEdge(int src, int dst) {
    maxSrc = Math.max(maxSrc, src+1);
    maxDst = Math.max(maxDst, dst+1);
    edges.add(makeEdge(src, dst));
  }

  private boolean containEdge(int src, int dst) {
    return edges.contains(makeEdge(src, dst));
  }

  private boolean dfs(int srcIndex, int[] prev, boolean[] visit) {
    if (srcIndex < 0) {
      return true;
    }
    for (int i = 0; i < maxDst; i++) {
      if (visit[i] || !containEdge(srcIndex, i)) {
        continue;
      }
      visit[i] = true;
      if (dfs(prev[i], prev, visit)) {
        prev[i] = srcIndex;
        return true;
      }
    }
    return false;
  }

  public int solve() {
    int count = 0;
    int[] prev = new int[maxDst];
    boolean[] visit = new boolean[maxDst];
    Arrays.fill(prev, -1);
    for (int i = 0; i < maxSrc; i++) {
      Arrays.fill(visit, false);
      if (dfs(i, prev, visit)) {
        count++;
      }
    }
    return count;
  }
}

class Edge {
  int x;
  int ymin;
  int ymax;

  public Edge(int x, int ymin, int ymax) {
    this.x = x;
    this.ymin = ymin;
    this.ymax = ymax;
  }

  public boolean conflict(Edge e) {
    return this.ymin <= e.x && e.x <= this.ymax &&
        e.ymin <= this.x && this.x <= e.ymax;
  }
}

public class G {
  private byte[][] parseLines(String[] lines) {
    byte[][] map = new byte[lines.length][lines[0].length()];
    for (int i = 0; i < lines.length; i++) {
      for (int j = 0; j < lines[0].length(); j++) {
        map[i][j] = ((lines[i].charAt(j) == '#') ? (byte)1 : (byte)0);
      }
    }
    return map;
  }

  private int countCorners(byte[][] map) {
    int counter = 0;
    for (int i = 1; i < map.length; i++) {
      for (int j = 1; j < map[i].length; j++) {
        if (map[i-1][j-1] + map[i-1][j] + map[i][j-1] + map[i][j] == 3) {
          counter++;
        }
      }
    }
    return counter;
  }

  private ArrayList<Edge> gatherHorizontalEdges(byte[][] map) {
    ArrayList<Edge> edges = new ArrayList<Edge>();
    for (int i = 1; i < map.length; i++) {
      for (int j = 1; j < map[i].length; j++) {
        if (map[i-1][j-1] + map[i][j-1] == 1 &&
            map[i-1][j] + map[i][j] == 2) {
          int k = j;
          for (; k < map[i].length; k++) {
            int n = map[i-1][k] + map[i][k];
            if (n == 1) {
              edges.add(new Edge(i, j, k));
              break;
            } else if (n == 0) {
              break;
            }
          }
          j = k;
        }
      }
    }
    return edges;
  }

  private byte[][] transpose(byte[][] map) {
    byte[][] t = new byte[map[0].length][map.length];
    for (int i = 0; i < map.length; i++) {
      for (int j = 0; j < map[i].length; j++) {
        t[j][i] = map[i][j];
      }
    }
    return t;
  }

  private int countMaximumIsolatedEdges(ArrayList<Edge> hEdges,
      ArrayList<Edge> vEdges) {
    MaximumBipartiteMatchingSolver solver =
        new MaximumBipartiteMatchingSolver();
    for (int i = 0; i < hEdges.size(); i++) {
      for (int j = 0; j < vEdges.size(); j++) {
        if (hEdges.get(i).conflict(vEdges.get(j))) {
          solver.addEdge(i, j);
        }
      }
    }
    return hEdges.size() + vEdges.size() - solver.solve();
  }

  public int solve(String[] lines) {
    byte[][] map = parseLines(lines);
    return 1 + countCorners(map)
        - countMaximumIsolatedEdges(
            gatherHorizontalEdges(map),
            gatherHorizontalEdges(transpose(map)));
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    G solver = new G();
    while (true) {
      int h = s.nextInt();
      int w = s.nextInt();
      if (h == 0) {
        break;
      }
      String[] lines = new String[h];
      for (int i = 0; i < h; i++) {
        lines[i] = s.next();
      }
      System.out.println(solver.solve(lines));
    }
  }
}
