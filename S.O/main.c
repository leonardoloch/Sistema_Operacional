#include <xc.h>
#include "kernel.h"
#include "tasks.h"
#include "timer.h"

int main(void) 
{
    // Inicia as estruturas de dados do S.O
    nojoStart();
    setupTimer();
    
    Init_PWM_AD();
    
    // Instalar as tarefas
    //nojoTaskCreate(1, 10, pisca_led_red);
    //nojoTaskCreate(2, 5, pisca_led_yellow);
    nojoTaskCreate(3, 7, modificar_temp);
    nojoTaskCreate(3, 7,verificarInput);
    nojoScheduler();

    while(1)
    {
        NOP();
    }
    return (EXIT_SUCCESS);
}
