import java.math.BigInteger;
import java.io.*;
import java.util.*;

class Main {
	
	public static BigInteger fact(int n) {
		BigInteger ans = BigInteger.ONE;
		for (int i = 2; i <= n; ++i) {
			ans = ans.multiply(BigInteger.valueOf(i));
		}
		return ans;
	}
	
	public static void main(String[] args) throws FileNotFoundException {
		//System.setIn(new FileInputStream("gen.in"));
		//System.setOut(new PrintStream(new FileOutputStream("gen.out")));
		
		Scanner cin = new Scanner(System.in);
		
	    int n = cin.nextInt();
	    BigInteger k = cin.nextBigInteger();
	    
	    TreeSet<Integer> avail = new TreeSet<Integer>();
	    for (int i = 0; i < n; ++i) {
	    	avail.add(i + 1);
	    }
	    
	    int ans[] = new int[n];
	    
	    for (int i = 0; i < n; ++i) {
	    	
	    	BigInteger m = fact(n - i - 1);
	    	
	    	for (Integer p : avail) {
	    		if (k.compareTo(m) <= 0) {
	    			// put p here
	    			ans[i] = p;
	    			avail.remove(p);
	    			break;
	    			
	    		} else {
	    			k = k.subtract(m);
	    		}
	    	}
	    }
	    
	    for (int i = 0; i < n; ++i) {
	    	if (i > 0) System.out.print(" ");
	    	System.out.print(ans[i]);
	    }
	    System.out.println();
	 }
}