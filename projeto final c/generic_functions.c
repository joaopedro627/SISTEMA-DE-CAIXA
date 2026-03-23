#include "MODEL_MAIN.H"

int walk_pags(int *contador, long *pag, long max_pags){

	long user_pag;
	int loop;
	char flag_pag, flag_return;
						
	printf("\n\t[ENTER] PROXIMA PAGINA\n\t[0] IR PARA A PAGINA\n\t[R] RETORNAR A FUNCAO ANTERIOR\n\t[S] RETORNAR AO SUBMENU ATUAL\n\nOPCAO: ");
    
    clear_buffer();
    flag_pag = getchar(); 
            
	if(flag_pag != '\n')
		clear_buffer();

    flag_pag = toupper(flag_pag); 

	if(flag_pag == '0'){
	    do{
	    	printf("\nQUAL PAGINA DESEJA IR: ");
	        scanf("%d", &user_pag);
	
	        clear_buffer(); 
	
            if(user_pag < 1 || user_pag > max_pags){
                printf("\nPAGINA INVALIDA ...\n\n");
                loop = 1;
            }
			else if(user_pag > 0 && user_pag != *pag){
	            *pag = user_pag;
	          	loop = 0;
	            *contador = 1;
	            return 0;
	    	}    
            else{
            	printf("\nUSUARIO JA ESTA NA PAGINA. RETORNANDO A FUNCAO\n");
            	return 0;
			}
                
	    }while(loop == 1);
    }
    else if(flag_pag == 'R')
        return RETORNAR_FUNCAO; 
    else if(flag_pag == 'S')
        return RETORNAR_SUBMENU;
    else{
        // Qualquer outra tecla (ou Enter) avança
        *pag += 1;
        *contador = 1;
        return 0;
    }	
	
}//end function walk_pags

long get_next_id(const char name_arq[], const int key_ship){
		
	FILE *p_arq = fopen(name_arq, "rb");
	
	if(p_arq == NULL){
        if (errno == ENOENT) {// ENOENT = Error No Entry. O arquivo realmente nao existe.
            return 1; 
        } else {
            printf("\nERRO CRITICO: Falha de hardware ou permissao ao abrir %s.", name_arq);
            printf("\nCodigo do erro do sistema: %d\n", errno);
            exit(EXIT_FAILURE);
        }
    }
	
	switch(key_ship){
		case KEY_PRODUCTS: {
			
			Products p;
			long id = 0;
			
			while(fread(&p, sizeof(Products), 1, p_arq))
				id = p.id;
			
			fclose(p_arq);
			return id + 1;
			
		}//end code block
			break;
		case KEY_EMPLOYEES: {
			
			Employee e;
			int id = 0;
			
			while(fread(&e, sizeof(Employee), 1, p_arq))
				id = e.id;
			
			fclose(p_arq);
			return id + 1;
			
		}//end code block
			break;
		case KEY_GROUPS: {
			
			Group g;
			int id = 0;
			
			while(fread(&g, sizeof(Group), 1, p_arq))
				id = g.id;
			
			fclose(p_arq);
			return id + 1;
			
		}//end code block
		break;
	}//end switch
				
}//end function get_next_id

long search_id_generic(const char name_arq[], const int key_ship){
	
	FILE *p_arq = fopen(name_arq, "rb");
	
	if(p_arq == NULL){
        printf("\nNao foi possivel abrir o arquivo. Fechando programa.");
		exit(EXIT_FAILURE);
    }

    long user_id;
    int encontrado = 0; // Usando como booleano

    printf("\nDigite o ID para busca: ");
    
    while(scanf("%ld", &user_id) != 1){
	    clear_buffer();
	    printf("\nInput invalido! Digite apenas NUMEROS para o ID: ");
	}

    switch(key_ship){
        case 1: { Products p;
            while(fread(&p, sizeof(Products), 1, p_arq)) {
                if(user_id == p.id) {
                    printf("\nProduto encontrado! ( %s )\n", p.name);
                    return user_id;
            	}
            }
		} break;
		
        case 2: { Employee e;
            while(fread(&e, sizeof(Employee), 1, p_arq)) {
                if(user_id == e.id) {
                    printf("\nFuncioanrio encontrado! ( %s )\n", e.name);
                    return user_id;
            	}
            }	
		} break;
		
        case 3: { Group g;
            while(fread(&g, sizeof(Group), 1, p_arq)) {
                if(user_id == g.id) {
                    printf("\nGupo encontrado! ( %s )\n", g.name);
                    return user_id;
            	}
            }
            
		} break;

    }//end switch
	
	printf("\nRegistro NAO encontrado. ID incorreto ou NAO existente\n");
	fclose(p_arq);	
	return 0;//return ID no found;

}//end function search_id

