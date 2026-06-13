package Practice_2;

class Animal {
    private String name;
    private int age;
    
    public Animal(String name, int age) {
        this.name = name;
        this.age = age;
    }

    @Override
    public String toString() {
        return "Animal [name=" + name + ", age=" + age + "]";
    }
    
    // your code
    public boolean isLethalToAdultHumans()
    {
        return true;
    }
    
}

// your code
class Bird extends Animal
{
    Bird(String name, int age)
    {
        super(name, age);
    }
}
class Mammal extends Animal
{
    Mammal(String name, int age)
    {
        super(name, age);
    }

    public void printBloodType()
    {
        System.out.println("Warm-Blooded");
    }
}
class Reptile extends Animal
{
    Reptile(String name, int age)
    {
        super(name, age);
    }
}
class Fish extends Animal
{
    Fish(String name, int age)
    {
        super(name, age);
    }
}
class Arachnid extends Animal
{
    Arachnid(String name, int age)
    {
        super(name, age);
    }
}

class Albatross extends Bird
{
    Albatross(String name, int age)
    {
        super(name, age);
    }
}

class Dog extends Mammal
{
    Dog(String name, int age)
    {
        super(name, age);
    }
}
class FruitBat extends Mammal
{
    FruitBat(String name, int age)
    {
        super(name, age);
    }
}
class Platypus extends Mammal
{
    Platypus(String name, int age)
    {
        super(name, age);
    }
}
class Human extends Mammal
{
    Human(String name, int age)
    {
        super(name, age);
    }
}

class EasternBrownSnake extends Reptile
{
    EasternBrownSnake(String name, int age)
    {
        super(name, age);
    }
}
class GreatWhiteShark extends Fish
{
    GreatWhiteShark(String name, int age)
    {
        super(name, age);
    }
}
class RedBackSpider extends Arachnid
{
    RedBackSpider(String name, int age)
    {
        super(name, age);
    }
}




public class Main {
    public static void main(String[] args) {
        Bird alex = new Albatross("Alex", 39);
        Mammal spot = new Dog("Spot", 7);
        Mammal fred = new FruitBat("Fred", 10);
        Reptile steph = new EasternBrownSnake("Steph", 12);
        Fish bruce = new GreatWhiteShark("Bruce", 40);
        Arachnid charlotte = new RedBackSpider("Charlotte", 1);
        Mammal perry = new Platypus("Perry", 5);
        Mammal bob = new Human("Bob", 20);

        Animal[] animals = { alex, spot, fred, steph, bruce, charlotte, perry, bob };
        for (Animal a : animals) {
            System.out.print(a);
            if (a instanceof Mammal) {
                ((Mammal) a).printBloodType();
            }
            if (a.isLethalToAdultHumans()) {
                System.out.print(", and it's lethal!");
            }
            System.out.println();
        }
        System.out.println();
    }
}

/* Output
Alexis a Albatross, aged 39
Spotis a Dog, aged 7, Warm-Blooded!
Fredis a FruitBat, aged 10, Warm-Blooded!
Stephis a EasternBrownSnake, aged 12, and it's lethal!
Bruceis a GreatWhiteShark, aged 40
Charlotteis a RedBackSpider, aged 1, and it's lethal!
Perryis a Platypus, aged 5, Warm-Blooded!
Bobis a Human, aged 20, Warm-Blooded!
*/
