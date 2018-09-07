#include <QTRSensors.h>
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
//-----------------------------------sensores
#define NUM_SENSORS             8  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  2  // average 4 analog samples per sensor reading
#define EMITTER_PIN              53 // emitter is controlled by digital pin 2

QTRSensorsAnalog qtra((unsigned char[]) {
  7, 6, 5, 4, 3, 2, 1, 0
},
NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];



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
  qtr_cal();
}

void loop()
{
  unsigned int position = qtra.readLine(sensorValues);
  oi();
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

  if (position == 0 || position > 6300 ) {
    frente(vm); Serial.println("frente");
  }
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
  if (sensor_1 < branco && position > 0 && position < 6400) {
    esque(vm); Serial.println("frente1__esquerda");
  }
  if(sensorE > p3 && position > 0 && position < 6400){
    esquerda(vm);  Serial.println("esqireuda__esquerda");
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
    else if (((qtr1 > p2 && qtr2 > p2 && qtr3 > p2 && qtr4 > p2 && qtr5 > p2 ) && sensorE < branco) || ((qtr1 < branco && qtr2 > verde && qtr3 > verde && qtr4 > verde && qtr5 > verde ) && sensorE < branco)) {
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

  if (sensor_2 < branco && position > 0 && position < 6400) {
    direi(vm ); Serial.println("frente2- direita");
  }
  if ((qtr6 > preto || qtr7 > preto ) && sensorE < p2) {
    direita(vm); Serial.println("DIREITA___");
    //delay(tempo);
  }
 /* if(sensorD > p3 && position > 0 && position < 7000){
    direi(vm);  Serial.println("direit__direit");
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
    else if (((qtr4 > verde && qtr5 > verde && qtr6 > verde-100 && qtr7 > preto && qtr8 > preto) && sensorD < branco) || ((qtr4 > verde && qtr5 > verde && qtr6 > verde-100 && qtr7 > preto && qtr8 < branco) && sensorD < branco)) {
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
  


}
void frente(int pwm) {

  analogWrite(pos1, pwm);
  analogWrite(neg1, 0);

  analogWrite(pos2, pwm);
  analogWrite(neg2, 0);
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
