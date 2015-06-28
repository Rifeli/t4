#if ! defined( CONTA_ )
#define CONTA_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: CNT  Contadores de passagem
*
*  Arquivo gerado:              CONTA.h
*  Letras identificadoras:      CNT
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
*     Este m�dulo implementa fun��es para o controle de cobertura dos
*     testes de m�dulos. O controle de cobertura baseia-se
*     em contagem de passagens
*
*     Contadores s�o identificados por nomes simb�licos, um string.
*     Para assegurar o controle efetivoo, deve ser criado um arquivo
*     com todos os nomes de contadores definidos no m�dulo a testar.
*     Este arquivo dever� ser lido antes de iniciar os testes.
*     Ao final a tabela de s�mbolos pode ser examinada � procura de
*     contadores que n�o tenham sido contados durante a execu��o do
*     teste.
*
*     Os m�dulos a serem medidos devem ser marcados com chamadas para
*     a fun��o de contagem disponibilizada pelo presente m�dulo:
*        CNT_Conta( <nome> ) ;
*     em que <nome> � um dos nomes que figura no arquivo de contagem.
*     Deve-se assegurar que todas as chamadas utilizem nomes diferentes
*     dos demais nomes utilizados em outras chjamadas a esta fun��o.
*
*     Os contadores podem ser inicializados com valores. Os seguintes
*     valores t�m significado especial:
*        -1 - contador opcional. Caso o teste n�o passe pela correspondente
*             chamada � fun��o de contagem, o sistema n�o acusar�
*             erro de falta de cobertura.
*        -2 - contador proibido. Deve ser utilizado para marcar os
*             fragmentos de c�digo que em uma execu��o correta normal
*             jamais devem ser executados. Estes fragmentos correspondem
*             tipicamente ao c�digo de controle de integridade da execu��o.
*
*     O arquivocont�m dados por linha de texto. Cada linha de texto
*     poder� ser um de:
*
*       // coment�rio - linha de coment�rio
*
*       linha em branco
*
*       nome/=numero  - defini��o de um contador.
*                       nome � o string que identifica o contador
*                       /= � o operador de inicializa��o, opcional
*                       numero � o valor inicial a ser atribu�do
*                              s� pode ser fornecido se o operador /=
*                              for fornecido
*
*     Os contadores podem ser acumulados em arquivos de totatilza��o.
*     Isto permite controlar a cobertura dos testes quando forem
*     utilizadas v�rias massas (scripts) de teste.
*     O arquivo de totaliza��o tem o mesmo formato que o de defini��o
*     de contadores.
*
*     Antes de iniciar a execu��os dos testes deve ser lido o arquivo
*     de defini��o de contadores e, se for o caso, identificado
*     o arquivo de totaliza��o.
*
*     Ao terminar os testes deve ser verificada a cobertura medida.
*     Caso esta n�o seja integral, as massas de teste devem ser
*     corrigidas de modo que a cobertura passe a ser integral.
*
*     Veja os comandos de teste
*        =inicializarcontadores
*        =lerarquivocontadores
*     definidos no m�dulo de interpreta��o de comandos de contagem
*
*        INTCNT
*
*  $EIU Interface com o usu�rio pessoa
*     Ao desenvolver m�dulos que dever�o ser medidos siga as
*     seguintes instru��es:
*
*     - Assegure que a fun��o CNT_InicializarContadores seja
*       chamada antes de iniciar a medi��o
*
*     - Assegure que a fun��o de declara��o de contadores seja
*       lida antes de iniciar a medi��o
*
*     - Assegure que a fun��o CNT_IniciarContagem seja chamada
*       ao iniciar a execu��o do c�digo a ser medido
*
*     - Dependendo do modo de medir inclua no m�dulo a medir
*       o fragmento
*          #ifdef _DEBUG
*             CNT_CONTAR( NomeContador ) ;
*          #endif
*
*     - Assegure que cada chamada a esta fun��o referencie um
*       contador n�o referenciado pelas demais chamadas.
*
*     - Ao terminar a execu��o da por��o de c�digo a medir
*       chame a fun��o CNT_PararContagem
*
*     - Antes de terminar a execu��o chame a fun��o CNT_VerificarContagem
*       Esta fun��o listar� todos os contadores que contenham zero,
*       ou seja que n�o tenham figurado em uma chamada para
*       CNT_CONTAR no decorrer da execu��o.
*
*     Este processo pode ser modificado no caso de se querer realizar
*     outras formas de contagem.
*
***************************************************************************/
 
#if defined( CONTA_OWN )
   #define CONTA_EXT
#else
   #define CONTA_EXT extern
#endif


