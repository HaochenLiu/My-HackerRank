import java.util.*;
import java.math.*;
import javafx.util.Pair;

class Solution {
    static class EmpSortByEmpId implements Comparator<Pair<BigDecimal, String>> {
        public int compare(Pair<BigDecimal, String> x, Pair<BigDecimal, String> y) {
            return y.getKey().compareTo(x.getKey());
        }
    }
    
    public static void main(String []argh) {
        Scanner cin = new Scanner(System.in);
        int T = cin.nextInt();
        
        ArrayList<Pair<BigDecimal, String>> a = new ArrayList<Pair<BigDecimal, String>>();
        for(int i = 0; i < T; i++){
            String s = cin.next();
            a.add(new Pair<BigDecimal, String>(new BigDecimal(s), s));
        }
        
        Collections.sort(a, new EmpSortByEmpId());
        for(int i = 0; i < T; i++) {
            System.out.println(a.get(i).getValue());
        }
    }
}
