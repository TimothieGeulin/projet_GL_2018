#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#define CREDIT 10
#define Nb_options 5	//	nombre d'options
#define Nb_etu 20 		//	nombre d'étudiants

typedef struct Etudiant {
	int idEtudiant;
	int creditO[Nb_options];
	int choice[Nb_options];
	int affectation;
} Etudiant;

typedef struct s_LL_etudiant LL_etudiant;

struct s_LL_etudiant{
	Etudiant etudiant;
	LL_etudiant* suiv;
};

typedef LL_etudiant *LISTE;


void remove_when_assigned(Etudiant current);
int check_assignement(int choice[Nb_options], Etudiant current, int cursor);
int is_in_array(int tab[Nb_options], int check);
void get_choice_for_everyone();
void new_affect_all();
void fill_option_list();
void tri_option_list();
void print_option_list();
void print_affectations();
