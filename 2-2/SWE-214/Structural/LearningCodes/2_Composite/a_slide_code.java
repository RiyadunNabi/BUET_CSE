// File Structure:
//     Component    : MenuComponent (Abstract Base)
//     Leaf         : MenuItem (The food)
//     Composite    : Menu (The container)
//     Main         : MenuTestDrive


import java.util.ArrayList;
import java.util.List;

// =========================
// 1. The Component (Abstract Base)
// =========================

abstract class MenuComponent {
    // We throw exceptions by default because some methods 
    // (like adding a child) don't make sense for a Leaf (MenuItem).
    
    public void add(MenuComponent menuComponent) {
        throw new UnsupportedOperationException();
    }
    public void remove(MenuComponent menuComponent) {
        throw new UnsupportedOperationException();
    }
    public MenuComponent getChild(int i) {
        throw new UnsupportedOperationException();
    }
    
    public String getName() {
        throw new UnsupportedOperationException();
    }
    public String getDescription() {
        throw new UnsupportedOperationException();
    }
    
    public double getPrice() {
        throw new UnsupportedOperationException();
    }
    public void print() {
        throw new UnsupportedOperationException();
    }
}

// =========================
// 2. The Leaf (MenuItem)
// =========================

class MenuItem extends MenuComponent {
    String name;
    String description;
    boolean vegetarian;
    double price;

    public MenuItem(String name, String description, boolean vegetarian, double price) {
        this.name = name;
        this.description = description;
        this.vegetarian = vegetarian;
        this.price = price;
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public String getDescription() {
        return description;
    }

    @Override
    public double getPrice() {
        return price;
    }

    @Override
    public void print() {
        System.out.print("  " + getName());
        if (vegetarian) {
            System.out.print("(v)");
        }
        System.out.println(", " + getPrice());
        System.out.println("     -- " + getDescription());
    }
}

// =========================
// 3. The Composite (Menu)
// =========================

class Menu extends MenuComponent {
    // A Menu can hold MenuItems OR other Menus!
    // We just call them 'MenuComponent' to treat them the same.
    List<MenuComponent> menuComponents = new ArrayList<>();
    String name;
    String description;

    public Menu(String name, String description) {
        this.name = name;
        this.description = description;
    }

    @Override
    public void add(MenuComponent menuComponent) {
        menuComponents.add(menuComponent);
    }

    @Override
    public void remove(MenuComponent menuComponent) {
        menuComponents.remove(menuComponent);
    }

    @Override
    public MenuComponent getChild(int i) {
        return menuComponents.get(i);
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public String getDescription() {
        return description;
    }

    @Override
    public void print() {
        System.out.print("\n" + getName());
        System.out.println(", " + getDescription());
        System.out.println("---------------------");

        // RECURSION MAGIC:
        // We iterate through the list. We don't care if it's a Menu or an Item.
        // We just call print() on it.
        for (MenuComponent menuComponent : menuComponents) {
            menuComponent.print();
        }
    }
}

// =========================
// 4. Main Driver Class (The Client)
// =========================

public class a_slide_code {
    public static void main(String[] args) {
        // 1. Create the main menus
        MenuComponent pancakeHouseMenu = new Menu("PANCAKE HOUSE MENU", "Breakfast");
        MenuComponent dinerMenu = new Menu("DINER MENU", "Lunch");
        MenuComponent cafeMenu = new Menu("CAFE MENU", "Dinner");
        
        // 2. Create a sub-menu (Dessert)
        MenuComponent dessertMenu = new Menu("DESSERT MENU", "Dessert of course!");

        // 3. Create the Top-Level Menu that holds everything
        MenuComponent allMenus = new Menu("ALL MENUS", "All menus combined");

        // 4. Build the Tree
        allMenus.add(pancakeHouseMenu);
        allMenus.add(dinerMenu);
        allMenus.add(cafeMenu);

        // Add items to Pancake House
        pancakeHouseMenu.add(new MenuItem(
            "K&B's Pancake Breakfast", 
            "Pancakes with scrambled eggs", 
            true, 
            2.99));

        // Add items to Diner
        dinerMenu.add(new MenuItem(
            "Vegetarian BLT", 
            "(Fakin') Bacon with lettuce & tomato", 
            true, 
            2.99));
        
        // Add the sub-menu to the Diner menu
        dinerMenu.add(dessertMenu);

        // Add items to the Dessert sub-menu
        dessertMenu.add(new MenuItem(
            "Apple Pie", 
            "Apple pie with flakey crust", 
            true, 
            1.59));

        // 5. The Moment of Truth
        // We print the ENTIRE tree with one call.
        // Client doesn't need to know about loops or recursion.
        allMenus.print();
    }
}