#include <LedControl.h>

int DIN = 12;

//matrix
int CS =  11;
int CLK = 10;
int ilosc_ekranow = 1;

//joystick
const int SW_pin = 4; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output

//ball
int ballSpeed = 200;  //szybkosc z jaka porusza sie pilka
int rsize = 3;        //wielkosc rakietki
int points = 5;       //liczba nieudanych prob odbic konczaca gre
int actualBallPositionRow;
int actualBallPositionColumn = 0;
int beginBallPosition;
int beginDirection;
int ballUp;     // 1 - pilka leci w gore, 0 - poziomo, -1 - w dol
bool ballRight;
int minBallSpeed = 1000;
int maxBallSpeed = 100;

//paddle
int paddleSize = 3;
int beginPaddlePosition = 1;
int actualPaddlePosition = 0; //-paddleSize(poza matryca z lewej strony), 8(poza matryca z prawej strony)

byte ascii_table[130][8];
LedControl lc=LedControl(DIN,CLK,CS,0);

void wypelnij()
{
/*ascii_table[4][0]=B01000110;
ascii_table[4][1]=B00010100;
ascii_table[4][2]=B10000000;
ascii_table[4][3]=B10000000;
ascii_table[4][4]=B00010100;
ascii_table[4][5]=B00100000;
ascii_table[4][6]=B00000001;
ascii_table[4][7]=B10100100;
ascii_table[4][8]=B00101000;
ascii_table[4][7]=8;*/
  
ascii_table[32][0]=B00000000;
ascii_table[32][1]=B00000000;
ascii_table[32][2]=B00000000;
ascii_table[32][3]=B00000000;
ascii_table[32][4]=B00000000;
ascii_table[32][7]=5;
 

/*ascii_table[33][0]=B00000000;
ascii_table[33][1]=B01011111;
ascii_table[33][2]=B00000000;
ascii_table[33][7]=3;
 
ascii_table[34][0]=B00000000;
ascii_table[34][1]=B00001110;
ascii_table[34][2]=B00000000;
ascii_table[34][3]=B00001110;
ascii_table[34][4]=B00000000;
ascii_table[34][7]=5;
 
ascii_table[35][0]=B00000000;
ascii_table[35][1]=B00010100;
ascii_table[35][2]=B01111111;
ascii_table[35][3]=B00010100;
ascii_table[35][4]=B01111111;
ascii_table[35][5]=B00010100;
ascii_table[35][6]=B00000000;
ascii_table[35][7]=7;
 
ascii_table[36][0]=B00000000;
ascii_table[36][1]=B00100100;
ascii_table[36][2]=B00101010;
ascii_table[36][3]=B01111111;
ascii_table[36][4]=B00101010;
ascii_table[36][5]=B00100100;
ascii_table[36][6]=B00000000;
ascii_table[36][7]=7;
 
ascii_table[37][0]=B00000000;
ascii_table[37][1]=B01100010;
ascii_table[37][2]=B01100100;
ascii_table[37][3]=B00001000;
ascii_table[37][4]=B00010011;
ascii_table[37][5]=B00100011;
ascii_table[37][6]=B00000000;
ascii_table[37][7]=7;
 
ascii_table[38][0]=B00000000;
ascii_table[38][1]=B01010000;
ascii_table[38][2]=B00100010;
ascii_table[38][3]=B01010101;
ascii_table[38][4]=B01001001;
ascii_table[38][5]=B00110110;
ascii_table[38][6]=B00000000;
ascii_table[38][7]=7;
 
ascii_table[39][0]=B00000000;
ascii_table[39][1]=B00000011;
ascii_table[39][2]=B00000101;
ascii_table[39][3]=B00000000;
ascii_table[39][7]=4;
 
ascii_table[40][0]=B00000000;
ascii_table[40][1]=B01000001;
ascii_table[40][2]=B00100010;
ascii_table[40][3]=B00011100;
ascii_table[40][4]=B00000000;
ascii_table[40][7]=5;
 
ascii_table[41][0]=B00000000;
ascii_table[41][1]=B00011100;
ascii_table[41][2]=B00100010;
ascii_table[41][3]=B01000001;
ascii_table[41][4]=B00000000;
ascii_table[41][7]=5;
 
ascii_table[42][0]=B00000000;
ascii_table[42][1]=B00010100;
ascii_table[42][2]=B00001000;
ascii_table[42][3]=B00111110;
ascii_table[42][4]=B00001000;
ascii_table[42][5]=B00010100;
ascii_table[42][6]=B00000000;
ascii_table[42][7]=7;
 
ascii_table[43][0]=B00000000;
ascii_table[43][1]=B00001000;
ascii_table[43][2]=B00001000;
ascii_table[43][3]=B00111110;
ascii_table[43][4]=B00001000;
ascii_table[43][5]=B00001000;
ascii_table[43][6]=B00000000;
ascii_table[43][7]=7;
 
ascii_table[44][0]=B00000000;
ascii_table[44][1]=B00110000;
ascii_table[44][2]=B01010000;
ascii_table[44][3]=B00000000;
ascii_table[44][7]=4;
 
ascii_table[45][0]=B00000000;
ascii_table[45][1]=B00001000;
ascii_table[45][2]=B00001000;
ascii_table[45][3]=B00001000;
ascii_table[45][4]=B00001000;
ascii_table[45][5]=B00000000;
ascii_table[45][7]=6;
 
ascii_table[46][0]=B00000000;
ascii_table[46][1]=B01100000;
ascii_table[46][2]=B01100000;
ascii_table[46][3]=B00000000;
ascii_table[46][7]=4;
 
ascii_table[47][0]=B00000000;
ascii_table[47][1]=B00000010;
ascii_table[47][2]=B00000100;
ascii_table[47][3]=B00001000;
ascii_table[47][4]=B00010000;
ascii_table[47][5]=B00100000;
ascii_table[47][6]=B00000000;
ascii_table[47][7]=7;
 
ascii_table[48][0]=B00000000;
ascii_table[48][1]=B00111110;
ascii_table[48][2]=B01000001;
ascii_table[48][3]=B01000001;
ascii_table[48][4]=B00111110;
ascii_table[48][5]=B00000000;
ascii_table[48][7]=6;
 
ascii_table[49][0]=B00000000;
ascii_table[49][1]=B01000000;
ascii_table[49][2]=B01111111;
ascii_table[49][3]=B01000010;
ascii_table[49][4]=B00000000;
ascii_table[49][7]=5;
 
ascii_table[50][0]=B00000000;
ascii_table[50][1]=B01000110;
ascii_table[50][2]=B01001001;
ascii_table[50][3]=B01010001;
ascii_table[50][4]=B01100011;
ascii_table[50][5]=B01000010;
ascii_table[50][6]=B00000000;
ascii_table[50][7]=7;
 
ascii_table[51][0]=B00000000;
ascii_table[51][1]=B00110001;
ascii_table[51][2]=B01001011;
ascii_table[51][3]=B01000101;
ascii_table[51][4]=B01000001;
ascii_table[51][5]=B00100001;
ascii_table[51][6]=B00000000;
ascii_table[51][7]=7;
 
ascii_table[52][0]=B00000000;
ascii_table[52][1]=B00010000;
ascii_table[52][2]=B01111111;
ascii_table[52][3]=B00010010;
ascii_table[52][4]=B00010100;
ascii_table[52][5]=B00011000;
ascii_table[52][6]=B00000000;
ascii_table[52][7]=7;
 
ascii_table[53][0]=B00000000;
ascii_table[53][1]=B00111001;
ascii_table[53][2]=B01000101;
ascii_table[53][3]=B01000101;
ascii_table[53][4]=B01000101;
ascii_table[53][5]=B00100111;
ascii_table[53][6]=B00000000;
ascii_table[53][7]=7;
 
ascii_table[54][0]=B00000000;
ascii_table[54][1]=B00110000;
ascii_table[54][2]=B01001001;
ascii_table[54][3]=B01001001;
ascii_table[54][4]=B01001010;
ascii_table[54][5]=B00111100;
ascii_table[54][6]=B00000000;
ascii_table[54][7]=7;
 
ascii_table[55][0]=B00000000;
ascii_table[55][1]=B00000111;
ascii_table[55][2]=B00001001;
ascii_table[55][3]=B01110001;
ascii_table[55][4]=B00000001;
ascii_table[55][5]=B00000011;
ascii_table[55][6]=B00000000;
ascii_table[55][7]=7;
 
ascii_table[56][0]=B00000000;
ascii_table[56][1]=B00110110;
ascii_table[56][2]=B01001001;
ascii_table[56][3]=B01001001;
ascii_table[56][4]=B01001001;
ascii_table[56][5]=B00110110;
ascii_table[56][6]=B00000000;
ascii_table[56][7]=7;
 
ascii_table[57][0]=B00000000;
ascii_table[57][1]=B00011110;
ascii_table[57][2]=B00101001;
ascii_table[57][3]=B01001001;
ascii_table[57][4]=B01001001;
ascii_table[57][5]=B00000110;
ascii_table[57][6]=B00000000;
ascii_table[57][7]=7;
 
ascii_table[58][0]=B00000000;
ascii_table[58][1]=B00110110;
ascii_table[58][2]=B00110110;
ascii_table[58][3]=B00000000;
ascii_table[58][7]=4;
 
ascii_table[59][0]=B00000000;
ascii_table[59][1]=B00110110;
ascii_table[59][2]=B01010110;
ascii_table[59][3]=B00000000;
ascii_table[59][7]=4;
 
ascii_table[60][0]=B00000000;
ascii_table[60][1]=B01000001;
ascii_table[60][2]=B00100010;
ascii_table[60][3]=B00010100;
ascii_table[60][4]=B00001000;
ascii_table[60][5]=B00000000;
ascii_table[60][7]=6;
 
ascii_table[61][0]=B00000000;
ascii_table[61][1]=B00010100;
ascii_table[61][2]=B00010100;
ascii_table[61][3]=B00010100;
ascii_table[61][4]=B00010100;
ascii_table[61][5]=B00010100;
ascii_table[61][6]=B00000000;
ascii_table[61][7]=7;
 
ascii_table[62][0]=B00000000;
ascii_table[62][1]=B00001000;
ascii_table[62][2]=B00010100;
ascii_table[62][3]=B00100010;
ascii_table[62][4]=B01000001;
ascii_table[62][5]=B00000000;
ascii_table[62][7]=6;
 
ascii_table[63][0]=B00000000;
ascii_table[63][1]=B00000110;
ascii_table[63][2]=B00001001;
ascii_table[63][3]=B01010001;
ascii_table[63][4]=B00000001;
ascii_table[63][5]=B00000010;
ascii_table[63][6]=B00000000;
ascii_table[63][7]=7;
 
ascii_table[64][0]=B00000000;
ascii_table[64][1]=B00111110;
ascii_table[64][2]=B01000001;
ascii_table[64][3]=B01111001;
ascii_table[64][4]=B01001001;
ascii_table[64][5]=B00110010;
ascii_table[64][6]=B00000000;
ascii_table[64][7]=7;*/
 
ascii_table[65][0]=B00000000;
ascii_table[65][1]=B01111110;
ascii_table[65][2]=B00010001;
ascii_table[65][3]=B00010001;
ascii_table[65][4]=B00010001;
ascii_table[65][5]=B01111110;
ascii_table[65][6]=B00000000;
ascii_table[65][7]=7;
 
/*ascii_table[66][0]=B00000000;
ascii_table[66][1]=B00110110;
ascii_table[66][2]=B01001001;
ascii_table[66][3]=B01001001;
ascii_table[66][4]=B01001001;
ascii_table[66][5]=B01111111;
ascii_table[66][6]=B00000000;
ascii_table[66][7]=7;
 
ascii_table[67][0]=B00000000;
ascii_table[67][1]=B00100010;
ascii_table[67][2]=B01000001;
ascii_table[67][3]=B01000001;
ascii_table[67][4]=B01000001;
ascii_table[67][5]=B00111110;
ascii_table[67][6]=B00000000;
ascii_table[67][7]=7;
 
ascii_table[68][0]=B00000000;
ascii_table[68][1]=B00011100;
ascii_table[68][2]=B00100010;
ascii_table[68][3]=B01000001;
ascii_table[68][4]=B01000001;
ascii_table[68][5]=B01111111;
ascii_table[68][6]=B00000000;
ascii_table[68][7]=7;*/
 
ascii_table[69][0]=B00000000;
ascii_table[69][1]=B01000001;
ascii_table[69][2]=B01001001;
ascii_table[69][3]=B01001001;
ascii_table[69][4]=B01111111;
ascii_table[69][5]=B00000000;
ascii_table[69][7]=6;
 
/*ascii_table[70][0]=B00000000;
ascii_table[70][1]=B00000001;
ascii_table[70][2]=B00001001;
ascii_table[70][3]=B00001001;
ascii_table[70][4]=B01111111;
ascii_table[70][5]=B00000000;
ascii_table[70][7]=6;*/
 
ascii_table[71][0]=B00000000;
ascii_table[71][1]=B01111010;
ascii_table[71][2]=B01001001;
ascii_table[71][3]=B01001001;
ascii_table[71][4]=B01000001;
ascii_table[71][5]=B00111110;
ascii_table[71][6]=B00000000;
ascii_table[71][7]=7;
 
/*ascii_table[72][0]=B00000000;
ascii_table[72][1]=B01111111;
ascii_table[72][2]=B00001000;
ascii_table[72][3]=B00001000;
ascii_table[72][4]=B01111111;
ascii_table[72][5]=B00000000;
ascii_table[72][7]=6;
 
ascii_table[73][0]=B00000000;
ascii_table[73][1]=B01000001;
ascii_table[73][2]=B01111111;
ascii_table[73][3]=B01000001;
ascii_table[73][4]=B00000000;
ascii_table[73][7]=5;
 
ascii_table[74][0]=B00000000;
ascii_table[74][1]=B00000001;
ascii_table[74][2]=B01111111;
ascii_table[74][3]=B01000001;
ascii_table[74][4]=B01000000;
ascii_table[74][5]=B00100000;
ascii_table[74][6]=B00000000;
ascii_table[74][7]=7;
 
ascii_table[75][0]=B00000000;
ascii_table[75][1]=B01000001;
ascii_table[75][2]=B00100010;
ascii_table[75][3]=B00010100;
ascii_table[75][4]=B00001000;
ascii_table[75][5]=B01111111;
ascii_table[75][6]=B00000000;
ascii_table[75][7]=7;
 
ascii_table[76][0]=B00000000;
ascii_table[76][1]=B01000000;
ascii_table[76][2]=B01000000;
ascii_table[76][3]=B01000000;
ascii_table[76][4]=B01111111;
ascii_table[76][5]=B00000000;
ascii_table[76][7]=6;*/
 
ascii_table[77][0]=B00000000;
ascii_table[77][1]=B01111111;
ascii_table[77][2]=B00000010;
ascii_table[77][3]=B00001100;
ascii_table[77][4]=B00000010;
ascii_table[77][5]=B01111111;
ascii_table[77][6]=B00000000;
ascii_table[77][7]=7;
 
/*ascii_table[78][0]=B00000000;
ascii_table[78][1]=B01111111;
ascii_table[78][2]=B00010000;
ascii_table[78][3]=B00001000;
ascii_table[78][4]=B00000100;
ascii_table[78][5]=B01111111;
ascii_table[78][6]=B00000000;
ascii_table[78][7]=7;*/
 
ascii_table[79][0]=B00000000;
ascii_table[79][1]=B00111110;
ascii_table[79][2]=B01000001;
ascii_table[79][3]=B01000001;
ascii_table[79][4]=B01000001;
ascii_table[79][5]=B00111110;
ascii_table[79][6]=B00000000;
ascii_table[79][7]=7;
 
/*ascii_table[80][0]=B00000000;
ascii_table[80][1]=B00000110;
ascii_table[80][2]=B00001001;
ascii_table[80][3]=B00001001;
ascii_table[80][4]=B00001001;
ascii_table[80][5]=B01111111;
ascii_table[80][6]=B00000000;
ascii_table[80][7]=7;
 
ascii_table[81][0]=B00000000;
ascii_table[81][1]=B01011110;
ascii_table[81][2]=B00100001;
ascii_table[81][3]=B01010001;
ascii_table[81][4]=B01000001;
ascii_table[81][5]=B00111110;
ascii_table[81][6]=B00000000;
ascii_table[81][7]=7;*/
 
ascii_table[82][0]=B00000000;
ascii_table[82][1]=B01000110;
ascii_table[82][2]=B00101001;
ascii_table[82][3]=B00011001;
ascii_table[82][4]=B00001001;
ascii_table[82][5]=B01111111;
ascii_table[82][6]=B00000000;
ascii_table[82][7]=7;
 
/*ascii_table[83][0]=B00000000;
ascii_table[83][1]=B00110001;
ascii_table[83][2]=B01001001;
ascii_table[83][3]=B01001001;
ascii_table[83][4]=B01001001;
ascii_table[83][5]=B01000110;
ascii_table[83][6]=B00000000;
ascii_table[83][7]=7;
 
ascii_table[84][0]=B00000000;
ascii_table[84][1]=B00000001;
ascii_table[84][2]=B00000001;
ascii_table[84][3]=B01111111;
ascii_table[84][4]=B00000001;
ascii_table[84][5]=B00000001;
ascii_table[84][6]=B00000000;
ascii_table[84][7]=7;
 
ascii_table[85][0]=B00000000;
ascii_table[85][1]=B00111111;
ascii_table[85][2]=B01000000;
ascii_table[85][3]=B01000000;
ascii_table[85][4]=B01000000;
ascii_table[85][5]=B00111111;
ascii_table[85][6]=B00000000;
ascii_table[85][7]=7;*/
 
ascii_table[86][0]=B00000000;
ascii_table[86][1]=B00011111;
ascii_table[86][2]=B00100000;
ascii_table[86][3]=B01000000;
ascii_table[86][4]=B00100000;
ascii_table[86][5]=B00011111;
ascii_table[86][6]=B00000000;
ascii_table[86][7]=7;
 
/*ascii_table[87][0]=B00000000;
ascii_table[87][1]=B00111111;
ascii_table[87][2]=B01000000;
ascii_table[87][3]=B00111000;
ascii_table[87][4]=B01000000;
ascii_table[87][5]=B00111111;
ascii_table[87][6]=B00000000;
ascii_table[87][7]=7;
 
ascii_table[88][0]=B00000000;
ascii_table[88][1]=B01100011;
ascii_table[88][2]=B00010100;
ascii_table[88][3]=B00001000;
ascii_table[88][4]=B00010100;
ascii_table[88][5]=B01100011;
ascii_table[88][6]=B00000000;
ascii_table[88][7]=7;
 
ascii_table[89][0]=B00000000;
ascii_table[89][1]=B00000111;
ascii_table[89][2]=B00001000;
ascii_table[89][3]=B01110000;
ascii_table[89][4]=B00001000;
ascii_table[89][5]=B00000111;
ascii_table[89][6]=B00000000;
ascii_table[89][7]=7;
 
ascii_table[90][0]=B00000000;
ascii_table[90][1]=B01000011;
ascii_table[90][2]=B01000101;
ascii_table[90][3]=B01001001;
ascii_table[90][4]=B01010001;
ascii_table[90][5]=B01100001;
ascii_table[90][6]=B00000000;
ascii_table[90][7]=7;
 
ascii_table[91][0]=B00000000;
ascii_table[91][1]=B01000001;
ascii_table[91][2]=B01000001;
ascii_table[91][3]=B01111111;
ascii_table[91][4]=B00000000;
ascii_table[91][7]=5;
 
ascii_table[93][0]=B00000000;
ascii_table[93][1]=B01111111;
ascii_table[93][2]=B01000001;
ascii_table[93][3]=B01000001;
ascii_table[93][4]=B00000000;
ascii_table[93][7]=5;
 
ascii_table[94][0]=B00000000;
ascii_table[94][1]=B00000100;
ascii_table[94][2]=B00000010;
ascii_table[94][3]=B00000001;
ascii_table[94][4]=B00000010;
ascii_table[94][5]=B00000100;
ascii_table[94][6]=B00000000;
ascii_table[94][7]=7;
 
ascii_table[95][0]=B00000000;
ascii_table[95][1]=B01000000;
ascii_table[95][2]=B01000000;
ascii_table[95][3]=B01000000;
ascii_table[95][4]=B01000000;
ascii_table[95][5]=B00000000;
ascii_table[95][7]=6;
 
ascii_table[123][0]=B00000000;
ascii_table[123][1]=B01000001;
ascii_table[123][2]=B00110110;
ascii_table[123][3]=B00001000;
ascii_table[123][4]=B00000000;
ascii_table[123][7]=5;

ascii_table[124][0]=B00000000;
ascii_table[124][1]=B01111111;
ascii_table[124][2]=B00000000;
ascii_table[124][7]=3;
 
ascii_table[125][0]=B00000000;
ascii_table[125][1]=B00001000;
ascii_table[125][2]=B00110110;
ascii_table[125][3]=B01000001;
ascii_table[125][4]=B00000000;
ascii_table[125][7]=5;
 
ascii_table[126][0]=B00000000;
ascii_table[126][1]=B00001000;
ascii_table[126][2]=B00010000;
ascii_table[126][3]=B00001000;
ascii_table[126][4]=B00001000;
ascii_table[126][5]=B00010000;
ascii_table[126][6]=B00000000;
ascii_table[126][7]=7;*/
}

