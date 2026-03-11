#include "MODEL_MAIN.H"

int options_product(){
	
	int flag_return, user_option;

	do{
	
		printf(" ----- MENU PRODUTOS ----- \n\n");
		printf("[1] = LISTA DE PRODUTOS\n[2] = NOVO PRODUTO\n[3] = DESATIVAR PRODUTO\n[4] = ALTERAR PRODUTO\n");
		printf("[5] = VISUALIZAR PRODUTO\n[6] = RETORNAR AO MENU PRINCIPAL\n[7] = SAIR DO PROGRAMA\n\n");
		printf("DIGITE A OPCAO DESEJADA: ");
		scanf("%d", &user_option);
		
		switch(user_option){
			case 1: printf("\nINCIANDO LISTA DE PRODUTOS ... \n");
				flag_return = list_products();
				if(flag_return == RETORNAR_MENU_PRINCIPAL)
					return 0;
				break;//end case 1
			case 2: printf("\nINCIANDO NOVO PRODUTO ... \n\n");
				new_product();
				break;//end case 2
			case 3: printf("\nINCIANDO DESATIVAR PRODUTO ... \n");
				flag_return = desativate_product();
				if(flag_return == RETORNAR_MENU_PRINCIPAL)
					return 0;
				break;
			case 4: printf("\nINICIANDO ALTERAR PRODUTO\n\n");
				flag_return = edit_product();
				if(flag_return == RETORNAR_MENU_PRINCIPAL)
					return 0;
				break;//end case 4
			case 5:
				printf("\nINCINADO VISUALIZAR PRODUTO\n\n");
				flag_return = search_product();
				if(flag_return == RETORNAR_MENU_PRINCIPAL)
					return 0;
				break;//end case 4
			case 6: printf("\nRETORNANDO AO MENU PRINCIPAL ... \n\n");
				return 0;
			case 7: printf("\nSAINDO DO PROGRAMA ... \n");
				return SAIR_PROGRAMA; 
			default: printf("\nOPCAO INVALIDA ... \nDIGITE UMAS DAS OPCOES: [1] - [2] - [3] - [4] - [5] - [6] - [7]\n\n");
				break;//end default case
		}//end switch
	}while(user_option >= 1 && user_option <= 7);//end do-while

}//end function options_product

