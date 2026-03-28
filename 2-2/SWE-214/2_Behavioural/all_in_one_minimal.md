
---

## 1. Strategy Pattern
> *"Swap algorithms at runtime"*

```java
// Strategy Interface
interface SortStrategy {
    void sort(int[] arr);
}

// Concrete Strategies
class BubbleSort implements SortStrategy {
    public void sort(int[] arr) { System.out.println("Bubble sorting..."); }
}

class MergeSort implements SortStrategy {
    public void sort(int[] arr) { System.out.println("Merge sorting..."); }
}

// Abstract Context
abstract class Sorter {
    protected SortStrategy strategy;

    public Sorter(SortStrategy strategy) {
        this.strategy = strategy;
    }

    public void sort(int[] arr) {
        strategy.sort(arr);
    }
}

// Concrete Sorters — strategy is fixed via constructor
class BubbleSorter extends Sorter {
    public BubbleSorter() { super(new BubbleSort()); }
}

class MergeSorter extends Sorter {
    public MergeSorter() { super(new MergeSort()); }
}

// Main
public class StrategyDemo {
    public static void main(String[] args) {
        int[] arr = {3, 1, 2};

        Sorter s1 = new BubbleSorter();
        s1.sort(arr);    // Bubble sorting...

        Sorter s2 = new MergeSorter();
        s2.sort(arr);    // Merge sorting...
    }
}
```

**Remember:** `SortStrategy` is the algorithm interface → `Sorter` is the abstract context that holds it → each concrete sorter wires up its own strategy in the constructor via `super(new XxxSort())`.

---

## 2. Template Method Pattern
> *"Parent defines the skeleton, children fill in the steps"*

```java
abstract class DataProcessor {

    public final void process() {
        readData();
        processData();
        writeData();
    }

    abstract void readData();
    abstract void processData();

    void writeData() {
        System.out.println("Writing to disk...");
    }
}

class CSVProcessor extends DataProcessor {
    void readData() {
        System.out.println("Reading CSV...");
    }

    void processData() {
        System.out.println("Processing CSV rows...");
    }
}

class JSONProcessor extends DataProcessor {
    void readData() {
        System.out.println("Reading JSON...");
    }

    void processData() {
        System.out.println("Parsing JSON keys...");
    }
}

public class Main {
    public static void main(String[] args) {
        new CSVProcessor().process();
        new JSONProcessor().process();
    }
}
```
**Remember:** Abstract class, `final` template method, `abstract` steps for subclasses. Like a recipe skeleton.

---

## 3. Observer Pattern
> *"Subscribe and get notified automatically"*

```java
import java.util.ArrayList;
import java.util.List;

// --- The "Subscriber" Interface ---
interface Observer {
    void update(float temp);
}

// --- The "Publisher" Interface ---
interface Subject {
    void registerObserver(Observer o);
    void notifyObservers();
}

// --- The Concrete Subject ---
class WeatherData implements Subject {
    private List<Observer> observers = new ArrayList<>();
    private float temp;

    public void registerObserver(Observer o) { observers.add(o); }

    public void notifyObservers() {
        for (Observer o : observers) {
            o.update(temp);
        }
    }

    public void setTemperature(float temp) {
        this.temp = temp;
        notifyObservers(); // Trigger the update automatically
    }
}

// --- Concrete Observers ---
class TemperatureDisplay implements Observer {
    TemperatureDisplay(Subject s) { s.registerObserver(this); }

    public void update(float temp) {
        System.out.println("Display: Current temperature is " + temp + "°F");
    }
}

class TrendDisplay implements Observer {
    private float lastTemp;

    TrendDisplay(Subject s) { s.registerObserver(this); }

    public void update(float temp) {
        String trend = (temp > lastTemp) ? "Rising" : "Falling";
        System.out.println("Trend: Temperature is " + trend);
        lastTemp = temp;
    }
}

// --- Execution ---
public class SimpleObserver {
    public static void main(String[] args) {
        WeatherData weatherStation = new WeatherData();

        new TemperatureDisplay(weatherStation);
        new TrendDisplay(weatherStation);

        System.out.println("--- Update 1 ---");
        weatherStation.setTemperature(80.0f);

        System.out.println("--- Update 2 ---");
        weatherStation.setTemperature(75.5f);
    }
}
```
**Remember:** Subject holds a list of observers → calls `update()` on all of them when state changes.

---

## 4. Mediator Pattern
> *"Everyone talks through a central hub, not each other"*

