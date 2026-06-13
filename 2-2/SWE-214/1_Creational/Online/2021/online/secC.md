C1: CSE 214

Online on Creational Pattern
Time: 25 minutes

In an e-commerce application, different payment methods are accepted (e.g., Credit card,
PayPal, and Cryptocurrency like Bitcoin). As the business expands, new payment methods
may be introduced and existing ones may undergo changes. The system should be designed to
accommodate these changes without modifying the existing codebase.
You have to implement the payment interface where a user can choose their preferred method
of payment and pay using that method. The classes that represent the payment methods will
contain a function to process the payment. A message ensuring successful payment will be
shown on the screen.

This problem describes the **Factory Method Pattern**.

**Why?**
The requirement *"system should be designed to accommodate these changes without modifying the existing codebase"* points directly to the **Open/Closed Principle**.

* A **Simple Factory** (with a `switch` statement) would require you to modify the factory code every time you add a new payment method (violating the principle).
* The **Factory Method Pattern** (using subclassed factories) allows you to add a new `CryptoFactory` later without touching the `CreditCardFactory` or the client logic.

Here is the solution:

### 1. The Product Interface

This defines the common behavior for all payment types.

```java
public interface Payment {
    void processPayment(double amount);
}

```

### 2. Concrete Products

The specific implementations of the payment methods.

```java
// Credit Card Implementation
public class CreditCardPayment implements Payment {
    @Override
    public void processPayment(double amount) {
        System.out.println("Success! Payment of $" + amount + " processed via Credit Card.");
    }
}

// PayPal Implementation
public class PayPalPayment implements Payment {
    @Override
    public void processPayment(double amount) {
        System.out.println("Success! Payment of $" + amount + " processed via PayPal.");
    }
}

// Bitcoin Implementation
public class BitcoinPayment implements Payment {
    @Override
    public void processPayment(double amount) {
        System.out.println("Success! Payment of $" + amount + " processed via Bitcoin (Crypto).");
    }
}

```

### 3. The Creator (Abstract Factory)

This interface declares the factory method. It doesn't know *which* payment method will be created, it just guarantees that a payment object will be returned.

```java
// The Creator Interface
public abstract class PaymentFactory {
    // The Factory Method
    public abstract Payment createPaymentMethod();

    // Optional: Shared logic (Template method)
    public void makePayment(double amount) {
        Payment payment = createPaymentMethod();
        payment.processPayment(amount);
    }
}

```

### 4. Concrete Creators

Each payment method has its own factory. If you add a new payment method later, you just create a new factory class for it (no existing code changes).

```java
public class CreditCardFactory extends PaymentFactory {
    @Override
    public Payment createPaymentMethod() {
        return new CreditCardPayment();
    }
}

public class PayPalFactory extends PaymentFactory {
    @Override
    public Payment createPaymentMethod() {
        return new PayPalPayment();
    }
}

public class BitcoinFactory extends PaymentFactory {
    @Override
    public Payment createPaymentMethod() {
        return new BitcoinPayment();
    }
}

```

### 5. Client Code (Main)

The client selects a factory, and the system handles the rest.

```java
import java.util.Scanner;

public class ECommerceApp {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        PaymentFactory factory = null;
        
        System.out.println("Select Payment Method:");
        System.out.println("1. Credit Card");
        System.out.println("2. PayPal");
        System.out.println("3. Bitcoin");
        
        int choice = scanner.nextInt();

        // The decision of WHICH factory to use happens once (Configuration)
        if (choice == 1) {
            factory = new CreditCardFactory();
        } else if (choice == 2) {
            factory = new PayPalFactory();
        } else if (choice == 3) {
            factory = new BitcoinFactory();
        } else {
            System.out.println("Invalid selection.");
            return;
        }

        // The rest of the application code doesn't care what specific class works underneath.
        // It just calls the abstract makePayment (or createPaymentMethod).
        System.out.print("Enter amount to pay: ");
        double amount = scanner.nextDouble();
        
        factory.makePayment(amount);
    }
}

```


C2: CSE 214

Online on Creational Pattern
Time: 25 minutes

You are designing a system to generate documents in different styles. The system needs to
support the creation of letters and resumes. The document creator you are implementing has
two modes: one for professional and formal use and the other for informal usage.
The client can select its preferred mode. After that, they can create letters or resumes from that
mode with their preferred style (formal/informal). The classes that represent document creators
must have functions that return objects of letters or resumes appropriately.



This problem is a classic example of the **Abstract Factory Pattern**.

**Why?**
The Abstract Factory pattern is used when you have **families of related products**. Here, you have two families:

1. **Professional Family**: Contains `FormalLetter` and `FormalResume`.
2. **Informal Family**: Contains `CasualLetter` and `CasualResume`.

You need a factory (the "mode") that ensures if you pick Professional, *both* your letter and resume come out Formal.

Here is the complete solution:

### 1. Abstract Products

Define the interfaces for the two types of documents the system can produce.

```java
// Interface for all Letters
interface Letter {
    void render();
}

// Interface for all Resumes
interface Resume {
    void render();
}

```

### 2. Concrete Products

Implement the specific versions (Formal vs. Informal) for each product type.

```java
// --- Professional Family ---
class FormalLetter implements Letter {
    @Override
    public void render() {
        System.out.println("Printing Formal Letter: 'To Whom It May Concern...' [Standard Font]");
    }
}

class FormalResume implements Resume {
    @Override
    public void render() {
        System.out.println("Printing Formal Resume: Chronological, plain text, professional layout.");
    }
}

// --- Informal Family ---
class CasualLetter implements Letter {
    @Override
    public void render() {
        System.out.println("Printing Casual Letter: 'Hey there!' [Handwritten Font]");
    }
}

class CasualResume implements Resume {
    @Override
    public void render() {
        System.out.println("Printing Casual Resume: Creative layout, colorful, skills-focused.");
    }
}

```

### 3. Abstract Factory

This interface defines the "Document Creator" capabilities. It must be able to create both a letter and a resume.

```java
public interface DocumentFactory {
    Letter createLetter();
    Resume createResume();
}

```

### 4. Concrete Factories

These correspond to the "Modes" mentioned in the problem. They group the correct family members together.

```java
// Factory for Professional Mode
class ProfessionalFactory implements DocumentFactory {
    @Override
    public Letter createLetter() {
        return new FormalLetter();
    }

    @Override
    public Resume createResume() {
        return new FormalResume();
    }
}

// Factory for Informal Mode
class InformalFactory implements DocumentFactory {
    @Override
    public Letter createLetter() {
        return new CasualLetter();
    }

    @Override
    public Resume createResume() {
        return new CasualResume();
    }
}

```

### 5. Client Code (Main)

The client selects a mode, and the application uses the abstract interfaces to generate the documents.

```java
import java.util.Scanner;

public class DocumentGenerator {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        DocumentFactory factory;

        System.out.println("Select Document Mode:");
        System.out.println("1. Professional (Formal)");
        System.out.println("2. Informal (Casual)");
        int choice = scanner.nextInt();

        // 1. Determine which factory (Mode) to use
        if (choice == 1) {
            factory = new ProfessionalFactory();
        } else {
            factory = new InformalFactory();
        }

        System.out.println("\n--- Generating User Documents ---");

        // 2. Create products using the factory. 
        // Notice the client code doesn't know if it's Formal or Casual, just that it's a Letter/Resume.
        Letter letter = factory.createLetter();
        Resume resume = factory.createResume();

        letter.render();
        resume.render();
    }
}

```