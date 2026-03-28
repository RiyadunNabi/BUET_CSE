Here you go Riyad:

---

|Section | Question | Pattern |
|---|---|---|
|A1| Payment system (Credit Card, BKash, Bitcoin) | **Strategy** |
|A2| Bank notification system (Email, SMS, App) | **Strategy** |
|C1| Stock price tracker | **Observer** |
|C2| Food delivery order status | **State** |
|B| Traffic light system | **State** |

---

## Q1 — Payment System (Strategy)

```java
// ─── Strategy Interface ───────────────────────────────────────────────────────

interface PaymentStrategy {
    void pay(double amount);
}

// ─── Concrete Strategies ──────────────────────────────────────────────────────

class CreditCardPayment implements PaymentStrategy {
    public void pay(double amount) {
        System.out.println("Paid " + amount + " via Credit Card.");
    }
}

class BkashPayment implements PaymentStrategy {
    public void pay(double amount) {
        System.out.println("Paid " + amount + " via BKash.");
    }
}

class BitcoinPayment implements PaymentStrategy {
    public void pay(double amount) {
        System.out.println("Paid " + amount + " via Bitcoin.");
    }
}

// ─── Context ──────────────────────────────────────────────────────────────────

class Checkout {
    private PaymentStrategy strategy;

    public void setPaymentMethod(PaymentStrategy strategy) {
        this.strategy = strategy;
    }

    public void processPayment(double amount) {
        strategy.pay(amount);
    }
}

// ─── Main ─────────────────────────────────────────────────────────────────────

public class PaymentSystem {
    public static void main(String[] args) {
        Checkout checkout = new Checkout();

        checkout.setPaymentMethod(new CreditCardPayment());
        checkout.processPayment(500.0);

        checkout.setPaymentMethod(new BkashPayment());
        checkout.processPayment(300.0);

        checkout.setPaymentMethod(new BitcoinPayment());
        checkout.processPayment(1000.0);
    }
}
```

**Output:**
```
Paid 500.0 via Credit Card.
Paid 300.0 via BKash.
Paid 1000.0 via Bitcoin.
```

---

## Q2 — Bank Notification System (Strategy)

```java
// ─── Strategy Interface ───────────────────────────────────────────────────────

interface NotificationChannel {
    void send(String message);
}

// ─── Concrete Strategies ──────────────────────────────────────────────────────

class EmailNotification implements NotificationChannel {
    public void send(String message) {
        System.out.println("Email: " + message);
    }
}

class SMSNotification implements NotificationChannel {
    public void send(String message) {
        System.out.println("SMS: " + message);
    }
}

class AppNotification implements NotificationChannel {
    public void send(String message) {
        System.out.println("App: " + message);
    }
}

// ─── Context ──────────────────────────────────────────────────────────────────

class BankNotifier {
    private NotificationChannel channel;

    public void setChannel(NotificationChannel channel) {
        this.channel = channel;
    }

    public void notify(String message) {
        channel.send(message);
    }
}

// ─── Main ─────────────────────────────────────────────────────────────────────

public class NotificationSystem {
    public static void main(String[] args) {
        BankNotifier notifier = new BankNotifier();

        notifier.setChannel(new EmailNotification());
        notifier.notify("Transaction of $500 completed.");

        notifier.setChannel(new SMSNotification());
        notifier.notify("Low balance warning: $50 remaining.");

        notifier.setChannel(new AppNotification());
        notifier.notify("Promotional offer: 10% cashback!");
    }
}
```

**Output:**
```
Email: Transaction of $500 completed.
SMS: Low balance warning: $50 remaining.
App: Promotional offer: 10% cashback!
```

---

## Q3 — Stock Price Tracker (Observer)

```java
import java.util.ArrayList;
import java.util.List;

// ─── Observer Interface ───────────────────────────────────────────────────────

interface Observer {
    void update(String stockName, double price);
}

// ─── Subject ──────────────────────────────────────────────────────────────────

class Stock {
    private List<Observer> observers = new ArrayList<>();
    private String name;
    private double price;

    Stock(String name, double price) {
        this.name  = name;
        this.price = price;
    }

    public void addObserver(Observer o)    { observers.add(o); }
    public void removeObserver(Observer o) { observers.remove(o); }

    public void setPrice(double price) {
        this.price = price;
        for (Observer o : observers)
            o.update(name, price);
    }
}

// ─── Concrete Observer ────────────────────────────────────────────────────────

class User implements Observer {
    private String name;

    User(String name) {
        this.name = name;
    }

    public void update(String stockName, double price) {
        System.out.println(name + " has been notified: The price of "
                + stockName + " is now " + price);
    }
}

// ─── Main ─────────────────────────────────────────────────────────────────────

public class StockTracker {
    public static void main(String[] args) {
        Stock googleStock = new Stock("Google", 1500);
        Stock appleStock  = new Stock("Apple", 1200);

        User alice = new User("Alice");
        User bob   = new User("Bob");

        googleStock.addObserver(alice);
        googleStock.addObserver(bob);
        appleStock.addObserver(alice);

        System.out.println("Updating Google stock price...");
        googleStock.setPrice(1550);

        System.out.println("\nUpdating Apple stock price...");
        appleStock.setPrice(1250);

        googleStock.removeObserver(alice);

        System.out.println("\nUpdating Google stock price again...");
        googleStock.setPrice(1600);
    }
}
```

