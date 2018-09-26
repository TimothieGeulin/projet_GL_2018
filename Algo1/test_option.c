// gcc test_option.c -std=c99 -o test_option


/* -----------------------------------------------------------------------------------------*/
/* TODO : 	1) Problème quand on affecte un étudiant à une option, 
				remove_when_assigned est censé passé


			2) Mettre en place une lecture de fichier .txt sous un format précis contenant
				nombre d'options n 
				effectif possible pour l'option 1
				effectif possible pour l'option 2
				...
				effectif possible pour l'option n
				nombre d'étudiants x
				idEtudiant1 creditOption1 creditOption2 ... creditOption n
				idEtudiantx creditOption1 creditOption2 ... creditOption n

			3) Sortir tous les résultats d'affectations sur un fichier .txt de sortie contenant :
			- id de l'étudiant + sa répartition de crédits sur les différentes options originales + son affectation finale
			- Calculer le % d'étudiant qui ont leur 1er choix / 2èeme etc...

			4) Faire un .h et un makefile ET SURTOUT UTILISER GIT quand j'aurais pas la flemme


/* -----------------------------------------------------------------------------------------*/		

#include "test_option.h"

Etudiant option_list[Nb_options][Nb_etu];			//La liste de tout les étudiants pour chaque Options
Etudiant copy_option_list[Nb_options][Nb_etu];		//Copie de option_list pour le affectations
Etudiant *listeEtu;
LISTE LL_option_list[Nb_options];
//int effectif[Nb_options] = {30, 28, 32, 27, 31}; 	//	effectif max pour les options
int effectif[Nb_options] = {6,4,3,5,4};

/*
void fill_option_list(Etudiant Tab[Nb_etu]){
	//printf("Start %s\n", __func__);
	for(int i=0; i<Nb_options; i++){
		for(int j=0; j<Nb_etu; j++){
			option_list[i][j] = Tab[j];
		}
	} 
	//printf("End %s\n", __func__);
}*/


void array_to_LL(){
	//printf("Start %s\n", __func__);

	for(int index_option = 0; index_option < Nb_options; index_option++){
		LISTE temp = malloc(sizeof(LL_etudiant));
		assert(temp);

		temp->etudiant = option_list[index_option][0];
		temp->suiv = NULL;
		LL_option_list[index_option] = temp;

		for(int i=1; i<Nb_etu; i++){
			LISTE temp2 = malloc(sizeof(LL_etudiant));
			assert(temp2);

			temp->suiv = temp2;
			temp2->etudiant = option_list[index_option][i];
			temp2->suiv = NULL;
			temp=temp2;
		}	
	}
	//printf("End %s\n", __func__);
}

void print_LL(){
	//printf("Start %s\n", __func__);
	for(int i=0; i<Nb_options; i++){
		printf("\n-------------\nOPTION %d\n", i);
		if(LL_option_list[i] == NULL){
			exit(0);
		}

		LISTE p = LL_option_list[i];

		while(p != NULL){
			printf("Etudiant %d | Credit : %d\n", p->etudiant.idEtudiant, p->etudiant.creditO[i]);
			p = p->suiv;
		}
	}
	//printf("End %s\n", __func__);
}

void remove_when_assigned(Etudiant current){	/*Enlève un étudiant des autres liste quand on lui affecte une option*/
	//printf("Start %s\n", __func__);
	printf("AVANT SUPRESSION : ETUDIANT %d \n",current.idEtudiant);
	print_LL();
	int check_first = 0;

	for(int index_option=0; index_option<Nb_options; index_option++){
		LISTE old;
		LISTE tmp = LL_option_list[index_option];
		if(tmp == NULL){
			exit(0);
		}
		
		while(tmp != NULL){
			if(tmp->etudiant.idEtudiant == current.idEtudiant){
				if(check_first == 0){
					LL_option_list[index_option] = LL_option_list[index_option]->suiv; 
				}
				else{
					old->suiv=tmp->suiv;
				}
			}
			if(check_first == 0){
				check_first ++;
			}
			old = tmp;
			tmp = tmp->suiv;
		}
	}	
		printf("-----------\nAPRES SUPRESSION\n");
		print_LL();
		
				
				// if(copy_option_list[i][j].idEtudiant == current.idEtudiant){
				// 	indice = j;
				// 	break;
				// }
				// Etudiant tmp = copy_option_list[i][indice];
				// if(indice != -1){
				// 	for(int j=indice; j<Nb_etu; j++){
				// 		copy_option_list[i][j] = copy_option_list[i][j+1];
				// 	}
				// 	copy_option_list[i][Nb_etu-1] = test;
				// }
	//printf("End %s\n", __func__);
}
 
/*	Regarde parmis les crédits déposé dans quelle options sera l'étudiant */
// int _assignement(int choice[Nb_options], Etudiant current, int cursor){	/* cursor pour regarder un choix x si un autre ne peut pas etre satisfait */
// 	//printf("Start %s\n", __func__);
// 	if (cursor > Nb_options){	/*On peut le caser nulle part || on reteste plus tard quand des places sont libérer ailleurs ? */
// 		return -1; 
// 	}

