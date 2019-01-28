#include "ListaDeFuncoes.h"
#include <QTRSensors.h>

#define esquerda 1
#define direita 2
#define duploV 3


QTRSensorsAnalog matrizSensores((unsigned char[]) {1, 2, 3, 4, 5, 6 }, 6);
QTRSensorsAnalog matrizSensores2((unsigned char[]) {7, 8}, 2);




Robo::Robo(int nada){
  pinMode(Rin1 ,OUTPUT);
  pinMode(Rin2 ,OUTPUT);
  pinMode(Lin1 ,OUTPUT);
  pinMode(Lin2 ,OUTPUT);
  pinMode(Mmode, INPUT_PULLUP);
  pinMode(r1, OUTPUT);
  pinMode(g1, OUTPUT);
  pinMode(b1, OUTPUT); 
  pinMode(r2, OUTPUT); 
  pinMode(g2, OUTPUT);
  pinMode(b2, OUTPUT);
}




bool Robo::checarEncruzilhada(){

  unsigned int pos1 = matrizSensores.readLine(qtrArray1);
  unsigned int pos2 = matrizSensores2.readLine(qtrArray2);
  
  if(qtrArray1[0] > preto && qtrArray1[1] > preto && qtrArray1[2] > preto && qtrArray1[3] > preto && qtrArray1[4] > preto && qtrArray1[5] > preto){
    frente = 0;
    return true;
  }
  
  if(qtrArray2[0] > preto && qtrArray2[1] > preto){
    frente = 1;
    if(qtrArray1[3] > preto && qtrArray1[4] > preto && qtrArray1[5] > preto)
      return true;
    else if(qtrArray1[2] > preto && qtrArray1[1] > preto && qtrArray1[0] > preto)
      return true;
  }

  frente = 0;
  return false;
}




int Robo::checarVerde(){ qualque coisa so editar aqui essas condiçoes
  int posicao;
  int media[4];
  int maior = 0;
  
  for(int j = 0; j<=200; j++){
    int LDR_d = analogRead(LDR1);
    int LDR_e = analogRead(LDR2);
    
    if ((LDR_d > 400 && LDR_d < 480) && LDR_e < 400 ){ // editei aqui, acrecentando o da direita
      media[direita] += 1;
      if((LDR_e > 400 && LDR_e < 480) && (LDR_d > 400 && LDR_d < 480))
        media[duploV] += 1;
    }
    if ((LDR_e > 400 && LDR_e < 480) && (LDR_d < 400 )){ // editei aqui, acrecentando o da esquerda
      media[esquerda] += 1;
      if((LDR_e > 400 && LDR_e < 480) && (LDR_d > 400 && LDR_d < 480))
        media[duploV] += 1;
    }
    if (LDR_e < 400 && LDR_d < 400)
      media[0] += 1;

    digitalWrite(r1, 1);
    digitalWrite(g1, 1);
    digitalWrite(b1, 0);
    digitalWrite(r2, 1);
    digitalWrite(g2, 1);
    digitalWrite(b2, 0);
    delay(1);
  }
    
  for(int k = 0; k<4; k++){
      if(media[k] > maior)
        maior = k;
  }
  
  posicao = maior;
  return posicao;
}




bool Robo::checarGap(){
  unsigned int pos1 = matrizSensores.readLine(qtrArray1);
  if(qtrArray1[0] < 100 && qtrArray1[1] < 100 && qtrArray1[2] < 100 && qtrArray1[3] < 100 && qtrArray1[4] < 100 && qtrArray1[5] < 100)
    return 1;
  else
    return 0;
}




