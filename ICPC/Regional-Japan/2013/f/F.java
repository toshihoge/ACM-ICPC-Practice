import java.util.*;

public class F {
  private static final int LIMIT = 64;
  private static final int TIMES = 32;
  
  private static void add(HashMap<Long, HashMap<Long, ArrayList<Vec>>> buckets, long i, long j, Vec vec) {
    HashMap<Long, ArrayList<Vec>> sub1 = buckets.get(i);
    if (sub1 == null) {
      sub1 = new HashMap<Long, ArrayList<Vec>>();
      buckets.put(i, sub1);
    }
    
    ArrayList<Vec> sub2 = sub1.get(j);
    if (sub2 == null) {
      sub2 = new ArrayList<Vec>();
      sub1.put(j, sub2);
    }
    
    sub2.add(vec);
  }
  
  private static int[] solve(int m, int n, int s, int w, int[] x, int[] y, int[] z) {
    HashSet<Vec> vecset = new HashSet<Vec>();
    for (int i = 0; i < m; i++) {
      vecset.add(new Vec(x[i], y[i], z[i]));
    }
    
    // Given input generator.
    int g = s;
    for(int i=m+1; i<=m+n; i++) {
      vecset.add(new Vec((g/7) % 100 + 1, (g/700) % 100 + 1, (g/70000) % 100 + 1));
      if( g%2 == 0 ) {
        g = (g/2);
      } else {
        g = ((g/2) ^ w);
      }
    }
    Vec[] vecs = vecset.toArray(new Vec[0]);
    Answer answer = new Answer(vecs[0], vecs[1]);
    
    double meshSize = 1.0;
    for (int t = 0; t < TIMES; t++) {
      HashMap<Long, HashMap<Long, ArrayList<Vec>>> buckets = new HashMap<Long, HashMap<Long, ArrayList<Vec>>>();
      for (Vec vec : vecs) {
        long i = (long)(vec.normA / meshSize);
        long j = (long)(vec.normB / meshSize);
        add(buckets, i, j, vec);
        add(buckets, i, j+1, vec);
        add(buckets, i+1, j+1, vec);
        add(buckets, i+1, j, vec);
      }
      
      vecset = new HashSet<Vec>();
      for (HashMap<Long, ArrayList<Vec>> sub1 : buckets.values()) {
        for (ArrayList<Vec> sub2 : sub1.values()) {
          if (sub2.size() > LIMIT && t < TIMES - 1) {
            for (Vec vec : sub2) {
              vecset.add(vec);
            }
          } else {
            for (int i = 0; i < sub2.size(); i++) {
              for (int j = i+1; j < sub2.size(); j++) {
                Answer temp = new Answer(sub2.get(i), sub2.get(j));
                if (answer.compareTo(temp) > 0) {
                  answer = temp;
                }
              }
            }
          }
        }
      }
      vecs = vecset.toArray(new Vec[0]);
      meshSize *= 0.5;
    }
    return answer.output;
  }
  
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    
    int counter = 1;
    while(true) {
      int m = sc.nextInt();
      int n = sc.nextInt();
      int s = sc.nextInt();
      int w = sc.nextInt();
      if (n + m == 0) {
        break;
      }
      int[] x = new int[m];
      int[] y = new int[m];
      int[] z = new int[m];
      for (int i = 0; i < m; i++) {
        x[i] = sc.nextInt();
        y[i] = sc.nextInt();
        z[i] = sc.nextInt();
      }
      int[] ans = solve(m, n, s, w, x, y, z);
      System.out.print(ans[0]);
      for (int i = 1; i < 6; i++) {
        System.out.printf(" %d", ans[i]);
      }
      System.out.println();
    }
  }
}

class Vec implements Comparable<Vec> {
  int x, y, z;
  double normA, normB;
  Vec(int x, int y, int z) {
    this.x = x;
    this.y = y;
    this.z = z;
    initNorm();
  }
  
  public int hashCode() {
    return 16384*x + 128*y + z;
  }
  
  public boolean equals(Object obj) {
    if (!(obj instanceof Vec)) {
      return false;
    }
    Vec vec = (Vec) obj;
    return this.x == vec.x && this.y == vec.y && this.z == vec.z;
  }
  
  // normA * (-1, 1, 0) + normB * (-1/2, -1/2, 1) + (1, 0, 0)
  // normA * (-1/2^0.5, 1/2^0.5, 0) + normB * (-1/6^0.5, -1/6^0.5, 2/6^0.5) + (1, 0 0)
  // normA * (-1/2^0.5) + normB * (-1/6^0.5) + 1 = normX
  // normA * (1/2^0.5)  + normB * (-1/6^0.5)     = normY
  // normA * 0          + normB * (2/6^0.5)      = normZ
  private void initNorm() {
    double normX = (double)x / (x + y + z);
    double normY = (double)y / (x + y + z);
    double normZ = (double)z / (x + y + z);
    normB = normZ * Math.sqrt(6) / 2;
    normA = (normY + normB / Math.sqrt(6)) * Math.sqrt(2);
    // Verify
    if (Math.abs(-normA / Math.sqrt(2) - normB / Math.sqrt(6) + 1.0 - normX) > 1e-6) {
      throw new RuntimeException();
    }
  }
  
  public int compareTo(Vec vec) {
    if (this.x != vec.x) {
      return this.x - vec.x;
    }
    if (this.y != vec.y) {
      return this.y - vec.y;
    }
    return this.z - vec.z;
  }
  
  public long norm() {
    return x*x + y*y + z*z;
  }
  
  public Vec sub(Vec vec) {
    return new Vec(this.x - vec.x, this.y - vec.y, this.z - vec.z);
  }
}

class Answer {
  private static final double EPS = 1e-9;
  
  int[] output;
  long acos2a;
  long acos2b;
  
  public Answer(Vec v1, Vec v2) {
    Vec[] vs = new Vec[]{v1, v2};
    Arrays.sort(vs);
    output = new int[]{
      vs[0].x,
      vs[0].y,
      vs[0].z,
      vs[1].x,
      vs[1].y,
      vs[1].z,
    };
    long a2 = v1.norm();
    long b2 = v2.norm();
    long c2 = v1.sub(v2).norm();
    acos2a = (a2 + b2 - c2)*(a2 + b2 - c2);
    acos2b = 4 * a2 * b2;
    // Completely same direction is not acceptable.
    if (acos2a == acos2b) {
      acos2a = 0;
      acos2b = 1;
    }
  }
  
  public int compareTo(Answer answer) {
    // this.acos2a / this.acos2b > answer.acos2a / answer.acos2b
    // this.acos2a * answer.acos2b > answer.acos2a * this.acos2b
    long diff = this.acos2a * answer.acos2b - answer.acos2a * this.acos2b;
    if (diff > 0) {
      return -1;
    } else if(diff < 0) {
      return 1;
    }
    for (int i = 0; i < 6; i++) {
      if (this.output[i] != answer.output[i]) {
        return this.output[i] - answer.output[i];
      }
    }
    return 0;
  }
}
