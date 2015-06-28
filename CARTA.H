/***************************************************************************
*  $MCI MÃ³dulo de implementaÃ§Ã£o: MÃ³dulo Carta
*
*  Arquivo gerado:              CARTA.H
*  Letras identificadoras:      CAR
*
*  Nome da base de software:    ArcabouÃ§o para a automaÃ§Ã£o de testes de programas redigidos em C
*  Projeto: INF 1628 T2 Jogo PaciÃªncia Spider
*
*  Gestor:  Flavio Bevilacqua
*
*  Autores: GM - Gabriel Medeiros
*           HR - Henrique Rito
*           VS - Victor Sabino

*  $HA HistÃ³rico de evoluÃ§Ã£o:
*     VersÃ£o   Autor    Data      ObservaÃ§Ãµes
*       1.00   HR  30/04/2015 InÃ­cio do desenvolvimento
*       2.00   GM  01/05/2015 Arrumacao das funcoes
*		3.00   GM  05/05/2015 Ajeitar ComentÃ¡rios
*
*		Interface da implementaÃ§Ã£o das cartas
*
***************************************************************************/


#ifndef CARTA_H
#define CARTA_H

typedef enum {
	CRT_CondRetOk = 0 ,
	     /* Executou correto */
 	CRT_CondRetFaltouMemoria = 1 ,
           /* Faltou memÃ³ria ao alocar dados */
	CRT_CondRetValorIndevido = 2 ,
               /* Naipe ou Valor indevido */
	CRT_CondRetCartaInexistente = 3 
                 /* NÃ£o Existe Carta */
	} CRT_tpCondRet ; 

typedef struct CRT_tgCarta * CRT_tppCarta;

/***********************************************************************
*
*  $FC FunÃ§Ã£o: CRT Cria Carta
*
*  $FV Valor retornado
*     CRT_CondRetFaltouMemoria caso nÃ£o consiga fazer a alocaÃ§Ã£o dinÃ¢mica de memÃ³ria
*     CRT_CondRetValorIndevido caso seja inserido naipe acima de 4 ou abaixo de 1 e valor abaixo de 1 ou acima de 13.
*	  CRT_CondRetOk
*		$ED DescriÃ§Ã£o do tipo
*		Cria carta com o valor e o naipe passados pelo parÃ¢metro
***********************************************************************/

CRT_tpCondRet CRT_CriaCarta(CRT_tppCarta * crt, int Num_Carta, int Naipe);

/***********************************************************************
*
*  $FC FunÃ§Ã£o: CRT Deleta Carta
*
*  $FV Valor retornado
*     CRT_CondRetFaltouMemoria caso nÃ£o consiga fazer a alocaÃ§Ã£o dinÃ¢mica de memÃ³ria
*	  CRT_CondRetCartaInexistente caso seja chamada antes de se criar uma carta.
*	  CRT_CondRetOk
*		$ED DescriÃ§Ã£o do tipo
*		DELETA CARTA
***********************************************************************/

CRT_tpCondRet CRT_DeletaCarta(CRT_tppCarta crt);

/***********************************************************************
*
*  $FC FunÃ§Ã£o: CRT Print Carta
*
*  $FV Valor retornado
*     CRT_CondRetFaltouMemoria caso nÃ£o consiga fazer a alocaÃ§Ã£o dinÃ¢mica de memÃ³ria
*	  CRT_CondRetCartaInexistente caso seja chamada antes de se criar uma carta.
*	  CRT_CondRetOk
*		$ED DescriÃ§Ã£o do tipo
*		Imprime o valor da carta passada por parÃ¢metro
***********************************************************************/

CRT_tpCondRet CRT_PrintCarta(CRT_tppCarta crt);

/***********************************************************************
*
*  $FC FunÃ§Ã£o: CRT ObtÃ©m Carta
*
*  $FV Valor retornado
*     CRT_CondRetFaltouMemoria caso nÃ£o consiga fazer a alocaÃ§Ã£o dinÃ¢mica de memÃ³ria
*	  CRT_CondRetCartaInexistente caso seja chamada antes de se criar uma carta.
*	  CRT_CondRetOk
*		$ED DescriÃ§Ã£o do tipo
*		Manda o valor da carta para duas variÃ¡veis
***********************************************************************/

CRT_tpCondRet CRT_ObtemCarta(CRT_tppCarta crt, int *  Num_Carta, int * Naipe);
/***********************************************************************
*
*  $FC FunÃ§Ã£o: CRT Vira Carta
*
*  $FV Valor retornado
*     CRT_CondRetFaltouMemoria caso nÃ£o consiga fazer a alocaÃ§Ã£o dinÃ¢mica de memÃ³ria
*	  CRT_CondRetCartaInexistente caso seja chamada antes de se criar uma carta.
*	  CRT_CondRetOk
*		$ED DescriÃ§Ã£o do tipo
*		Multiplica o valor e o naipe por -1, efetivamente indicando que uma carta com valor "negativo" estÃ¡ virada.
***********************************************************************/

CRT_tpCondRet CRT_ViraCarta(CRT_tppCarta crt);



#endif