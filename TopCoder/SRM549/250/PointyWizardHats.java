import java.util.*;
public class PointyWizardHats {
  int[] ths, trs, bhs, brs;
  int nt;
  int nb;
  int m;

  private boolean canMakeHat(int th, int tr, int bh, int br) {
    //th/tr <= bh/br
    if (th*br <= bh*tr) {
      return false;
    }
    if (tr >= br) {
      return false;
    }
    return true;
  }
  private boolean[][] makeMatrix() {
    boolean[][] matrix = new boolean[m][m];
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < m; j++) {
        matrix[i][j] = false;
      }
    }

    for (int i = 0; i < nt; i++) {
      for (int j = 0; j < nb; j++) {
        matrix[i][nt + j] = canMakeHat(ths[i], trs[i], bhs[j], brs[j]);
      }
    }

    for (int i = 0; i < nt; i++) {
      matrix[m-2][i] = true;
    }
    for (int i = 0; i < nb; i++) {
      matrix[nt + i][m-1] = true;
    }
    return matrix;
  }

  private boolean dfs(int prev, boolean[][] matrix, boolean[] visit) {
    if (prev == m-1) {
      return true;
    }
    visit[prev] = true;

    for (int i = 0; i < m; i++) {
      if (matrix[prev][i]) {
        if (visit[i]) {
          continue;
        }
        if (dfs(i, matrix, visit)) {
          matrix[prev][i] = false;
          matrix[i][prev] = true;
          return true;
        }
      }
    }
    return false;
  }

  private boolean findNewPath(boolean[][] matrix) {
    boolean[] visit = new boolean[m];
    Arrays.fill(visit, false);
    return dfs(m-2, matrix, visit);
  }

  private int findMaxMaching(boolean[][] matrix) {
    int result = 0;
    while(findNewPath(matrix)) {
      result++;
    }
    return result;
  }

  public int getNumHats(int[] topHeight, int[] topRadius, int[] bottomHeight, int[] bottomRadius) {
    nt = topHeight.length;
    ths = topHeight;
    trs = topRadius;
    nb = bottomHeight.length;
    bhs = bottomHeight;
    brs = bottomRadius;
    m = nt+nb+2;

    return findMaxMaching(makeMatrix());
  }

