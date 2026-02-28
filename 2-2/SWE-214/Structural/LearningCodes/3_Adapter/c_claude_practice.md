# 3. ADAPTER PATTERN

---

## Problem 1 — Payment Gateway
Your system uses `PaymentProcessor` interface but you have a `ThirdPartyPayPal` class with a different method signature. Adapt it.

```java
// Target Interface (what your system expects)
interface PaymentProcessor {
    void processPayment(String currency, double amount);
}

// Adaptee 1 (ThirdParty - can't modify)
class ThirdPartyPayPal {
    public void makePayment(double usdAmount) {
        System.out.println("PayPal: Processing $" + usdAmount + " USD");
    }
}

// Adaptee 2
class ThirdPartyStripe {
    public void charge(String token, int amountInCents) {
        System.out.println("Stripe: Charging " + amountInCents + " cents (token: " + token + ")");
    }
}

// Adaptee 3
class ThirdPartyCrypto {
    public void sendCrypto(String coin, double value) {
        System.out.println("Crypto: Sending " + value + " " + coin);
    }
}

// Adapters
class PayPalAdapter implements PaymentProcessor {
    private ThirdPartyPayPal paypal;
    public PayPalAdapter(ThirdPartyPayPal p) { this.paypal = p; }
    public void processPayment(String currency, double amount) {
        System.out.println("Adapter: Converting " + currency + " to USD...");
        paypal.makePayment(amount);
    }
}

class StripeAdapter implements PaymentProcessor {
    private ThirdPartyStripe stripe;
    public StripeAdapter(ThirdPartyStripe s) { this.stripe = s; }
    public void processPayment(String currency, double amount) {
        int cents = (int)(amount * 100);
        stripe.charge("tok_" + currency, cents);
    }
}

class CryptoAdapter implements PaymentProcessor {
    private ThirdPartyCrypto crypto;
    public CryptoAdapter(ThirdPartyCrypto c) { this.crypto = c; }
    public void processPayment(String currency, double amount) {
        crypto.sendCrypto(currency, amount);
    }
}

public class PaymentDemo {
    public static void main(String[] args) {
        PaymentProcessor[] processors = {
            new PayPalAdapter(new ThirdPartyPayPal()),
            new StripeAdapter(new ThirdPartyStripe()),
            new CryptoAdapter(new ThirdPartyCrypto())
        };

        processors[0].processPayment("BDT", 100.00);
        processors[1].processPayment("USD", 49.99);
        processors[2].processPayment("BTC", 0.002);
    }
}
```
**Output:**
```
Adapter: Converting BDT to USD...
PayPal: Processing $100.0 USD
Stripe: Charging 4999 cents (token: tok_USD)
Crypto: Sending 0.002 BTC
```

---

## Problem 2 — Media Player
Old `AudioPlayer` plays MP3. New system needs to also play MP4 and VLC using an adapter.

```java
// Target
interface MediaPlayer {
    void play(String fileType, String fileName);
}

// Advanced / Adaptee interface
interface AdvancedMediaPlayer {
    void playMp4(String fileName);
    void playVlc(String fileName);
}

// Concrete Adaptees
class Mp4Player implements AdvancedMediaPlayer {
    public void playMp4(String fileName) {
        System.out.println("MP4 Player: Playing " + fileName);
    }
    public void playVlc(String fileName) { /* not supported */ }
}

class VlcPlayer implements AdvancedMediaPlayer {
    public void playMp4(String fileName) { /* not supported */ }
    public void playVlc(String fileName) {
        System.out.println("VLC Player: Playing " + fileName);
    }
}

// Adapter
class MediaAdapter implements MediaPlayer {
    private AdvancedMediaPlayer advancedPlayer;

    public MediaAdapter(String fileType) {
        if (fileType.equals("mp4")) advancedPlayer = new Mp4Player();
        else if (fileType.equals("vlc")) advancedPlayer = new VlcPlayer();
    }

    public void play(String fileType, String fileName) {
        if (fileType.equals("mp4")) advancedPlayer.playMp4(fileName);
        else if (fileType.equals("vlc")) advancedPlayer.playVlc(fileName);
    }
}

// Client - AudioPlayer (uses adapter internally)
class AudioPlayer implements MediaPlayer {
    public void play(String fileType, String fileName) {
        if (fileType.equals("mp3")) {
            System.out.println("AudioPlayer: Playing MP3 - " + fileName);
        } else if (fileType.equals("mp4") || fileType.equals("vlc")) {
            MediaAdapter adapter = new MediaAdapter(fileType);
            adapter.play(fileType, fileName);
        } else {
            System.out.println("Unsupported format: " + fileType);
        }
    }
}

public class MediaPlayerDemo {
    public static void main(String[] args) {
        AudioPlayer player = new AudioPlayer();
        player.play("mp3", "song.mp3");
        player.play("mp4", "video.mp4");
        player.play("vlc", "movie.vlc");
        player.play("avi", "clip.avi");
    }
}
```
**Output:**
```
AudioPlayer: Playing MP3 - song.mp3
MP4 Player: Playing video.mp4
VLC Player: Playing movie.vlc
Unsupported format: avi
```

---

## Problem 3 — Temperature Sensor
Old sensor gives Fahrenheit. New system needs Celsius. Adapt it.

```java
// Target
interface TemperatureSensor {
    double getTemperatureCelsius();
    String getLocation();
}

// Adaptee (old legacy sensor - can't modify)
class LegacyFahrenheitSensor {
    private String sensorId;
    private double tempF;

    public LegacyFahrenheitSensor(String id, double tempF) {
        this.sensorId = id; this.tempF = tempF;
    }
    public double readFahrenheit() { return tempF; }
    public String getSensorId()   { return sensorId; }
}

// Adapter
class FahrenheitToCelsiusAdapter implements TemperatureSensor {
    private LegacyFahrenheitSensor sensor;

    public FahrenheitToCelsiusAdapter(LegacyFahrenheitSensor sensor) {
        this.sensor = sensor;
    }

    public double getTemperatureCelsius() {
        return (sensor.readFahrenheit() - 32) * 5.0 / 9.0;
    }

    public String getLocation() { return sensor.getSensorId(); }
}

// Client
class WeatherStation {
    public void printReport(TemperatureSensor sensor) {
        System.out.printf("Sensor [%s]: %.2f°C%n",
            sensor.getLocation(), sensor.getTemperatureCelsius());
    }
}

public class TemperatureDemo {
    public static void main(String[] args) {
        LegacyFahrenheitSensor s1 = new LegacyFahrenheitSensor("Roof-01",    98.6);
        LegacyFahrenheitSensor s2 = new LegacyFahrenheitSensor("Basement-02", 68.0);
        LegacyFahrenheitSensor s3 = new LegacyFahrenheitSensor("Garden-03",  77.0);

        WeatherStation station = new WeatherStation();
        station.printReport(new FahrenheitToCelsiusAdapter(s1));
        station.printReport(new FahrenheitToCelsiusAdapter(s2));
        station.printReport(new FahrenheitToCelsiusAdapter(s3));
    }
}
```
**Output:**
```
Sensor [Roof-01]: 37.00°C
Sensor [Basement-02]: 20.00°C
Sensor [Garden-03]: 25.00°C
```

---
---