void setup(){
 Serial.begin(9600);
 pinMode(SW_pin, INPUT);
 digitalWrite(SW_pin, HIGH);
 lc.shutdown(0,false);      // wyjscie z trybu uspienia
 lc.setIntensity(0,1);      // ustawienie jasnosci
 randomSeed(analogRead(4));
 startGame();
 }
 
 
 /*for (int j1=0; j1<90; j1++)      //petla do wypelnienia ascii
  {
    for (int i1=0; i1<8; i1++)
        {
         ascii_table[i1][j1]=0;
          }
  }
}*/

void loop(){
    wypelnij();
    moveBallAndPaddle();  //zmienia aktualne pozycje paletki i pilki oraz zwieksza/zmniejsza predkosc pilki, wyswietla paletke
    checkWalls();         //sprawdza ewentualne odbicie pilki od sciany
    showBall();           //wyswietla na matrycy led
    delay(ballSpeed);
    bounce();             //sprawdza czy pilka zostala odbita od paletki, kiedy dojdzie do prawej krawedzi
    //printAscii(4);
    //slideAscii(tekscik);
    Serial.println("Funkcja loop");
}

void startGame () {
 actualPaddlePosition = beginPaddlePosition;
 lc.clearDisplay(0);        // czyszczenie ekranu
beginBallPosition = random(2);
beginDirection = random(3);
 if (beginBallPosition == 1) {
  lc.setLed(0,3,0,true);
  actualBallPositionRow = 3;
 }
 else {
  lc.setLed(0,4,0,true);
  actualBallPositionRow = 4;
 }

  if (beginDirection == 0)
      ballUp = 1;
  else if (beginDirection == 1)
      ballUp = 0;
  else
      ballUp = -1;

  ballRight = 1;

  actualBallPositionColumn = 0;

 lc.setLed(0,actualPaddlePosition,7,true);
 lc.setLed(0,actualPaddlePosition+1,7,true);
 lc.setLed(0,actualPaddlePosition+2,7,true);

 while(digitalRead(SW_pin) == 1)
  delay(100);
}

