/**********Libraries include:************/
#include <Servo.h>          //Servo lib
#include <SoftwareSerial.h> //Bluetooh lib

/******************************************/

/**********Variable definition:************/
int RX_bluetooh = 0;
int TX_bluetooh = 1;
int servo_pin = 13;
int obstacle_pin = 8;
int track1_pin = 12;
int final_pin = 7;
int motorR_forward = 10;
int motorR_reverse = 11;
int motorL_forward = 9;
int motorL_reverse = 6;
int buzzer = 5;
int R = 2;
int G = 3;
int B = 4;
int servo_open = 90;  //REVISAR ESTOS VALORES PARA SETEO DE GRADOS DE MOVIMIENTO DEL SERVO
int servo_close = 135; //REVISAR ESTOS VALORES PARA SETEO DE GRADOS DE MOVIMIENTO DEL SERVO
double adjustM_delay = 2;
double stopD = 0;
double motorPower = 129;
/*  PWM values for motorPower:
     _______________________________
    |   value   |  Ciclo de trabajo |
    |===============================|
    |    0      |       0%          |
    |    63     |       25%         |
    |    127    |       50%         |
    |    190    |       75%         |
    |    255    |       100%        |
    |_______________________________|
*/

bool obstacle_presence = digitalRead(obstacle_pin);
bool track1 = digitalRead(track1_pin);      //front detect                                  // detect = 0 //  no detect = 1  //
bool final_sensor = digitalRead(final_pin); //rear detect for final of track                // detect = 0 //  no detect = 1  //
bool state = 0;                             //  state = 0 -> tracking mode  //  state = 1 -> control mode //
int c;                                      //variable for serial readings

//IN TO READ FROM INTERFASE:
int left = 0;
int right = 0;
int go = 0;
int back = 0;

int reactionD = 2000;
/////////////

Servo myServo;
SoftwareSerial mySerial(RX_bluetooh, TX_bluetooh); // (RX,TX)

/******************************************/

/**********SETUP:************/
void setup()
{
  //Set for Serial communication:
  Serial.begin(9600);

  //Set for Bluetooh:
  mySerial.begin(38400);

  //Set for analog pin:
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);

  //Set for digital pin:
  pinMode(servo_pin, OUTPUT);
  pinMode(obstacle_pin, INPUT);
  pinMode(track1_pin, INPUT);
  pinMode(final_sensor, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(motorL_forward, OUTPUT);
  pinMode(motorL_reverse, OUTPUT);
  pinMode(motorR_forward, OUTPUT);
  pinMode(motorR_reverse, OUTPUT);

  //Set for servo
  myServo.attach(servo_pin);
  myServo.write(servo_close);
  delay(500);
  myServo.detach();

  analogWrite(motorR_forward, 0);
  analogWrite(motorL_forward, 0);
  analogWrite(motorR_reverse, 0);
  analogWrite(motorL_reverse, 0);
}

/*******************  LOOP : **********************/
void loop()
{

  //CONTROL MODE
  /*if (mySerial.available())
    {
    c = mySerial.read();

    while (c == 'a')
    {
      goR_control();
      c = mySerial.read();
    }

    while (c == 'd')
    {
      goL_control();
      c = mySerial.read();
    }

    while (c == 'w')
    {
      forward_control();
      c = mySerial.read();
    }

    while (c == 's')
    {
      reverse_control();
      c = mySerial.read();
    }

    while (c == 't')
    {
      trompo();
      c = mySerial.read();
    }
    }*/

  goR();
  goL();


  //obstacle_detection(obstacle_presence);
  /*
    if (end_detection(track1, final_sensor) == true)
    {
    delay(250);
    final_track_indicator();
    delay(250);
    state = 1;
    ////////////
    //    ACÁ NECESITAMOS METER EL CÓDIGO QUE LEE LOS VALORES QUE VIENEN DE LA INTERFAZ PARA ASIGNARLOS Y USARLOS EN EL CONTROLMODE
    ///////////
    }*/
}

//****************FUNCTIONS: **********************

