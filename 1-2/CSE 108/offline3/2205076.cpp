#include <iostream>
#include <cstring>
using namespace std;
class Planet
{
    char *name;   // Pointer for the name of the planet
    int distance; // Distance from the sun in millions of kilometers
public:
    Planet()
    {
        name = new char[1];
        name[0] = '\0';
        distance = 0;
    }
    Planet(const char *planetName, int dist)
    {
        name = new char[strlen(planetName) + 1];
        strcpy(name, planetName);
        distance = dist;
    }
    Planet(const Planet &other)
    {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        distance = other.distance;
    }
    Planet &operator=(const Planet &p)
    {
        if (this == &p)
        {
            return *this;
        }

        delete name;
        name = new char[strlen(p.name) + 1];
        strcpy(this->name, p.name);
        distance = p.distance;
        return *this;
    }
    Planet operator+(const Planet &p) const
    {
        char *newName = new char[strlen("Combined") + 1];
        strcpy(newName, "Combined");
        int d = distance + p.distance;
        // cout << d << " " << distance << " " << p.distance << endl;
        return Planet(newName, d);
    }
    // Planet &operator+=(int dist)
    // {
    //     distance += dist;
    //     return *this;
    // }

    int operator<(Planet &q)
    {
        return distance<q.distance;
    }
    void display()
    {
        cout << "Planet: " << name << ", Distance: " << distance << " million km\n";
    }

    // Method to get the planet name
    const char *getName()
    {
        return name;
    }
    friend Planet operator+(int dist, const Planet &p);
    ~Planet()
    {
        delete[] name;
    }
};
Planet operator+(int dist, const Planet &p)
{
    return Planet(p.name, dist + p.distance);
}

class SolarSystem
{
    Planet planets[10];
    int planetCount;

public:
    SolarSystem()
    {
        planetCount = 0;
    }
    // Add a planet to the solar system
    void addPlanet(const char *name, int distance)
    {
        if (planetCount < 10)
        {
            Planet p(name, distance);
            planets[planetCount] = p;
            planetCount++;
        }
        else
        {
            cout << "Solar system is full. Can't add more planets.\n";
        }
    }
    Planet &operator[](int a)
    {
        return planets[a];
    }
    Planet &operator[](const char *c)
    {
        int a = 1;
        while (a<planetCount && strcmp(planets[a].getName(), c))  //strcmp returns 0 when it finds equality
        {
            a++;
        }
        // if (a == planetCount)
        // {
        //     cout << "Planet not found!\n";
        //     // Optionally, throw an exception or return a reference to a dummy planet.
        //     static Planet dummy("Unknown", 0);
        //     return dummy;
        // }
        return planets[a];
    }
    
};
int main()
{
    SolarSystem solarSystem;
    // Add planets to the solar system
    solarSystem.addPlanet("Invalid", -1);
    solarSystem.addPlanet("Sun", 0);
    solarSystem.addPlanet("Earth", 150);
    solarSystem.addPlanet("Mars", 228);
    // Display all planets in the solar system
    solarSystem[1].display();
    solarSystem[2].display();
    solarSystem[3].display();

    solarSystem[3] = 140 + solarSystem[3];
    solarSystem[3].display();
    Planet p = solarSystem["Earth"] + solarSystem["Mars"];
    p.display();
    if (solarSystem[2] < solarSystem[3])
    {
        cout << "Earth is closer to the Sun than Mars\n";
    }
    else
    {
        cout << "Mars is closer to the Sun than Earth\n";
    }
    p = solarSystem[1];
    p.display();

    return 0;
}