int list_products(){
	
	FILE *products_p = fopen(ARQ_PRODUCTS, "rb");
	long pag = 1;
	int filter_option, contador = 1, flag_return;
	char flag_filter;
	
	if(products_p == NULL){//file failure open check
		printf("\nNao foi possivel abrir o arquivo. Fechando programa.");
		exit(EXIT_FAILURE);
	}
	
	//variaveis auxiliares para alocação dinamica
	long tam_bytes_arq;
	size_t tam_array = 0, i = 0;
	
	fseek(products_p, 0, SEEK_END);
	
	if(ftell(products_p) != 0){
		tam_bytes_arq = ftell(products_p);
		tam_array = (size_t)tam_bytes_arq / sizeof(Products);
	}
	else{
		printf("\nNenhum produto cadastrado.\n");
    	fclose(products_p);
    	return 0;
	}
	
	Products *products_array = malloc(tam_array * sizeof(Products));
	
	if(products_array == NULL){
		printf("\nNao foi possivel alocar memoria.Verifique a capacidade maxima de RAM do computador\n");
		printf("\nFechando programa.");
		fclose(products_p);
		exit(EXIT_FAILURE);
	}
	
	rewind(products_p);
	
	tam_array = fread(products_array, sizeof(Products), tam_array, products_p);
	
	fclose(products_p);
	
	long max_pags = tam_array / 20;
	if (tam_array % 20 != 0)
	    max_pags++;
	
	
	printf("\n----- LISTA DE PRODUTOS ---- \t\t[%ld] NUMEROS DE PAGINA\n", max_pags);
	printf("\n\n----- Pagina %ld ----\n\n", pag);
	
   	for(i = 0; i < tam_array; i++, contador++){
   		
   		printf("ID: %.6ld | NOME: %s | PRECO: %.2f | PRECO_COMPRA: %.2f | ESTOQUE: %d |  ", products_array[i].id, products_array[i].name, products_array[i].sale_price, products_array[i].purchase_price, products_array[i].stock);
		printf("STATUS: %s\n", products_array[i].status == ATIVO ? "ATIVO" : "INATIVO");
			
		if(contador % 20 == 0 && i + 1 != tam_array){
			clear_buffer();
			flag_return = walk_pags(&contador, &pag, max_pags);
			if(flag_return == RETORNAR_SUBMENU){
				printf("\nRETORNANDO AO SUBMENU...\n");
				free(products_array);
				return RETORNAR_SUBMENU;
			}
			else if(flag_return == RETORNAR_MENU_PRINCIPAL){
				printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
				free(products_array);
				return RETORNAR_MENU_PRINCIPAL;
			}	
			else if(flag_return == RETORNAR_FUNCAO)
				printf("\nFuncao Lista de Produtos.\n");
				
				clear_buffer();
				printf("\nPara acessar o painel de filtros digite 'F'");
				i = ((pag - 1) * 20) - 1;//troca o valor do i para caminhar entre paginas
				flag_filter = getchar();

	            if(flag_filter != '\n') 
	            	clear_buffer();
				
	        	flag_filter = toupper(flag_filter);
	        	
	        	if(flag_filter == 'F'){
	        		
	        		flag_return = filters(products_array, tam_array);
        			if(flag_return == RETORNAR_SUBMENU){
						printf("\nRETORNANDO AO MENU SUBMENU...\n\n");
						free(products_array);
						return RETORNAR_SUBMENU;	
					}
					else if(flag_return == RETORNAR_FUNCAO)
						printf("\nFuncao Lista de Produtos.\n");
					else if(flag_return == RETORNAR_MENU_PRINCIPAL){
						free(products_array);
						return RETORNAR_MENU_PRINCIPAL;
					}	
        			else if(flag_return == FILTRO_BEM_SUCEDIDO){
        				printf("\n--- Fim dos registros. Saindo da funcao\n\n");
        				free(products_array);
        				return 0;
					}
				}//if 'F'		
				printf("\n\n----- Pagina %ld ----\n\n", pag);
		}//end contador	

	}//end for para impressao da lista
   	printf("\n--- Fim dos registros.\n\n");
   	free(products_array);
	return 0;//retorna a ultima função
		
}//end function list_product

	int filters(Products array[], size_t tam_array){
		
		int option_filter, option_filter_intern, flag_return, contador;
		long i;
		
		//variables og_array
		long pag = 1;
		long max_pags = tam_array / 20;
			if (tam_array % 20 != 0)
			    max_pags++;
		           
		printf("\nFILTRAR POR:\n\t[1] = ATIVO\\INATIVO\n\t[2] = PRECO.COMPRA\n\t[3] = ID.DECRESCENTE\n\t[4] = ORDEM.ALFABETICA\n\t[5] = RETORNAR A FUNCAO ANTERIOR\n\t[6] = RETORNAR AO MENU SUBMENU\n\t[7] = RETORNAR AO MENU PRINCIPAL\n\nDIGITE A OPCAO DESEJADA: ");
		do{
			scanf("%d", &option_filter);
			
			switch(option_filter){
				case 1:
				flag_return = status_filter(array, tam_array);
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
				case 3: printf("\n----- LISTA DE PRODUTOS ---- \t\t[%ld] NUMEROS DE PAGINA\n", max_pags);
					printf("\n\n----- Pagina %ld ----\n\n", pag);
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
							printf("\n\n----- Pagina %ld ----\n\n", pag);
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

		int status_filter(Products array[], size_t tam_array){
			
			size_t i, j;
			int status_option, contador = 1, flag_return, flag_filter;
			
			//variables og_array
			long pag = 1;
			long max_pags = tam_array / 20;
			if (tam_array % 20 != 0)
			    max_pags++;
			//variables inactive_array
			size_t qtd_inactive_product = 0;
			
			for(i = 0; i < tam_array; i++){//for para preenchimento de vetor de produtos desativados
				if(array[i].status == INATIVO)
					qtd_inactive_product++;
			}
			long pag_inactive = 1;
			long max_pags_inactive = qtd_inactive_product / 20;
			if(qtd_inactive_product % 20 != 0)
				   max_pags_inactive++;
			size_t qtd_active_product = tam_array - qtd_inactive_product;
			
			long pag_active = 1;
			long max_pags_active = qtd_active_product / 20;
			if (qtd_active_product % 20 != 0)
				   max_pags_active++;
		
			printf("\nFILTRAR POR:\n\t[1] = ATIVO\n\t[2] = INATIVO\n\t[3] = AMBOS\n\t[4] = RETORNAR AO MENU SUBMENU\n\t[5] = RETORNAR AO MENU PRINCIPAL\n\nDIGITE A OPCAO DESEJADA: ");
			
			do{
				scanf("%d", &status_option);
			        
			    switch(status_option){
		        	case 1: if(qtd_active_product == 0){	
		        		printf("\nNAO HA PRODUTOS ATIVOS NA LISTA\nRETORNANDO AO MENU SUBMENU\n");
		        		return RETORNAR_SUBMENU;
						}
						printf("\n----Lista filtro ATIVO---- \t\t[%ld] NUMEROS DE PAGINA\n", max_pags_active);
						printf("\n\n----- Pagina %ld ----\n\n", pag_active);
		        		Products *products_active = malloc(qtd_active_product * sizeof(Products));
		        		
		        		j = 0;
		        		
		      			for(i = 0; i < tam_array; i++){
	        				if(array[i].status == ATIVO){
	        					products_active[i] = array[i];
	        					j++;
							}
        				}//end for para preenchimento do vetor de ativos
		        		
		        		for(i = 0; i < qtd_active_product; i++, contador++){
		        					
							printf("ID: %.6ld | NOME: %s | PRECO: %.2f | PRECO-COMPRA: %.2f | ESTOQUE: %d | STATUS: ATIVO\n", products_active[i].id, products_active[i].name, products_active[i].sale_price, products_active[i].purchase_price, products_active[i].stock);
						
							if(contador % 20 == 0 && i + 1 != qtd_active_product){
								clear_buffer(); 
								flag_return = walk_pags(&contador, &pag_active, max_pags_inactive);
								if(flag_return == RETORNAR_SUBMENU){
									free(products_active);
									return RETORNAR_SUBMENU;
								}
									
								else if(flag_return == RETORNAR_FUNCAO)
									printf("\nFuncao Lista de Produtos > Filtro de Status.\n");
								printf("\n\n----- Pagina %ld ----\n\n", pag_active);
								i = ((pag_active - 1) * 20) - 1;//troca o valor do i para caminhar entre paginas
							}//end contador
							
						}//end for para impressao
							
						free(products_active);
						printf("\n-------------------\n");
											
						return FILTRO_BEM_SUCEDIDO;
		        	case 2: if(qtd_inactive_product == 0){	
		        		printf("\nNAO HA PRODUTOS INATIVOS NA LISTA\nRETORNANDO AO MENU SUBMENU\n");
		        		return RETORNAR_SUBMENU;
						}
					
					 	printf("\n----Lista filtro INATIVO----\t\t[%ld] NUMEROS DE PAGINA\n", max_pags_inactive);
						printf("\n\n----- Pagina %ld ----\n\n", pag_inactive);
		        		Products *products_inactive = malloc(qtd_inactive_product * sizeof(Products));
		        		
		        		j = 0;
		        		
		      			for(i = 0; i < tam_array; i++){
	        				if(array[i].status == INATIVO){
	        					products_inactive[i] = array[i];
	        					j++;
							}
        				}//end for para preenchimento do vetor de inativos
		        		
	        			for(i = 0; i < qtd_inactive_product; i++, contador++){
	        				
							printf("ID: %.6ld | NOME: %s | PRECO: %.2f | PRECO-COMPRA: %.2f | ESTOQUE: %d | STATUS: INATIVO\n", products_inactive[i].id, products_inactive[i].name, products_inactive[i].sale_price, products_inactive[i].purchase_price, products_inactive[i].stock);
								
							if(contador % 20 == 0 && i + 1 != qtd_inactive_product){
								clear_buffer();
								flag_return = walk_pags(&contador, &pag_inactive, max_pags_inactive);
								if(flag_return == RETORNAR_SUBMENU){
									free(products_inactive);
									return RETORNAR_SUBMENU;
								}
									
								else if(flag_return == RETORNAR_FUNCAO)
									printf("\nFuncao Lista de Produtos > Filtro de Status.\n");
								printf("\n\n----- Pagina %ld ----\n\n", pag_inactive);
								i = ((pag_inactive - 1) * 20) - 1;//troca o valor do i para caminhar entre paginas
							}//end contador
								
	        			}//end for para impressao		
						
						free(products_inactive);
						printf("\n-------------------\n");
	        			return FILTRO_BEM_SUCEDIDO;
		        	case 3: printf("\n----Lista AMBOS Status---- \t\t[%ld] NUMEROS DE PAGINA\n", max_pags);
						printf("\n\n----- Pagina %ld ----\n\n", pag);
						for(i = 0; i < tam_array; i++, contador++){
			        		
			        		printf("ID: %.6ld | NOME: %s | PRECO: %.2f | PRECO_COMPRA: %.2f | ESTOQUE: %d |", array[i].id, array[i].name, array[i].sale_price, array[i].purchase_price, array[i].stock);
							printf(" STATUS: %s\n",array[i].status == ATIVO ? "ATIVO" : "INATIVO");
							
							if(contador % 20 == 0 && i + 1 != tam_array){
								clear_buffer();
								flag_return = walk_pags(&contador, &pag, max_pags);
								if(flag_return == RETORNAR_SUBMENU)
									return RETORNAR_SUBMENU;
								else if(flag_return == RETORNAR_FUNCAO)
									printf("\nFuncao Lista de Produtos > Filtro de Status.\n");	
								printf("\n\n----- Pagina %ld ----\n\n", pag);
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
	
		int price_filter(Products array[], size_t tam_array, long max_pags){
		
			int order_option, contador = 1, flag_return;
			size_t i;
			long pag = 1;
			
			printf("\nFILTRAR EM ORDEM:\n\t[1] = CRESCENTE\n\t[2] = DECRESCENTE\n\t[3] = RETORNAR AO MENU SUBMENU\n\t[4] = RETORNAR AO MENU PRINCIPAL\n\nDIGITE A OPCAO DESEJADA: ");
			
			do{
				scanf("%d", &order_option);
				clear_buffer();
				
				switch(order_option){
					case 1:	qsort(array, tam_array, sizeof(Products), comparar_sale_price_cre);
						printf("\n----- LISTA DE PRODUTOS ---- \t\t[%ld] NUMEROS DE PAGINA\n", max_pags);
						printf("\n\n----- Pagina %ld ----\n", pag);
						
						for(i = 0; i < tam_array; i++, contador++){
				        		
			        		printf("ID: %.6ld | NOME: %s | PRECO: %.2f | PRECO_COMPRA: %.2f | ESTOQUE: %d | STATUS: %s\n", array[i].id, array[i].name, array[i].sale_price, array[i].purchase_price, array[i].stock);
							printf("STATUS: %s\n", array[i].status == ATIVO ? "ATIVO" : "INATIVO");
							if(contador % 20 == 0){
								flag_return = walk_pags(&contador, &pag, max_pags);
								if(flag_return == RETORNAR_SUBMENU)
									return RETORNAR_SUBMENU;
								else if(flag_return == RETORNAR_FUNCAO)
									printf("\nFuncao Lista de Produtos > Filtro de Preco.\n");
								printf("\n\n----- Pagina %ld ----\n\n", pag);
								i = ((pag - 1) * 20) - 1;//troca o valor do i para caminhar entre paginas
							}//end contador
									
						}//end for para impressao
						return FILTRO_BEM_SUCEDIDO;
						
					case 2:	qsort(array, tam_array, sizeof(Products), comparar_sale_price_dec);
					
						printf("\n----- LISTA DE PRODUTOS ---- \t\t[%ld] NUMEROS DE PAGINA\n", max_pags);
						printf("\n\n----- Pagina %ld ----\n", pag);
						
						for(i = 0; i < tam_array; i++, contador++){
				        		
				        		printf("ID: %.6ld | NOME: %s | PRECO: %.2f | PRECO_COMPRA: %.2f | ESTOQUE: %d | STATUS: %s\n", array[i].id, array[i].name, array[i].sale_price, array[i].purchase_price);
								printf("STATUS: %s\n", array[i].status == ATIVO ? "ATIVO" : "INATIVO");
								if(contador % 20 == 0){
									flag_return = walk_pags(&contador, &pag, max_pags);
									if(flag_return == RETORNAR_SUBMENU)
										return RETORNAR_SUBMENU;
									else if(flag_return == RETORNAR_FUNCAO)
										printf("\nFuncao Lista de Produtos > Filtro de Preco.\n");
									printf("\n\n----- Pagina %ld ----\n\n", pag);
									i = ((pag - 1) * 20) - 1;//troca o valor do i para caminhar entre paginas
								}//end contador
									
							}//end for para impressao
						return FILTRO_BEM_SUCEDIDO;
					case 3: return RETORNAR_SUBMENU;
					case 4: return RETORNAR_MENU_PRINCIPAL;
					default: printf("\nOPCAO INVALIDA ...\nDIGITE UMAS DAS OPCOES: [1] - [2] - [3] - [4]\n\n");
						break;
				}//end swicth order_option
				
			}while(order_option >= 1 && order_option <= 4);//end while switch(order_option)
		
		}//end function price_filters
	
		int comparar_sale_price_cre(const void *p1, const void *p2){
			
			const Products *price_1 = (Products *)p1;
			const Products *price_2 = (Products *)p2;
			
			if (price_1->sale_price < price_2->sale_price) return -1; //p1 vem antes
		    if (price_1->sale_price > price_2->sale_price) return 1;  //p1 vem depois
		    return 0;//São iguais
		}//end function comparar_prices_cre
	
		int comparar_sale_price_dec(const void *p1, const void *p2){
		    const Products *price_1 = (const Products *)p1;
		    const Products *price_2 = (const Products *)p2;
		    
		    if (price_1->sale_price < price_2->sale_price) return 1;  //p2(maior) sobe na lista
		    if (price_1->sale_price > price_2->sale_price) return -1; //p1(maior) fica no topo
		    return 0;
		}//end function comparar_prices_dec

	int alphabetical_filter(Products array[], size_t tam_array, long max_pags){
		
		int contador = 1, flag_return;
		long i, pag = 1;
		
		qsort(array, tam_array, sizeof(Products), comparar_nomes);
	
		printf("\n----- LISTA DE PRODUTOS ---- \t\t[%ld] NUMEROS DE PAGINA\n", max_pags);
		printf("\n\n----- Pagina %ld ----\n", pag);
		for(i = 0; i < tam_array; i++, contador++){
	
			printf("ID: %.6ld | NOME: %s | PRECO: %.2f | PRECO_COMPRA: %.2| ESTOQUE: %d |", array[i].id, array[i].name, array[i].sale_price, array[i].purchase_price, array[i].stock);
			printf("STATUS: %s\n", array[i].status == ATIVO ? "ATIVO" : "INATIVO");
			
			if(contador % 20 == 0){
				flag_return = walk_pags(&contador, &pag, max_pags);
				clear_buffer();
				if(flag_return == RETORNAR_SUBMENU)
					return RETORNAR_SUBMENU;
				else if(flag_return == RETORNAR_FUNCAO)
					printf("\nFuncao Lista de Produtos > Filtro de Ordem Alfabetica.\n");
				printf("\n\n----- Pagina %ld ----\n\n", pag);
				i = ((pag - 1) * 20) - 1;//troca o valor do i para caminhar entre paginas
			}//end contador
	
		}//end for para impressao
		return FILTRO_BEM_SUCEDIDO;
	}//end function alphabetical_filter

		int comparar_nomes(const void *n1, const void *n2){
			
			const Products *nome_1 = (Products *)n1;
			const Products *nome_2 = (Products *)n2;
			
			return _stricmp(nome_1->name, nome_2->name);
		}//end function comparar_nomes

void new_product(){
	
	FILE *arq_product = fopen(ARQ_PRODUCTS, "ab+");
	Products p;
	int loop = 0;

	if(arq_product){
		//verificações do nome do produto
		do{
			p.id = get_next_id(ARQ_PRODUCTS, KEY_PRODUCTS);
			
			clear_buffer();
			printf("DIGITE O NOME DO NOVO PRODUTO: ");
			fgets(p.name, MAX_PRODUCT_NAME, stdin);
			p.name[strcspn(p.name, "\n")] = 0;
			if(loop = check_empty_text(p.name))
				continue;
			if(loop = check_burst_buffer(p.name, MAX_PRODUCT_NAME))
				continue;
			if(verify_duplicate_name_product(p.name)){
				printf("\n[X] ERRO: Produto ja existe! Cadastro cancelado.\n");
				fclose(arq_product);
			    return;
			}
			    
			if (check_similar_names_product(p.name) > 0) {
			    char confirma;
			    printf("\nO nome '%s' parece com os itens acima.", p.name);
			    printf("\nDeseja cadastrar mesmo assim? [S/N]: ");
			    scanf(" %c", &confirma); 
			    clear_buffer(); // Limpa buffer
			
			    if (toupper(confirma) != 'S') {
			        printf("\nCadastro cancelado pelo usuario.\n");
			        fclose(arq_product);
			        return;
			    }
			}
		}while(loop == 1);
		//verificações do preço do produto
		do{
			printf("\nDIGITE O PRECO DE VENDA DO PRODUTO: ");
			scanf("%f", &p.sale_price);
			loop = validate_price(p.sale_price);
		}while(loop == 1);
		
		printf("\nDIGITE O PRECO DE COMPRA DO PRODUTO: ");
		scanf("%f", &p.purchase_price);
		if(p.purchase_price <= 0)
			p.purchase_price = 0;
			
		printf("\nDIGITE O ESTOQUE DO PRODUTO: ");
		scanf("%d", &p.stock);
		if(p.stock <= 0)
			p.stock = 0;
		
		p.status = ATIVO;
		p.group = 0;
		
		clear_buffer();
		printf("\nPara confirmar o novo produto digite 'C'\n");
		char validate_product = getchar();

        if(validate_product != '\n')
            clear_buffer();
		
    	validate_product = toupper(validate_product);
    	
    	if(validate_product == 'C'){
    		if(fwrite(&p, sizeof(Products), 1, arq_product)){
				printf("\n\nGravacao concluida com exito\n\n");
				fclose(arq_product);
				return;
			}
			else{
				printf("\n\nHouve um erro na gravacao do arquivo. Fechando programa.\n");
				exit(EXIT_FAILURE);
			}			
		}//end if
		else{
			printf("\nNao houve confirmacao do usuario, cancelando novo produto\n");
			fclose(arq_product);
			return;
		}
				
	}//end if arq_product
	else{
		printf("Nao foi possivel criar o arquivo! fechando o programa!\n");
		exit(EXIT_FAILURE);
		}//end else
}//end fuction new_product

int desativate_product(){
	
	long id;
	int search_option;
	
	printf("\nQUAL PRODUTO DESEJA ALTERAR?");
	printf("\n[1] = BUSCAR POR ID\n[2] = BUSCAR PELA LISTA\n[3] = BUSCAR POR NOME\n[4] = RETORNAR AO MENU PRODUTOS\n[5] = RETORNAR AO MENU PRINCIPAL\n\nDIGITE A OPCAO DESEJADA: ");
	
	do{
		scanf("%d", &search_option);
		
		switch(search_option){
			case 1: id = search_id_generic(ARQ_PRODUCTS, KEY_PRODUCTS);
				if(id == 0){
					printf("\nPRODUTO NAO ENCONTRADO. RETORNANDO AO MENU PRODUTOS...\n\n");
					return 0;
				}//end if(id == 0)
				
				edit_status(ARQ_PRODUCTS, KEY_PRODUCTS, id);
				printf("\nPRODUTO DESATIVADO COM SUCESSO\n\nRETORNANDO AO MENU PRODUTOS...\n\n");
					return 0;				
			case 2: id = search_id_generic_list(KEY_PRODUCTS);
			
				if(id == 0){
					printf("\nPRODUTO NAO ENCONTRADO. RETORNANDO AO MENU PRODUTOS...\n\n");
					return 0;
				}//end if(id == 0)
				if(id == RETORNAR_SUBMENU){
					printf("\nRETORNANDO AO MENU PRODUTOS...\n");
					return RETORNAR_SUBMENU;
				}//end if(id == 0)
				if(id == RETORNAR_MENU_PRINCIPAL){
					printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
					return RETORNAR_MENU_PRINCIPAL;
				}//end if(id == 0)
				edit_status(ARQ_PRODUCTS, KEY_PRODUCTS, id);
				printf("\nPRODUTO DESATIVADO COM SUCESSO\n\nRETORNANDO AO MENU PRODUTOS...\n\n");
					return 0;		
			case 3: id = search_name_product();
			
				if(id == 0){
					printf("\nPRODUTO NAO ENCONTRADO. RETORNANDO AO MENU PRODUTOS...\n\n");
					return RETORNAR_SUBMENU;
				}//end if(id == 0)
			
				edit_status(ARQ_PRODUCTS, KEY_PRODUCTS, id);
				printf("\nPRODUTO DESATIVADO COM SUCESSO\n\nRETORNANDO AO MENU PRODUTOS...\n\n");
					return 0;		
			case 4: printf("\nRETORNANDO AO MENU PRODUTOS...\n");
				return RETORNAR_SUBMENU;
			case 5: printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
				return RETORNAR_MENU_PRINCIPAL;
			default:  printf("\nOPCAO INVALIDA ...\nDIGITE UMAS DAS OPCOES: [1] - [2] - [3] - [4] - [5]\n\n");
				break;			
		}//end switch option_search
		
	}while(search_option >= 1 && search_option <= 5);//end do-while switch(search_option)
	
}//end function desativate_product

int edit_product(){
	
	long id;
	int search_option, edit_option, loop;
	
	printf("QUAL PRODUTO DESEJA ALTERAR?");
	printf("\n[1] = BUSCAR POR ID\n[2] = BUSCAR PELA LISTA\n[3] = BUSCAR POR NOME\n[4] = RETORNAR AO MENU PRODUTOS\n[5] = RETORNAR AO MENU PRINCIPAL\n\nDIGITE A OPCAO DESEJADA: ");
	
	do{
		scanf("%d", &search_option);
		
		switch(search_option){
			
			case 1:
				id = search_id_generic(ARQ_PRODUCTS, KEY_PRODUCTS);
				
				if(id == 0){
					printf("\nPRODUTO NAO ENCONTRADO. RETORNANDO AO MENU PRODUTOS...\n\n");
					return 0;
				}//end if(id == 0)
				
				printf("\nQUAL PARAMETRO DO PRODUTO DESEJA ALTERAR?");
				printf("\n\t[1] = NOME\n\t[2] = PRECO DE VENDA\n\t[3] = PRECO DE COMPRA\n\t[4] = ESTOQUE\n\t[5] = STATUS\n\t[6] = TUDO\n\t[7] = RETORNAR AO MENU PRODUTOS\n\t[8] = RETORNAR AO MENU PRINCIPAL\n\nDIGITE A OPCAO DESEJADA: ");
				scanf("%d", &edit_option);
				
				do{	
					switch(edit_option){
						case 1: edit_name_product(id);	
							return 0;
						case 2: edit_sale_price_product(id);
							return 0;
						case 3: edit_purchase_price_product(id);
							return 0;
						case 4: edit_stock_product(id);
							return 0;
						case 5: edit_status(ARQ_PRODUCTS, KEY_PRODUCTS, id);
							return 0;
						case 6: edit_name_product(id);
							edit_sale_price_product(id);
							edit_purchase_price_product(id);
							edit_stock_product(id);
							edit_status(ARQ_PRODUCTS, KEY_PRODUCTS, id);
							return 0;
						case 7: printf("\nRETORNANDO AO MENU PRODUTOS...\n");
							return RETORNAR_SUBMENU;
						case 8:	printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
							return RETORNAR_MENU_PRINCIPAL;	
						default: printf("\nOPCAO INVALIDA ... \nDIGITE UMAS DAS OPCOES: [1] - [2] - [3] - [4] - [5] - [6] - [7] - [8]\n\n");
							break;
					}//end switch edit_option					
				}while(edit_option >= 0 && edit_option <= 8);
				
				break;//break case 1 (search_option)
			case 2: id = search_id_generic_list(KEY_PRODUCTS);
			
				if(id == 0){
					printf("\nPRODUTO NAO ENCONTRADO. RETORNANDO AO MENU PRODUTOS...\n\n");
					return 0;
				}//end if(id == 0)
				if(id == RETORNAR_SUBMENU){
					printf("\nRETORNANDO AO MENU PRODUTOS...\n");
					return RETORNAR_SUBMENU;
				}//end if(id == 0)
				if(id == RETORNAR_MENU_PRINCIPAL){
					printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
					return RETORNAR_MENU_PRINCIPAL;
				}//end if(id == 0)
					
				printf("QUAL PARAMETRO DO PRODUTO DESEJA ALTERAR?\n");
				printf("\n\t[1] = NOME\n\t[2] = PRECO DE VENDA\n\t[3] = PRECO DE COMPRA\n\t[4] = ESTOQUE\n\t[5] = STATUS\n\t[6] = TUDO\n\t[7] = RETORNAR AO MENU PRODUTOS\n\t[8] = RETORNAR AO MENU PRINCIPAL\n\nDIGITE A OPCAO DESEJADA: ");
				scanf("%d", &edit_option);
				
				do{	
					switch(edit_option){
						case 1: edit_name_product(id);	
							return 0;
						case 2: edit_sale_price_product(id);
							return 0;
						case 3: edit_purchase_price_product(id);
							return 0;
						case 4: edit_stock_product(id);
							return 0;
						case 5: edit_status(ARQ_PRODUCTS, KEY_PRODUCTS, id);
							return 0;
						case 6: edit_name_product(id);
							edit_sale_price_product(id);
							edit_purchase_price_product(id);
							edit_stock_product(id);
							edit_status(ARQ_PRODUCTS, KEY_PRODUCTS, id);
							return 0;
						case 7: printf("\nRETORNANDO AO MENU PRODUTOS...\n");
							return RETORNAR_SUBMENU;
						case 8:	printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
							return RETORNAR_MENU_PRINCIPAL;	
						default: printf("\nOPCAO INVALIDA ... \nDIGITE UMAS DAS OPCOES: [1] - [2] - [3] - [4] - [5] - [6] - [7] - [8]\n\n");
							break;
					}//end switch edit_option					
				}while(edit_option >= 0 && edit_option <= 8);
					
				break;//break case 2 (search_option)
			case 3: id = search_name_product();
			
				if(id == 0){
					printf("\nPRODUTO NAO ENCONTRADO. RETORNANDO AO MENU PRODUTOS...\n\n");
					return RETORNAR_SUBMENU;
				}//end if(id == 0)
				
				printf("\nQUAL PARAMETRO DO PRODUTO DESEJA ALTERAR?");
				printf("\n\t[1] = NOME\n\t[2] = PRECO DE VENDA\n\t[3] = PRECO DE COMPRA\n\t[4] = ESTOQUE\n\t[5] = STATUS\n\t[6] = TUDO\n\t[7] = RETORNAR AO MENU PRODUTOS\n\t[8] = RETORNAR AO MENU PRINCIPAL\n\nDIGITE A OPCAO DESEJADA: ");
				scanf("%d", &edit_option);
				
				do{	
					switch(edit_option){
						case 1: edit_name_product(id);	
							return 0;
						case 2: edit_sale_price_product(id);
							return 0;
						case 3: edit_purchase_price_product(id);
							return 0;
						case 4: edit_stock_product(id);
							return 0;
						case 5: edit_status(ARQ_PRODUCTS, KEY_PRODUCTS, id);
							return 0;
						case 6: edit_name_product(id);
							edit_sale_price_product(id);
							edit_purchase_price_product(id);
							edit_stock_product(id);
							edit_status(ARQ_PRODUCTS, KEY_PRODUCTS, id);
							return 0;
						case 7: printf("\nRETORNANDO AO MENU PRODUTOS...\n");
							return RETORNAR_SUBMENU;
						case 8:	printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
							return RETORNAR_MENU_PRINCIPAL;	
						default: printf("\nOPCAO INVALIDA ... \nDIGITE UMAS DAS OPCOES: [1] - [2] - [3] - [4] - [5] - [6] - [7] - [8]\n\n");
							break;
					}//end switch edit_option					
				}while(edit_option >= 0 && edit_option <= 8);
				
				break;//break case 3 (search_option)
			case 4:	("\nRETORNANDO AO MENU PRODUTOS...\n");
				return RETORNAR_SUBMENU;
			case 5: printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
				return RETORNAR_MENU_PRINCIPAL;
			default: printf("\nOPCAO INVALIDA ... \nDIGITE UMAS DAS OPCOES: [1] - [2] - [3] - [4] - [5]\n\n");
				break;
		}//end switch search_option
			
	}while(search_option >= 1 && search_option <= 5);//end do_while(swicth(search_option)
	
}//end fuction edit_product
	
	int edit_name_product(long id_product){
	
		FILE *products_p = fopen(ARQ_PRODUCTS, "rb+");
		Products alter_product;
		
		int loop;
		
		if(products_p == NULL){//file failure open check
			printf("\nNao foi possivel abrir o arquivo. Fechando programa.");
			exit(EXIT_FAILURE);
		}//end if(file failure open check)
		
		while(fread(&alter_product, sizeof(Products), 1, products_p) != 0 && id_product != alter_product.id){}//continua lendo até achar ou acabar
									
		do{	
			printf("DIGITE O NOVO NOME DO PRODUTO: ");
			clear_buffer();
			fgets(alter_product.name, MAX_PRODUCT_NAME, stdin);
			alter_product.name[strcspn(alter_product.name, "\n")] = 0;
			if(loop = check_empty_text(alter_product.name))
				continue;
			if(loop = check_burst_buffer(alter_product.name, MAX_PRODUCT_NAME))
				continue;
			if(verify_duplicate_name_product(alter_product.name)){
				printf("\n[X] ERRO: Produto ja existe! Edicao cancelado.\n");
				fclose(products_p);
			    return 0;
			}
									
		}while(loop == 1);
		
		clear_buffer();
		printf("\nPara confirmar a alteracao digite 'C'\n");
		char validate_product = getchar();

        if(validate_product != '\n')
            clear_buffer();
		
    	validate_product = toupper(validate_product);
    	
    	if(validate_product == 'C'){
    		if(fseek(products_p, (id_product - 1) * sizeof(Products), SEEK_SET) ==  0){
				if(fwrite(&alter_product, sizeof(Products), 1, products_p)){
					printf("\nGravacao concluida com exito.\n");
					fclose(products_p);
					return 0;
				}
				else{
					printf("\n\nHouve um erro na gravacao do arquivo. Fechando programa.\n");
					fclose(products_p);
					exit(EXIT_FAILURE);
				}
			}
			else{
				printf("\nNao foi possivel posicionar o ponteiro do arquivc. Fechando programa.");
				fclose(products_p);
				exit(EXIT_FAILURE);
			}			
		}//end if
		else{
			printf("\nNao houve confirmacao do usuario, cancelando novo produto\n");
			fclose(products_p);
			return 0;
		}
	
	}//end function edit_name_product
	
	int edit_sale_price_product(long id_product){
	
		FILE *products_p = fopen(ARQ_PRODUCTS, "rb+");
		Products alter_product;
		
		int loop;
		
		if(products_p == NULL){//file failure open check
			printf("\nNao foi possivel abrir o arquivo. Fechando programa.");
			fclose(products_p);
			exit(EXIT_FAILURE);
		}//end if(file failure open check)
		
		while (fread(&alter_product, sizeof(Products), 1, products_p) != 0 && id_product != alter_product.id){}//continua lendo até achar ou acabar
								
		do{
			printf("\nDIGITE O NOVO PREÇO DE VENDA DO PRODUTO: ");
			scanf("%f", &alter_product.sale_price);
			loop = validate_price(alter_product.sale_price);
		}while(loop == 1);
		
		clear_buffer();						
		printf("\nPara confirmar a alteracao digite 'C'\n");
		char validate_product = getchar();

        if(validate_product != '\n')
            clear_buffer();
		
    	validate_product = toupper(validate_product);
    	
    	if(validate_product == 'C'){
    		if(fseek(products_p, (id_product - 1) * sizeof(Products), SEEK_SET) ==  0){
				if(fwrite(&alter_product, sizeof(Products), 1, products_p)){
					printf("\nGravacao concluida com exito.\n");
					fclose(products_p);
					return 0;
				}
				else{
					printf("\n\nHouve um erro na gravacao do arquivo. Fechando programa.\n");
					fclose(products_p);
					exit(EXIT_FAILURE);
				}
			}
			else{
				printf("\nNao foi possivel posicionar o ponteiro do arquivc. Fechando programa.");
				fclose(products_p);
				exit(EXIT_FAILURE);
			}			
		}//end if
		else{
			printf("\nNao houve confirmacao do usuario, cancelando novo produto\n");
			fclose(products_p);
			return 0;
		}
	
	}//end function edit_sale_price_product
	
	int edit_purchase_price_product(long id_product){
	
		FILE *products_p = fopen(ARQ_PRODUCTS, "rb+");
		Products alter_product;
		
		if(products_p == NULL){//file failure open check
			printf("\nNao foi possivel abrir o arquivo. Fechando programa.");
			fclose(products_p);
			exit(EXIT_FAILURE);
		}//end if(file failure open check)
		
		while (fread(&alter_product, sizeof(Products), 1, products_p) != 0 && id_product != alter_product.id){}//continua lendo até achar ou acabar
		
		printf("\nDIGITE O NOVO PREÇO DE COMPRA DO PRODUTO: ");
		scanf("%f", &alter_product.purchase_price);
		if(alter_product.purchase_price <= 0)
			alter_product.purchase_price = 0;
		
		clear_buffer();
		printf("\nPara confirmar a alteracao digite 'C'\n");
		char validate_product = getchar();

        if(validate_product != '\n')
            clear_buffer();
		
    	validate_product = toupper(validate_product);
    	
    	if(validate_product == 'C'){
    		if(fseek(products_p, (id_product - 1) * sizeof(Products), SEEK_SET) ==  0){
				if(fwrite(&alter_product, sizeof(Products), 1, products_p)){
					printf("\nGravacao concluida com exito.\n");
					fclose(products_p);
					return 0;
				}
				else{
					printf("\n\nHouve um erro na gravacao do arquivo. Fechando programa.\n");
					fclose(products_p);
					exit(EXIT_FAILURE);
				}
			}
			else{
				printf("\nNao foi possivel posicionar o ponteiro do arquivc. Fechando programa.");
				fclose(products_p);
				exit(EXIT_FAILURE);
			}			
		}//end if
		else{
			printf("\nNao houve confirmacao do usuario, cancelando novo produto\n");
			fclose(products_p);
			return 0;
		}
		
	}//end function edit_purchase_price_product
	
	int edit_stock_product(long id_product){
		
		FILE *products_p = fopen(ARQ_PRODUCTS, "rb+");
		Products alter_product;
		
		if(products_p == NULL){//file failure open check
			printf("\nNao foi possivel abrir o arquivo. Fechando programa.");
			fclose(products_p);
			exit(EXIT_FAILURE);
		}//end if(file failure open check)
		
		while (fread(&alter_product, sizeof(Products), 1, products_p) != 0 && id_product != alter_product.id){}//continua lendo até achar ou acabar
		
		printf("\nDIGITE O NOVO ESTOQUE DO PRODUTO: ");
		scanf("%d", &alter_product.stock);
		if(alter_product.stock <= 0)
			alter_product.stock = 0;
		
		clear_buffer();
		printf("\nPara confirmar a alteracao digite 'C'\n");
		char validate_product = getchar();

        if(validate_product != '\n')
            clear_buffer();
		
    	validate_product = toupper(validate_product);
    	
    	if(validate_product == 'C'){
    		if(fseek(products_p, (id_product - 1) * sizeof(Products), SEEK_SET) ==  0){
				if(fwrite(&alter_product, sizeof(Products), 1, products_p)){
					printf("\nGravacao concluida com exito.\n");
					fclose(products_p);
					return 0;
				}
				else{
					printf("\n\nHouve um erro na gravacao do arquivo. Fechando programa.\n");
					fclose(products_p);
					exit(EXIT_FAILURE);
				}
			}
			else{
				printf("\nNao foi possivel posicionar o ponteiro do arquivc. Fechando programa.");
				fclose(products_p);
				exit(EXIT_FAILURE);
			}			
		}//end if
		else{
			printf("\nNao houve confirmacao do usuario, cancelando novo produto\n");
			fclose(products_p);
			return 0;
		}
		
	}//end function edit_stock_product
	
int search_product(){
	
	FILE *products_p = fopen(ARQ_PRODUCTS, "rb");
	Products product;
	
	if(products_p == NULL){//file failure open check
		printf("\nNao foi possivel abrir o arquivo. Fechando programa.");
		exit(EXIT_FAILURE);
	}//end if(file failure open check)
		
	long id;
	int search_option, edit_option, loop;
	
	printf("QUAL PRODUTO DESEJA VISUALIZAR?\n");
	printf("[1] = BUSCAR POR ID\n[2] = BUSCAR PELA LISTA\n[3] = BUSCAR POR NOME\n[4] = RETORNAR AO MENU PRODUTOS\n[5] = RETORNAR AO MENU PRINCIPAL\n\nDIGITE A OPCAO DESEJADA: ");
	
	do{
		scanf("%d", &search_option);
		
		switch(search_option){
			
			case 1:
				id = search_id_generic(ARQ_PRODUCTS, KEY_PRODUCTS);
				
				if(id == 0){
					printf("\nPRODUTO NAO ENCONTRADO. RETORNANDO AO MENU PRODUTOS...\n\n");
					fclose(products_p);
					return 0;
				}//end if(id == 0)
				
				if(fseek(products_p, (id - 1) * sizeof(Products), SEEK_SET) ==  0){
					if(fread(&product, sizeof(Products), 1, products_p)){
						printf("ID: %.6ld\nNOME: %s\nPRECO: %.2f\nPRECO_COMPRA: %.2f\nESTOQUE: %d\n", product.id, product.name, product.sale_price, product.purchase_price, product.stock);
						printf("STATUS: %s\n", product.status == ATIVO ? "ATIVO" : "INATIVO");
						fclose(products_p);
						clear_buffer();
						printf("\nCaso queria editar alguma das informações digite 'E'\n");
						char flag_edit = getchar();
				
				        if(flag_edit != '\n')
				            clear_buffer();
						
				    	flag_edit = toupper(flag_edit);
				    	
				    	if(flag_edit == 'E'){
							printf("\nQUAL PARAMETRO DO PRODUTO DESEJA ALTERAR?");
							printf("\n\t[1] = NOME\n\t[2] = PRECO DE VENDA\n\t[3] = PRECO DE COMPRA\n\t[4] = ESTOQUE\n\t[5] = STATUS\n\t[6] = TUDO\n\t[7] = RETORNAR AO MENU PRODUTOS\n\t[8] = RETORNAR AO MENU PRINCIPAL\n\nDIGITE A OPCAO DESEJADA: ");
							scanf("%d", &edit_option);
				
							do{	
								switch(edit_option){
									case 1: edit_name_product(id);	
										return 0;
									case 2: edit_sale_price_product(id);
										return 0;
									case 3: edit_purchase_price_product(id);
										return 0;
									case 4: edit_stock_product(id);
										return 0;
									case 5: edit_status(ARQ_PRODUCTS, KEY_PRODUCTS, id);
										return 0;
									case 6: edit_name_product(id);
										edit_sale_price_product(id);
										edit_purchase_price_product(id);
										edit_stock_product(id);
										edit_status(ARQ_PRODUCTS, KEY_PRODUCTS, id);
										return 0;
									case 7: printf("\nRETORNANDO AO MENU PRODUTOS...\n");
										return RETORNAR_SUBMENU;
									case 8:	printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
										return RETORNAR_MENU_PRINCIPAL;	
									default: printf("\nOPCAO INVALIDA ... \nDIGITE UMAS DAS OPCOES: [1] - [2] - [3] - [4] - [5] - [6] - [7] - [8]\n\n");
										break;
								}//end switch edit_option					
							}while(edit_option >= 0 && edit_option <= 8);			
							
						}//end if 'E'
				        else{
				        	printf("\nRETORNANDO AO MENU...\n\n");
				        	return RETORNAR_SUBMENU;
						}
					}//end if fread
					else{
						printf("\nERRO: Houve um erro na leitura do arquivo. Fechando programa.\n");
						fclose(products_p);
		        		exit(EXIT_FAILURE);
					}
				}//if fseek
			//end case 1
			case 2: id = search_id_generic_list(KEY_PRODUCTS);
			
				if(id == 0){
					printf("\nPRODUTO NAO ENCONTRADO. RETORNANDO AO MENU...\n\n");
					fclose(products_p);
					return 0;
				}//end if(id == 0)
				if(id == RETORNAR_SUBMENU){
					printf("\nRETORNANDO AO MENU PRODUTOS...\n");
					fclose(products_p);
					return RETORNAR_SUBMENU;
				}//end if(id == 0)
				if(id == RETORNAR_MENU_PRINCIPAL){
					printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
					fclose(products_p);
					return RETORNAR_MENU_PRINCIPAL;
				}//end if(id == 0)
				
				if(fseek(products_p, (id - 1) * sizeof(Products), SEEK_SET) ==  0){
					if(fread(&product, sizeof(Products), 1, products_p)){
						printf("ID: %.6d\nNOME: %s\nPRECO: %.2f\nPRECO_COMPRA: %.2f\nESTOQUE: %d\n", product.id, product.name, product.sale_price, product.purchase_price, product.stock);
						printf("STATUS: %s\n", product.status == ATIVO ? "ATIVO" : "INATIVO");
						fclose(products_p);
						
						clear_buffer();
						printf("\nCaso queria editar alguma das informações digite 'E'\n");
						char flag_edit = getchar();
				
				        if(flag_edit != '\n')
				            clear_buffer();
						
				    	flag_edit = toupper(flag_edit);
				    	
				    	if(flag_edit == 'E'){
							printf("\nQUAL PARAMETRO DO PRODUTO DESEJA ALTERAR?");
							printf("\n\t[1] = NOME\n\t[2] = PRECO DE VENDA\n\t[3] = PRECO DE COMPRA\n\t[4] = ESTOQUE\n\t[5] = STATUS\n\t[6] = TUDO\n\t[7] = RETORNAR AO MENU PRODUTOS\n\t[8] = RETORNAR AO MENU PRINCIPAL\n\nDIGITE A OPCAO DESEJADA: ");
							scanf("%d", &edit_option);
				
							do{	
								switch(edit_option){
									case 1: edit_name_product(id);	
										return 0;
									case 2: edit_sale_price_product(id);
										return 0;
									case 3: edit_purchase_price_product(id);
										return 0;
									case 4: edit_stock_product(id);
										return 0;
									case 5: edit_status(ARQ_PRODUCTS, KEY_PRODUCTS, id);
										return 0;
									case 6: edit_name_product(id);
										edit_sale_price_product(id);
										edit_purchase_price_product(id);
										edit_stock_product(id);
										edit_status(ARQ_PRODUCTS, KEY_PRODUCTS, id);
										return 0;
									case 7: printf("\nRETORNANDO AO MENU PRODUTOS...\n");
										return RETORNAR_SUBMENU;
									case 8:	printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
										return RETORNAR_MENU_PRINCIPAL;	
									default: printf("\nOPCAO INVALIDA ... \nDIGITE UMAS DAS OPCOES: [1] - [2] - [3] - [4] - [5] - [6] - [7] - [8]\n\n");
										break;
								}//end switch edit_option					
							}while(edit_option >= 0 && edit_option <= 8);		
							
						}//end if 'E'
				        else{
				        	printf("\nRETORNANDO AO MENU...\n\n");
				        	return RETORNAR_SUBMENU;
						}
					}//end if fread
					else{
						printf("\nERRO: Houve um erro na leitura do arquivo. Fechando programa.\n");
						fclose(products_p);
		        		exit(EXIT_FAILURE);
					}
				}//if fseek
			//end case 2
			case 3: id = search_name_product();
			
				if(id == 0){
					printf("\nPRODUTO NAO ENCONTRADO. RETORNANDO AO MENU...\n\n");
					fclose(products_p);
					return 0;
				}//end if(id == 0)
				
				if(fseek(products_p, (id - 1) * sizeof(Products), SEEK_SET) ==  0){
					if(fread(&product, sizeof(Products), 1, products_p)){
						printf("ID: %.6d | NOME: %s | PRECO: %.2f | PRECO_COMPRA: %.2f | ESTOQUE: %d |", product.id, product.name, product.sale_price, product.purchase_price, product.stock);
						printf(" STATUS: %s\n", product.status == ATIVO ? "ATIVO" : "INATIVO");
						fclose(products_p);
						
						clear_buffer();
						printf("\nCaso queria editar alguma das informações digite 'E'\n");
						char flag_edit = getchar();
				
				        if(flag_edit != '\n')
				            clear_buffer();
						
				    	flag_edit = toupper(flag_edit);
				    	
				    	if(flag_edit == 'E'){
							printf("\nQUAL PARAMETRO DO PRODUTO DESEJA ALTERAR?");
							printf("\n\t[1] = NOME\n\t[2] = PRECO DE VENDA\n\t[3] = PRECO DE COMPRA\n\t[4] = ESTOQUE\n\t[5] = STATUS\n\t[6] = TUDO\n\t[7] = RETORNAR AO MENU PRODUTOS\n\t[8] = RETORNAR AO MENU PRINCIPAL\n\nDIGITE A OPCAO DESEJADA: ");
							scanf("%d", &edit_option);
				
							do{	
								switch(edit_option){
									case 1: edit_name_product(id);	
										return 0;
									case 2: edit_sale_price_product(id);
										return 0;
									case 3: edit_purchase_price_product(id);
										return 0;
									case 4: edit_stock_product(id);
										return 0;
									case 5: edit_status(ARQ_PRODUCTS, KEY_PRODUCTS, id);
										return 0;
									case 6: edit_name_product(id);
										edit_sale_price_product(id);
										edit_purchase_price_product(id);
										edit_stock_product(id);
										edit_status(ARQ_PRODUCTS, KEY_PRODUCTS, id);
										return 0;
									case 7: printf("\nRETORNANDO AO MENU PRODUTOS...\n");
										return RETORNAR_SUBMENU;
									case 8:	printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
										return RETORNAR_MENU_PRINCIPAL;	
									default: printf("\nOPCAO INVALIDA ... \nDIGITE UMAS DAS OPCOES: [1] - [2] - [3] - [4] - [5] - [6] - [7] - [8]\n\n");
										break;
								}//end switch edit_option					
							}while(edit_option >= 0 && edit_option <= 8);		
							
						}//end if 'E'
				        else{
				        	printf("\nRETORNANDO AO MENU...\n\n");
				        	return RETORNAR_SUBMENU;
						}
					}//end if fread
					else{
						printf("\nERRO: Houve um erro na leitura do arquivo. Fechando programa.\n");
						fclose(products_p);
		        		exit(EXIT_FAILURE);
					}
				}//if fseek
			//end case 3
			case 4:	printf("\nRETORNANDO AO MENU PRODUTOS...\n");
				fclose(products_p);
				return RETORNAR_SUBMENU;
			case 5: printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
				fclose(products_p);
				return RETORNAR_MENU_PRINCIPAL;
			default: printf("\nOPCAO INVALIDA ... \nDIGITE UMAS DAS OPCOES: [1] - [2] - [3] - [4] - [5]\n\n");
				break;
		}//end switch search_option
			
	}while(search_option >= 1 && search_option <= 5);
	
}//end fuction search-a-product

long search_name_product(){
	
	FILE *products_p = fopen(ARQ_PRODUCTS, "rb");
    Products p;
    
    if(products_p == NULL){
        printf("\nERRO: Nao foi possivel abrir o arquivo. Fechando programa.");
        exit(EXIT_FAILURE);
    }

    char termo_busca[MAX_PRODUCT_NAME];    // O que o usuario digitou
    char busca_min[MAX_PRODUCT_NAME];      // Versao minuscula do que o usuario digitou
    char nome_produto_min[MAX_PRODUCT_NAME]; // Versao minuscula do nome do produto no arquivo
    
    int encontrou_algum = 0;
    long id_escolhido = 0;
    int loop;

    // 1. CAPTURA DO TERMO DE BUSCA
    do{
        printf("\n--- BUSCA INTELIGENTE ---\n");
        printf("Digite parte do nome (ex: 'video'): ");
        
        // Limpeza de buffer básica se necessario
        // fflush(stdin); 
        
        fgets(termo_busca, MAX_PRODUCT_NAME, stdin);
        termo_busca[strcspn(termo_busca, "\n")] = 0; // Remove o Enter no final
        
        // Validação simples se está vazio
        if(strlen(termo_busca) < 1) {
            printf("Digite pelo menos uma letra!\n");
            loop = 1;
        } else {
            loop = 0;
        }
    } while(loop);

    printf("\n--- RESULTADOS ENCONTRADOS ---\n");
    printf("%-5s | %-30s | %-10s\n", "ID", "NOME", "PRECO");
    printf("----------------------------------------------------\n");

    // Converte o que o usuário digitou para minúsculo
    texto_minusculo(busca_min, termo_busca);

    // 2. O LOOP "GOOGLE" (VARREDURA)
    while(fread(&p, sizeof(Products), 1, products_p)){
        
        // Converte o nome do produto atual para minúsculo numa variável temporária
        texto_minusculo(nome_produto_min, p.name);

        // A MÁGICA: strstr verifica se a busca existe DENTRO do nome
        if(strstr(nome_produto_min, busca_min) != NULL){
            printf("%03ld   | %-30.30s | R$ %.2f\n", p.id, p.name, p.sale_price);
            encontrou_algum++;
        }
    }

    // 3. DECISÃO FINAL
    if(encontrou_algum == 0){
        printf("\nNenhum produto encontrado com esse termo.\n");
        fclose(products_p);
        return 0;
        
    } else {
        printf("----------------------------------------------------\n");
        printf("\nForam encontrados %d produtos.\n", encontrou_algum);
        printf("Digite o ID do produto que deseja SELECIONAR (ou 0 para cancelar): ");
        scanf("%ld", &id_escolhido);
        
        if(id_escolhido > 0){
        	printf("\nO usuario digitou '0', retornando a ULTIMA funcao\n");
		}
        	return 0;
        
        // Limpa buffer pós-scanf para não travar o menu lá fora
        // fflush(stdin); 
        clear_buffer(); 

        fclose(products_p);
        return id_escolhido; // Retorna o ID que o usuário escolheu na lista
    }
	
}//end function search_name