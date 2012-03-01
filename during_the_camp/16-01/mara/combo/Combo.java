import java.util.*;
import java.io.*;
import java.math.*;

class Combo {
    public static void main(String args[]) throws Exception {
        System.setIn(new FileInputStream("combo.in"));
        System.setOut(new PrintStream("combo.out"));
        Scanner cin = new Scanner(System.in);
        PrintStream cout = System.out;
        
        int n, k; BigInteger l;
        n = cin.nextInt();
        k = cin.nextInt();
        l = cin.nextBigInteger();

        BigInteger choose[][] = new BigInteger[n + 1][n + 1];
        for (int i = 0; i <= n; ++i) for (int j = 0; j <= n; ++j) choose[i][j] = BigInteger.ZERO;
        choose[0][0] = BigInteger.ONE;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= n; ++j) {
                choose[i][j] = choose[i - 1][j];
                if (j - 1 >= 0) choose[i][j] = choose[i][j].add(choose[i - 1][j - 1]);
            }
        }
        
        for (int i = 0; i < n; ++i){
            if (k == 0) break;
            if (choose[n - 1 - i][k - 1].compareTo(l) >= 0) {
                cout.print(i + 1);
                cout.print(" ");
                k--;
            } else {
                l = l.subtract(choose[n - 1 - i][k - 1]);
            }
        }
        cout.println();
    }
}