// BEGIN CUT HERE
    public static void main(String[] args) {
        try {
            eq(0,(new PointyWizardHats()).getNumHats(new int[] {30}, new int[] {3}, new int[] {3}, new int[] {30}),1);
            eq(1,(new PointyWizardHats()).getNumHats(new int[] {4,4}, new int[] {4,3}, new int[] {5,12}, new int[] {5,4}),1);
            eq(2,(new PointyWizardHats()).getNumHats(new int[] {3}, new int[] {3}, new int[] {1,1}, new int[] {2,4}),1);
            eq(3,(new PointyWizardHats()).getNumHats(new int[] {10,10}, new int[] {2,5}, new int[] {2,9}, new int[] {3,6}),2);
            eq(4,(new PointyWizardHats()).getNumHats(new int[] {3,4,5}, new int[] {5,4,3}, new int[] {3,4,5}, new int[] {3,8,5}),2);
            eq(5,(new PointyWizardHats()).getNumHats(new int[] {1,2,3,4,5}, new int[] {2,3,4,5,6}, new int[] {2,3,4,5,6}, new int[] {1,2,3,4,5}),0);
            eq(6,(new PointyWizardHats()).getNumHats(new int[] {123,214,232,323,342,343}, new int[] {123,123,232,123,323,434}, new int[] {545,322,123,545,777,999}, new int[] {323,443,123,656,767,888}),5);
            eq(7,(new PointyWizardHats()).getNumHats(new int[] {999,999,999,10000,10000,10000}, new int[] {10000,10000,10000,1,2,3}, new int[] {2324,2323,234,5454,323,232}, new int[] {1,2,3222,434,5454,23}),3);
        } catch( Exception exx) {
            System.err.println(exx);
            exx.printStackTrace(System.err);
        }
    }
    private static void eq( int n, int a, int b ) {
        if ( a==b )
            System.err.println("Case "+n+" passed.");
        else
            System.err.println("Case "+n+" failed: expected "+b+", received "+a+".");
    }
    private static void eq( int n, char a, char b ) {
        if ( a==b )
            System.err.println("Case "+n+" passed.");
        else
            System.err.println("Case "+n+" failed: expected '"+b+"', received '"+a+"'.");
    }
    private static void eq( int n, long a, long b ) {
        if ( a==b )
            System.err.println("Case "+n+" passed.");
        else
            System.err.println("Case "+n+" failed: expected \""+b+"L, received "+a+"L.");
    }
    private static void eq( int n, boolean a, boolean b ) {
        if ( a==b )
            System.err.println("Case "+n+" passed.");
        else
            System.err.println("Case "+n+" failed: expected "+b+", received "+a+".");
    }
    private static void eq( int n, String a, String b ) {
        if ( a != null && a.equals(b) )
            System.err.println("Case "+n+" passed.");
        else
            System.err.println("Case "+n+" failed: expected \""+b+"\", received \""+a+"\".");
    }
    private static void eq(int n, double a, double b) {
        if (Math.abs(a - b) < 1e-9)
            System.err.println("Case "+n+" passed.");
        else
            System.err.println("Case "+n+" failed: expected \""+b+"\", received \""+a+"\".");
    }
    private static void eq( int n, int[] a, int[] b ) {
        if ( a.length != b.length ) {
            System.err.println("Case "+n+" failed: returned "+a.length+" elements; expected "+b.length+" elements.");
            return;
        }
        for ( int i= 0; i < a.length; i++)
            if ( a[i] != b[i] ) {
                System.err.println("Case "+n+" failed. Expected and returned array differ in position "+i);
                print( b );
                print( a );
                return;
            }
        System.err.println("Case "+n+" passed.");
    }
    private static void eq( int n, long[] a, long[] b ) {
        if ( a.length != b.length ) {
            System.err.println("Case "+n+" failed: returned "+a.length+" elements; expected "+b.length+" elements.");
            return;
        }
        for ( int i= 0; i < a.length; i++ )
            if ( a[i] != b[i] ) {
                System.err.println("Case "+n+" failed. Expected and returned array differ in position "+i);
                print( b );
                print( a );
                return;
            }
        System.err.println("Case "+n+" passed.");
    }
    private static void eq( int n, String[] a, String[] b ) {
        if ( a.length != b.length) {
            System.err.println("Case "+n+" failed: returned "+a.length+" elements; expected "+b.length+" elements.");
            return;
        }
        for ( int i= 0; i < a.length; i++ )
            if( !a[i].equals( b[i])) {
                System.err.println("Case "+n+" failed. Expected and returned array differ in position "+i);
                print( b );
                print( a );
                return;
            }
        System.err.println("Case "+n+" passed.");
    }
    private static void print( int a ) {
        System.err.print(a+" ");
    }
    private static void print( long a ) {
        System.err.print(a+"L ");
    }
    private static void print( String s ) {
        System.err.print("\""+s+"\" ");
    }
    private static void print( int[] rs ) {
        if ( rs == null) return;
        System.err.print('{');
        for ( int i= 0; i < rs.length; i++ ) {
            System.err.print(rs[i]);
            if ( i != rs.length-1 )
                System.err.print(", ");
        }
        System.err.println('}');
    }
    private static void print( long[] rs) {
        if ( rs == null ) return;
        System.err.print('{');
        for ( int i= 0; i < rs.length; i++ ) {
            System.err.print(rs[i]);
            if ( i != rs.length-1 )
                System.err.print(", ");
        }
        System.err.println('}');
    }
    private static void print( String[] rs ) {
        if ( rs == null ) return;
        System.err.print('{');
        for ( int i= 0; i < rs.length; i++ ) {
            System.err.print( "\""+rs[i]+"\"" );
            if( i != rs.length-1)
                System.err.print(", ");
        }
        System.err.println('}');
    }
    private static void nl() {
        System.err.println();
    }
// END CUT HERE
}
