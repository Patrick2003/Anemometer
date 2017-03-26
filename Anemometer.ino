
   

  #include <SPI.h>
  #include <Wire.h>
  #include <Adafruit_GFX.h>
  #include <Adafruit_SSD1306.h>

  #define OLED_RESET D3
  Adafruit_SSD1306 display(OLED_RESET);

  #define NUMFLAKES 10
  #define XPOS 0
  #define YPOS 1
  #define DELTAY 2


  #define LOGO16_GLCD_HEIGHT 16
  #define LOGO16_GLCD_WIDTH  16
  static const unsigned char PROGMEM logo16_glcd_bmp[] =
  { B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000
  };

  #define SSD1306_LCDHEIGHT 64

  #if (SSD1306_LCDHEIGHT != 64)
  #error("Height incorrect, please fix Adafruit_SSD1306.h!");
  #endif
unsigned long Time = 0;
double Speedcm = 0;
double Speedm  = 0;
double Speedkm = 0;
int RPM = 0;
int count = 0;




void setup() {


   //Umfang=47,1cm


  Serial.begin(9600);

    // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
    // init done

    // Show image buffer on the display hardware.
    // Since the buffer is intialized with an Adafruit splashscreen
    // internally, this will display the splashscreen.
    display.display();
    delay(2000);

    // Clear the buffer.
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.display();
    pinMode(A0, INPUT);
 


}

bool current_state = false;
int current_value = 0;
int last_value = 0;

void loop() {

int hall = analogRead(A0);

if (hall>540){
    current_state = true;
}
if(hall<=540 && current_state == true) {
  current_state = false;
    Serial.println("HALL"); 
    count++; 
}

  if (millis() - Time >= 10000) {
    current_value =  count;
    RPM = (current_value-last_value)*6;
    Speedcm = RPM*47/60;
    Speedm = Speedcm/100;
    Speedkm = Speedm*3,6;
    Serial.println(" ");
    Serial.println(Speedcm);
    Serial.println(Speedm);
    Serial.println(Speedkm);
    Serial.println(RPM);
    Serial.println(" ");
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(2);
    if (Speedkm < 1) {
      Serial.println("still");
      display.println("still");
    }
    else if (Speedkm <= 19) {
      Serial.println("leichte Brise");
      display.println("leichte");
      display.println("Brise");
    }
    else if (Speedkm <= 38) {
     Serial.println("frische Brise");
     display.println("frische");
     display.println("Brise");
     
    }
    else if (Speedkm <= 61) {
      Serial.println("starker Wind");
      display.println("starker");
      display.println("Wind");
    }
    else if (Speedkm <= 88) {
      Serial.println("Sturm");
      display.println("Sturm");
    }
    else if (Speedkm <= 117) {
      Serial.println("schwerer Sturm");
      display.println("schwerer");
      display.println("Sturm");
    }
    else if (Speedkm > 117) {
      Serial.println("Orkan");
      display.println("Orkan");
    }
    Time = millis();
    last_value = current_value;
      display.print("ca ");
      display.print(round(Speedkm));
      display.println(" km/h");
      display.print("RPM: ");
      display.println(RPM);
      display.display();
  }
  delay(15);
}