// 	int option = choice[cursor];
// 	for(int i=0; i<effectif[cursor]; i++){
// 		if(option_list[option][i].idEtudiant == current.idEtudiant){	/* l'étudiant est accepté pour l'option */
// 			effectif[cursor]--;		/* Affecté donc une place de moins dans l'option */
// 			remove_when_assigned(current);
// 			return option;
// 		}
// 	}
// 	return _assignement(choice, current, cursor+1);
// 	//printf("End %s\n", __func__);
// }


int is_in_array(int tab[Nb_options], int check){
	//printf("Start %s\n", __func__);
	for(int i=0; i<Nb_options; i++){
		if (tab[i] == check)
		return 1;
	}
	return 0;
	//printf("End %s\n", __func__);
}

/* Affecte un étudiant dans une matière selon ses choix */
/*int affect(Etudiant current){
	//printf("Start %s\n", __func__);
	int choice[Nb_options];
	int best_choice;
	int best_index;


	for(int i=0; i<Nb_options; i++){
		choice[i] = -1;
	}

	for(int i=0; i<Nb_options; i++){	// Permet d'avoir les options par ordre de demande dans choice[]
		best_choice = -1;
		for(int j=0; j<Nb_options; j++){
			if(best_choice < current.creditO[j]){
				if(!is_in_array(choice, j)){
					best_choice = current.creditO[j];
					best_index = j;
				}
			}
		}
		choice[i]=best_index;
	}

	return _assignement(choice, current, 0);	
	//printf("End %s\n", __func__);	
}*/

/*Affecte tous les étudiants a une matière */
/*void affect_all(){
	//printf("Start %s\n", __func__);
	for (int i = 0; i < Nb_etu; i++)		{
		listeEtu[i].affectation = affect(listeEtu[i]);
	}
	//printf("End %s\n", __func__);
}*/

void print_choice(){
	//for(int i = 0; i<Nb_options; i++){
		for(int i = 0; i<Nb_etu; i++){
			printf("---------------------\nEtudiant %d :\n", i);
			for(int j = 0; j<Nb_options; j++){
				printf("Choix %d = Option %d\n", j, listeEtu[i].choice[j]);
			}
		}
	//}
}

int check_if_everyone_is_assigned(){
	for (int i=0; i<Nb_etu; i++){
		if(listeEtu[i].affectation == -1)
			return 0;
	}
	return 1;
}

void get_choice_for_everyone(){
	int best_choice;
	int best_index;

	for(int i=0; i<Nb_etu; i++){
		best_index = -1;
		for(int j=0; j<Nb_options; j++){
			listeEtu[i].choice[j] = -1;
		}

		for(int j=0; j<Nb_options; j++){	// Permet d'avoir les options par ordre de demande dans choice[]
			best_choice = -1;
			for(int k=0; k<Nb_options; k++){
				if(best_choice < listeEtu[i].creditO[k]){
					if(!is_in_array(listeEtu[i].choice, k)){
						best_choice = listeEtu[i].creditO[k];
						best_index = k;
					}
				}
			}
		listeEtu[i].choice[j]=best_index;
		}
	}
}

void reset_assignement(){
	for (int i=0; i<Nb_etu; i++){
		listeEtu[i].affectation = -1;
	}

	array_to_LL();
}

int new_affect(int choice_index){	// renvoi 1 si une affectation a eu lieu, sinon 0

	int change = 0;
	for (int i=0; i<Nb_etu; i++){
		if(listeEtu[i].affectation == -1){
			int option = listeEtu[i].choice[choice_index];	//On récupère le choix de l'étudiant qu'on va traiter
			int compteur = 0;
			LISTE tmp = LL_option_list[option];
			while (compteur < effectif[option]){
				if (tmp->etudiant.idEtudiant == listeEtu[i].idEtudiant){
					if(change == 0)
						change = 1;
					effectif[option]--;
					listeEtu[i].affectation = option;
					remove_when_assigned(listeEtu[i]);
				}
				tmp = tmp->suiv;
				compteur ++;
			}
			/*for(int j=0; j<effectif[option]; j++){
				if (copy_option_list[option][j].idEtudiant == listeEtu[i].idEtudiant){
					if(change == 0){
						change = 1;	// On a eu une affectation, on refera l'affect apres
					}
					effectif[option]--;
					listeEtu[i].affectation = option;
					remove_when_assigned(listeEtu[i]);
					
				}
			}*/
		}
	}

	return change;
}

void new_affect_all(){
		get_choice_for_everyone();
		//print_choice();	

		int check_change;
		for(int i=0; i<Nb_options; i++){
			check_change = 1;
			while (check_change){
				check_change = new_affect(i);
				printf("check_change = %d\n", check_change);
			}
			printf("Aucun changement on regarde les choix %d -> check_change = %d\n", i+1, check_change);
		}
} 



