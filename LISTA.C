/***************************************************************************
*  $MCI Módulo de implementação: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define LISTA_OWN
#include "LISTA.h"
#undef LISTA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

   typedef struct tagElemLista {

         void * pValor ;
               /* Ponteiro para o valor contido no elemento */

         struct tagElemLista * pAnt ;
               /* Ponteiro para o elemento predecessor */

         struct tagElemLista * pProx ;
               /* Ponteiro para o elemento sucessor */
         #ifdef _DEBUG
            char[50] tipo;
         #endif
   } tpElemLista ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabeça de lista
*
*
***********************************************************************/

   typedef struct LIS_tagLista {

         tpElemLista * pOrigemLista ;
               /* Ponteiro para a origem da lista */

         tpElemLista * pFimLista ;
               /* Ponteiro para o final da lista */

         tpElemLista * pElemCorr ;
               /* Ponteiro para o elemento corrente da lista */

         int numElem ;
               /* Número de elementos da lista */

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a função de destruição do valor contido em um elemento */

   } LIS_tpLista ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void LiberarElemento( LIS_tppLista   pLista ,
                                tpElemLista  * pElem   ) ;

   static tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                       void *       pValor  ) ;

   static void LimparCabeca( LIS_tppLista pLista ) ;

/*****  Código das funções exportadas pelo módulo  *****/
#ifdef _DEBUG
   static char lixo[256] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
   //ação 1: libera elemento corrente da estrutura escolhida
  int LIS_LiberaElemCorrente(LIS_tppLista pLista)
   {
      free( pLista->pElemCorr ) ;
      return 1;
   }
   //ação 2: atribui null para o sucesso
   int LIS_SucesNULL(LIS_tppLista pLista)
   {
      pLista->pElemCorr->pProx = NULL ;
      return 1;
   }
   //ação 3: atribui null para o antecessor
   int LIS_PreNULL(LIS_tppLista pLista)
   {
      pLista->pElemCorr->pAnt = NULL ;
      return 1;
   }
   //ação 4: atribui lixo para o sucesso
   int LIS_LixoSucessor(LIS_tppLista pLista)
   {
      pLista->pElemCorr->pProx = (LIS_tppLista *) lixo;
      return 1;
   }
   //ação 5: atribui lixo para o precessor
   int LIS_LixoPre(LIS_tppLista pLista)
   {
      pLista->pElemCorr->pProx = (LIS_tppLista *) lixo;
      return 1;
   }
   //ação 6: atribui NULL para o conteudo do nó
   int LIS_NULLConteudo(LIS_tppLista pLista)
   {
      pLista->pElemCorr->pValor = NULL ;
      return 1;
   }
   //ação 7: altera o tipo do nó
   int LIS_AlteraTipoDoConteudo(LIS_tppLista pLista)
   {
      pLista->pElemCorr->tipo = "tipo_errado";
      return 1;
   }
   //ação 8: destaca o conteudo
   int LIS_DestacaConteudo(LIS_tppLista pLista)
   {
      pLista->pElemCorr->pAnt->pProx = pLista->pElemCorr->pProx ;
      pLista->numElem--;
      pLista->pElemCorr->pProx->pAnt = pLista->pElemCorr->pAnt ;
      return 1;
   }
   //ação 9: corrente nulo
   int LIS_NULLCorrente(LIS_tppLista pLista)
   {
      pLista->pElemCorr = NULL ;
      return 1;
   }
   //ação 10: origim nulo
   int LIS_NULLOrigem(LIS_tppLista pLista)
   {
      pLista->pOrigemLista = NULL ;
      return 1;
   }

#endif

#ifdef _DEBUG

LIS_tpCondRet LIS_VerificaLiberaElemCorrente(LIS_tppLista pLista){
   if(pLista->pElemCorr == NULL)
      return LIS_CondRetListaNaoExiste;
}

LIS_tpCondRet LIS_VerificaSucessorNULL(LIS_tppLista pLista){
   int cond;
   LIS_tppLista lis;

   cond = IrFinalLista(pLista);
   if( cond != LIS_CondRetOK)
      return cond;

   for(lis = pLista; lis->ant != NULL; lis = list->ant)
      if(lis->ant->prox == NULL)
         return LIS_CondRetSucessorNulo;

   if(lis->prox == NULL)
      return LIS_CondRetSucessorNulo;

   return LIS_CondRetOK;
}



LIS_tpCondRet LIS_VerificaPredecessorNULL(LIS_tppLista pLista){
   int cond;
   LIS_tppLista lis;

   cond = IrInicioLista(pLista);
   if( cond != LIS_CondRetOK)
      return cond;

   for(lis = pLista; lis->prox != NULL; lis = list->prox)
      if(lis->prox->ant == NULL)
         return LIS_CondRetPredecessor;

   if(lis->ant == NULL)
      return LIS_CondRetPredecessor;

   return LIS_CondRetOK;
}

