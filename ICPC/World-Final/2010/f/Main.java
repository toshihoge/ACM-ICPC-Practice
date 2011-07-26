import java.util.*;

class Machine implements Comparable<Machine> {
  private long d;
  private long p;
  private long r;
  private long g;

  public Machine (long d, long p, long r, long g) {
    this.d = d;
    this.p = p;
    this.r = r;
    this.g = g;
  }

  public int compareTo(Machine m) {
    if (this.d < m.d) {
      return -1;
    } else if (this.d > m.d) {
      return 1;
    } else {
      return 0;
    }
  }

  public long getD() {
    return d;
  }

  public long getP() {
    return p;
  }

  public long getR() {
    return r;
  }

  public long getG() {
    return g;
  }
}

class Line {
  private long m;
  private long c;

  public Line(long m, long c) {
    this.m = m;
    this.c = c;
  }

  //m(x - x0) + y0
  public Line(long m, long x, long y) {
    this.m = m;
    this.c = y - m*x;
  }

  public long getM() {
    return m;
  }

  public long getC() {
    return c;
  }

  public long calculateY(long x) {
    return m*x + c;
  }
}

class PolyLineSegmentTree {
  private final static long MAX_WIDTH = 1L << 30;

  private long begin;
  private long end;
  private Line line;
  private PolyLineSegmentTree lower;
  private PolyLineSegmentTree higher;

  private PolyLineSegmentTree (long begin, long end,
      Line line, PolyLineSegmentTree lower, PolyLineSegmentTree higher) {
    this.begin = begin;
    this.end = end;
    this.line = line;
    this.lower = lower;
    this.higher = higher;
  }

  private PolyLineSegmentTree (long begin, long end, Line line) {
    this(begin, end, line, null, null);
  }

  public static PolyLineSegmentTree getInstanceWithOneHorizontalLine(long c) {
    Line line = new Line(0, c);
    return new PolyLineSegmentTree(0, MAX_WIDTH, line);
  }

  private boolean isSingleLine() {
    return line != null;
  }

  private long getBegin() {
    return begin;
  }

  private PolyLineSegmentTree getSingleLineSegmentIncludingX(long x) {
    if (isSingleLine()) {
      return this;
    } else if (higher.getBegin() <= x) {
      return higher.getSingleLineSegmentIncludingX(x);
    } else {
      return lower.getSingleLineSegmentIncludingX(x);
    }
  }

  private long getM(long x) {
    PolyLineSegmentTree tree = getSingleLineSegmentIncludingX(x);
    return tree.line.getM();
  }

  public long calculateY(long x) {
    PolyLineSegmentTree tree = getSingleLineSegmentIncludingX(x);
    return tree.line.calculateY(x);
  }

  private void override(long nextBegin, long nextEnd, Line nextLine) {
    if (nextBegin == this.begin && nextEnd == this.end) {
      line = nextLine;
      lower = null;
      higher = null;
      return;
    }
    long mid = (this.begin + this.end) / 2;
    if (isSingleLine()) {
      lower = new PolyLineSegmentTree(this.begin, mid, this.line);
      higher = new PolyLineSegmentTree(mid, this.end, this.line);
      line = null;
    }
    if (nextBegin < mid) {
      lower.override(nextBegin, Math.min(mid, nextEnd), nextLine);
    }
    if (mid < nextEnd) {
      higher.override(Math.max(nextBegin, mid), nextEnd, nextLine);
    }
  }

  private long binarySearchBiggestXWithLessThanM(long m) {
    long xmin = 0;
    long xmax = MAX_WIDTH;
    long mAtMax = getM(xmax);
    if (mAtMax < m) {
      return xmax;
    }
    long mAtMin = getM(xmin);
    if (mAtMin > m) {
      return xmin;
    }
    while (xmax - xmin > 1) {
      long xmid = (xmax + xmin)/2;
      long mAtMid = getM(xmid);
      if (mAtMid >= m) {
        xmax = xmid;
      } else {
        xmin = xmid;
      }
    }
    return xmax;
  }

