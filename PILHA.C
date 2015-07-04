/***************************************************************************
*  $MCI MÃ³dulo de implementaÃ§Ã£o: MÃ³dulo Pilha
*
*  Arquivo gerado:              PILHA.C
*  Letras identificadoras:      PIL
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
*		3.00   VS  04/05/2015 Ajeitar ComentÃ¡rios
*		4.00   VS  02/07/2015 verificacao e deturpacao
*
*		MÃ³dulo de implementaÃ§Ã£o de pilha de cartas
*
***************************************************************************/
#include "CARTA.H"
#include "LISTA.H"
#include "PILHA.H"
#include <string.h>

#include <stdio.h>
#include <stdlib.h>

#ifdef _DEBUG
#include "IdTiposEspaco.def"
#include "TiposEspacosPilha.def"
#include "CONTA.H"
#include "CESPDIN.H"
#include "GENERICO.H"
#endif



/***********************************************************************
*
*  $TC Tipo de dados: PILHA estrutura de Pilha
*
*
*  $ED DescriÃ§Ã£o do tipo
*     descreve a Pilha de Cartas
*
***********************************************************************/

typedef struct PILHA_tgPilha{
	LIS_tppLista topo;
	int quantidade;
	void(*ExcluirValor) (void * pValor);
} PILHA_tpPilha;


/********************************************************************************
* PILHA_Deturpa
* Deturpacao da pilha de acordo com o modulo de deturpacao recebido
*********************************************************************************/

void PILHA_Deturpa(PILHA_tppPilha pPilha, PILHA_tpModosDeturpacao ModoDeturpar){
   //ação 2: atribui null para o sucesso
   if(ModoDeturpar == null_sucessor)
		int LIS_SucesNULL(ppilha->topo);

   //ação 3: atribui null para o antecessor
   if(ModoDeturpar == null_predecessor)
		int LIS_PreNULL(ppilha->topo);

	//ação 4: atribui lixo para o sucesso
	if(ModoDeturpar == lixo_sucessor)
		int LIS_LixoSucessor(ppilha->topo);

	//ação 5: atribui lixo para o precessor
	if(ModoDeturpar == lixo_predecessor)
		int LIS_LixoPre(ppilha->topo);

	//ação 6: atribui NULL para o conteudo do nó
	if(ModoDeturpar == lixo_ponteiro)
		int LIS_NULLConteudo(ppilha->topo);

	//ação 7: altera o tipo do nó
	if(ModoDeturpar == null_conteudo)
		int LIS_AlteraTipoDoConteudo(ppilha->topo);

	//ação 8: destaca o conteudo
	if(ModoDeturpar == destaca_elemento)
		int LIS_DestacaConteudo(ppilha->topo);

	//ação 9: corrente nulo
	if(ModoDeturpar == null_corrente)
  		int LIS_NULLCorrente(ppilha->topo);

   //ação 1: libera elemento corrente da estrutura escolhida
   if(ModoDeturpar = elimina_corrente)
		int LIS_LiberaElemCorrente(ppilha->topo);
	
	//ação 10: origim nulo
	if(ModoDeturpar == null_origem)
		int LIS_NULLOrigem(ppilha->topo);

}

PILHA_tpCondRet PILHA_VerificarPilha( PILHA_tppPilha pPiLha, int * quantidadeErros){
	*quantidadeErros = 0;
	
	if(LIS_VerificaLiberaElemCorrente != LIS_CondRetOK)
		*quantidadeErros += 1;
	if(LIS_VerificaSucessorNULL != LIS_CondRetOK)
		*quantidadeErros += 1;
	if(LIS_VerificaPredecessorNULL != LIS_CondRetOK)
		*quantidadeErros += 1;
	if(LIS_VerificaLixoSucessor != LIS_CondRetOK)
		*quantidadeErros += 1;
	if(LIS_VerificaLixoPredecessor != LIS_CondRetOK)
		*quantidadeErros += 1;
	if(LIS_VerificaConteudoNulo != LIS_CondRetOK)
		*quantidadeErros += 1;
	if(LIS_VerificaTipoConteudo != LIS_CondRetOK)
		*quantidadeErros += 1;
	if(LIS_VerificaCorrenteNulo != LIS_CondRetOK)
		*quantidadeErros += 1;
	if(LIS_NumeroDeElementos != LIS_CondRetOK)
		*quantidadeErros += 1;
	if(LIS_confereNumero != LIS_CondRetOK)
		*quantidadeErros += 1;

	return PILHA_CondRetOk;
}


/***********************************************************************
*
*  $FC FunÃ§Ã£o: PILHA Cria Pilha
*
*  $FV Valor retornado
*     PILHA_CondRetFaltouMemoria caso nÃ£o consiga fazer a alocaÃ§Ã£o dinÃ¢mica de memÃ³ria
*	  PILHA_CondRetOk
*		$ED DescriÃ§Ã£o do tipo
*		CRIA PILHA
***********************************************************************/

