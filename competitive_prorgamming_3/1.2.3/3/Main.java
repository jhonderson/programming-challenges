import java.time.LocalDate;

public class Main {
    private static void printWeekDay(LocalDate localDate) {
        System.out.println(localDate.getDayOfWeek());
    }

    public static void main(String args[]) {
        LocalDate date = LocalDate.now();
        printWeekDay(date);
        date = LocalDate.of(2010, 8, 9);
        printWeekDay(date);
        date = LocalDate.of(1991, 6, 14);
        printWeekDay(date);
    }
}