#include "MODEL_MAIN.H"

int options_groups_products(){
	
	int flag_return, user_option;

	do{
	
		printf(" ----- MENU GRUPOS ----- \n\n");
		printf("[1] = LISTA DE GRUPOS\n[2] = NOVO GRUPO\n[3] = EDICAO DE GRUPOS DA INTERFACE\n");
		printf("[4] = ALTERAR PARAMETROS DO GRUPO\n[5] = VISUALIZAR GRUPO\n[6] = DESATIVAR GRUPO\n[7] = RETORNANDO AO MENU PRINCIPAL\n[8] = SAIR DO PROGRAMA\n\n");
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
				//flag_return = edit_interface_groups();
				if(flag_return == RETORNAR_MENU_PRINCIPAL)
					return 0;
				break;
			case 4: printf("\nINICIANDO ALTERAR ITENS DO GRUPO\n\n");
				flag_return = edit_element(KEY_GROUPS, NULL);
				if(flag_return == RETORNAR_MENU_PRINCIPAL)
					return 0;
				break;
			case 5: printf("\nINICIANDO VISUALIZAR GRUPO\n\n");
				flag_return = visualize_element(ARQ_GROUPS, KEY_GROUPS);
				if(flag_return == RETORNAR_MENU_PRINCIPAL)
					return 0;
				break;
			case 6: printf("\nINCIANDO DESATIVAR GRUPO ... \n");
				flag_return = desativate_element(KEY_GROUPS);
				if(flag_return == RETORNAR_MENU_PRINCIPAL)
					return 0;
				break;
			case 7: printf("\nRETORNANDO AO MENU PRINCIPAL ... \n\n");
				return RETORNAR_MENU_PRINCIPAL;
			case 8: printf("\nSAINDO DO PROGRAMA ... \n");
				return SAIR_PROGRAMA;
			default: printf("\nOPCAO INVALIDA ... \nDIGITE UMAS DAS OPCOES: [1] - [2] - [3] - [4] - [5] - [6] - [7]\n\n");
				break;//end default case
		}//end switch
	}while(user_option >= 1 && user_option <= 8);//end do-while

}//end function options_employees

