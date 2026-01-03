public class ChineseMealBuilder extends MealBuilder {
    @Override
    public void buildStarter() {
        meal.setStarter("Soup");
    }

    @Override
    public void buildMainDish() {
        meal.setMainDish("Peking Duck");
    }

    @Override
    public void buildDessert() {
        meal.setDessert("Pudding");
    }
}