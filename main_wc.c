/**
*@file main_wc.c
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


int main() {

	display_entrada();

	int modo_menu;

	printf("Digite:\n");
	printf("[1]-Jogar\n");
	printf("[2]-Sair\n");

	scanf("%d", &modo_menu);

	while(modo_menu != 1 && modo_menu != 2){

		printf("Digite Novamente\n");

		scanf("%d", &modo_menu);

	}

	if(modo_menu == 2){
		exit(0);
	}


	t_node *root = tree_create();

	create_worldcup(root);

	int modo;

	list* times = create_random_list();

	int time_escolhido = print_list(times);

	Team *player = mostra_time_escolhido(times,time_escolhido);

	continua();

	insere_times_arvore(times,root,1);

	display_oitavas();

	seu_time(player,0);

	procura_adversario(player,root);

	int atributo_escolhido = escolhe_atributo();

	procura_player(player,root,atributo_escolhido);

	continua();

	display_quartas();

	if(verifica(root, player) == 1){

		seu_time(player,atributo_escolhido);

		procura_adversario(player,root);

		atributo_escolhido = escolhe_atributo();
	}


	procura_player(player,root,atributo_escolhido);

	continua();

	display_semi();

	if(verifica(root, player) == 1){

		seu_time(player, atributo_escolhido);

		procura_adversario(player, root);

		atributo_escolhido = escolhe_atributo();	
	}


	procura_player(player, root, atributo_escolhido);

	continua();

	display_final();

	if(verifica(root, player) == 1){

		seu_time(player, atributo_escolhido);

		procura_adversario(player, root);

		atributo_escolhido = escolhe_atributo();
		
	}


	procura_player(player, root, atributo_escolhido);

	if(root->team == player){

		display_campeao();

	}

	tree_free(root);

	free_list(times);

	modo = deseja_continuar(root, times);

	if(modo == -1){

		exit(0);
	}

	return 0;
}