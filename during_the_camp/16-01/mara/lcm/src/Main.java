import java.math.BigInteger;
import java.io.*;
import java.util.*;

class Main {
	
	public static BigInteger lcm(BigInteger a, BigInteger b) {
		BigInteger g = a.gcd(b);
		return a.divide(g).multiply(b);
	}
	
	public static void main(String[] args) throws FileNotFoundException {
		System.setIn(new FileInputStream("lcm.in"));
		System.setOut(new PrintStream(new FileOutputStream("1cm.out")));
		
		Scanner cin = new Scanner(System.in);
		
	    int n = cin.nextInt();

	    BigInteger ans = BigInteger.ONE;
	    for (int i = 2; i <= n; ++i) {
	      ans = Main.lcm(ans, BigInteger.valueOf(i));
	    }
	    
	    System.out.println(ans);
	}
}