#include "tasks.h"
#include "kernel.h"
#include "perifericos.h"
#include"semaphore.h"
#define   UP_TEMP        PORTAbits.RA1
#define   DOWN_TEMP      PORTAbits.RA2
sem_t sem;
//sem_create(&sem,2);
//sem_wait(&sem);
//sem_post(&sem);



//Max Temp é 40

int temperatura_desejada,unidade,dezena;

/*TASK pisca_led_red()
{
    TRISDbits.RD0 = 0;                                                          // D0 configurado como saída de dados
    PORTDbits.RD0 = 0;                                                          // Porta está em estado 0
    
    while(1)
    {
        PORTDbits.RD0 = ~LATDbits.LD0;
        nojoDelay(150);
    }
    
    return NULL;
}*/

TASK pisca_led_yellow()
{
    TRISAbits.RA3 = 0;                                                          // D0 configurado como saída de dados
    PORTAbits.RA3 = 0;                                                          // Porta está em estado 0
    
    while(1)
    {
        PORTAbits.RA3 = ~LATAbits.LA3;
        asm("nop");
        asm("nop");
        asm("nop");
    }
    
    return NULL;
}

TASK pisca_led_green()
{
    TRISAbits.RA4 = 0;                                                          // D0 configurado como saída de dados
    PORTAbits.RA4 = 0;                                                          // Porta está em estado 0
    
    while(1)
    {
        PORTAbits.RA4 = ~LATAbits.LA4;
        asm("nop");
        asm("nop");
        asm("nop");
    }
    
    return NULL;
}

void valor_res_motor(unsigned int temp)
{   
    int  motor,resistor;
    if(temp>=20)
    {
        //20° 20% motor e resistencia 40° 100% de ambos
        motor=10*temp+150;
        resistor=10*temp+150;
        PWM1_value(motor,resistor);
    
    }
    else
    { 
        motor=-10*temp+250;       
        PWM1_value(motor,0);        
    
    }


}
void modificar_temp()
{
    TRISAbits.RA4 = 0;                                                          // D0 configurado como saída de dados
    PORTAbits.RA4 = 0; 
    
    unsigned int temp;
    while(1)
    {        
        PORTAbits.RA4 = ~LATAbits.LA4;
        temp=LerADC();
        while(temp!=map(temperatura_desejada, 0, 99, 0, 1023))//Tem q converter o valor do sensor para comparar com uma temp real
        {
            temp=LerADC();   
            valor_res_motor(temp);
             
        }
    }





}


TASK verificarInput(){
  
    TRISCbits.RC0=1;
    TRISAbits.RA4=0;
    TRISB=0;
    TRISD=0;
    
    while (1){        
        //PORTDbits.RD15=0;
        //PORTDbits.RD0=0;
        if (PORTCbits.RC0==0){ 
            
              //create_task(2, 5, PiscaLed1);
              //nojoDelay(100);
            PORTAbits.RA4 = ~LATAbits.LA4;
            asm("nop");
            asm("nop");
            asm("nop");
      
            
       
            botaoAumentar();
              //nojoTaskCreate(2, 1, Distancia);
              
        }
        if (DOWN_TEMP==0){ 
            
              //create_task(2, 5, PiscaLed1);
              //nojoDelay(100);
              //botaoAumentar();
              //nojoTaskCreate(2, 1, Distancia);
        }
        
        
    }
  return NULL;

}


//------------------Display--------------------------
void botaoAumentar(){
         
            if(temperatura_desejada==40);
            else 
            {
                temperatura_desejada++;    
                /*dezena=temperatura_desejada/10;
                unidade=(temperatura_desejada%10); 
                 */
                unidade++;
                if(unidade>=10)
                {
                    unidade=0;
                    dezena++;
                
                }
            }
           
            mostraDisplay(unidade,dezena, '°');
            asm("nop");
            asm("nop");
            asm("nop");

                  
  }

void mostraDisplay(int unidade,int dezena, char identificador){
    PORTD=(dezena<<4)|(unidade); 
    if(identificador=='1') PORTB=0b0000110;
    
    if(identificador=='2') PORTB=0b1011011;
    
    if(identificador=='°') PORTB=0b1100011;
}