void moveBallAndPaddle() {
  Serial.println("Funkcja moveBallAndPaddle");
  lc.setLed(0,actualBallPositionRow,actualBallPositionColumn,false);
  if (ballRight == 1) {
    actualBallPositionColumn += 1;
    Serial.println(actualBallPositionColumn);}
  else
    actualBallPositionColumn -= 1;

  if (ballUp == 1)
    actualBallPositionRow -= 1;
  else if (ballUp == -1)
    actualBallPositionRow += 1;

  if (analogRead(Y_pin) >= 1018 && actualPaddlePosition < 8) {
    lc.setLed(0,actualPaddlePosition,7,false);
    lc.setLed(0,actualPaddlePosition+3,7,true);
    actualPaddlePosition += 1;
  }
  else if (analogRead(Y_pin) <= 5 && actualPaddlePosition > -3) {
    lc.setLed(0,actualPaddlePosition+2,7,false);
    lc.setLed(0,actualPaddlePosition-1,7,true);
    actualPaddlePosition -= 1;
  }

  if (analogRead(X_pin) >= 1018 && ballSpeed > maxBallSpeed)
    ballSpeed += 10;
  else if (analogRead(X_pin) <= 5 && ballSpeed < minBallSpeed)
    ballSpeed -= 10;
}

