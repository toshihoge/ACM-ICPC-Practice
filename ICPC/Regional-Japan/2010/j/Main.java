import java.util.*;

class Token {
  public final static char PLUS = '+';
  public final static char MINUS = '-';
  public final static char NEGATE = '^';
  public final static char MULTIPLY = '*';
  public final static char OPENCASEARC = '(';
  public final static char CLOSECASEARC = ')';
  public final static char COMMA = ',';
  public final static char OPENBRACKET = '[';
  public final static char CLOSEBRACKET = ']';
  public final static char TRANSPOSE = '\'';
  public final static char SPACE = ' ';
  public final static char SEMICOLON = ';';
  public final static char NUMBER = 'n';
  public final static char VAR = 'v';
  public final static char NULL = '#';
  
  char type;
  int number;
  
  Token(char t, int n) {
    type = t;
    number = n;
  }
  
  Token(char t) {
    this(t, 0);
  }
}

class Matrix {
  private final static int MOD = 32768;
  
  int begin;
  int h;
  int w;
  long[][] matrix;
  
  public Matrix(long v) {
    begin = 0;
    h = 1;
    w = 1;
    matrix = new long[1][1];
    matrix[0][0] = v;
  }
  
  public Matrix(int h, int w) {
    begin = 0;
    this.h = h;
    this.w = w;
    matrix = new long[this.h][this.w];
  }
  
  public Matrix setBegin(int b) {
    begin = b;
    return this;
  }
  
  private static long normalize(long n) {
    while (n < 0) {
      n += MOD;
    }
    return n % MOD;
  }
  
  private boolean isScale() {
    return h == 1 && w == 1;
  }
  
  public static Matrix add(Matrix mb1, Matrix mb2) {
    if (mb1.isScale()) {
      return addScale(mb2, mb1.matrix[0][0]);
    } else if (mb2.isScale()) {
      return addScale(mb1, mb2.matrix[0][0]);
    } else {
      return addSameSize(mb1, mb2);
    }
  }
  
  private static Matrix addSameSize(Matrix mb1, Matrix mb2) {
    if (mb1.h == mb2.h && mb1.w == mb2.w) {
      Matrix output = new Matrix(mb1.h, mb1.w);
      for (int i = 0; i < mb1.h; i++) {
        for (int j = 0; j < mb1.w; j++) {
          output.matrix[i][j] = normalize(mb1.matrix[i][j] + mb2.matrix[i][j]);
        }
      }
      return output;
    } else {
      throw new RuntimeException();
    }
  }
  
  private static Matrix addScale(Matrix mb, long scale) {
    Matrix output = new Matrix(mb.h, mb.w);
    for (int i = 0; i < mb.h; i++) {
      for (int j = 0; j < mb.w; j++) {
        output.matrix[i][j] = normalize(mb.matrix[i][j] + scale);
      }
    }
    return output;
  }
  
  public static Matrix sub(Matrix mb1, Matrix mb2) {
    if (mb1.isScale()) {
      return multiplyScale(addScale(mb2, -mb1.matrix[0][0]), -1);
    } else if (mb2.isScale()) {
      return addScale(mb1, -mb2.matrix[0][0]);
    } else {
      return addSameSize(mb1, multiplyScale(mb2, -1));
    }
  }
  
  private static Matrix multiplyMatrix(Matrix mb1, Matrix mb2) {
    if (mb1.w == mb2.h) {
      Matrix output = new Matrix(mb1.h, mb2.w);
      for (int i = 0; i < mb1.h; i++) {
        for (int j = 0; j < mb2.w; j++) {
          long sum = 0;
          for (int k = 0; k < mb1.w; k++) {
            sum += mb1.matrix[i][k] * mb2.matrix[k][j];
          }
          output.matrix[i][j] = normalize(sum);
        }
      }
      return output;
    } else {
      throw new RuntimeException();
    }
  }
  
  public static Matrix mul(Matrix mb1, Matrix mb2) {
    if (mb1.isScale()) {
      return multiplyScale(mb2, mb1.matrix[0][0]);
    } else if (mb2.isScale()) {
      return multiplyScale(mb1, mb2.matrix[0][0]);
    } else {
      return multiplyMatrix(mb1, mb2);
    }
  }
  
  public static Matrix negate(Matrix mb) {
    return multiplyScale(mb, -1);
  }
  
  private static Matrix multiplyScale(Matrix mb, long scale) {
    Matrix output = new Matrix(mb.h, mb.w);
    for (int i = 0; i < mb.h; i++) {
      for (int j = 0; j < mb.w; j++) {
        output.matrix[i][j] = normalize(mb.matrix[i][j] * scale);
      }
    }
    return output;
  }
  
  public static Matrix transpose(Matrix mb) {
    Matrix output = new Matrix(mb.w, mb.h);
    for (int i = 0; i < mb.h; i++) {
      for (int j = 0; j < mb.w; j++) {
        output.matrix[j][i] = mb.matrix[i][j];
      }
    }
    return output;
  }
  
