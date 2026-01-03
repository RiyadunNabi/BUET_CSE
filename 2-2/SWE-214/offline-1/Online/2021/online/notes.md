Ok, these was my previous year questions. Tomorrow is my exam, to pass in exam, what to do. I generally forget the syntax or pattern, like there might be many creational ways of doing, even if we only consider abstract factory. Can u give an exact methods those i will cram 


If you are cramming for tomorrow, **stop trying to understand the "why" and start memorizing the "skeleton".**

In university exams, professors look for specific **structures** (interfaces, classes, override annotations). If you write the correct structure, you get 80% of the marks even if the logic inside is simple.

Here are the **4 Golden Templates** you need to memorize. Use these exact variable names and structures, just swap the class names (e.g., change `Product` to `Pizza`).

---

### 1. The Factory Method Pattern

**Cram this when:** The question asks for **one type** of object (e.g., "Documents") but implies there will be **new types added later** (e.g., "PDF, Word, and maybe more later") and mentions "open/closed principle" or "without modifying existing code."

**The Skeleton (Memorize this structure):**

```java
// 1. The Interface (THE WHAT)
interface Product {
    void doStuff();
}

// 2. Concrete Classes (THE VERSIONS)
class ConcreteProductA implements Product {
    public void doStuff() { System.out.println("I am A"); }
}

class ConcreteProductB implements Product {
    public void doStuff() { System.out.println("I am B"); }
}

// 3. The Creator (THE FACTORY - Abstract)
// *** CRITICAL STEP: This abstract method is the "Factory Method" ***
abstract class Creator {
    public abstract Product createProduct(); 

    // Optional: Shared logic
    public void render() {
        Product p = createProduct();
        p.doStuff();
    }
}

// 4. Concrete Creators (THE DECIDERS)
class ConcreteCreatorA extends Creator {
    @Override
    public Product createProduct() { return new ConcreteProductA(); }
}

class ConcreteCreatorB extends Creator {
    @Override
    public Product createProduct() { return new ConcreteProductB(); }
}

```

---

### 2. The Abstract Factory Pattern

**Cram this when:** The question mentions **"Families"**, **"Teams"**, or **"Pairs"** of items that must go together. (e.g., "Light Mode" needs "Light Button" AND "Light Text", or "Mac" needs "Mac Button" AND "Mac Window").

**The Skeleton:**

```java
// 1. Abstract Products (The Parts)
interface Button { void paint(); }
interface Checkbox { void paint(); }

// 2. Concrete Products (Family 1)
class WinButton implements Button { public void paint() { System.out.println("Win Button"); } }
class WinCheckbox implements Checkbox { public void paint() { System.out.println("Win Checkbox"); } }

// 3. Concrete Products (Family 2)
class MacButton implements Button { public void paint() { System.out.println("Mac Button"); } }
class MacCheckbox implements Checkbox { public void paint() { System.out.println("Mac Checkbox"); } }

// 4. Abstract Factory (THE CONTRACT)
// *** CRITICAL: Must have methods for ALL parts ***
interface GUIFactory {
    Button createButton();
    Checkbox createCheckbox();
}

// 5. Concrete Factories (THE FAMILIES)
class WinFactory implements GUIFactory {
    public Button createButton() { return new WinButton(); }
    public Checkbox createCheckbox() { return new WinCheckbox(); }
}

class MacFactory implements GUIFactory {
    public Button createButton() { return new MacButton(); }
    public Checkbox createCheckbox() { return new MacCheckbox(); }
}

```

---

### 3. The Builder Pattern

**Cram this when:** The question asks to create a **"Complex Object"** or mentions **"Steps"** (e.g., "Make a meal with starter, main, dessert" or "Build a house with walls, roof, garage").

**The Skeleton:**

```java
// 1. The Complex Product
class Product {
    String partA, partB;
    public void setPartA(String s) { partA = s; }
    public void setPartB(String s) { partB = s; }
}

// 2. The Builder Abstract Class (THE BLUEPRINT)
abstract class Builder {
    protected Product product = new Product();
    public Product getResult() { return product; }
    
    // The Steps
    public abstract void buildPartA();
    public abstract void buildPartB();
}

// 3. Concrete Builder (THE SPECIFIC RECIPE)
class ConcreteBuilder1 extends Builder {
    public void buildPartA() { product.setPartA("Value A1"); }
    public void buildPartB() { product.setPartB("Value B1"); }
}

// 4. The Director (THE BOSS)
class Director {
    private Builder builder;
    public Director(Builder b) { this.builder = b; }
    
    public void construct() {
        builder.buildPartA();
        builder.buildPartB();
    }
}

```

---

### 4. The Singleton Pattern

**Cram this when:** The question says "Global point of access," "Only one instance," "Database Connection," or "Logger." (This is the easiest points you will ever get).

**The Skeleton:**

