/**
*@file worldcup_2018.c
*@author João Victor Cabral de Melo
*@author NightOff
*@date 18 June 2018
*@brief Jogo utilizando árvore binaria da Copa do Mundo na Rússia 2018
*/



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "worldcup_2018.h"
#include <unistd.h>
#include <string.h>



/*@brief cria um novo no seta seus ponteiro para NULL */

t_node *node_create (){

	t_node *new_node = malloc(sizeof(t_node));	//aloca memoria do tamanho de no

	new_node->team   = NULL;					//seta ponteiro pra team como NULL

	new_node->left   = NULL;					//seta ponteiro pra left como NULL

	new_node->right  = NULL;					//seta ponteiro pra right como NULL

	return new_node;							//retorna o novo_no

}

/*@brief Aloca dinamicamento os atributos do time e por copia o nome da seleçao 
* @param1 _nome  @param2 _ataque  @param3 _defesa @param4 _resistencia  @param5 _velocidade
* return new_team
*/

Team *team_create(char* _nome, int _ataque, int _defesa, int _resistencia, int _velocidade){

	Team *new_team = malloc(sizeof(Team));						//aloca memoria necessaria para estrutura team 

	new_team->nome = malloc(sizeof(char) * (strlen(_nome) + 1));//aloca memoria necessaria para string nome + o \0

	strcpy(new_team->nome, _nome); 								//faz copia o ponteiro 

	new_team->ataque = _ataque;									//recebe o novo ataque 

	new_team->defesa = _defesa;									//recebe nova defesa

	new_team->resistencia = _resistencia;						//recebe nova resistencia

	new_team->velocidade  = _velocidade;						//recebe nova velocidade

	return new_team;											//retorna o novo time

}

/*@brief Libera a estrutura Team liberando primeiro o nome depois o team
*@param team
*@return void
*/

void team_free(Team *team){

	free(team->nome);//libera memoria alocado para nome na memoria 
	free(team);//depois libera estrutura 

}

/*@brief Aloca um no ponteiro pra raiz e retorna uma arvore de quatro niveis  
*@return root
*/

t_node* tree_create(){

	t_node *root = node_create();	//cria um ponteiro pro no raiz para a arvore 

	return root;					//retorna ele 

}

/*@brief Da free na arvore fazendo pos-ordem quando chega no que quer da team free depois libera no 
*@param tree
*@return void 
*/

void tree_free(t_node* tree){

	if(tree != NULL){			//Condição de parada da recursão

		tree_free(tree->left);	//Faz recursão pra esquerda 

		tree_free(tree->right);	//Faz recursão pra direita

		free(tree);				//Libera o no
	}
}


/*@brief Printa a arvore em pre ordem 
*@param tree
*@return void 
*/

void tree_print_preorder(t_node* tree){

	if(tree != NULL){						//Condição de parada da recursão

		if(tree->team != NULL){

			printa_team(tree->team);		//Printa o time
		}

		tree_print_preorder(tree->left);	//Faz recursão pra esquerda 

		tree_print_preorder(tree->right);	//Faz recursão pra direita 

	}
}

/*@brief Retorna o vencedor do jogo pelo atributo escolhido 
*@param1 team_one @param2 team_two @param3 attribute
*@return winner
*/


Team* match(Team *team_one, Team *team_two, int attribute){

	Team *Winner;//Cria ponteiro pra o vencendor

	switch (attribute) {//Verifico qual dos atributos foi escolhido

		case 1 ://se for o um e o atributo de ataque 

			if(team_one->ataque >= team_two->ataque){//se o primeiro time tiver atributo maior ou igual ele e o vencedor

				Winner = team_one;//aponta pro vencedor

				return Winner;//retorna vencedor
			}
			else {

				Winner =  team_two; //então o vencedor e o time dois 

				return Winner;//retorna vencedor
			}

			break;

		case 2 ://se for 2 então o atributo escolhido foi a defesa 

			if(team_one->defesa >= team_two->defesa){//se o primeiro time tiver atributo maior ou igual ele e o vencedor

				Winner = team_one;//aponta pro vencedor

				return Winner;//retorna vencedor
			}
			else {

				Winner = team_two;//então o vencedor e o time dois 

				return Winner;//retorna vencedor
			}

			break;

		case 3 ://Se for 3 então o atributo escolhido foi resitência 

			if(team_one->resistencia >= team_two->resistencia){//se o primeiro time tiver atributo maior ou igual ele e o vencedor

				Winner = team_one;//aponta pro vencedor

				return Winner;//retorna vencedor
			}
			else {

				Winner = team_two;//aponta pro vencedor

				return Winner;//retorna vencedor
			}

			break;

		case 4 ://Se for 4 então o atributo escolhido foi velocidade

			if(team_one->velocidade >= team_two->velocidade){//se o primeiro time tiver atributo maior ou igual ele e o vencedor

				Winner = team_one;//aponta pro vencedor

				return Winner;//retorna vencedor

			}
			else {

				Winner = team_two;//aponta pro vencedor

				return Winner;//retorna vencedor
			}

			break;
	}
}


