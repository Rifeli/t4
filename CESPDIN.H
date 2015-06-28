#if ! defined( CESPDIN_ )
#define CESPDIN_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: CED  Controlador de espa�os de dados alocados dinamicamente
*
*  Arquivo gerado:              CESPDIN.h
*  Letras identificadoras:      CED
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: C:\AUTOTEST\PROJETOS\INSTRUM.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     O m�dulo de instrumenta��o CNTESPAC disponibiliza um conjunto de
*     fun��es para
*     - controlar a extravas�o de espa�os de dados alocados ao usu�rio
*     - controlar o acesso a espa�os j� desalocados
*     - controlar a consist�ncia entre o tipo implicito de um ponteiro e o
*       tipo do espa�o por ele apontado
*     - controlar o vazamento de mem�ria
*     - simular ter-se atingido o limite de mem�ria dispon�vel
*     - controlar a integridade da estrutura de espa�os de dados din�micos
*     - exibir o conte�udo de espa�os de dados em formato hexadecimal
*
*  $EIU Interface com o usu�rio pessoa
*     Para fazer com que um determinado m�dulo tenha todos os usos de
*     malloc e free controlados, basta incluir o m�dulo de defini��o
*     deste m�dulo. Idealmente use uma constru��o similar a:
*
*     #ifdef _DEBUG
*        #include "cntespac.h"
*     #endif
*
*     Isto far� com que todas as chamadas malloc e free do m�dulo controlado
*     sejam direcionadas para as fun��es equivalentes disponibilizadas
*     pelo presente m�dulo.
*
*     Para possibilitar a remo��o autom�tica da instrumenta��o
*     circunde todos os usos de fun��es desse m�dulo com o
*     comando de compila��o condicional #ifdef _DEBUG
*     A recompila��o do m�dulo instrumentado sem o nome _DEBUG
*     definido deveria resultar em zero erros de compila��o.
*     Antes de recompilar destrua o correspondente m�dulo objeto.
*
*     Para o correto funcionamento das fun��es desse m�dulo, � necess�rio
*     que contenha o comando:
*
*     #pragma pack (1)
*
*     Esse comando pode introduzir depend�ncias de plataforma,
*     tornando o m�dulo n�o port�til. Nesse caso remova o comando
*     #pragma e fa�a os ajustes necess�rios nas massas de teste e no
*     presente m�dulo de modo que se torne operacional na plataforma
*     desejada.
*
*     Em geral, o sintoma de mal funcionamento ap�s a remo��o de #pragma
*     � pequenas extravas�es de espa�o passarem despercebidas pela
*     instrumenta��o.
*
***************************************************************************/
 
#if defined( CESPDIN_OWN )
   #define CESPDIN_EXT
#else
   #define CESPDIN_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

#define     CED_PONTEIRO_NULO       -2


/***********************************************************************
*
*  $TC Tipo de dados: CED Modos de exibi��o
*
*
*  $ED Descri��o do tipo
*     Enumera todos os modos de listar espa�os alocados
*
***********************************************************************/

   typedef enum {

         CED_ExibirTodos    = 1 ,
               /* Exibir todos os espa�os */

         CED_ExibirAtivos   = 2 ,
               /* Exibir todos os espa�os ativos */

         CED_ExibirInativos = 3
               /* Exibir todos os espa�os inativos */

   } CED_tpModoExibir ;


/***********************************************************************
*
*  $FC Fun��o: CED  &Inicializar o controlador de aloca��o de espa�os din�micos
*
*  $ED Descri��o da fun��o
*     Esta fun��o inicializa o controlador de espa�os em mem�ria din�mica.
*     A fun��o deve ser chamada uma �nica vez, antes de qualquer outra fun��o
*     do m�dulo.
*     Sugere-se que seja chamada ao iniciar o teste do m�dulo controlado.
*     O interpretador de comandos de controle de espa�os din�micos
*     prov� o comando de teste  =inicializarespacos  que chama a presente
*     fun��o.
*
*  $EP Par�metros
*     $P pArqLogParm - ponteiro para o arquivo log de teste. N�o pode ser nulo.
*
***********************************************************************/

   void CED_InicializarControlador( void ) ;