**Output:**
```
Updating Google stock price...
Alice has been notified: The price of Google is now 1550.0
Bob has been notified: The price of Google is now 1550.0

Updating Apple stock price...
Alice has been notified: The price of Apple is now 1250.0

Updating Google stock price again...
Bob has been notified: The price of Google is now 1600.0
```

---

## Q4 — Food Delivery Order Status (State)

```java
// ─── State Interface ──────────────────────────────────────────────────────────

interface State {
    void next(Order order);
    void cancel(Order order);
}

// ─── Context ──────────────────────────────────────────────────────────────────

class Order {
    private State state;

    Order() {
        this.state = new PlacedState();
        System.out.println("Order created → PLACED.");
    }

    public void setState(State s) { this.state = s; }
    public void next()            { state.next(this);   }
    public void cancel()          { state.cancel(this); }
}

// ─── Concrete States ──────────────────────────────────────────────────────────

class PlacedState implements State {
    public void next(Order order) {
        System.out.println("PLACED → CONFIRMED.");
        order.setState(new ConfirmedState());
    }

    public void cancel(Order order) {
        System.out.println("PLACED → CANCELLED.");
        order.setState(new CancelledState());
    }
}

class ConfirmedState implements State {
    public void next(Order order) {
        System.out.println("CONFIRMED → SHIPPED.");
        order.setState(new ShippedState());
    }

    public void cancel(Order order) {
        System.out.println("CONFIRMED → CANCELLED.");
        order.setState(new CancelledState());
    }
}

class ShippedState implements State {
    public void next(Order order) {
        System.out.println("SHIPPED → DELIVERED.");
        order.setState(new DeliveredState());
    }

    public void cancel(Order order) {
        System.out.println("Cannot cancel — order already SHIPPED.");
    }
}

class DeliveredState implements State {
    public void next(Order order) {
        System.out.println("Order already DELIVERED.");
    }

    public void cancel(Order order) {
        System.out.println("Cannot cancel — order already DELIVERED.");
    }
}

class CancelledState implements State {
    public void next(Order order) {
        System.out.println("Cannot proceed — order is CANCELLED.");
    }

    public void cancel(Order order) {
        System.out.println("Order already CANCELLED.");
    }
}

// ─── Main ─────────────────────────────────────────────────────────────────────

public class FoodDelivery {
    public static void main(String[] args) {
        Order order = new Order();

        System.out.println("\n--- Normal flow ---");
        order.next();
        order.next();
        order.next();

        System.out.println("\n--- Try to cancel after shipping ---");
        order.cancel();

        System.out.println("\n--- New order, cancelled early ---");
        Order order2 = new Order();
        order2.next();
        order2.cancel();
    }
}
```

**Output:**
```
Order created → PLACED.

--- Normal flow ---
PLACED → CONFIRMED.
CONFIRMED → SHIPPED.
SHIPPED → DELIVERED.

--- Try to cancel after shipping ---
Cannot cancel — order already SHIPPED.

--- New order, cancelled early ---
Order created → PLACED.
PLACED → CONFIRMED.
CONFIRMED → CANCELLED.
```

---

## Q5 — Traffic Light System (State)

```java
// ─── State Interface ──────────────────────────────────────────────────────────

interface State {
    void handle(TrafficLight light) throws InterruptedException;
}

// ─── Context ──────────────────────────────────────────────────────────────────

class TrafficLight {
    private State state;

    TrafficLight() {
        state = new RedState();
    }

    public void setState(State s) { this.state = s; }

    public void run() throws InterruptedException {
        while (true) {
            state.handle(this);
        }
    }
}

// ─── Concrete States ──────────────────────────────────────────────────────────

class RedState implements State {
    public void handle(TrafficLight light) throws InterruptedException {
        System.out.println("RED    → Stop!  (5 seconds)");
        Thread.sleep(5000);
        light.setState(new YellowState());
    }
}

class YellowState implements State {
    public void handle(TrafficLight light) throws InterruptedException {
        System.out.println("YELLOW → Wait!  (2 seconds)");
        Thread.sleep(2000);
        light.setState(new GreenState());
    }
}

class GreenState implements State {
    public void handle(TrafficLight light) throws InterruptedException {
        System.out.println("GREEN  → Go!    (10 seconds)");
        Thread.sleep(10000);
        light.setState(new RedState());
    }
}

// ─── Main ─────────────────────────────────────────────────────────────────────

public class TrafficLightSystem {
    public static void main(String[] args) throws InterruptedException {
        TrafficLight light = new TrafficLight();
        light.run();
    }
}
```

**Output:**
```
RED    → Stop!  (5 seconds)
YELLOW → Wait!  (2 seconds)
GREEN  → Go!    (10 seconds)
RED    → Stop!  (5 seconds)
...
```

---

All the best on your online Riyad! 🎯