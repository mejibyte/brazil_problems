// Solution to problem Secret Word
//
// Problem setter: Andrés Mejía-Posada <andr@esmejia.com>
// Intended solution: Run KMP on str + "$" + reverse(str)
// Complexity: O(n) per test case
//
import java.io.*;
import java.util.*;

public class Secret {
	public static BufferedReader in;
	public static PrintStream out;
	
	private void solve(String s) {
		int n = s.length();
		StringBuilder b = new StringBuilder(s);
		b.append("$");
		
		StringBuilder reverser = new StringBuilder(s);
		reverser.reverse();
		b.append(reverser.toString());
		
		s = b.toString();
		// s = s + $ + reverse(s)
		int m = 2 * n + 1;
		assert m == s.length();
		
		int border[] = new int[m];
		border[0] = 0;
		for (int i = 1; i < m; ++i){
			border[i] = border[i - 1];
			while (border[i] > 0 && s.charAt(border[i]) != s.charAt(i)) {
				border[i] = border[ border[i] - 1 ];
			}
			if (s.charAt(border[i]) == s.charAt(i)) {
				border[i]++;
			}
		}
		int best = 0, at = -1;
		for (int i = n + 1; i < m; ++i) {
			if (border[i] > best) {
				best = border[i];
				at = i;
			}
		}
		String ans = s.substring(m - 1 - at, m - 1 - at + best);
		out.println(ans);
	}
	
	public void run() throws NumberFormatException, IOException{
		int T = Integer.parseInt(in.readLine());
		assert T <= 150;
		for (int t = 0; t < T; ++t) {
			String s = in.readLine();
			solve(s);
		}
	}
	
	public static void main(String[] args) throws IOException {
		Secret.in = new BufferedReader(new InputStreamReader(System.in));
		Secret.out = new PrintStream(System.out);
		(new Secret()).run();
		in.close();
		out.close();
	}
}
