# Vending Machine
This program implements the class class representing a coin-accepting and dispensing machine.
The initial homework task was to: 
Accept coins from the user (calculate the amount inserted and count the available coins),
subtract from the money inserted the amount for which the product was purchased (the product price was given in the main when "buying a product"),
Spend the change

Some time after I submitting this program as my homework I decided to upgrade the program, so now there are 2 two types of vendings machines. (CoffeeMachine and SnackMachine)
That means, there are now 2 classes which inherit after the abstract class - vendingMachine(). 
Addictionally, there is a list of product user can choose from with given prices (not like I have done for my homework version (writing the price of the product by hand).

The vending machine only accepts coin payments, itself having a pool of 10 coins available from the start.
Available and valid denominations are 10gr, 20gr, 50gr, 1 zl, 2zl, 5zl, 10zl, 20zl, 50zl, 100zl.
denominations and their available number in a machine are implemented in a map.


# Maybe I will add in a future
It is worth noting that the algorithm I use is using a greedy method and in denominations used by me there always there is the way to give the change (if there was an infinite amout of them in the machine).
However, it is not the most optimal way to give the change, as it can result in Vending Machine being out of small types of denominations quickly.
The idea is to change the algorithm to a dynamic one.

Second thing I can upgrade is to to use int instead of float to store the denominations (store them in gr not zl), because it can lead to some mistakes.

Next aspect of this project to be changed is error handling. 
The initial version of this project was using try catch. However, I do not feel confident using try catch yet and I need more time to research the topic.

# What I have learned from this project
During this project i practised the inheritance of classes in C++, and usage of map structure.
