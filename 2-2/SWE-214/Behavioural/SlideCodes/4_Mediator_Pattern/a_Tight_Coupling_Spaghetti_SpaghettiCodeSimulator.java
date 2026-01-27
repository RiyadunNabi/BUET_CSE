// =========================
// ❌ THE PROBLEM: Tight Coupling (Spaghetti)
// =========================

// 1. The Text Box
class CompanyTextBox {
    private boolean isEnabled = false;

    public void enable() {
        isEnabled = true;
        System.out.println("Company Text Box is now ENABLED.");
    }

    public void disable() {
        isEnabled = false;
        System.out.println("Company Text Box is now DISABLED.");
    }

    public boolean isEnabled() {
        return isEnabled;
    }
}

// 2. The Checkbox (The Culprit)
class BusinessCheckbox {
    // PAIN POINT: Direct dependency on a specific text box!
    // You cannot reuse this class in any other dialog.
    private CompanyTextBox companyTextBox;

    public BusinessCheckbox(CompanyTextBox box) {
        this.companyTextBox = box;
    }

    public void check() {
        System.out.println("Checkbox checked.");
        // BAD: The checkbox is controlling the text box directly.
        companyTextBox.enable(); 
    }

    public void uncheck() {
        System.out.println("Checkbox unchecked.");
        // BAD: Logic is hardcoded inside the component.
        companyTextBox.disable();
    }
}

// 3. The Submit Button
class SubmitButton {
    private BusinessCheckbox checkbox;
    private CompanyTextBox textBox;

    public SubmitButton(BusinessCheckbox cb, CompanyTextBox tb) {
        this.checkbox = cb;
        this.textBox = tb;
    }

    public void click() {
        // PAIN POINT: The button has to know the internal state of other components.
        // If logic gets complex, this button code becomes huge.
        if (checkbox != null && textBox.isEnabled()) {
            System.out.println("Validating Company Name...");
        } else {
            System.out.println("Submitting Personal Account...");
        }
    }
}

// 4. Main Simulation
public class a_Tight_Coupling_Spaghetti_SpaghettiCodeSimulator {
    public static void main(String[] args) {
        // We have to wire everything manually
        CompanyTextBox myTextBox = new CompanyTextBox();
        
        // The Checkbox depends on the TextBox
        BusinessCheckbox myCheckbox = new BusinessCheckbox(myTextBox);
        
        // The Button depends on BOTH
        SubmitButton myButton = new SubmitButton(myCheckbox, myTextBox);

        System.out.println("--- User interactions ---");
        myCheckbox.check(); // Internally calls myTextBox.enable()
        myButton.click();
    }
}