void checkWalls () {
  if (actualBallPositionColumn == 0)
    ballRight = 1;
  else if (actualBallPositionColumn == 6) {                 //odbicie pilki od rakietki
    beginDirection = random(10);
    if (beginDirection > 4 && beginDirection <= 6)
      ballUp = 1;
    if (beginDirection > 6 && beginDirection <= 8)
      ballUp = 0;
    if (beginDirection > 8)
      ballUp = -1;
      
    ballRight = 0;
    
    
  }
  
  if (actualBallPositionRow == 0)
    ballUp = -1;
  else if (actualBallPositionRow == 7)
    ballUp = 1;
}

void showBall () {
  lc.setLed(0,actualBallPositionRow,actualBallPositionColumn,true);
}

void bounce () {
  if (actualBallPositionColumn == 6 && (actualBallPositionRow < actualPaddlePosition || actualBallPositionRow > actualPaddlePosition+2)) {    //przypadek straty pilki
    points = points-1;
    Serial.print("Loose points: "); Serial.println(points);
    if (points == 0) {
      gameOver();
    }
    else
      startGame();
    //Serial.print("Loose points: "); Serial.println(points);
    
  }
}


void gameOver () {
  points = 5;
  Serial.println("Game Over");
  while (digitalRead(SW_pin) == 1) {
    slideAscii("GAME OVER");
    delay(100);
  }
}


