## Pre-discussion: Mediator Pattern

**Core idea:** Think of an **air traffic controller (ATC)**. Planes don't talk to each other directly — that would be chaotic. Every plane talks *only* to the ATC, and ATC coordinates everything. The Mediator is that ATC.

**The problem it solves:** When you have many objects that need to communicate with each other, direct connections create a "spaghetti" of dependencies. Every object ends up knowing about every other object. The Mediator centralizes all communication through one object, so each participant only knows about the mediator — not each other.

**Compare with Observer:**
- Observer → one subject, many listeners (one-to-many)
- Mediator → many objects talking through one hub (many-to-many, but routed centrally)

**Key roles:**
- `Mediator` — interface defining how colleagues send messages through it
- `ConcreteMediator` — knows all colleagues, contains the routing logic
- `Colleague` — each participant; only holds a reference to the mediator, never to other colleaguesThe left side is what happens without a mediator — `n` objects need `n(n-1)/2` connections. With a mediator, it's always just `n` connections, one per colleague.

---

Here's the full runnable code. The example is a **chat room** — a classic and clean fit for this pattern:

```java
import java.util.ArrayList;
import java.util.List;

// ─── Step 1: Mediator Interface ───────────────────────────────────────────────
interface ChatMediator {
    void sendMessage(String message, User sender);
    void addUser(User user);
}

// ─── Step 2: Colleague (abstract base) ───────────────────────────────────────
// Each user only knows about the mediator, never about other users directly.
abstract class User {
    protected ChatMediator mediator;
    protected String name;

    public User(ChatMediator mediator, String name) {
        this.mediator = mediator;
        this.name = name;
    }

    public String getName() { return name; }

    // To send: talk to mediator
    public abstract void send(String message);

    // To receive: mediator calls this
    public abstract void receive(String message, String fromUser);
}

// ─── Step 3: Concrete Mediator — ChatRoom ─────────────────────────────────────
// This class IS the intelligence. It decides who gets what message.
class ChatRoom implements ChatMediator {
    private List<User> users = new ArrayList<>();

    @Override
    public void addUser(User user) {
        users.add(user);
        System.out.println("[ChatRoom] " + user.getName() + " joined the room.");
    }

    @Override
    public void sendMessage(String message, User sender) {
        System.out.println("\n[ChatRoom] Routing message from " + sender.getName() + "...");
        for (User user : users) {
            // Mediator decides: don't send back to the sender themselves
            if (!user.getName().equals(sender.getName())) {
                user.receive(message, sender.getName());
            }
        }
    }
}

// ─── Step 4: Concrete Colleague — RegularUser ────────────────────────────────
class RegularUser extends User {

    public RegularUser(ChatMediator mediator, String name) {
        super(mediator, name);
    }

    @Override
    public void send(String message) {
        System.out.println("  [" + name + "] sending: \"" + message + "\"");
        // Notice: doesn't call other users directly — goes through mediator
        mediator.sendMessage(message, this);
    }

    @Override
    public void receive(String message, String fromUser) {
        System.out.println("  [" + name + "] received from " + fromUser + ": \"" + message + "\"");
    }
}

// ─── Step 5: Concrete Colleague — AdminUser ───────────────────────────────────
// Admins broadcast with a prefix — same mediator, different behavior
class AdminUser extends User {

    public AdminUser(ChatMediator mediator, String name) {
        super(mediator, name);
    }

    @Override
    public void send(String message) {
        String adminMessage = "[ADMIN BROADCAST] " + message;
        System.out.println("  [" + name + " (admin)] sending broadcast");
        mediator.sendMessage(adminMessage, this);
    }

    @Override
    public void receive(String message, String fromUser) {
        System.out.println("  [" + name + " (admin)] received from " + fromUser + ": \"" + message + "\"");
    }
}

// ─── Step 6: Main ─────────────────────────────────────────────────────────────
public class MediatorPatternDemo {

    public static void main(String[] args) {

        // Create mediator
        ChatMediator chatRoom = new ChatRoom();

        // Create colleagues — each one gets the mediator injected
        User alice = new RegularUser(chatRoom, "Alice");
        User bob   = new RegularUser(chatRoom, "Bob");
        User carol = new RegularUser(chatRoom, "Carol");
        User admin = new AdminUser(chatRoom, "Admin");

        // Register with mediator
        chatRoom.addUser(alice);
        chatRoom.addUser(bob);
        chatRoom.addUser(carol);
        chatRoom.addUser(admin);

        // Alice sends a message — she only calls mediator, knows nothing about Bob or Carol
        System.out.println("\n========== Alice sends a message ==========");
        alice.send("Hey everyone, what's up?");

        // Bob replies
        System.out.println("\n========== Bob replies ==========");
        bob.send("All good Alice!");

        // Admin broadcasts
        System.out.println("\n========== Admin broadcasts ==========");
        admin.send("Server maintenance in 10 minutes.");
    }
}
```

**Expected output:**
```
[ChatRoom] Alice joined the room.
[ChatRoom] Bob joined the room.
[ChatRoom] Carol joined the room.
[ChatRoom] Admin joined the room.

========== Alice sends a message ==========
  [Alice] sending: "Hey everyone, what's up?"
[ChatRoom] Routing message from Alice...
  [Bob]         received from Alice: "Hey everyone, what's up?"
  [Carol]       received from Alice: "Hey everyone, what's up?"
  [Admin (admin)] received from Alice: "Hey everyone, what's up?"

========== Bob replies ==========
  [Bob] sending: "All good Alice!"
[ChatRoom] Routing message from Bob...
  [Alice] received from Bob: "All good Alice!"
  [Carol] received from Bob: "All good Alice!"
  [Admin (admin)] received from Bob: "All good Alice!"

========== Admin broadcasts ==========
  [Admin (admin)] sending broadcast
[ChatRoom] Routing message from Admin...
  [Alice] received from Admin: "[ADMIN BROADCAST] Server maintenance in 10 minutes."
  [Bob]   received from Admin: "[ADMIN BROADCAST] Server maintenance in 10 minutes."
  [Carol] received from Admin: "[ADMIN BROADCAST] Server maintenance in 10 minutes."
```

---

**The key thing to internalize, Riyad:** Notice that `alice.send()` never mentions Bob or Carol anywhere. Alice literally doesn't know they exist. She just hands the message to the ChatRoom and says "deal with it." That's the entire point.

**Real-world uses:** Swing/JavaFX UI components (button clicks routed through a controller), air traffic control systems, multiplayer game servers coordinating players.

Which one's next — Strategy, Template Method, Command, or State?