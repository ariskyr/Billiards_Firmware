# Billiards project using an arduino Uno Board

simple project to learn how to code a simple automatic billiards table.
Using C++ and arduino IDE.
Detailed instructions on the development and simulation of the program can be found in report.pdf which is written in greek.
## Executing Program

Arduino IDE to run. You can also simulate it through here:

[Wokwi Simulator](https://wokwi.com/arduino/projects/318524296632730177)

Start the simulation, it will start counting down to simulate the coin acceptor.

Every push of the button sends an impulse, 1 pulse equals 2 euros, 2 pulses 1 euro etc
After 5 euros have been placed, a game will start with a random sequence of balls placed to show the correct usage of the program. After a black ball is detected, the game ends adding the game price to the total and incrementing the games played.
## Dependencies

My implementation uses the TM1637 Display to output the amount of coins are inserted inside the
Coin Acceptor. Inside Arduino IDE go to:
Sketch -> Include Libray -> Manage Libraries
and search for TM1637Display and import it.

## Wifi support

The ESP8266 cant be simulated but the process of configuring it for a localhost goes as follows:

* create an apache server with mysql database using xampp (or any other), then make a table with the following columns:
  * ID
  * b_table
  * money
  * games
  * Timestamp

The file ESPData.php should be included in the database folder (xampp case using phpMyAdmin it should be in htdocs) and creates the connection with the database.
## Module requirements

Code has functionality to simulate the outputs of the modules using the serial monitor but for an actual implementation you will need the following modules:

* Color Sensor TCS3200
* Coin Acceptor CH-926
* Wi-Fi microchip ESP8266
* TM1637 Display
* Dual Motor Driver Module L298N

## Authors

- [@Aris_Kyriakopoulos](https://github.com/SneakyTattas)
- [@Akis S.](https://github.com/Likecinema)

## Versions History

* 1.0
  * Added report in greek - Final

* 0.2
  * ESP8266 implementation for wifi connection to mySQL database

- 0.1
  - Initial Commit
  * Added Readme file

## Known Issues

- singular big commit because version control was not used during the making of the project
* no way of simulating ESP8266 use