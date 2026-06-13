class FoodItem {
    String name;
    double price;
    String quantity;
    
    public FoodItem(String name, double price, String quantity) {
        this.name = name;
        this.price = price;
        this.quantity = quantity;
    }

    public void displayInfo() {
        System.out.println("--- Food Cart Items --- \nName: " + name + ", Price: " + price + ", Quantity: " + quantity);
    }

    public void applyDiscount(double percentage)
    {
        price=price*(1-percentage*0.01);
    }

    public double getPrice() {
        return price;
    } 
}

class Beverage extends FoodItem
{
    String size;
    boolean hasIce;
    public Beverage(String name, double price, String quantity, String size) {
        super(name, price, quantity);
        hasIce=false;
        this.size=size;
    }

    @Override
    public void displayInfo()
    {
        super.displayInfo();
        System.out.println("Size: "+ size + ", Ice: " + hasIce+ "\n");
    }
    
    public void addIce(boolean ice)
    {
        hasIce=ice;
    }
    
}

class Snack extends FoodItem
{
    boolean isSpicy;

    public Snack(String name, double price, String quantity, boolean isSpicy) {
        super(name, price, quantity);
        this.isSpicy = isSpicy;
    }



    @Override
    public void displayInfo()
    {
        super.displayInfo();
        System.out.println("Spicy: " + isSpicy+"\n");
    }

    public void  toggleSpiciness()
    {
        if(isSpicy)
        {
            isSpicy=false;
        }
        else isSpicy=true;
    }
    
}

class Dessert extends FoodItem
{
    int calories;

    public Dessert(String name, double price, String quantity, int calories) {
        super(name, price, quantity);
        this.calories = calories;
    }

    public void displayInfo()
    {
        super.displayInfo();
        System.out.println("Calories: "+ calories+"\n");
    }

    public void halfServing()
    {
        price=price/2;
        quantity="small";
    }
}

class FoodCart
{
    FoodItem[] items=new FoodItem[10];
    int countItems;

    public void addItem(FoodItem item)
    {
        items[countItems++]=item;
    }

    public void showCart()
    {
        for(int i=0; i<countItems; i++)
        {
            items[i].displayInfo();
        }
    }

    public double calculateTotal()
    {
        double total=0;
        for(int i=0; i<countItems; i++)
        {
            total+=items[i].getPrice();
        }

        return total;
    }
}

// Main Class
public class FoodCartManagementSystem {
    public static void main(String[] args) {
        Beverage soda = new Beverage("Soda", 1.99, "Medium","Medium");
        Snack chips = new Snack("Chips", 2.49,"Medium", true);
        Dessert cake = new Dessert("Chocolate Cake", 4.99,"Medium", 300);

        FoodCart cart = new FoodCart();

        cart.addItem(soda);
        cart.addItem(chips);
        cart.addItem(cake);

        System.out.println("Initial Cart:");
        cart.showCart();

        soda.applyDiscount(10); // 10% off
        cake.applyDiscount(15); // 15% off

        System.out.println("Updated Cart After Discounts:");
        cart.showCart();

        double total = cart.calculateTotal();
        System.out.println("Total Price: $" + total);
    }
}


//Output

// Initial Cart:
// --- Food Cart Items ---
// Name: Soda, Price: $1.99, Quantity: 2
// Size: Medium, Ice: No Ice
// --------------------
// Name: Chips, Price: $2.49, Quantity: 1
// Spicy: Yes
// --------------------
// Name: Chocolate Cake, Price: $4.99, Quantity: 3
// Calories: 300 kcal
// --------------------

// Ice added to Soda
// Spiciness of Chips is now disabled
// Half serving applied to Chocolate Cake

// Updated Cart After Applying Unique Features and Discounts:
// --- Food Cart Items ---
// Name: Soda, Price: $1.79, Quantity: 2
// Size: Medium, Ice: Added
// --------------------
// Name: Chips, Price: $2.49, Quantity: 1
// Spicy: No
// --------------------
// Name: Chocolate Cake, Price: $2.12, Quantity: 1
// Calories: 300 kcal
// --------------------

// Total Price: $8.19