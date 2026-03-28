# 4. BRIDGE PATTERN

---

## Problem 1 — Remote Control & Devices
Remote controls (BasicRemote, AdvancedRemote) work with different devices (TV, Radio). Bridge separates them.

```java
// Implementor
interface Device {
    void turnOn();
    void turnOff();
    void setVolume(int volume);
    String getStatus();
}

// Concrete Implementors
class TV implements Device {
    private boolean on = false;
    private int volume = 10;
    public void turnOn()  { on = true;  System.out.println("TV: ON"); }
    public void turnOff() { on = false; System.out.println("TV: OFF"); }
    public void setVolume(int v) { volume = v; System.out.println("TV: Volume = " + v); }
    public String getStatus() { return "TV [on=" + on + ", vol=" + volume + "]"; }
}

class Radio implements Device {
    private boolean on = false;
    private int volume = 5;
    public void turnOn()  { on = true;  System.out.println("Radio: ON"); }
    public void turnOff() { on = false; System.out.println("Radio: OFF"); }
    public void setVolume(int v) { volume = v; System.out.println("Radio: Volume = " + v); }
    public String getStatus() { return "Radio [on=" + on + ", vol=" + volume + "]"; }
}

// Abstraction
abstract class Remote {
    protected Device device;
    public Remote(Device device) { this.device = device; }
    public abstract void togglePower();
    public abstract void volumeUp();
    public abstract void volumeDown();
}

// Refined Abstractions
class BasicRemote extends Remote {
    private int currentVolume = 10;
    public BasicRemote(Device d) { super(d); }

    public void togglePower() {
        System.out.println("BasicRemote: Toggle Power");
        device.turnOn();
    }
    public void volumeUp() {
        currentVolume += 5;
        device.setVolume(currentVolume);
    }
    public void volumeDown() {
        currentVolume -= 5;
        device.setVolume(currentVolume);
    }
}

class AdvancedRemote extends Remote {
    private int currentVolume = 10;
    public AdvancedRemote(Device d) { super(d); }

    public void togglePower() {
        System.out.println("AdvancedRemote: Toggle Power");
        device.turnOn();
    }
    public void volumeUp()   { currentVolume += 10; device.setVolume(currentVolume); }
    public void volumeDown() { currentVolume -= 10; device.setVolume(currentVolume); }

    public void mute() {
        System.out.println("AdvancedRemote: MUTE");
        device.setVolume(0);
    }
}

public class RemoteDemo {
    public static void main(String[] args) {
        Remote r1 = new BasicRemote(new TV());
        r1.togglePower();
        r1.volumeUp();
        r1.volumeUp();

        System.out.println();

        AdvancedRemote r2 = new AdvancedRemote(new Radio());
        r2.togglePower();
        r2.volumeUp();
        r2.mute();
    }
}
```
**Output:**
```
BasicRemote: Toggle Power
TV: ON
TV: Volume = 15
TV: Volume = 20

AdvancedRemote: Toggle Power
Radio: ON
Radio: Volume = 20
AdvancedRemote: MUTE
Radio: Volume = 0
```

---

## Problem 2 — Message Sender
Messages (Urgent, Normal) are sent via different channels (Email, SMS, Push). Bridge separates message type from channel.

