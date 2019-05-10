/* 
 * File:   perifericos.h
 * Author: leonardo
 *
 * Created on November 1, 2017, 12:59 PM
 */

#ifndef PERIFERICOS_H
#define	PERIFERICOS_H


unsigned int LerADC(void);
void PWM1_value(int velocidade,int resistencia);
int  map(int x, int in_min, int in_max, int out_min, int out_max);
#endif	/* PERIFERICOS_H */