long search_id_generic_list(const int key_ship){
	
	long id_return;
	int flag_return;
	printf("\nAbrindo Lista\n");
	
	switch(key_ship){
		case 1: flag_return = list_products();
			if(flag_return == RETORNAR_SUBMENU)
				return RETORNAR_SUBMENU;
			if(flag_return == RETORNAR_MENU_PRINCIPAL)
				return RETORNAR_MENU_PRINCIPAL;
			id_return = search_id_generic(ARQ_PRODUCTS, KEY_PRODUCTS);
				return id_return;
		case 2: flag_return = list_employees();
			if(flag_return == RETORNAR_SUBMENU)
				return RETORNAR_SUBMENU;
			if(flag_return == RETORNAR_MENU_PRINCIPAL)
				return RETORNAR_MENU_PRINCIPAL;
			id_return = search_id_generic(ARQ_EMPLOYEES, KEY_EMPLOYEES);
			return id_return;
		case 3:	flag_return = list_groups();
			if(flag_return == RETORNAR_SUBMENU)
				return RETORNAR_SUBMENU;
			if(flag_return == RETORNAR_MENU_PRINCIPAL)
				return RETORNAR_MENU_PRINCIPAL;
			id_return = search_id_generic(ARQ_GROUPS, KEY_GROUPS);	
			return id_return;
	}//end switch
	
}//end function search_list_id

