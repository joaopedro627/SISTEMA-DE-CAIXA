#include "MODEL_MAIN.H"

int edit_element(const int key_ship, const long *ship_id){
	
	int search_option, edit_option, loop, flag_return;
	
	if(ship_id != NULL){
		
		switch(key_ship){
			case KEY_PRODUCTS: {	
					printf("\nQUAL PARAMETRO DO PRODUTO DESEJA ALTERAR?");
					printf("\n\t[1] = NOME\n\t[2] = PRECO DE VENDA\n\t[3] = PRECO DE COMPRA\n\t[4] = ESTOQUE\n\t[5] = STATUS\n\t[6] = TUDO\n\t[7] = RETORNAR AO MENU PRODUTOS\n\t[8] = RETORNAR AO MENU PRINCIPAL\n\nDIGITE A OPCAO DESEJADA: ");
					scanf("%d", &edit_option);
					
					do{	
						switch(edit_option){
							case 1: edit_name(ARQ_PRODUCTS, KEY_PRODUCTS, *ship_id);	
								return 0;
							case 2: edit_sale_price_product(*ship_id);
								return 0;
							case 3: edit_purchase_price_product(*ship_id);
								return 0;
							case 4: edit_stock_product(*ship_id);
								return 0;
							case 5: edit_status(ARQ_PRODUCTS, KEY_PRODUCTS, *ship_id);
								return 0;
							case 6: edit_name(ARQ_PRODUCTS, KEY_PRODUCTS, *ship_id);
								edit_sale_price_product(*ship_id);
								edit_purchase_price_product(*ship_id);
								edit_stock_product(*ship_id);
								edit_status(ARQ_PRODUCTS, KEY_PRODUCTS, *ship_id);
								return 0;
							case 7: printf("\nRETORNANDO AO MENU PRODUTOS...\n");
								return RETORNAR_SUBMENU;
							case 8:	printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
								return RETORNAR_MENU_PRINCIPAL;	
							default: printf("\nOPCAO INVALIDA ... \nDIGITE UMAS DAS OPCOES: [1] - [2] - [3] - [4] - [5] - [6] - [7] - [8]\n\n");
								break;
						}//end switch edit_option					
					}while(edit_option >= 0 && edit_option <= 8);
				
				}//end code block
				break;
			case KEY_EMPLOYEES: {
				
					printf("\nQUAL PARAMETRO DO FUNCIONARIO DESEJA ALTERAR?");
					printf("\n\t[1] = NOME\n\t[2] = CARGO\n\t[3] = SALARIO\n\t[4] = VOUCHER\n\t[5] = STATUS\n\t[6] = TUDO\n\t[7] = RETORNAR AO MENU FUNCIONARIOS\n\t[8] = RETORNAR AO MENU PRINCIPAL\n\nDIGITE A OPCAO DESEJADA: ");
					scanf("%d", &edit_option);
					
					do{	
						switch(edit_option){
							case 1: edit_name(ARQ_EMPLOYEES, KEY_EMPLOYEES, *ship_id);	
								return 0;
							case 2: edit_position_employee(*ship_id);
								return 0;
							case 3: edit_salary_employee(*ship_id);
								return 0;
							case 4: edit_voucher_employee(*ship_id);
								return 0;
							case 5: edit_status(ARQ_EMPLOYEES, KEY_EMPLOYEES, *ship_id);
								return 0;
							case 6: edit_name(ARQ_EMPLOYEES, KEY_EMPLOYEES, *ship_id);	
								edit_position_employee(*ship_id);
								edit_salary_employee(*ship_id);
								edit_voucher_employee(*ship_id);
								edit_status(ARQ_EMPLOYEES, KEY_EMPLOYEES, *ship_id);
								return 0;
							case 7: printf("\nRETORNANDO AO MENU FUNCIONARIOS...\n");
								return RETORNAR_SUBMENU;
							case 8:	printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
								return RETORNAR_MENU_PRINCIPAL;	
							default: printf("\nOPCAO INVALIDA ... \nDIGITE UMAS DAS OPCOES: [1] - [2] - [3] - [4] - [5] - [6] - [7] - [8]\n\n");
								break;
						}//end switch edit_option					
					}while(edit_option >= 0 && edit_option <= 8);						
			
				}//end code block
				break;
			case KEY_GROUPS: {
				
					printf("\nQUAL PARAMETRO DO GRUPO DESEJA ALTERAR?");
					printf("\n\t[1] = NOME\n\t[2] = ITENS\n\t[3] = STATUS\n\t[4] = TUDO\n\t[5] = RETORNAR AO MENU FUNCIONARIOS\n\t[6] = RETORNAR AO MENU PRINCIPAL\n\nDIGITE A OPCAO DESEJADA: ");
					scanf("%d", &edit_option);
					
					do{	
						switch(edit_option){
							case 1: edit_name(ARQ_GROUPS, KEY_GROUPS, *ship_id);	
								return 0;
							case 2: edit_itens_group(*ship_id);
								return 0;
							case 3: edit_status(ARQ_GROUPS, KEY_GROUPS, *ship_id);
								return 0;
							case 4: edit_name(ARQ_GROUPS, KEY_GROUPS, *ship_id);
								flag_return = edit_itens_group(*ship_id);
								if(flag_return == RETORNAR_SUBMENU){
									printf("\nRETORNANDO AO MENU FUNCIONARIOS...\n");
									return RETORNAR_SUBMENU;
								}
								else if(flag_return == RETORNAR_MENU_PRINCIPAL){
									printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
									return RETORNAR_MENU_PRINCIPAL;	
								}
								edit_status(ARQ_GROUPS, KEY_GROUPS, *ship_id);
								return 0;
							case 5: printf("\nRETORNANDO AO MENU FUNCIONARIOS...\n");
								return RETORNAR_SUBMENU;
							case 6:	printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
								return RETORNAR_MENU_PRINCIPAL;	
							default: printf("\nOPCAO INVALIDA ... \nDIGITE UMAS DAS OPCOES: [1] - [2] - [3] - [4] - [5] - [6] - [7] - [8]\n\n");
								break;
						}//end switch edit_option					
					}while(edit_option >= 0 && edit_option <= 8);				
			
				}//end code block
				break;
		}//end switch
		
	}//end if ship_id
	
	long id;
	
	do{
		
		printf("QUAL PARAMETRO DE BUSCA DESEJA ALTERAR?");
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
		 			id = search_id_generic_list(KEY_EMPLOYEES);
		 			
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
			case 4:	("\nRETORNANDO AO MENU SUBMENU...\n");
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
					
	}while(search_option >= 1 && search_option <= 5);			
	
	switch(key_ship){
		case KEY_PRODUCTS: {
			
				do{
					
					printf("QUAL PARAMETRO DO PRODUTO DESEJA ALTERAR?\n");
					printf("\n\t[1] = NOME\n\t[2] = PRECO DE VENDA\n\t[3] = PRECO DE COMPRA\n\t[4] = ESTOQUE\n\t[5] = STATUS\n\t[6] = TUDO\n\t[7] = RETORNAR AO MENU PRODUTOS\n\t[8] = RETORNAR AO MENU PRINCIPAL\n\nDIGITE A OPCAO DESEJADA: ");
					scanf("%d", &edit_option);
					
					switch(edit_option){
						case 1: edit_name(ARQ_PRODUCTS, KEY_PRODUCTS, id);	
							return 0;
						case 2: edit_sale_price_product(id);
							return 0;
						case 3: edit_purchase_price_product(id);
							return 0;
						case 4: edit_stock_product(id);
							return 0;
						case 5: edit_status(ARQ_PRODUCTS, KEY_PRODUCTS, id);
							return 0;
						case 6: edit_name(ARQ_PRODUCTS, KEY_PRODUCTS, id);
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
			
			}//end code block	
			break;
			
		case KEY_EMPLOYEES: {
			
				printf("\nQUAL PARAMETRO DO FUNCIONARIO DESEJA ALTERAR?");
				printf("\n\t[1] = NOME\n\t[2] = CARGO\n\t[3] = SALARIO\n\t[4] = VOUCHER\n\t[5] = STATUS\n\t[6] = TUDO\n\t[7] = RETORNAR AO MENU FUNCIONARIOS\n\t[8] = RETORNAR AO MENU PRINCIPAL\n\nDIGITE A OPCAO DESEJADA: ");
				scanf("%d", &edit_option);
				
				do{	
					switch(edit_option){
						case 1: edit_name(ARQ_EMPLOYEES, KEY_EMPLOYEES, id);	
							return 0;
						case 2: edit_position_employee(id);
							return 0;
						case 3: edit_salary_employee(id);
							return 0;
						case 4: edit_voucher_employee(id);
							return 0;
						case 5: edit_status(ARQ_EMPLOYEES, KEY_EMPLOYEES, id);
							return 0;
						case 6: edit_name(ARQ_EMPLOYEES, KEY_EMPLOYEES, id);	
							edit_position_employee(id);
							edit_salary_employee(id);
							edit_voucher_employee(id);
							edit_status(ARQ_EMPLOYEES, KEY_EMPLOYEES, id);
							return 0;
						case 7: printf("\nRETORNANDO AO MENU FUNCIONARIOS...\n");
							return RETORNAR_SUBMENU;
						case 8:	printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
							return RETORNAR_MENU_PRINCIPAL;	
						default: printf("\nOPCAO INVALIDA ... \nDIGITE UMAS DAS OPCOES: [1] - [2] - [3] - [4] - [5] - [6] - [7] - [8]\n\n");
							break;
					}//end switch edit_option					
				}while(edit_option >= 0 && edit_option <= 8);					
		
			}//end code block
				break;
			/*case KEY_GROUPS : {
				
				break;
			}*/
	}//end switch key ship edit			
	
}//end fuction edit_element

int edit_name(const char name_arq[], const int key_ship, const long id){

	FILE *p_arq = fopen(name_arq, "rb+");

	
	int loop;
	clear_buffer();
	
	if(p_arq == NULL){//file failure open check
		printf("\nNao foi possivel abrir o arquivo. Fechando programa.");
		exit(EXIT_FAILURE);
	}//end if(file failure open check)
	
	switch(key_ship){
		case KEY_PRODUCTS: {
			
			Products alter_product;
			
			while(fread(&alter_product, sizeof(Products), 1, p_arq) != 0 && id != alter_product.id){}//continua lendo até achar ou acabar

			do{	
				printf("DIGITE O NOVO NOME DO PRODUTO: ");
				fgets(alter_product.name, MAX_PRODUCT_NAME, stdin);
				alter_product.name[strcspn(alter_product.name, "\n")] = 0;
				if(loop = check_empty_text(alter_product.name))
					continue;
				if(loop = check_burst_buffer(alter_product.name, MAX_PRODUCT_NAME))
					continue;
				if(verify_duplicate_name(ARQ_PRODUCTS, KEY_PRODUCTS, alter_product.name)){
					printf("\n[X] ERRO: Produto ja existe! Edicao cancelado.\n");
					fclose(p_arq);
				    return 0;
				}
										
			}while(loop == 1);
			
			clear_buffer();
			printf("\nPara confirmar a alteracao digite 'C'\n");
			char validate = getchar();
		
		    if(validate != '\n')
		        clear_buffer();
			
			validate = toupper(validate);
			
			if(validate == 'C'){
				if(fseek(p_arq, (id - 1) * sizeof(Products), SEEK_SET) ==  0){
					if(fwrite(&alter_product, sizeof(Products), 1, p_arq)){
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
				printf("\nNao houve confirmacao do usuario, cancelando novo produto\n");
				fclose(p_arq);
				return 0;
			}
		
		}//end code block
			break;
		case KEY_EMPLOYEES: {
			
			Employee alter_employee;
			
			while(fread(&alter_employee, sizeof(Employee), 1, p_arq) != 0 && id != alter_employee.id){}//continua lendo até achar ou acabar
									
			do{//verificações do nome do funcionario
			
				clear_buffer();
				printf("DIGITE O NOME NOVO DO FUNCIONARIO: ");
				fgets(alter_employee.name, MAX_EMPLOYEE_NAME, stdin);
				alter_employee.name[strcspn(alter_employee.name, "\n")] = 0;
				if(loop = check_empty_text(alter_employee.name))
					continue;			
				if(loop = check_burst_buffer(alter_employee.name, MAX_EMPLOYEE_NAME))
					continue;
				
				if(verify_duplicate_name(ARQ_EMPLOYEES, KEY_EMPLOYEES, alter_employee.name)){
				    printf("\nERRO: FUNCIONARIO com NOME ja existente! Edicao cancelado.\n");
				    fclose(p_arq);
				    return 0;
				}
				
			}while(loop == 1);
		
			clear_buffer();
			printf("\nPara confirmar a alteracao digite 'C'\n");
			char validate = getchar();
	
	        if(validate != '\n')
	            clear_buffer();
			
	    	validate = toupper(validate);
	    	
	    	if(validate == 'C'){
			
				if(fseek(p_arq, (id - 1) * sizeof(Employee), SEEK_SET) ==  0){
					if(fwrite(&alter_employee, sizeof(Employee), 1, p_arq)){
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
			}
			else{
				printf("\nNao houve confirmacao do usuario, cancelando novo funcionario\n");
				fclose(p_arq);
				return 0;
			}
		
		}//end code block
			break;
		case KEY_GROUPS: {
			
			Group alter_group;
			
			while(fread(&alter_group, sizeof(Group), 1, p_arq) != 0 && id != alter_group.id){}//continua lendo até achar ou acabar
									
			do{//verificações do nome do funcionario
			
				clear_buffer();
				printf("DIGITE O NOME NOVO DO GRUPO: ");
				fgets(alter_group.name, MAX_GROUP_NAME, stdin);
				alter_group.name[strcspn(alter_group.name, "\n")] = 0;
				if(loop = check_empty_text(alter_group.name))
					continue;			
				if(loop = check_burst_buffer(alter_group.name, MAX_GROUP_NAME))
					continue;
				
				if(verify_duplicate_name(ARQ_GROUPS, KEY_GROUPS, alter_group.name)){
				    printf("\nERRO: GRUPO com NOME ja existente! Edicao cancelado.\n");
				    fclose(p_arq);
				    return 0;
				}
				
			}while(loop == 1);
		
			clear_buffer();
			printf("\nPara confirmar a alteracao digite 'C'\n");
			char validate = getchar();
	
	        if(validate != '\n')
	            clear_buffer();
			
	    	validate = toupper(validate);
	    	
	    	if(validate == 'C'){
			
				if(fseek(p_arq, (id - 1) * sizeof(Group), SEEK_SET) ==  0){
					if(fwrite(&alter_group, sizeof(Group), 1, p_arq)){
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
			}
			else{
				printf("\nNao houve confirmacao do usuario, cancelando novo funcionario\n");
				fclose(p_arq);
				return 0;
			}			
		
		}//end code block
			break;
	}//end switch

}//end function edit_name_product

int edit_status(const char name_arq[], const int key_ship, const long id){ 
		
	FILE *p_arq = fopen(name_arq, "rb+");
	int status_flag, loop;
	
	if(p_arq == NULL){//file failure open check
		printf("\nNao foi possivel abrir o arquivo. Fechando programa.");
		fclose(p_arq);
		exit(EXIT_FAILURE);
	}//end if(file failure open check)
	
	clear_buffer();
	
	switch(key_ship){
		case KEY_PRODUCTS: {
			
				Products alter_product;
				
				while (fread(&alter_product, sizeof(Products), 1, p_arq) != 0 && id != alter_product.id){}//continua lendo até achar ou acabar
				
				printf("\n\t[1] ATIVO\t[2] DESATIVADO\nDIGITE O NOVO STATUS DO PRODUTO: ");
						
				do{
					
					scanf("%d", &status_flag);
					
					if(status_flag == 1){
						printf("\n%s\n", alter_product.status == ATIVO ? "Produto ja estava ATIVO" : "Produto ATIVO");
						alter_product.status = ATIVO;
						loop = 0;
					}
					else if(status_flag == 2){
						printf("\n%s\n", alter_product.status == INATIVO ? "Produto ja estava DESATIVADO" : "Produto DESATIVADO");
						alter_product.status = INATIVO;
						loop = 0;
					}
					else
						printf("\nOpcao INVALIDA ... \n\t[1] ATIVO\t[2] DESATIVADO\nDigite o novo Status do produto: ");
												
				}while(loop == 1);//end do-while 
				
				clear_buffer();
				
				printf("\nPara confirmar a alteracao digite 'C'\n");
				char validate_product = getchar();
			
			    if(validate_product != '\n')
			        clear_buffer();
				
				validate_product = toupper(validate_product);
	
				if(validate_product == 'C'){
					if(fseek(p_arq, (id - 1) * sizeof(Products), SEEK_SET) ==  0){
						if(fwrite(&alter_product, sizeof(Products), 1, p_arq)){
							printf("\nGravacao concluida com exito.\n");
							fclose(p_arq);
							return 0;
						}
						else{
							printf("\n\nHouve um erro na gravacao do arquivo. Fechando programa.\n");
							fclose(p_arq);
							exit(EXIT_FAILURE);
						}
					}//end if fseek
					else{
						printf("\nNao foi possivel posicionar o ponteiro do arquivc. Fechando programa.");
						fclose(p_arq);
						exit(EXIT_FAILURE);
					}			
				}//end if 'C'
				
			}//end code block
			break;
		case KEY_EMPLOYEES: {
			
				Employee alter_employee;
				
				while (fread(&alter_employee, sizeof(Employee), 1, p_arq) != 0 && id != alter_employee.id){}//continua lendo até achar ou acabar
				
				printf("\n\t[1] ATIVO\t[2] DESATIVADO\nDIGITE O NOVO STATUS DO FUNCIONARIO: ");
						
				do{
					scanf("%d", &status_flag);
					if(status_flag == 1){
						printf("\n%s\n", alter_employee.status == ATIVO ? "Funcionario ja estava ATIVO" : "Funcionario ATIVO");
						alter_employee.status = ATIVO;
						loop = 0;
					}
					else if(status_flag == 2){
						printf("\n%s\n", alter_employee.status == INATIVO ? "Funcionario ja estava DESATIVADO" : "Funcionario DESATIVADO");
						alter_employee.status = INATIVO;
						loop = 0;
					}
					else
						printf("\nOpcao INVALIDA ... \n\t[1] ATIVO\t[2] DESATIVADO\nDigite o novo Status do funcionario: ");
												
				}while(loop == 1);//end do-while 
			
				clear_buffer();
				printf("\nPara confirmar a alteracao digite 'C'\n");
				char validate_employee = getchar();
		
		        if(validate_employee != '\n')
		            clear_buffer();
				
		    	validate_employee = toupper(validate_employee);
		    	
		    	if(validate_employee == 'C'){
		    		
					if(fseek(p_arq, (id - 1) * sizeof(Employee), SEEK_SET) ==  0){
						if(fwrite(&alter_employee, sizeof(Employee), 1, p_arq)){
						printf("\nGravacao concluida com exito.\n");
						fclose(p_arq);
						return 0;
						}
						else{
							printf("\n\nHouve um erro na gravacao do arquivo. Fechando programa.\n");
							fclose(p_arq);
							exit(EXIT_FAILURE);
						}
					}//end if fseek
					else{
						printf("\nNao foi possivel posicionar o ponteiro do arquivc. Fechando programa.");
						fclose(p_arq);
						exit(EXIT_FAILURE);
					}			
				}//end if 'C'
						
			}//end code block
			break;
		case KEY_GROUPS: {
			
				Group alter_group;
				
				while (fread(&alter_group, sizeof(Group), 1, p_arq) != 0 && id != alter_group.id){}//continua lendo até achar ou acabar
				
				printf("\n\t[1] ATIVO\t[2] DESATIVADO\nDIGITE O NOVO STATUS DO GRUPO: ");
						
				do{
					scanf("%d", &status_flag);
					if(status_flag == 1){
						printf("\n%s\n", alter_group.status == ATIVO ? "Grupo ja estava ATIVO" : "Grupo ATIVO");
						alter_group.status = ATIVO;
						loop = 0;
					}
					else if(status_flag == 2){
						printf("\n%s\n", alter_group.status == INATIVO ? "Grupo ja estava DESATIVADO" : "Grupo DESATIVADO");
						alter_group.status = INATIVO;
						loop = 0;
					}
					else
						printf("\nOpcao INVALIDA ... \n\t[1] ATIVO\t[2] DESATIVADO\nDigite o novo Status do grupo: ");
												
				}while(loop == 1);//end do-while 
			
				clear_buffer();
				printf("\nPara confirmar a alteracao digite 'C'\n");
				char validate_group = getchar();
		
		        if(validate_group != '\n')
		            clear_buffer();
				
		    	validate_group = toupper(validate_group);
		    	
		    	if(validate_group == 'C'){
		    		
					if(fseek(p_arq, (id - 1) * sizeof(Group), SEEK_SET) ==  0){
						if(fwrite(&alter_group, sizeof(Group), 1, p_arq)){
						printf("\nGravacao concluida com exito.\n");
						fclose(p_arq);
						return 0;
						}
						else{
							printf("\n\nHouve um erro na gravacao do arquivo. Fechando programa.\n");
							fclose(p_arq);
							exit(EXIT_FAILURE);
						}
					}//end if fseek
					else{
						printf("\nNao foi possivel posicionar o ponteiro do arquivc. Fechando programa.");
						fclose(p_arq);
						exit(EXIT_FAILURE);
					}			
			}//end if 'C'
			
		}//end code block
		break;
	}//end switch
	
	printf("\nNao houve confirmacao do usuario, cancelando alteraçao\n");
	fclose(p_arq);
	return 0;
	
}//end function edit_status_product

int desativate_element(const int key_ship){
	
	long id;
	int search_option;
	
	do{
		
		printf("QUAL PARAMETRO DE BUSCA DESEJA ALTERAR?");
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
		 			id = search_id_generic_list(KEY_EMPLOYEES);
		 			
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
			case 4:	("\nRETORNANDO AO MENU SUBMENU...\n");
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
					
	}while(search_option >= 1 && search_option <= 5);
	
	if(key_ship == KEY_PRODUCTS){
		edit_status(ARQ_PRODUCTS, KEY_PRODUCTS, id);
		printf("\nPRODUTO DESATIVADO COM SUCESSO\n\nRETORNANDO AO MENU PRODUTOS...\n\n");
			return 0;
	}
	else if(key_ship == KEY_EMPLOYEES){
		edit_status(ARQ_EMPLOYEES, KEY_EMPLOYEES, id);
		printf("\nFUNCIONARIO DESATIVADO COM SUCESSO\n\nRETORNANDO AO MENU FUNCIONARIOS...\n\n");
			return 0;	
	}
	else{
		edit_status(ARQ_GROUPS, KEY_GROUPS, id);
		printf("\nGRUPO DESATIVADO COM SUCESSO\n\nRETORNANDO AO MENU FUNCIONARIOS...\n\n");
			return 0;
	}
	
}//end function desativate_employee