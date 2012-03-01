import java.util.*;
import java.io.*;
import java.math.*;

public class Main {
    public static void main(String[] args) throws Exception {
        System.setIn(new FileInputStream("string.in"));
        System.setOut(new PrintStream("string.out"));
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        OutputWriter out = new OutputWriter(outputStream);
        Task solver = new Task();
        solver.solve(1, in, out);
        out.close();
    }
}

class Task {
    private BigInteger fact(int n) {
        BigInteger ans = BigInteger.ONE;
        for (int i = 2; i <= n; ++i) ans = ans.multiply(BigInteger.valueOf(i));
        return ans;
    }
    
    private BigInteger ways(TreeMap<Character, Integer> freq) {
        int total = 0;
        for (Map.Entry<Character, Integer> entry : freq.entrySet()) {
            total += entry.getValue();
        }
        BigInteger ans = fact(total);
        for (Map.Entry<Character, Integer> entry : freq.entrySet()) {
            ans = ans.divide(fact(entry.getValue()));
        }
        return ans;
    }
    
    public void solve(int testNumber, InputReader in, OutputWriter out) {
        
        TreeMap<Character, Integer> freq = new TreeMap<Character, Integer>();
        for (char c = 'a'; c <= 'z'; ++c) {
            freq.put(c, 0);
        }
        
        String s = in.readString();
        for (int i = 0; i < s.length(); ++i) {
            int value = freq.get(s.charAt(i));
            value++;
            freq.put(s.charAt(i), value);
        }
        
        BigInteger ans = BigInteger.ZERO;
        for (int i = 0; i < s.length(); ++i) {
            
            for (char c = 'a'; c < s.charAt(i); ++c) {
                int value = freq.get(c);
                if (value > 0) {
                    freq.put(c, value - 1);
                    ans = ans.add(ways(freq));
                    freq.put(c, value);
                }
            }
            
            freq.put(s.charAt(i), freq.get(s.charAt(i)) - 1);
        }
        
        ans = ans.add(BigInteger.ONE);
        out.printLine(ans);
    }
}

class InputReader {
    private InputStream stream;
    private byte[] buf = new byte[1024];
    private int curChar;
    private int numChars;

    public InputReader(InputStream stream) {
        this.stream = stream;
    }

    public int read() {
        if (numChars == -1)
            throw new InputMismatchException();
        if (curChar >= numChars) {
            curChar = 0;
            try {
                numChars = stream.read(buf);
            } catch (IOException e) {
                throw new InputMismatchException();
            }
            if (numChars <= 0)
                return -1;
        }
        return buf[curChar++];
    }

    public String readString() {
        int c = read();
        while (isSpaceChar(c))
            c = read();
        StringBuffer res = new StringBuffer();
        do {
            res.appendCodePoint(c);
            c = read();
        }
        while (!isSpaceChar(c));
        return res.toString();
    }

    public static boolean isSpaceChar(int c) {
        return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
    }
}

class OutputWriter {
    private final PrintWriter writer;

    public OutputWriter(OutputStream outputStream) {
        writer = new PrintWriter(outputStream);
    }

    public OutputWriter(Writer writer) {
        this.writer = new PrintWriter(writer);
    }

    public void print(Object...objects) {
        for (int i = 0; i < objects.length; i++) {
            if (i != 0)
                writer.print(' ');
            writer.print(objects[i]);
        }
    }

    public void printLine(Object...objects) {
        print(objects);
        writer.println();
    }

    public void close() {
        writer.close();
    }
}
