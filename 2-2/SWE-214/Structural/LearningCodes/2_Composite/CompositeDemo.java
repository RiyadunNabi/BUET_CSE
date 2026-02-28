// public  COMPOSITE PATTERN
// Problem: A file system has files and folders. Folders can contain files or other folders. Calculate total size of any file or folder.

import java.util.ArrayList;
import java.util.List;

// Component
interface FileSystemComponent {
    String getName();
    int getSize();
    void display(String indent);
}

// Leaf
class File implements FileSystemComponent {
    private String name;
    private int size;

    public File(String name, int size) {
        this.name = name;
        this.size = size;
    }
    public String getName() { return name; }
    public int getSize()    { return size; }
    public void display(String indent) {
        System.out.println(indent + "📄 " + name + " (" + size + " KB)");
    }
}

// Composite
class Folder implements FileSystemComponent {
    private String name;
    private List<FileSystemComponent> children = new ArrayList<>();

    public Folder(String name) { this.name = name; }

    public void add(FileSystemComponent c)    { children.add(c); }
    public void remove(FileSystemComponent c) { children.remove(c); }

    public String getName() { return name; }
    public int getSize() {
        return children.stream().mapToInt(FileSystemComponent::getSize).sum();
    }
    public void display(String indent) {
        System.out.println(indent + "📁 " + name + " (" + getSize() + " KB)");
        for (FileSystemComponent c : children) {
            c.display(indent + "   ");
        }
    }
}

// Main
public class CompositeDemo {
    public static void main(String[] args) {
        File f1 = new File("resume.pdf", 200);
        File f2 = new File("photo.jpg", 500);
        File f3 = new File("notes.txt", 50);
        File f4 = new File("music.mp3", 4000);

        Folder docs = new Folder("Documents");
        docs.add(f1);
        docs.add(f3);

        Folder media = new Folder("Media");
        media.add(f2);
        media.add(f4);

        Folder root = new Folder("Root");
        root.add(docs);
        root.add(media);

        root.display("");
        System.out.println("\nTotal Root Size: " + root.getSize() + " KB");
    }
}
// ```

// **Output:**
// ```
// 📁 Root (4750 KB)
//    📁 Documents (250 KB)
//       📄 resume.pdf (200 KB)
//       📄 notes.txt (50 KB)
//    📁 Media (4500 KB)
//       📄 photo.jpg (500 KB)
//       📄 music.mp3 (4000 KB)

// Total Root Size: 4750 KB {
    
// }
// import java.util.ArrayList;
