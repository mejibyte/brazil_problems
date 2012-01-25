// Solution to problem Stones
//
// Problem setter: Andrés Mejía-Posada <andr@esmejia.com>
// Intended solution: Dynamic Programming
// Complexity: O(n^2) per test case

import java.io.PrintStream;
import java.util.Scanner;


public class Stones {
	public static Scanner in;
	public static PrintStream out;

	boolean memo[][];
	boolean been[][];

	public boolean canWin(int pile, int limit) {
		if (pile == 0) return false;
		limit = Math.min(limit, pile);
		if (been[pile][limit]) return memo[pile][limit];
		boolean ans = false;
		for (int take = 1; take <= limit && take <= pile; ++take) {
			if (!canWin(pile - take, 2 * take)) {
				ans = true;
				break;
			}
		}
		been[pile][limit] = true;
		return memo[pile][limit] = ans;
	}

	public void run() {
		memo = new boolean[1001][1001];
		been = new boolean[1001][1001];

		int n;
		while (true) {
			n = in.nextInt();
			if (n == 0) break;
			assert 2 <= n && n <= 1000;

			if (canWin(n, n - 1)) {
				out.println("Alicia");
			} else {
				out.println("Roberto");
			}	
		}
	}
	public static void main(String[] args) {
		Stones.in = new Scanner(System.in);
		Stones.out = new PrintStream(System.out);
		(new Stones()).run();
		in.close();
		out.close();
	}
}