int list_groups(){
	
	FILE *p_arq = fopen("groups.dat", "rb");
	Employee file_groups;
	long pag = 1;
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
		printf("\nNenhum grupo cadastrado.\n");
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
	
	long max_pags = tam_array / 20;
	if (tam_array % 20 != 0)
	    max_pags++;

	printf("\n----- LISTA DE GRUPOS ---- \t\t[%ld] NUMEROS DE PAGINA\n", max_pags);
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
				
				printf("\nPara vizualizar itens do grupo digite o ID do grupo\nCaso nao deseje vizualizar digite um valor menor ou igual a 0.\nDigite: \n\n");
				int id_group;
		
		        scanf("%d", &id_group);
				
				if(id_group > 0)
					itens_group(id_group);
				
				printf("\n\n----- Pagina %ld ----\n\n", pag);
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
		long pag = 1;
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
				//flag_return = price_filter(array, tam_array, max_pags);
					if(flag_return == RETORNAR_SUBMENU)
						return RETORNAR_SUBMENU;
					else if(flag_return == FILTRO_BEM_SUCEDIDO)
						return FILTRO_BEM_SUCEDIDO;
					else if(flag_return == RETORNAR_MENU_PRINCIPAL)
						return RETORNAR_MENU_PRINCIPAL;
				case 3: printf("\n----- LISTA DE GRUPOS ---- \t\t[%d] NUMEROS DE PAGINA\n", max_pags);
					printf("\n\n----- Pagina %d ----\n\n", pag);
				   	for(i = tam_array - 1; i >= 0; i--, contador++){
				   		
				   		printf("ID: %.6d | NOME: %s | QUANTIDADE DE PRODUTOS: %.3d | ", array[i].id, array[i].name, array[i].quant_products);
						printf(" STATUS: %s\n",array[i].status == ATIVO ? "ATIVO" : "INATIVO");
							
						if(contador % 20 == 0){
							clear_buffer();
							flag_return = walk_pags(&contador, &pag, max_pags);
							if(flag_return == RETORNAR_SUBMENU)
								return RETORNAR_SUBMENU;
							else if(flag_return == RETORNAR_FUNCAO)
								return RETORNAR_FUNCAO;
							printf("\n\n----- Pagina %ld ----\n\n", pag);
							i = ((tam_array - 1) - ((pag - 1) * 20)) + 1;//troca o valor do i para caminhar entre paginas
						}//end contador
					}//end for para impressao
					return FILTRO_BEM_SUCEDIDO;
				//case 4: flag_return = alphabetical_filter(array, tam_array, max_pags);
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
		long pag = 1;
		int max_pags = tam_array / 20;
			if (tam_array % 20 != 0)
			    max_pags++;
		//variables inactive_array
		size_t qtd_inactive_group = 0;
		
		for(i = 0; i < tam_array; i++){//for para preenchimento de vetor de produtos desativados
			if(array[i].status == INATIVO)
				qtd_inactive_group++;
		}
		long pag_inactive = 1;
		int max_pags_inactive = qtd_inactive_group / 20;
		if(qtd_inactive_group % 20 != 0)
			   max_pags++;
		size_t qtd_active_group = tam_array - qtd_inactive_group;
		
		long pag_active = 1;
		int max_pags_active = qtd_active_group / 20;
		if (qtd_active_group % 20 != 0)
			   max_pags_active++;
		
		
		printf("\nFILTRAR POR:\n\t[1] = ATIVO\n\t[2] = INATIVO\n\t[3] = AMBOS\n\t[4] = RETORNAR AO MENU SUBMENU\n\t[5] = RETORNAR AO MENU PRINCIPAL\n\nDIGITE A OPCAO DESEJADA: ");
		
		do{
			scanf("%d", &status_option);
		        
		    switch(status_option){
	        	case 1: if(qtd_active_group == 0){	
	        		printf("\nNAO HA GRUPOS ATIVOS NA LISTA\nRETORNANDO AO MENU SUBMENU\n");
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
	        			
        			for(i = 0; i < qtd_inactive_group; i++, contador++){
        				
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
	
	FILE *p_group = fopen(ARQ_GROUPS, "ab+");
	Group record_group;
	int loop = 0, i , j;
	char confirma;
	
	if(p_group == NULL){
		printf("\nNao foi possivel abrir o arquivo dos grupos. Fechando programa.");
		exit(EXIT_FAILURE);
	}
	
	do{		
		record_group.id = get_next_id(ARQ_GROUPS, KEY_GROUPS);
			
			clear_buffer();
			printf("DIGITE O NOME DO NOVO GRUPO: ");
			fgets(record_group.name, MAX_GROUP_NAME, stdin);
			record_group.name[strcspn(record_group.name, "\n")] = 0;
			if(loop = check_empty_text(record_group.name))
				continue;
			if(loop = check_burst_buffer(record_group.name, MAX_GROUP_NAME))
				continue;
			if(verify_duplicate_name(ARQ_GROUPS, KEY_GROUPS, record_group.name)){
				printf("\n[X] ERRO: GRUPO ja existe! Cadastro cancelado.\n");
				fclose(p_group);
			    return;
			}
			    
			if (check_similar_names(ARQ_GROUPS, KEY_GROUPS, record_group.name) > 0) {
			    printf("\nO nome '%s' parece com os itens acima.", record_group.name);
			    printf("\nDeseja cadastrar mesmo assim? [S/N]: ");
			    scanf(" %c", &confirma); 
			    clear_buffer(); // Limpa buffer
			
			    if (toupper(confirma) != 'S') {
			        printf("\nCadastro cancelado pelo usuario.\n");
			        fclose(p_group);
			        return;
			    }
			}
		
	}while(loop == 1);
	
	for(i = 0; i < MAX_ITENS_GROUP; i++){//insere valores -1 como valor de segurança
		record_group.id_products[i] = -1;
		record_group.sales_products[i] = -1;
	}
	record_group.quant_products = 0;
	record_group.status = ATIVO;
	
	printf("\nDeseja adcionar Produtos no grupo?\nDigite 'A' para começar a adcionar produtos!");
	scanf(" %c", &confirma);
	
	char view_list;
	long user_id;
	int flag_same_product;
	FILE *p_products = fopen(ARQ_PRODUCTS, "rb");
	Products product;
		
	if (toupper(confirma) == 'A') {
    	clear_buffer();
    	
    	if(p_products == NULL){
    		printf("\nNao foi possivel abrir o arquivo dos grupos. Fechando programa.");
			exit(EXIT_FAILURE);
		}
		
    	printf("\nCaso queira ver a lista de produtos digite 'L'\n"); 
		view_list = getchar();
		
		if(view_list != '\n')
    	    clear_buffer();
	
		view_list = toupper(view_list);
	
		if(view_list == 'L')
			list_products();
		
		printf("\nVoce devera digitar o ID do produto que deseja adcionar ao grupo, sendo no maximo 30 produtos!\n");
		printf("Caso nao queria adcionar mais produtos digite 0!\nID: ");
	
		for(i = 0; i < MAX_ITENS_GROUP; i++) {
    		printf("\nID do Produto: ");
    		scanf("%ld", &user_id);

    		if(user_id == 0) break;
			
			if(user_id < 0){
				printf("\nERRO: Valor invalido inserido pelo usuario!");
				user_id = 0;
				clear_buffer();
				i--;
				continue;
			}
			
			if(record_group.quant_products == MAX_ITENS_GROUP){
				printf("\nGrupo com numero maximo de itens atingido! Crie um novo grupo.");
				break;
			}
			
			flag_same_product = 0;
			
			if(fseek(p_products, (user_id - 1) * sizeof(Products), SEEK_SET) == 0 && fread(&product, sizeof(Products), 1, p_products) == 1){
       		 
				for(j = 0; j < MAX_ITENS_GROUP ; j++){//loop interno para checagem de produto ja inserido no grupo
					if(record_group.id_products[j] == product.id){
						printf("\nProduto ( ID %ld, %s ) ja existente no grupo", product.id, product.name);
						flag_same_product = true;
						break;
					}
				}//end for check same product in group
				if(flag_same_product == true){
					i--;
					continue;
				}
				
				record_group.id_products[i] = product.id;
				record_group.quant_products = record_group.quant_products + 1;
			}//END FSEEK
			else{
				if (feof(p_products)) {
		        	printf("\n[!] Produto ID %ld nao encontrado. (Fim do arquivo).\n", user_id);// Erro comum: O usuário digitou um ID muito alto que passou do limite do arquivo
			    }
				else if (ferror(p_products)){
			        printf("\n[X] ERRO CRITICO DE LEITURA no arquivo de produtos!\n");// Erro Crítico: O SO bloqueou a leitura ou o arquivo corrompeu
			        printf("Codigo do Sistema: %s\n", strerror(errno)); // Mostra o erro exato do Windows/Linux
			        
			        clearerr(p_products); // OBRIGATORIO: Limpa a flag de erro para o loop poder tentar ler o proximo!
			        
			    }
				else
			        printf("\n[!] Falha ao posicionar a busca no arquivo.\n");// O fseek que falhou (ex: arquivo vazio, ID negativo que escapou da validação)
			    
			    i--; // Volta uma casa no loop para o usuario tentar outro ID
			}
		}//end for
		
    }//caso o usuario digite A
    	
	clear_buffer();
	printf("\nPara confirmar o novo grupo digite 'C'\n");
	char validate_group = getchar();
	
	if(validate_group != '\n')
        clear_buffer();
	
	validate_group = toupper(validate_group);
	
	if(validate_group == 'C'){
	
		if(fwrite(&record_group, sizeof(Group), 1, p_group)){
			printf("\n\nGravacao concluida com exito\n\n");
			fclose(p_group);
			fclose(p_products);
			return;
		}
		else{
			printf("\n\nHouve um erro na gravacao do arquivo. Fechando programa.\n");
			fclose(p_group);
			fclose(p_products);
			exit(EXIT_FAILURE);
		}
	}
	else{
		printf("\nNao houve confirmacao do usuario, cancelando novo grupo\n");
		fclose(p_group);
		fclose(p_products);
		return;
	}
	
}//end function new_group

int edit_itens_group(int id){
	
	FILE *p_arq = fopen(ARQ_GROUPS, "rb+");
	Group edit_group;
	
	if(p_arq == NULL){
		printf("\nNao foi possivel abrir o arquivo. Fechando programa.");
		exit(EXIT_FAILURE);
	}
	
	if(fseek(p_arq, (id - 1) * sizeof(Group), SEEK_SET) == 0){
		if(fread(&edit_group, sizeof(Group), 1, p_arq) != 1){ 
			printf("\n\nHouve um erro na leitura do arquivo. Fechando programa.\n");
			fclose(p_arq);
			exit(EXIT_FAILURE);
		}
	}
	else{
		printf("\nNao foi possivel posicionar o ponteiro do arquivo. Fechando programa.");
		fclose(p_arq);
		exit(EXIT_FAILURE);
	}
	
	// CORREÇÃO: flag_return declarada aqui
	int i, j, flag_same_product, copy_flag = 0, flag_return;
	long id_selecionado;
	char confirm_delete, view_list;
	
	FILE *p_arq_product = fopen(ARQ_PRODUCTS, "rb");
	Products products_group;
		
	clear_buffer();
	printf("\nDIGITE 'A' PARA ADICIONAR ITENS NO GRUPO\nDIGITE 'E' PARA EXCLUIR ITENS  DO GRUPO\nOPCAO: ");
	char edit_option = getchar();

	if(edit_option != '\n') clear_buffer();
	
	edit_option = toupper(edit_option);
	
	if(edit_option == 'A'){
		if(edit_group.quant_products == MAX_ITENS_GROUP){
			printf("\nNUMERO MAXIMO DE ITENS DO GRUPO\nRETORNANDO AO SUBMENU");
			fclose(p_arq);
			fclose(p_arq_product);
			return 0;
		}
		
		printf("\nCaso queira ver a lista de produtos digite 'L'\n"); 
		view_list = getchar();
		
		if(view_list != '\n') clear_buffer();
	
		view_list = toupper(view_list);
	
		if(view_list == 'L'){
			flag_return = list_products();
			if(flag_return == RETORNAR_SUBMENU){
				fclose(p_arq);
				fclose(p_arq_product);
				return 0; // Ou RETORNAR_SUBMENU
			}
			else if(flag_return == RETORNAR_MENU_PRINCIPAL){
				fclose(p_arq);
				fclose(p_arq_product);
				return RETORNAR_MENU_PRINCIPAL;
			}
		}//end if 'L'
			
		printf("\nVoce devera digitar o ID do produto que deseja adicionar ao grupo, maximo %d!\n", (MAX_ITENS_GROUP - edit_group.quant_products));
		printf("Caso nao queira adicionar mais produtos digite 0!\n");
	
		for(i = 0; i < MAX_ITENS_GROUP; i++) {
			printf("ID do Produto: ");
			scanf("%ld", &id_selecionado);

			if(id_selecionado == 0) break;
			
			if(id_selecionado < 0){
				printf("\nERRO: Valor invalido inserido pelo usuario!\n");
				id_selecionado = 0;
				clear_buffer();
				i--;
				continue;
			}
			
			if(edit_group.quant_products == MAX_ITENS_GROUP){
				printf("\nGrupo com numero maximo de itens atingido! Crie um novo grupo.");
				break;
			}
			
			flag_same_product = 0;
				
			if(fseek(p_arq_product, (id_selecionado - 1) * sizeof(Products), SEEK_SET) == 0 && fread(&products_group, sizeof(Products), 1, p_arq_product) == 1){
				
				for(j = 0; j < MAX_ITENS_GROUP ; j++){
					if(edit_group.id_products[j] == products_group.id){
						printf("\nProduto ( ID %ld, %s ) ja existente no grupo\n", products_group.id, products_group.name);
						flag_same_product = 1; // CORREÇÃO: trocado true por 1
						break;
					}
				}
				if(flag_same_product == 1){ // CORREÇÃO: trocado true por 1
					i--;
					continue;
				}
				
				edit_group.id_products[edit_group.quant_products] = products_group.id;
				edit_group.quant_products++;
				printf("\n[+] Produto adicionado com sucesso!\n");
			}//END FSEEK
			else{
				if (feof(p_arq_product)) {
					printf("\n[!] Produto ID %ld nao encontrado. (Fim do arquivo).\n", id_selecionado);
				}
				else if (ferror(p_arq_product)){
					printf("\n[X] ERRO CRITICO DE LEITURA no arquivo de produtos!\n");
					printf("Codigo do Sistema: %s\n", strerror(errno)); 
					clearerr(p_arq_product); 
				}
				else {
					printf("\n[!] Falha ao posicionar a busca no arquivo.\n");
				}
				i--; 
			}
		}//end for
	}
	
	else if(edit_option == 'E'){
		
		if (edit_group.quant_products == 0) {
			printf("\nO grupo esta vazio! Nao ha itens para excluir.\n");
			fclose(p_arq);
			fclose(p_arq_product);
			return 0;
		}

		printf("\n----- LISTA DE PRODUTOS DO GRUPO -----\n");
		for(i = 0; i < edit_group.quant_products; i++){ 
			long id_atual = edit_group.id_products[i];
			
			if(fseek(p_arq_product, (id_atual - 1) * sizeof(Products), SEEK_SET) == 0){
				if(fread(&products_group, sizeof(Products), 1, p_arq_product)){
					printf("ID: %.6ld | NOME: %s\n", products_group.id, products_group.name);
				}
			}
		}
		
		printf("\nDIGITE O ID DO PRODUTO QUE DESEJA EXCLUIR (ou 0 para sair): ");
		scanf("%ld", &id_selecionado);
		
		if(id_selecionado != 0){
			clear_buffer();
			printf("\nPara confirmar a exclusao do item digite 'E': ");
			confirm_delete = toupper(getchar());
		
			if(confirm_delete != '\n') clear_buffer();
			
			if(confirm_delete == 'E'){
				
				int posicao_encontrada = -1;
				
				for(j = 0; j < edit_group.quant_products; j++){
					if(edit_group.id_products[j] == id_selecionado){
						posicao_encontrada = j;
						break;
					}
				}
				
				if(posicao_encontrada != -1){
					for(j = posicao_encontrada; j < edit_group.quant_products - 1; j++){
						edit_group.id_products[j] = edit_group.id_products[j + 1];
						edit_group.sales_products[j] = edit_group.sales_products[j + 1];
					}
					
					edit_group.id_products[edit_group.quant_products - 1] = -1;
					edit_group.sales_products[edit_group.quant_products - 1] = -1;
					edit_group.quant_products--;
					
					printf("\n[+] Produto removido do grupo com sucesso!\n");
				}
				else {
					printf("\n[!] Produto nao pertence a este grupo.\n");
				}
			}
		}
	}
	
	fclose(p_arq_product);	
	
	clear_buffer();
	printf("\nPara confirmar a alteracao no grupo digite 'C': ");
	char validate_group = getchar();

	if(validate_group != '\n') clear_buffer();
	
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
			printf("\nNao foi possivel posicionar o ponteiro do arquivo. Fechando programa.");
			fclose(p_arq);
			exit(EXIT_FAILURE);
		}
	}
	else{
		printf("\nNao houve confirmacao do usuario, cancelando alteracao.\n");
		fclose(p_arq);
		return 0;
	}
}//end function edit_itens_group