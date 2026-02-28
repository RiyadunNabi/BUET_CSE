// ZBazar Delivery Logistics (Bridge Pattern)
// CSE-214 Online - 3 (C2)
// Structural Design Pattern
// Duration: 25 minutes

// ZBazar is an online grocery platform that offers multiple 
// delivery options, as given below:

// Standard Delivery (delivered within 24 hours)
// Express Delivery (delivered within 4 hours)
// Scheduled Delivery (delivered at a chosen time slot)

// Each delivery type has its own pricing logic 
// and estimated delivery time calculation. 
// Regardless of the type, every order must ultimately be dispatched 
// using a physical transportation method. 
// Until now, ZBazar has relied on bike couriers and van deliveries 
// to fulfill orders.
// Recently, however, the company has decided to introduce drone delivery 
// in selected cities to speed up last-mile logistics. 
// As a result, the development team now finds itself updating 
// multiple classes just to support this new transportation method, 
// such as adding drone-specific dispatch logic, tracking integration, 
// safety checks, etc., in several places. 
// The situation is becoming harder to manage because, 
// in the near future, ZBazar is also considering introducing 
// robot delivery for gated communities and smart neighborhoods.

// The challenge is that business policies for delivery types 
// may change frequently, while transport technologies may expand 
// over time. However, the current design tightly couples 
// everything and thus forces code duplication and repeated modifications 
// whenever either dimension changes. 
// Your task is to redesign the system with an appropriate design pattern 
// so that new transport technologies like drones or robots to be 
// introduced without rewriting existing delivery-type logic, 
// and vice versa.


// Implementor - Transport
interface Transport {
    String deliver(String address);
    double calculateTime();
}

// Concrete Implementors
class BikeTransport implements Transport {
    public String deliver(String address) { return "Bike courier to " + address; }
    public double calculateTime() { return 1.0; }
}

class VanTransport implements Transport {
    public String deliver(String address) { return "Van delivery to " + address; }
    public double calculateTime() { return 2.0; }
}

class DroneTransport implements Transport {
    public String deliver(String address) { return "Drone delivery to " + address; }
    public double calculateTime() { return 0.5; }
}

class RobotTransport implements Transport {
    public String deliver(String address) { return "Robot delivery to " + address; }
    public double calculateTime() { return 1.5; }
}

// Abstraction - Delivery Type
abstract class DeliveryType {
    protected Transport transport;
    public DeliveryType(Transport transport) { this.transport = transport; }
    public abstract double getPrice();
    public abstract String getDetails(String address);
}

// Refined Abstractions
class StandardDelivery extends DeliveryType {
    public StandardDelivery(Transport t) { super(t); }
    public double getPrice() { return 50.0; }
    public String getDetails(String address) {
        return "Standard (24hr) | " + transport.deliver(address)
             + " | ETA: " + transport.calculateTime() + "hr(s) | Price: $" + getPrice();
    }
}

class ExpressDelivery extends DeliveryType {
    public ExpressDelivery(Transport t) { super(t); }
    public double getPrice() { return 100.0; }
    public String getDetails(String address) {
        return "Express (4hr) | " + transport.deliver(address)
             + " | ETA: " + transport.calculateTime() + "hr(s) | Price: $" + getPrice();
    }
}

class ScheduledDelivery extends DeliveryType {
    private String timeSlot;
    public ScheduledDelivery(Transport t, String timeSlot) {
        super(t); this.timeSlot = timeSlot;
    }
    public double getPrice() { return 75.0; }
    public String getDetails(String address) {
        return "Scheduled (" + timeSlot + ") | " + transport.deliver(address)
             + " | ETA: " + transport.calculateTime() + "hr(s) | Price: $" + getPrice();
    }
}

// Main
public class b_online_C2_ZBazarDeliveryMain {
    public static void main(String[] args) {
        DeliveryType d1 = new StandardDelivery(new BikeTransport());
        System.out.println(d1.getDetails("House 5, Road 3, Dhaka"));

        DeliveryType d2 = new ExpressDelivery(new DroneTransport());
        System.out.println(d2.getDetails("Gulshan, Dhaka"));

        DeliveryType d3 = new ScheduledDelivery(new RobotTransport(), "6:00 PM");
        System.out.println(d3.getDetails("Dhanmondi, Dhaka"));
    }
}