long search_name(const char name_arq[], const int key_ship){
	
	FILE *p_arq = fopen(name_arq, "rb");
    
    int encontrou_algum = 0;
    long id_escolhido = 0;
    int loop;
    
    if(p_arq == NULL){
        printf("\nERRO: Nao foi possivel abrir o arquivo. Fechando programa.");
        exit(EXIT_FAILURE);
    }
    
	switch(key_ship){
		case KEY_PRODUCTS: {	
				Products p;
				
			    char termo_busca[MAX_PRODUCT_NAME];   // O que o usuario digitou
			    char busca_min[MAX_PRODUCT_NAME];     // Versao minuscula do que o usuario digitou
			    char nome_product_min[MAX_PRODUCT_NAME]; // Versao minuscula do nome do funcionario no arquivo
		
			    do{
			        printf("\n--- BUSCA INTELIGENTE ---\n");
			        printf("Digite parte do nome (ex: 'Coca'): ");
			        clear_buffer();
			        fgets(termo_busca, MAX_PRODUCT_NAME, stdin);
			        termo_busca[strcspn(termo_busca, "\n")] = 0; // Remove o Enter no final
			        
			        // Validação simples se está vazio
			        if(strlen(termo_busca) < 1) {
			            printf("Digite pelo menos uma letra!\n");
			            loop = 1;
			        } 
					else 
			        	loop = 0;
	
	  			} while(loop);
	  			
	  		    printf("\n--- RESULTADOS ENCONTRADOS ---\n");
				printf("%-5s | %-40s | %-10s\n", "ID", "NOME", "PRECO");
			    printf("----------------------------------------------------\n");
			
			    texto_minusculo(busca_min, termo_busca);// Converte o que o usuário digitou para minúsculo
			
			    while(fread(&p, sizeof(Products), 1, p_arq)){
			        			        
			        texto_minusculo(nome_product_min, p.name);// Converte o nome do produto atual para minúsculo numa variável temporária
			
			        // A MÁGICA: strstr verifica se a busca existe DENTRO do nome
			        if(strstr(nome_product_min, busca_min) != NULL){
			            printf("%03ld   | %-40.40s | R$ %.2f\n", p.id, p.name, p.sale_price);
			            encontrou_algum++;
			        }
			    }

				if(encontrou_algum != 0){
			        printf("----------------------------------------------------\n");
			        printf("\nForam encontrados %d produtos.\n", encontrou_algum);
			        printf("Digite o ID do produto que deseja SELECIONAR (ou 0 para cancelar): ");
			        scanf("%ld", &id_escolhido);
			        
			        if(id_escolhido > 0){
			        	printf("\nO usuario digitou '0', retornando a ULTIMA funcao\n");
			        	return 0;
			    	}
			    	
			        clear_buffer(); 
			
			        fclose(p_arq);
			        return id_escolhido; // Retorna o ID que o usuário escolheu na lista
			    }//end if != 0					
		
			}//end block case
			break;
		case KEY_EMPLOYEES: {
				Employee e;
				
			    char termo_busca[MAX_EMPLOYEE_NAME];   // O que o usuario digitou
			    char busca_min[MAX_EMPLOYEE_NAME];     // Versao minuscula do que o usuario digitou
			    char nome_employee_min[MAX_EMPLOYEE_NAME]; // Versao minuscula do nome do funcionario no arquivo
		
			   do{
			        printf("\n--- BUSCA INTELIGENTE ---\n");
			        printf("Digite parte do nome (ex: 'Joao'): ");
			        clear_buffer();
			        fgets(termo_busca, MAX_EMPLOYEE_NAME, stdin);
			        termo_busca[strcspn(termo_busca, "\n")] = 0; // Remove o Enter no final
			        
			        // Validação simples se está vazio
			        if(strlen(termo_busca) < 1) {
			            printf("Digite pelo menos uma letra!\n");
			            loop = 1;
			        } 
					else 
			        	loop = 0;
	
	  			} while(loop);
		
				printf("\n--- RESULTADOS ENCONTRADOS ---\n");
	   			printf("%-5s | %-40s | %-30s | %-10s\n", "ID", "NOME", "CARGO", "SALARIO");
				printf("--------------------------------------------------------------------------\n");
								
	    		texto_minusculo(busca_min, termo_busca);// Converte o que o usuário digitou para minúsculo
	    		
	    		while(fread(&e, sizeof(Employee), 1, p_arq)){
	        
			        texto_minusculo(nome_employee_min, e.name);// Converte o nome do produto atual para minúsculo numa variável temporária
			
			        // A MÁGICA: strstr verifica se a busca existe DENTRO do nome
			       if(strstr(nome_employee_min, busca_min) != NULL){
				        // %03d para ID, %-30.30s para nome, %-15s para cargo, %.2f para salário
				        printf("%03d   | %-40.40s | %-30s | R$ %.2f\n", e.id, e.name, e.position, e.salary);
				        encontrou_algum++;
			    	}
	    		}//end while
	    		
				if(encontrou_algum != 0){
			        printf("----------------------------------------------------\n");
			        printf("\nForam encontrados %d funcionarios.\n", encontrou_algum);
			        printf("Digite o ID do funcionario que deseja SELECIONAR (ou 0 para cancelar): ");
			        scanf("%d", &id_escolhido);
			        
			        if(id_escolhido > 0){
			        	printf("\nO usuario digitou '0', retornando a ULTIMA funcao\n");
			        	return 0;
			    	}
			    	
			        clear_buffer(); 
			
			        fclose(p_arq);
			        return id_escolhido; // Retorna o ID que o usuário escolheu na lista
			    }//end if != 0
				
			}//end code block
			break;
		case KEY_GROUPS: {
				Group g;
				
			    char termo_busca[MAX_GROUP_NAME];   // O que o usuario digitou
			    char busca_min[MAX_GROUP_NAME];     // Versao minuscula do que o usuario digitou
			    char nome_group_min[MAX_GROUP_NAME]; // Versao minuscula do nome do funcionario no arquivo
		
			   do{
			        printf("\n--- BUSCA INTELIGENTE ---\n");
			        printf("Digite parte do nome (ex: 'sorvetes'): ");
			        clear_buffer();
			        fgets(termo_busca, MAX_GROUP_NAME, stdin);
			        termo_busca[strcspn(termo_busca, "\n")] = 0; // Remove o Enter no final
			        
			        // Validação simples se está vazio
			        if(strlen(termo_busca) < 1) {
			            printf("Digite pelo menos uma letra!\n");
			            loop = 1;
			        } 
					else 
			        	loop = 0;
	
	  			} while(loop);
		
				printf("\n--- RESULTADOS ENCONTRADOS ---\n");
	   			printf("%-5s | %-20s | %-4s\n", "ID", "NOME", "QUANTIDADE PRODUTOS");
				printf("--------------------------------------------------------------------------\n");
				
			
	    		texto_minusculo(busca_min, termo_busca);// Converte o que o usuário digitou para minúsculo
	    		
	    		while(fread(&g, sizeof(Group), 1, p_arq)){
	        
			        texto_minusculo(nome_group_min, g.name);// Converte o nome do produto atual para minúsculo numa variável temporária
			
			        // A MÁGICA: strstr verifica se a busca existe DENTRO do nome
			       if(strstr(nome_group_min, busca_min) != NULL){
				        // %03d para ID, %-30.30s para nome, %-15s para cargo, %.2f para salário
				        printf("%03d   | %-20.20s | %d\n", g.id, g.name, g.quant_products);
				        encontrou_algum++;
			    	}
	    		}//end while
	    		
				if(encontrou_algum != 0){
			        printf("----------------------------------------------------\n");
			        printf("\nForam encontrados %d grupos.\n", encontrou_algum);
			        printf("Digite o ID do grupo que deseja SELECIONAR (ou 0 para cancelar): ");
			        scanf("%d", &id_escolhido);
			        
			        if(id_escolhido > 0){
			        	printf("\nO usuario digitou '0', retornando a ULTIMA funcao\n");
			        	return 0;
			    	}
			    	
			        clear_buffer(); 
			
			        fclose(p_arq);
			        return id_escolhido; // Retorna o ID que o usuário escolheu na lista
			    }//end if != 0
			
			}//end code block
			break;
	}//end switch

   	if(encontrou_algum == 0){
        printf("\nNenhum funcionario encontrado com esse termo.\n");
        fclose(p_arq);
        return 0; 
    }
	
}//end function search_name

