import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String sa = sc.next();
        String sb = sc.next();
        BigInteger a = new BigInteger(sa);
        BigInteger b = new BigInteger(sb);
        System.out.println(a.add(b));
        System.out.println(a.multiply(b));
    }
}
