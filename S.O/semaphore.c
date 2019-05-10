#include "semaphore.h"
#include "kernel.h"

void sem_create(sem_t *handler, u_int initial_value){
    handler->sem_value = initial_value;
    queue_create(&handler->sem_queue);
}

void sem_wait(sem_t *handler){
    DISABLE_GLOBAL_INTERRUPTS();
    
    if(--handler->sem_value < 0){
        // Bloqueia o Processo
        queue_insert(&handler->sem_queue, F_APTOS.task_running);
        F_APTOS.FILA_APTOS[F_APTOS.task_running].task_STATE = WAITING;
        nojoDispatcher(WAITING);
        // Salva o contexto
       // SAVE_CONTEXT();
    }
    
    
    
    ENABLE_GLOBAL_INTERRUPTS();
}

void sem_post(sem_t *handler){
    DISABLE_GLOBAL_INTERRUPTS();
    u_int id_to_unblock;
   
    if(++handler->sem_value <= 0) {
        id_to_unblock=queue_remove(&handler->sem_queue);
        F_APTOS.FILA_APTOS[id_to_unblock].task_STATE = READY;
    }
    
    ENABLE_GLOBAL_INTERRUPTS();
}
