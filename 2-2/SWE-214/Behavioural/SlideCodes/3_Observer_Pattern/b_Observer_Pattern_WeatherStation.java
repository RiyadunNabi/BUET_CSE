import java.util.ArrayList;
import java.util.List;

// =========================
// 1. The Interfaces
// =========================

interface Observer {
    // All displays must implement this to get updates
    void update(float temp, float humidity, float pressure);
}

interface Subject {
    // Methods to register and remove observers
    void registerObserver(Observer o);
    void removeObserver(Observer o);
    // Method to tell everyone the state has changed
    void notifyObservers();
}

interface DisplayElement {
    void display();
}

// =========================
// 2. The Subject (The Publisher)
// =========================

class WeatherData implements Subject {
    // We keep a list of observers (Subscribers)
    private List<Observer> observers;
    private float temperature;
    private float humidity;
    private float pressure;

    public WeatherData() {
        observers = new ArrayList<>();
    }

    @Override
    public void registerObserver(Observer o) {
        observers.add(o);
    }

    @Override
    public void removeObserver(Observer o) {
        observers.remove(o);
    }

    @Override
    public void notifyObservers() {
        // THE MAGIC: Loop through the list and update everyone.
        // We don't care if it's a ForecastDisplay or a HeatIndexDisplay.
        // We just know it's an 'Observer'.
        for (Observer observer : observers) {
            observer.update(temperature, humidity, pressure);
        }
    }

    public void measurementsChanged() {
        notifyObservers();
    }

    // Simulate new data coming from sensors
    public void setMeasurements(float temperature, float humidity, float pressure) {
        this.temperature = temperature;
        this.humidity = humidity;
        this.pressure = pressure;
        measurementsChanged();
    }
}

// =========================
// 3. The Observers (The Subscribers)
// =========================

class CurrentConditionsDisplay implements Observer, DisplayElement {
    private float temperature;
    private float humidity;
    private Subject weatherData;

    public CurrentConditionsDisplay(Subject weatherData) {
        this.weatherData = weatherData;
        // AUTOMATIC REGISTRATION: I want to listen immediately
        weatherData.registerObserver(this);
    }

    @Override
    public void update(float temp, float humidity, float pressure) {
        this.temperature = temp;
        this.humidity = humidity;
        display();
    }

    @Override
    public void display() {
        System.out.println("Current conditions: " + temperature 
                           + "F degrees and " + humidity + "% humidity");
    }
}

class StatisticsDisplay implements Observer, DisplayElement {
    private float maxTemp = 0.0f;
    private float minTemp = 200;
    private float tempSum = 0.0f;
    private int numReadings;
    private Subject weatherData;

    public StatisticsDisplay(Subject weatherData) {
        this.weatherData = weatherData;
        weatherData.registerObserver(this);
    }

    @Override
    public void update(float temp, float humidity, float pressure) {
        tempSum += temp;
        numReadings++;

        if (temp > maxTemp) maxTemp = temp;
        if (temp < minTemp) minTemp = temp;

        display();
    }

    @Override
    public void display() {
        System.out.println("Avg/Max/Min temperature = " + (tempSum / numReadings) 
                           + "/" + maxTemp + "/" + minTemp);
    }
}

class ForecastDisplay implements Observer, DisplayElement {
    private float currentPressure = 29.92f;
    private float lastPressure;
    private Subject weatherData;

    public ForecastDisplay(Subject weatherData) {
        this.weatherData = weatherData;
        weatherData.registerObserver(this);
    }

    @Override
    public void update(float temp, float humidity, float pressure) {
        lastPressure = currentPressure;
        currentPressure = pressure;
        display();
    }

    @Override
    public void display() {
        System.out.print("Forecast: ");
        if (currentPressure > lastPressure) {
            System.out.println("Improving weather on the way!");
        } else if (currentPressure == lastPressure) {
            System.out.println("More of the same");
        } else {
            System.out.println("Watch out for cooler, rainy weather");
        }
    }
}

// =========================
// 4. Main Driver Class
// =========================

public class b_Observer_Pattern_WeatherStation {
    public static void main(String[] args) {
        WeatherData weatherData = new WeatherData();

        // Create displays (they automatically register themselves in their constructor)
        CurrentConditionsDisplay currentDisplay = new CurrentConditionsDisplay(weatherData);
        StatisticsDisplay statisticsDisplay = new StatisticsDisplay(weatherData);
        ForecastDisplay forecastDisplay = new ForecastDisplay(weatherData);

        System.out.println("\n--- First Weather Update: 80F, 65% humidity, 30.4 pressure ---");
        weatherData.setMeasurements(80, 65, 30.4f);

        System.out.println("\n--- Second Weather Update: 82F, 70% humidity, 29.2 pressure ---");
        weatherData.setMeasurements(82, 70, 29.2f);

        System.out.println("\n--- Third Weather Update: 78F, 90% humidity, 29.2 pressure ---");
        weatherData.setMeasurements(78, 90, 29.2f);
        
        // Bonus: Remove a display dynamically
        System.out.println("\n--- Removing Statistics Display ---");
        weatherData.removeObserver(statisticsDisplay);
        
        System.out.println("--- Fourth Weather Update ---");
        weatherData.setMeasurements(60, 40, 28.5f);
        // Notice StatisticsDisplay does NOT print anything here!
    }
}



// --- First Weather Update: 80F, 65% humidity, 30.4 pressure ---
// Current conditions: 80.0F degrees and 65.0% humidity
// Avg/Max/Min temperature = 80.0/80.0/80.0
// Forecast: Improving weather on the way!

// --- Second Weather Update: 82F, 70% humidity, 29.2 pressure ---
// Current conditions: 82.0F degrees and 70.0% humidity
// Avg/Max/Min temperature = 81.0/82.0/80.0
// Forecast: Watch out for cooler, rainy weather

// --- Third Weather Update: 78F, 90% humidity, 29.2 pressure ---
// Current conditions: 78.0F degrees and 90.0% humidity
// Avg/Max/Min temperature = 80.0/82.0/78.0
// Forecast: More of the same

// --- Removing Statistics Display ---
// --- Fourth Weather Update ---
// Current conditions: 60.0F degrees and 40.0% humidity
// Forecast: Watch out for cooler, rainy weather