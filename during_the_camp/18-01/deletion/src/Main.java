
import java.math.BigInteger;
import java.io.*;
import java.util.*;

class Node {
    private static final Random random = new Random(654312);
    
    Node L;
    Node R;
    int x, y, c;
    // x = BST key
    // y = Heap key
    // c = node count
    
    void update() {
        c = 1;
        if (L != null) c += L.c;
        if (R != null) c += R.c;
    }
    
    Node(int x) {
        this.x = x;
        this.y = random.nextInt();
        this.update();
    }
}

public class Main {
    
    Node[] split(Node T, int x) {
        Node [] ans = new Node[2];        
        if (T == null) {
            ans[0] = ans[1] = null;
            return ans;
        } else {
            if (x < T.x) {
                Node [] t = split(T.L, x);
                ans[0] = t[0];
                T.L = t[1];
                T.update();
                ans[1] = T;

            } else {
                Node [] t = split(T.R, x);
                T.R = t[0];
                T.update();
                ans[0] = T;
                ans[1] = t[1];
            }
        }
        return ans;
    }
    
    Node merge(Node L, Node R) {
        Node p;
        if (L == null) p = R;
        else if (R == null) p = L;
        else if (L.y > R.y) {
            L.R = merge(L.R, R);
            p = L;
        } else {
            R.L = merge(L, R.L);
            p = R;
        }
        p.update();
        return p;
    }
    
    Node insert(Node T, Node N) {        
        if (T == null || N.y > T.y) {
            Node [] t = split(T, N.x);
            N.L = t[0];
            N.R = t[1];
            N.update();
            return N;
        }
        if (N.x < T.x) T.L = insert(T.L, N);
        else T.R = insert(T.R, N);
        T.update();
        return T;
    }
    
    Node delete(Node T, int x) {
        if (T == null) return null;
        if (T.x == x) {
            Node P = merge(T.L, T.R);
            P.update();
            return P;
        } else {
            if (x < T.x) T.L = delete(T.L, x);
            else T.R = delete(T.R, x);
            T.update();
            return T;
        }
    }
    
    Node find(Node T, int x) {
        Node cur = T;
        while (cur != null && cur.x != x) {
            if (x < cur.x) cur = cur.L;
            else cur = cur.R;
        }
        return cur;
    }
    
    void print(Node T) {
        if (T == null) return;
        print(T.L);
        
        System.err.printf("x = %d, y = %d, c = %d\n", T.x, T.y, T.c);
        
        print(T.R);
    }
    
    public static BufferedReader in;
    public static PrintWriter out;
    
    int n;
    
    void run() throws IOException {
        
        StringTokenizer tokens = new StringTokenizer(in.readLine());
        
        n = Integer.parseInt(tokens.nextToken());
        int k = Integer.parseInt(tokens.nextToken());
        int l = Integer.parseInt(tokens.nextToken());
        
        
        Node root = new Node(0);
        for  (int i = 1; i <= n; ++i) {
            insert(root, new Node(i));
            System.out.println("After inserting i = " + i);
            print(root);
        }
        
        
    }
        
    public static void main(String[] args) throws Exception {
        in = new BufferedReader(new FileReader("deletion.in"));
        out = new PrintWriter(new FileOutputStream("deletion.out"));
        (new Main()).run();
        Main.in.close();
        Main.out.close();
    }
}
