import java.util.ArrayList;
import java.util.List;

public class Meal {
    private String starter;
    private String mainDish;
    private String dessert;

    public Meal(String starter, String mainDish, String dessert) {
        this.starter = starter;
        this.mainDish = mainDish;
        this.dessert = dessert;
    }

    public void showMealDetails() {
        System.out.println("Meal Courses:");
        System.out.println(" - Starter:   " + starter);
        System.out.println(" - Main Dish: " + mainDish);
        System.out.println(" - Dessert:   " + dessert);
        System.out.println("-------------------------");
    }
}