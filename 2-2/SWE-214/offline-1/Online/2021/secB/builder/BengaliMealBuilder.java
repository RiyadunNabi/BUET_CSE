public class BengaliMealBuilder extends MealBuilder {
    @Override
    public void buildStarter() {
        meal.setStarter("Vegetable");
    }

    @Override
    public void buildMainDish() {
        meal.setMainDish("Chicken Curry");
    }

    @Override
    public void buildDessert() {
        meal.setDessert("Sweet Curd");
    }
}