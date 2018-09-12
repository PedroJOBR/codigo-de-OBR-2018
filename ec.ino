#include <QTRSensors.h>
#include "Ultrasonic.h"
#include <Servo.h>
// testabdoddd

Servo garra;
//-------------------------------------Biblioteca
int branco = 300;
int preto = 500;
int tempo = 180;
int p2 = 200;
int p3 = 400;
int sensor_1 = 0;
int sensor_2 = 0;
int sensorE = 0;
int sensorD = 0;
int verde = 300;
int TCRT_D = A11;
int TCRT_E = A10;
int TCRT_f1 = A14;
int TCRT_f2 = A15;
int vm = 180;

//----------------area_vitima
int parede = 60;
int parede_p = 20;
unsigned long time;

//-----------------------------------sensores
#define NUM_SENSORS             8  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  2  // average 4 analog samples per sensor reading
#define EMITTER_PIN              53 // emitter is controlled by digital pin 2

QTRSensorsAnalog qtra((unsigned char[]) {
  7, 6, 5, 4, 3, 2, 1, 0
},

NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS]; 

//----------------------------------Ultrassônicos
Ultrasonic ultrasonic_F(30,31);
Ultrasonic ultrasonic_E(34,32);
Ultrasonic ultrasonic_D(33,36);
 int frente_U = ultrasonic_F.Ranging(CM);
 int direita_U = ultrasonic_D.Ranging(CM);
 int esquerda_U = ultrasonic_E.Ranging(CM);


//----------------------------------motorea
//motor_A
int neg1 = 28 ;
int pos1 = 26 ;

