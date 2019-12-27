#include "jogo.h"

/* __________________________ INTERRUPCOES _______________________________ */
void trataSystick(void){
    int aux;
    //            TRATA TEMPO
    // Quando atingir o tempo, troca a posicao do alvo
    if (tempo == 1000){
        aux = gera_posicao();
        // Para garantir que o alvo nao gere a mesma posicao de antes
        while (aux == alvo.p_tela){
          aux = gera_posicao();
        }
        alvo.p_tela = aux;
        alvo.x = alvo.xo + alvo.peso_de_x*(alvo.p_tela-1);
        tempo = 0;
    } else
        tempo++;
}

/* ---------------------------------------------------------------------- */
int tiro_linhear(int boneco, int alvo)
{
  int x,y;
  if ( boneco == 1){
    for ( x = 60; x > 8; x--){
        y = (-0.192)*x + 41.5384;
        Nokia5110_SetPxl(y,x);
    }
    Nokia5110_DisplayBuffer();
    if (alvo == 1)
      return 1;
    else
      return 0;
  }

  else if ( boneco == 2){
    for ( x = 68; x > 23; x--){
        y = (-0.223)*x + 45.111;
        Nokia5110_SetPxl(y,x);
    }
    Nokia5110_DisplayBuffer();
    if (alvo == 2)
      return 1;
    else
      return 0;
  }

  else if ( boneco == 3){
    for ( x = 74; x > 38; x--){
        y = (-0.28)*x + 50.5;
        Nokia5110_SetPxl(y,x);
    }
    Nokia5110_DisplayBuffer();
    if (alvo == 3)
      return 1;
    else
      return 0;
  }
  return 0;
}

/* ---------------------------------------------------------------------- */
void destrava_pino(uint32_t portal_base){
    ESC_REG(portal_base + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    ESC_REG(portal_base + GPIO_O_CR) = 0x01;
}

void bloqueia_GPIO(uint32_t portal){
    ESC_REG(portal + GPIO_O_CR) = 0;
}

/* ---------------------------------------------------------------------- */
void habilita_display_nokia(void){
  Nokia5110_Init();
  Nokia5110_Clear();
  Nokia5110_SetCursor(0,0);
}

/* ------------------------------------------------------ */
int gera_posicao(void){
	//srand(time(NULL)); -> Colocar na main
	int num = rand () % 3;
	num++;
	return num;
}

/* ------------------------------------------------------ */
int movimento_de_objeto_3posi(int referencia, int mov){
  if (referencia == 1 && mov == 0)
    return 3;
  else if ( referencia == 1 && mov == 1)
    return 2;

  else if (referencia == 2 && mov == 0)
    return 1;

  else if ( referencia == 2 && mov == 1)
    return 3;

  else if ( referencia == 3 && mov == 0)
    return 2;
  else if ( referencia == 3 && mov == 1)
    return 1;
  else
    return 0;
}
