 /***************************************************************************
 *
 *  $MCD Módulo de definição: SEQFIM Sequencia Final
 *
 *  Arquivo gerado:              TESTPIL.C
 *  Letras identificadoras:      PILHA
 *
 *  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
 *
 *  Projeto: Jogo Spider / Progamação Modular
 *  Autores: GM - Gabriel Medeiros
 *           HR - Henrique Rito
 *           VS - Victor Sabino
 *
 *  $HA Histórico de evolução:
 *     Versão      Autor            Data                Observações
 *     1.0       GM,HR,VS        17/04/2015       Início do desenvolvimento
 *     2.0       GM,HR,VS        03/04/2015              Correções 
 *     3.0        HR,VS          02/28/2015       Adicionar chamadas de script pra deturpacao e verificacao 
 *
 *  $ED Descrição do módulo
 *     Teste de Pilha
 *
 *   Comandos
 *   =criar 0
 *   =destruir 0
 *   =push 0 valor naipe
 *   =print 0
 *   =inserir 0 quantidade
 *
 ***************************************************************************/


#include    <string.h>
#include    <stdio.h>

#include    "CARTA.H"
#include    "pilha.h"
#include    "generico.h"
#include    "lerparm.h"

#include "TST_ESPC.H"
/* Tabela dos nomes dos comandos de teste específicos */

#define     CRIA_PILHA         "=criar"
#define     PUSH_PILHA         "=push"
#define     POP_PILHA          "=pop"
#define     QUANTIDADE         "=quantidade"
#define     DECREMENTA_PILHA   "=decrementa"
#define     INCREMENTA_PILHA   "=incrementa"
#define     DETURPA            "=deturpa"
#define     VERIFICA           "=verifica"

/*****  Código das funções exportadas pelo módulo  *****/


   PILHA_tppPilha pPilha = NULL;
   

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      PILHA_tpCondRet CondRetObtido   = PILHA_CondRetOK ;
      PILHA_tpCondRet CondRetEsperada = PILHA_CondRetOK ;
      PILHA_tpCondRet CondRetDada = PILHA_CondRetOK ;
                                      /* inicializa para qualquer coisa */
	  
      char ValorEsperado = '?'  ;
      char ValorObtido   = '!'  ;
      int  NumLidos = -1 ;
      int acao = 0;
      int nErros = 0;
	  int  quantidade;
	  CRT_tppCarta carta = NULL;

      TST_tpCondRet Ret ;
	  
      /* Testar PILHA Criar Pilha*/

         if ( strcmp( ComandoTeste , CRIA_PILHA ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = PILHA_CriarPilha(&pPilha) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar Pilha." );

         } /* fim ativa: Testar PILHA Criar Pilha */

		       /* Testar PILHA push */

         if ( strcmp( ComandoTeste , PUSH_PILHA ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm;
            } /* if */

			CRT_CriaCarta(&carta, 3, 4);
            CondRetObtido = PILHA_Push(pPilha, (void*) carta) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar Pilha." );

         } /* fim ativa: Testar PILHA PUSH */
            /* Testar PILHA pop */
		  if ( strcmp( ComandoTeste , POP_PILHA) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm;
            } /* if */

			   CRT_CriaCarta(&carta, 3, 4);
            CondRetObtido = PILHA_Pop(pPilha, (void*) carta) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar Pilha." );

         } /* fim ativa: Testar PILHA POP */


            /* Testar PILHA quantidade */
            if ( strcmp( ComandoTeste , QUANTIDADE) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                               &CondRetEsperada, &quantidade) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm;
            } /* if */

             
            CondRetObtido = PILHA_Quantidade(pPilha, &quantidade) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar Pilha." );

         } /* fim ativa: Testar Pilha quantidade */


             /* Testar PILHA decrementa */

             if ( strcmp( ComandoTeste , DECREMENTA_PILHA) == 0 )
          {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm;
            } /* if */

            CondRetObtido = PILHA_Decrementa(pPilha) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar Pilha." );

         } /* fim ativa: Testar Pilha decrementada */

            if ( strcmp( ComandoTeste , DETURPA) == 0 )
          {

            NumLidos = LER_LerParametros( "ii" ,
                               &CondRetEsperada, &acao) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm;
            } /* if */

            CondRetObtido = PILHA_Deturpa(pPilha, condDeturpacao) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Erro na deturpacao da pilha." );

         } /* fim ativa: Testar Pilha deturpa */

          if ( strcmp( ComandoTeste , VERIFICA) == 0 )
          {

            NumLidos = LER_LerParametros( "ii" ,
                               &CondRetEsperada, &nErros) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm;
            } /* if */

            CondRetObtido = PILHA_VerificarPilha(pPilha, &nErros);
            CondRetObtido = PILHA_VerificarPilha(pPilha, &nErros);
            printf("%d erros na pilha\n", nErro);

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Existem erros na pilha" );

         } /* fim ativa: Testar Pilha decrementada */

			  if ( strcmp( ComandoTeste , INCREMENTA_PILHA) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm;
            } /* if */

            CondRetObtido = PILHA_Incrementa(pPilha) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar Pilha." );

         } /* fim ativa: Testar Pilha incrementa */

            return TST_CondRetNaoConhec ;
}