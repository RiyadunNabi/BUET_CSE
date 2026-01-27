// =========================
// 1. The Command Interface
// =========================

interface Command {
    void execute();
    // Bonus: Commands often have undo() too!
}

// =========================
// 2. The Receiver (The Business Logic)
// =========================

class TextEditor {
    public void save() {
        System.out.println("[Logic] Saving document to hard drive...");
    }

    public void open() {
        System.out.println("[Logic] Opening file selector dialog...");
    }

    public void copy() {
        System.out.println("[Logic] Copied text to clipboard.");
    }

    public void paste() {
        System.out.println("[Logic] Pasted text from clipboard.");
    }
}

// =========================
// 3. Concrete Commands (The Bridge)
// =========================

class SaveCommand implements Command {
    private TextEditor editor;

    public SaveCommand(TextEditor editor) {
        this.editor = editor;
    }

    @Override
    public void execute() {
        // Delegate the work to the receiver
        editor.save();
    }
}

class OpenCommand implements Command {
    private TextEditor editor;

    public OpenCommand(TextEditor editor) {
        this.editor = editor;
    }

    @Override
    public void execute() {
        editor.open();
    }
}

class CopyCommand implements Command {
    private TextEditor editor;

    public CopyCommand(TextEditor editor) {
        this.editor = editor;
    }

    @Override
    public void execute() {
        editor.copy();
    }
}

// =========================
// 4. The Invoker (The UI Element)
// =========================

class Button {
    private String label;
    private Command command;

    public Button(String label) {
        this.label = label;
    }

    // We can swap commands at runtime!
    public void setCommand(Command command) {
        this.command = command;
    }

    public void click() {
        System.out.print("User clicked '" + label + "': ");
        if (command != null) {
            command.execute();
        } else {
            System.out.println("Nothing assigned to this button.");
        }
    }
}

// =========================
// 5. Main Driver Class (The Client)
// =========================

public class b_Command_Pattern_TextEditorApp {
    public static void main(String[] args) {
        // 1. Create the Receiver (The Logic)
        TextEditor myEditor = new TextEditor();

        // 2. Create Commands (Wrap the logic)
        Command saveCmd = new SaveCommand(myEditor);
        Command openCmd = new OpenCommand(myEditor);
        Command copyCmd = new CopyCommand(myEditor);

        // 3. Create Invokers (The UI Buttons)
        // Notice: The Button class is generic. No "SaveButton" class needed!
        Button btnSave = new Button("Save Icon");
        Button btnOpen = new Button("Open Icon");
        Button btnCopy = new Button("Copy Icon");

        // 4. Assign Commands to Buttons
        btnSave.setCommand(saveCmd);
        btnOpen.setCommand(openCmd);
        btnCopy.setCommand(copyCmd);

        // 5. User interacts with UI
        System.out.println("--- Testing Toolbar ---");
        btnSave.click();
        btnCopy.click();
        btnOpen.click();

        // 6. Dynamic Reassignment (The Power of Command Pattern)
        System.out.println("\n--- Reassigning Button ---");
        // Imagine the user changed a setting to make the "Copy" button do a "Save" instead
        btnCopy.setCommand(saveCmd); 
        btnCopy.click(); // Now it saves!
    }
}