int visualize_element(const char name_arq[], const int key_ship){
	
	FILE *p_arq = fopen(name_arq, "rb");
	
	if(p_arq == NULL){//file failure open check
		printf("\nNao foi possivel abrir o arquivo. Fechando programa.");
		exit(EXIT_FAILURE);
	}//end if(file failure open check)
	
	long id;
	int i, search_option, edit_option, loop, flag_return;
	
	do{
		
		printf("QUAL PARAMETRO DE BUSCA DESEJA UTILIZAR?");
		printf("\n[1] = BUSCAR POR ID\n[2] = BUSCAR PELA LISTA\n[3] = BUSCAR POR NOME\n[4] = RETORNAR AO MENU SUBMENU\n[5] = RETORNAR AO MENU PRINCIPAL\n\nDIGITE A OPCAO DESEJADA: ");

		scanf("%d", &search_option);
			 	
 		switch(search_option){
 			
 			case 1: if(key_ship == KEY_PRODUCTS)
		 			id = search_id_generic(ARQ_PRODUCTS, KEY_PRODUCTS);
		 		else if(key_ship == KEY_EMPLOYEES)
		 			id = search_id_generic(ARQ_EMPLOYEES, KEY_EMPLOYEES);
		 		else 
		 			id = search_id_generic(ARQ_GROUPS, KEY_GROUPS);
		 			
				break;
 			case 2: 
			 	if(key_ship == KEY_PRODUCTS){
			 		id = search_id_generic_list(KEY_PRODUCTS);
			 		
			 		if(id == RETORNAR_SUBMENU){
						printf("\nRETORNANDO AO MENU PRODUTOS...\n");
						return RETORNAR_SUBMENU;
					}//end if(id == 0)
					if(id == RETORNAR_MENU_PRINCIPAL){
						printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
						return RETORNAR_MENU_PRINCIPAL;
					}//end if(id == 0)
					
				}//end key product
		 			
		 		else if(key_ship == KEY_EMPLOYEES){
		 			id = search_id_generic_list (KEY_EMPLOYEES);
		 			
		 			if(id == RETORNAR_SUBMENU){
						printf("\nRETORNANDO AO MENU DE FUNCIONARIOS...\n");
						return RETORNAR_SUBMENU;
					}//end if(id == 0)
					if(id == RETORNAR_MENU_PRINCIPAL){
						printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
						return RETORNAR_MENU_PRINCIPAL;
					}//end if(id == 0)
					
				}//end key employee
		 			
		 		else{
		 			id = search_id_generic_list(KEY_GROUPS);
		 			
		 			if(id == RETORNAR_SUBMENU){
						printf("\nRETORNANDO AO MENU DE GRUPOS...\n");
						return RETORNAR_SUBMENU;
					}//end if(id == 0)
					if(id == RETORNAR_MENU_PRINCIPAL){
						printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
						return RETORNAR_MENU_PRINCIPAL;
					}//end if(id == 0)
		 			
				}//end key group
		 			
 				break;
 			case 3: if(key_ship == KEY_PRODUCTS)
		 			id = search_name(ARQ_PRODUCTS, KEY_PRODUCTS);
		 		else if(key_ship == KEY_EMPLOYEES)
		 			id = search_name(ARQ_EMPLOYEES, KEY_EMPLOYEES);
		 		else
		 			id = search_name(ARQ_GROUPS, KEY_GROUPS);
		 			 
 				break;	
			case 4:	printf("\nRETORNANDO AO MENU SUBMENU...\n");
				return RETORNAR_SUBMENU;
			case 5: printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
				return RETORNAR_MENU_PRINCIPAL;
 			default: printf("\nOPCAO INVALIDA ... \nDIGITE UMAS DAS OPCOES: [1] - [2] - [3] - [4] - [5]\n\n");
				break;
		}//end switch search_option
			 		
 		if(id == 0){
			printf("\nELEMENTO NAO ENCONTRADO. RETORNANDO AO SUBMENU...\n\n");
			return RETORNAR_SUBMENU;
		}//end if(id == 0)
		else 
			break;
						
	}while(search_option >= 1 && search_option <= 5);
	
	switch(key_ship){
		case KEY_PRODUCTS: {
				Products product;
				
				if(fseek(p_arq, (id - 1) * sizeof(Products), SEEK_SET) ==  0){
					if(fread(&product, sizeof(Products), 1, p_arq)){
						printf("ID: %.6ld\nNOME: %s\nPRECO: %.2f\nPRECO_COMPRA: %.2f\nESTOQUE: %d\n", product.id, product.name, product.sale_price, product.purchase_price, product.stock);
						printf("STATUS: %s\n", product.status == ATIVO ? "ATIVO" : "INATIVO");
						fclose(p_arq);
						clear_buffer();
						printf("\nCaso queria editar alguma das informações digite 'E'\n");
						char flag_edit = getchar();
				
				        if(flag_edit != '\n')
				            clear_buffer();
						
				    	flag_edit = toupper(flag_edit);
				    	
				    	if(flag_edit == 'E'){
							flag_return = edit_element(KEY_PRODUCTS, &id);
							if(flag_return == RETORNAR_MENU_PRINCIPAL){
								printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
								return RETORNAR_MENU_PRINCIPAL;	
							}
							else if(flag_return == RETORNAR_SUBMENU){
								printf("\nRETORNANDO AO MENU PRODUTOS...\n\n");
								return RETORNAR_MENU_PRINCIPAL;	
							}
						}//end if 'E'
						else 
							return 0;//todo processo foi bem sucedido
					}//end if fread
					else{
						printf("\nERRO: Houve um erro na leitura do arquivo. Fechando programa.\n");
						fclose(p_arq);
		        		exit(EXIT_FAILURE);
					}
				}//if fseek
				else{
					printf("\nNao foi possivel posicionar o ponteiro do arquivc. Fechando programa.");
					fclose(p_arq);
					exit(EXIT_FAILURE);
				}				

			}//end code block
			break;
		case KEY_EMPLOYEES: {
				Employee employee;
				
				if(fseek(p_arq, (id - 1) * sizeof(Employee), SEEK_SET) ==  0){
					if(fread(&employee, sizeof(Employee), 1, p_arq)){
						printf("ID: %.6d\nNOME: %s\nCARGO: %s\nSALARIO: %.2f\nVOUCHER: %.2f\n", employee.id, employee.name, employee.position, employee.salary, employee.voucher);
						printf("STATUS: %s\n", employee.status == ATIVO ? "ATIVO" : "INATIVO");
						fclose(p_arq);
						
						clear_buffer();
						printf("\nCaso queria editar alguma das informações digite 'E'\n");
						char flag_edit = getchar();
				
				        if(flag_edit != '\n')
				            clear_buffer();
						
				    	flag_edit = toupper(flag_edit);
				    	
				    	if(flag_edit == 'E'){
							flag_return = edit_element(KEY_EMPLOYEES, &id);
							if(flag_return == RETORNAR_MENU_PRINCIPAL){
								printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
								return RETORNAR_MENU_PRINCIPAL;	
							}
							else if(flag_return == RETORNAR_SUBMENU){
								printf("\nRETORNANDO AO MENU FUNCIONARIOS...\n\n");
								return RETORNAR_MENU_PRINCIPAL;	
							}
						}//end if 'E'
						else 
							return 0;//todo processo foi bem sucedido
					}//end if fread
					else{
						printf("\nERRO: Houve um erro na leitura do arquivo. Fechando programa.\n");
						fclose(p_arq);
		        		exit(EXIT_FAILURE);
					}
				}//if fseek
				else{
					printf("\nNao foi possivel posicionar o ponteiro do arquivc. Fechando programa.");
					fclose(p_arq);
					exit(EXIT_FAILURE);
				}				
		
			}//end code block
			break;
		case KEY_GROUPS:{
				Group group;
				FILE *p_arq_products = fopen(ARQ_PRODUCTS, "rb");
				Products products_group;
				
				if(p_arq_products == NULL){
					printf("\nNao foi possivel abrir o arquivo de produtos. Fechando programa.");
					fclose(p_arq);
					exit(EXIT_FAILURE);
				}
				
				if(fseek(p_arq, (id - 1) * sizeof(Group), SEEK_SET) ==  0){
					if(fread(&group, sizeof(Group), 1, p_arq)){
						printf("ID: %02d\nNOME: %-40s\nQUANTIDADE DE PRODUTOS: %d\n", group.id, group.name, group.quant_products);
						printf("\n%-8s | %-30s | %-12s | %-8s", "ID", "NOME DO PRODUTO", "PRECO", "ESTOQUE");
						for(i = 0; i < MAX_ITENS_GROUP; i++){
							if(fseek(p_arq_products, (group.id_products[i] - 1) * sizeof(Products), SEEK_SET) == 0){
								if(fread(&products_group, sizeof(Products), 1, p_arq_products)){
									printf("\n%-08.6ld | %-30.30s | R$ %-9.2f | %-8d", products_group.id, products_group.name, products_group.sale_price, products_group.stock);
								}//end fread de leitura de produtos
							}//end fseek product para leitura de produtos do grupo
							else{
								printf("\nNao foi possivel posicionar o ponteiro do arquivc de produtos. Fechando programa.");
								fclose(p_arq);
								fclose(p_arq_products);
								exit(EXIT_FAILURE);
							}
						}//end for
						printf("\n--------------------------------------------------------------------------------");
						printf("\nSTATUS DO GRUPO: %s\n", group.status == ATIVO ? "ATIVO" : "INATIVO");
						
						fclose(p_arq);
						fclose(p_arq_products);
						
						clear_buffer();
						printf("\nCaso queria editar alguma das informações digite 'E'\n");
						char flag_edit = getchar();
				
				        if(flag_edit != '\n')
				            clear_buffer();
						
				    	flag_edit = toupper(flag_edit);
				    	
				    	if(flag_edit == 'E'){
							flag_return = edit_element(KEY_GROUPS, &id);
							if(flag_return == RETORNAR_MENU_PRINCIPAL){
								printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
								return RETORNAR_MENU_PRINCIPAL;	
							}
							else if(flag_return == RETORNAR_SUBMENU){
								printf("\nRETORNANDO AO MENU FUNCIONARIOS...\n\n");
								return RETORNAR_MENU_PRINCIPAL;	
							}
						}//end if 'E'
						else 
							return 0;//todo processo foi bem sucedido
					}//end if fread
					else{
						printf("\nERRO: Houve um erro na leitura do arquivo. Fechando programa.\n");
						fclose(p_arq);
		        		exit(EXIT_FAILURE);
					}
				}//if fseek
				else{
					printf("\nNao foi possivel posicionar o ponteiro do arquivc. Fechando programa.");
					fclose(p_arq);
					fclose(p_arq_products);
					exit(EXIT_FAILURE);
				}	
		
			}//end code block
			break;
	}//end switch key ship
	
}//end fuction visualize element