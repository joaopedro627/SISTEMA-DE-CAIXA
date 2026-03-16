#include "MODEL_MAIN.H"
/*
int options_groups_products(){
	
	int flag_return, user_option;

	do{
	
		printf(" ----- MENU GRUPOS ----- \n\n");
		printf("[1] = LISTA DE GRUPOS\n[2] = NOVO GRUPO\n[3] = EDICAO DE GRUPOS DA INTERFACE\n");
		printf("[4] = ALTERAR PARAMETROS DO GRUPO\n[5] = VISUALIZAR GRUPO\n[6] = RETORNANDO AO MENU PRINCIPAL\n[7] = SAIR DO PROGRAMA\n\n");
		printf("DIGITE A OPCAO DESEJADA: ");								//[6] atualizar valores. S/V
		scanf("%d", &user_option);
		
		switch(user_option){
			case 1: printf("\nINCIANDO LISTA DE GRUPOS ... \n");
				flag_return = list_groups();
				if(flag_return == RETORNAR_MENU_PRINCIPAL)
					return 0;
				break;
			case 2: printf("\nINCIANDO NOVO GRUPO... \n\n");
				new_group();
				break;//end case 2
			case 3: printf("\nINCIANDO EDICAO DE GRUPOS DA INTERFACE... \n");
				flag_return = edit_interface_groups();
				if(flag_return == RETORNAR_MENU_PRINCIPAL)
					return 0;
				break;
			case 4: printf("\nINICIANDO ALTERAR ITENS DO GRUPO\n\n");
				flag_return = edit_group();
				if(flag_return == RETORNAR_MENU_PRINCIPAL)
					return 0;
				break;
			case 5: printf("\nINICIANDO VISUALIZAR GRUPO\n\n");
				flag_return = search_group();
				if(flag_return == RETORNAR_MENU_PRINCIPAL)
					return 0;
				break;
			case 6: printf("\nRETORNANDO AO MENU PRINCIPAL ... \n\n");
				return RETORNAR_MENU_PRINCIPAL;
			case 7: printf("\nSAINDO DO PROGRAMA ... \n");
				return SAIR_PROGRAMA;
			default: printf("\nOPCAO INVALIDA ... \nDIGITE UMAS DAS OPCOES: [1] - [2] - [3] - [4] - [5] - [6] - [7]\n\n");
				break;//end default case
		}//end switch
	}while(user_option >= 1 && user_option <= 7);//end do-while

}//end function options_employees

int list_groups(){
	
	FILE *p_arq = fopen("groups.dat", "rb");
	Employee file_groups;
	int pag = 1;
	int filter_option, contador = 1, flag_return;
	char flag_filter;
	
	if(p_arq == NULL){//file failure open check
		printf("\nNao foi possivel abrir o arquivo. Fechando programa.");
		exit(EXIT_FAILURE);
	}
	
	//variaveis auxiliares para alocação dinamica
	long tam_bytes_arq;
	size_t tam_array = 0, i = 0, j;
	
	fseek(p_arq, 0, SEEK_END);
	
	if(ftell(p_arq) != 0){
		tam_bytes_arq = ftell(p_arq);
		tam_array = (size_t)tam_bytes_arq / sizeof(Group);
	}
	else{
		printf("\nNenhum funcionario cadastrado.\n");
    	fclose(p_arq);
    	return 0;
	}
	
	Group *groups_array = malloc(tam_array * sizeof(Group));
	
	if(groups_array == NULL){
		printf("\nNao foi possivel alocar memoria.Verifique a capacidade maxima de RAM do computador\n");
		printf("\nFechando programa.");
		fclose(p_arq);
		exit(EXIT_FAILURE);
	}
	
	rewind(p_arq);
	
	tam_array = fread(groups_array, sizeof(Group), tam_array, p_arq);
	
	fclose(p_arq);
	
	int max_pags = tam_array / 20;
	if (tam_array % 20 != 0)
	    max_pags++;

	printf("\n----- LISTA DE GRUPOS ---- \t\t[%d] NUMEROS DE PAGINA\n", max_pags);
	printf("\n\n----- Pagina %d ----\n\n", pag);
	
   	for(i = 0; i < tam_array; i++, contador++){
   		
   		printf("ID: %.6d | NOME: %s | QUANT.PRODUTOS: %d |  ", groups_array[i].id, groups_array[i].name, groups_array[i].quant_products);
		printf("STATUS: %s\n", groups_array[i].status == ATIVO ? "ATIVO" : "INATIVO");
			
		if(contador % 20 == 0 && i + 1 != tam_array){
			clear_buffer();
			flag_return = walk_pags(&contador, &pag, max_pags);
			if(flag_return == RETORNAR_SUBMENU){
				printf("\nRETORNANDO AO MENU GRUPOS...\n");
				free(groups_array);
				return RETORNAR_SUBMENU;
			}
			else if(flag_return == RETORNAR_MENU_PRINCIPAL){
				printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
				free(groups_array);
				return RETORNAR_MENU_PRINCIPAL;
			}	
			else if(flag_return == RETORNAR_FUNCAO)
				printf("\nFuncao Lista de Grupos.\n");
				
				clear_buffer();
				printf("\nPara acessar o painel de filtros digite 'F'");
				i = ((pag - 1) * 20) - 1;//troca o valor do i para caminhar entre paginas
				flag_filter = getchar();

	            if(flag_filter != '\n') 
	            	clear_buffer();
				
	        	flag_filter = toupper(flag_filter);
	        	
	        	if(flag_filter == 'F'){
	        		
	        		flag_return = filters_groups(groups_array, tam_array);
        			if(flag_return == RETORNAR_SUBMENU){
						printf("\nRETORNANDO AO MENU GRUPOS...\n\n");
						free(groups_array);
						return RETORNAR_SUBMENU;	
					}
					else if(flag_return == RETORNAR_FUNCAO)
						printf("\nFuncao Lista de Grupos.\n");
					else if(flag_return == RETORNAR_MENU_PRINCIPAL){
						free(groups_array);
						return RETORNAR_MENU_PRINCIPAL;
					}	
        			else if(flag_return == FILTRO_BEM_SUCEDIDO){
        				printf("\n--- Fim dos registros. Saindo da funcao\n\n");
        				free(groups_array);
        				return 0;
					}
				}//if 'F'		
				
				printf("\nPara vizualizar itens do grupo digite o ID do grupo\nCaso nao deseje vizualizar digite um valor menor ou igual a 0. Digite: \n\n");
				int id_group;
		
		        scanf("%d", &id_group);
				
				if(id_group > 0)
					itens_group(id_group);
				
				printf("\n\n----- Pagina %d ----\n\n", pag);
		}//end contador	
		
		printf("\nPara vizualizar itens do grupo digite o ID do grupo\nCaso nao deseje vizualizar digite um valor menor ou igual a 0. Digite: \n\n");
		int id_group;
		
	    scanf("%d", &id_group);
				
		if(id_group > 0)
			itens_group(id_group);
		
	}//end for para impressao da lista
   	printf("\n--- Fim dos registros.\n\n");
   	free(groups_array);
	return 0;//retorna a ultima função
	
}//end function list_groups

	void itens_group(int id){
		
		FILE *p_arq = fopen("groups.dat", "rb");
		Group view_group;
		
		FILE *p_arq_products = fopen("products.dat", "rb");
		
		int i;
		
		if(p_arq == NULL){
			printf("\nNao foi possivel abrir o arquivo dos grupos. Fechando programa.");
			exit(EXIT_FAILURE);
		}
		
		if(p_arq_products == NULL){
			printf("\nNao foi possivel abrir o arquivo dos produtos. Fechando programa.");
			fclose(p_arq);
			exit(EXIT_FAILURE);
		}
		
		long tam_bytes_arq;
		size_t tam_array = 0;
	
		fseek(p_arq_products, 0, SEEK_END);
		
		tam_bytes_arq = ftell(p_arq_products);
		tam_array = (size_t)tam_bytes_arq / sizeof(Products);
		
		Products *products_array = malloc(tam_array * sizeof(Products));
		
		if(products_array == NULL){
			printf("\nNao foi possivel alocar memoria.Verifique a capacidade maxima de RAM do computador\n");
			printf("\nFechando programa.");
			fclose(p_arq_products);
			fclose(p_arq);
			exit(EXIT_FAILURE);
		}
		
		rewind(p_arq_products);
		
		tam_array = fread(products_array, sizeof(Products), tam_array, p_arq_products);
    	
		fclose(p_arq_products);
		
		while(fread(&view_group, sizeof(Group), 1, p_arq)){
			if(id == view_group.id){
				printf("\nPRODUTOS GRUPO %s\n", view_group.name);
				for(i = 0; i < MAX_ITENS_GROUP; i++){
					if(view_group.id_products[i] == products_array[i].id)
						printf("ITEM ID: %.6ld | NOME: %s | PREÇO : %.2f | VENDAS DO PRODUTO: %.2f\n", products_array[i].id, products_array[i].name, products_array[i].sale_price, view_group.sales_products[i]);	
					else if(view_group.id_products[i] == 0){
						printf("\nFim dos itens do grupo ( %s )", view_group.name);
						fclose(p_arq);
						free(products_array);
						return;
					}
				}		
			}//end verificate if(id == id-group) 		
		}
		printf("\nFim dos itens do grupo");
		fclose(p_arq);
		free(products_array);	
		return;
		
	}//end function itens_group

	int filters_groups(Group array[], size_t tam_array){
		
		int option_filter, option_filter_intern, flag_return, contador;
		int i;
		
		//variables og_array
		int pag = 1;
		int max_pags = tam_array / 20;
			if (tam_array % 20 != 0)
			    max_pags++;
		           
		printf("\nFILTRAR POR:\n\t[1] = ATIVO\\INATIVO\n\t[2] = MAIORES VENDAS\n\t[3] = ID.DECRESCENTE\n\t[4] = ORDEM.ALFABETICA\n\t[5] = RETORNAR A FUNCAO ANTERIOR\n\t[6] = RETORNAR AO MENU SUBMENU\n\t[7] = RETORNAR AO MENU PRINCIPAL\n\nDIGITE A OPCAO DESEJADA: ");
		do{
			scanf("%d", &option_filter);
			
			switch(option_filter){
				case 1:
				flag_return = status_filter_groups(array, tam_array);
					if(flag_return == RETORNAR_SUBMENU)
						return RETORNAR_SUBMENU;
					else if(flag_return == FILTRO_BEM_SUCEDIDO)
						return FILTRO_BEM_SUCEDIDO;
					else if(flag_return == RETORNAR_MENU_PRINCIPAL)
						return RETORNAR_MENU_PRINCIPAL;
				case 2:
				flag_return = price_filter(array, tam_array, max_pags);
					if(flag_return == RETORNAR_SUBMENU)
						return RETORNAR_SUBMENU;
					else if(flag_return == FILTRO_BEM_SUCEDIDO)
						return FILTRO_BEM_SUCEDIDO;
					else if(flag_return == RETORNAR_MENU_PRINCIPAL)
						return RETORNAR_MENU_PRINCIPAL;
				case 3: printf("\n----- LISTA DE PRODUTOS ---- \t\t[%d] NUMEROS DE PAGINA\n", max_pags);
					printf("\n\n----- Pagina %d ----\n\n", pag);
				   	for(i = tam_array - 1; i >= 0; i--, contador++){
				   		
				   		printf("ID: %.6d | NOME: %s | PRECO: %.2f | PRECO_COMPRA: %.2f | ESTOQUE: %d | ", array[i].id, array[i].name, array[i].sale_price, array[i].purchase_price, array[i].stock);
						printf(" STATUS: %s\n",array[i].status == ATIVO ? "ATIVO" : "INATIVO");
							
						if(contador % 20 == 0){
							clear_buffer();
							flag_return = walk_pags(&contador, &pag, max_pags);
							if(flag_return == RETORNAR_SUBMENU)
								return RETORNAR_SUBMENU;
							else if(flag_return == RETORNAR_FUNCAO)
								return RETORNAR_FUNCAO;
							printf("\n\n----- Pagina %d ----\n\n", pag);
							i = ((tam_array - 1) - ((pag - 1) * 20)) + 1;//troca o valor do i para caminhar entre paginas
						}//end contador
					}//end for para impressao
					return FILTRO_BEM_SUCEDIDO;
				case 4: flag_return = alphabetical_filter(array, tam_array, max_pags);
					if(flag_return == RETORNAR_SUBMENU)
						return RETORNAR_SUBMENU;
					else if(flag_return == FILTRO_BEM_SUCEDIDO)
						return FILTRO_BEM_SUCEDIDO;
				case 5: return RETORNAR_FUNCAO;
				case 6: return RETORNAR_SUBMENU;
				case 7: return RETORNAR_MENU_PRINCIPAL;
				default: printf("\nOPCAO INVALIDA ...\nDIGITE UMAS DAS OPCOES: [1] - [2] - [3] - [4] - [5] - [6] - [7]\n\n");
					break;
			}//end switch option_filter
		}while(option_filter >= 1 && option_filter <= 7);//end do-while switch (option_filter)
		
	}//end function filters

	int status_filter_groups(Group array[], size_t tam_array){
			
		size_t i, j;
		int status_option, contador = 1, flag_return, flag_filter;
		
		//variables og_array
		int pag = 1;
		int max_pags = tam_array / 20;
			if (tam_array % 20 != 0)
			    max_pags++;
		//variables inactive_array
		size_t qtd_inactive_group = 0;
		
		for(i = 0; i < tam_array; i++){//for para preenchimento de vetor de produtos desativados
			if(array[i].status == INATIVO)
				qtd_inactive_group++;
		}
		int pag_inactive = 1;
		int max_pags_inactive = qtd_inactive_group / 20;
		if(qtd_inactive_group % 20 != 0)
			   max_pags_group++;
		size_t qtd_active_group = tam_array - qtd_inactive_group;
		
		int pag_active = 1;
		int max_pags_active = qtd_active_group / 20;
		if (qtd_active_group % 20 != 0)
			   max_pags_active++;
		
		
		printf("\nFILTRAR POR:\n\t[1] = ATIVO\n\t[2] = INATIVO\n\t[3] = AMBOS\n\t[4] = RETORNAR AO MENU SUBMENU\n\t[5] = RETORNAR AO MENU PRINCIPAL\n\nDIGITE A OPCAO DESEJADA: ");
		
		do{
			scanf("%d", &status_option);
		        
		    switch(status_option){
	        	case 1: if(qtd_active_product == 0){	
	        		printf("\nNAO HA PRODUTOS ATIVOS NA LISTA\nRETORNANDO AO MENU SUBMENU\n");
	        		return RETORNAR_SUBMENU;
					}
					printf("\n----Lista filtro ATIVO---- \t\t[%d] NUMEROS DE PAGINA\n", max_pags_active);
					printf("\n\n----- Pagina %d ----\n\n", pag_active);
	        		Group *groups_active = malloc(qtd_active_group * sizeof(Group));
	        		
					j = 0;
						
	        		for(i = 0; i < tam_array; i++){
        				if(array[i].status == ATIVO){
        					groups_active[j] = array[i];
        					j++;
						}
        			}//end for para preenchimento do vetor de ativos
        			
        			for(i = 0; i < qtd_active_group; i++, contador++){
        				
		 			  	printf("ID: %.6d | NOME: %s | QUANT.PRODUTOS: %d\n", groups_active[i].id, groups_active[i].name, groups_active[i].quant_products);

						if(contador % 20 == 0 && i + 1 != qtd_active_group){
							clear_buffer(); 
							flag_return = walk_pags(&contador, &pag_active, max_pags_inactive);
							if(flag_return == RETORNAR_SUBMENU){
								free(groups_active);
								return RETORNAR_SUBMENU;
							}
								
							else if(flag_return == RETORNAR_FUNCAO)
								printf("\nFuncao Lista de Grupos > Filtro de Status.\n");
							printf("\n\n----- Pagina %d ----\n\n", pag_active);
							i = ((pag_active - 1) * 20) - 1;//troca o valor do i para caminhar entre paginas
						}//end contador
						
					}//end for para impressao
					
					free(groups_active);
					
					printf("\n-------------------\n");
									
					return FILTRO_BEM_SUCEDIDO;
		       	case 2: if(qtd_inactive_group == 0){	
	        		printf("\nNAO HA GRUPOS INATIVOS NA LISTA\nRETORNANDO AO MENU SUBMENU\n");
	        		return RETORNAR_SUBMENU;
					}
				
				 	printf("\n----Lista filtro INATIVO----\t\t[%d] NUMEROS DE PAGINA\n", max_pags_inactive);
					printf("\n\n----- Pagina %d ----\n\n", pag_inactive);
	        		Group *groups_inactive = malloc(qtd_inactive_group * sizeof(Group));
	        		
	        		j = 0;
	        			
        			for(i = 0; i < tam_array; i++){
        				if(array[i].status == INATIVO){
        					groups_inactive[j] = array[i];
        					j++;
						}
        			}//end for para preenchimento do vetor de inativos
	        			
        			for((i = 0; i < qtd_inactive_group; i++, contador++){
        				
        				printf("ID: %.6d | NOME: %s | QUANT.PRODUTOS: %d\n", groups_inactive[i].id, groups_inactive[i].name, groups_inactive[i].quant_products);
								
						if(contador % 20 == 0 && i + 1 != qtd_inactive_group){
							clear_buffer();
							flag_return = walk_pags(&contador, &pag_inactive, max_pags_inactive);
							if(flag_return == RETORNAR_SUBMENU){
								free(groups_inactive);
								return RETORNAR_SUBMENU;
							}
								
							else if(flag_return == RETORNAR_FUNCAO)
								printf("\nFuncao Lista de Grupos > Filtro de Status.\n");
							printf("\n\n----- Pagina %d ----\n\n", pag_inactive);
							i = ((pag_inactive - 1) * 20) - 1;//troca o valor do i para caminhar entre paginas
						}//end contador
					}//end for para impressao
		 			  		
					free(groups_inactive);
					printf("\n-------------------\n");
        			return FILTRO_BEM_SUCEDIDO;
		       	case 3: printf("\n----Lista AMBOS Status---- \t\t[%d] NUMEROS DE PAGINA\n", max_pags);
					printf("\n\n----- Pagina %d ----\n\n", pag);
					for(i = 0; i < tam_array; i++, contador++){
		        		
				   		printf("ID: %.6d | NOME: %s | QUANT.PRODUTOS: %d |  ", array[i].id, array[i].name, array[i].quant_products);
						printf("STATUS: %s\n", array[i].status == ATIVO ? "ATIVO" : "INATIVO");
						
						if(contador % 20 == 0 && i + 1 != tam_array){
							clear_buffer();
							flag_return = walk_pags(&contador, &pag, max_pags);
							if(flag_return == RETORNAR_SUBMENU)
								return RETORNAR_SUBMENU;
							else if(flag_return == RETORNAR_FUNCAO)
								printf("\nFuncao Lista de Grupos > Filtro de Status.\n");	
							printf("\n\n----- Pagina %d ----\n\n", pag);
							i = ((pag - 1) * 20) - 1;//troca o valor do i para caminhar entre paginas
						}//end contador
							
					}//end for para impressao
					return FILTRO_BEM_SUCEDIDO;	
	        	case 4: return RETORNAR_SUBMENU;
	        	case 5: return RETORNAR_MENU_PRINCIPAL;
	        	default: printf("\nOPCAO INVALIDA ...\nDIGITE UMAS DAS OPCOES: [1] - [2] - [3] - [4] - [5]\n\n");
	        		break;
				}//end switch(status_option)
		                
		}while(status_option >= 1 && status_option <= 5);
			
	}//end function status_filter

void new_group(){
	
	FILE *p_arq = fopen("groups.dat", "ab+");
	Group record_group;
	int loop = 0, max_item, i, j;
	int flag_return;
	int produtos_encontrados[MAX_ITENS_GROUP];
	
	FILE *products_p = fopen("products.dat", "rb");
	Products p;
	
	if(products_p == NULL){//file failure open check
		printf("\nNao foi possivel abrir o arquivo dos produtos. Fechando programa.");
		exit(EXIT_FAILURE);
	}
	
	if(p_arq){
		
		do{//verificações do nome do funcionario
			record_group.id = get_next_id(ARQ_GROUPS, KEY_GROUPS);
			
			clear_buffer();
			printf("DIGITE O NOME DO NOVO GRUPO: ");
			fgets(record_group.name, MAX_GROUP_NAME, stdin);
			record_group.name[strcspn(record_group.name, "\n")] = 0;
			if(loop = check_empty_text(record_group.name))
				continue;			
			if(loop = check_burst_buffer(record_group.name, MAX_GROUP_NAME))
				continue;

			if(verify_duplicate_name_group(record_group.name)){
			    printf("\nERRO: GRUPO com NOME ja existente! Cadastro cancelado.\n");
			    fclose(p_arq);
			    return;
			}
		}while(loop == 1);
		
		printf("\nADCIONE OS PRODUTOS DO GRUPO. MAX: %d\nPara acessar a lista de produtos digite 'L'\nPara nao adcionar produto digite qualquer tecla (ENTER)", MAX_ITENS_GROUP);
		
		for(i = 0; i < MAX_ITENS_GROUP; i++){
			record_group.id_products[i] = 0;
			record_group.sales_products[i] = 0;
		}
		
		clear_buffer();
		char flag_list = getchar();

        if(flag_list != '\n')
            clear_buffer();
		
    	flag_list = toupper(flag_list);
    	
    	if(flag_list == 'L'){
    		
    		list_products();
    		
    		printf("\nADCIONE OS PRODUTOS DO GRUPO. MAX: %d\nPara adcionar produto por produto digite 'U' (Indicado para grandes listas de produtos)\nPara adcionar varios produto digite 'V'\nPara nao adcionar produto digite qualquer tecla (ENTER)", MAX_ITENS_GROUP);
    		
	    	clear_buffer();
			char quant_products = getchar();
	
	        if(quant_products != '\n')
	            clear_buffer();
			
	    	quant_products = toupper(quant_products);
	    	
	    	if(quant_products == 'U'){
	    		
	    		for(i = 0; i < MAX_ITENS_GROUP; i++){
	    			
	    			list_products();
	    			printf("PRODUTO NUMERO: %d NO GRUPO\nDigite -1 para parar o envio de produtos\nDIGITE O PREÇO DO PRODUTO: ", i + 1);
	    			scanf("%ld", &record_group.id_products[i]);
	    			
	    			if(record_group.id_products[i] < 0){
	    				printf("\nERRO: ID incorreto o id precisa ser > 0");
	    				i--;
	    				continue;
					}
	    			
	    			if(record_group.id_products[i] == -1){
	    				for(j = 0; j < MAX_ITENS_GROUP; j++){
	    					if(record_group.id_products[j] == 0){
	    						max_item = j;
	    						break;
							}	
						}
						printf("\nO numeros de produtos do grupo sera de %d", max_item);
						break;
					}//end if id_products == -1
	    			
	    			while(fread(&p, sizeof(Products), 1, products_p)){
	    				produto_encontrado = 0;
						if(record_group.id_products[i] == p.id){
							if(p.status == INATIVO){
								printf("\nProduto (%s) nao pode ser adcionado por estar INATIVO\nEdite o status do produto!\nCadastro do produto cancelado.", p.name);
								i--;
								break;
							}
							printf("\nProduto encontrado! ( %s )\n", p.name);
							produto_encontrado = 1;
							break;
						}//end verificate if(user_id == id) 
						else
							produto_encontrado = 0;			
					}
					if(produto_encontrado == 0){
						printf("\nProduto NAO encontrado. ID incorreto ou NAO existente\n");
						i--;
						continue;
					}	
	    			
				}//end for para preenchimento dos produtos 1:1
	    		
    		}//end if 'U'
    		else if(quant_products == 'V'){
    			
    			for(i = 0; i < MAX_ITENS_GROUP; i++){
	    			
	    			list_products();
	    			printf("DIGITE O NUMERO MAXIMO DE PRODUTOS QUE CONSEGUIR\nDigite -1 para parar o envio de produtos\nDIGITE O PREÇO DO PRODUTO: ");
	    			
	    			scanf("%ld", &record_group.id_products[i]);
	    			
	    			if(record_group.id_products[i] == -1){
	    				for(j = 0; j < MAX_ITENS_GROUP; j++){
	    					if(record_group.id_products[j] == 0){
	    						max_item = j - 1;
	    						break;
							}	
						}
						printf("\nO numeros de produtos do grupo sera de %d", max_item + 1);
						break;
					}//end if id_products == -1
	    			
	    			if(record_group.id_products[i] < 0){
	    				printf("\nERRO: ID incorreto o id precisa ser > 0");
	    				i--;
	    				continue;
					}
	    			
	    			while(fread(&p, sizeof(Products), 1, products_p)){
	    				produtos_encontrados[i] = 0;
						if(record_group.id_products[i] == p.id){
							if(p.status == INATIVO){
								printf("\nProduto (%s) pode ser adcionado por estar INATIVO\nEdite o status do produto!\nCadastro do produto cancelado.", p.name);
								i--;
								break;
							}
							produtos_encontrados[i] = 1;
							break;
						}//end verificate if(user_id == id) 
						else
							produtos_encontrados[i] = 0;			
					}
					if(produtos_encontrados[i] == 0){
						printf("\nProduto %d NAO encontrado. ID incorreto ou NAO existente\n", i + 1);
						continue;
					}
	    			
				}//end for para preenchimento de varios produtos 
    			
			}//end if 'V'
			else
				max_item = 0;
				
		}//end if 'L'
		else
			max_item = 0;

		for(i = 0; i < MAX_ITENS_PRODUCTS; i++){
			if(record_group.id_products[i] == 0){
				record_group.quant_products = i;
				break;
			}	
		}
		
		record_group.status = ATIVO;
		
		clear_buffer();
		printf("\nPara confirmar o novo grupo digite 'C'\n");
		char validate_group = getchar();

        if(validate_group != '\n')
            clear_buffer();
		
    	validate_group = toupper(validate_group);
    	
    	if(validate_group == 'C'){
		
			if(fwrite(&record_group, sizeof(Group), 1, p_arq)){
				printf("\n\nGravacao concluida com exito\n\n");
				fclose(p_arq);
				fclose(products_p);
				return;
			}
			else{
				printf("\n\nHouve um erro na gravacao do arquivo. Fechando programa.\n");
				fclose(p_arq);
				fclose(products_p);
				exit(EXIT_FAILURE);
			}
		}	
		else{
			printf("\nNao houve confirmacao do usuario, cancelando novo funcionario\n");
			fclose(p_arq);
			fclose(products_p);
			return;
		}
			
	}//end if p_arq
	else{
		printf("Nao foi possivel criar o arquivo! fechando o programa!\n");
		exit(EXIT_FAILURE);
	}//end else
	
}//end function new_group

int edit_group(){
	
	int id;
	int search_option, edit_option, loop;
	
	printf("QUAL GRUPO DESEJA ALTERAR?");
	printf("\n[1] = BUSCAR POR ID\n[2] = BUSCAR PELA LISTA\n[3] = BUSCAR POR NOME\n[4] = RETORNAR AO MENU PRODUTOS\n[5] = RETORNAR AO MENU PRINCIPAL\n\nDIGITE A OPCAO DESEJADA: ");
	
	
}//end function edit_group
*/
#include <stdlib.h>

