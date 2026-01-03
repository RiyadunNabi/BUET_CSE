secA:
CSE 214

Online on Creational Pattern
Time: 30 minutes

You are developing a system to build meal plans for a restaurant. There are two kinds of
meals available for now. Each meal has a starter, main dish and a dessert. A Bengali
meal contains vegetable, chicken curry and sweet curd. A Chinese meal contains soup,
Peking Duck and Pudding.
After the user chooses his preferred meal, you have to create the meal with all three
courses using appropriate design pattern. For this task, you don’t need to create
classes for each of the courses and can use strings for demonstrating your
design. You must create a class that represents the final meal with all its courses.
-- 
--builder 
This problem is a classic scenario for the **Builder Pattern**.

While you suspected Factory or Abstract Factory, the **Builder Pattern** is actually the most appropriate choice here.

**Why?**

* **Factory/Abstract Factory** is used when you want to create a *family of related objects* (e.g., a UI toolkit with Buttons and Checkboxes that look the same), but it doesn't handle the *step-by-step construction* logic well.
* **Builder Pattern** is specifically designed for creating **complex objects** (like a `Meal`) that need to be assembled in specific **steps** (Starter -> Main -> Dessert). It separates the *construction process* (Director) from the *specific representation* (Bengali vs. Chinese).

Here is the complete solution using the Builder Pattern.

### 1. The Product (The Final Object)

This is the class that represents the final meal with all its courses.

```java
import java.util.ArrayList;
import java.util.List;

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

```

### 2. The Abstract Builder

This defines the steps required to create a meal.

```java
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

```

### 3. Concrete Builders

These classes implement the specific steps for each type of meal (Bengali vs. Chinese).

**Bengali Meal Builder**

```java
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

```

**Chinese Meal Builder**

```java
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

```

### 4. The Director

This class controls the construction flow. It knows *how* to build a meal (the order of steps) but doesn't know *what* specific food is being put in.

```java
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

```

### 5. Client Code (Main)

Simulating the user choosing a preferred meal.

```java
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

```
but do this using factory

Since you need to use a **Factory Pattern** (specifically **Factory Method**), we will treat "Bengali Meal" and "Chinese Meal" as two specific configurations of a `Meal` that need to be created.

In this approach, the **Factory** is responsible for assembling the specific combination of Strings (courses) into the `Meal` object.

### 1. The Product (The Final Object)

This class represents the final meal with all its courses.

```java
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

```

### 2. The Creator (Abstract Factory)

This defines the contract. Any factory that claims to make a meal must implement this method.

```java
public abstract class MealFactory {
    // The Factory Method
    public abstract Meal createMeal();
}

```

### 3. Concrete Creators

These classes contain the specific "recipes" (logic) for creating the Bengali and Chinese variants using Strings.

**Bengali Meal Factory**

```java
public class BengaliMealFactory extends MealFactory {
    @Override
    public Meal createMeal() {
        // Encapsulating the logic for Bengali ingredients here
        return new Meal("Vegetable", "Chicken Curry", "Sweet Curd");
    }
}

```

**Chinese Meal Factory**

```java
public class ChineseMealFactory extends MealFactory {
    @Override
    public Meal createMeal() {
        // Encapsulating the logic for Chinese ingredients here
        return new Meal("Soup", "Peking Duck", "Pudding");
    }
}

```

### 4. Client Code (Main)

The client code (Main) works with the factories to get the meals. It doesn't need to know the specific strings (like "Peking Duck"), it just asks the factory for a meal.

```java
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        MealFactory factory = null;

        System.out.println("Select Meal Type: (1) Bengali, (2) Chinese");
        int choice = scanner.nextInt();

        // 1. Decide which Factory to use
        if (choice == 1) {
            factory = new BengaliMealFactory();
        } else if (choice == 2) {
            factory = new ChineseMealFactory();
        } else {
            System.out.println("Invalid choice");
            return;
        }

        // 2. Use the factory to create the Product
        // Note: The client doesn't need to know the ingredients, only the factory does.
        Meal myMeal = factory.createMeal();
        
        System.out.println("Meal Prepared Successfully!");
        myMeal.showMealDetails();
    }
}

```

### Why this fits the requirement

* **"Create a class that represents the final meal":** The `Meal` class handles this.
* **"Use strings for demonstrating":** The `Meal` class uses Strings for fields, and the Concrete Factories inject these specific strings (e.g., "Sweet Curd").
* **"Appropriate design pattern":** The **Factory Method** encapsulates the creation logic. The Client doesn't manually `setStarter` or `setMainDish`; it simply asks the specific factory to `createMeal()`, and the factory handles the configuration.