/***********************************************************************
*
*  $FC Fun��o: CED  &Alocar espa�o
*
*  $ED Descri��o da fun��o
*     Nos m�dulos controlados esta fun��o substitui a fun��o "malloc".
*     A susbtitui��o � transparente para o m�dulo controlado,
*     basta que inclua o m�dulo de controle de acesso a espa�os de dados
*     din�micos. Ou seja, se o m�dulo de defini��o "Cntespac.h" for
*     incluido, a presente fun��o ser� utilizada ao chamar "malloc"
*     dentro do m�dulo cliente. N�o sendo incluido "Cntespac.h", ser�
*     chamada a fun��o "malloc" padr�o de C.
*
*     O espa�o ser� alocado com controle somente se o m�dulo de controle
*     de espa�o din�mico tiver sido inicializado, ver comando de teste
*
*         =inicializarespacos     e a correspondente fun��o.
*
*     Desta forma pode-se restringir o controle somente aos m�dulos
*     sob teste.
*
*     O valor (parte �til do espa�o alocado) � inicializado para o
*     caractere '|', permitindo a verifica��o de se o valor foi
*     corretamente inicializado ou n�o ap�s � inicializa��o na fun��o
*     cliente.
*
*     Para assegurar transpar�ncia � definida a macro CED_MALLOC
*     que providencia os argumentos linha e arquivo fonte. Estes, por sua
*     vez, permitem identificar onde o espa�o foi alocado, facilitando,
*     assim, resolver eventuais problemas de vazamento de mem�ria
*     e/ou de uso incorreto de espa�os.
*
*     A fun��o aloca um "struct" contendo diversos controles al�m do
*     espa�o �til (valor). O campo valor deste "struct" corresponde ao
*     espa�o que seria alocado pela fun��o de biblioteca "malloc".
*     O ponteiro retornado aponta para o campo valor, tornando
*     transparente o fato de se utilizar "malloc" ou esta fun��o.
*
*     A fun��o pode simular o esgotamento de mem�ria. Para isto � necess�rio
*     estabelecer um limite atrav�s de uma das fun��es a isto destinadas.
*     Por exemplo, se o limite de espa�o alocado for diferente de zero e o
*     total de espa�o j� alocado acrescido do espa�o solicitado for maior
*     do que o limite estabelecido, a fun��o n�o aloca espa�o e retorna NULL,
*     simulando falta de mem�ria.
*
*     Consulte as fun��es CED_Limitar... para detalhes das formas de
*     limite que podem ser estabelecidas.
*
*  $EP Par�metros
*     $P Tamanho          - n�mero de bytes do valor a ser alocado.
*     $P numLinhaFonte    - n�mero da linha do c�digo fonte onde foi
*                           chamada a fun��o. Use __LINE__ como argumento
*                           da chamada.
*     $P NomeArquivoFonte - nome do arquivo fonte contendo a chamada.
*                           Use __FILE__ como argumento da chamada.
*
*  $FV Valor retornado
*     Ponteiro void para o espa�o �til disponibilizado para a fun��o
*     cliente. O espa�o �til corresponde a o que seria retornado por malloc
*
*  $EIU Interface com usu�rio pessoa
*     Ao inv�s de utilizar a fun��o CED_Malloc utilize a macro CED_MALLOC
*     uma vez que esta fornece autom�ticamente a identifica��o do local
*     onde foi realizada a chamada.
*
***********************************************************************/

   #define  CED_MALLOC( Tamanho ) \
               CED_Malloc( Tamanho , __LINE__ , __FILE__ )

   void * CED_Malloc( size_t Tamanho ,
                      int    numLinhaFonte ,
                      char * NomeArquivoFonte ) ;


