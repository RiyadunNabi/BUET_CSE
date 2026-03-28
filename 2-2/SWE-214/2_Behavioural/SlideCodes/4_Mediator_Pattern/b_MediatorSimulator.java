import java.util.ArrayList;
import java.util.List;

// =========================
// 1. The Mediator Interface
// =========================

interface Mediator {
    // The central hub method: Components call this to say "Something happened!"
    void notify(Component sender, String event);
}

// =========================
// 2. The Abstract Colleague (Component)
// =========================

abstract class Component {
    protected Mediator mediator;
    protected String name;

    public Component(String name) {
        this.name = name;
    }

    // Every component needs a reference to the Mediator
    public void setMediator(Mediator mediator) {
        this.mediator = mediator;
    }

    public String getName() {
        return name;
    }
}

// =========================
// 3. Concrete Components (The UI Elements)
// =========================

// A Checkbox (e.g., "Is Business Account?")
class Checkbox extends Component {
    private boolean checked = false;

    public Checkbox(String name) {
        super(name);
    }

    public void check() {
        checked = true;
        System.out.println(name + " checked.");
        // CRITICAL: We don't touch the TextBox directly. We tell the Mediator.
        mediator.notify(this, "check");
    }

    public void uncheck() {
        checked = false;
        System.out.println(name + " unchecked.");
        mediator.notify(this, "uncheck");
    }

    public boolean isChecked() {
        return checked;
    }
}

// A TextBox (e.g., "Company Name")
class TextBox extends Component {
    private boolean enabled = false;

    public TextBox(String name) {
        super(name);
    }

    public void enable() {
        enabled = true;
        System.out.println(name + " is now ENABLED.");
    }

    public void disable() {
        enabled = false;
        System.out.println(name + " is now DISABLED.");
    }
    
    public boolean isEnabled() {
        return enabled;
    }
}

// A Button (e.g., "Submit")
class Button extends Component {
    public Button(String name) {
        super(name);
    }

    public void click() {
        System.out.println(name + " clicked.");
        mediator.notify(this, "click");
    }
}

// =========================
// 4. The Concrete Mediator (The Dialog Logic)
// =========================

class ProfileDialog implements Mediator {
    // The Mediator knows about all the specific components
    private Checkbox isBusinessCheckbox;
    private TextBox companyNameBox;
    private TextBox usernameBox;
    private Button submitButton;

    // Methods to register components (or you could do this in a constructor)
    public void setBusinessCheckbox(Checkbox cb) { this.isBusinessCheckbox = cb; cb.setMediator(this); }
    public void setCompanyBox(TextBox tb) { this.companyNameBox = tb; tb.setMediator(this); }
    public void setUsernameBox(TextBox tb) { this.usernameBox = tb; tb.setMediator(this); }
    public void setSubmitButton(Button b) { this.submitButton = b; b.setMediator(this); }

    @Override
    public void notify(Component sender, String event) {
        // --- LOGIC CENTRAL ---
        // All the "Spaghetti" logic lives ONLY here.
        
        // Logic 1: If "Is Business" is checked, enable Company Name box
        if (sender == isBusinessCheckbox && event.equals("check")) {
            System.out.println(">> Mediator: Business account selected. Enabling company field...");
            companyNameBox.enable();
        }
        
        // Logic 2: If "Is Business" is unchecked, disable Company Name box
        if (sender == isBusinessCheckbox && event.equals("uncheck")) {
            System.out.println(">> Mediator: Personal account selected. Disabling company field...");
            companyNameBox.disable();
        }

        // Logic 3: If Submit is clicked, validate
        if (sender == submitButton && event.equals("click")) {
            System.out.println(">> Mediator: Validating form...");
            if (isBusinessCheckbox.isChecked() && !companyNameBox.isEnabled()) {
                 System.out.println("   ERROR: Logic mismatch!");
            } else {
                 System.out.println("   SUCCESS: Form submitted!");
            }
        }
    }
}

// =========================
// 5. Main Driver Class
// =========================

public class b_MediatorSimulator {
    public static void main(String[] args) {
        // 1. Create the Mediator
        ProfileDialog dialog = new ProfileDialog();

        // 2. Create Components
        Checkbox businessCheck = new Checkbox("Business Checkbox");
        TextBox companyBox = new TextBox("Company Name Box");
        TextBox userBox = new TextBox("Username Box");
        Button okBtn = new Button("Submit Button");

        // 3. Register them with Mediator
        dialog.setBusinessCheckbox(businessCheck);
        dialog.setCompanyBox(companyBox);
        dialog.setUsernameBox(userBox);
        dialog.setSubmitButton(okBtn);

        System.out.println("--- Scenario 1: User clicks Business Checkbox ---");
        // User interacts with the COMPONENT, but the logic is handled by MEDIATOR
        businessCheck.check(); 
        
        System.out.println("\n--- Scenario 2: User unchecks Business Checkbox ---");
        businessCheck.uncheck();

        System.out.println("\n--- Scenario 3: User clicks Submit ---");
        okBtn.click();
    }
}

// --- Scenario 1: User clicks Business Checkbox ---
// Business Checkbox checked.
// >> Mediator: Business account selected. Enabling company field...
// Company Name Box is now ENABLED.

// --- Scenario 2: User unchecks Business Checkbox ---
// Business Checkbox unchecked.
// >> Mediator: Personal account selected. Disabling company field...
// Company Name Box is now DISABLED.

// --- Scenario 3: User clicks Submit ---
// Submit Button clicked.
// >> Mediator: Validating form...
//    SUCCESS: Form submitted!