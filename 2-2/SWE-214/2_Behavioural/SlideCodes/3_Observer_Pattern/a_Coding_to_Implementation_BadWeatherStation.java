// =========================
// THE PROBLEM: Coding to Implementation
// =========================

class CurrentConditionsDisplay {
    public void update(float temp, float humidity, float pressure) {
        System.out.println("Current conditions: " + temp + "F degrees and " + humidity + "% humidity");
    }
}

class StatisticsDisplay {
    public void update(float temp, float humidity, float pressure) {
        System.out.println("Avg/Max/Min temperature = " + temp + "/" + temp + "/" + temp); 
    }
}

class ForecastDisplay {
    public void update(float temp, float humidity, float pressure) {
        System.out.println("Forecast: More of the same");
    }
}

class WeatherData {
    // PAIN POINT 1: We have to hardcode the instance variables for every display
    CurrentConditionsDisplay currentDisplay;
    StatisticsDisplay statisticsDisplay;
    ForecastDisplay forecastDisplay;

    public WeatherData() {
        currentDisplay = new CurrentConditionsDisplay();
        statisticsDisplay = new StatisticsDisplay();
        forecastDisplay = new ForecastDisplay();
    }

    public void measurementsChanged(float temp, float humidity, float pressure) {
        // PAIN POINT 2: We must manually update each one.
        // If we add a 4th display, we have to CHANGE this code.
        currentDisplay.update(temp, humidity, pressure);
        statisticsDisplay.update(temp, humidity, pressure);
        forecastDisplay.update(temp, humidity, pressure);
    }
}

public class a_Coding_to_Implementation_BadWeatherStation {
    public static void main(String[] args) {
        WeatherData weatherData = new WeatherData();
        weatherData.measurementsChanged(80, 65, 30.4f);
    }
}