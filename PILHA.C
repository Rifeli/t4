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
*		3.00   Vic  04/05/2015 Ajeitar ComentÃ¡rios
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

#ifdef _DEBUG
	PILHA_tppPilha pCabeca;
	int idTipo;
	int tamValor;
#endif
} PILHA_tpPilha;

#ifdef _DEBUG

static char EspacoLixo[ 256 ] =
	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" ;
/* Espaço de dados lixo usado ao testar */

#endif

/********************************************************************************
* PILHA_Deturpa
* Deturpacao da pilha de acordo com o modulo de deturpacao recebido
*********************************************************************************/

void PILHA_Deturpa(PILHA_tppPilha pPilha, PILHA_tpModosDeturpacao ModoDeturpar){
	int i;

	PILHA_tppPilha pPilhaAux = NULL;
	CRT_tppCarta pCarta = NULL;

	CRT_CriaCarta(&pCarta, 15, 15);
	PILHA_CriarPilha(&pPilhaAux);

	if(PILHA_DeturpaCabeca){
		pPilha->topo = NULL;
	}
	else if(PILHA_DeturpaTipoCabeca){
		CED_DefinirTipoEspaco( pPilha , CED_ID_TIPO_ILEGAL ) ;
	}
	else if(PILHA_DeturpaEspacoCabeca){
		memcpy( (( char * )( pPilha )) - 10 , "????" , 4 ) ;
	}
	else if(PILHA_DeturpaQuantidade){
		pPilha->quantidade = INT_MAX;
	}
	else if(PILHA_DeturpaEspacoTopo){
		if(PILHA_Pop(pPilha, &pCarta) == PILHA_CondRetOK){
			memcpy( (( char * )( pCarta )) - 10 , "????" , 4 ) ;
			PILHA_Push(pPilha, pCarta);
		}
	}
	else if(PILHA_DeturpaLixoTopo){
		if(PILHA_Pop(pPilha, &pCarta) == PILHA_CondRetOK){
			pCarta = ( CRT_tppCarta )( EspacoLixo ) ;
			PILHA_Push(pPilha, pCarta);
		}
	}
	else if(PILHA_DeturpaLixoCelulaInterna){
		for(i = 0; i < pPilha->quantidade/2; i++){
			PILHA_Pop(pPilha, &pCarta);
			if(i == ((pPilha->quantidade/2) - 1)){
				pCarta = ( CRT_tppCarta )( EspacoLixo ) ;
			}
			PILHA_Push(pPilhaAux, pCarta);
		}
		for(; i > 0; i--){
			PILHA_Pop(pPilhaAux, &pCarta);
			PILHA_Push(pPilha, pCarta);
		}
	}
	else if(PILHA_DeturpaTipoTopo){
		if(PILHA_Pop(pPilha, &pCarta) == PILHA_CondRetOK){
			CED_DefinirTipoEspaco( pPilha , CED_ID_TIPO_ILEGAL );
			PILHA_Push(pPilha, pCarta);
		}

	}
	else if(PILHA_DeturpaEspacoCelularInterna){
		for(i = 0; i < pPilha->quantidade/2; i++){
			PILHA_Pop(pPilha, &pCarta);
			if(i == ((pPilha->quantidade/2) - 1)){
				memcpy( (( char * )( pCarta )) - 10 , "????" , 4 ) ;
			}
			PILHA_Push(pPilhaAux, pCarta);
		}
		for(; i > 0; i--){
			PILHA_Pop(pPilhaAux, &pCarta);
			PILHA_Push(pPilha, pCarta);
		}
	}
}

PILHA_tpCondRet PILHA_VerificaCabeca( PILHA_tppPilha pPilha ){
	if(pPilha == NULL){
		TST_NotificarFalha( "Tentou verificar cabeça inexistente." ) ;
		return PILHA_CondRetErroEstrutura;
	}

	if ( TST_CompararInt( PILHA_TipoEspacoTopo ,
		CED_ObterTipoEspaco( ( void * )pPilha ) ,
		"Tipo do espaço de dados não é cabeca de pilha." ) != TST_CondRetOK ){
			return PILHA_CondRetErroEstrutura;
	}

	if (!CED_VerificarEspaco(( void * )pPilha, NULL)){
		TST_NotificarFalha( "Tentou verificar cabeça inexistente." ) ;
		return PILHA_CondRetErroEstrutura;
	}

	return PILHA_CondRetOK;
}

PILHA_tpCondRet PILHA_VerificaTopo( PILHA_tppPilha pPilha ){
	CRT_tppCarta pCarta = NULL;
	CRT_CriaCarta(&pCarta, 15, 15);

	PILHA_Pop(pPilha, &pCarta);

	if(pCarta == NULL){
		TST_NotificarFalha( "Tentou verificar topo inexistente." ) ;
		return PILHA_CondRetErroEstrutura;
	}

	PILHA_Push(pPilha, pCarta);
	PILHA_Pop(pPilha, &pCarta);

	if ( TST_CompararInt( PILHA_TipoEspacoTopo ,
		CED_ObterTipoEspaco( ( void * )pCarta ) ,
		"Tipo do espaço de dados não é topo de pilha." ) != TST_CondRetOK ){
			return PILHA_CondRetErroEstrutura;
	}

	PILHA_Push(pPilha, pCarta);
	PILHA_Pop(pPilha, &pCarta);

	if (!CED_VerificarEspaco(( void * )pCarta, NULL)){
		TST_NotificarFalha( "Tentou verificar topo inexistente." ) ;
		return PILHA_CondRetErroEstrutura;
	}

	return PILHA_CondRetOK;
}

PILHA_tpCondRet PILHA_VerificaCelulaInterna( PILHA_tppPilha pPilha ){
	if(pPilha == NULL){
		TST_NotificarFalha( "Tentou verificar cabeça inexistente." ) ;
		return PILHA_CondRetErroEstrutura;
	}

	return PILHA_CondRetOK;
}

PILHA_tpCondRet PILHA_VerificarPilha( PILHA_tppPilha pPiLha ){
	PILHA_tppPilha pPilha = NULL;

	if(PILHA_VerificaTopo(pPilha) == PILHA_CondRetErroEstrutura){
		return PILHA_CondRetErroEstrutura;
	}
	if(PILHA_VerificaCabeca(pPilha) == PILHA_CondRetErroEstrutura){
		return PILHA_CondRetErroEstrutura;
	}

	return PILHA_VerificaCelulaInterna(pPilha);
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
#else
	p = NULL ;   
#endif

	p->topo = LIS_CriarLista(NULL);
	p->ExcluirValor = NULL;
	p->quantidade = 0;
	*pp = p;

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
	if (!p) 
		return PILHA_CondRetPilhaInexistente;

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

	if (p == NULL)
		return PILHA_CondRetPilhaInexistente;

	if (p->topo == NULL)
		return PILHA_CondRetPilhaInexistente;

	//LIS_AvancarElementoCorrente(p->topo);
	crt_aux = (CRT_tppCarta)LIS_ObterValor(p->topo);
	CRT_ObtemCarta(crt_aux, &crt[0], &crt[1]);

	condRet = LIS_ExcluirElemento(p->topo);
	if (condRet == 1){
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


