/***************************************************************************
*  $MCI Módulo de implementação: Módulo Carta
*
*  Arquivo gerado:              CARTA.C
*  Letras identificadoras:      CAR
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
*       1.00   HR  20/05/2015 Desenvolvimento/Término
*		2.00   GM  05/05/2015  Ajeitar Comentários
*
*		Módulo de implementação de cartas
*
***************************************************************************/

#include "CARTA.H"
#include <stdlib.h>
#include <stdio.h>
#ifdef _DEBUG
#include "CESPDIN.H"
#endif

/***********************************************************************
*
*  $TC Tipo de dados: CRT Carta
* $ED Descrição do tipo
*     descreve a estrutura Carta
*
***********************************************************************/


typedef struct CRT_tgCarta {
	int Num_Carta;
	int Naipe;
	/* Valor e naipe da carta em questão */
} CRT_tpCarta;


/***********************************************************************
*
*  $FC Função: CRT Cria Carta
*
*  $FV Valor retornado
*     CRT_CondRetFaltouMemoria caso não consiga fazer a alocação dinâmica de memória
*     CRT_CondRetValorIndevido caso seja inserido naipe acima de 4 ou abaixo de 1 e valor abaixo de 1 ou acima de 13.
*	  CRT_CondRetOk
*		$ED Descrição do tipo
*		Cria carta com o valor e o naipe passados pelo parâmetro
***********************************************************************/

CRT_tpCondRet CRT_CriaCarta(CRT_tppCarta * crt, int Num_Carta, int Naipe){
	CRT_tppCarta crt_aux = NULL;
	crt_aux = (CRT_tppCarta)malloc(sizeof(CRT_tpCarta));

#ifdef _DEBUG
	CED_MarcarEspacoAtivo(crt);
#endif

	if(!crt_aux){
		return CRT_CondRetFaltouMemoria;
	} /* if */

	if(((Num_Carta < -13 || Num_Carta > -1)) && Num_Carta != 15){
		return CRT_CondRetValorIndevido;
	} /* if */

	if((Naipe > 4 || Naipe < 1) && Num_Carta != 15){
		return CRT_CondRetValorIndevido;
	} /* if */

	crt_aux->Num_Carta = Num_Carta;
	crt_aux->Naipe = Naipe;
	*crt = crt_aux;

	return CRT_CondRetOk;
} /* Fim da função: CRT Cria carta */

/***********************************************************************
*
*  $FC Função: CRT Deleta Carta
*
*  $FV Valor retornado
*     CRT_CondRetFaltouMemoria caso não consiga fazer a alocação dinâmica de memória
*	  CRT_CondRetCartaInexistente caso seja chamada antes de se criar uma carta.
*	  CRT_CondRetOk
*		$ED Descrição do tipo
*		DELETA CARTA
***********************************************************************/

CRT_tpCondRet CRT_DeletaCarta(CRT_tppCarta crt){
#ifdef _DEBUG
	CED_MarcarEspacoNaoAtivo(crt);
#endif

	if(crt == NULL){
		return CRT_CondRetCartaInexistente;
	} /* if */

	free(crt);
	crt = NULL;

	return CRT_CondRetOk;
}/* Fim função: CRT Deleta carta */

/***********************************************************************
*
*  $FC Função: CRT Print Carta
*
*  $FV Valor retornado
*     CRT_CondRetFaltouMemoria caso não consiga fazer a alocação dinâmica de memória
*	  CRT_CondRetCartaInexistente caso seja chamada antes de se criar uma carta.
*	  CRT_CondRetOk
*		$ED Descrição do tipo
*		Imprime o valor da carta passada por parâmetro
***********************************************************************/

CRT_tpCondRet CRT_PrintCarta(CRT_tppCarta crt){
	char c = 0, n = 0;
	char x = 'X';

	if(crt == NULL){
		return CRT_CondRetCartaInexistente;
	} /* if */
	if (crt->Num_Carta == 15)
		return CRT_CondRetCartaInexistente;
	if (crt->Num_Carta < 0){
		printf("  %c%c ", x, x);
		return CRT_CondRetOk;
	}
	if(!((crt->Num_Carta <= 13 && crt->Num_Carta >= 1) || (crt->Num_Carta >= -13 && crt->Num_Carta <= -1))){
		return CRT_CondRetCartaInexistente;
	}

	if(crt->Naipe == 1)
		n = 'E';
	else if (crt->Naipe == 2)
		n = 'O';
	else if (crt->Naipe == 3)
		n = 'C';
	else if (crt->Naipe == 4)
		n = 'P';

	if(crt->Num_Carta == 1 || crt->Num_Carta >= 11){
		if(crt->Num_Carta == 1)
			c = 'A';
		else if(crt->Num_Carta == 11)
			c = 'J';
		else if(crt->Num_Carta == 12)
			c = 'Q';
		else if(crt->Num_Carta == 13)
			c = 'K';


		printf("  %c%c ", c, n);
	}
	else if (crt->Num_Carta == 10){
		printf("  %d%c", crt->Num_Carta, n);
	}
	else{
		printf("  %d%c ", crt->Num_Carta, n);
	}

	return CRT_CondRetOk;
}/* Fim função: CRT Print carta */

/***********************************************************************
*
*  $FC Função: CRT Obtém Carta
*
*  $FV Valor retornado
*     CRT_CondRetFaltouMemoria caso não consiga fazer a alocação dinâmica de memória
*	  CRT_CondRetCartaInexistente caso seja chamada antes de se criar uma carta.
*	  CRT_CondRetOk
*		$ED Descrição do tipo
*		Manda o valor da carta para duas variáveis
***********************************************************************/

CRT_tpCondRet CRT_ObtemCarta(CRT_tppCarta crt, int *  Num_Carta, int * Naipe){
	if(!crt){
		return CRT_CondRetCartaInexistente;
	} /* if */

	*Num_Carta = crt->Num_Carta;
	*Naipe = crt->Naipe;

	return CRT_CondRetOk;
}/* Fim função: CRT Obtem carta */

/***********************************************************************
*
*  $FC Função: CRT Vira Carta
*
*  $FV Valor retornado
*     CRT_CondRetFaltouMemoria caso não consiga fazer a alocação dinâmica de memória
*	  CRT_CondRetCartaInexistente caso seja chamada antes de se criar uma carta.
*	  CRT_CondRetOk
*		$ED Descrição do tipo
*		Multiplica o valor e o naipe por -1, efetivamente indicando que uma carta com valor "negativo" está virada.
***********************************************************************/

CRT_tpCondRet CRT_ViraCarta(CRT_tppCarta crt){
	if(crt == NULL)
		return CRT_CondRetCartaInexistente;
	/* if */
	crt->Num_Carta *= -1;


	return CRT_CondRetOk;
}/* Fim função: CRT Vira Carta */