/* Ajoutes tous les étudiants a toutes les listes d'options pour la trié par la suite */
void fill_option_list(){
	//printf("Start %s\n", __func__);
	for(int i=0; i<Nb_options; i++){
		for(int j=0; j<Nb_etu; j++){
			option_list[i][j] = listeEtu[j];
		}
	} 
	//printf("End %s\n", __func__);
}

/* tri la liste des options par étudiants selon ceux qui ont le plus de crédits */
void tri_option_list(){
	//printf("Start %s\n", __func__);
	Etudiant tmp;
	for(int indice_option=0; indice_option<Nb_options; indice_option++){
		for(int i=0; i<=Nb_etu -1; i++)
			for(int j=0; j<Nb_etu; j++)
				if (option_list[indice_option][i].creditO[indice_option] >
							option_list[indice_option][j].creditO[indice_option]) {	
					tmp = option_list[indice_option][i];
					option_list[indice_option][i] = option_list[indice_option][j];
					option_list[indice_option][j] = tmp;
				}
	}
	//printf("End %s\n", __func__);
}


/*void tri(Etudiant Tab[Nb_etu], int M){
	Etudiant tmp;
	for(int i=0; i<=Nb_etu -1; i++)
		for(int j=0; j<Nb_etu; j++)
    		if (Tab[i].creditO[M] > Tab[j].creditO[M]) {
                tmp = Tab[i];
                Tab[i] = Tab[j];
                Tab[j] = tmp;
	        }  
}*/



void print_option_list(){
	//printf("Start %s\n", __func__);
	for(int i=0; i<Nb_options; i++){
		printf("	||| Option %d |||\n", i);
		for (int j=0; j<Nb_etu; j++) {
			printf("	  Etudiant n°%d\n", option_list[i][j].idEtudiant);
		}
		printf("  --------------------------------------------\n");
		printf("  --------------------------------------------\n");
		printf("  --------------------------------------------\n");
	}
	//printf("End %s\n", __func__);
}

void print_copy_option_list(){
	//printf("Start %s\n", __func__);
	for(int i=0; i<Nb_options; i++){
		printf("	||| Option %d |||\n", i);
		for (int j=0; j<Nb_etu; j++) {
			printf("	  Etudiant n°%d\n", copy_option_list[i][j].idEtudiant);
		}
		printf("  --------------------------------------------\n");
		printf("  --------------------------------------------\n");
		printf("  --------------------------------------------\n");
	}
	//printf("End %s\n", __func__);
}

void print_affectations(){
	//printf("Start %s\n", __func__);
	for (int i=0; i<Nb_etu; i++){
		printf("\nETUDIANT %d\n", i);
		for (int j=0; j<Nb_options; j++){
			printf("Option %d : %d\n", j, listeEtu[i].creditO[j]);
		}
		printf("Affectation : %d\n", listeEtu[i].affectation);
	}
	//printf("End %s\n", __func__);
}


int main(int argc, char const *argv[]){
/* Création des étudiants + affectations credits */
	srand(time(NULL));
	//Etudiant listeEtu[Nb_etu]; 
	listeEtu = malloc(sizeof(Etudiant)*Nb_etu);

	for(int i = 0; i<Nb_etu; i++){
		//printf("Premier for\n");
		listeEtu[i].idEtudiant = i;
		listeEtu[i].affectation = -1;

		for(int j=0; j<CREDIT; j++){
			//printf("Deuxieme for ||| i = %d j = %d\n", i, j);

			int draw = rand()%Nb_options;	
			while (listeEtu[i].creditO[draw] >= 7)
				//printf("while ||| i = %d j = %d\n", i, j);
				draw = rand()%Nb_options;

			listeEtu[i].creditO[draw] += 1;			
		}
	}


/*** BLOC USELESS MAIS SEGFAULT SI JE L'ENLEVE, AUCUNE LOGIQUE ***/

	Etudiant M1[Nb_etu];
	for (int i=0; i<Nb_etu; i++){
		M1[i] = listeEtu[i];
	}
	Etudiant M2[Nb_etu];
	for (int i=0; i<Nb_etu; i++){
		M2[i] = listeEtu[i];
	}
	Etudiant M3[Nb_etu];
	for (int i=0; i<Nb_etu; i++){
		M3[i] = listeEtu[i];
	}
	Etudiant M4[Nb_etu];
	for (int i=0; i<Nb_etu; i++){
		M4[i] = listeEtu[i];
	}
	Etudiant M5[Nb_etu];
	for (int i=0; i<Nb_etu; i++){
		M5[i] = listeEtu[i];
	}
	
/***	FIN DU BLOC DE MERDE	***/

	/* triage des étudiants dans les matieres */

	fill_option_list();
	//print_option_list();
	tri_option_list();
	//print_option_list();
	array_to_LL();
	//print_LL();
	new_affect_all();


	//print_LL();
	/*for(int i=0; i<Nb_options; i++){
		printf("%d / ",effectif[i]);
	}*/

	//affect_all();
	
	print_affectations();

	/*print_affectations();
	print_copy_option_list();

	for(int i=0; i<Nb_options; i++){
		printf("%d / ",effectif[i]);
	}
*/
	
	return 0;

}
