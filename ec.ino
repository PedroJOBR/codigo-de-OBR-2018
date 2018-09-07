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
Ultrasonic ultrasonic_F(35,37);
Ultrasonic ultrasonic_E(34,32);
Ultrasonic ultrasonic_D(30,36);
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

}

void loop()
{

  unsigned int position = qtra.readLine(sensorValues);
  oi();
  int frente_U = ultrasonic_F.Ranging(CM);

  
  Serial.print("(F-");
  Serial.print(frente_U);
  Serial.println("cm) ");
  
  sensor_1 = analogRead(TCRT_f1);
  sensor_2 = analogRead(TCRT_f2);

  sensorE = analogRead(TCRT_E);
  sensorD = analogRead(TCRT_D);

  int qtr1 = sensorValues[0];//                                                                  ||                  ||
  int qtr2 = sensorValues[1];//                                                                  ||                  ||
  int qtr3 = sensorValues[2];//                                                                  ||                  ||
  int qtr4 = sensorValues[3];//                                |qtr1|   |qtr2|   |qtr3|   |qtr4| || |qtr5|    |qtr6| ||  |qtr7|   |qtr8|
  int qtr5 = sensorValues[4];//                                                                  ||                  ||
  int qtr6 = sensorValues[5];//                                                                  ||                  ||
  int qtr7 = sensorValues[6];//                                                                  ||                  ||
  int qtr8 = sensorValues[7];//                                                                  ||                  ||

  /*if(frente_U < 2){
    atras(vm);
    delay(300);
    desviar();
  }*/
  if ( sensor_1 > p2 && sensor_2 > p2) {
    frente(vm); Serial.println("frente _ ww - preto");
  }
  if ( sensor_1 < p2 && sensor_2 < p2) {
    frente(vm); Serial.println("frente _ ww _ branco");
  }
  if (qtr1 > preto && qtr2 > preto && qtr3 > preto && qtr4 > preto && qtr5 > preto && qtr6 > preto && qtr7 > preto && qtr8 > preto) {
    frente(vm); Serial.println("pretos");
  }
  //-----------------------------------------------------------ESQUERDA
  if (sensor_1 < branco && position > 0 && position < 7000) {
    esque(vm); Serial.println("frente1__esquerda");
  }
  /*if ((qtr1 > preto || qtr2 > preto || qtr3 > preto) && sensorD < p2) {
    esquerda(vm); Serial.println("ESQUERDA___");
  }*/

  if ((qtr1 > preto && qtr2 > preto && qtr3 > preto) && (sensor_1 > p2 || sensor_2 > p2) ) {
    frente(vm); Serial.println("engano");

  }
  else if ((qtr1 > preto && qtr2 > preto && qtr3 > preto) && (sensor_1 < p2 && sensor_2 < p2)) {
    frente(vm); delay(300);
    do {
      sensor_1 = analogRead(TCRT_f1);
      sensor_2 = analogRead(TCRT_f2);
      esquerda(vm);
    } while ((sensor_1 < 400 || sensor_1 > 600) || (sensor_2 < 400 || sensor_2 > 600));

    Serial.println("saiu esquerda");
    frente(0);
    delay(1000);
  }
    else if ((qtr1 > verde && qtr2 > verde && qtr3 > verde && qtr4 > verde && qtr5 > verde ) && sensorE < branco) {
    frente(vm); delay(400);
    esquerda(vm); delay(300);
    Serial.println("entreiiiiiiiiiii tmbbbbbbbbbbbb");
    do {
      sensor_1 = analogRead(TCRT_f1);
      sensor_2 = analogRead(TCRT_f2);
      esquerda(vm);
    } while ((sensor_1 < 400 || sensor_1 > 600) || (sensor_2 < 400 || sensor_2 > 600));

    Serial.println("saiu esquerda");
    frente(vm);
    delay(200);
    frente(0);
    delay(1000);
  }
    
    



  //-------------------------------------------------------------------------DIREITA

  if (sensor_2 < branco && position > 0 && position < 7000) {
    direi(vm ); Serial.println("frente2- direita");
  }
  /*if ((qtr6 > preto || qtr7 > preto || qtr8 > preto) && sensorE < p2) {
    direita(vm); Serial.println("DIREITA___");
    //delay(tempo);
  }*/
  if ((qtr6 > preto && qtr7 > preto && qtr8 > preto) && (sensor_1 > p2 || sensor_2 > p2)) {
    frente(vm); Serial.println("engano_D");
  }
  else if ((qtr6 > preto && qtr7 > preto && qtr8 > preto) && (sensor_1 < p2 && sensor_2 < p2)) {
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
    else if ((qtr4 > verde && qtr5 > verde && qtr6 > verde-100 && qtr7 > preto && qtr8 > preto) && sensorD < branco) {
    frente(vm); delay(500);
    direita(vm); delay(300);
    Serial.println("entreiiii------------------------------------------------------------");
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
  

//localizar();

}
void frente(int pwm) {

  analogWrite(pos1, pwm);
  analogWrite(neg1, 0);

  analogWrite(pos2, pwm);
  analogWrite(neg2, 0);
}
void atras(int pwm) {

  analogWrite(pos1, 0);
  analogWrite(neg1, pwm);

  analogWrite(pos2, 0);
  analogWrite(neg2, pwm);
}
void direi(int pwm){
  analogWrite(pos1, pwm);
  analogWrite(neg1, pwm);

  analogWrite(pos2, pwm);
  analogWrite(neg2, 0);


}
void esquerda(int pwm) {

  analogWrite(pos1, pwm);
  analogWrite(neg1, 0);

  analogWrite(pos2, 0);
  analogWrite(neg2, pwm);

}
void esque(int pwm){
  
  analogWrite(pos1, pwm);
  analogWrite(neg1, 0);

  analogWrite(pos2, pwm);
  analogWrite(neg2, pwm);

}
void direita(int pwm) {

  analogWrite(pos1, 0);
  analogWrite(neg1, pwm);

  analogWrite(pos2, pwm);
  analogWrite(neg2, 0);
}



void qtr_cal()
{
  delay(500);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
  for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
  {
    qtra.calibrate();       // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
  }
  digitalWrite(13, LOW);     // turn off Arduino's LED to indicate we are through with calibration

  // print the calibration minimum values measured when emitters were on
  Serial.begin(9600);
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtra.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();

  // print the calibration maximum values measured when emitters were on
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtra.calibratedMaximumOn[i]);
    Serial.print(' ');

  }
  Serial.println();
  Serial.println();
  delay(1000);
}
void oi() {
  unsigned int position = qtra.readLine(sensorValues);
  sensorE = analogRead(TCRT_E);
  sensorD = analogRead(TCRT_D);

  // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
  // 1000 means minimum reflectance, followed by the line position
  Serial.print(sensorValues[0]);//                                                                  ||                  ||
  Serial.print('\t');
  Serial.print(sensorValues[1]);//                                                                  ||                  ||
  Serial.print('\t');
  Serial.print(sensorValues[2]);//                                                                  ||                  ||
  Serial.print('\t');
  Serial.print(sensorValues[3]);//                                |qtr1|   |qtr2|   |qtr3|   |qtr4| || |qtr5|    |qtr6| ||  |qtr7|   |qtr8|
  Serial.print('\t');
  Serial.print(sensorValues[4]);//                                                                  ||                  ||
  Serial.print('\t');
  Serial.print(sensorValues[5]);//                                                                  ||                  ||
  Serial.print('\t');
  Serial.print(sensorValues[6]);//                                                                  ||                  ||
  Serial.print('\t');
  Serial.print(sensorValues[7]);//                                                                  ||                  ||
  Serial.print('\t');

  sensor_1 = analogRead(TCRT_f1);
  sensor_2 = analogRead(TCRT_f2);
  Serial.print("(");
  Serial.print(sensorE);
  Serial.print(" --- ");
  Serial.print(sensorD);
  Serial.print(") ---");
  Serial.print(sensor_1);
  Serial.print(" --- ");
  Serial.print(sensor_2);
  Serial.print('\t');
  //Serial.println(); // uncomment this line if you are using raw values
  Serial.println(position); // comment this line out if you are using raw values
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

//--------------------------------------Localiza a área da vítima

void area_vitima(){
 ultra();
 int area_aonde = 0;
 int frente_U = ultrasonic_F.Ranging(CM);
 int direita_U = ultrasonic_D.Ranging(CM);
 int esquerda_U = ultrasonic_E.Ranging(CM);
 frente(0);
  if(frente_U < parede && esquerda_U > parede){
    area_aonde=1;
    digitalWrite(11, 1);
    delay(1000);
}
  else if(frente_U > parede && esquerda_U < parede){
    area_aonde=2;
    digitalWrite(12, 1);
    delay(1000);
}
  else if(frente_U > parede && esquerda_U > parede){
    area_aonde=3;
    digitalWrite(12, 1);
    digitalWrite(11, 1);
    delay(1000);
}
  
 digitalWrite(12, 0);
 digitalWrite(11, 0);
 frente(0);//tempo de espera
 delay(2000);
} 

//------------------------------------Localiza a vítima
void localizar(){
  time=millis();
  int tempinho=0;
  int tempo=2700;
  int confirm=0;
  int frente_U = ultrasonic_F.Ranging(CM);
  int direita_U = ultrasonic_D.Ranging(CM);
  int esquerda_U = ultrasonic_E.Ranging(CM);
 
  Serial.println(time);
  frente(vm);
    if(esquerda_U < parede_p){
      Serial.println("indo para frente");
      Serial.println(time);
      tempinho = time;
      PrimeiraRonda();
      tempo = tempo - tempinho;
      Serial.println(tempo);
      confirm=1; //se confirm for igual a 1 ele já pegou a vítima e não fará a segunda ronda  
    }
    /*else if(frente < parede_p){
      segunda_ronda();
    }*/
    else if(time > tempo){
      meio();
    }

}

//------------------------------------Vai até o meio
void meio(){
  Serial.println("Estou indo ao meio!");
  frente(0);
  delay(1000);;
  esquerda(vm);
  delay(930);
  int frente_U = ultrasonic_F.Ranging(CM);
  int direita_U = ultrasonic_D.Ranging(CM);
  int esquerda_U = ultrasonic_E.Ranging(CM);
  time=millis();
  frente(vm);
  if(frente_U < 5){
    pegar();
  }
  else if(time > 1500){
    Serial.println("Cheguei ao meio!");
    frente(0);
    delay(100000);
    terceira_ronda();
  }
}

//------------------------------------Pega a vítima com a "garra" 
void pegar(){
      digitalWrite(12,1);
      digitalWrite(11,1);
      delay(1000);
      frente(0);
      delay(100000);
  
}

//------------------------------------Indica quantos centimetros os ultrassônicos estão lendo
// pegar a vitima
void pegacao(){
  
}

void PrimeiraRonda(){
 ultra();
 int frente_U = ultrasonic_F.Ranging(CM);
 int direita_U = ultrasonic_D.Ranging(CM);
 int esquerda_U = ultrasonic_E.Ranging(CM);
  
  Serial.println("gira atras da bola");
  esquerda(vm+30);
  delay(760); // menos de 90 graus para usar o ultrasonico para confirmar a bola
  do{
    int frente_U = ultrasonic_F.Ranging(CM);
    int direita_U = ultrasonic_D.Ranging(CM);
    int esquerda_U = ultrasonic_E.Ranging(CM);
    Serial.println("confirma a bola");

    esquerda(vm - 30);
    delay(40);
  }while(frente_U < 20);

  frente(0);
  delay(800);
    
  frente_U = ultrasonic_F.Ranging(CM);
  direita_U = ultrasonic_D.Ranging(CM);
  esquerda_U = ultrasonic_E.Ranging(CM);
 
  ultra();
  do{  
    int frente_U = ultrasonic_F.Ranging(CM);
    int direita_U = ultrasonic_D.Ranging(CM);
    int esquerda_U = ultrasonic_E.Ranging(CM);
    Serial.println("indo atras da bola");

    frente(vm);
    }while(frente_U < 5);
      Serial.println("pegando a bola");
      
      frente_U = ultrasonic_F.Ranging(CM);
      direita_U = ultrasonic_D.Ranging(CM);
      esquerda_U = ultrasonic_E.Ranging(CM);
 
      ultra();
      pegar();
      
  Serial.println("ferrou");
/*

//não encontrou a vítima, irá ao centro
  else if(time>6000 && confirm==0){
    Serial.println("Não encontrei a vítima ainda :(, calma que vai dar certo :), irei ao centro para buscar ela lá!");
    digitalWrite(12,1);
    digitalWrite(11,1);
    delay(10002);
  }*/

}

void segunda_ronda(){
  
}

void terceira_ronda(){
  frente(0);
  delay(10000);
}

void ultra(){
  Serial.print(" ((  ");
  Serial.print("(F-");
  Serial.print(frente_U);
  Serial.print("cm) ");
  
  Serial.print("(D-");
  Serial.print(direita_U);
  Serial.print("cm) ");
  
  Serial.print("(E-");
  Serial.print(esquerda_U);
  Serial.print("cm) ");
  Serial.println(" ))");
  delay(41);
}