PILHA_tpCondRet PILHA_CriarPilha(PILHA_tppPilha * pp)
{
	PILHA_tppPilha p = NULL;
	p = (PILHA_tppPilha)malloc(sizeof(PILHA_tpPilha));
	if (!p)
		return PILHA_CondRetFaltouMemoria;

#ifdef _DEBUG
	CNT_CONTAR("PILHA_CriarPilha");

	CED_DefinirTipoEspaco( p , PILHA_TipoEspacoNo ) ;  
#endif

	p->topo = LIS_CriarLista(NULL);
	p->ExcluirValor = NULL;
	p->quantidade = 0;
	*pp = p;
	#ifdef _DEBUG
		CED_MarcarEspacoAtivo(pp);
	#endif
	return PILHA_CondRetOK;
} /* Fim funÃ§Ã£o: PILHA Cria Pilha */

/***********************************************************************
*
*  $FC FunÃ§Ã£o: PILHA Push Pilha
*
*  $FV Valor retornado
*	  PILHA_CondRetNaoExiste Caso a PILHA nao exista
*	  PILHA_CondRetOk
*		$ED DescriÃ§Ã£o do tipo
*		bota um elemento no topo da pilha
***********************************************************************/
PILHA_tpCondRet PILHA_Push(PILHA_tppPilha p, CRT_tppCarta carta){
	if (!p){
		#ifdef _DEBUG
		CNT_CONTAR("PILHA_Push-pilhaInexistente");
		CED_MarcarEspacoAtivo(carta);
		#endif
		return PILHA_CondRetPilhaInexistente;
	}

	IrInicioLista(p->topo);

	LIS_InserirElementoAntes(p->topo, carta);
	p->quantidade += 1;
	return PILHA_CondRetOK;
} /* Fim funÃ§Ã£o: PILHA Push Pilha */

/***********************************************************************
*
*  $FC FunÃ§Ã£o: PILHA Pop Pilha
*
*  $FV Valor retornado
*	  PILHA_CondRetNaoExiste Caso a PILHA nao exista
*	  PILHA_CondRetOk
*		$ED DescriÃ§Ã£o do tipo
*		tira um elemento do topo da pilha
***********************************************************************/
PILHA_tpCondRet PILHA_Pop(PILHA_tppPilha p, CRT_tppCarta * carta){
	int crt[2];
	int condRet = 0;
	CRT_tppCarta crt_aux = NULL;

	if (p == NULL){
		#ifdef _DEBUG
		CNT_CONTAR("PILHA_Pop-PilhaInexistente");
		#endif
		return PILHA_CondRetPilhaInexistente;
	}
	if (p->topo == NULL){
		#ifdef _DEBUG
		CNT_CONTAR("PILHA_Pop-PilhaTopoInexistente");
		#endif
		return PILHA_CondRetPilhaInexistente;
	}
	//LIS_AvancarElementoCorrente(p->topo);
	crt_aux = (CRT_tppCarta)LIS_ObterValor(p->topo);
	CRT_ObtemCarta(crt_aux, &crt[0], &crt[1]);

	condRet = LIS_ExcluirElemento(p->topo);
	
	if (condRet == 1){
		#ifdef _DEBUG
		CNT_CONTAR("PILHA_Pop-PilhaTopoInexistente-2");
		#endif
		p = NULL;
		return PILHA_CondRetPilhaInexistente;
	}

	CRT_CriaCarta(&crt_aux, crt[0], crt[1]);
	*carta = crt_aux;
	p->quantidade -= 1;

	return PILHA_CondRetOK;

} /* Fim funÃ§Ã£o: PILHA POP Pilha */

/***********************************************************************
*
*  $FC FunÃ§Ã£o: PILHA Print Topo
*
*  $FV Valor retornado
*	  PILHA_CondRetNaoExiste Caso a PILHA nao exista
*	  PILHA_CondRetOk
*		$ED DescriÃ§Ã£o do tipo
*		Imprime o topo da pilha
***********************************************************************/


/***********************************************************************
*
*  $FC FunÃ§Ã£o: PILHA Print Pilha Completa
*
*  $FV Valor retornado
*	  PILHA_CondRetNaoExiste Caso a PILHA nao exista
*	  PILHA_CondRetOk
*		$ED DescriÃ§Ã£o do tipo
*		Imprime o topo da pilha
***********************************************************************/

PILHA_tpCondRet PILHA_Quantidade(PILHA_tppPilha p, int * quantidade){
	*quantidade = p->quantidade;
	return PILHA_CondRetOK;
}

PILHA_tpCondRet PILHA_Decrementa(PILHA_tppPilha p){
	p->quantidade--;
	return PILHA_CondRetOK;
}

PILHA_tpCondRet PILHA_Incrementa(PILHA_tppPilha p){
	p->quantidade++;
	return PILHA_CondRetOK;
}

/***********************************************************************
*  $FC FunÃ§Ã£o: PILHA Insere Monte
*
*  $FV Valor retornado
*	  PILHA_CondRetNaoExiste Caso a PILHA nao exista
*	  PILHA_CondRetOk
*		$ED DescriÃ§Ã£o do tipo
*		Move cartas de uma pilha para a outra
***********************************************************************/