```java
import java.util.*;

interface Mediator {
    void sendMessage(String msg, User sender);
}

abstract class User {
    protected Mediator mediator;
    protected String name;

    User(Mediator m, String name) {
        this.mediator = m;
        this.name     = name;
    }

    abstract void send(String msg);
    abstract void receive(String msg, String from);
}

class ChatRoom implements Mediator {
    private List<User> users = new ArrayList<>();

    public void addUser(User u) {
        users.add(u);
    }

    public void sendMessage(String msg, User sender) {
        for (User u : users) {
            if (!u.name.equals(sender.name)) {
                u.receive(msg, sender.name);
            }
        }
    }
}

class Member extends User {

    Member(Mediator m, String name) {
        super(m, name);
    }

    public void send(String msg) {
        mediator.sendMessage(msg, this);
    }

    public void receive(String msg, String from) {
        System.out.println(name + " got from " + from + ": " + msg);
    }
}

public class Main {
    public static void main(String[] args) {
        ChatRoom room  = new ChatRoom();
        Member   alice = new Member(room, "Alice");
        Member   bob   = new Member(room, "Bob");

        room.addUser(alice);
        room.addUser(bob);

        alice.send("Hi Bob!");    // Bob got from Alice: Hi Bob!
    }
}
```
**Remember:** Colleagues only reference the mediator. Mediator knows everyone and routes messages.
---
or, (from slide minimal code)
```java
// ─── Mediator Interface ───────────────────────────────────────────────────────

interface Mediator {
    void notify(Component sender, String event);
}

// ─── Abstract Component ───────────────────────────────────────────────────────

abstract class Component {
    protected Mediator mediator;

    public void setMediator(Mediator m) {
        this.mediator = m;
    }
}

// ─── Concrete Components ──────────────────────────────────────────────────────

class Checkbox extends Component {
    private boolean checked = false;

    public void check() {
        checked = true;
        mediator.notify(this, "check");
    }

    public boolean isChecked() { return checked; }
}

class TextBox extends Component {
    private boolean enabled = false;

    public void enable()  { enabled = true;  System.out.println("TextBox: ENABLED");  }
    public void disable() { enabled = false; System.out.println("TextBox: DISABLED"); }
}

class Button extends Component {
    public void click() {
        mediator.notify(this, "click");
    }
}

// ─── Concrete Mediator ────────────────────────────────────────────────────────

class Dialog implements Mediator {
    private Checkbox checkbox;
    private TextBox  textBox;
    private Button   button;

    public Dialog(Checkbox cb, TextBox tb, Button btn) {
        this.checkbox = cb;
        this.textBox  = tb;
        this.button   = btn;

        cb.setMediator(this);
        tb.setMediator(this);
        btn.setMediator(this);
    }

    public void notify(Component sender, String event) {
        if (sender == checkbox && event.equals("check")) {
            System.out.println("Mediator: Checkbox checked → enabling TextBox");
            textBox.enable();
        }
        if (sender == button && event.equals("click")) {
            System.out.println("Mediator: Button clicked → form submitted!");
        }
    }
}

// ─── Main ─────────────────────────────────────────────────────────────────────

public class MediatorPattern {
    public static void main(String[] args) {
        Checkbox cb  = new Checkbox();
        TextBox  tb  = new TextBox();
        Button   btn = new Button();

        new Dialog(cb, tb, btn);

        System.out.println("--- User checks checkbox ---");
        cb.check();

        System.out.println("\n--- User clicks button ---");
        btn.click();
    }
}
```

---

**Output:**
```
--- User checks checkbox ---
Mediator: Checkbox checked → enabling TextBox
TextBox: ENABLED

--- User clicks button ---
Mediator: Button clicked → form submitted!
```
---

## 5. Command Pattern
> *"Wrap a request as an object — supports undo/redo/queue"*

```java
// ─── Command Interface ────────────────────────────────────────────────────────

interface Command {
    void execute();
    void undo();
}

// ─── Receiver ─────────────────────────────────────────────────────────────────

class Light {
    public void on()  { System.out.println("Light ON");  }
    public void off() { System.out.println("Light OFF"); }
}

// ─── Concrete Command ─────────────────────────────────────────────────────────

class LightOnCommand implements Command {
    private Light light;

    LightOnCommand(Light l) {
        this.light = l;
    }

    public void execute() { light.on();  }
    public void undo()    { light.off(); }
}

// ─── Invoker ──────────────────────────────────────────────────────────────────

class RemoteControlButton {
    private Command command;

    RemoteControlButton(Command cmd) {
        this.command = cmd;
    }

    public void pressButton(){ 
        command.execute(); 
    }
    public void pressUndo(){ 
        command.undo();    
    }
}

// ─── Main ─────────────────────────────────────────────────────────────────────

public class CommandPattern {
    public static void main(String[] args) {
        Light light = new Light();
        RemoteControlButton remote = new RemoteControlButton(new LightOnCommand(light));

        remote.pressButton();    // Light ON
        remote.pressUndo();      // Light OFF
    }
}
```

---