/***********************************************************************
*
*  $TC Tipo de dados: CNT Condi��es de retorno
*
*
***********************************************************************/

   typedef enum {

         CNT_CondRetOK = 0 ,
               /* CNT retornou normal */

         CNT_CondRetErro = -11 ,
               /* CNT Encontrou erro */

         CNT_CondRetNaoContador = -12 ,
               /* CNT Contador n�o existe */

         CNT_CondRetOpcional = -13 ,
               /* CNT Contador � opcional */

         CNT_CondRetProibido = -14 ,
               /* CNT Contador n�o pode ser contado */

         CNT_CondRetInicializado = -15 ,
               /* CNT M�dulo contador j� inicializado */

         CNT_CondRetNaoInicializado = -16 ,
               /* CNT M�dulo contador n�o inicializado */

         CNT_CondRetNaoIterador = -17
               /* CNT Iterador lista ordenada n�o incializado */

   } CNT_tpCondRet ;


/***********************************************************************
*
*  $FC Fun��o: CNT  &Inicializar contadores
*
*  $ED Descri��o da fun��o
*     Esta fun��o inicializa uma se��o de contagem.
*     Uma aplica��o pode conter diversas se��es de contagem mutuamente
*     independentes.
*     Esta fun��o deve ser chamada exatamente uma vez no in�cio de
*     cada se��o.
*     Ao final da se��o deve ser chamada a fun��o
*        CNT_TerminarContadores
*
*  $EP Par�metros
*     $P pArqLog  - ponteiro FILE * apontando para o arquivo log
*                   em uso. Todas as mensagens s�o gravadas no arquivo log.
*                   Se este ponteiro for NULL ser� utilizado o arquivo
*                   stdout.
*
*     $P NomeArquivo - ponteiro para o nome do arquivo de contagem
*                   acumulada. Se NULL ou se n�o conseguir abrir,
*                   n�o existe arquivo de contagem acumulada.
*                   Neste caso deve ser lido o arquivo de defini��o
*                   de nomes de contadores.
*                   Ao final da se��o de contagem ser� gerado o arquivo
*                   de contagem acumulada, caso o par�metro tenha sido
*                   diferente de NULL.
*
***********************************************************************/

   CNT_tpCondRet CNT_InicializarContadores( FILE * pArqLog , char * NomeArquivo ) ;


/***********************************************************************
*
*  $FC Fun��o: CNT  &Registrar arquivo acumulador
*
*  $ED Descri��o da fun��o
*     Registra ou substitui o nome do arquivo acumulador registrado no
*     m�dulo contador
*
***********************************************************************/

   void CNT_RegistrarAcumulador( char * NomeArquivo ) ;


/***********************************************************************
*
*  $FC Fun��o: CNT  &Terminar contadores
*
*  $ED Descri��o da fun��o
*     Termina a se��o de contagem.
*     Grava o arquivo de contagem acumulada caso tenha sido definido.
*
*     Veja CNT_InicializarContadores para mais detalhes.
*
***********************************************************************/

   CNT_tpCondRet CNT_TerminarContadores( ) ;


/***********************************************************************
*
*  $FC Fun��o: CNT  &Ler arquivo de defini��o de contadores
*
*  $FV Valor retornado
*     Retorna o n�mero de erros de leitura reportado.
*
***********************************************************************/

   int CNT_LerContadores( char * NomeArquivoDefinicao ) ;


/***********************************************************************
*
*  $FC Fun��o: CNT  &Iniciar a contagem
*
*  $ED Descri��o da fun��o
*     Inicia a contagem. Enquanto esta fun��o n�o tiver sido chamada,
*     n�o � realizada a contagem ao passar pela fun��o CNT_Conta
*     Starts passage counting. Passage counting will occur only
*
*     Contagem pode ser parada com CNT_PararContagem
*
***********************************************************************/

   void CNT_IniciarContagem( ) ;


/***********************************************************************
*
*  $FC Fun��o: CNT  &Contar
*
*  $ED Descri��o da fun��o
*     Adiciona 1 ao contador dado.
*     Se o contador continha -1 - atribui 1 a ele.
*     Se o contador continha -2 - emite uma mensagem de erro acusando
*     a execu��o de um fragmento de c�digo proibido.
*
*     No m�dulo a medir devem ser inseridas chamadas para esta fun��o em
*     todos os lugares em que interessa contar conforme a estrat�gia de
*     contagem utilizada.
*
*  $EP Par�metros
*     $P NomeContador - a zero terminated string identifying the counter.
*                      Assure that names are unique, for example using
*                      a module identifying prefix for all names of
*                      a given module. Should not be NULL.
*     $P numLinha     - the line number where the call is issued.
*                      Use allways the ANSI-C standard __LINE__ constant
*                      as the actual parameter. Or use the CNT_COUNT macro.
*
*  $FV Valor retornado
*     CNT_CondRetOK  se processou normal
*     CNT_CondRetProibido se tentou contar um contador marcado proibido,
*             contagem inicializada para -2
*     CNT_CondRetNaoContador se tentou contar um contador que n�o consta
*             da tabela de contadores lida de arquivo
*     CNT_CondRetNaoInicializado o m�dulo ainda n�o foi inicializado
*
*  $EIU Interface com usu�rio pessoa
*     Sinaliza erro na sa�da se
*     Nome do contador n�o existe
*     Se for tentado contar um contador proibido
*
*     As mensagens indicam a causa e o n�mero da linha de c�digo fonte
*     que cont�m a chamada para a fun��o CNT_Contar
*
***********************************************************************/

   #define CNT_CONTAR( NomeContador )  \
           CNT_Contar( NomeContador , __LINE__ )

   CNT_tpCondRet CNT_Contar( char * NomeContador , int numLinha ) ;


