#include "jogo.h"

/* _____________________________ MAIN ____________________________________ */
int main(void)
{
    // Gerar numeros aleatorios
    srand(time(NULL));
    // Habilita o clock do tiva para 80 MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    // Habilita os portais
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    habilita_display_nokia();
    habilita_portas_matriz_botoes();

    // _________  Setando variaveis globais _________
    //         Menu de jogo
    estado_de_escolha  = 1;      // Arte que esta na tela
    estado_de_nivel = 0;
    // 1 jogar - 2 nivel - 3 - criador

    //        Setagem boneco
    boneco.p_tela = 1;
    boneco.y = 25;
    boneco.x = 61;
    boneco.xo = 61;
    boneco.peso_de_x = 7;

    //        Setagem Alvo
    alvo.p_tela = 1;
    alvo.y = 35;
    alvo.x = 2;
    alvo.xo = 3;
    alvo.peso_de_x = 14;

    //        Controle do jogo
    pontuacao = 0;
    nivel = 1; // por padrao, vem em modo facil
    tempo = 0;
    qnt_tiro = 20; // Numero de tiros para facil

    // Introdução ao jogo
    introducao();

    // Mostrar o bitmap ja no menu
    Nokia5110_DrawFullImage(menu_selec_jogar_Bitmap);
    while (1){
      while(  menu_iniciar() ){
          SysCtlDelay( tempin_ajustavel );
      }

      Nokia5110_Clear();
      if ( nivel == 2)
          qnt_tiro -= 3;
      else if ( nivel == 3)
          qnt_tiro -= 5;
      SysCtlDelay( tempin_ajustavel * 3 );
      SysTickEnable ();
      SysTickIntEnable();
      SysTickPeriodSet (222000 / nivel);

      while( jogar() ){
          SysCtlDelay( tempin_ajustavel );
      }
    }
}
/* _______________________________________________________________________ */
