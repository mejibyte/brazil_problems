import java.math.BigInteger;
import java.io.*;
import java.util.*;

class Fido {
	public static void main(String[] args) throws FileNotFoundException {
		System.setIn(new FileInputStream("fido.in"));
		System.setOut(new PrintStream(new FileOutputStream("fido.out")));
		
		Scanner cin = new Scanner(System.in);
		
	    int n = cin.nextInt();

	    BigInteger ans[] = new BigInteger[1001];
	    ans[0] = BigInteger.ZERO;
	    ans[1] = BigInteger.ONE;
	    ans[2] = BigInteger.ONE;
	    for (int i = 3; i <= 1000; ++i) {
	    	ans[i] = ans[i - 1].add(ans[i - 3]);
	    }
	    System.out.println(ans[n]);
	}
}