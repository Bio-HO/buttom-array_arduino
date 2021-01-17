#include "Keyboard.h"

//buttom array connected pins 
#define X0 3
#define X1 4
#define X2 5
#define Y0 6
#define Y1 7
#define Y2 8
#define Y3 9

//keys refer to your buttom array
const char keys[4][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'},{'*','0','#'}};

//buttom's register
bool buttom[3][4],buttom_pre[3][4];

//function to detect buttom array
void buttom_manager(void);

void setup() {
  // put your setup code here, to run once:
  //set pin mode
  pinMode(X0,OUTPUT);
  pinMode(X1,OUTPUT);
  pinMode(X2,OUTPUT);
  pinMode(Y0,INPUT_PULLUP);
  pinMode(Y1,INPUT_PULLUP);
  pinMode(Y2,INPUT_PULLUP);
  pinMode(Y3,INPUT_PULLUP);

  //initial serial port
  Serial.begin(9600);
  Serial.println("begin!");

  //initial registers
  buttom[3][4]={0};
  buttom_pre[3][4]={0};

  //initial and start Keyboard
  Keyboard.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  //detect buttom array
  buttom_manager();

  //read register and do something
  for(int i=0;i<3;i++){
    for(int j=0;j<4;j++){
      //output when the buttom was just push down, if the buttom not get release, the buttom_pre will be 0 and won't output until the buttom been release.
      if((buttom[i][j]==0)&&(buttom_pre[i][j]==1)){ 
        Serial.print("bottom:");
        Serial.println(keys[j][i]);
        Keyboard.write(keys[j][i]);
      }
      buttom_pre[i][j]=buttom[i][j];
    }
  }

}

void buttom_manager(){
  //detect X0 row
  digitalWrite(X0,LOW);
  digitalWrite(X1,HIGH);
  digitalWrite(X2,HIGH);
  buttom[0][0]=digitalRead(Y0);
  buttom[0][1]=digitalRead(Y1);
  buttom[0][2]=digitalRead(Y2);
  buttom[0][3]=digitalRead(Y3);

  //detect X1 row
  digitalWrite(X0,HIGH);
  digitalWrite(X1,LOW);
  digitalWrite(X2,HIGH);
  buttom[1][0]=digitalRead(Y0);
  buttom[1][1]=digitalRead(Y1);
  buttom[1][2]=digitalRead(Y2);
  buttom[1][3]=digitalRead(Y3);

  //detect X2 row
  digitalWrite(X0,HIGH);
  digitalWrite(X1,HIGH);
  digitalWrite(X2,LOW);
  buttom[2][0]=digitalRead(Y0);
  buttom[2][1]=digitalRead(Y1);
  buttom[2][2]=digitalRead(Y2);
  buttom[2][3]=digitalRead(Y3);

  //prevent bouncing
  delay(100);
}
