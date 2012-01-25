// Solution to problem Conga Line
//
// Problem setter: Ana Echavarría
// Intended solution: Greedy algorithm
// Complexity: O(n) per test case
//

import java.io.*;
import java.util.*;

public class Conga {
	public static Scanner in;
	public static PrintStream out;
	
	public void run(){
		while (true) {
			int n = in.nextInt();
			if (n == 0) break;
			long a[] = new long[n];
			for (int i = 0; i < n; ++i){
				a[i] = in.nextLong();
			}
			long ans = 0;
			for (int i = 1; i < n; ++i) {
				ans += Math.min(i, n - i) * (a[i] - a[i - 1] - 1);
			}
			out.println(ans);
		}
	}
	
	public static void main(String[] args) {
		Conga.in = new Scanner(System.in);
		Conga.out = new PrintStream(System.out);
		(new Conga()).run();
		in.close();
		out.close();
	}
}
