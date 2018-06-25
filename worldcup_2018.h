/**
*@file worldcup_2018.h
*@author João Victor Cabral de Melo
*@author NightOff
*@date 18 June 2018
*@brief Jogo utilizando árvore binaria da Copa do Mundo na Rússia 2018
*/

#ifndef __WORLDCUP_H__
#define __WORLDCUP_H__


/*@brief Estrutura para a seleção na copa 
*@brief	Possuindo atributos de 0 a 100 de ataque, defesa, resistencia
*/
typedef struct {

	char *nome;		//Nome da seleção 
	int ataque;		//Nro de ataque da seleção
	int defesa;		//Nro de defesa da seleção
	int resistencia;//Nro de resistência da seleção
	int velocidade; //Nro de velocidade da seleção

}Team; //Estrutura de Team

/*@brief Estrututra para o no de árvore 
*
*/

typedef struct node {

	Team *team;			//ponteiro pra time 
	struct node *left;	//ponteiro pra esquerda 
	struct node *right;	//ponteiro pra direita

}t_node;//nomeando a estrutura como tree node

/*@brief Estrutra do tipo lista para armazenar os times
*/

typedef struct element{

	Team *team;					//ponteiro para a seleção
	struct element *proximo;	//ponteiro para o proximo
	struct element *anterior;	//ponteiro para anterior 

}l_element; //nomeando a estrutura como lista elemento

/*@brief Estrutura da lista tendo um ponteiro para o primeiro e o último 
*/

typedef struct{

	l_element *primeiro;	//ponteiro pro primeiro elemento da lista 
	l_element *ultimo;		//ponteiro pro ultimo elemento da lsita

}list;//lista


/*@brief Cria um novo no e faz o ponteiro team e left e right ficaram todos NULL */

t_node *node_create ();


/*@brief Aloca dinamicamento os atributos do time e por copia o nome da seleçao 
* @param1 _nome  @param2 _ataque  @param3 _defesa @param4 _resistencia  @param5 _velocidade
* return new_team
*/

Team *team_create(char* _nome, int _ataque, int _defesa, int _resistencia, int velocidade);

/*@brief Libera a estrutura Team liberando primeiro o nome depois o team
*@param team
*/

void team_free(Team *team);

/*@brief Aloca um no ponteiro pra raiz e retorna uma arvore de quatro niveis  
*@return root
*/

t_node* tree_create();

/*@brief Da free na arvore fazendo pos-ordem quando chega no que quer da team free depois libera no 
*@param tree
*@return void 
*/

void tree_free(t_node* tree);

/*@brief Printa a arvore em pre ordem 
*@param tree
*@return void 
*/

void tree_print_preorder(t_node* tree);


/*@brief Retorna o vencedor do jogo pelo atributo escolhido 
*@param1 team_one @param2 team_two @param3 attribute
*@return winner
*/

Team* match(Team *team_one, Team *team_two, int attribute);

/*@brief O tree_node cria nos que tiverem NULL em seus nos 
*@param root
*@return root
*/

t_node *tree_node(t_node *root);

/*@brief O height calcula a altura ou o nivel que esta o no que foi passado como referencia 
*@param root
*@return height_right ou height_left dependendo quem for maior
*/

int height(t_node *root);

/*@brief A create_worldcup(t_node *root) cria uma arvore de altura 4 ou seja 4 niveis e 31 nos 
*@param t_node* root
*@return void
*/

void create_worldcup(t_node *root);

/*@brief Afunção alloc_element(Team *new_team) cria um novo elemento para a lista e ja coloca nele um time e o ponteiros pro anterior
*e para o proximo como NULL 
*@param new_team da estrutura Team
*@return new_element da estrutura l_element 
*/

l_element *alloc_element(Team *new_team);


/*@brief A função alloc_list() aloca um ponteiro pra lista e faz lista->primeiro apontar pra null e lista->ultimo apontar pra null
*retornando lista no final
*@return new_list
*/

list *alloc_list();


/*@brief A função free_list(list *lista) vai dar free na lista inteira considerando primeiro a estrutura team depois o tipo elemento
*@param lista do tipo list
*@return void 
*/

void free_list(list *lista);

/*@brief A função insere_team_lista(Team *new_team, list *lista) tem como função receber um time e uma lista e inserir de forma
*correta o time na lista sendo ela vazia ou não
*@param1 Team *new_team @param2 list *lista
*@return void 
*/

void insere_team_lista(Team *new_team, list *lista);

