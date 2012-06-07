import java.util.*;
public class StrIIRec {
  int n;
  int minInv;
  char[] minStrChars;

  String dfs(int index, char[] array, boolean[] used, boolean prefixEqual, int maxInv) {
    if (index == n) {
      return new String(array);
    }
    if (maxInv < minInv) {
      return "";
    }
    int invCount = 0;
    for (int i = 0; i < n; i++) {
      if (used[i]) {
        continue;
      } else {
        int nextMaxInv = maxInv - (n-1) + index + invCount;
        used[i] = true;
        array[index] = (char)('a' + i);
        if (!prefixEqual || minStrChars[index] <= array[index]) {
          String result = dfs(index+1, array, used, prefixEqual && minStrChars[index] == array[index], nextMaxInv);
          if (!result.equals("")) {
            return result;
          }
        }
        used[i] = false;
        invCount++;
      }
    }
    return "";
  }

  public String recovstr(int n, int minInv, String minStr) {
    this.n = n;
    this.minInv = minInv;
    minStrChars = new char[n];
    Arrays.fill(minStrChars, '0');
    for (int i = 0; i < minStr.length(); i++) {
      minStrChars[i] = minStr.charAt(i);
    }
    boolean[] used = new boolean[n];
    Arrays.fill(used, false);
    return dfs(0, new char[n], used, true, n*(n-1)/2);
  }

// BEGIN CUT HERE
    public static void main(String[] args) {
        try {
            eq(0,(new StrIIRec()).recovstr(2, 1, "ab"),"ba");
            eq(1,(new StrIIRec()).recovstr(9, 1, "efcdgab"),"efcdgabhi");
            eq(2,(new StrIIRec()).recovstr(11, 55, "debgikjfc"),"kjihgfedcba");
            eq(3,(new StrIIRec()).recovstr(15, 0, "e"),"eabcdfghijklmno");
            eq(4,(new StrIIRec()).recovstr(9, 20, "fcdebiha"),"fcdehigba");
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