/*@brief O tree_node cria nos que tiverem NULL em seus nos 
*@param root
*@return root
*/

t_node *tree_node(t_node *root){

	if(root == NULL){							//condiçao para criar no se o no atual tiver endereço igual a NULL

		return node_create();					//retorna o no criado

	}
	else {

		root->left  = tree_node(root->left);	//faz recursão em pre ordem da arvore 

		root->right = tree_node(root->right);	//faz recursão em pre ordem da arvore 

	}

	return root;								//retorna a raiz

}

/*@brief O height calcula a altura ou o nivel que esta o no que foi passado como referencia 
*@param root
*@return height_right ou height_left dependendo quem for maior
*/

int height(t_node *root){

	if(root == NULL){							//condição de parada da recursão para retornar 0 de altura se o no atual for null

		return 0;

	}

	int height_left  = height(root->left);		//faz recursão pra esquerda pre ordem

	int height_right = height(root->right);		//faz recursão pra direita pre ordem

	if(height_left >= height_right){			//verifico qual altura e maior nessa recursão retorna e soma mais um nela 

		return height_left + 1;					//nesse caso que se altura da esquerda for igual ou maior a da direita então soma mais um a ela 
	}
	else {

		return height_right + 1;				//caso contrario soma mais um na altura da direita 
	}
}

/*@brief A função create_worldcup(t_node *root) cria uma arvore de altura 4 ou seja 4 niveis e 31 nos 
*@param t_node* root
*@return void
*/

void create_worldcup(t_node *root){

	int h = 0;				//seta a altura ja como zero

	while(h <= 4){			//equanto a altura for menor ou igual a quatro continua criando nos 

		tree_node(root);	//cria no tanto da direita como da esquerda 

		h = height(root);	// verifica a altura atual da raiz pra ver se não chegou na altura pedida que é 4 

	}
}


/*@brief A função alloc_element(Team *new_team) cria um novo elemento para a lista e ja coloca nele um time e o ponteiros pro anterior
*e para o proximo como NULL 
*@param new_team da estrutura Team
*@return new_element da estrutura l_element 
*/

l_element *alloc_element(Team *new_team){

	l_element *new_element = malloc(sizeof(l_element));		//aloca o tamanho de l_elemento pois ele vai pra lista

	new_element->team      = new_team;						//coloca ja o novo elemento em team 

	new_element->anterior  = NULL;							//aponto seu anterior pra NULL

	new_element->proximo   = NULL;							//aponto o proximo como NULL

	return new_element;										//retorno elemento

}

/*@brief A função alloc_list() aloca um ponteiro pra lista e faz lista->primeiro apontar pra null e lista->ultimo apontar pra null
*retornando lista no final
*@return new_list
*/


list *alloc_list(){

	list *new_list     = malloc(sizeof(list));	//aloca memoria pra nova lista 

	new_list->primeiro = NULL;					//seta o primeiro como NULL

	new_list->ultimo   = NULL;					//seta o ultimo como NULL

	return new_list;							//retorna nova lista

}

/*@brief A função free_list(list *lista) vai dar free na lista inteira considerando primeiro a estrutura team depois o tipo elemento
*@param lista do tipo list
*@return void 
*/

void free_list(list *lista){

	l_element* aux = lista->primeiro;					//cria um ponteiro auxiliar para o lista->primeiro

	while(aux != NULL){									//enquanto não chegar no final da lista faça

		lista->primeiro = lista->primeiro->proximo;		//atualiza lista->primeiro 

		team_free(aux->team);							//da free na estrutura team apontado por aux 

		free(aux);										//da free em aux 

		aux             = lista->primeiro;				//faz aux apontar pro novo lista->primeiro
	}

	free(lista);										//da free no ponteiro de lista 
}


