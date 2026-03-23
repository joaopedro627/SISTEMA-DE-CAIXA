#include <stdio.h>
#define MAX_COMP_LINER 30

int main(){

	int semana[7];
	int i;
	
	/*
	semana[0] = seg
	semana[1] = ter
	semana[2] = qua
	semana[3] = qui
	semana[4] = sex
	semana[5] = sab
	semana[6] = dom	
	*/
	
	for(i = 0; i < 7; i++){//input faturamento dos dias da semana
		printf("\ndigite o faturamento do dia %d: ", i + 1);
		scanf("%d", &semana[i]);	
	}
	
	int dia_melhor_faturamento = 0;
	
	for(i = 1; i < 7; i++){//pega o valor do mlehor dia de faturamento
		if(semana[dia_melhor_faturamento] < semana[i])
			dia_melhor_faturamento = i;
	}
	
	printf("melhor dia de faturametno foi %d = %d\n\n", dia_melhor_faturamento + 1, semana[dia_melhor_faturamento]);
	
	int valor_divisor_grafico = semana[dia_melhor_faturamento] / MAX_COMP_LINER;
	int numero_de_colunas;
	for(i = 0; i < 7; i++){
		
		switch(i){
			case 0: printf("SEGUNDA | ");
				numero_de_colunas = semana[i] / valor_divisor_grafico;
				if(numero_de_colunas == 0)
					numero_de_colunas = 1;
				printf("%.*s", numero_de_colunas, "============================================================");
				printf(" R$%d\n\n", semana[i]);
				break;
			case 1: printf("TERCA   | ");
				numero_de_colunas = semana[i] / valor_divisor_grafico;
				if(numero_de_colunas == 0)
					numero_de_colunas = 1;
				printf("%.*s", numero_de_colunas, "============================================================");
				printf(" R$%d\n\n", semana[i]);
				break;
			case 2: printf("QUARTA  | ");
				numero_de_colunas = semana[i] / valor_divisor_grafico;
				if(numero_de_colunas == 0)
					numero_de_colunas = 1;
				printf("%.*s", numero_de_colunas, "============================================================");
				printf(" R$%d\n\n", semana[i]);
				break;
			case 3: printf("QUINTA  | ");
				numero_de_colunas = semana[i] / valor_divisor_grafico;
				if(numero_de_colunas == 0)
					numero_de_colunas = 1;
				printf("%.*s", numero_de_colunas, "============================================================");
				printf(" R$%d\n\n", semana[i]);
				break;
			case 4: printf("SEXTA   | ");
				numero_de_colunas = semana[i] / valor_divisor_grafico;
				if(numero_de_colunas == 0)
					numero_de_colunas = 1;
				printf("%.*s", numero_de_colunas, "============================================================");
				printf(" R$%d\n\n", semana[i]);
				break;
			case 5: printf("SABADO  | ");
				numero_de_colunas = semana[i] / valor_divisor_grafico;
				if(numero_de_colunas == 0)
					numero_de_colunas = 1;
				printf("%.*s", numero_de_colunas, "============================================================");
				printf(" R$%d\n\n", semana[i]);
				break;
			case 6: printf("DOMINGO | ");
				numero_de_colunas = semana[i] / valor_divisor_grafico;
				if(numero_de_colunas == 0)
					numero_de_colunas = 1;
				printf("%.*s", numero_de_colunas, "============================================================");
				printf(" R$%d\n\n", semana[i]);
				break;
		}
		
	}//end for
	
	return 0;
	
}