/*@brief cria uma lista aleatoria com as seleçao no teams.txt usando um vetor com nro aleatorios unicos até 32 de 
* tamanho 16 e depois pega as selação pela sua linha no teams.txt de acordo com nro aleatorio no vetor 
*@return random_list 
*/

list *create_random_list();

/*@brief A função print_list(list *lista) apenas mostra a lista no terminal que foi gerada pela create_random_list()
*@param list *lista
*@return retorna time escolhido
*/

int print_list(list *lista);

/*@brief A função mostra_time_escolhido(list *lista, int nro_escolhido) anda na lista o nro de vezes do nro_escolhido
*e retorna o time daquela lista
*@param1 list *lista @param2 int nro_escolhido 
*@return time_escolhido 
*/

Team *mostra_time_escolhido(list *lista, int nro_escolhido);

/*@brief A função printa_team(Team *team) mostra na tela os atributos do time que recebe como parametro
*@return void 
*/

void printa_team(Team *team);

/*@brief a função insere_times_arvore(list *lista, t_node *root, int contador) insere os times da lista no nos folhas da arvore 
*@param1 list *lista  @param2 t_node *root @param3 int contador 
*@return void
*/

void insere_times_arvore(list *lista, t_node *root, int contador);

/*@brief A função procura_player(Team *team, t_node *root, int atributo) realiza os jogos entres os times na arvore 
*@param1 team @param2 root, @param3 atributo
*@return  int i se tiver o player jogando
*/

int procura_player(Team *team, t_node *root, int atributo);

/*@brief A funçao escolhe_atributo() retorna o valor escolhido pelo jogador 
*@return atributo_escolhido 
*/

int escolhe_atributo();

/*@brief A função make_random() retorna um valor aleatorio de 1 a 4 
*@return random
*/

int make_random();

/*@brief A função combat(Team *team_1, Team *team_2, int atributo) printa os combates entres os times na arvore 
*@param1 team_1 @param2 team_2 @param3 int atributo
*/

void combat(Team *team_1, Team *team_2, int atributo);

/*@brief A função procura_adversario(Team *player, t_node *root) mostra o adversario do player 
*@param1 player @param2 root
*@return void 
*/

void procura_adversario(Team *player, t_node *root);

/*@brief A função seu_time(Team *player, int atributo_escolhido) printa o status do seu time na rodada atual 
*@param1 player @param2 atributo_escolhido
*@return void 
*/

void seu_time(Team *player, int atributo_escolhido);

/*@brief A função continua() espera receber um valor para continuar 
*@return void 
*/

void continua();

/*@brief A função deseja_continuar() retorna o modo que quer continuar 
*@return modo
*/

int deseja_continuar(t_node *root, list *lista);

/*@brief A função player_na_arvore(t_node *root, Team* player, list* times_jogando) cria uma lista dos times que ainda estão jogando
*@param1 root @param2 player @param3 times_jogando
*@return void
*/

void player_na_arvore(t_node *root, Team* player, list* times_jogando);

/*@brief A função verifica_player_jogando(list *times_jogando, Team* player) verifica se o player esta na lista de times jogando 
*@param1 times_jogando @param2 player
*@return encontrou
*/

int verifica_player_jogando(list *times_jogando, Team* player);

/*@brief A função verifica(t_node *root, Team* player) retorna uma flag e aloca lista de times jogando chamando sua respectivas funções 
*@param1 root @param2 player
*@return encontrou
*/

int verifica(t_node *root, Team* player);

/*@brief A função menu_principal() chama toda a main denovo so que sem o display
*@return void 
*/

void menu_principal();

/*@brief A função display_entrada() mostra um display no terminal
*@return void
*/

void display_entrada();

/*@brief A função display_times() mostra o display de escolha do seu time 
*@return void 
*/

void display_times();

/*@brief A função display_vitoria() mostra na tela vitoria 
*@return void 
*/

void display_vitoria();

/*@brief A função display_derrota() mostra na tela derrota 
*@return void 
*/

void display_derrota();

/*@brief A função display_campeao() mostra na tela o campeao 
*@return void 
*/

void display_campeao();

/*@brief A função display_oitavas mostra quartas na tela 
*@return void 
*/

void display_oitavas();

/*@brief A função display_quartas mostra quartas na tela 
*@return void 
*/

void display_quartas();

/*@brief A função display_semi mostra semi na tela 
*@return void 
*/

void display_semi();

/*@brief A função display_final mostra final na tela 
*@return void 
*/

void display_final();

#endif