/***********************************************************************
*
*  $FC Fun��o: CNT  &Parar contagem
*
*  $ED Descri��o da fun��o
*     Para a contagem. Ap�s este comando todas as chamadas da fun��o
*     CNT_Contar realizam nada.
*     A contagem somente ser� iniciada ou retomada com uma chamada
*     da fun��o CNT_IniciarContagem
*
***********************************************************************/

   void CNT_PararContagem( ) ;


/***********************************************************************
*
*  $FC Fun��o: CNT  &Verificar contagem
*
*  $ED Descri��o da fun��o
*     Verifica se existe algum contador com contagem igual a zero
*     (nunca foi contado). Emite uma mensagem para cada contador
*     zero encontrado.
*     Retorna o n�mero de erros reportados.
*       -1 se ainda n�o incializado
*
***********************************************************************/

   int CNT_VerificarContagem( ) ;


/***********************************************************************
*
*  $FC Fun��o: CNT  &Obter valor de contagem
*
*  $ED Descri��o da fun��o
*     Retorna CNT_CondRetNaoContador se o contador n�o existe
*     Obs. o valor de todas as condi��es de retorno s�o negativas.
*
***********************************************************************/

   long CNT_ObterContagem( char * NomeContador ) ;


/***********************************************************************
*
*  $FC Fun��o: CNT  &Obter n�mero de contadores
*
***********************************************************************/

   int CNT_ObterNumeroContadores( ) ;


/***********************************************************************
*
*  $FC Fun��o: CNT  &Obter total de contagem
*
***********************************************************************/

   long CNT_ObterContagemTotal( ) ;


/***********************************************************************
*
*  $FC Fun��o: CNT  &Iterador: obter contagem corrente
*
*  $ED Descri��o da fun��o
*     Retorna a contagem associada com o contador corrente do iterador
*
*     Retorna CNT_CondRetNaoIterador caso este n�o tenha sido iniciado
*     ou j� tenha percorrido todos os contadores
*
***********************************************************************/

   long CNT_ObterContagemCorrente( ) ;


/***********************************************************************
*
*  $FC Fun��o: CNT  &Iterator: obter nome de contador corrente
*
*  $FV Valor retornado
*     Retorna o ponteiro para o nome do contador.
*     Jamais altere o nome pois o contador se tornaria inacess�vel.
*     Retorna NULL se o iterador n�o est� ativo.
*
***********************************************************************/

   char * CNT_ObterContadorCorrente( ) ;


/***********************************************************************
*
*  $FC Fun��o: CNT  &Iterador: avan�ar para o pr�ximo contador
*
***********************************************************************/

   void CNT_IrProximoContador( ) ;


/***********************************************************************
*
*  $FC Fun��o: CNT  &Iterator: iniciar percorrimento da lista em ordem alfab�tica
*
*  $ED Descri��o da fun��o
*     Inicializa ou reinicializa o iterador que percorre a lista ordenada.
*     A qualquer momento no m�ximo um um iterador estar� ativo.
*
***********************************************************************/

   void CNT_IniciarIterador( ) ;


/***********************************************************************
*
*  $FC Fun��o: CNT  &Iterator: verificar se o iterador est� ativo
*
***********************************************************************/

   int CNT_EhAtivoIterador( ) ;


/***********************************************************************
*
*  $FC Fun��o: CNT  &Zerar todos contadores
*
***********************************************************************/

   CNT_tpCondRet CNT_ZerarContadores( ) ;


/***********************************************************************
*
*  $FC Fun��o: CNT  &Zerar contador dado
*
***********************************************************************/

   CNT_tpCondRet CNT_ZerarContador( char * NomeContador ) ;


/***********************************************************************
*
*  $FC Fun��o: CNT  &Verificar a estrutura dos contadores
*
*  $ED Descri��o da fun��o
*     Verifica a integridade da estrutura de dados do m�dulo contador
*
*  $FV Valor retornado
*     Retorna o n�mero de erros estruturais encontrados. Este n�mero
*     n�o corresponde � totalidade de erros, uma vez que o processamento
*     pode ser interrompido dependendo da severidade do erro encontrado.
*
***********************************************************************/

#ifdef _DEBUG

   int CNT_VerificarEstruturaContadores( ) ;

#endif

#undef CONTA_EXT

/********** Fim do m�dulo de defini��o: CNT  Contadores de passagem **********/

#else
#endif