  public static Matrix indexedPrimary(Matrix mb1, Matrix mb2, Matrix mb3) {
    if (mb2.h == 1 && mb3.h == 1) {
      Matrix output = new Matrix(mb2.w, mb3.w);
      for (int i = 0; i < mb2.w; i++) {
        for (int j = 0; j < mb3.w; j++) {
          output.matrix[i][j] = mb1.matrix[(int)mb2.matrix[0][i]-1][(int)mb3.matrix[0][j]-1];
        }
      }
      return output;
    } else {
      throw new RuntimeException();
    }
  }
  
  public static Matrix concatenateRowSequence(Matrix mb1, Matrix mb2) {
    if (mb1.w == mb2.w) {
      Matrix output = new Matrix(mb1.h+mb2.h, mb1.w);
      for (int i = 0; i < mb1.h; i++) {
        for (int j = 0; j < mb1.w; j++) {
          output.matrix[i][j] = mb1.matrix[i][j];
        }
      }
      for (int i = 0; i < mb2.h; i++) {
        for (int j = 0; j < mb2.w; j++) {
          output.matrix[mb1.h + i][j] = mb2.matrix[i][j];
        }
      }
      return output;
    } else {
      throw new RuntimeException();
    }
  }
  
  public static Matrix concatenateRow(Matrix mb1, Matrix mb2) {
    if (mb1.h == mb2.h) {
      Matrix output = new Matrix(mb1.h, mb1.w + mb2.w);
      for (int i = 0; i < mb1.h; i++) {
        for (int j = 0; j < mb1.w; j++) {
          output.matrix[i][j] = mb1.matrix[i][j];
        }
        for (int j = 0; j < mb2.w; j++) {
          output.matrix[i][mb1.w + j] = mb2.matrix[i][j];
        }
      }
      return output;
    } else {
      throw new RuntimeException();
    }
  }
  
  public void print() {
    for (int i = 0; i < h; i++) {
      System.out.print(matrix[i][0]);
      for (int j = 1; j < w; j++) {
        System.out.print(" ");
        System.out.print(matrix[i][j]);
      }
      System.out.print("\n");
    }
  }
}

class Parser {
  Matrix[] environment;
  ArrayList<Token> tokens;
  
  Parser (Matrix[] environment) {
    this.environment = environment;
  }
  
  private Matrix parseExpr(int e) {
    Matrix term = parseTerm(e);
    if (term == null) {
      return null;
    }
    
    if (getTokenType(term.begin-1) == Token.PLUS) {
      Matrix expr = parseExpr(term.begin-2);
      if (expr != null) {
        return Matrix.add(expr, term).setBegin(expr.begin);
      }
    }
    if (getTokenType(term.begin-1) == Token.MINUS) {
      Matrix expr = parseExpr(term.begin-2);
      if (expr != null) {
        return Matrix.sub(expr, term).setBegin(expr.begin);
      }
    }
    return term;
  }
  
  private Matrix parseTerm(int e) {
    Matrix factor = parseFactor(e);
    if (factor == null) {
      return null;
    }
    
    if (getTokenType(factor.begin-1) == Token.MULTIPLY) {
      Matrix term = parseTerm(factor.begin-2);
      if (term != null) {
        return Matrix.mul(term, factor).setBegin(term.begin);
      }
    }
    return factor;
  }
  
  private Matrix parseFactor(int e) {
    Matrix primary = parsePrimary(e);
    if (primary == null) {
      return null;
    }
    if (getTokenType(primary.begin-1) == Token.NEGATE) {
      return Matrix.negate(primary).setBegin(primary.begin-1);
    } else {
      return primary;
    }
  }
  
  private Matrix parseIndexedPrimary(int e) {
    if (getTokenType(e) == Token.CLOSECASEARC) {
      Matrix expr = parseExpr(e-1);
      if (expr != null && getTokenType(expr.begin-1) == Token.COMMA) {
        Matrix exprFront = parseExpr(expr.begin - 2);
        if (exprFront != null && getTokenType(exprFront.begin-1) == Token.OPENCASEARC) {
          Matrix primary = parsePrimary(exprFront.begin - 2);
          if (primary != null) {
            return Matrix.indexedPrimary(primary, exprFront, expr).setBegin(primary.begin);
          }
        }
      }
    }
    return null;
  }
  
  private Matrix parseCaseArcBlock(int e) {
    if (getTokenType(e) == Token.CLOSECASEARC) {
      Matrix expr = parseExpr(e-1);
      if (expr != null && getTokenType(expr.begin-1) == Token.OPENCASEARC) {
        return expr.setBegin(expr.begin-1);
      }
    }
    return null;
  }
      
  private Matrix parseTranspose(int e) {
    if (getTokenType(e) == Token.TRANSPOSE) {
      Matrix primary = parsePrimary(e-1);
      if (primary != null) {
        return Matrix.transpose(primary).setBegin(primary.begin);
      }
    }
    return null;
  }
  
