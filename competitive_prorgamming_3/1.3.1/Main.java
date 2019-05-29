import java.util.Scanner;

public class Main {
    private static void readInputWhenNumberOfLinesIsSpecified() {
        Scanner scanner = new Scanner(System.in);
        int numberOfLines = scanner.nextInt();
        while(numberOfLines-- > 0) {
            int a = scanner.nextInt();
            int b = scanner.nextInt();
            System.out.println(a + b);
        }
    }

    private static void readInputWhenAnSpecialFlagForStopReadingIsWriten() {
        Scanner scanner = new Scanner(System.in);
        int a, b;
        a = scanner.nextInt();
        b = scanner.nextInt();
        while(a != 0 || b != 0) {
            System.out.println(a + b);
            a = scanner.nextInt();
            b = scanner.nextInt();
        }
    }

    private static void readInputUntilEndOfLine() {
        Scanner scanner = new Scanner(System.in);
        while(scanner.hasNextLine()) {
            int a = scanner.nextInt();
            int b = scanner.nextInt();
            System.out.println(a + b);
        }
    }

    private static void readInputUntilEndOfLinePrintingCaseNumber() {
        Scanner scanner = new Scanner(System.in);
        int caseNumber = 1;
        while(scanner.hasNext()) {
            int a = scanner.nextInt();
            int b = scanner.nextInt();
            System.out.printf("Case %d: %d\n\n", caseNumber++, a + b);
        }
    }

    private static void readInputUntilEndOfLinePrintingCaseNumberWithoutExtraLine() {
        Scanner scanner = new Scanner(System.in);
        int caseNumber = 1;
        while(scanner.hasNext()) {
            if (caseNumber > 1)
                System.out.println();
            int a = scanner.nextInt();
            int b = scanner.nextInt();
            System.out.printf("Case %d: %d\n", caseNumber++, a + b);
        }
    }

    private static void readInputUntilEndOfLineWithKnownNumOfSumands() {
        Scanner scanner = new Scanner(System.in);
        int numberOfSummands;
        while(scanner.hasNext()) {
            numberOfSummands = scanner.nextInt();
            int sum = 0;
            while(numberOfSummands-- > 0) {
                sum += scanner.nextInt();
            }
            System.out.println(sum);
        }
    }

    private static void readInputUntilEndOfLineWithUnknownNumSumands() {
        Scanner scanner = new Scanner(System.in);
        while(scanner.hasNext()) {
            String line = scanner.nextLine();
            int sum = 0;
            String[] numbers = line.split("\\s+");
            for(String numberAsStr : numbers) {
                sum += Integer.parseInt(numberAsStr);
            }
            System.out.println(sum);
        }
    }

    public static void main(String args[]) {
        readInputUntilEndOfLineWithUnknownNumSumands();
    }
}