/*@brief A função insere_team_lista(Team *new_team, list *lista) tem como função receber um time e uma lista e inserir de forma
*correta o time na lista sendo ela vazia ou não
*@param1 Team *new_team @param2 list *lista
*@return void 
*/

void insere_team_lista(Team *new_team, list *lista){

	if(lista->primeiro == NULL && lista->ultimo == NULL){		//verifica se a lista esta vazia 

		l_element *new_element = alloc_element(new_team);		//se estiver aloca novo elemento

		lista->primeiro        = new_element;					//coloca ele tanto no primeiro como no ultimo elemento

		lista->ultimo          = new_element;					//coloca ele tanto no primeiro como no ultimo elemento
	}

	else {

		l_element *new_element = alloc_element(new_team);		//aloco novo elemento 

		lista->ultimo->proximo = new_element;					//proximo do ultimo e apontado para novo elemento

		new_element->anterior  = lista->ultimo;					//anterior do novo elemento aponta pro ultimo

		lista->ultimo          = new_element;					//o o novo elemento se torna o ultimo da lista

		lista->ultimo->proximo = NULL;							//o proximo do ultimo aponta pra NULL
	}
}

/*@brief cria uma lista aleatoria com as seleçao no teams.txt usando um vetor com nro aleatorios unicos até 32 de 
* tamanho 16 e depois pega as selação pela sua linha no teams.txt de acordo com nro aleatorio no vetor 
*@return random_list 
*/

list *create_random_list(){

	FILE *teams;																				//ponteiro pro arquivo teams.txt

	char selecao[10000];																		//string pro nome da seleção
	int ataque, defesa, resistencia, velocidade;												//atributos da seleção

	teams             = fopen("teams.txt", "r");												//abre o arquivo teams.txt para leitura

	list *random_list = alloc_list();															//aloca uma nova lista

	if(teams == NULL){																			//Verifica se conseguiu abrir o arquivo teams.txt 

		printf("Arquivo dos times da copa inexistente T-T\n");

		exit -1;																				//Se não para de executar a função
	} 

	int i, j = 0, random, flag;																	//seta o valor dos indices, e a flag e declara a variavel que segura o valor randomico 

	struct timespec seed;																		//Estrutura da time.h para setar a semente 

	int vet_de_nros_randoms[16];																//vetor que vai segurar 16 nros randomicos de ate 32 distintos

	while(j < 16){																				//Enquanto não prencher o vetor 

		clock_gettime(CLOCK_REALTIME, &seed);													//Seta a semente em nanosegundos

		srand(seed.tv_nsec);																	//Idem	

		random = rand()%32 + 1;																	//Cria nro randomico de 0 até 32

		for(i = 0; i < 16; i++){																//Verifica se o nro criado não é igual a um no vetor

			if(vet_de_nros_randoms[i] == random){												//Se for seta a flag 

				flag = 1;																		//Flag setada

			}
		}

		if(flag != 1){																			//Se a flag não tiver setada então 

			vet_de_nros_randoms[j] = random;													//Significa que o nro aleatorio não é repetido então coloca no vetor 

			j++;																				//Acrescenta no indice
		}

		flag = 0;																				//Seta a flag pra falso denovo
	}

	int m = 0;																					//Criamos um novo indice

	while(m < 16){																				//Enquanto indice não chegar no final do vetor faça 

		for(i = 0; i < vet_de_nros_randoms[m];i++){												//Da scan na lista o nro de vezes que tem o nro aleatorio no vetor o que acaba chegando na linha da seleção desejada

			fscanf(teams,"%[^',']s",selecao);													//Dou scan ate a ',' em formato de string
			fgetc(teams);																		//Pego a virgula depois				
			fscanf(teams,"%d, %d, %d, %d", &ataque, &defesa, &resistencia, &velocidade); 		//Dou scan nos atributos
		}

		Team* new_team = team_create(selecao, ataque, defesa, resistencia, velocidade);			//aloco um novo time e passos os atributos scaneados

		insere_team_lista(new_team, random_list);												//Insiro ele na lista 

		rewind(teams);																			//Voltou meu ponteiro pro inicio do arquivo

		m++;																					//E acrescento mais um no indice
	}

	fclose(teams);																				//Fecha o arquivo e daa free no ponteiro teams

	return random_list;																			//Retornando a lista gerado no final

}

/*@brief A função print_list(list *lista) apenas mostra a lista no terminal que foi gerada pela create_random_list()
*@param list *lista
*@return time_escolhido
*/ 

