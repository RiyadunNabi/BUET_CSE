// =========================
// 1. The State Interface
// =========================

interface State {
    void insertQuarter();
    void ejectQuarter();
    void turnCrank();
    void dispense();
}

// =========================
// 2. The Context (The Machine)
// =========================

class GumballMachine {
    // States
    State soldOutState;
    State noQuarterState;
    State hasQuarterState;
    State soldState;

    // Current State
    State state;
    int count = 0;

    public GumballMachine(int numberGumballs) {
        // Initialize all state objects
        soldOutState = new SoldOutState(this);
        noQuarterState = new NoQuarterState(this);
        hasQuarterState = new HasQuarterState(this);
        soldState = new SoldState(this);

        this.count = numberGumballs;
        if (numberGumballs > 0) {
            state = noQuarterState;
        } else {
            state = soldOutState;
        }
    }

    // Actions delegate to the current state
    public void insertQuarter() {
        state.insertQuarter();
    }

    public void ejectQuarter() {
        state.ejectQuarter();
    }

    public void turnCrank() {
        state.turnCrank();
        state.dispense(); // Internal action
    }

    void releaseBall() {
        System.out.println("A gumball comes rolling out the slot...");
        if (count != 0) {
            count = count - 1;
        }
    }

    // Getters and Setters for states to transition
    void setState(State state) {
        this.state = state;
    }

    public State getHasQuarterState() { return hasQuarterState; }
    public State getNoQuarterState() { return noQuarterState; }
    public State getSoldState() { return soldState; }
    public State getSoldOutState() { return soldOutState; }
    public int getCount() { return count; }
}

// =========================
// 3. Concrete States
// =========================

class NoQuarterState implements State {
    GumballMachine gumballMachine;

    public NoQuarterState(GumballMachine gumballMachine) {
        this.gumballMachine = gumballMachine;
    }

    @Override
    public void insertQuarter() {
        System.out.println("You inserted a quarter");
        // TRANSITION: No Quarter -> Has Quarter
        gumballMachine.setState(gumballMachine.getHasQuarterState());
    }

    @Override
    public void ejectQuarter() {
        System.out.println("You haven't inserted a quarter");
    }

    @Override
    public void turnCrank() {
        System.out.println("You turned, but there's no quarter");
    }

    @Override
    public void dispense() {
        System.out.println("You need to pay first");
    }
}

class HasQuarterState implements State {
    GumballMachine gumballMachine;

    public HasQuarterState(GumballMachine gumballMachine) {
        this.gumballMachine = gumballMachine;
    }

    @Override
    public void insertQuarter() {
        System.out.println("You can't insert another quarter");
    }

    @Override
    public void ejectQuarter() {
        System.out.println("Quarter returned");
        // TRANSITION: Has Quarter -> No Quarter
        gumballMachine.setState(gumballMachine.getNoQuarterState());
    }

    @Override
    public void turnCrank() {
        System.out.println("You turned...");
        // TRANSITION: Has Quarter -> Sold
        gumballMachine.setState(gumballMachine.getSoldState());
    }

    @Override
    public void dispense() {
        System.out.println("No gumball dispensed");
    }
}

class SoldState implements State {
    GumballMachine gumballMachine;

    public SoldState(GumballMachine gumballMachine) {
        this.gumballMachine = gumballMachine;
    }

    @Override
    public void insertQuarter() {
        System.out.println("Please wait, we're already giving you a gumball");
    }

    @Override
    public void ejectQuarter() {
        System.out.println("Sorry, you already turned the crank");
    }

    @Override
    public void turnCrank() {
        System.out.println("Turning twice doesn't get you another gumball!");
    }

    @Override
    public void dispense() {
        gumballMachine.releaseBall();
        if (gumballMachine.getCount() > 0) {
            // TRANSITION: Sold -> No Quarter (Reset)
            gumballMachine.setState(gumballMachine.getNoQuarterState());
        } else {
            System.out.println("Oops, out of gumballs!");
            // TRANSITION: Sold -> Sold Out
            gumballMachine.setState(gumballMachine.getSoldOutState());
        }
    }
}

class SoldOutState implements State {
    GumballMachine gumballMachine;

    public SoldOutState(GumballMachine gumballMachine) {
        this.gumballMachine = gumballMachine;
    }

    @Override
    public void insertQuarter() {
        System.out.println("You can't insert a quarter, the machine is sold out");
    }

    @Override
    public void ejectQuarter() {
        System.out.println("You can't eject, you haven't inserted a quarter yet");
    }

    @Override
    public void turnCrank() {
        System.out.println("You turned, but there are no gumballs");
    }

    @Override
    public void dispense() {
        System.out.println("No gumball dispensed");
    }
}

// =========================
// 4. Main Driver Class
// =========================

public class b_GumballSimulator {
    public static void main(String[] args) {
        GumballMachine gumballMachine = new GumballMachine(5);

        System.out.println("--- Test 1: Normal Flow ---");
        gumballMachine.insertQuarter(); // No Quarter -> Has Quarter
        gumballMachine.turnCrank();     // Has Quarter -> Sold -> No Quarter

        System.out.println("\n--- Test 2: Double Quarter Error ---");
        gumballMachine.insertQuarter();
        gumballMachine.insertQuarter(); // Should fail
        gumballMachine.ejectQuarter();  // Back to No Quarter

        System.out.println("\n--- Test 3: Emptying the Machine ---");
        gumballMachine.insertQuarter(); gumballMachine.turnCrank();
        gumballMachine.insertQuarter(); gumballMachine.turnCrank();
        gumballMachine.insertQuarter(); gumballMachine.turnCrank();
        gumballMachine.insertQuarter(); gumballMachine.turnCrank(); // Now count is 0

        System.out.println("\n--- Test 4: Sold Out ---");
        gumballMachine.insertQuarter(); // Should fail (Sold Out)
    }
}