import java.math.BigInteger;

public class Main {
    private static String convertNumberToBase(String str, int baseFrom, int baseTo) {
        return new BigInteger(str, baseFrom).toString(baseTo);
    }
    public static void main(String[] args) {
        String str = "FF"; int X = 16, Y = 10, Z = 2;
        System.out.println(convertNumberToBase(str, X, Y));
        System.out.println(convertNumberToBase(str, X, Z));
    }
}
