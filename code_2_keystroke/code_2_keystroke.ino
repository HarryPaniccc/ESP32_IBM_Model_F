/*
Author: Harry Papanicolaou
Date: 14/04/2026

This data reads the data code transmitted by an IBM model F keyboard and uses a lookup table to translate it to a keystroke.
This code is built off of the linetester.ino code in the same repo

guided by information from https://github.com/tmk/tmk_keyboard/wiki/IBM-PC-XT-Keyboard-Protocol#8088-irq1interrupt-09h

TODO:
Why does the first keystroke LSB output as 1 on (not boot) POWER ON
Write a lookup table
Why does the random data output occur?
NOTE: where the "0 INS" key should be (where . Del is now) is a dead key. Scroll Lock is also the broken
*/



// Setting the GPIO pin numbers for the clk and data lines. For my purposes GPIO12 is clk and GPIO13 is da.
int keyboard_clk = 25;   // Sets the keyboard clock pin to pin number 25
int keyboard_data = 26;  // Sets the keyboard datas pin to pin number 26


// The character code that the keyboard sends is in this variable.
uint16_t output_character_code = 0; // Code format as: UP/DOWN bit, 8-bit key identifier, end bit (0). To store all values we need 2 bytes, but its only ever 10 bits.
int data_bit_number = 0;  // Which bit of data are we reading. Only goes up to 10 so like we really dont need anything big.


// the setup routine runs once when you press reset:
void IRAM_ATTR clock_falling_edge() {
  output_character_code = output_character_code + (digitalRead(keyboard_data) << data_bit_number);
  data_bit_number++;                                                                                //increment the bit by 1. If it reaches 10, we need to reset it.
}


