#include "jogo.h"

/* _______________________________________________________________________ */
//                        HISTÓRIA E MANUAL
void introducao(void){
    Nokia5110_OutString("Uma grande  batalha estase          aproximando");
    SysCtlDelay( tempin_ajustavel * 30);
    Nokia5110_Clear();
    Nokia5110_OutString("Seu objetivoAcertar 10  tiros no    alvo");
    SysCtlDelay( tempin_ajustavel * 30);
    Nokia5110_Clear();
    Nokia5110_OutString("Os alvos se mexem       conforme    passa o     tempo");
    SysCtlDelay( tempin_ajustavel * 30);
    Nokia5110_Clear();
    Nokia5110_OutString("Quando maioro nivel,    mais rapido os alvos se mexem");
    SysCtlDelay( tempin_ajustavel * 30);
    Nokia5110_Clear();
    Nokia5110_OutString("e menor a   quantidade  de tiro ...");
    SysCtlDelay( tempin_ajustavel * 30);
    Nokia5110_Clear();
    Nokia5110_OutString("Voce esta   pronto para a batalha?");
    SysCtlDelay( tempin_ajustavel * 30);
    Nokia5110_Clear();
    Nokia5110_DrawFullImage(explica_controle);
    SysCtlDelay( tempin_ajustavel * 35);
    Nokia5110_Clear();
    Nokia5110_DrawFullImage(explica_cenario);
    SysCtlDelay( tempin_ajustavel * 35);
    Nokia5110_Clear();
}

/* _______________________________________________________________________ */
//                        MENU DE SELECECAO
bool menu_iniciar(void)
{
  c = leitura_matriz_botao();
  int aux;

  // Acionamento da seta
  if ( c == 0 || c == 1 ){
    aux = movimento_de_objeto_3posi(estado_de_escolha,c);
    // Blindagem contra usuario
    if (aux != 0 && aux < 6)
      estado_de_escolha = aux;
  }

  if ( estado_de_nivel == 0){
    if (estado_de_escolha == 1)
      Nokia5110_DrawFullImage(menu_selec_jogar_Bitmap);

    if ( estado_de_escolha == 2 )
      Nokia5110_DrawFullImage(menu_selec_nivel_Bitmap);

    if ( estado_de_escolha == 3 )
      Nokia5110_DrawFullImage(menu_selec_criador_Bitmap);

    if ( estado_de_escolha == 5)
      Nokia5110_DrawFullImage(autor);
  }

  if ( estado_de_nivel == 1){
    if ( estado_de_escolha == 1)
      Nokia5110_DrawFullImage(nivel_facil);

    if ( estado_de_escolha == 2)
      Nokia5110_DrawFullImage(nivel_medio);

    if ( estado_de_escolha == 3)
      Nokia5110_DrawFullImage(nivel_dificil);
  }

  if ( estado_de_escolha == 5 && (c == 2 || c == 3))
    estado_de_escolha = 1;

  else if ( ( c == 2 || c == 3 ) && estado_de_nivel == 1){
    estado_de_nivel = 0;
    nivel = estado_de_escolha;
    estado_de_escolha = 1;
  }

  else if ( ( c == 2 || c == 3 ) && estado_de_nivel == 0){
    if (estado_de_escolha == 1) // jogar
      return 0;

    if (estado_de_escolha == 2) // nivel
        estado_de_nivel = 1;

    if ( estado_de_escolha == 3){ // Autor
      estado_de_escolha = 5;
    }
  }
  return 1;
}

/* _______________________________________________________________________ */
//                                    JOGO
bool jogar(void)
{
  int acertou = 0;
  c = leitura_matriz_botao();
  int aux;

  //      MOVIMENTA O BONECO
  if ( c == 0 || c == 1){
      boneco.p_tela = movimento_de_objeto_3posi(boneco.p_tela,c);
      boneco.x = boneco.xo + boneco.peso_de_x*(boneco.p_tela-1);
  }

  if ( c == 2){
      acertou = tiro_linhear(boneco.p_tela,alvo.p_tela);
      if (acertou == 0)
          qnt_tiro--;
  }

  //          MOSTRA DISPLAY
  exibe_objetos_de_jogar_nokia();
  Nokia5110_DisplayBuffer();
  Nokia5110_ClearBuffer();

  if ( acertou == 1){
      qnt_tiro--;
      pontuacao++;
      aux = gera_posicao();
      // Para garantir que o alvo nao gere a mesma posicao de antes
      while (aux == alvo.p_tela){
        aux = gera_posicao();
      }
      alvo.p_tela = aux;
      alvo.x = alvo.xo + alvo.peso_de_x*(alvo.p_tela-1);
  }

  if ( qnt_tiro <= 0){
      SysTickDisable();
      // Mostra para o usuario que ele ganhou
      Nokia5110_DrawFullImage(perdeu_Bitmap);
      pontuacao = 0;
      qnt_tiro = 20;
      SysCtlDelay( tempin_ajustavel * 20);
      return 0;
  }

  if ( pontuacao == 10 ){
      SysTickDisable();
      // Mostra para o usuario que ele ganhou
      Nokia5110_DrawFullImage(ganohu_Bitmap);
      pontuacao = 0;
      qnt_tiro = 20;
      SysCtlDelay( tempin_ajustavel * 20);
      return 0;
  }

  return 1;
}

/* _______________________________________________________________________ */
//                        MOSTRAR NO NOKIA
void exibe_objetos_de_jogar_nokia(void){
    //            CENARIO
    Nokia5110_PrintBMP2(61, 38, base_boneco, 23, 10);
    Nokia5110_PrintBMP2(0, 46, base_alvo, 60, 2);
    Nokia5110_PrintBMP2(4, 3, n_p, 3, 5);
    Nokia5110_PrintBMP2(47, 3, n_t, 3, 5);

    //            PONTUACAO
    if ( pontuacao < 10){
      Nokia5110_PrintBMP2(8, 3, vetor_de_numero[0], 3, 5);
      Nokia5110_PrintBMP2(12, 3, vetor_de_numero[pontuacao], 3, 5);
    }
    else if ( pontuacao < 20){
      Nokia5110_PrintBMP2(8, 3, vetor_de_numero[1], 3, 5);
      Nokia5110_PrintBMP2(12, 3, vetor_de_numero[pontuacao - 10], 3, 5);
    }

    //          QUANTIDADE DE TIRO
    if ( qnt_tiro < 10){
      Nokia5110_PrintBMP2(51, 3, vetor_de_numero[0], 3, 5);
      Nokia5110_PrintBMP2(55, 3, vetor_de_numero[qnt_tiro], 3, 5);
    }
    else if ( qnt_tiro < 20){
      Nokia5110_PrintBMP2(51, 3, vetor_de_numero[1], 3, 5);
      Nokia5110_PrintBMP2(55, 3, vetor_de_numero[qnt_tiro - 10], 3, 5);
    }
    else{
        Nokia5110_PrintBMP2(51, 3, vetor_de_numero[2], 3, 5);
        Nokia5110_PrintBMP2(55, 3, vetor_de_numero[qnt_tiro - 20], 3, 5);
    }

    //                MOVEIS
    Nokia5110_PrintBMP2(alvo.x, alvo.y, alvo_imagem, 11, 11); // ALVO
    Nokia5110_PrintBMP2(boneco.x, boneco.y, boneco_imagem, 9, 13); // BONECO
}
