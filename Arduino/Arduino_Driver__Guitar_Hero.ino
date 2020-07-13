/*
Packet Order:   Star Power, Strum Up, Strump Down, Select, Start, Green, Red, Yellow, Blue, Orange, Whammy Bar
key in driver: [s           u         d            enter   ' '    1      2    3       4     5       Mouse Movement]
Packet Example: 0:1:0:0:0:0:1:1:0:0:512

Pin Configuration on Arduino:
  strum bar
     strumpDown = D3;
     strumUp = D4;
 
  control
     select = D5;
     start = D6;

  note buttons
     green = D7;
     red = D8;
     yellow = D9;
     blue = D10;
     orange = D11;
     
  misc
     starPower = D2;
     whammyBar = A2;
*/
//feel free to change baudrate, just remember to recompile the driver to have the same baudrate
//remember that too low of a baudrate could interfere with in-game reaction
const int baudrate = 115200;

void setup() {
  Serial.begin(baudrate);
  for(int i = 2; i < 12; i++){
    pinMode(i, INPUT);
  }
  pinMode(A2, INPUT);
}

void loop() { 
  //collect and print data for the push buttons and the dirrectional sensor for starpower
  for(int i = 2; i < 12; i++){
    Serial.print(digitalRead(i));
    Serial.print(":");      
  }
    
  //format whammybar so that there are always 3 digits
  int whammybar = analogRead(A2);
  if(whammybar <= 9){
    Serial.print("00");
    Serial.println(whammybar);
  }else if(whammybar <= 99){
    Serial.print("0");
    Serial.println(whammybar);
  }else{
    Serial.println(whammybar);
  }
}
