# Summary
Our task was to create a simple, clean, functional and interactive gradebook program. The basic idea is that the user tells the program what it wants to do with academic records, and the program performs the corresponding action. 

# Planning
This was the initial proposal for the control flow of the program: 
![sydney-flow-chart](https://user-images.githubusercontent.com/123519150/221390111-4a7e2456-e55a-4184-b0ac-c9dad6238da0.png)

Then a slightly updated version:
![kai-review-project-flowchart](https://user-images.githubusercontent.com/123519150/221390061-53dff300-5014-4282-9292-fddafb454ee4.jpeg)

After this, it was a matter of implimenting it, and writing the functions needed to 

# Compiling & running the program
For safest results, compile with C++ 11: other versions of C++ may work, but they have not been tested. Navigate to where the source code is stored: the following line generates the executable, which can be run with ```./gradebook```:

```g++ -o gradebook main.cpp gradebook.cpp -std=c++11```

Make sure to include any ```.grades```files you would like to modify in the same directory so the program can access it. In addition, any additional ```.grades``` files will be stored where the program is being run. 

## What the hecks is a .grades file anyways?

This is simply the way that data is stored in each student's file. The program is written in such a way that the user should never have to go "under the hood" in these files, as any changes are meant to be made with the program. 

## User commands
Here are all of the different commands (with their parameters) the user can input into the program. All commands display an error of some kind if given an improper number of arguments. 
 
```help [command]```
+ no ```[command]``` given: gives a general overview of each command
+ ```[command]``` given: gives an overview of the command [command]

```new [student]```
+ creates a new student with name ```[student]```

```load [student]```
+ *loads* a student ```[student]``` from a corresponding ```.grades``` file

```save```
 + *saves* all of the student's data to file

```add [category] [name] [grade] [max]```
+ *adds* a new entry to the student based on its arguments, where: 
  + ```[category]``` - the type of assignment being **created**
  + ```[name]``` - is the name of the assignment to **create**
  + ```[grade]``` - is the number of points earned on the assignment
  + ```[max]``` - is the maximum number of potential points that can be achieved on the assignment

```modify [category] [name] [newgrade] [newmax]```
+ *modifies* a currently existing assignment based on its arguments, where: 
  + ```[category]``` - the **type** of assignment that is being **modified**
  + ```[name]``` - is the **name** of the assignment to **modify**
  + ```[grade]``` - is the **new** number of points earned on the assignment
  + ```[max]``` - is the **new** maximum number of potential points that can be achieved on the assignment

```delete [category] [name]```
+ *deletes* an entry based on given arguments, where
  + ```[category]``` - the **type** of assignment that is being **deleted**
  + ```[name]``` - is the **name** of the assignment to **deleted**

There are a few variants of the ```print``` command:

```print all [flags]```

+ *prints* all assignments

```print [category] [flags]```

+ *prints* all assignments of **type** ```[category]```

```print [category] [name]```

+ *prints* a **specific** assignment of **type** ```[category]``` and **name** ```[name]```

There are a few optional flags that can be used with the *print* command as well:
+ ```-o``` *prints* course grade but **not** categories or entries (**only** works with ```print all``` variant)
+ ```-c``` *prints* **categories** but **not** entries (**does not** work with ```print [category] [name]``` variant)

```exit```
+ if the user has unfinished progress, they will be given a prompt, then/otherwise closes program

### Some examples of the program in action
![io1](https://user-images.githubusercontent.com/123519150/221448050-f89a25b3-083e-43de-86dd-bd4f104baa80.jpg)
The printed output of all individual, all category, and overall grades of a student named Sydney
![io2](https://user-images.githubusercontent.com/123519150/221448056-47e96407-2d67-4d3a-934a-680dae5f9815.jpg)
The grades of a student named Kai before changes are made with functions
![io3](https://user-images.githubusercontent.com/123519150/221448074-a09a57bc-b08a-4d72-96e6-87a9d5caf5c2.jpg)
The results after calling add, delete, and modify functions
