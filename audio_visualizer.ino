#include "MSGEQ7.h" //audio analyzer library
#include "U8g2lib.h" //OLED library

/**
  * Audio Amplfier with Integrated 7-Band Audio Visualizer Project
  
  * This program implements a real-time 7-band audio visualizer using an Arduino Nano, MSGEQ7 frequency analyzer chip, 
  * and an OLED display.  This program is apart of a custom PB audio amplifier project that includes stereo sound output
  * and user controls for volume, amplifier gain, and bass boost.
  *
  * The visualizer reads audio freuqnecy data from the MSGEQ7 chip, processes it, and displays and bar graph representation
  * of the 7 bands on the OLED screen.  The frequency bands displayed are: 63 Hz, 160 Hz, 400 Hz, 1 kHz, 2.5 kHz, 6.3 kHz,
  * and 16 kHz.
  *
  * @author Andy Gonzalez
  * @date September 11, 2024
*/

//OLED Display Object
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

int spectrum_values[7]; // 7-band frequency values
byte audio_bar_height[7]; // sizes for the individual bars
int led_pin = 10; // green led pin

const int MAX_DISPLAY_HEIGHT = 53; // Maximum height of the display area for bars
const int MAX_INPUT_VALUE = 255; // Maximum frequency value from the MSGEQ7 library
const int decrease_factor = 0; // Decrease frequency value for better bar display
const int led_value = 50;

//MSGEQ7 Pin Definition
#define SMOOTH true
#define SOUND_IN A0
#define RESET_PIN 5
#define STROBE_PIN 4
#define MSGEQ7_INTERVAL ReadsPerSecond(50)

CMSGEQ7<SMOOTH, RESET_PIN, STROBE_PIN, SOUND_IN> MSGEQ7;

void setup() 
{
    MSGEQ7.begin(); // start msgeqy7 library
    Serial.begin(115200);

    u8g2.begin(); // start the u8g2 library/display
    pinMode(led_pin, OUTPUT);
    analogWrite(led_pin, led_value); //turn on led when nano is on
}

void loop() {

  //clear display buffer
  u8g2.clearBuffer();

  // Analyze MSGEQ7 ICs, Will always return true.
  bool newReading = MSGEQ7.read(MSGEQ7_INTERVAL);

  if(newReading)
  {
    //loop through 7-band frequncies
    for (int i = 0; i < 7; i++)
    {
      uint8_t input = MSGEQ7.get(i, 0);
      if (input > decrease_factor)
      {
        input -= decrease_factor;
      }

      //print frequency bands to serial monitor
      Serial.print(input);
      Serial.print(" ");

      //add frequency band value to value array
      spectrum_values[i] = input;
    }

    Serial.println();
  }

  //Save frequency-band values and draw their respective audio bars
  for (int i = 0; i < 7; i++) 
  {
    //Convert frequency value to bar value
    int mappedValue = map(spectrum_values[i], 0, MAX_INPUT_VALUE, 0, MAX_DISPLAY_HEIGHT);
    audio_bar_height[i] = mappedValue;

    //Ensure we always draw at least a 1-pixel high bar
    int barHeight = max(audio_bar_height[i], 1);
    u8g2.drawBox(2 + i*19, MAX_DISPLAY_HEIGHT-barHeight, 10, barHeight);
  }     

  //Draw X-axis values
  u8g2.setFont(u8g2_font_nerhoe_tr);
  u8g2.drawStr(  2, 64, "63"); 
  u8g2.drawStr( 19, 64, "160"); 
  u8g2.drawStr( 37, 64, "400"); 
  u8g2.drawStr( 60, 64, "1k"); 
  u8g2.drawStr( 75, 64, "2.5k"); 
  u8g2.drawStr( 95, 64, "6.3k"); 
  u8g2.drawStr(115, 64, "16k");         

  //Send values to display
  u8g2.sendBuffer();

  // Short delay to allow time for serial output  
  delay(50);   
}
