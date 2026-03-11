#include "models.h"

void options_menu(){
	
	int run_flag = 0, user_option;
	
	do{
		printf("----- MENU ABERTO -----\n\n");
		printf("%t1 = PAINEL DE VENDAS\n%t2 = PRODUTOS\n%t3 = PAINEL DE FUNCIONARIOS\n");
		printf("%t4 = FECHAMENTO DE CAIXA\n%t5 = SAIR DO PROGRAMA\n\n");
		printf("%tDIGITE A OPCAO DESEJADA: ");
		scanf("%d", &user_option);
		
		switch(user_option){
			case 1: printf("\nINCIANDO PAINEL DE VENDAS...\n");
					break;//end case 1
			case 2: printf("\nINCIANDO PRODUTOS...\n");
					break;//end case 2
			case 3:	printf("\nINCIANDO PAINEL DE FUNCIONARIOS...\n");
					break;//end case 3
			case 4: printf("\nINCIANDO FECHAMENTO DE CAIXA...\n");
					break;//end case 4
			case 5: printf("\nSAINDO DO PROGRAMA...\n");
					break;//end case 5
			default: printf("\nOPCAO INVALIDA...\nDIGITE UMAS DAS OPCOES: 1 - 2 - 3 - 4 - 5\n");
					break;//end default case
		}
		
	}while(run_flag == 0);//end do-while
	
}//end function options_menu