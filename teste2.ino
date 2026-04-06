const int trigPin = 5;
const int echoPin = 18;
const int LedVerde = 13;
const int LedVermelho = 12;
const int motor1Pin1 = 23; 
const int motor1Pin2 = 22; 
const int enable1Pin = 21; 
const int motor2Pin1 = 4; 
const int motor2Pin2 = 27; 
const int enable2Pin = 25;




const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 200;
//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define LED 2

long duration;
float distanceCm;
float distanceInch;
int luvaimport;

void setup() {
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(LedVerde, OUTPUT);
  pinMode(LedVermelho, OUTPUT);
  // sets the pins as outputs:
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  
  // configure LEDC PWM
  ledcAttachChannel(enable2Pin, freq, resolution, pwmChannel);
  ledcAttachChannel(enable1Pin, freq, resolution, pwmChannel);
}

void loop() {
  moverfrente();
  delay(1000);
  moverdireitafrente();
  delay(1000);
}
 void receberluva(){
  luvaimport= random(1, 4);
  interpretarluva(luvaimport);
 }

 void interpretarluva(int luvaimport){
  if (luvaimport==1){//frente
    calculardistancia();
    if (distanceCm>5){
      moverfrente();
    }
  }
  if (luvaimport==2){//trás
    movertras();
  }
  if (luvaimport==3){//direita pra frente
   calculardistancia();
    if (distanceCm>5){
     moverdireitafrente();
    }
  }
  if (luvaimport==4){//esquerda frente
    calculardistancia();
    if (distanceCm>5){
     moveresquerdafrente();
    }
  }
 }

 void calculardistancia(){
 digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
 }

 void moverfrente(){
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  digitalWrite(motor1Pin2, HIGH); 
 }

void movertras(){
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW); 
  digitalWrite(motor1Pin2, LOW);
}

void parar(){
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor1Pin2, LOW);
}
void moverdireitafrente(){
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor1Pin2, HIGH); 
}
void moveresquerdafrente(){
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor2Pin2, HIGH);
  digitalWrite(motor1Pin2, LOW); 
}