void printAscii(int indeks)        //funkcja do stałego napisu
{
  int i = 0;
  for(i=0;i<8;i++)
  {
    lc.setRow(0,i,ascii_table[indeks][i]);
    delay(50);
  }
}

int ile_lini(String tekst)              //funkcja liczaca ilosc lini do wyswietlenia
{
  int liczbowa[tekst.length()];                   //tablica zbierajaca liczby
  char znakowa[tekst.length()];                   //tablica zbierajaca znaki
  int linie;                                        //zmienna pomocnicza liczaca linie
  tekst.toCharArray(znakowa, tekst.length()+1);     //zamiana stringa na tablice char
  for (int i=0; i<tekst.length();i++)                 
      {
        liczbowa[i]=zamien_ascii(znakowa[i]);             //zamiana znakow na liczby
        linie = linie + ascii_table[liczbowa[i]][7];      //zliczenie ile lini z 7 pola ascii
        }
  return linie;
}

void slideAscii(String tekst)
{
  int lini = ile_lini(tekst);                         //ilosc lini tekstu
  byte pattern[lini+(16*ilosc_ekranow)];              //tablica ktora finalnie bedziemy wyswietlac

  int liczbowa[tekst.length()];                         //fragment przekopiowany z funkcji ile_lini
  char znakowa[tekst.length()];                         //
  tekst.toCharArray(znakowa, tekst.length()+1);         //
  for (int i=0; i<tekst.length();i++)                   //
      {                                                 //
        liczbowa[i]=zamien_ascii(znakowa[i]);           //
        //Serial.println(liczbowa[i]);                  //
        }                                               //
  int licznik = 0;                                      //zmienna liczaca ktory raz petla sie wypelnia
  for (int k=0;k<(8*ilosc_ekranow);k++)                 //wypelnienie pierwszego ekranu w pattern B00000000
      {
      pattern[licznik]=B00000000;
      Serial.println(pattern[licznik]);
      licznik++;
      }
  for (int i=0; i<tekst.length();i++)                             //wypelnianie napisem tablicy pattern
      {                                                           //zalezne od dlugosci tekstu
         //Serial.print("liczba: ");
         //Serial.println(i);
         
        for (int j=ascii_table[liczbowa[i]][7]; j>0;j--)          //oraz od ilosci lini w danym znaku
              {
                pattern[licznik] = ascii_table[liczbowa[i]][j-1];
                //Serial.println(pattern[licznik]);
                licznik++;
                }         
        }
  for (int k=0;k<(8*ilosc_ekranow);k++)                 //wypelnanie koncowego ekranu w pattern B00000000
      {
      pattern[licznik]=B00000000;
      Serial.println(pattern[licznik]);
      licznik++;
      }

      for(int k=0;k<(lini+(8*ilosc_ekranow));k++)
          {
          int pasy=0;
          for (int i=0;i<ilosc_ekranow;i++)                     //petla wypisujaca na matrycy
                {
                  for (int j=0;j<8;j++)                         //petla wewnetrzna wypisujaca na matrycy
                        {
                          lc.setRow(i,j,pattern[pasy+k]);           //lc.setRow funkcja wypisujaca
                          pasy++;                                   //pattern jest obiektem ktory wypisujemy
                          }                                         //pasy poniewaz jest to dodatkowa petla liczaca
                  }                                                 // +k aby napis mogl sie przesuwac
        
      delay(30);                                                  //opoznienie czyli predkosc przesuwania sie tekstu
           }
}

