// =========================
// THE PROBLEM: Subclassing for Logic
// =========================

// The Logic Class (The Receiver)
class TextEditor {
    public void save() { System.out.println("Saving file to disk..."); }
    public void open() { System.out.println("Opening file..."); }
}

// The Base UI Class
class Button {
    public void click() {}
}

// BAD: We are creating a whole new class just to change what click() does.
class SaveButton extends Button {
    private TextEditor editor;
    
    public SaveButton(TextEditor editor) {
        this.editor = editor;
    }

    @Override
    public void click() {
        // COUPLING: The UI button is directly doing file operations!
        editor.save(); 
    }
}

// BAD: Another class...
class OpenButton extends Button {
    private TextEditor editor;
    
    public OpenButton(TextEditor editor) {
        this.editor = editor;
    }

    @Override
    public void click() {
        editor.open();
    }
}
// Now imagine doing this for Copy, Paste, Cut, Undo, Redo, Print...