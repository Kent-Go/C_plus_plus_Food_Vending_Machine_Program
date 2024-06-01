## C++ Food Vending Machine Program - Group + Individual Enhancement

### Overview

Advanced programming technique’s course project developed in C++ for user to view food menu, purchase meal, save menu and balance into .dat file. Functionalities Include adding new food, removing existing food, viewing vending machine’s balance and enable/disable help message are available for admin users. Doubly-linked lists and Vector ADT are used for efficient insertion, deletion, accessor and mutator methods of food and balance data. C++14 pointers and heap memory are utilised for dynamic memory allocation. Command design pattern is used for main menu options to adhere to single responsibility, and open/closed principles. Testings are conducted to ensure appropriate exception handling and program behaviour. Achieved “High Distinction” grade for the project.

### Individual Enhancement
- Minor Enhancement:
  - 4.1.1 Help!
 
    Whenever there is a user prompt, the user may type “help” and the program should display some text to help
    the user determine what they commands they may execute. This enhancement could be enable/disable at runtime.
- Major Enhancement:
  - 4.2.2 Doubly-linked list
 
    Re-implement your singly-linked-list for your ftt into a doubly-linked list, where you can navigate either in
    forward or backward direction on the list. In fact, you can start traversing the list from either the start or the
    end of the list now. Your functionalities for ftt as described in Section 2 should remain the same. For your
    implementation, you need to demonstrate that for both “inserting” and “removing” items functionalities, your
    doubly-linked list should be functional accordingly.

  - 4.2.3 Reimplement the main menu using the Command design pattern
 
    Design patterns are examples of common solutions to a problem that have been distilled into recommended
    approaches. With this extension you will use the Command pattern which is an object-oriented approach that
    uses inheritance to model menu items with text and a callable function. Please see this webpage:
    https://refactoring.guru/design-patterns/command
    for a further explanation. Please note that while the example provided uses the idea of ‘buttons’, it can just as
    easily be applied to menu items.

### Information for compiling and running the program

To compile the program, you need to run the following command:

```make```

To run the program, you need to first read the data from the files foods.dat and coins.dat by running the following command:

```./ftt foods.dat coins.dat```

To run the program with the test files, you need to run the following command:

```
./ftt foods.dat coins.dat < <testname>.input > <testname>.actual_output
diff -w <testname>.expected_output <testname>.actual_output
diff -w -y <testname>.expected_coins <actual_saved_coins>
```

For test *req-5-purchase-meal-cannot-refund*, which tests when the system cannot refund the user purchasing a meal, the data file for the coins should be **nocoins.dat**, which will load no coins into the system.
```
./ftt foods.dat nocoins.dat < req-5-purchase-meal-cannot-refund.input > req-5-purchase-meal-cannot-refund.actual_output
```
