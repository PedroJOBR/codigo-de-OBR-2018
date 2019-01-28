#ifndef ListaDeFuncoes_h
#define ListaDeFuncoes_h
 
#include <Arduino.h>

class Robo
{
    public:
        //construtor
        Robo(int nada);

        //funções da classe
        void seguirLinha();
        void calibrarSensores();
        void cruzada(bool motor, int velocidade);
        bool checarEncruzilhada();
        int checarVerde();
        void atravessar(int posicaoVerde);
        bool checarGap();

        //constantes do controle PID
        float KP; 
        float KI; 
        float KD;
 
    private:
      // variáveis de encruzilhada
        bool frente;
        unsigned int qtrArray1[];
        unsigned int qtrArray2[];
    
      // variáveis do motor
        uint8_t Lin1 = 3;
        uint8_t Lin2 = 4;
        uint8_t Rin1 = 5;
        uint8_t Rin2 = 6;
        uint8_t Mmode = 7;
        bool motorEsquerda = 1;
        bool motorDireita = 0;

      // variáveis do controle PID
        int setpoint = 2500; // como são 6 sensores, os valores variam de 0 a 5.000, onde 2.500 são a metade, ou seja, o robô anda simétrico sobre a linha
        int integral = 0;
        int erroAnterior = 0;
        int velocidadeMotor1 = 255;
        int velocidadeMotor2 = 255;
        // sensores de 0 a 5 estão conectados as entradas analógicas 1 a 6, respectivamente

      // variáveis do sensor RGB
        uint8_t r1 = 8;
        uint8_t g1 = 9;
        uint8_t b1 = 10;
        uint8_t LDR1 = 10;
        uint8_t r2 = 24;
        uint8_t g2 = 26;
        uint8_t b2 = 28;
        uint8_t LDR2 = 9;

      // variaveis de cor
        int preto = 750;
        int branco = 100;
};
 
#endif
