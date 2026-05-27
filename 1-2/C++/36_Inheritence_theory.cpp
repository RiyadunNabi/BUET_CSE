/*
Inheritance in C++ an Overview
i.   Reusability is a very important feature of OOPs
ii.  In C++ we can reuse a class and add additional features to it
iii. Reusing classes saves time and money
iv.  Reusing already tested and debugged classes will save a lot of effort of developing and debugging the same thing again


What is Inheritance in C++?
i.   The concept of reusability in C++ is supported using inheritance
ii.  We can reuse the properties of an existing class by inheriting it
iii. The existing class is called a base class
iv.  The new class which is inherited from the base class is called a derived class
v.   Reusing classes saves time and money
vi.  There are different types of inheritance in C++


Forms of Inheritance in C++
i.   Single Inheritance
ii.  Multiple Inheritance
iii. Hierarchical Inheritance
iv.  Multilevel Inheritance
v.   Hybrid Inheritance


i)   Single Inheritance in C++
Single inheritance is a type of inheritance in which a derived class is inherited with only one base class. 
For example, we have two classes “employee” and “programmer”. 
If the “programmer” class is inherited from the “employee” class 
which means that the “programmer” class can now implement the functionalities of the “employee” class.

ii)  Multiple Inheritances in C++
Multiple inheritances are a type of inheritance in which one derived class is inherited with more than one base class. 
For example, we have three classes “employee”, “assistant” and “programmer”. 
If the “programmer” class is inherited from the “employee” and “assistant” class 
which means that the “programmer” class can now implement the functionalities of the “employee” and “assistant” class.

iii) Hierarchical Inheritance
A hierarchical inheritance is a type of inheritance in which several derived classes are inherited from a single base class. 
For example, we have three classes “employee”, “manager” and “programmer”. 
If the “programmer” and “manager” classes are inherited from the “employee” class 
which means that the “programmer” and “manager” class can now implement the functionalities of the “employee” class.

iv)  Multilevel Inheritance in C++
Multilevel inheritance is a type of inheritance in which one derived class is inherited from another derived class. 
For example, we have three classes “animal”, “mammal” and “cow”. 
If the “mammal” class is inherited from the “animal” class and “cow” class is inherited from “mammal” 
which means that the “mammal” class can now implement the functionalities of “animal” and “cow” class can now implement the functionalities of “mammal” class.

v)   Hybrid Inheritance in C++
Hybrid inheritance is a combination of multiple inheritance and multilevel inheritance. 
In hybrid inheritance, a class is derived from two classes as in multiple inheritances. 
However, one of the parent classes is not a base class. For example, we have four classes “animal”, “mammal”, “bird”, and “bat”. 
If “mammal”  and “bird” classes are inherited from the “animal” class and “bat” class is inherited from “mammal” and “bird” classes 
which means that “mammal” and “bird” classes can now implement the functionalities of “animal” class and 
“bat” class can now implement the functionalities of “mammal” and “bird” classes.

*/