```java
class Database {
    // 1. Private Static Instance
    private static Database instance;

    // 2. Private Constructor (CRITICAL: Prevents 'new Database()')
    private Database() {}

    // 3. Public Static Access Method
    public static Database getInstance() {
        if (instance == null) {
            instance = new Database();
        }
        return instance;
    }
    
    public void query(String sql) { System.out.println(sql); }
}

```

---

### How to pass the exam tomorrow (The "Cheat Code"):

1. **Read the Question First:**
* Does it say "Families" or "Related objects"? -> **Abstract Factory**.
* Does it say "Steps" or "Complex construction"? -> **Builder**.
* Does it say "New types added without changing code"? -> **Factory Method**.
* Does it say "One instance"? -> **Singleton**.


2. **Write the Skeleton First:**
* Before you even think about the logic, write the `interface`, the `class`, and the `extends` keywords.
* Swap the names. If the question is about `Pizza`, change `Product` -> `Pizza`, `ConcreteProduct` -> `CheesePizza`, `Creator` -> `PizzaStore`.


3. **Don't Panic about Logic:**
* Inside the methods, just write `System.out.println("...");`. Professors rarely care if you implement complex logic; they check if you **called the factory correctly**.



Good luck. Memorize the 4 skeletons above. If you can write those out from memory, you will pass.










Give full skeleton for abstract factory 

Here is the full, memorizable skeleton for the **Abstract Factory Pattern**.

**Concept:** You are creating **Families** of products (e.g., A "Modern" family and a "Victorian" family). Each family has the same parts (e.g., a Chair and a Sofa), but they look different.

### 1. The Abstract Products (The Parts)

Define what "parts" every family must have.
*(Exam Tip: If the question asks for "Buttons and Windows", these are your two interfaces.)*

```java
// Interface for Part A
interface ProductA {
    void useA();
}

// Interface for Part B
interface ProductB {
    void useB();
}

```

### 2. The Concrete Products (The specific versions)

Create the actual implementations for **Family 1** and **Family 2**.

```java
// --- Family 1 (e.g., Modern) ---
class ConcreteProductA1 implements ProductA {
    public void useA() { System.out.println("Using Part A - Style 1"); }
}

class ConcreteProductB1 implements ProductB {
    public void useB() { System.out.println("Using Part B - Style 1"); }
}

// --- Family 2 (e.g., Vintage) ---
class ConcreteProductA2 implements ProductA {
    public void useA() { System.out.println("Using Part A - Style 2"); }
}

class ConcreteProductB2 implements ProductB {
    public void useB() { System.out.println("Using Part B - Style 2"); }
}

```

### 3. The Abstract Factory (The Contract)

This tells the world: "If you want to be a factory, you MUST be able to create BOTH Part A and Part B."

```java
interface AbstractFactory {
    ProductA createProductA();
    ProductB createProductB();
}

```

### 4. The Concrete Factories (The Assemblers)

These factories ensure that parts from Family 1 never mix with Family 2.

```java
// Factory for Family 1
class ConcreteFactory1 implements AbstractFactory {
    @Override
    public ProductA createProductA() { return new ConcreteProductA1(); }

    @Override
    public ProductB createProductB() { return new ConcreteProductB1(); }
}

// Factory for Family 2
class ConcreteFactory2 implements AbstractFactory {
    @Override
    public ProductA createProductA() { return new ConcreteProductA2(); }

    @Override
    public ProductB createProductB() { return new ConcreteProductB2(); }
}

```

### 5. The Client (The Exam Answer)

This shows you know how to use it. The client **never uses `new**` to create products; it asks the factory.

```java
class ClientApplication {
    private ProductA partA;
    private ProductB partB;

    // The client accepts ANY factory (Polymorphism)
    public ClientApplication(AbstractFactory factory) {
        this.partA = factory.createProductA();
        this.partB = factory.createProductB();
    }

    public void run() {
        partA.useA();
        partB.useB();
    }
}

// Main execution
public class Main {
    public static void main(String[] args) {
        // 1. Choose the factory (this is the only place you specify the family)
        AbstractFactory factory = new ConcreteFactory1(); 
        
        // 2. Pass it to the client
        ClientApplication app = new ClientApplication(factory);
        app.run();
    }
}

```

### ⚡ Cram Sheet for Tomorrow

* **Identify it:** Look for keywords like **"Families"**, **"Styles"**, **"Themes"**, or sets of objects that **"must go together"**.
* **The Check:** Your `AbstractFactory` interface **MUST** have multiple methods (one for each product type, e.g., `createChair()` AND `createSofa()`).
* **The Trick:** If the question asks for "Windows and Buttons" for "Mac and Windows":
* `ProductA` -> `Button`
* `ProductB` -> `Window`
* `ConcreteFactory1` -> `MacFactory`
* `ConcreteFactory2` -> `WinFactory`