int print_list(list *lista){

	int time_escolhido;					//Declara variavel de retorno 

	display_times();

	sleep(1);		

	l_element *aux = lista->primeiro;								//cria um ponteiro auxiliar para apontar para lista

	int contador = 1, random; 

	struct timespec seed;

	while(aux != NULL){												//enquanto não chegar no fim da lista faça
 

		clock_gettime(CLOCK_REALTIME, &seed);						//Seta a semente em nanosegundos

		srand(seed.tv_nsec);

		random = rand()%4 +1;

		printf("\n\nTime %d: \n", contador);

		switch(random){

			case 1:

				printf("Ataque: %d ",aux->team->ataque);

				break;

			default :

				printf("Ataque: ?? ");

				break;
		}

		switch(random){

			case 2:

				printf("Defesa: %d ",aux->team->defesa);

				break;

			default :

				printf("Defesa: ?? ");

				break;
		}

		switch(random){

			case 3:

				printf("Resistencia: %d ", aux->team->resistencia);

				break;

			default :

				printf("Resistencia: ?? ");

				break;
		}

		switch(random){

			case 4:

				printf("Velocidade: %d\n", aux->team->velocidade);

				break;

			default :

				printf("Velocidade: ??\n");

				break;
		}


		aux = aux->proximo;											//vai para o proximo elemento da lista

		contador++;
	}

	printf("\n\n\n");

	scanf("%d", &time_escolhido);

	return time_escolhido;

}

/*@brief A função mostra_time_escolhido(list *lista, int nro_escolhido) anda na lista o nro de vezes do nro_escolhido
*e retorna o time daquela lista
*@param1 list *lista @param2 int nro_escolhido 
*@return time_escolhido 
*/

Team *mostra_time_escolhido(list *lista, int nro_escolhido){

	l_element *aux = lista->primeiro;		//aponta um ponteiro auxiliar para o primeiro da lista

	Team *time_escolhido;					//ponteiro para o time escolhido

	int contador = 1;						//contador setado pra 1

	while(nro_escolhido > contador){		//enquanto o contador nao chegar no nro_escolhido pelo player 

		aux  = aux->proximo;				//anda na lista

		contador++;							//soma o contador 
	}

	time_escolhido = aux->team;				//time_escolhido recebe time apontado pelo auxiliar na lista

	printa_team(time_escolhido);			//printa os atributos do time escolhido

	return time_escolhido;					//retorna o ponteiro do tipo Team 
}

/*@brief A função printa_team(Team *team) mostra na tela os atributos do time que recebe como parametro
*@return void 
*/

void printa_team(Team *team){

	printf("\n\n\n");
	printf("Seu Time        : %s   \n", team->nome);
	printf("1)Ataque        : %d   \n", team->ataque);
	printf("2)Defesa        : %d   \n", team->defesa);
	printf("3)Resistencia   : %d   \n", team->resistencia);
	printf("4)Velocidade    : %d   \n", team->velocidade);	
	printf("\n\n\n");

}

/*@brief a função insere_times_arvore(list *lista, t_node *root, int contador) insere os times da lista no nos folhas da arvore 
*@param1 list *lista  @param2 t_node *root @param3 int contador 
*@return void
*/

void insere_times_arvore(list *lista, t_node *root, int contador){

	int i;																//seta o contador

	if(root->left != NULL && root->right != NULL){						//se seus filhos da esquerda e direita for diferente de NULL então não chegouo na folha

		insere_times_arvore(lista, root->left, contador*2);				//faz recursão pra esquerda

		insere_times_arvore(lista, root->right, contador*2 +1);			//faz recursão pra direita
		
	}
	else {

		contador -= 16;													//contador menos o numero de recursões

		l_element *aux = lista->primeiro;								//aponta pro primeiro

		if(contador == 0){

			root->team = lista->primeiro->team;							//se o contador for zero então insere no primeiro

		}
		else {															//senão vamos andar ate achar time passado pelo contador

			i = contador;												//seta o valor pra andar na lista

			while(i > 0){												//equanto não chegar no numero do time anda na lista

				aux = aux->proximo;										//anda na lista

				i--;													//diminui no valor

			}

			root->team = aux->team;										//no recebe time

		}

	}
}

/*@brief A função procura_player(Team *team, t_node *root, int atributo) realiza os jogos entres os times na arvore 
*@param1 team @param2 root, @param3 atributo
*@return  int i se tiver o player jogando
*/

