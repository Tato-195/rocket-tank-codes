// ======================= PINOS =======================
const int trigPin = 5;
const int echoPin = 18;

const int motor1Pin1 = 23; 
const int motor1Pin2 = 22; 
const int enable1Pin = 21; 

const int motor2Pin1 = 4; 
const int motor2Pin2 = 27; 
const int enable2Pin = 25;

// ======================= PWM =======================
const int freq = 30000;
const int resolution = 8;

const int pwmChannel1 = 0;
const int pwmChannel2 = 1;

int dutyCycle = 200;

// ======================= SENSOR =======================
#define SOUND_SPEED 0.034

long duration;
float distanceCm;

int luvaimport;

// ======================= SETUP =======================
void setup() {
  Serial.begin(115200);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);

  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

  // PWM
  ledcAttachChannel(enable1Pin, freq, resolution, pwmChannel1);
  ledcAttachChannel(enable2Pin, freq, resolution, pwmChannel2);

  ledcWrite(enable1Pin, dutyCycle);
  ledcWrite(enable2Pin, dutyCycle);
}

// ======================= LOOP =======================
void loop() {
  receberluva();
  delay(500);
}

// ======================= LÓGICA =======================
void receberluva(){
  luvaimport = random(1, 5); // agora inclui 4
  interpretarluva(luvaimport);
}

void interpretarluva(int luvaimport){
  if (luvaimport == 1){ // frente
    calculardistancia();
    if (distanceCm > 5){
      moverfrente();
    } else {
      parar();
    }
  }
  else if (luvaimport == 2){ // trás
    movertras();
  }
  else if (luvaimport == 3){ // direita frente
    calculardistancia();
    if (distanceCm > 5){
      moverdireitafrente();
    } else {
      parar();
    }
  }
  else if (luvaimport == 4){ // esquerda frente
    calculardistancia();
    if (distanceCm > 5){
      moveresquerdafrente();
    } else {
      parar();
    }
  }
}

// ======================= SENSOR =======================
void calculardistancia(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_SPEED / 2;

  Serial.print("Distancia: ");
  Serial.println(distanceCm);
}

// ======================= MOVIMENTO =======================
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