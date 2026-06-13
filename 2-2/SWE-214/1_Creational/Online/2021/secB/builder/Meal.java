
public class Meal {
    private String starter;
    private String mainDish;
    private String dessert;

    public void setStarter(String starter) {
        this.starter = starter;
    }

    public void setMainDish(String mainDish) {
        this.mainDish = mainDish;
    }

    public void setDessert(String dessert) {
        this.dessert = dessert;
    }

    public void showMealDetails() {
        System.out.println("Meal Courses:");
        System.out.println(" - Starter: " + starter);
        System.out.println(" - Main Dish: " + mainDish);
        System.out.println(" - Dessert: " + dessert);
        System.out.println("-------------------------");
    }
}