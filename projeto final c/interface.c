#include "MODEL_MAIN.H"

//arquivo de interface guardara, configuração de interface e grupos existentes

int config_interface(){
	
	char titulo[] = "TITULO RASCUNHO TEST";
	char up_char_model[] = "-----";
	char dn_char_model[] = "--------------------";
	int option_y = 3, option_x, i, j;
	printf("\n----- INICIANDO CONFIGURACAO DE INTERFACE -----\nA interface nao pode estar com uma coluna quebrada, os blocos precisam estar totalmente visiveis!\n");
	
	char confirm_interface;
	
	do{
		
		printf("\nDIGITE O QUANTO DE COLUNAS DESEJA NA SUA INTERFACE: ");
		scanf("%d", &option_y);
		printf("DIGITE O QUANTO DE LINHAS DESEJA NA SUA INTERFACE: ");
		scanf("%d", &option_x);
	
		printf("\n\nVOCE DIGITOU O MODO %dX%d\nEXEMPLO DO MODO DIGITADO\n\n", option_y, option_x);
		for(i = 0; i < option_x; i++){
			for(j = 0; j < option_y; j++){
				printf("%s Grupo 00 %s    ", up_char_model, up_char_model);
			}
			printf("\n");
			for(j = 0; j < option_y; j++){
				printf("%s    ", titulo);//esse espaço (\t) tem valor fixo de 4!
			}
			printf("\n");
			for(j = 0; j < option_y; j++){
				printf("%s    ", dn_char_model);
			}
			printf("\n");
		}
		
		int end_group_interface = (option_y * 20) + (option_y - 1) * 4; // valor de '===' sendo 20 tamanho de blocos + tamanho de um \t
		
		printf("\n\nESCOLHA O ID DO GRUPO PARA ACESSAR OS PRODUTOS: ");
		
		int end_products_group_interface = (end_group_interface / 2) - 11;
		
		printf("\n%.*s", end_products_group_interface, "===============================================================================================================================================================================");
		printf(" Produtos do grupo 00 ");
		printf("%.*s\n\n", end_products_group_interface, "===============================================================================================================================================================================");
		
		long id_product_model = 353;
		char name_product_model[] = "Camiseta Básica Conforto Algodão Premium";
		float price_product_model = 15.98;
		
		for(i = 0; i < 15; i++){
			printf("%.6ld | %s | R$%.2lf\t", id_product_model, name_product_model, price_product_model);
			printf("%.6ld | %s | R$%.2lf\n", id_product_model, name_product_model, price_product_model);

		}
		
		printf("\nPara confirmar a interface do sistema digite 'C'\nPara retornar ao menu principal digite 'R'\nPara testar outro modelo digite qualquer outra tecla! OPCAO: ");
		clear_buffer();
		confirm_interface = getchar();
		
		if(confirm_interface != '\n')
	        clear_buffer();
		
		confirm_interface = toupper(confirm_interface);
		
		if(confirm_interface == 'C'){
			//
		}
		else if(confirm_interface == 'R')
			return RETORNAR_SUBMENU;
		
	}while(confirm_interface != 'C');
	
	
}//end config_interface