int procura_player(Team *team, t_node *root, int atributo){

	if(root != NULL && root->team == NULL){												//Enquanto não chegar no pai dos nos que tem times

		if(root->left->team != NULL && root->right->team != NULL){						//Verifica se o no atual tem times no filho da esquerda e da direita

			if(root->right->team == team){												//Se o jogador estiver no filho da direita

				Team *Winner = match(root->left->team, team, atributo);					//retorna o ponteiro do vencedor do jogo

				combat(root->left->team, team, atributo);								//printa o jogo

				if(Winner == team){

					display_vitoria();

				}
				else {

					display_derrota();
				}

				root->team = Winner;													//no pai recebe o vencedor

				return 1;

			}
			else if(root->left->team == team){											//Se o jogador estiver no filho da esquerda

				Team *Winner = match(team, root->right->team, atributo);				//retorna o ponteiro do vencedor do jogo

				combat(team, root->right->team, atributo);								//printa o jogo

				if(Winner == team){

					display_vitoria();
				}
				else {

					display_derrota();
				}

				root->team = Winner;													//no pai recebe o vencedor

				return 1;
			}
			else {																		//Caso que são dois bots lutando

				int atributo = make_random();											//faz o random

				Team *Winner = match(root->left->team, root->right->team, atributo);	//retorna o ponteiro vencedor do jogo

				combat(root->left->team, root->right->team, atributo);					//printa jogo

				root->team = Winner;													//no pai recebe o vencedor
			}
			
		}
		procura_player(team,root->left,atributo);										//faz recursão esquerda 

		procura_player(team,root->right,atributo);										//faz recursão direita										

	}
}


/*@brief A funçao escolhe_atributo() retorna o valor escolhido pelo jogador 
*@return atributo_escolhido 
*/

int escolhe_atributo(){

	int atributo_escolhido;

	printf("Escolha seu atributo : \n");


	scanf("%d", &atributo_escolhido);		//recebe atributo

	while(atributo_escolhido != 1 && atributo_escolhido != 2 && atributo_escolhido != 3 && atributo_escolhido != 4){//condição de atributo valido

		printf("Atributo Invalido \n");

		printf("Digite um novo atributo entre 1 a 4 \n");

		scanf("%d", &atributo_escolhido);

	}

	return atributo_escolhido;				//retorna atributo
}

/*@brief A função make_random() retorna um valor aleatorio de 1 a 4 
*@return random
*/

int make_random(){
	
	struct timespec seed;

	clock_gettime(CLOCK_REALTIME, &seed);						//Seta a semente em nanosegundos

	srand(seed.tv_nsec);

	int random = rand()%4 +1;

	return random;

}

/*@brief A função combat(Team *team_1, Team *team_2, int atributo) printa os combates entres os times na arvore 
*@param1 team_1 @param2 team_2 @param3 int atributo
*/

void combat(Team *team_1, Team *team_2, int atributo){

	switch(atributo){				//printa atributos

		case 1:

			printf("%s (%d Ataque) vs %s (%d Ataque)\n\n", team_1->nome, team_1->ataque, team_2->nome, team_2->ataque);

			break;

		case 2:

			printf("%s (%d Defesa) vs %s (%d Defesa)\n\n", team_1->nome, team_1->defesa, team_2->nome, team_2->defesa);

			break;

		case 3:

			printf("%s (%d Resistencia) vs %s (%d Resistencia)\n\n", team_1->nome, team_1->resistencia, team_2->nome, team_2->resistencia);

			break;

		case 4:

			printf("%s (%d Velocidade) vs %s (%d Velocidade)\n\n", team_1->nome, team_1->velocidade, team_2->nome, team_2->velocidade);

			break;
	}
}

/*@brief A função procura_adversario(Team *player, t_node *root) mostra o adversario do player 
*@param1 player @param2 root
*@return void 
*/

void procura_adversario(Team *player, t_node *root){

	if(root != NULL && root->team == NULL){											//faço recursão enquanto achar nos NULL com filhos NULLS

		if(root->left->team != NULL && root->right->team != NULL){					//Verifico se tem times no nos filhos

			if(root->left->team == player){											//Verifico se e o player esta no no da esquerda

				printf("\n\nSeu adversario e : %s \n", root->right->team->nome);	//Mostra adversario

			}

			else if(root->right->team == player){

				printf("\n\nSeu adversario e : %s \n", root->left->team->nome);		//Mostra adversario

			}

		}

		procura_adversario(player, root->left);										//faz recursão

		procura_adversario(player, root->right);									//faz recursão
	}
}