void Robo::atravessar(int posicaoVerde){
  int contador;
  
  // estadoAnterior = 1 = preto
  // estadoAnterior = 0 = branco
  bool estadoAnterior = 0;

  // caso 1 = verde na esquerda
  switch(posicaoVerde){
    
    // encruzilhada sem o verde
    case 0:
      while(qtrArray1[5] > 100 || qtrArray1[0] > 100){
        unsigned int pos1 = matrizSensores.readLine(qtrArray1);
        cruzada(motorDireita, 255);
        cruzada(motorEsquerda, 255);
      }
    break;

    // detecção do verde para esquerda
    case 1:
      while(qtrArray1[5] > 200){
        unsigned int pos1 = matrizSensores.readLine(qtrArray1);
        cruzada(motorDireita, 0);
        cruzada(motorEsquerda, 0);
      }
      
      if(frente){
        while(contador != 4){
          unsigned int pos1 = matrizSensores.readLine(qtrArray1);
          if(qtrArray1[5] < 200){
            cruzada(motorDireita, 255);
            cruzada(motorEsquerda, 255);  
          }
          else{
            cruzada(motorDireita, 255);
            cruzada(motorEsquerda, 0);
          }
          if(qtrArray1[0] > 200 && estadoAnterior == 0){
            contador += 1;
            estadoAnterior = 1;
          }
          if(qtrArray1[0] < 50 && estadoAnterior == 1){
            contador += 1;
            estadoAnterior = 0;
          }
        }
      }
      
      else{
        while(contador != 2){
          unsigned int pos1 = matrizSensores.readLine(qtrArray1);
          if(qtrArray1[5] < 200){
            cruzada(motorDireita, 255);
            cruzada(motorEsquerda, 255);  
          }
          else{
            cruzada(motorDireita, 255);
            cruzada(motorEsquerda, 0);
          }
          if(qtrArray1[0] > 200 && estadoAnterior == 0){
            contador += 1;
            estadoAnterior = 1;
          }
          if(qtrArray1[0] < 50 && estadoAnterior == 1){
            contador += 1;
            estadoAnterior = 0;
          }
        }
      }
    break;

    // detecção do verde para direita
    case 2:
      while(qtrArray1[0] > 200){
        unsigned int pos1 = matrizSensores.readLine(qtrArray1);
        cruzada(motorDireita, 0);
        cruzada(motorEsquerda, 0);
      }
      
      if(frente){
        while(contador != 4){
          unsigned int pos1 = matrizSensores.readLine(qtrArray1);
          if(qtrArray1[0] < 200){
            cruzada(motorDireita, 255);
            cruzada(motorEsquerda, 255);  
          }
          else{
            cruzada(motorDireita, 255);
            cruzada(motorEsquerda, 0);
          }
          if(qtrArray1[5] > 200 && estadoAnterior == 0){
            contador += 1;
            estadoAnterior = 1;
          }
          if(qtrArray1[5] < 50 && estadoAnterior == 1){
            contador += 1;
            estadoAnterior = 0;
          }
        }
      }
      else{
        while(contador != 2){
          unsigned int pos1 = matrizSensores.readLine(qtrArray1);
          if(qtrArray1[0] < 200){
            cruzada(motorDireita, 255);
            cruzada(motorEsquerda, 255);  
          }
          else{
            cruzada(motorDireita, 255);
            cruzada(motorEsquerda, 0);
          }
          if(qtrArray1[5] > 200 && estadoAnterior == 0){
            contador += 1;
            estadoAnterior = 1;
          }
          if(qtrArray1[5] < 50 && estadoAnterior == 1){
            contador += 1;
            estadoAnterior = 0;
          }
        }
      }
    break;

    // detecção do verde duplo
    case 3:
      
    break;

    // detecção de gaps em geral
    default:
      while(qtrArray1[5] < 750 && qtrArray1[4] < 750 && qtrArray1[3] < 750 && qtrArray1[2] < 750 && qtrArray1[1] < 750 && qtrArray1[0] < 750){
        unsigned int pos1 = matrizSensores.readLine(qtrArray1);
        cruzada(motorDireita, 255);
        cruzada(motorEsquerda, 255); 
      }
    break;
    
  }
}




void Robo::calibrarSensores(){
  delay(500);
  for (int i = 0; i < 200; i++) // faz a calibração tomar cerca de 5 segundos
  {
    matrizSensores.calibrate(); // lê todos os sensores 10 vezes em 2.5 ms por 6 sensores (~25 ms por chamada da função)
    matrizSensores2.calibrate();
  }  
}




void Robo::seguirLinha(){
  // leitura dos sensores
  unsigned int arraySensores[6];  
  int leituraSensores = matrizSensores.readLine(arraySensores);
  
  // cálculo do PID
  int erro = leituraSensores - setpoint;
  int sinalControlador = KP * erro + KD * (erro - erroAnterior) + KI * integral;
  erroAnterior = erro;
  int novaVelocidadeMotor1 = velocidadeMotor1 + sinalControlador;
  int novaVelocidadeMotor2 = velocidadeMotor2 - sinalControlador;
  integral = integral + erro;
 
  // correção dos valores extremos dos motores
  if (novaVelocidadeMotor1 < 127)
    novaVelocidadeMotor1 = 127;
  if (novaVelocidadeMotor2 < 127)
    novaVelocidadeMotor2 = 127;
 
  if (novaVelocidadeMotor1 > 255)
    novaVelocidadeMotor1 = 255;
  if (novaVelocidadeMotor2 > 255)
    novaVelocidadeMotor2 = 255;
 
  // aplicação das novas velocidades dos motores via PWM
  cruzada(motorEsquerda,novaVelocidadeMotor1);
  cruzada(motorDireita,novaVelocidadeMotor2);  
}




void Robo::cruzada(bool motor, int velocidade){
  // função responsável por fazer a conversão do sistema 0 a 255 das entradas analógicas, onde:
  // para 0 a 126, o motor irá se mover p/ trás 
  // para 127, o motor estará parado
  // para 128 a 255, o motor irá se mover p/ frente
  
  if(motor > 0){
    if(velocidade == 127){
      analogWrite(Rin2, 255);
    }
    if(velocidade > 127){
      digitalWrite(Rin1, 1);
      analogWrite(Rin2, map(velocidade, 128, 255, 255, 0));
    }
    if(velocidade < 127){
      digitalWrite(Rin1, 0);
      analogWrite(Rin2, map(velocidade, 0, 126, 255, 0));
    }
  }
  if(motor <= 0){
    if(velocidade == 127){
      analogWrite(Lin2, 255);
    }
    if(velocidade > 127){
      digitalWrite(Lin1, 1);
      analogWrite(Lin2, map(velocidade, 128, 255, 255, 0));
    }
    if(velocidade < 127){
      digitalWrite(Lin1, 0);
      analogWrite(Lin2, map(velocidade, 0, 126, 255, 0));
    }
  }
}