  private Matrix parsePrimary(int e) {
    Matrix result = parseNumber(e);
    if (result != null) return result;
    result = parseVar(e);
    if (result != null) return result;
    result = parseMatrix(e);
    if (result != null) return result;
    result = parseCaseArcBlock(e);
    if (result != null) return result;
    result = parseIndexedPrimary(e);
    if (result != null) return result;
    result = parseTranspose(e);
    return result;
  }
  
  private Matrix parseMatrix(int e) {
    if (getTokenType(e) == Token.CLOSEBRACKET) {
      Matrix rowSequence = parseRowSequence(e-1);
      if (rowSequence != null && getTokenType(rowSequence.begin-1) == Token.OPENBRACKET) {
        return rowSequence.setBegin(rowSequence.begin-1);
      }
    }
    return null;
  }
  
  private Matrix parseRowSequence(int e) {
    Matrix row = parseRow(e);
    if (row == null) {
      return null;
    }
    
    if (getTokenType(row.begin-1) == Token.SEMICOLON) {
      Matrix rowSequence = parseRowSequence(row.begin-2);
      if (rowSequence != null) {
        return Matrix.concatenateRowSequence(rowSequence, row).setBegin(rowSequence.begin);
      }
    }
    return row;
  }
  
  private Matrix parseRow(int e) {
    Matrix expr = parseExpr(e);
    if (expr == null) {
      return null;
    }
    if(getTokenType(expr.begin-1) == Token.SPACE) {
      Matrix row = parseRow(expr.begin-2);
      if (row != null) {
        return Matrix.concatenateRow(row, expr).setBegin(row.begin);
      }
    }
    return expr;
  }
  
  private Matrix parseNumber(int e) {
    if (getTokenType(e) == Token.NUMBER) {
      return new Matrix(tokens.get(e).number).setBegin(e);
    }
    return null;
  }
  
  private Matrix parseVar(int e) {
    if (getTokenType(e) == Token.VAR) {
      return environment[tokens.get(e).number].setBegin(e);
    }
    return null;
  }
  
  private char getTokenType(int index) {
    if (index < 0) return Token.NULL;
    return tokens.get(index).type;
  }
  
  private static ArrayList<Token> lex(String line) {
    ArrayList<Token> output = new ArrayList<Token>();
    int index = 0;
    while (index < line.length()) {
      char c = line.charAt(index);
      if (Character.isDigit(c)) {
        int number = 0;
        while (index < line.length() && Character.isDigit(line.charAt(index))) {
          number *= 10;
          number += (line.charAt(index) - '0');
          index++;
        }
        output.add(new Token(Token.NUMBER, number));
      } else if ('A' <= c && c <= 'Z') {
        output.add(new Token(Token.VAR, c - 'A'));
        index++;
      } else {
        switch (c) {
        case '+':
        case '-':
        case '^':
        case '*':
        case '(':
        case ')':
        case ',':
        case '[':
        case ']':
        case '\'':
        case ' ':
        case ';':
          output.add(new Token(c));
          break;
        default:
          throw new RuntimeException("Lex exception!");
        }
        index++;
      }
    }
    return output;
  }
  
  private static String convert3SpacesTo1Space(String line) {
    while (line.contains("---")) {
      line = line.replaceAll("---", "-");
    }
    return line;
  }
  
  public static String convert2Spaces(String line) {
    line = line.replaceAll("^--", "");
    line = line.replaceAll("([0-9A-Z\\)\\]'])--", "$1+");
    line = line.replaceAll("([\\(\\[ ;\\*\\+])--", "$1");
    line = line.replaceAll("^-", "^");
    line = line.replaceAll("([\\(\\[ ;\\*\\+])-", "$1^");
    return line;
  }
  
  private static String preprocess(String line) {
    line = line.replaceAll("\\.", "");
    line = convert3SpacesTo1Space(line);
    line = convert2Spaces(line);
    return line;
  }
  
  public Matrix parse(String line) {
    line = preprocess(line);
    tokens = lex(line);
    Matrix expr = parseExpr(tokens.size() - 1);
    if (expr != null && expr.begin == 0) {
      return expr;
    } else {
      throw new RuntimeException();
    }
  }
}

public class Main {
  private static void solve(String[] lines) {
    Matrix[] results = new Matrix[26];
    Arrays.fill(results, null);
    for (String line : lines) {
      String rightPart = line.substring(2);
      Parser parser = new Parser(results);
      results[line.charAt(0) - 'A'] = parser.parse(rightPart);
      results[line.charAt(0) - 'A'].print();
    }
    System.out.print("-----\n");
  }
  
  public static void main (String[] args) {
    Scanner s = new Scanner(System.in);
    while (true) {
      int n = Integer.parseInt(s.nextLine());
      if (n == 0) {
        break;
      }
      String lines[] = new String[n];
      for (int i = 0; i < n; i++) {
        lines[i] = s.nextLine();
      }
      solve(lines);
    }
  }
}
