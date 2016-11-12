import java.util.*;

class Project implements Comparable<Project> {
  int cost;

  Project(int cost) {
    this.cost = cost;
  }

  public int compareTo(Project project) {
    return this.cost - project.cost;
  }
}

class TradingPost extends Project {
  int city;

  TradingPost(int city, int cost) {
    super(cost);
    this.city = city;
  }
}

class Road extends Project {
  int a, b;
  Road(int a, int b, int cost) {
    super(cost);
    this.a = a;
    this.b = b;
  }
}

class City {
  City parent;
  int rank;
  boolean hasTradingPost;

  City() {
    parent = null;
    rank = 0;
    hasTradingPost = false;
  }

  City getRoot() {
    if (parent == null) {
      return this;
    }
    parent = parent.getRoot();
    return parent;
  }

  static boolean merge(City c1, City c2) {
    City c1root = c1.getRoot();
    City c2root = c2.getRoot();
    if (c1root.hasTradingPost && c2root.hasTradingPost) {
      return false;
    }
    if (c1root.rank < c2root.rank) {
      c2root.parent = c1root;
      c1root.hasTradingPost |= c2root.hasTradingPost;
      return true;
    } else if (c1root.rank > c2root.rank) {
      c1root.parent = c2root;
      c2root.hasTradingPost |= c1root.hasTradingPost;
      return true;
    } else if (c1root != c2root) {
      c1root.parent = c2root;
      c2root.hasTradingPost |= c1root.hasTradingPost;
      c2root.rank++;
      return true;
    } else {
      return false;
    }
  }
}

public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    int m = s.nextInt();
    City[] cities = new City[n+1];
    for (int i = 1; i <= n; i++) {
      cities[i] = new City();
    }
    ArrayList<Project> projects = new ArrayList<Project>();
    for (int i = 1; i <= n; i++) {
      int cost = Integer.parseInt(s.next());
      projects.add(new TradingPost(i, cost));
    }
    for (int i = 0; i < m; i++) {
      int a = Integer.parseInt(s.next());
      int b = Integer.parseInt(s.next());
      int cost = Integer.parseInt(s.next());
      projects.add(new Road(a, b, cost));
    }
    Collections.sort(projects);
    long sum = 0;
    for (Project project : projects) {
      if (project instanceof TradingPost) {
        TradingPost tradingPost = (TradingPost)project;
        City rootCity = cities[tradingPost.city].getRoot();
        if (rootCity.hasTradingPost) {
          continue;
        }
//        System.out.printf("%d\n", tradingPost.city);
        sum += tradingPost.cost;
        rootCity.hasTradingPost = true;
      } else if (project instanceof Road) {
        Road road = (Road)project;
        if (City.merge(cities[road.a], cities[road.b])) {
          sum += road.cost;
//        System.out.printf("%d %d\n", road.a, road.b);
        }
      }
    }
    System.out.println(sum);
  }
}