/***********************************************************************
*
*  $FC Fun��o: CED  &Desalocar espa�o
*
*  $ED Descri��o da fun��o
*     Elimina o elemento da lista de controle. Todos os bytes s�o tornados
*     iguais a '!' (x21). O identificador do tipo do espa�o tamb�m
*     � destru�do, possibilitando verificar se ele ainda est� alocado.
*
*     Ao usar esta fun��o deve-se tomar os seguintes cuidados:
*     - nunca use esta fun��o para desalocar um espa�o que n�o esteja sob
*       controle deste m�dulo. Ou seja, evite o uso de malloc e free em
*       m�dulos distintos em que malloc n�o � controlado e free �.
*     - nunca use free para desalocar um espa�o controlado por este m�dulo.
*       Ou seja, evite o uso de malloc e free em m�dulos distintos em
*       que malloc � controlado e free n�o �.
*
*     O mais seguro � ou ter todos os m�dulos sob controle, ou ter nenhum.
*
*  $EP Par�metros
*     $P Ponteiro - ponteiro para o campo valor (espa�o �til) do espa�o
*                   a ser liberado
*
***********************************************************************/

   void CED_Free( void * Ponteiro ) ;


/***********************************************************************
*
*  $FC Fun��o: CED  &Exibir conte�do do espa�o
*
*  $ED Descri��o da fun��o
*     Exibe o conteudo completo de um espa�o de mem�ria.
*     A parte �til � exibida em formato hexadecimal convencional
*
*  $EP Par�metros
*     $P Ponteiro - ponteiro para o valor (parte �til) contido no espa�o
*                   alocado, � o ponteiro retornado por CED_Malloc.
*
***********************************************************************/

   void CED_ExibirEspaco( void * Ponteiro ) ;


/***********************************************************************
*
*  $FC Fun��o: CED  &Exibir todos os espa�os
*
*  $ED Descri��o da fun��o
*     Exibe todos os espa�os que satisfazem uma determinada regra.
*     Ver o tipo CED_tpModoExibir para uma explica��o quanto �s regras
*     de sele��o de espa�os a exibir.
*
***********************************************************************/

   void CED_ExibirTodosEspacos( CED_tpModoExibir Regra ) ;


/***********************************************************************
*
*  $FC Fun��o: CED  &Definir tipo do espa�o
*
*  $ED Descri��o da fun��o
*     Caso o tipo do espa�o ainda n�o esteja definido, atribui o tipo.
*
*     O tipo do espa�o � inicializado para CED_ID_TIPO_VALOR_NULO
*     quando da aloca��o com CED_Malloc. Posteriormente pode ser
*     alterado com a presente fun��o.
*
*     A atribui��o ser� realizada somente se uma das condi��es a seguir
*     for verdadeira:
*     - o tipo a ser atribuido � CED_ID_TIPO_VALOR_NULO
*     - ou o tipo do espa�o � CED_ID_TIPO_VALOR_NULO
*
*     Para trocar o tipo de um espa�o precisa-se primeiro torn�-lo
*     igual a CED_ID_TIPO_VALOR_NULO para, depois, atribuir o novo tipo.
*
*     Uma vez definido o tipo do espa�o, fun��es cliente podem controlar
*     a consist�ncia entre o tipo implicitamente associado ao ponteiro
*     e o tipo que o espa�o de fato cont�m.
*
*     Sugere-se que o desenvolvedor da aplica��o crie uma tabela global
*     contendo um "enum" com os nomes de todos os tipos ('typedef struct') que
*     podem ser utilizados como declaradores de espa�os din�micos.
*     Ao definir o tipo, pode-se, agora, utilizar o nome correspondente
*     ao tipo do espa�o alocado como o idTipo a ser definido. Veja
*     as explica��es no arquivo IdTiposEspaco.def
*
*     O presente sistema de controle de tipos n�o prev� mecanismos para
*     tratamentoi de heran�a.
*
*  $EP Par�metros
*     $P Ponteiro - ponteiro para o campo valor (espa�o �til) do espa�o
*                   a ser tipado
*     $P idTipo   - novo identificador de tipo a ser dado ao espa�o.
*
*  $FV Valor retornado
*     TRUE   1    - se a atribui��o foi bem sucedida
*     FALSE  0    - se n�o foi poss�vel atribuir. Isto ser� o caso se
*                   o tipo do esp�co j� estava definido ao chamar a fun��o,
*                   ou se o ponteiro for NULL.
*
***********************************************************************/

   int CED_DefinirTipoEspaco( void * Ponteiro , int idTipo ) ;


