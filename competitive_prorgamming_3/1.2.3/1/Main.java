public class Main {
    private static String OUTPUT_FORMAT = "%7.3f";
    public static void main(String[] args) {
        java.util.Scanner scanner = new java.util.Scanner(System.in);
        Double number;
        while ((number = scanner.nextDouble()) != null)
            System.out.println(String.format(OUTPUT_FORMAT, number));
    }
}