///////////////////////////////////////////////////
void goR () {
  while (track1 != 1) {
    track1 = digitalRead(track1_pin);
    analogWrite(motorR_forward, 0);
    analogWrite(motorL_forward, motorPower);
    analogWrite(motorR_reverse, 0);
    analogWrite(motorL_reverse, 0);
    delay (adjustM_delay);
  };

  analogWrite(motorR_forward, 0);
  analogWrite(motorL_forward, 0);
  analogWrite(motorR_reverse, 0);
  analogWrite(motorL_reverse, 0);
  delay(stopD);

};

///////////////////////////////////////////////////
void goL () {
  while (track1 != 0) {
    track1 = digitalRead(track1_pin);
    analogWrite(motorR_forward, motorPower);
    analogWrite(motorL_forward, 0);
    analogWrite(motorR_reverse, 0);
    analogWrite(motorL_reverse, 0);
    delay (adjustM_delay);

  };
  analogWrite(motorR_forward, 0);
  analogWrite(motorL_forward, 0);
  analogWrite(motorR_reverse, 0);
  analogWrite(motorL_reverse, 0);
  delay(stopD);

}
///////////////////////////////////////////////////
void goR_control()
{
  analogWrite(motorL_reverse, 0);
  analogWrite(motorL_forward, 0);
  analogWrite(motorR_reverse, 0);
  analogWrite(motorR_forward, motorPower);
  delay(reactionD);
};
///////////////////////////////////////////////////
void goL_control()
{
  analogWrite(motorL_reverse, 0);
  analogWrite(motorL_forward, motorPower);
  analogWrite(motorR_reverse, 0);
  analogWrite(motorR_forward, 0);
  delay(reactionD);
};
///////////////////////////////////////////////////
void forward_control()
{
  analogWrite(motorL_reverse, 0);
  analogWrite(motorL_forward, motorPower);
  analogWrite(motorR_reverse, 0);
  analogWrite(motorR_forward, motorPower);
  delay(reactionD);
};
///////////////////////////////////////////////////
void reverse_control()
{
  analogWrite(motorL_reverse, motorPower);
  analogWrite(motorL_forward, 0);
  analogWrite(motorR_reverse, motorPower);
  analogWrite(motorR_forward, 0);
  delay(reactionD);
};
///////////////////////////////////////////////////
bool end_detection(bool _track1, bool _track2)
{
  bool FINAL_DE_PISTA = false;
  if (_track1 == true && _track2 == true)
  {
    FINAL_DE_PISTA = true;
  }
  return FINAL_DE_PISTA;
};

///////////////////////////////////////////////////
void obstacle_detection(bool _obstacle_presence)
{
  if (_obstacle_presence == true)
  {
    myServo.attach(servo_pin);
    myServo.write(servo_open);
    delay(700);
    myServo.write(servo_close);
    delay(700);
  };
  myServo.detach();
}

///////////////////////////////////////////////////
void final_track_indicator()
{
  digitalWrite(R, HIGH);
  delay(100);
  digitalWrite(R, LOW);
  delay(50);
  digitalWrite(G, HIGH);
  delay(100);
  digitalWrite(G, LOW);
  delay(50);
  digitalWrite(B, HIGH);
  delay(100);
  digitalWrite(B, LOW);
  delay(50);
  digitalWrite(R, HIGH);
  delay(100);
  digitalWrite(R, LOW);
  delay(50);
  digitalWrite(G, HIGH);
  delay(100);
  digitalWrite(G, LOW);
  delay(50);
  digitalWrite(B, HIGH);
  delay(100);
  digitalWrite(B, LOW);
  delay(50);
};

///////////////////////////////////////////////////
void trompo()
{
  analogWrite(motorL_reverse, motorPower);
  analogWrite(motorL_forward, 0);
  analogWrite(motorR_reverse, 0);
  analogWrite(motorR_forward, motorPower);
  delay(reactionD);
};

///////////////////////////////////////////////////
/*void controlMode(bool _state, char _left, char _right, char _go, char _back)
  {
    while (_state == 1)
    {
        _left = ;
        _right = ;
        _go = ;
        _back = ;
        while (_left == 'a')
        {
            goR();
        };
        while (_right == 1)
        {
        };

        while (_go == 1)
        {
        };

        while (_back == 1)
        {
        };
    }
  };

  ///////////////////////////////////////////////////
*/
