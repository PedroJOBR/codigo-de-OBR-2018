#include "ListaDeFuncoes.h"

// motor parado: 127
// velocidade máxima p/ frente: 255
// velocidade máxima p/ trás: 0
// função para chamar os motores: robo.cruzada(motor, velocidade);
// 0 = motor direita
// 1 = motor esquerda

Robo robo(0);

void setup()  
{
  robo.KP = 0.1;
  robo.KI = 0.00022;
  robo.KD = 0.18;
  robo.calibrarSensores();   
}

void loop()
{
  robo.seguirLinha();
  
  if(robo.checarEncruzilhada()){
    robo.atravessar(robo.checarVerde());
  }
  if(robo.checarGap()){
    robo.atravessar(5);
  }
}
