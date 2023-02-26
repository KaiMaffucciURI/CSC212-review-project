# Introduction
Our task was to create a simple, clean, functional and interactive gradebook program. The basic idea is that the user tells the program what it wants to do with academic records, and the program performs the corresponding action. 

# Compiling the program
For the safest results, compile with C++ 11: other versions of C++ may work, but they are not tested. The following line generates the executable, which can be run with ```./gradebook```:

```g++ -o gradebook gradebook.cpp -std=c++11```

# User commands
 Here are all of the different commands (with their parameters) the user can input into the program, and their respective function/method calls. 
 All commands display an error of some kind if given improper arguments. 
 
```help [command]```
+ no ```[command]``` given: gives a general overview of each command
+ ```[command]``` given: gives an overview of the command [command]


```new [student]```
+ creates a new student with name ```[student]```

```load [student]```
+ loads a student ```[student]``` from a corresponding ```.grades``` file

```save```
 + saves all of the student's data to file

```add [category] [name] [grade] [max]```
+ adds a new entry to the student based on its arguments, where: 
  + ```[category]``` - the type of assignment being **created**
  + ```[name]``` - is the name of the assignment to **create**
  + ```[grade]``` - is the number of points earned on the assignment
  + ```[max]``` - is the maximum number of potential points that can be achieved on the assignment

```modify [category] [name] [newgrade] [newmax]```
+ modifies a currently existing assignment based on its arguments, where: 
  + ```[category]``` - the **type** of assignment that is being **modified**
  + ```[name]``` - is the **name** of the assignment to **modify**
  + ```[grade]``` - is the **new** number of points earned on the assignment
  + ```[max]``` - is the **new** maximum number of potential points that can be achieved on the assignment

```delete [category] [name]```
+ **deletes** an entry based on given arguments, where
  + ```[category]``` - the **type** of assignment that is being **deleted**
  + ```[name]``` - is the **name** of the assignment to **deleted**




# Classes & Methods (for developers' eyes)

If you want to take our code and develop it yourself, this documentation will likely be useful. 

## Gradebook

### Data members

### Methods


 
 