/*@brief A função seu_time(Team *player, int atributo_escolhido) printa o status do seu time na rodada atual 
*@param1 player @param2 atributo_escolhido
*@return void 
*/

void seu_time(Team *player, int atributo_escolhido){

	printf("\n\nSeu time: %s \n", player->nome);

	switch(atributo_escolhido){							//Faz switch em cada atributo sendo por padrão printa todos eles se receber o atributo anteriormente não printa 

		case 1:

			printf("X)XX          : XX\n");

			break;

		default:

			printf("1)Ataque      : %d\n", player->ataque);

			break;
	}

	switch(atributo_escolhido){
		
		case 2:

			printf("X)XX          : XX\n");

			break;

		default:

			printf("2)Defesa      : %d\n", player->defesa);

			break;
	}

	switch(atributo_escolhido){

		case 3:

			printf("X)XX          : XX\n");

			break;

		default:

			printf("3)Resistencia : %d\n", player->resistencia);

			break;

	}

	switch(atributo_escolhido){

		case 4:

			printf("X)XX          : XX\n");

			break;

		default:

			printf("4)Velocidade  : %d\n", player->velocidade);

			break;
	}
}

/*@brief A função continua() espera receber um valor para continuar 
*@return void 
*/

void continua(){

	setbuf(stdin,NULL);

	printf("\n\n");
	printf("Digite qualquer tecla para continuar:\n");
	getchar();

}

/*@brief A função deseja_continuar() retorna o modo que quer continuar 
*@return modo
*/


int deseja_continuar(t_node *root, list *times){


	int modo;
	printf("\n\n[1] Voltar ao menu principal\n");
	printf("[2] Sair\n");

	scanf("%d", &modo);

	while(modo != 1 && modo != 2){					//Verifica se foi digitado o modo correto
		printf("Modo Invalido\n");
		printf("Digite modo novamente\n");
		scanf("%d", &modo);
	}

	if(modo == 1){

		menu_principal();

	}
	else {

		return -1;

	}

}

/*@brief A função player_na_arvore(t_node *root, Team* player, list* times_jogando) cria uma lista dos times que ainda estão jogando
*@param1 root @param2 player @param3 times_jogando
*@return void
*/

void player_na_arvore(t_node *root, Team* player, list* times_jogando){

	if(root != NULL && root->team == NULL){								//Faz recursão na arvore ate o pai 

		if(root->left->team != NULL && root->right->team != NULL){		//verifica se ele tem nos filhos com times não nulos

			insere_team_lista(root->left->team,times_jogando);			//Se tiver inseri eles na lista

			insere_team_lista(root->right->team,times_jogando);			//Se tiver inseri eles na lista

		}

		player_na_arvore(root->left, player, times_jogando);			//Anda na arvore 
		player_na_arvore(root->right, player, times_jogando);
	}
}

/*@brief A função verifica_player_jogando(list *times_jogando, Team* player) verifica se o player esta na lista de times jogando 
*@param1 times_jogando @param2 player
*@return encontrou
*/

int verifica_player_jogando(list *times_jogando, Team* player){

	l_element *aux = times_jogando->primeiro;						//recebe ponteiro pro inicio da insere_team_lista

	int encontrou = 0;												//seta flag

	while(aux != NULL && encontrou != 1){							//anda na lista

		if(aux->team == player){									//se achar seta a flag pra True

			encontrou = 1;

		}

		aux = aux->proximo;											     //anda na lista

	}


	l_element* aux2 = times_jogando->primeiro;							//cria um ponteiro auxiliar para o lista->primeiro

	while(aux2 != NULL){												//enquanto não chegar no final da lista faça

		times_jogando->primeiro = times_jogando->primeiro->proximo;		//atualiza lista->primeiro  

		free(aux2);														//da free em aux 

		aux2                    = times_jogando->primeiro;				//faz aux apontar pro novo lista->primeiro
	}

	free(times_jogando);


	return encontrou;													//return flag
}

/*@brief A função verifica(t_node *root, Team* player) retorna uma flag e aloca lista de times jogando chamando sua respectivas funções 
*@param1 root @param2 player
*@return encontrou
*/


int verifica(t_node *root, Team* player){

	list* times_jogando = alloc_list();									//aloca nova lista

	int encontrou;														//flag

	player_na_arvore(root, player, times_jogando);						//chama pra inserir 

	encontrou = verifica_player_jogando(times_jogando, player);			//chama função que verifica na lista

	return encontrou;													//retorna flag
}


