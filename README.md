# Trenchcoatinator

Project built using C++20 and Qt5 with a strong emphasis on OOP principles, simulating a trenchcoat shop management app having two main modes:

- Admin Mode - used to administrate and visualize the shop's stock of trenchcoats. Basic CRUD
operations are operations are provided, along with a statistic view of the stock. The trenchcoat
stock can be represented as a text file or a SQL database.

- User Mode - used to present trenchcoats to the user to buy, tracking the shopper's bought coats. 
The logged shopping basket can be stored in HTML or CSV.

# Object-Oriented Programming & Design Patterns
The program follows a layered architecture, facilitating flexibilty and extensibility.
Therefore, each part of the program can be easily replaced or modified.

The usage of concepts such as inheritance, polymorphism or templates, combined 
with the utilization of design patterns such as Command, Factory or MVC make the program's 
architecture versatile, while still easy to use. 

Therefore, layers such as data input/manipulation/output and user interface are abstracted 
away and we can choose between several user interfaces (text/graphical), data sources (text/SQL)
or output formats (HTML/CSV) with ease.

The design patterns make complicated things look easy. Factories help with the program's 
initialization, commands encapsulate operations and allow for better control (e.g. operation undo/redo), while the Model-View-Controller (used in the whole app, and more specifically in the database's table view+model+delegate implementation) brings everything together.

A part of the project's architecture can be seen in the UML diagram for a simplified text 
based UI app version at [`docs/Trenchcoatinator.svg`](https://github.com/thesstefan/trenchcoatinator/master/docs/Trenchcoatinator.svg').

# Installation and Usage
The project assumes that Qt5 and a compiler supporting C++20 is installed. If this is satisfied,
the project must be simply cloned and compiled using your preferred IDE and the provided qmake file. Assuming a shell environment this is easily done by executing
```bash
git clone git@github.com:thesstefan/trenchcoatinator.git && cd trenchcoatinator
qmake && make -jX
./trenchcoatinator
```
where `X` is the recommended to be your CPU's core count. 

# Screenshots

## Admin Mode
<p align="center">
  <img src="https://github.com/thesstefan/trenchcoatinator/blob/master/readme/admin.png" alt="User Mode Screenshot"/>
</p>

## User Mode
<p align="center">
  <img src="https://github.com/thesstefan/trenchcoatinator/blob/master/readme/user.png" alt="User Mode Screenshot"/>
</p>
