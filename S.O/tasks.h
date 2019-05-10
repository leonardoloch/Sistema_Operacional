#ifndef TASKS_H
#define	TASKS_H

#include "types.h"
#include "config.h"

//TASK pisca_led_red();
TASK pisca_led_yellow();
TASK pisca_led_green();
TASK verificarInput();
void modificar_temp();
void botaoAumentar();
void mostraDisplay(int unidade,int dezena, char identificador);

#endif	/* TASKS_H */