/***********************************************************************
*
*  $FC Fun��o: CED  &Marcar ativo o espa�o
*
*  $ED Descri��o da fun��o
*     Marca determinado espa�o como ativo.
*
*     A marca ativo/n�o ativo � utilizada para apoiar o controle de
*     vazamento de mem�ria. Siga o seguinte roteiro:
*     - Marque todos os espa�os n�o ativos.
*     - Percorra as estruturas ativas marcando ativos os espa�os visitados.
*     - Percorra a lista de todos os espa�os verificando se cada espa�o visitado
*       � ou n�o inativo.
*
*  $EP Par�metros
*     $P Ponteiro - ponteiro para o campo valor (espa�o �til) do espa�o
*                   a ser marcado
*
***********************************************************************/

   void CED_MarcarEspacoAtivo( void * Ponteiro ) ;


/***********************************************************************
*
*  $FC Fun��o: CED  &Marcar n�o ativo o espa�o
*
*  $ED Descri��o da fun��o
*     Ver CED_MarcarEspacoAtivo
*
*  $EP Par�metros
*     $P Ponteiro - ponteiro para o campo valor (espa�o �til) do espa�o
*                   a ser marcado
*
***********************************************************************/

   void CED_MarcarEspacoNaoAtivo( void * Ponteiro ) ;


/***********************************************************************
*
*  $FC Fun��o: CED  &Marcar n�o ativos todos os espa�os
*
*  $ED Descri��o da fun��o
*     Percorre todos os espa�os alocados marcando-os inativos.
*
***********************************************************************/

   void CED_MarcarTodosEspacosInativos( ) ;


/***********************************************************************
*
*  $FC Fun��o: CED  &Limitar mem�ria dispon�vel
*
*  $ED Descri��o da fun��o
*     Estabelece um limite de mem�ria dispon�vel. Este limite afeta
*     o comportamento da fun��o CED_Malloc.
*
*     Embora a fun��o possa ser chamada a qualquer momento, recomenda-se
*     que seja chamada antes do primeiro caso de teste capaz de alocar
*     espa�o de mem�ria din�mica por interm�dio da fun��o CED_Malloc
*     contida nesse m�dulo.
*
*  $EP Par�metros
*     $P NovoLimiteMemoria - Estabelece o limite de mem�ria dispon�vel.
*                            Caso seja zero, o controle de limite n�o
*                            ser� efetuado por CED_Malloc.
*
***********************************************************************/

   void CED_LimitarMemoriaDisponivel( long NovoLimiteMemoria ) ;


/***********************************************************************
*
*  $FC Fun��o: CED  &Limitar n�mero de espa�os alocados
*
*  $ED Descri��o da fun��o
*     Limita o n�mero de espa�os alocados. Esta fun��o afeta o comportamento
*     de CED_Malloc, estabelecendo um limite para o n�mero total de
*     espa�os alocados em um dado momento.
*
*     Embora a fun��o possa ser chamada a qualquer momento, recomenda-se
*     que seja chamada antes do primeiro caso de teste que provoque
*     aloca��o de espa�o de mem�ria.
*
*  $EP Par�metros
*     $P numTotalEspacos - indica o limite de espa�os que podem estar
*                          alocados a cada instante. Se zero, n�o
*                          ser� realizado o controle.
*
***********************************************************************/

   void CED_LimitarNumeroTotalEspacos( long numTotalEspacos ) ;


/***********************************************************************
*
*  $FC Fun��o: CED  &Limitar, eliminar limites
*
*  $ED Descri��o da fun��o
*     Esta fun��o elimina todos os limites de mem�ria por ventura em vigor.
*
***********************************************************************/

   void CED_EliminarLimites( ) ;