//motor_B
int neg2 = 22 ;
int pos2 = 24 ;
void setup()
{
  Serial.begin(9600);  //  setup porta serial
  pinMode(neg1, OUTPUT);
  pinMode(pos1, OUTPUT);
  pinMode(neg2, OUTPUT);
  pinMode(pos2, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  qtr_cal();
  garra.attach(18);
  // rampa();

}

void loop()
{
  desligar();
  unsigned int position = qtra.readLine(sensorValues);
  oi();
  ultra();
  sensor_1 = analogRead(TCRT_f1);
  sensor_2 = analogRead(TCRT_f2);

  sensorE = analogRead(TCRT_E);
  sensorD = analogRead(TCRT_D);

  int frente_U = ultrasonic_F.Ranging(CM);
 int direita_U = ultrasonic_D.Ranging(CM);
 int esquerda_U = ultrasonic_E.Ranging(CM);

  int qtr1 = sensorValues[0];//                                                                  ||                  ||
  int qtr2 = sensorValues[1];//                                                                  ||                  ||
  int qtr3 = sensorValues[2];//                                                                  ||                  ||
  int qtr4 = sensorValues[3];//                                |qtr1|   |qtr2|   |qtr3|   |qtr4| || |qtr5|    |qtr6| ||  |qtr7|   |qtr8|
  int qtr5 = sensorValues[4];//                                                                  ||                  ||
  int qtr6 = sensorValues[5];//                                                                  ||                  ||
  int qtr7 = sensorValues[6];//                                                                  ||                  ||
  int qtr8 = sensorValues[7];//                                                                  ||                  ||

 if (position == 0 || position > 6300 ) {
    frente(vm); Serial.println("frente");
  //ligar();
  }
  if ( sensor_1 > p2 && sensor_2 > p2) {
    frente(vm); Serial.println("frente _ ww - preto");
    //ligar();
  }
  if ( sensor_1 < p2 && sensor_2 < p2) {
    frente(vm); Serial.println("frente _ ww _ branco");
    //ligar();
  }
  if (qtr1 > preto && qtr2 > preto && qtr3 > preto && qtr4 > preto && qtr5 > preto && qtr6 > preto && qtr7 > preto && qtr8 > preto) {
    frente(vm); Serial.println("pretos");
    //ligar();
  }
  
  //-----------------------------------------------------------ESQUERDA
 if (sensor_1 < branco && position > 0 && position < 6400) {
    esque(vm); Serial.println("frente1__esquerda");
    //led_E();
  }
  if((qtr3 > preto || qtr2 > preto ) && sensorD < p2){
    //led_E();
    esquerda(vm);  Serial.println("esqireuda__esquerda");
  }
  /*if ((qtr1 > preto || qtr2 > preto || qtr3 > preto) && sensorD < p2) {
    esquerda(vm); Serial.println("ESQUERDA___");
  }*/

  if ((qtr1 > preto && qtr2 > preto && qtr3 > preto) && (sensor_1 > p2 || sensor_2 > p2) ) {
    frente(vm); Serial.println("engano");
    //led_E();
  }
  else if ((qtr1 > preto && qtr2 > preto && qtr3 > preto) && sensorE > p3 && (sensor_1 < p2 && sensor_2 < p2)) {
    frente(vm); delay(300);
   // led_E();
    do {
      oi();
      sensor_1 = analogRead(TCRT_f1);
      sensor_2 = analogRead(TCRT_f2);
      esquerda(vm);
    } while (sensor_1 < p3  ||  sensor_2 < p3);

    Serial.println("saiu esquerda");
    frente(0);
    delay(1000);
  }
    else if (((qtr1 > p2 && qtr2 > p2 && qtr3 > p2 && qtr4 > p2 && qtr5 > p2 ) && sensorE < branco) || ((qtr1 < branco && qtr2 > verde && qtr3 > verde && qtr4 > verde && qtr5 > verde ) && sensorE < branco)) {
    //led_E();
    frente(vm); delay(400);
    esquerda(vm); delay(300);
    Serial.println("entreiiii __ esquerda");
    do {
      oi();
      sensor_1 = analogRead(TCRT_f1);
      sensor_2 = analogRead(TCRT_f2);
      esquerda(vm);
    } while (sensor_1 < p3  ||  sensor_2 < p3);

    Serial.println("saiu esquerda");
    frente(vm);
    delay(200);
    frente(0);
    delay(1000);
  }

   
  //-------------------------------------------------------------------------DIREITA
if (sensor_2 < branco && position > 0 && position < 6400) {
    direi(vm ); Serial.println("frente2- direita");
    //led_D();
  }
  if (qtr6 > preto && qtr7 > preto ) {
    //led_D();
    direita(vm); Serial.println("DIREITA___");
    //delay(tempo);
  }
 /* if(sensorD > p3 && position > 0 && position < 7000){
    direi(vm);  Serial.println("direit__direit");
  }
  */
  if ((qtr6 > preto && qtr7 > preto && qtr8 > preto) && (sensor_1 > p2 || sensor_2 > p2) ) {
    //led_D();
    frente(vm); Serial.println("engano_D");
  }
  else if (/*(qtr6 > preto && qtr7 > preto && qtr8 > preto)*/  (sensor_1 < p2 && sensor_2 < p2) && sensorD > p3) {
    //led_D();
    frente(vm); delay(300);
    do {
      sensor_1 = analogRead(TCRT_f1);
      sensor_2 = analogRead(TCRT_f2);
      direita(vm);
    } while ((sensor_1 < 400 || sensor_1 > 600) || (sensor_2 < 400 || sensor_2 > 600));
    Serial.println("saiu direita"); 
    frente(0);
    delay(1000);
  }
  
    else if (((qtr4 > verde && qtr5 > verde && qtr6 > verde-100 && qtr7 > preto && qtr8 > preto) && sensorD < branco) || ((qtr4 > verde && qtr5 > verde && qtr6 > verde-100 && qtr7 > preto && qtr8 < branco) && sensorD < branco)) {
  //  led_D();
    frente(vm); delay(400);
    direita(vm); delay(300);
    Serial.println("entreiiii------direita");
    do {
      sensor_1 = analogRead(TCRT_f1);
      sensor_2 = analogRead(TCRT_f2);
      direita(vm);
    } while ((sensor_1 < 400 || sensor_1 > 600) || (sensor_2 < 400 || sensor_2 > 600));
    Serial.println("saiu direita_verde");
   frente(vm);
    delay(300);
    frente(0);
    delay(1000);
  }
// ---------------------------------------------- condiçoes de ultra

  if(frente_U > 0 && frente_U < 2){
    atras(vm);
    delay(300);
    desviar();
  }
  else if(esquerda_U > 0 &&esquerda_U < 5 && direita_U > 0 && direita_U < 5){
    frente(vm);
    delay(800);
    rampa();  
  }
}


//--------------------Desviando de Obstaculos

void desviar(){
   
  sensor_1 = analogRead(TCRT_f1);
  sensor_2 = analogRead(TCRT_f2);
Serial.println("entrei");
  
   frente(0);
   delay(500);
   esquerda(vm);
   delay(1240);
   frente(vm);
   delay(1000);
   direita(vm);
   delay(1050);
   frente(vm);
   delay(2000);
   direita(vm);
   delay(1260);
Serial.println("sair");
  sensor_1 = analogRead(TCRT_f1);
  sensor_2 = analogRead(TCRT_f2);

 frente(vm);
 if(sensor_1 > p3 && sensor_2 > p3){
frente(vm);
delay(200);
  sensor_1 = analogRead(TCRT_f1);
  sensor_2 = analogRead(TCRT_f2);

  do {
      sensor_1 = analogRead(TCRT_f1);
      sensor_2 = analogRead(TCRT_f2);
  esquerda(vm);
    } while ((sensor_1 < 400 || sensor_1 > 600) || (sensor_2 < 400 || sensor_2 > 600));
 }
 
  }
//--------------------------Rampa


void ultra(){
 int frente_U = ultrasonic_F.Ranging(CM);
 int direita_U = ultrasonic_D.Ranging(CM);
 int esquerda_U = ultrasonic_E.Ranging(CM);

  Serial.print(" ((  ");
  Serial.print("(F-");
  Serial.print(frente_U);
  Serial.println("cm) ");
  delay(41);
 /* 
  Serial.print("(D-");
  Serial.print(direita_U);
  Serial.print("cm) ");
  
  Serial.print("(E-");
  Serial.print(esquerda_U);
  Serial.print("cm) ");
  Serial.println(" ))");
  delay(41);
  */
}
// ligando os leds