int edit_itens_group(int id){
	
	FILE *p_arq = fopen(ARQ_GROUPS, "rb+");
	Group edit_group, temp_array;
	if(p_arq == NULL){
		printf("\nNao foi possivel abrir o arquivo. Fechando programa.");
		exit(EXIT_FAILURE);
	}
	
	int i;
	long id_selecionado;
	char confirm_delete;
	
	FILE *p_arq_product = fopen(ARQ_PRODUCTS, "rb");
	Products products_group;
		
	clear_buffer();
	printf("\nDIGITE 'A' PARA ADCIONAR ITENS NO GRUPO\nDIGITE 'E' PARA EXCLUIR ITENS  DO GRUPO\nOPCAO: ");
	char edit_option = getchar();

    if(edit_option != '\n')
        clear_buffer();
	
	edit_option = toupper(edit_option);
	
	if(edit_option == 'A'){
		if(edit_group.quant_products == MAX_ITENS_GROUP){
			printf("NUMERO MAXIMO DE ITENS DO GRUPO\nRETORNANDO AO MENU");
			fclose(p_arq);
			fclose(p_arq_products);
			return 0;
		}
		/*bloco de codigo para insercao de produtos no grupo*/
	}
	else if(edit_option == 'E'){
		
		printf("\nLISTA DE PRODUTOS DO GRUPO\n");
		printf("\nDigite 0 caso nao queira excluir o item");
		
		for(i = 0; i < MAX_ITENS_GROUP; i++){
			
			if(fseek(p_arq_products, (edit_group.id - 1) * sizeof(Products), SEEK_SET) != 0){
				printf("\nNao foi possivel posicionar o ponteiro do arquivc. Fechando programa.");
				fclose(p_arq);
				fclose(p_arq_products);
				exit(EXIT_FAILURE);
			}
			
			if(fread(&products_group, sizeof(Products), 1, p_arq_products)){
				printf("\nID:%.5ld | NOME : %s\tDIGITE O ID: ");
				scanf("%ld", &id_selecionado);
				
				if(id_selecionado == 0)
					continue;
				
				clear_buffer();
				printf("\nPara excluir item do grupo digite 'E'\n");
				char confirm_delete = getchar();
			
			    if(confirm_delete != '\n')
			        clear_buffer();
				
				confirm_delete = toupper(confirm_delete);
				
				if(confirm_delete == 'E'){
					for(j = 0; j < MAX_ITENS_GROUP; j++){
						temp_group[j].id_products[i] = edit_products.id_products[j];
						if(edit_group.id_products[j] == id_selecionado){
							
						}
					}//end for para encontrar id do grupo
					
				}
			}//end if fread
			else{
				printf("\n\nHouve um erro na leitura do arquivo. Fechando programa.\n");
				fclose(p_arq);
				fclose(p_arq_products);	
				exit(EXIT_FAILURE);
			}		
		}//end for
	}

	clear_buffer();
	printf("\nPara confirmar a alteracao digite 'C'\n");
	char validate_group = getchar();

    if(validate_group != '\n')
        clear_buffer();
	
	validate_group = toupper(validate_group);
	
	if(validate_group == 'C'){
	
		if(fseek(p_arq, (id - 1) * sizeof(Group), SEEK_SET) ==  0){
			if(fwrite(&edit_group, sizeof(Group), 1, p_arq)){
				printf("\nGravacao concluida com exito.\n");
				fclose(p_arq);
				return 0;
			}
			else{
				printf("\n\nHouve um erro na gravacao do arquivo. Fechando programa.\n");
				fclose(p_arq);
				exit(EXIT_FAILURE);
			}
		}
		else{
			printf("\nNao foi possivel posicionar o ponteiro do arquivc. Fechando programa.");
			fclose(p_arq);
			exit(EXIT_FAILURE);
		}
	}//end if
	else{
		printf("\nNao houve confirmacao do usuario, cancelando novo funcionario\n");
		fclose(p_arq);
		return 0;
	}//end else if 'C'
	
}//end function edit_itens_group
