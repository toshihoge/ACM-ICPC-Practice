import java.util.*;

class LevelLine {
  int minX;
  int midX;
  int maxX;
  int minY;
  LevelLine[] children;

  LevelLine (int minX, int maxX, int minY) {
    this.minX = minX;
    this.midX = (minX + maxX) / 2;
    this.maxX = maxX;
    this.minY = minY;
    this.children = null;
  }

  public boolean isCovered(int x, int y) {
    if (children == null) {
      return this.minY <= y;
    }
    if (x < midX) {
      return children[0].isCovered(x, y);
    } else {
      return children[1].isCovered(x, y);
    }
  }

  public void update(int minX, int minY) {
    if (this.maxX <= minX) {
      return;
    }
    if (children == null && this.minY < minY) {
      return;
    }
    if (minX <= this.minX && minY <= this.minY) {
      children = null;
      this.minY = minY;
      return;
    }
    if (children == null) {
      children = new LevelLine[2];
      children[0] = new LevelLine(this.minX, this.midX, this.minY);
      children[1] = new LevelLine(this.midX, this.maxX, this.minY);
    }
    for (LevelLine child : children) {
      child.update(minX, minY);
    }
    this.minY = Math.min(this.minY, minY);
  }
}

class XY {
  int x, y;

  XY(int x, int y) {
    this.x = x;
    this.y = y;
  }
}

class LevelLineGroup {
  private static final int MAX = 1<<20;
  
  private ArrayList<LevelLine> levelLines;
  
  LevelLineGroup () {
    levelLines = new ArrayList<LevelLine>();
    levelLines.add(new LevelLine(0, MAX, 0));
  }

  private int binarySearchZ(int x, int y) {
    int maxZ = levelLines.size();
    int minZ = 0;

    while (maxZ - minZ > 1) {
      int midZ = (maxZ + minZ) / 2;
      if (levelLines.get(midZ).isCovered(x, y)) {
        minZ = midZ;
      } else {
        maxZ = midZ;
      }
    }
    return minZ;
  }

  private void addSameLevelXYs(ArrayList<XY> xys) {
    ArrayList<Integer> zs = new ArrayList<Integer>();
    for (XY xy : xys) {
      int z = binarySearchZ(xy.x - 1, xy.y - 1);
      zs.add(z);
    }

    for (int i = 0; i < zs.size(); i++) {
      if (zs.get(i)+1 == levelLines.size()) {
        levelLines.add(new LevelLine(0, MAX, MAX));
      }
      XY xy = xys.get(i);
      levelLines.get(zs.get(i)+1).update(xy.x, xy.y);
    }
  }

  public int solve(int n, int[] xs, int[] ys, int[] zs) {
    HashMap<Integer, ArrayList<XY>> xyGroupByZ = new HashMap<Integer, ArrayList<XY>>();
    for (int i = 0; i < n; i++) {
      ArrayList<XY> xys = xyGroupByZ.get(zs[i]);
      if (xys == null) {
        xys = new ArrayList<XY>();
        xyGroupByZ.put(zs[i], xys);
      }
      xys.add(new XY(xs[i], ys[i]));
    }

    for (int z = 0; z < MAX; z++) {
      ArrayList<XY> xys = xyGroupByZ.get(z);
      if (xys != null) {
        addSameLevelXYs(xys);
      }
    }

    return levelLines.size()-1;
  }
}

class Generator {
  int a;
  int b;
  int c;
  int m;
  
  Generator(int a, int b) {
    this.a = a;
    this.b = b;
    this.c = ~(1<<31);
    this.m = (1<<16) - 1;
  }
  
  public int generate() {
    a = 36969 * (a & m) + (a >> 16);
    b = 18000 * (b & m) + (b >> 16);
    return (c & ((a << 16) + b)) % 1000000;
  }
}

public class G {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    
    while(true) {
      int m = s.nextInt();
      int n = s.nextInt();
      int a = s.nextInt();
      int b = s.nextInt();
      if (m + n == 0) {
        break;
      }
      int[] x = new int[m+n];
      int[] y = new int[m+n];
      int[] z = new int[m+n];
      for (int i = 0; i < m; i++) {
        x[i] = s.nextInt()+1;
        y[i] = s.nextInt()+1;
        z[i] = s.nextInt()+1;
      }
      Generator generator = new Generator(a, b);
      for (int i = m; i < m+n; i++) {
        x[i] = generator.generate()+1;
        y[i] = generator.generate()+1;
        z[i] = generator.generate()+1;
      }
      
      LevelLineGroup llg = new LevelLineGroup();
      System.out.println(llg.solve(m+n, x, y, z));
    }
  }
}
