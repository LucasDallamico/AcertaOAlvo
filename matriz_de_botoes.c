#include "jogo.h"
/*
0 1 2 3
4 5 6 7
8 9 A B
C D E F

BOTOES: F0  F1  F2  F3 ( COLUNAS)
        F4  B0  B1  B5 ( LINHAS )
*/
/* ======================================================================== */
void habilita_portas_matriz_botoes(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    destrava_pino(GPIO_PORTF_BASE);
    // Envio de informações ( COLUNAS )
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    // Recebe informações ( LINHAS )
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_5);
    // Configurando as portas como pulldown
    ESC_REG(GPIO_PORTF_BASE + GPIO_O_PUR)|= GPIO_PIN_4 ;
    ESC_REG(GPIO_PORTB_BASE + GPIO_O_PUR)|= GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_5 ;
    bloqueia_GPIO(GPIO_PORTF_BASE);
}

/* ======================================================================== */
int leitura_matriz_botao(void){
  uint32_t portal_linhas[4] = {GPIO_PORTF_BASE, GPIO_PORTB_BASE, GPIO_PORTB_BASE, GPIO_PORTB_BASE};
  uint32_t portal_colunas[4] = {GPIO_PORTF_BASE, GPIO_PORTF_BASE, GPIO_PORTF_BASE, GPIO_PORTF_BASE};
  uint32_t pinos_linhas[4] = {GPIO_PIN_4, GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_5};
  uint32_t pinos_colunas[4] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3};

  int i,j;
  int retorno = - 1;

  for ( i = 0; i < 4; i++){
    GPIOPinWrite(portal_colunas[i], pinos_colunas[0]|pinos_colunas[1]|pinos_colunas[2]|pinos_colunas[3], ~(pinos_colunas[i]));
    for ( j = 0; j < 4; j++){
       if(GPIOPinRead(portal_linhas[j], pinos_linhas[j]) == 0x00 ){
           retorno = j*4 + i;
           return retorno;
       }

    }
  }
  return retorno;
}
/* ======================================================================== */
