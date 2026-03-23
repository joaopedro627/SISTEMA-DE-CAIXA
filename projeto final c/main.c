#include "MODEL_MAIN.H"

int main() {
	
	int exit_flag;
	config_interface();
	exit_flag = options_menu();
	if(exit_flag == SAIR_PROGRAMA)
		return 0;
	return 0;
}

int options_menu(){

	int exit_flag, user_option, exit_program;

	do{
	
		printf(" ----- MENU ABERTO ----- \n\n");
		printf("[1] = PAINEL DE VENDAS\n[2] = PRODUTOS\n[3] = PAINEL DE FUNCIONARIOS\n");
		printf("[4] = FECHAMENTO DE CAIXA\n[5] = GRUPOS\n[6] = FECHAMENTO DE CAIXA\n\n");
		printf("DIGITE A OPCAO DESEJADA: ");
		scanf("%d", &user_option);
		
		switch(user_option){
			case 1: printf("\nINCIANDO PAINEL DE VENDAS ... \n\n");
				break;//end case 1
			case 2: printf("\nINCIANDO PRODUTOS ... \n\n");
				exit_flag = options_product();
				if(exit_flag == SAIR_PROGRAMA)
					return SAIR_PROGRAMA;
				else
					continue;
			case 3: printf("\nINCIANDO PAINEL DE FUNCIONARIOS ... \n\n");
				exit_flag = options_employees();
				if(exit_flag == SAIR_PROGRAMA)
					return SAIR_PROGRAMA;
				else
					continue;
			case 4: printf("\nINCIANDO FECHAMENTO DE CAIXA ... \n\n");;
				break;
			case 5: printf("\nINCIANDO GRUPOS ... \n\n");
				options_groups_products();
				break;//end case 4
			case 6: printf("\nSAINDO DO PROGRAMA ... \n");
				return SAIR_PROGRAMA;
			default: printf("\nOPCAO INVALIDA ... \nDIGITE UMAS DAS OPCOES: 1 - 2 - 3 - 4 - 5\n\n");
				break;//end default case
		}//end switch
	}while(user_option >= 1 && user_option <= 6);//end do-while

}//end function options_menu4