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
 + saves the student currently loaded into memory to file

```add [category] [name] [grade] [max]```
+ adds a new entry based on arguments, where: 
  + ```[category]``` is the type of assignment it is
  + ```[name]``` is the name of the assignment
  + ```[grade]``` is the number of points earned on the assignment
  + ```[max]``` is the maximum number of potential points that can be achieved on the assignment



# CLASSES & METHODS

## Gradebook

### Data members

### Methods


 
 