**Output:**
```
Light ON
Light OFF
```
**Remember:** Command = `execute()` + `undo()`. Invoker doesn't know what it's executing. Receiver does the actual work.

---

## 6. State Pattern
> *"Object changes behavior when its internal state changes"*

```java
interface State {
    void handle(TrafficLight light);
}

class TrafficLight {
    private State state;

    public TrafficLight() {
        state = new RedState();
    }

    public void setState(State s) { this.state = s; }

    public void change() {
        state.handle(this);
    }
}

class RedState implements State {
    public void handle(TrafficLight light) {
        System.out.println("RED — Stop!");
        light.setState(new GreenState());
    }
}

class GreenState implements State {
    public void handle(TrafficLight light) {
        System.out.println("GREEN — Go!");
        light.setState(new YellowState());
    }
}

class YellowState implements State {
    public void handle(TrafficLight light) {
        System.out.println("YELLOW — Slow down!");
        light.setState(new RedState());
    }
}

public class Main {
    public static void main(String[] args) {
        TrafficLight light = new TrafficLight();

        light.change();    // RED — Stop!
        light.change();    // GREEN — Go!
        light.change();    // YELLOW — Slow down!
        light.change();    // RED — Stop!
    }
}
```
**Remember:** Context holds a `State` reference → each state transitions to the next. No giant if-else chains.

---
---
```java
// ─── State Interface ──────────────────────────────────────────────────────────

interface State {
    void insertQuarter();
    void turnCrank();
}

// ─── Context ──────────────────────────────────────────────────────────────────

class GumballMachine {
    State noQuarterState  = new NoQuarterState(this);
    State hasQuarterState = new HasQuarterState(this);
    State soldOutState    = new SoldOutState(this);

    State state;
    int   count;

    GumballMachine(int count) {
        this.count = count;
        state = count > 0 ? noQuarterState : soldOutState;
    }

    public void insertQuarter() { state.insertQuarter(); }
    public void turnCrank()     { state.turnCrank();     }

    public void setState(State s) { this.state = s; }

    public void releaseBall() {
        System.out.println("Gumball released!");
        count--;
    }
}

// ─── Concrete States ──────────────────────────────────────────────────────────

class NoQuarterState implements State {
    GumballMachine machine;
    NoQuarterState(GumballMachine m) { this.machine = m; }

    public void insertQuarter() {
        System.out.println("Quarter inserted.");
        machine.setState(machine.hasQuarterState);
    }

    public void turnCrank() {
        System.out.println("No quarter inserted!");
    }
}

class HasQuarterState implements State {
    GumballMachine machine;
    HasQuarterState(GumballMachine m) { this.machine = m; }

    public void insertQuarter() {
        System.out.println("Already has a quarter!");
    }

    public void turnCrank() {
        System.out.println("Crank turned...");
        machine.releaseBall();
        if (machine.count > 0) {
            machine.setState(machine.noQuarterState);
        } else {
            System.out.println("Out of gumballs!");
            machine.setState(machine.soldOutState);
        }
    }
}

class SoldOutState implements State {
    SoldOutState(GumballMachine m) {}

    public void insertQuarter() { System.out.println("Machine is sold out!"); }
    public void turnCrank()     { System.out.println("Machine is sold out!"); }
}

// ─── Main ─────────────────────────────────────────────────────────────────────

public class StatePattern {
    public static void main(String[] args) {
        GumballMachine machine = new GumballMachine(2);

        System.out.println("--- Normal flow ---");
        machine.insertQuarter();
        machine.turnCrank();

        System.out.println("\n--- Error: no quarter ---");
        machine.turnCrank();

        System.out.println("\n--- Last gumball ---");
        machine.insertQuarter();
        machine.turnCrank();

        System.out.println("\n--- Sold out ---");
        machine.insertQuarter();
    }
}
```

---

**Output:**
```
--- Normal flow ---
Quarter inserted.
Crank turned...
Gumball released!

--- Error: no quarter ---
No quarter inserted!

--- Last gumball ---
Quarter inserted.
Crank turned...
Gumball released!
Out of gumballs!

--- Sold out ---
Machine is sold out!
```




## Quick Cheat Sheet

| Pattern | One-liner | Key roles |
|---|---|---|
| **Strategy** | Swap algorithm at runtime | Context + Interface + ConcreteStrategies |
| **Template Method** | Parent skeleton, children fill steps | Abstract class + subclasses |
| **Observer** | Notify all subscribers on change | Subject + Observer interface + ConcreteObservers |
| **Mediator** | Central hub routes all communication | Mediator + Colleague base + ConcreteColleagues |
| **Command** | Request as object with undo | Command interface + Invoker + Receiver |
| **State** | Behavior changes with internal state | Context + State interface + ConcreteStates |

All the best on your test, Riyad! 🎯