// ADAPTER PATTERN
// Problem: You have an old LegacyPrinter that prints in plain text. A new system expects a ModernPrinter interface that prints with formatting. Adapt the legacy printer.
// java// Target Interface (what client expects)

interface ModernPrinter {
    void printFormatted(String text, String format);
}

// Adaptee (existing legacy class)
class LegacyPrinter {
    public void printPlain(String text) {
        System.out.println("Legacy Print: " + text);
    }
}

// Adapter
class PrinterAdapter implements ModernPrinter {
    private LegacyPrinter legacyPrinter;

    public PrinterAdapter(LegacyPrinter legacyPrinter) {
        this.legacyPrinter = legacyPrinter;
    }

    @Override
    public void printFormatted(String text, String format) {
        String formatted = "[" + format.toUpperCase() + "] " + text;
        legacyPrinter.printPlain(formatted);
    }
}

// Main
public class AdapterDemo {
    public static void main(String[] args) {
        LegacyPrinter legacy = new LegacyPrinter();
        ModernPrinter modern = new PrinterAdapter(legacy);

        modern.printFormatted("Hello World", "bold");
        modern.printFormatted("Error occurred", "red");
    }
}

// ```

// **Output:**
// ```
// Legacy Print: [BOLD] Hello World
// Legacy Print: [RED] Error occurred