// Im afraid there is simply no other way...
char code2key(code){
  //need to instantiate output somehow...
  switch(code){
      case 0b0001111010: output = KEY_A_PRESS; break;
      case 0b1001111010: output = KEY_A_RELEASE; break;
      case 0b0011000010: output = KEY_B_PRESS; break;
      case 0b1011000010: output = KEY_B_RELEASE; break;
      case 0b0010111010: output = KEY_C_PRESS; break;
      case 0b1010111010: output = KEY_C_RELEASE; break;
      case 0b0010000010: output = KEY_D_PRESS; break;
      case 0b1010000010: output = KEY_D_RELEASE; break;
      case 0b0001001010: output = KEY_E_PRESS; break;
      case 0b1001001010: output = KEY_E_RELEASE; break;
      case 0b0010000110: output = KEY_F_PRESS; break;
      case 0b1010000110: output = KEY_F_RELEASE; break;
      case 0b0010001010: output = KEY_G_PRESS; break;
      case 0b1010001010: output = KEY_G_RELEASE; break;
      case 0b0010001110: output = KEY_H_PRESS; break;
      case 0b1010001110: output = KEY_H_RELEASE; break;
      case 0b0001011110: output = KEY_I_PRESS; break;
      case 0b1001011110: output = KEY_I_RELEASE; break;
      case 0b0010010010: output = KEY_J_PRESS; break;
      case 0b1010010010: output = KEY_J_RELEASE; break;
      case 0b0010010110: output = KEY_K_PRESS; break;
      case 0b1010010110: output = KEY_K_RELEASE; break;
      case 0b0010011010: output = KEY_L_PRESS; break;
      case 0b1010011010: output = KEY_L_RELEASE; break;
      case 0b0011001010: output = KEY_M_PRESS; break;
      case 0b1011001010: output = KEY_M_RELEASE; break;
      case 0b0011000110: output = KEY_N_PRESS; break;
      case 0b1011000110: output = KEY_N_RELEASE; break;
      case 0b0001100010: output = KEY_O_PRESS; break;
      case 0b1001100010: output = KEY_O_RELEASE; break;
      case 0b0001100110: output = KEY_P_PRESS; break;
      case 0b1001100110: output = KEY_P_RELEASE; break;
      case 0b0001000010: output = KEY_Q_PRESS; break;
      case 0b1001000010: output = KEY_Q_RELEASE; break;
      case 0b0001001110: output = KEY_R_PRESS; break;
      case 0b1001001110: output = KEY_R_RELEASE; break;
      case 0b0011111110: output = KEY_S_PRESS; break;
      case 0b1001111110: output = KEY_S_RELEASE; break;
      case 0b0001010010: output = KEY_T_PRESS; break;
      case 0b1001010010: output = KEY_T_RELEASE; break;
      case 0b0001011010: output = KEY_U_PRESS; break;
      case 0b1001011010: output = KEY_U_RELEASE; break;
      case 0b0010111110: output = KEY_V_PRESS; break;
      case 0b1010111110: output = KEY_V_RELEASE; break;
      case 0b0001000110: output = KEY_W_PRESS; break;
      case 0b1001000110: output = KEY_W_RELEASE; break;
      case 0b0010110110: output = KEY_X_PRESS; break;
      case 0b1010110110: output = KEY_X_RELEASE; break;
      case 0b0001010110: output = KEY_Y_PRESS; break;
      case 0b1001010110: output = KEY_Y_RELEASE; break;
      case 0b0010110010: output = KEY_Z_PRESS; break;
      case 0b1010110010: output = KEY_Z_RELEASE; break;

      case 0b0000000110: output = KEY_ESC_PRESS; break;
      case 0b1000000110: output = KEY_ESC_RELEASE; break;
      case 0b0000001010: output = KEY_1_PRESS; break;
      case 0b1000001010: output = KEY_1_RELEASE; break;
      case 0b0000001110: output = KEY_2_PRESS; break;
      case 0b1000001110: output = KEY_2_RELEASE; break;
      case 0b0000010010: output = KEY_3_PRESS; break;
      case 0b1000010010: output = KEY_3_RELEASE; break;
      case 0b0000010110: output = KEY_4_PRESS; break;
      case 0b1000010110: output = KEY_4_RELEASE; break;
      case 0b0000011010: output = KEY_5_PRESS; break;
      case 0b1000011010: output = KEY_5_RELEASE; break;
      case 0b0000011110: output = KEY_6_PRESS; break;
      case 0b1000011110: output = KEY_6_RELEASE; break;
      case 0b0000100010: output = KEY_7_PRESS; break;
      case 0b1000100010: output = KEY_7_RELEASE; break;
      case 0b0000100110: output = KEY_8_PRESS; break;
      case 0b1000100110: output = KEY_8_RELEASE; break;
      case 0b0000101010: output = KEY_9_PRESS; break;
      case 0b1000101010: output = KEY_9_RELEASE; break;
      case 0b0000101110: output = KEY_0_PRESS; break;
      case 0b1000101110: output = KEY_0_RELEASE; break;

      case 0b0000110010: output = KEY_MINUS_PRESS; break;
      case 0b1000110010: output = KEY_MINUS_RELEASE; break;
      case 0b0000110110: output = KEY_EQUALS_PRESS; break;
      case 0b1000110110: output = KEY_EQUALS_RELEASE; break;
      case 0b0000111010: output = KEY_BACKSPACE_PRESS; break;
      case 0b1000111010: output = KEY_BACKSPACE_RELEASE; break;
      
      // numpad
      case 0b0101001110: output = KEY_KP_0_PRESS; break;
      case 0b1101001110: output = KEY_KP_0_RELEASE; break;
      case 0b0100111110: output = KEY_KP_1_PRESS; break;
      case 0b1100111110: output = KEY_KP_1_RELEASE; break;
      case 0b0101000010: output = KEY_KP_2_PRESS; break;
      case 0b1101000010: output = KEY_KP_2_RELEASE; break;
      case 0b0101000110: output = KEY_KP_3_PRESS; break;
      case 0b1101000110: output = KEY_KP_3_RELEASE; break;
      case 0b0100101110: output = KEY_KP_4_PRESS; break;
      case 0b1100101110: output = KEY_KP_4_RELEASE; break;
      case 0b0100110010: output = KEY_KP_5_PRESS; break;
      case 0b1100110010: output = KEY_KP_5_RELEASE; break;
      case 0b0100110110: output = KEY_KP_6_PRESS; break;
      case 0b1100110110: output = KEY_KP_6_RELEASE; break;
      case 0b0100011110: output = KEY_KP_7_PRESS; break;
      case 0b1100011110: output = KEY_KP_7_RELEASE; break;
      case 0b0100100010: output = KEY_KP_8_PRESS; break;
      case 0b1100100010: output = KEY_KP_8_RELEASE; break;
      case 0b0100100110: output = KEY_KP_9_PRESS; break;
      case 0b1100100110: output = KEY_KP_9_RELEASE; break;
      case 0b0100111010: output = KEY_KP_PLUS_PRESS; break;
      case 0b1100111010: output = KEY_KP_PLUS_RELEASE; break;
      case 0b0100101010: output = KEY_KP_MINUS_PRESS; break;
      case 0b1100101010: output = KEY_KP_MINUS_RELEASE; break;
      case 0b0101001010: output = KEY_NUMLOCK_PRESS; break;
      case 0b1101001010: output = KEY_NUMLOCK_RELEASE; break;
      
      //f keys
      case 0b0011101110: output = KEY_F1_PRESS; break;
      case 0b1011101110: output = KEY_F1_RELEASE; break;
      case 0b0011110010: output = KEY_F2_PRESS; break;
      case 0b1011110010: output = KEY_F2_RELEASE; break;
      case 0b0011110110: output = KEY_F3_PRESS; break;
      case 0b1011110110: output = KEY_F3_RELEASE; break;
      case 0b0011111010: output = KEY_F4_PRESS; break;
      case 0b1011111010: output = KEY_F4_RELEASE; break;
      case 0b0011111110: output = KEY_F5_PRESS; break;
      case 0b1011111110: output = KEY_F5_RELEASE; break;
      case 0b0100000010: output = KEY_F6_PRESS; break;
      case 0b1100000010: output = KEY_F6_RELEASE; break;
      case 0b0100000110: output = KEY_F7_PRESS; break;
      case 0b1100000110: output = KEY_F7_RELEASE; break;
      case 0b0100001010: output = KEY_F8_PRESS; break;
      case 0b1100001010: output = KEY_F8_RELEASE; break;
      case 0b0100001110: output = KEY_F9_PRESS; break;
      case 0b1100001110: output = KEY_F9_RELEASE; break;
      case 0b0100010010: output = KEY_F10_PRESS; break;
      case 0b1100010010: output = KEY_F10_RELEASE; break;

      //Edge keys
      case 0b000111110: output = KEY_TAB_PRESS; break;
      case 0b1000111110: output = KEY_TAB_RELEASE; break;
      case 0b0001110110: output = KEY_CTRL_PRESS; break;
      case 0b1001110110: output = KEY_CTRL_RELEASE; break;
      case 0b0010101010: output = KEY_LSHIFT_PRESS; break;
      case 0b1010101010: output = KEY_LSHIFT_RELEASE; break;
      case 0b0011100010: output = KEY_ALT_PRESS; break;
      case 0b1011100010: output = KEY_ALT_RELEASE; break;
      case 0b0011100110: output = KEY_SPACE_PRESS; break;
      case 0b1011100110: output = KEY_SPACE_RELEASE; break;
      case 0b0011101010: output = KEY_CAPSLOCK_PRESS; break;
      case 0b1011101010: output = KEY_CAPSLOCK_RELEASE; break;
      case 0b0011011010: output = KEY_RSHIFT_PRESS; break;
      case 0b1011011010: output = KEY_RSHIFT_RELEASE; break;

      case 0b0010101110: output = KEY_BACKSLASH_PRESS; break;
      case 0b1010101110: output = KEY_BACKSLASH_RELEASE; break;
      case 0b0011001110: output = KEY_COMMA_PRESS; break;
      case 0b1011001110: output = KEY_COMMA_RELEASE; break;
      case 0b0011010010: output = KEY_PERIOD_PRESS; break;
      case 0b1011010010: output = KEY_PERIOD_RELEASE; break;
      case 0b0011010110: output = KEY_SLASH_PRESS; break;
      case 0b1011010110: output = KEY_SLASH_RELEASE; break;
      case 0b0011010110: output = KEY_SEMICOLON_PRESS; break;
      case 0b1011010110: output = KEY_SEMICOLON_RELEASE; break;
      case 0b0010011110: output = KEY_AT_PRESS; break;
      case 0b1010011110: output = KEY_AT_RELEASE; break;
      case 0b0010100010: output = KEY_HASH_PRESS; break;
      case 0b1010100010: output = KEY_HASH_RELEASE; break;
      case 0b0010100110: output = KEY_LBRACKET_PRESS; break;
      case 0b1010100110: output = KEY_LBRACKET_RELEASE; break;
      case 0b0001101010: output = KEY_RBRACKET_PRESS; break;
      case 0b1001101010: output = KEY_RBRACKET_RELEASE; break;
      case 0b0001101110: output = KEY_RBRACKET_PRESS; break;
      case 0b1001101110: output = KEY_RBRACKET_RELEASE; break;
      case 0b011011110: output = KEY_ASTERISK_PRESS; break;
      case 0b1011011110: output = KEY_ASTERISK_RELEASE; break;

      default:
          output = KEY_NONE;
          break;
  }
  return key
}

/* Update: Uint8 is too small
  Actually every last bit appears to be 0, so thats the end bit code and it seems we are missing the MSB
*/

void setup() {
  // initialize serial communication at 115200 bits per second:
  //supposedly instructions happen once every 2.5 uS = 400 000 times a second

  Serial.begin(115200);  //TODO: Maybe the baud rate needs to be upped? I think scaling it makes sense, but lets be sure about that first.

  // Set the pins to inputs/interrupts:

  pinMode(keyboard_clk, INPUT);  //This is an INPUT pin because the keyboard actually generates the clock, so we get to sample this side.
  attachInterrupt(keyboard_clk, clock_falling_edge, FALLING);

  pinMode(keyboard_data, INPUT);
}


// the loop routine runs over and over again forever:
void loop() {

  if (data_bit_number >= 10) {
    Serial.println(output_character_code, BIN);  //Output the full data of the code
    //Type 3 - if output_character_code is uint8_t then it just cuts off the start bits because of how this shit works. CANT USE FREAKY MODE.

    data_bit_number = 0;
    output_character_code = 0;
  }
}
