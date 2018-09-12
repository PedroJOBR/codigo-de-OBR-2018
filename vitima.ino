void rampa(){
  while(1){
  desligar();
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
  ligar();
  }
  if ( sensor_1 > p2 && sensor_2 > p2) {
    frente(vm); Serial.println("frente _ ww - preto");
    ligar();
  }
  if ( sensor_1 < p2 && sensor_2 < p2) {
    frente(vm); Serial.println("frente _ ww _ branco");
    ligar();
  }
  if (qtr1 > preto && qtr2 > preto && qtr3 > preto && qtr4 > preto && qtr5 > preto && qtr6 > preto && qtr7 > preto && qtr8 > preto) {
    frente(vm); Serial.println("pretos");
    ligar();
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
    led_D();
  }
  if ((qtr6 > preto || qtr7 > preto ) && sensorE < p2) {
    led_D();
    direita(vm); Serial.println("DIREITA___");
    //delay(tempo);
  }
//------------------entrando na area da vitima

if(esquerda > 10){
  frente(vm);
  delay(1000);
  area_vitima();
}
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
// ------------------------------ RAMPA


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