/*@brief A função menu_principal() chama toda a main denovo so que sem o display
*@return void 
*/


void menu_principal(){

	t_node *root = tree_create();									//cria raiz

	create_worldcup(root);											//cria um torneio de 4 niveis

	int modo;														//variavel do modo escolhido 

	list* times = create_random_list();								//cria lista randomica de times

	int time_escolhido = print_list(times);							//printa a lista com os atributos encorbertos

	Team *player = mostra_time_escolhido(times,time_escolhido);		//mostra seu time escolhido

	continua();														//espera confirmação

	insere_times_arvore(times,root,1);								//insere nas folhas

	display_oitavas();						

	seu_time(player,0);												//Printa o estado atual de seu time

	procura_adversario(player,root);								//mostra seu adversario nessa fase

	int atributo_escolhido = escolhe_atributo();					//pega atributo escolhido

	procura_player(player,root,atributo_escolhido);					//faz o jogos da copa do mundo acontecer

	continua();														//espera a confirmação

	display_quartas();						

	if(verifica(root, player) == 1){								//verifica se o player ainda esta na copa 

		seu_time(player,atributo_escolhido);						//se estiver printa estado atual do seu time

		procura_adversario(player,root);							//mostra seu novo adversario

		atributo_escolhido = escolhe_atributo();					//pega atributo escolhido
	}


	procura_player(player,root,atributo_escolhido);					//faz os jogas da copa acontecer

	continua();														//espera confirmação

	display_semi();

	if(verifica(root, player) == 1){								//verifica se o player ainda esta na copa

		seu_time(player, atributo_escolhido);						//se estiver printa estado atual de seu time

		procura_adversario(player, root);							//mostra seu adversario nessa fase

		atributo_escolhido = escolhe_atributo();					//pega seu atributo
	}


	procura_player(player, root, atributo_escolhido);				//faz a copa acontecer

	continua();														//espera confimarção

	display_final();

	if(verifica(root, player) == 1){								//verifica se o time ainda esta na copa
		
		seu_time(player, atributo_escolhido);						//printa estado atual do time 

		procura_adversario(player, root);							//procura seu adversario

		atributo_escolhido = escolhe_atributo();					//pega seu atributo
		
	}


	procura_player(player, root, atributo_escolhido);				//faz o jogo acontecer

	if(root->team == player){										//se o jogador estiver na raiz da arvore então ele ganhou

		display_campeao();

	}

	tree_free(root);												//da free na arvore 

	free_list(times);												//da free na lista

	modo = deseja_continuar(root, times);							//pergunta se deseja continuar

	if(modo == -1){													//se o modo for 2-Sair então da exit

		exit(0);
	}

}

/*@brief A função display_entrada() mostra um display no terminal
*@return void
*/

void display_entrada(){

	system("clear");											//limpa a tela para o display

	char matrix[6][126];										//matriz do display

	int i,j;													//linhas e colunas

	FILE *display_entrada;										//ponteiro para o display

	display_entrada = fopen("display_entrada.txt", "r");		//abra o arquivo

	while(!feof(display_entrada)){								//leio do arquivo a matriz

		for(i = 0; i < 6;i++){

			for(j = 0; j < 126;j++){

				fscanf(display_entrada, "%c", &matrix[i][j]);
			}
		}
	}

	for(i = 0; i < 6;i++){										//mostro matriz na tela

		for(j = 0; j < 126;j++){

			printf("%c", matrix[i][j]);

		}
	}

	printf("\n\n\n\n");

	fclose(display_entrada);									//fecho arquivo
}

/*@brief A função display_times() mostra o display de escolha do seu time 
*@return void 
*/

void display_times(){

	system("clear");

	char matrix[6][77];

	int i, j;

	FILE *display_times;

	display_times = fopen("display_escolha.txt", "r");

	while(!feof(display_times)){

		for(i = 0; i < 6; i++){

			for(j = 0; j < 77; j++){

				fscanf(display_times, "%c", &matrix[i][j]);

			}
		}
	}

	for(i = 0; i < 6; i++){

		for(j = 0; j < 77; j++){

			printf("%c", matrix[i][j]);
		}
	}

	printf("\n\n\n");

	fclose(display_times);
}

/*@brief A função display_vitoria() mostra na tela vitoria 
*@return void 
*/

