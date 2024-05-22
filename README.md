# EVM

A project to simulate an electronic voting machine using the microcontroller ESP32 as part of the course 19CCE201 - Microcontrollers & Interfacing Techniques. The external peripherals such as LCD for displaying candidates and their votes, LED for indicating button press, and switches acting as buttons for each candidates are connected to ESP32.

The embedded code used to program the microcontroller ESP32 in a simulating software environment such as Proteus is written using Arduino IDE. The program code presets the value of the no. of candidates in a selected constituency. It is assumed to be 3 and hardcoded in the program.

The final results of the voting processs are printed in a virtual terminal connected to the microcontroller by displaying the winning candidate's name and the no.of votes obtained by the candidate.

The project documentation contains additional details on the project, the working of the EVM and also a reference circuit model for simulation in Proteus.
