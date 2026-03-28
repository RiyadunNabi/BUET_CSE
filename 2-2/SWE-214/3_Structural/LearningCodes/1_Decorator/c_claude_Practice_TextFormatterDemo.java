// Text Formatter
// Apply formatting (Bold, Italic, Underline, Uppercase) to plain text dynamically.

interface TextComponent {
    String render();
}

class PlainText implements TextComponent {
    private String text;
    public PlainText(String text) { this.text = text; }
    public String render() { return text; }
}

abstract class TextDecorator implements TextComponent {
    protected TextComponent component;
    public TextDecorator(TextComponent component) { this.component = component; }
}

class BoldText extends TextDecorator {
    public BoldText(TextComponent c) { super(c); }
    public String render() { return "**" + component.render() + "**"; }
}

class ItalicText extends TextDecorator {
    public ItalicText(TextComponent c) { super(c); }
    public String render() { return "_" + component.render() + "_"; }
}

class UnderlineText extends TextDecorator {
    public UnderlineText(TextComponent c) { super(c); }
    public String render() { return "__" + component.render() + "__"; }
}

class UppercaseText extends TextDecorator {
    public UppercaseText(TextComponent c) { super(c); }
    public String render() { return component.render().toUpperCase(); }
}

public class c_claude_Practice_TextFormatterDemo {
    public static void main(String[] args) {
        TextComponent t1 = new PlainText("hello world");
        System.out.println(t1.render());

        TextComponent t2 = new BoldText(new ItalicText(new PlainText("hello world")));
        System.out.println(t2.render());

        TextComponent t3 = new UppercaseText(new UnderlineText(new BoldText(new PlainText("hello world"))));
        System.out.println(t3.render());
    }
}


// ```
// **Output:**
// ```
// hello world
// **_hello world_**
// __**HELLO WORLD**__ {
    
// }
