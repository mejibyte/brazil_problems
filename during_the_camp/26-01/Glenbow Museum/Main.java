import java.math.*;
import java.util.*;
import java.io.*;

public class Main {
	public static void main(String[] args) throws IOException {
		final int MAXN = 1005;
		BigInteger dp[][][] = new BigInteger[MAXN][MAXN][2];
		for (int i = 0; i < MAXN; ++i){
			for (int j = 0; j < MAXN; ++j){
				dp[i][j][0] = BigInteger.ZERO;
				dp[i][j][1] = BigInteger.ZERO;
			}
		}
	    dp[1][1][0] = BigInteger.ONE;
	    for (int len = 1; len + 1 < MAXN; ++len) {
	    	for (int r = 0; r < MAXN; ++r) {
	    		
	    		if (r + 1 < MAXN) {
	    			dp[len + 1][r + 1][0] = dp[len + 1][r + 1][0].add( dp[len][r][0] );
	    			dp[len + 1][r + 1][0] = dp[len + 1][r + 1][0].add( dp[len][r][1] );	    			
	    		}
	    		
	    		dp[len + 1][r][1] = dp[len + 1][r][1].add( dp[len][r][0] );
	    	}
	    }
	    
	    
//	    for (int len = 55; len < MAXN; ++len) {
//	    	for (int r = 0; r < MAXN; ++r) {
//	    		for (int p = 0; p < 2; ++p) {
//	    			int o = len - r;
//		    		if (o > r) {
//		    			if (dp[len][r][p].compareTo(BigInteger.ZERO) > 0) {
//		    				throw new RuntimeException(len + " " + r + " " + p + " = " + dp[len][r][p].toString());
//		    			}
//		    		}
//	    		}
//	    	}
//	    }
	   
	    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
	    PrintStream out = System.out;
	    
	    int run = 1;
	    while (true) {
	    	String s = in.readLine();
	    	if (s == null || s.trim().isEmpty()) break;
	    	out.printf("Case %d: ", run++);
	    	 BigInteger ans = BigInteger.ZERO;
	    	 int len = Integer.parseInt(s);
	         for (int r = 4; r <= len; ++r){
	             int o = len - r;
	             if (r - o == 4) {
	             //printf("r = %d, o = %d -> added %d\n", r, o, int(dp[len][r][false] + dp[len][r][true]));
	            	 ans = ans.add( dp[len][r][0] ).add(  dp[len][r][1].multiply(BigInteger.valueOf(2)) );
	             }
	         }
	         out.println(ans);
	    }
	}
}
