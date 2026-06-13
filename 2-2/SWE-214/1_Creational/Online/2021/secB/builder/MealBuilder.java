public abstract class MealBuilder {
    protected Meal meal;

    public void createNewMeal() {
        meal = new Meal();
    }

    public Meal getMeal() {
        return meal;
    }

    // Steps to build the meal
    public abstract void buildStarter();
    public abstract void buildMainDish();
    public abstract void buildDessert();
}