void display_vitoria(){

	char matrix[9][69];

	int i, j;

	FILE *display_vitoria;

	display_vitoria = fopen("display_vitoria.txt", "r");

	while(!feof(display_vitoria)){

		for(i = 0; i < 9; i++){

			for(j = 0; j < 69; j++){

				fscanf(display_vitoria, "%c", &matrix[i][j]);

			}
		}
	}

	for(i = 0; i < 9; i++){

		for(j = 0; j < 69; j++){

			printf("%c", matrix[i][j]);
		}
	}

	printf("\n\n\n");

	fclose(display_vitoria);

}

/*@brief A função display_derrota() mostra na tela derrota 
*@return void 
*/

void display_derrota(){

	char matrix[9][76];

	int i, j;

	FILE *display_derrota;

	display_derrota = fopen("display_derrota.txt", "r");

	while(!feof(display_derrota)){

		for(i = 0; i < 9; i++){

			for(j = 0; j < 76; j++){

				fscanf(display_derrota, "%c", &matrix[i][j]);

			}
		}
	}

	for(i = 0; i < 9; i++){

		for(j = 0; j < 76; j++){

			printf("%c", matrix[i][j]);
		}
	}

	printf("\n\n\n");

	fclose(display_derrota);
}

/*@brief A função display_campeao() mostra na tela o campeao 
*@return void 
*/

void display_campeao(){

	system("clear");

	char matrix[9][80];

	int i, j;

	FILE *display_campeao;

	display_campeao = fopen("display_campeao.txt", "r");

	while(!feof(display_campeao)){

		for(i = 0; i < 9; i++){

			for(j = 0; j < 80; j++){

				fscanf(display_campeao, "%c", &matrix[i][j]);

			}
		}
	}

	for(i = 0; i < 9; i++){

		for(j = 0; j < 80; j++){

			printf("%c", matrix[i][j]);
		}
	}

	printf("\n\n\n");

	fclose(display_campeao);
}

/*@brief A função display_oitavas mostra oitavas na tela 
*@return void 
*/

void display_oitavas(){

	system("clear");

	char matrix[6][71];

	int i, j;

	FILE *display_oitavas;

	display_oitavas = fopen("display_oitavas.txt", "r");

	while(!feof(display_oitavas)){

		for(i = 0; i < 6; i++){

			for(j = 0; j < 71; j++){

				fscanf(display_oitavas, "%c", &matrix[i][j]);

			}
		}
	}

	for(i = 0; i < 6; i++){

		for(j = 0; j < 71; j++){

			printf("%c", matrix[i][j]);
		}
	}

	printf("\n\n\n");

	fclose(display_oitavas);

}
/*@brief A função display_quartas mostra quartas na tela 
*@return void 
*/

void display_quartas(){

	system("clear");

	char matrix[6][76];

	int i, j;

	FILE *display_quartas;

	display_quartas = fopen("display_quartas.txt", "r");

	while(!feof(display_quartas)){

		for(i = 0; i < 6; i++){

			for(j = 0; j < 76; j++){

				fscanf(display_quartas, "%c", &matrix[i][j]);

			}
		}
	}

	for(i = 0; i < 6; i++){

		for(j = 0; j < 76; j++){

			printf("%c", matrix[i][j]);
		}
	}

	printf("\n\n\n");

	fclose(display_quartas);
}

/*@brief A função display_semi mostra semi na tela 
*@return void 
*/

void display_semi(){

	system("clear");

	char matrix[6][43];

	int i, j;

	FILE *display_semi;

	display_semi = fopen("display_semi.txt", "r");

	while(!feof(display_semi)){

		for(i = 0; i < 6; i++){

			for(j = 0; j < 43; j++){

				fscanf(display_semi, "%c", &matrix[i][j]);

			}
		}
	}

	for(i = 0; i < 6; i++){

		for(j = 0; j < 43; j++){

			printf("%c", matrix[i][j]);
		}
	}

	printf("\n\n\n");

	fclose(display_semi);
}

/*@brief A função display_final mostra final na tela 
*@return void 
*/

void display_final(){

	system("clear");

	char matrix[6][51];

	int i, j;

	FILE *display_final;

	display_final = fopen("display_final.txt", "r");

	while(!feof(display_final)){

		for(i = 0; i < 6; i++){

			for(j = 0; j < 51; j++){

				fscanf(display_final, "%c", &matrix[i][j]);

			}
		}
	}

	for(i = 0; i < 6; i++){

		for(j = 0; j < 51; j++){

			printf("%c", matrix[i][j]);
		}
	}

	printf("\n\n\n");

	fclose(display_final);
}