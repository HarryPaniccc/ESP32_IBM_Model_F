/*
Author: Harry Papanicolaou
Date: 19/02/2025

this code reads in the data line of a IBM Model F keyboard on the falling edge of its clock, but is also kinda a playground to mess with things
guided by information from https://github.com/tmk/tmk_keyboard/wiki/IBM-PC-XT-Keyboard-Protocol#8088-irq1interrupt-09h

*/

// Setting the GPIO pin numbers for the clk and data lines. For my purposes GPIO12 is clk and GPIO13 is da.
int keyboard_clk = 12;
int keyboard_data = 13;
int previous_clk = 0; // The value of the clock before the current, used to detect falling edges.
int data_bit_number = 0; // Which bit of data are we reading.

// the setup routine runs once when you press reset:
void setup() {

  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  
  // make the pushbutton's pin an input:
  pinMode(keyboard_clk, INPUT);
  pinMode(keyboard_data, INPUT);

}

// the loop routine runs over and over again forever:
void loop() {


  int current_clk = digitalRead(keyboard_clk);  // read the clock value

  if (current_clk == 0 && previous_clk == 1){ // does something on a falling edge
    
  
  }

  previous_clk = digitalRead(keyboard_clk);

  // print out the state of the button:
  Serial.println(buttonState);
  delay(1);  // delay in between reads for stability
}
