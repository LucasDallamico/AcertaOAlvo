#ifndef JOGO_H
#define JOGO_H

/* _______________________________________________________________________ */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/debug.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/uart.h"
#include "driverlib/systick.h"
#include "utils/uartstdio.h"
#include "driverlib/timer.h"

#include "utils/ustdlib.h"
#include "driverlib/hibernate.h"

#include "artes_de_jogo.h"
#include "Nokia5110.h"

#define GPIO_O_LOCK                 0x520
#define GPIO_O_CR                   0x524
#define GPIO_LOCK_KEY               0x4C4F434B
#define GPIO_O_PUR                  0x510
#define ESC_REG(x)                  (*((volatile uint32_t *)(x)))

#define tempin_ajustavel 1700000

/* _______________________________________________________________________ */
//                        Variaveis globais

int estado_de_escolha;      // Arte que esta na tela
bool estado_de_nivel;       // 1 jogar - 2 nivel - 3 - criador
int pontuacao;
int nivel;
int tempo;
int qnt_tiro;

typedef struct posicao_moveis{
    int p_tela;
    int x;
    int peso_de_x;
    int xo;
    int y; // Não altera
};

struct posicao_moveis boneco;
struct posicao_moveis alvo;

int c;

/* _______________________________________________________________________ */
//                       COORDENADAS DO DISPLAY
/*  ALVO  1-> 3X36 : 13X45
          2-> 17X36: 27X45
          3-> 32X36: 42X45

   Boneco 1-> 61x25: 69x38
          2-> 68x25: 77x38
          3-> 74x75: 82x38
*/

/* _______________________________________________________________________ */
/*                          BOTOES USADOS
p/ esquerda  [0] | p/ direita  [1] | Tiro linear  [2] | Tiro parabolico [3]
*/

/* _______________________________________________________________________ */
//                         FUNCOES DE JOGO
void introducao(void);
void iniciar(void);
bool menu_iniciar(void);
bool jogar(void);
int tiro_linhear(int boneco, int alvo);
void exibe_objetos_de_jogar_nokia(void);

/* _______________________________________________________________________ */
//                 FUNCOES INICIAIS DE CONFIGURACAO DO TIVA
void habilita_todos_os_botoes(void);
void habilita_display_nokia(void);

/* _______________________________________________________________________ */
//                         FUNCOES AUXILIARES
int movimento_de_objeto_3posi(int referencia, int mov);
int gera_posicao(void);
void destrava_pino(uint32_t portal_base);
void bloqueia_GPIO(uint32_t portal);

/* _______________________________________________________________________ */
//                             BOTOES
void habilita_portas_matriz_botoes(void);
int leitura_matriz_botao(void);

/* _______________________________________________________________________ */
//                           INTERRUPCAO
void trataSystick(void);

#endif