LIS_tpCondRet LIS_VerificaLixoSucessor(LIS_tppLista pLista){
   int cond;
   LIS_tppLista lis;

   cond = IrFinalLista(pLista);
   if( cond != LIS_CondRetOK)
      return cond;

   for(lis = pLista; lis->ant != NULL; lis = list->ant)
      if(lis->ant->prox != NULL && lis->ant->prox != lis)
         return LIS_CondRetSucessorLixo;

   if(lis->prox != NULL && lis->prox->ant->prox != lis->prox)
      return LIS_CondRetSucessorLixo;

   return LIS_CondRetOK;
}

LIS_tpCondRet LIS_VerificaLixoPredecessor(LIS_tppLista pLista){
   int cond;
   LIS_tppLista lis;

   cond = IrInicioLista(pLista);
   if( cond != LIS_CondRetOK)
      return cond;

   for(lis = pLista; lis->prox != NULL && lis->prox->ant == list; lis = list->prox)
      if(lis->prox->ant != NULL && lis->prox->ant != lis)
         return LIS_CondRetPredecessorLixo;

   if(lis->ant != NULL && lis->ant->prox != lis)
      return LIS_CondRetPredecessorLixo;

   return LIS_CondRetOK;
}

LIS_tpCondRet LIS_VerificaConteudoNulo(LIS_tppLista pLista){
   return (pLista->pElemCorr->valor == NULL) ? LIS_CondRetConteudoNulo : LIS_CondRetOK;
}

LIS_tpCondRet LIS_VerificaTipoConteudo(LIS_tppLista pLista, char * tipo){
   return (strcmp(pLista->pElemCorr->tipo,tipo) == 0 ? LIS_CondRetOK : LIS_CondRetTipoInvalido);
}

LIS_tpCondRet LIS_VerificaCorrenteNulo(LIS_tppLista pLista){
   return (pLista->pElemCorr == NULL) ? LIS_CondRetCorrenteNull : LIS_CondRetOK;
}

LIS_tpCondRet LIS_pOrigemNulo(LIS_tppLista pLista){
   return (pLista->pOrigemLista == NULL) ? LIS_CondRetCorrenteNull : LIS_CondRetOK;   
}
//confere numero da quantidade com o numero de movimentos possiveis dentro da lista
LIS_tpCondRet LIS_confereNumero(LIS_tppLista pLista){
   int i, j;
   LIS_tppLista lis;
   cond = IrInicioLista(pLista);
   if(cond != LIS_CondRetOK)
      return cond;
   for(lis = pLista, i = 0; lis->prox != NULL; lis = list->prox, i++);
   cond = IrFinalLista(pLista);
   if(cond != LIS_CondRetOK)
      return cond;
   for(lis = pLista, j = 0; lis->ant != NULL; lis = list->ant, j++);
   return ((i > j ? i : j) < (pLista->numElem ? LIS_CondRetOK : LIS_CondRetNaoAchou));
}

#endif

int LIS_NumeroDeElementos(LIS_tppLista pLista){
   return pLista->numElem;
}

/***************************************************************************
*
*  Função: LIS  &Criar lista
*  ****/

   LIS_tppLista LIS_CriarLista(
             void   ( * ExcluirValor ) ( void * pDado ) )
   {

      LIS_tpLista * pLista = NULL ;

      pLista = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista )) ;
      if ( pLista == NULL )
      {
         return NULL ;
      } /* if */

      LimparCabeca( pLista ) ;

      pLista->ExcluirValor = ExcluirValor ;

      return pLista ;

   } /* Fim função: LIS  &Criar lista */

/***************************************************************************
*
*  Função: LIS  &Destruir lista
*  ****/

   void LIS_DestruirLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      LIS_EsvaziarLista( pLista ) ;

      free( pLista ) ;

   } /* Fim função: LIS  &Destruir lista */

/***************************************************************************
*
*  Função: LIS  &Esvaziar lista
*  ****/

   void LIS_EsvaziarLista( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;
      tpElemLista * pProx ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      pElem = pLista->pOrigemLista ;
      while ( pElem != NULL )
      {
         pProx = pElem->pProx ;
         LiberarElemento( pLista , pElem ) ;
         pElem = pProx ;
      } /* while */

      LimparCabeca( pLista ) ;

   } /* Fim função: LIS  &Esvaziar lista */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento antes
*  ****/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor,
                                           char * tipo)
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Criar elemento a inerir antes */

         pElem = CriarElemento( pLista , pValor, tipo ) ;
         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento antes do elemento corrente */

         if ( pLista->pElemCorr == NULL )
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pAnt != NULL )
            {
               pElem->pAnt  = pLista->pElemCorr->pAnt ;
               pLista->pElemCorr->pAnt->pProx = pElem ;
            } else
            {
               pLista->pOrigemLista = pElem ;
            } /* if */

            pElem->pProx = pLista->pElemCorr ;
            pLista->pElemCorr->pAnt = pElem ;
         } /* if */

         pLista->pElemCorr = pElem ;

         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Inserir elemento antes */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento após
