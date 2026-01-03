public class RestaurantDirector {
    private MealBuilder mealBuilder;

    // Set the specific builder (Bengali or Chinese)
    public void setMealBuilder(MealBuilder mealBuilder) {
        this.mealBuilder = mealBuilder;
    }

    public Meal getMeal() {
        return mealBuilder.getMeal();
    }

    // The algorithm to build a meal
    public void constructMeal() {
        mealBuilder.createNewMeal();
        mealBuilder.buildStarter();
        mealBuilder.buildMainDish();
        mealBuilder.buildDessert();
    }
}