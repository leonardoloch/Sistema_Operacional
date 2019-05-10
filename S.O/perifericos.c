/* 
 * File:   perifericos.c
 * Author: leonardo
 *
 * Created on November 1, 2017, 12:58 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "delay.h"
#include "kernel.h"
#include "perifericos.h"


//-------------------------------------------------------
//--------------Sensor Temp------------------------------
unsigned int LerADC(void){
 unsigned int temp;

ADCON0bits.GO = 1;               // Inicia aquisição
 while(ADCON0bits.DONE);         // Aguarda o fim da aquisição (quando bit DONE = 0)
 temp = ADRESH;                  // Parte alta do valor lido
 temp = ((temp << 8)| ADRESL );  // Junta parte alta com parte baixa em um valor de 16 bits

return temp;
}


//------ MOTOR E RESISTENCIA 
void PWM1_value(int velocidade,int resistencia)
{    
    CCPR1L = velocidade; // pulse width = CCPR1L * prescaler * Tcy = 100us
    CCPR2L = resistencia; // pulse width = CCPR1L * prescaler * Tcy = 100us
}

//---------------------------Ajuda------------------------------------------

int  map(int x, int in_min, int in_max, int out_min, int out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}