/***********************************************************************
*
*  $FC Fun��o: CED  &Obter o tipo do espa�o de dados
*
*  $ED Descri��o da fun��o
*     Retorna o identificador do tipo do espa�o apontado.
*     Ser� CED_ID_TIPO_ESPACO_NULO se nunca foi atribu�do um tipo ao espa�o
*     e ser� CED_ID_TIPO_ILEGAL se o espa�o j� havia sido liberado.
*
*  $EP Par�metros
*     $P Ponteiro - ponteiro para o campo valor (espa�o �til) do espa�o
*                   do qual se deseja saber o tipo
*
***********************************************************************/

   int CED_ObterTipoEspaco( void * Ponteiro ) ;


/***********************************************************************
*
*  $FC Fun��o: CED  &Obter tamanho do valor contido no espa�o
*
*  $ED Descri��o da fun��o
*     Retorna o n�mero de bytes �teis do espa�o
*
*  $EP Par�metros
*     $P Ponteiro - ponteiro para a por��o �til do espa�o
*                   da qual se deseja saber o tamanho
*
***********************************************************************/

   int CED_ObterTamanhoValor( void * Ponteiro ) ;


/***********************************************************************
*
*  $FC Fun��o: CED  &Obter n�mero de espa�os alocados
*
*  $ED Descri��o da fun��o
*     Retorna o n�mero de espa�os contidos na lista de espa�os alocados
*
***********************************************************************/

   int CED_ObterNumeroEspacosAlocados( ) ;


/***********************************************************************
*
*  $FC Fun��o: CED  &Obter total de espa�os alocados
*
*  $ED Descri��o da fun��o
*     Retorna o n�mero total de vezes que foi chamada a fun��o
*     CED_Malloc.
*
***********************************************************************/

   int CED_ObterTotalAlocacoes( ) ;


/***********************************************************************
*
*  $FC Fun��o: CED  &Obter n�mero de espa�os segundo regra
*
***********************************************************************/

   int CED_ObterNumeroEspacos( CED_tpModoExibir Regra ) ;


/***********************************************************************
*
*  $FC Fun��o: CED  &Obter espa�o total alocado
*
*  $ED Descri��o da fun��o
*     Obt�m o total em bytes de espa�os �teis alocados.
*
***********************************************************************/

   long CDE_ObterEspacoTotalAlocado( ) ;


/***********************************************************************
*
*  $FC Fun��o: CED  &Iterador: iniciar iterador de espa�os
*
*  $ED Descri��o da fun��o
*     Inicia o iterador com o primeiro espa�o da lista de controle de espa�os
*     din�micos.
*
***********************************************************************/

   void CED_InicializarIteradorEspacos( ) ;


/***********************************************************************
*
*  $FC Fun��o: CED  &Iterador: avan�ar para o pr�ximo espa�o
*
*  $ED Descri��o da fun��o
*     Avan�a o iterador para o pr�ximo espa�o.
*
*  $FV Valor retornado
*     TRUE  caso o espaco para o qual caminhou existe.
*     FALSE se n�o existe iterador ou chegou ao fim da lista de espa�os
*
***********************************************************************/

   int CED_AvancarProximoEspaco( ) ;


/***********************************************************************
*
*  $FC Fun��o: CED  &Iterador: obter refer�ncia para o espa�o corrente
*
*  $ED Descri��o da fun��o
*     Obt�m a refer�ncia para a parte �til do espa�o corrente.
*
***********************************************************************/

   void * CED_ObterPonteiroEspacoCorrente( ) ;


/***********************************************************************
*
*  $FC Fun��o: CED  &Iterador: existe espa�o corrente
*
*  $ED Descri��o da fun��o
*     Verifica se o iterador referencia um espa�o corrente.
*
***********************************************************************/

   int CED_ExisteEspacoCorrente( ) ;