*  ****/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor
                                          char * tipo)
      
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Criar elemento a inerir após */

         pElem = CriarElemento( pLista , pValor , tipo) ;
         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento após o elemento */

         if ( pLista->pElemCorr == NULL )
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pProx != NULL )
            {
               pElem->pProx  = pLista->pElemCorr->pProx ;
               pLista->pElemCorr->pProx->pAnt = pElem ;
            } else
            {
               pLista->pFimLista = pElem ;
            } /* if */

            pElem->pAnt = pLista->pElemCorr ;
            pLista->pElemCorr->pProx = pElem ;

         } /* if */
                  
         pLista->pElemCorr = pElem ;
                  
         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Inserir elemento após */

/***************************************************************************
*
*  Função: LIS  &Excluir elemento
*  ****/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      pElem = pLista->pElemCorr ;

      /* Desencadeia à esquerda */

         if ( pElem->pAnt != NULL )
         {
            pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pElemCorr    = pElem->pAnt ;
         } else {
            pLista->pElemCorr    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pElemCorr ;
         } /* if */

      /* Desencadeia à direita */

         if ( pElem->pProx != NULL )
         {
            pElem->pProx->pAnt = pElem->pAnt ;
         } else
         {
            pLista->pFimLista = pElem->pAnt ;
         } /* if */

      LiberarElemento( pLista , pElem ) ;

      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Excluir elemento */

/***************************************************************************
*
*  Função: LIS  &Obter referência para o valor contido no elemento
*  ****/

   void * LIS_ObterValor( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
        return NULL ;
      } /* if */

      return pLista->pElemCorr->pValor ;

   } /* Fim função: LIS  &Obter referência para o valor contido no elemento */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento inicial
*  ****/

   void IrInicioLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      pLista->pElemCorr = pLista->pOrigemLista ;

   } /* Fim função: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento final
*  ****/

   void IrFinalLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      pLista->pElemCorr = pLista->pFimLista ;

   } /* Fim função: LIS  &Ir para o elemento final */

/***************************************************************************
*
*  Função: LIS  &Avançar elemento
*  ****/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem )
   {

      int i ;

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Tratar lista vazia */

         if ( pLista->pElemCorr == NULL )
         {

            return LIS_CondRetListaVazia ;

         } /* fim ativa: Tratar lista vazia */

      /* Tratar avançar para frente */

         if ( numElem > 0 )
         {

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i > 0 ; i-- )
            {
               if ( pElem == NULL )
               {
                  break ;
               } /* if */
               pElem    = pElem->pProx ;
            } /* for */

            if ( pElem != NULL )
            {
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pFimLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avançar para frente */

      /* Tratar avançar para trás */

         else if ( numElem < 0 )
         {

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i < 0 ; i++ )
            {
               if ( pElem == NULL )
               {
                  break ;
               } /* if */
               pElem    = pElem->pAnt ;
            } /* for */

            if ( pElem != NULL )
            {
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pOrigemLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avançar para trás */

      /* Tratar não avançar */

         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Avançar elemento */

/***************************************************************************
*
*  Função: LIS  &Procurar elemento contendo valor
*  ****/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor        )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      for ( pElem  = pLista->pElemCorr ;
            pElem != NULL ;
            pElem  = pElem->pProx )
      {
         if ( pElem->pValor == pValor )
         {
            pLista->pElemCorr = pElem ;
            return LIS_CondRetOK ;
         } /* if */
      } /* for */

      return LIS_CondRetNaoAchou ;

   } /* Fim função: LIS  &Procurar elemento contendo valor */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: LIS  -Liberar elemento da lista
*
*  $ED Descrição da função
*     Elimina os espaços apontados pelo valor do elemento e o
*     próprio elemento.
*
***********************************************************************/

   void LiberarElemento( LIS_tppLista   pLista ,
                         tpElemLista  * pElem   )
   {

      if ( ( pLista->ExcluirValor != NULL )
        && ( pElem->pValor != NULL        ))
      {
         pLista->ExcluirValor( pElem->pValor ) ;
      } /* if */

      free( pElem ) ;

      pLista->numElem-- ;

   } /* Fim função: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Função: LIS  -Criar o elemento
*
***********************************************************************/

   tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                void *       pValor  ,
                                char * tipo)
   {

      tpElemLista * pElem ;

      pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
      if ( pElem == NULL )
      {
         return NULL ;
      } /* if */

      pElem->pValor = pValor ;
      pElem->pAnt   = NULL  ;
      pElem->pProx  = NULL  ;
      pElem->tipo   = tipo;
      pLista->numElem ++ ;

      return pElem ;

   } /* Fim função: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Função: LIS  -Limpar a cabeça da lista
*
***********************************************************************/

   void LimparCabeca( LIS_tppLista pLista )
   {

      pLista->pOrigemLista = NULL ;
      pLista->pFimLista = NULL ;
      pLista->pElemCorr = NULL ;
      pLista->numElem   = 0 ;

   } /* Fim função: LIS  -Limpar a cabeça da lista */

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/