```java
// Implementor
interface MessageChannel {
    void sendMessage(String title, String body);
}

// Concrete Implementors
class EmailChannel implements MessageChannel {
    public void sendMessage(String title, String body) {
        System.out.println("📧 Email | " + title + ": " + body);
    }
}

class SMSChannel implements MessageChannel {
    public void sendMessage(String title, String body) {
        System.out.println("📱 SMS | " + title + ": " + body);
    }
}

class PushChannel implements MessageChannel {
    public void sendMessage(String title, String body) {
        System.out.println("🔔 Push | " + title + ": " + body);
    }
}

// Abstraction
abstract class Message {
    protected MessageChannel channel;
    protected String content;

    public Message(MessageChannel channel, String content) {
        this.channel = channel; this.content = content;
    }
    public abstract void send();
}

// Refined Abstractions
class UrgentMessage extends Message {
    public UrgentMessage(MessageChannel c, String content) { super(c, content); }
    public void send() {
        channel.sendMessage("🚨 URGENT", content);
    }
}

class NormalMessage extends Message {
    public NormalMessage(MessageChannel c, String content) { super(c, content); }
    public void send() {
        channel.sendMessage("INFO", content);
    }
}

class PromotionalMessage extends Message {
    public PromotionalMessage(MessageChannel c, String content) { super(c, content); }
    public void send() {
        channel.sendMessage("🎉 PROMO", content);
    }
}

public class MessageDemo {
    public static void main(String[] args) {
        Message m1 = new UrgentMessage(new SMSChannel(), "Server is down!");
        Message m2 = new NormalMessage(new EmailChannel(), "Your order is confirmed.");
        Message m3 = new PromotionalMessage(new PushChannel(), "50% off today only!");
        Message m4 = new UrgentMessage(new EmailChannel(), "Security breach detected!");

        m1.send();
        m2.send();
        m3.send();
        m4.send();
    }
}
```
**Output:**
```
📱 SMS | 🚨 URGENT: Server is down!
📧 Email | INFO: Your order is confirmed.
🔔 Push | 🎉 PROMO: 50% off today only!
📧 Email | 🚨 URGENT: Security breach detected!
```

---

## Problem 3 — Vehicle & Engine
Vehicles (Car, Boat) use different engines (Petrol, Electric, Diesel). Bridge separates them.

```java
// Implementor
interface Engine {
    void start();
    void stop();
    int getPower();
}

// Concrete Implementors
class PetrolEngine implements Engine {
    public void start() { System.out.println("Petrol Engine: Vroom!"); }
    public void stop()  { System.out.println("Petrol Engine: Stopped"); }
    public int getPower() { return 150; }
}

class ElectricEngine implements Engine {
    public void start() { System.out.println("Electric Engine: Silent start..."); }
    public void stop()  { System.out.println("Electric Engine: Powered down"); }
    public int getPower() { return 200; }
}

class DieselEngine implements Engine {
    public void start() { System.out.println("Diesel Engine: Rumble..."); }
    public void stop()  { System.out.println("Diesel Engine: Stopped"); }
    public int getPower() { return 180; }
}

// Abstraction
abstract class Vehicle {
    protected Engine engine;
    public Vehicle(Engine engine) { this.engine = engine; }
    public abstract void drive();
    public abstract void park();
}

// Refined Abstractions
class Car extends Vehicle {
    private String model;
    public Car(String model, Engine engine) {
        super(engine); this.model = model;
    }
    public void drive() {
        System.out.println("Car [" + model + "] driving with " + engine.getPower() + "hp");
        engine.start();
    }
    public void park() {
        System.out.println("Car [" + model + "] parked");
        engine.stop();
    }
}

class Boat extends Vehicle {
    public Boat(Engine engine) { super(engine); }
    public void drive() {
        System.out.println("Boat sailing with " + engine.getPower() + "hp");
        engine.start();
    }
    public void park() {
        System.out.println("Boat docked");
        engine.stop();
    }
}

public class VehicleDemo {
    public static void main(String[] args) {
        Vehicle v1 = new Car("Tesla", new ElectricEngine());
        Vehicle v2 = new Car("Toyota", new PetrolEngine());
        Vehicle v3 = new Boat(new DieselEngine());

        v1.drive(); v1.park();
        System.out.println();
        v2.drive(); v2.park();
        System.out.println();
        v3.drive(); v3.park();
    }
}
```
**Output:**
```
Car [Tesla] driving with 200hp
Electric Engine: Silent start...
Car [Tesla] parked
Electric Engine: Powered down

Car [Toyota] driving with 150hp
Petrol Engine: Vroom!
Car [Toyota] parked
Petrol Engine: Stopped

Boat sailing with 180hp
Diesel Engine: Rumble...
Boat docked
Diesel Engine: Stopped
```