/***********************************************************************
*
*  $FC Fun��o: CED  &Iterador: terminar iterador
*
*  $ED Descri��o da fun��o
*     Desativa o iterador. Deixa de existir a refer�ncia para o esp�co corrente.
*
***********************************************************************/

   void CED_TerminarIteradorEspacos( ) ;


/***********************************************************************
*
*  $FC Fun��o: CED  &Iterador: excluir espa�o corrente
*
*  $ED Descri��o da fun��o
*     Elimina o espa�o corrente da lista de espa�os controlados.
*     O espa�o � liberado tornando ilegais todos os acessos realizados
*     por fun��es do usu�rio. Utilize esta fun��o somente para deturpar, ou
*     para eliminar espa�os sabidamente inativos.
*
***********************************************************************/

   void CED_ExcluirEspacoCorrente( ) ;


/***********************************************************************
*
*  $FC Fun��o: CED  &Verificar se espa�o � ativo
*
*  $ED Descri��o da fun��o
*     Retorna TRUE se o espa�o referenciado est� marcado ativo
*
*  $EP Par�metros
*     $P Ponteiro - ponteiro para o campo valor (espa�o �til) do espa�o
*                   do qual se deseja saber se � ativo ou n�o
*
***********************************************************************/

   int CED_EhEspacoAtivo( void * Ponteiro ) ;


/***********************************************************************
*
*  $FC Fun��o: CED  &Verificar a integridade de um espa�o de dados
*
*  $ED Descri��o da fun��o
*     Verifica a integridade de um determinado espa�o de dados.
*     Retorna o n�mero de falhas encontradas.
*     Esta fun��o pode levar a um cancelamento por erro, caso o ponteiro
*     fornecido esteja errado.
*
*  $EP Par�metros
*     $P Ponteiro para a por��o �til do espa�o. Este � o ponteiro
*                 retornado pela fun��o CED_Malloc
*     $P int pVerificarValor( void * pValor )
*                 fun��o fornecida pelo cliente para verificar a corretude
*                 do espa�o �til. A fun��o recebe como par�metro um
*                 ponteiro para o espa�o a verificar e retorna
*                 0 caso o espa�o n�o esteja correto e != 0 se estiver
*                 correto. Todas as mensagens de erro devem ser dadas
*                 pela fun��o de verifica��o. Procure utilizar as
*                 fun��es do m�dulo TESTEGEN para exibir as mensagens
*                 e realizar as compara��es.
*                 Caso n�o deseje verificar o valor, forne�a NULL como
*                 argumento.
*
*  $FV Valor retornado
*     TRUE   se espa�o � v�lido ou o ponteiro for NULL
*     FALSE  caso contr�rio
*
***********************************************************************/

   int CED_VerificarEspaco( void * Ponteiro ,
                            int ( * pVerificarValor )( void * pValor )) ;


/***********************************************************************
*
*  $FC Fun��o: CED  &Verificar todos os espa�os alocados
*
*  $ED Descri��o da fun��o
*     Percorre toda a lista, verificando um a um os espa�os.
*     Caso um ou mais espa�os estejam errados, pode ocorrer
*     cancelamento da execu��o em virtude de acesso a mem�ria ilegal.
*
*  $EP Par�metros
*     $P pVerificarValor - � o ponteiro para uma fun��o que verifica o conte�do
*                          do espa�o �til. O par�metro pValor dessa fun��o
*                          apontar� para o valor a ser controlado
*
*  $FV Valor retornado
*     TRUE   se todos os espa�os est�o v�lidos
*     FALSE  caso contr�rio
*
***********************************************************************/

   int CED_VerificarTudo( int ( * pVerificarValor )( void * pValor )) ;

/***********************************************************************

/* C�digo final do m�dulo */

#if !defined( CESPDIN_OWN )
   #define malloc CED_MALLOC
   #define free   CED_Free
#endif

#undef CESPDIN_EXT

/********** Fim do m�dulo de defini��o: CED  Controlador de espa�os de dados alocados dinamicamente **********/

#else
#endif