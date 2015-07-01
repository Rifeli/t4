/***************************************************************************
*  $MCI Módulo de implementação: Módulo Pilha
*
*  Arquivo gerado:              PILHA.H
*  Letras identificadoras:      PIL
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Projeto: INF 1628 T2 Jogo Paciência Spider
*
*  Gestor:  Flavio Bevilacqua
*
*  Autores: GM - Gabriel Medeiros
*           HR - Henrique Rito
*           VS - Victor Sabino

*  $HA Histórico de evolução:
*     Versão   Autor    Data      Observações
*       1.00   HR  30/04/2015 Início do desenvolvimento
*       2.00   GM  01/05/2015 Arrumacao das funcoes
*		3.00   Vic  04/05/2015 Ajeitar Comentários
*
*		Interface da implementação de pilha de cartas
*
***************************************************************************/

#ifndef PILHA_H
#define PILHA_H
#include "LISTA.H"
#include "CARTA.H"

typedef enum {

         PILHA_CondRetOK = 0 ,
               /* Executou correto */
        PILHA_CondRetFaltouMemoria = 1 ,
               /* Faltou memória ao alocar dados */
        PILHA_CondRetPilhaInexistente = 2 ,
        	 /* Não Existe Pilha */
	    PILHA_CondRetTopoInexistente = 3 ,

		PILHA_CondRetErroEstrutura = 4 ,

   } PILHA_tpCondRet ;

typedef struct PILHA_tgPilha * PILHA_tppPilha;

typedef enum { 

	PILHA_DeturpaCabeca ,
	PILHA_DeturpaTipoCabeca ,
	PILHA_DeturpaEspacoCabeca ,
	PILHA_DeturpaQuantidade ,
	PILHA_DeturpaEspacoTopo ,
	PILHA_DeturpaLixoTopo ,
	PILHA_DeturpaLixoCelulaInterna ,
	PILHA_DeturpaTipoTopo ,
	PILHA_DeturpaEspacoCelularInterna ,

} PILHA_tpModosDeturpacao;

void PILHA_Deturpa(PILHA_tppPilha * pPilha, PILHA_tpModosDeturpacao ModoDeturpar);

/***********************************************************************
*
*  $FC Função: PILHA Cria Pilha
*
*  $FV Valor retornado
*     PILHA_CondRetFaltouMemoria caso não consiga fazer a alocação dinâmica de memória
*	  PILHA_CondRetOk
*		$ED Descrição do tipo
*		CRIA PILHA
***********************************************************************/

PILHA_tpCondRet PILHA_CriarPilha(PILHA_tppPilha * pp);
/***********************************************************************
*
*  $FC Função: PILHA Push Pilha
*
*  $FV Valor retornado
*	  PILHA_CondRetNaoExiste Caso a SEQ nao exista
*	  PILHA_CondRetOk
*		$ED Descrição do tipo
*		bota um elemento no topo da pilha
***********************************************************************/

PILHA_tpCondRet PILHA_Push (PILHA_tppPilha p, CRT_tppCarta carta);

/***********************************************************************
*
*  $FC Função: PILHA Pop Pilha
*
*  $FV Valor retornado
*	  PILHA_CondRetNaoExiste Caso a SEQ nao exista
*	  PILHA_CondRetOk
*		$ED Descrição do tipo
*		tira um elemento do topo da pilha
***********************************************************************/

PILHA_tpCondRet PILHA_Pop (PILHA_tppPilha p, CRT_tppCarta * carta);

/***********************************************************************
*
*  $FC Função: PILHA Print Topo
*
*  $FV Valor retornado
*	  PILHA_CondRetNaoExiste Caso a SEQ nao exista
*	  PILHA_CondRetOk
*		$ED Descrição do tipo
*		Imprime o topo da pilha
***********************************************************************/

PILHA_tpCondRet PILHA_insereMonte(PILHA_tppPilha pPilhaFonte, PILHA_tppPilha * pPilhaDestino, int quantidade);

/***********************************************************************
*
*  $FC Função: PILHA Insere Monte
*
*  $FV Valor retornado
*	  PILHA_CondRetNaoExiste Caso a SEQ nao exista
*	  PILHA_CondRetOk
*		$ED Descrição do tipo
*		Move cartas de uma pilha para a outra
***********************************************************************/

PILHA_tpCondRet PILHA_PrintTopo(PILHA_tppPilha p);

PILHA_tpCondRet PILHA_Quantidade(PILHA_tppPilha p, int * quantidade);

PILHA_tpCondRet PILHA_Decrementa(PILHA_tppPilha p);
PILHA_tpCondRet PILHA_Incrementa(PILHA_tppPilha p);

#endif 