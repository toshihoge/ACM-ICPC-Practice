import java.util.*;

class Mesh {
  double cx, cy, width;

  Mesh(double cx, double cy, double width) {
    this.cx = cx;
    this.cy = cy;
    this.width = width;
  }
}

public class Main {
  private static double[] DY = new double[]{ 1, 1, -1, -1};
  private static double[] DX = new double[]{-1, 1,  1, -1};

  static int n;
  static int m;
  static double r;
  static double[] as;
  static double[] bs;
  static double[] cs;
  static double[] ps;
  static double[] qs;

  static double calculateDistRoad(double x, double y, int i) {
    return Math.abs(as[i]*x + bs[i]*y + cs[i]) / Math.sqrt(as[i]*as[i] + bs[i]*bs[i]);
  }

  static double calculateDistPoint(double x, double y, int i) {
    double dx = x - ps[i];
    double dy = y - qs[i];
    return Math.sqrt(dx*dx + dy*dy);
  }

  static double calculateF(Mesh mesh) {
    double distRoadMin = Double.MAX_VALUE;
    for (int i = 0; i < n; i++) {
      distRoadMin = Math.min(
          distRoadMin,
          calculateDistRoad(mesh.cx, mesh.cy, i));
    }
    double distPointMin = Double.MAX_VALUE;
    for (int i = 0; i < m; i++) {
      distPointMin = Math.min(
          distPointMin,
          calculateDistPoint(mesh.cx, mesh.cy, i));
    }
    return distRoadMin + distPointMin*distPointMin;
  }

  static double calculateFUpperBound(Mesh mesh) {
    double distRoadMaxMin = Double.MAX_VALUE;
    for (int i = 0; i < n; i++) {
      double distRoadMax = 0.0;
      for (int j = 0; j < 4; j++) {
        double cx = mesh.cx + DX[j]*mesh.width;
        double cy = mesh.cy + DY[j]*mesh.width;
        distRoadMax = Math.max(
            distRoadMax,
            calculateDistRoad(cx, cy, i));
      }
      distRoadMaxMin = Math.min(distRoadMaxMin, distRoadMax);
    }

    double distPointMaxMin = Double.MAX_VALUE;
    for (int i = 0; i < m; i++) {
      double distPointMax = 0.0;
      for (int j = 0; j < 4; j++) {
        double cx = mesh.cx + DX[j]*mesh.width;
        double cy = mesh.cy + DY[j]*mesh.width;
        distPointMax = Math.max(
            distPointMax,
            calculateDistPoint(cx, cy, i));
      }
      distPointMaxMin = Math.min(distPointMaxMin, distPointMax);
    }
    return distRoadMaxMin + distPointMaxMin*distPointMaxMin;
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    n = s.nextInt();
    m = s.nextInt();
    r = s.nextDouble();
    as = new double[n];
    bs = new double[n];
    cs = new double[n];
    for (int i = 0; i < n; i++) {
      as[i] = s.nextDouble();
      bs[i] = s.nextDouble();
      cs[i] = s.nextDouble();
    }
    ps = new double[m];
    qs = new double[m];
    for (int i = 0; i < m; i++) {
      ps[i] = s.nextDouble();
      qs[i] = s.nextDouble();
    }

    ArrayList<Mesh> before = new ArrayList<Mesh>();
    before.add(new Mesh(0.0, 0.0, r));
    double fMax = 0.0;
    for (int i = 0; i < 48; i++) {
      ArrayList<Mesh> after = new ArrayList<Mesh>();
      for (Mesh mesh : before) {
        double f = calculateF(mesh);
        fMax = Math.max(fMax, f);
      }
      for (Mesh mesh : before) {
        for (int j = 0; j < 4; j++) {
          Mesh next = new Mesh(
              mesh.cx + DX[j]*mesh.width/2,
              mesh.cy + DY[j]*mesh.width/2,
              mesh.width/2);
          double fUpperBound = calculateFUpperBound(next);
          if (fUpperBound >= fMax) {
            after.add(next);
          }
        }
      }
      before = after;
    }
    System.out.println(fMax);
  }
}
