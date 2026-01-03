public class Main {
    public static void main(String[] args) {
        RestaurantDirector waiter = new RestaurantDirector();
        
        // 1. User wants a Bengali Meal
        MealBuilder bengaliBuilder = new BengaliMealBuilder();
        
        waiter.setMealBuilder(bengaliBuilder);
        waiter.constructMeal(); // The waiter builds the meal step-by-step
        Meal bengaliMeal = waiter.getMeal();
        
        System.out.println("Ordered: Bengali Meal");
        bengaliMeal.showMealDetails();

        // 2. User wants a Chinese Meal
        MealBuilder chineseBuilder = new ChineseMealBuilder();
        
        waiter.setMealBuilder(chineseBuilder);
        waiter.constructMeal();
        Meal chineseMeal = waiter.getMeal();
        
        System.out.println("Ordered: Chinese Meal");
        chineseMeal.showMealDetails();
    }
}