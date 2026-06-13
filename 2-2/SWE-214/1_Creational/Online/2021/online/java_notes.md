Here is your **Emergency Java Syntax Cheat Sheet**. This covers the 20% of Java you need to write 80% of exam code (especially for Design Patterns).

### 1. The Basics (Class Structure)

Every file needs a class. The class name must match the file name.

```java
public class MyClass {
    // 1. Fields (Attributes) - usually private
    private String name;
    private int id;

    // 2. Constructor (Must match class name, no return type)
    public MyClass(String name, int id) {
        this.name = name; // 'this' refers to the current object
        this.id = id;
    }

    // 3. Methods (Behavior)
    public String getName() {
        return this.name;
    }
}

```

### 2. Inheritance & Abstraction (Crucial for Patterns)

This is the bread and butter of Factory, Abstract Factory, and Strategy patterns.

**The Interface (Pure contract, no code body)**

```java
// Define it
interface Animal {
    void makeSound(); // No body!
}

// Implement it
class Dog implements Animal {
    @Override
    public void makeSound() {
        System.out.println("Bark");
    }
}

```

**The Abstract Class (Mix of contract and shared code)**

```java
abstract class Vehicle {
    // Abstract method (Children MUST implement this)
    public abstract void move();

    // Concrete method (Children inherit this logic)
    public void stop() {
        System.out.println("Stopping...");
    }
}

class Car extends Vehicle {
    @Override
    public void move() {
        System.out.println("Driving on road");
    }
}

```

### 3. Collections (Lists & Maps)

You will need these to store lists of observers, items, or strategy maps.

**ArrayList (Dynamic Array)**

```java
import java.util.List;
import java.util.ArrayList;

// Create
List<String> items = new ArrayList<>();

// Add
items.add("Apple");
items.add("Banana");

// Get
String fruit = items.get(0); // Index starts at 0

// Size
int size = items.size();

```

**HashMap (Key-Value Pairs)**

```java
import java.util.Map;
import java.util.HashMap;

// Create
Map<String, Integer> scores = new HashMap<>();

// Put
scores.put("Alice", 95);
scores.put("Bob", 80);

// Get
int score = scores.get("Alice");

// Check if exists
if (scores.containsKey("Bob")) { ... }

```

### 4. Loops (Iterating)

Use the "Enhanced For-Loop" (For-Each) for almost everything. It's shorter and less error-prone.

```java
// Loop through a List
for (String item : items) {
    System.out.println(item);
}

// Standard Loop (if you need index)
for (int i = 0; i < items.size(); i++) {
    System.out.println(items.get(i));
}

```

### 5. Input & Output (Console)

For `Main` class interactions.

```java
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Print
        System.out.println("Enter name:");

        // Read String
        String name = scanner.nextLine();

        // Read Integer
        int age = scanner.nextInt();
        
        // Read Double
        double price = scanner.nextDouble();
    }
}

```

### 6. Static & Final (For Singletons & Constants)

* **`static`**: Belongs to the class, not the object.
* **`final`**: Cannot be changed (constant).

```java
public class Config {
    // Constant
    public static final double PI = 3.14159;

    // Static Method (Call without 'new Config()')
    public static void printLog() {
        System.out.println("Log entry");
    }
}

// Usage:
Config.printLog();

```

### 7. Exception Handling (Try-Catch)

Wrap risky code (like File I/O) in this.

```java
try {
    // Risky code
    int result = 10 / 0;
} catch (Exception e) {
    // Handle error
    System.out.println("Error happened: " + e.getMessage());
}

```

### Exam Syntax Checklist (Don't forget these!)

1. **Semicolons `;**`: At the end of every statement.
2. **Braces `{ }**`: For every class, method, if, loop.
3. **Case Sensitivity**: `String` is not `string`. `System` is not `system`.
4. **Constructor Name**: Must be **exactly** the same as the class name.
5. **`new` keyword**: Required to create objects (e.g., `new Car()`).

---

**Next Step:** Would you like a "Fill in the blank" practice question for one of the patterns (Factory or Abstract Factory) to test if you remember the syntax?