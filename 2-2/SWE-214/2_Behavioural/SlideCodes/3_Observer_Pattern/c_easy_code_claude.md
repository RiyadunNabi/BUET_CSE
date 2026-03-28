Great, Riyad! Let's kick off with the **Observer Pattern** — arguably the most important of the bunch since many other patterns build on its ideas.

## Pre-discussion: Observer Pattern

**Core idea:** Imagine a YouTube channel. You (subscriber) don't constantly check if there's a new video — you *subscribe*, and YouTube *notifies* you automatically. That's Observer in a nutshell.

**The problem it solves:** When one object (the *Subject*) changes state, several other objects (the *Observers*) need to react — but the Subject shouldn't be tightly coupled to who those observers are.

**Key roles:**
- `Subject` (a.k.a. Publisher) — holds state, maintains a list of observers, notifies them on change
- `Observer` — an interface with an `update()` method
- `ConcreteObserver` — actual classes that react to notifications

Here's how the pieces connect:**Key rules to remember:**
- Subject holds a `List<Observer>` — it doesn't know *what kind* they are, just that they have `update()`
- Observers register themselves — Subject never creates them
- This achieves **loose coupling**: you can add new observer types without touching the Subject

---

Now here's the full runnable Java code. Everything is in one file:

```java
import java.util.ArrayList;
import java.util.List;

// ─── Step 1: Observer Interface ───────────────────────────────────────────────
interface Observer {
    void update(String eventType, float data);
}

// ─── Step 2: Subject Interface ────────────────────────────────────────────────
interface Subject {
    void registerObserver(Observer o);
    void removeObserver(Observer o);
    void notifyObservers(String eventType);
}

// ─── Step 3: Concrete Subject — WeatherStation ───────────────────────────────
class WeatherStation implements Subject {
    private List<Observer> observers = new ArrayList<>();
    private float temperature;
    private float humidity;

    @Override
    public void registerObserver(Observer o) {
        observers.add(o);
        System.out.println("[Station] Observer registered: " + o.getClass().getSimpleName());
    }

    @Override
    public void removeObserver(Observer o) {
        observers.remove(o);
        System.out.println("[Station] Observer removed: " + o.getClass().getSimpleName());
    }

    @Override
    public void notifyObservers(String eventType) {
        float dataToSend = eventType.equals("TEMPERATURE") ? temperature : humidity;
        for (Observer o : observers) {
            o.update(eventType, dataToSend);
        }
    }

    // These are the "state change" methods that trigger notifications
    public void setTemperature(float temp) {
        System.out.println("\n[Station] Temperature changed to " + temp + "°C");
        this.temperature = temp;
        notifyObservers("TEMPERATURE");
    }

    public void setHumidity(float humidity) {
        System.out.println("\n[Station] Humidity changed to " + humidity + "%");
        this.humidity = humidity;
        notifyObservers("HUMIDITY");
    }
}

// ─── Step 4: Concrete Observers ───────────────────────────────────────────────

class PhoneApp implements Observer {
    private String userName;

    public PhoneApp(String userName) {
        this.userName = userName;
    }

    @Override
    public void update(String eventType, float data) {
        if (eventType.equals("TEMPERATURE")) {
            System.out.println("  [PhoneApp - " + userName + "] 📱 Temp alert: " + data + "°C");
        } else {
            System.out.println("  [PhoneApp - " + userName + "] 📱 Humidity alert: " + data + "%");
        }
    }
}

class Billboard implements Observer {
    private String location;

    public Billboard(String location) {
        this.location = location;
    }

    @Override
    public void update(String eventType, float data) {
        System.out.println("  [Billboard @ " + location + "] 🖥️  Display updated — "
                + eventType + ": " + data);
    }
}

class WeatherLogger implements Observer {
    @Override
    public void update(String eventType, float data) {
        System.out.println("  [Logger] 📝 Logged to DB — " + eventType + " = " + data);
    }
}

// ─── Step 5: Main — Putting it all together ───────────────────────────────────
public class ObserverPatternDemo {

    public static void main(String[] args) {

        // Create the subject
        WeatherStation station = new WeatherStation();

        // Create observers
        PhoneApp alicePhone = new PhoneApp("Alice");
        PhoneApp bobPhone   = new PhoneApp("Bob");
        Billboard dhakaBillboard = new Billboard("Dhaka Central");
        WeatherLogger logger = new WeatherLogger();

        // Register observers
        station.registerObserver(alicePhone);
        station.registerObserver(bobPhone);
        station.registerObserver(dhakaBillboard);
        station.registerObserver(logger);

        // Trigger state changes — all observers get notified automatically
        station.setTemperature(36.5f);
        station.setHumidity(85.0f);

        // Remove one observer mid-way
        System.out.println("\n--- Bob unsubscribes ---");
        station.removeObserver(bobPhone);

        // Now only remaining observers get notified
        station.setTemperature(38.0f);
    }
}
```

**Expected output:**
```
[Station] Observer registered: PhoneApp
[Station] Observer registered: PhoneApp
[Station] Observer registered: Billboard
[Station] Observer registered: WeatherLogger

[Station] Temperature changed to 36.5°C
  [PhoneApp - Alice] 📱 Temp alert: 36.5°C
  [PhoneApp - Bob]   📱 Temp alert: 36.5°C
  [Billboard @ Dhaka Central] 🖥️  Display updated — TEMPERATURE: 36.5
  [Logger] 📝 Logged to DB — TEMPERATURE = 36.5

[Station] Humidity changed to 85.0%
  [PhoneApp - Alice] 📱 Humidity alert: 85.0%
  ...

--- Bob unsubscribes ---
[Station] Observer removed: PhoneApp

[Station] Temperature changed to 38.0°C
  [PhoneApp - Alice] 📱 Temp alert: 38.0°C
  [Billboard @ Dhaka Central] 🖥️  Display updated — TEMPERATURE: 38.0
  [Logger] 📝 Logged to DB — TEMPERATURE = 38.0
```

---

**Quick mental checklist to spot Observer in the wild:**
- Something changes → something else reacts → you need that decoupled? → Observer
- Java's built-in `java.util.Observer` (deprecated) and event listeners in Android/Swing all use this pattern
- It's also the backbone of **React state**, **Redux**, and **RxJava**

Ready to move to **Strategy Pattern** next, Riyad?