  private long binarySearchBiggestXWithLineExceed(Line line,
      long xmin, long xmax) {
    while (xmax - xmin > 1) {
      long xmid = (xmax + xmin)/2;
      long yAtMidOnThis = calculateY(xmid);
      long yAtMidOnLine = line.calculateY(xmid);
      if (yAtMidOnThis >= yAtMidOnLine) {
        xmax = xmid;
      } else {
        xmin = xmid;
      }
    }
    return xmax;
  }

  private long binarySearchSmallestXWithLineExceed(Line line,
      long xmin, long xmax) {
    while (xmax - xmin > 1) {
      long xmid = (xmax + xmin)/2;
      long yAtMidOnThis = calculateY(xmid);
      long yAtMidOnLine = line.calculateY(xmid);
      if (yAtMidOnThis <= yAtMidOnLine) {
        xmax = xmid;
      } else {
        xmin = xmid;
      }
    }
    return xmax;
  }

  private void insertLineCrossesTwiceOrZero(Line line) {
    long xSplit = binarySearchBiggestXWithLessThanM(line.getM());
    long ySplitOnThis = calculateY(xSplit);
    long ySplitOnLine = line.calculateY(xSplit);
    if (ySplitOnThis >= ySplitOnLine) {
      return;
    }
    long xBiggest =
        binarySearchBiggestXWithLineExceed(line, xSplit, MAX_WIDTH);
    long xSmallest = binarySearchSmallestXWithLineExceed(line, 0, xSplit);
    override(xSmallest, xBiggest, line);
  }

  private void insertLineBiggerSide(Line line) {
    long xSmallest = binarySearchSmallestXWithLineExceed(line, 0, MAX_WIDTH);
    override(xSmallest, MAX_WIDTH, line);
  }

  public void insertLine(Line line) {
    long yAtMinOnThis = calculateY(0);
    long yAtMaxOnThis = calculateY(MAX_WIDTH);
    long yAtMinOnLine = line.calculateY(0);
    long yAtMaxOnLine = line.calculateY(MAX_WIDTH);

    if (yAtMinOnThis >= yAtMinOnLine && yAtMaxOnThis >= yAtMaxOnLine) {
      insertLineCrossesTwiceOrZero(line);
    } else if (yAtMinOnThis >= yAtMinOnLine && yAtMaxOnThis <= yAtMaxOnLine) {
      insertLineBiggerSide(line);
    }
  }
  
  public void print() {
    if (isSingleLine()) {
      System.out.printf("%08x %08x %d %d\n",
          begin, end, line.getM(), line.getC());
      return;
    }
    lower.print();
    higher.print();
  }
}

public class Main {
  private static long solve(long c, long d, Machine[] machines) {
    PolyLineSegmentTree root =
        PolyLineSegmentTree.getInstanceWithOneHorizontalLine(c);
    Arrays.sort(machines);
    for (Machine machine : machines) {
      long yPreviousDay = root.calculateY(machine.getD() - 1);
      if (yPreviousDay < machine.getP()) {
        continue;
      }
      long y = yPreviousDay - machine.getP() + machine.getR();
      Line line = new Line(machine.getG(), machine.getD(), y);
      root.insertLine(line);
    }
    return root.calculateY(d);
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    for (int casenumber = 1; true; casenumber++) {
      int n = s.nextInt();
      long c = s.nextLong();
      long d = s.nextLong();
      if (n == 0) {
        break;
      }
      Machine[] machines = new Machine[n];
      for (int i = 0; i < n; i++) {
        machines[i] = new Machine(s.nextLong(), s.nextLong(), s.nextLong(),
            s.nextLong());
      }
      System.out.printf("Case %d: %d\n", casenumber, solve(c, d, machines));
    }
  }
}