int zamien_ascii(char znak)       //zamiana znaku na ascii
{
if (znak==' '){return 32;}
if (znak=='!'){return 33;}
if (znak=='"'){return 34;}
if (znak=='#'){return 35;}
if (znak=='$'){return 36;}
if (znak=='%'){return 37;}
if (znak=='&'){return 38;}
if (znak=='('){return 40;}
if (znak==')'){return 41;}
if (znak=='*'){return 42;}
if (znak=='+'){return 43;}
if (znak==','){return 44;}
if (znak=='-'){return 45;}
if (znak=='.'){return 46;}
if (znak=='/'){return 47;}
if (znak=='0'){return 48;}
if (znak=='1'){return 49;}
if (znak=='2'){return 50;}
if (znak=='3'){return 51;}
if (znak=='4'){return 52;}
if (znak=='5'){return 53;}
if (znak=='6'){return 54;}
if (znak=='7'){return 55;}
if (znak=='8'){return 56;}
if (znak=='9'){return 57;}
if (znak==':'){return 58;}
if (znak==';'){return 59;}
if (znak=='<'){return 60;}
if (znak=='='){return 61;}
if (znak=='>'){return 62;}
if (znak=='?'){return 63;}
if (znak=='@'){return 64;}
if (znak=='A'){return 65;}
if (znak=='B'){return 66;}
if (znak=='C'){return 67;}
if (znak=='D'){return 68;}
if (znak=='E'){return 69;}
if (znak=='F'){return 70;}
if (znak=='G'){return 71;}
if (znak=='H'){return 72;}
if (znak=='I'){return 73;}
if (znak=='J'){return 74;}
if (znak=='K'){return 75;}
if (znak=='L'){return 76;}
if (znak=='M'){return 77;}
if (znak=='N'){return 78;}
if (znak=='O'){return 79;}
if (znak=='P'){return 80;}
if (znak=='Q'){return 81;}
if (znak=='R'){return 82;}
if (znak=='S'){return 83;}
if (znak=='T'){return 84;}
if (znak=='U'){return 85;}
if (znak=='V'){return 86;}
if (znak=='W'){return 87;}
if (znak=='X'){return 88;}
if (znak=='Y'){return 89;}
if (znak=='Z'){return 90;}
if (znak=='['){return 91;}
if (znak==']'){return 93;}
if (znak=='^'){return 94;}
if (znak=='_'){return 95;}
if (znak=='{'){return 123;}
if (znak=='|'){return 124;}
if (znak=='}'){return 125;}
if (znak=='~'){return 126;}
return 32;
}




