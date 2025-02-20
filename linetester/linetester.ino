/*
Author: Harry Papanicolaou
Date: 19/02/2025

this code reads in the data line of a IBM Model F keyboard on the falling edge of its clock, but is also kinda a playground to mess with things
guided by information from https://github.com/tmk/tmk_keyboard/wiki/IBM-PC-XT-Keyboard-Protocol#8088-irq1interrupt-09h

*/

// Setting the GPIO pin numbers for the clk and data lines. For my purposes GPIO12 is clk and GPIO13 is da.
int keyboard_clk = 25;
int keyboard_data = 26; //Note: Keeping these both ints because like I dont want to fuckaround and find out

uint16_t output_character_code = 0; /* The data is sent supposedly in 8 bits plus 2 start bits on the front.
                                      So on interrupt we should read in data and feed the last integer of data out into the serial port.
*/

int previous_clk = 0; // The value of the clock before the current, used to detect falling edges. Unnecessary?
int data_bit_number = 0; // Which bit of data are we reading. Only goes up to 10 so like we really dont need anything big.


// the setup routine runs once when you press reset:

void IRAM_ATTR clock_falling_edge(){
  // output_character_code = (output_character_code >> 1) + (digitalRead(keyboard_data) << 7); //FREAKY mode
  output_character_code = (output_character_code << 1) + digitalRead(keyboard_data); // NORMAL mode

  data_bit_number++; //increment the bit by 1. If it reaches 10, we need to reset it.
}



void setup() {

  // initialize serial communication at 115200 bits per second:
  //supposedly instructions happen once every 2.5 uS = 400 000 times a second

  Serial.begin(9600); //TODO: Maybe the baud rate needs to be upped? I think scaling it makes sense, but lets be sure about that first.
  
  // Set the pins to inputs/interrupts:

  pinMode(keyboard_clk, INPUT);
  attachInterrupt(keyboard_clk, clock_falling_edge, FALLING);

  pinMode(keyboard_data, INPUT);

}

// the loop routine runs over and over again forever:
void loop() {

  //Using interrupts maybe we can have an interrupt on clock change > disable interrupts for process > reenable interrupts once recorded information?

  if (data_bit_number >= 10){
    // Serial.println("bit number = " + data_bit_number);
    Serial.println(output_character_code, BIN);
    data_bit_number = 0;
    output_character_code = 0;
  }
}
