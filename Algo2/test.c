#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NB_E 20
#define NB_M 5
#define NB_C 10

int affect(int max, int total, int position, int E[NB_E][NB_M], char A[NB_E][NB_M], char Amax[NB_E][NB_M])
{
	int i,j;

	//printf("Position = %d",position);
	if(position>=NB_E)
	{
		//printf("Position finale atteinte (total = %d)\n", total);
		/*for(i=0;i<NB_E;i++)
		{
			for(j=0;j<NB_M;j++) 
			{
				printf("%d ",A[i][j]);
			}
			printf("\n");
		}
		printf("===============\n");*/
		if(total>max) 
		{
			printf("Nouveau max %d\n",total);
			for(j=0;j<NB_M;j++) 
				for(j=0;j<NB_C;j++) Amax[i][j] = A[i][j];
			return total;
		}
		else return max;
	}
	for(i=0; i<NB_M; i++)
	{
		A[position][i]=1;
		total += E[position][i];
		max = affect(max, total, position+1, E, A, Amax);
		total -= E[position][i];
		A[position][i]=0;
	}
	return max;
}

int main(void)
{
	srand(time(0));
	//Création du tableau d'élèves et d'affectations.
	int E[NB_E][NB_M]; //Eleves
	char A[NB_E][NB_M];	//Affectations (binaire)
	char Amax[NB_E][NB_M]; //Meilleure affectation
	int i,j,k;
	//Initialisation et remplissage aléatoire
	for(i=0;i<NB_E;i++)
	{
		for(j=0;j<NB_M;j++) 
		{
			A[i][j]=0;
			Amax[i][j]=0;
			E[i][j]=0;
		}
		for(k=0;k<NB_C;k++)
		{
			E[i][rand()%NB_M]++;
		}
	}

	
	//Recherche du max
	printf("Recherche du max\n");
	int max = 0;
	max = affect(max,0,0,E,A,Amax);

	for(i=0;i<NB_E;i++)
	{
		for(j=0;j<NB_M;j++) 
		{
			printf("%d ",Amax[i][j]);
		}
		printf("\n");
	}
	printf("===============\n");
}

