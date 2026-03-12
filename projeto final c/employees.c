#include "MODEL_MAIN.H"

int options_employees(){
	
	int flag_return, user_option;

	do{
	
		printf(" ----- MENU FUNCIONARIOS ----- \n\n");
		printf("[1] = LISTA DE FUNCIONARIOS\n[2] = NOVO FUNCIONARIO\n[3] = DESATIVAR FUNCIONARIO\n");
		printf("[4] = ALTERAR INFOR.FUNCIONARIO\n[5] = VISUALIZAR FUNCIONARIO\n[6] = ATUALIZAR VALORES Salario/Voucher\n[7] = RETORNANDO AO MENU PRINCIPAL\n[8] = SAIR DO PROGRAMA\n\n");
		printf("DIGITE A OPCAO DESEJADA: ");								//[6] atualizar valores. S/V
		scanf("%d", &user_option);
		
		switch(user_option){
			case 1: printf("\nINCIANDO LISTA DE FUNCIONARIOS ... \n");
				flag_return = list_employees();
				if(flag_return == RETORNAR_MENU_PRINCIPAL)
					return 0;
				break;
			case 2: printf("\nINCIANDO NOVO FUNCIONARIO... \n\n");
				new_employee();
				break;//end case 2
			case 3: printf("\nINCIANDO DESATIVAR FUNCIONARIO... \n");
				flag_return = desativate_employee();
				if(flag_return == RETORNAR_MENU_PRINCIPAL)
					return 0;
				break;
			case 4: printf("\nINICIANDO ALTERAR INFORMACOES DO FUNCIONARIO\n\n");
				flag_return = edit_employee();
				if(flag_return == RETORNAR_MENU_PRINCIPAL)
					return 0;
				break;
			case 5: printf("\nINICIANDO VISUALIZAR FUNCIONARIO\n\n");
				flag_return = search_employee();
				if(flag_return == RETORNAR_MENU_PRINCIPAL)
					return 0;
				break;
			case 6: printf("\nINICIANDO ATUALIZAR VALORES S/V\n\n");
				flag_return = update_valors();
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

int list_employees(){
	
	FILE *p_arq = fopen(ARQ_EMPLOYEES, "rb");
	Employee file_employees;
	long pag = 1;
	int filter_option, contador = 1, flag_return;
	char flag_filter;
	
	if(p_arq == NULL){//file failure open check
		printf("\nNao foi possivel abrir o arquivo. Fechando programa.");
		exit(EXIT_FAILURE);
	}
	
	//variaveis auxiliares para alocação dinamica
	long tam_bytes_arq;
	size_t tam_array = 0, i = 0;
	
	fseek(p_arq, 0, SEEK_END);
	
	if(ftell(p_arq) != 0){
		tam_bytes_arq = ftell(p_arq);
		tam_array = (size_t)tam_bytes_arq / sizeof(Employee);
	}
	else{
		printf("\nNenhum funcionario cadastrado.\n");
    	fclose(p_arq);
    	return 0;
	}
	
	Employee *employees_array = malloc(tam_array * sizeof(Employee));
	
	if(employees_array == NULL){
		printf("\nNao foi possivel alocar memoria.Verifique a capacidade maxima de RAM do computador\n");
		printf("\nFechando programa.");
		fclose(p_arq);
		exit(EXIT_FAILURE);
	}
	
	rewind(p_arq);
	
	tam_array = fread(employees_array, sizeof(Employee), tam_array, p_arq);
	
	fclose(p_arq);
	
	long max_pags = tam_array / 20;
	if (tam_array % 20 != 0)
	    max_pags++;
		
	printf("\n----- LISTA DE FUNCIONARIOS ---- \t\t[%ld] NUMEROS DE PAGINA\n", max_pags);
	printf("\n\n----- Pagina %ld ----\n\n", pag);
	
   	for(i = 0; i < tam_array; i++, contador++){
   		
   		printf("ID: %.6d | NOME: %s | CARGO: %s | SALARIO: %.2f | VOUCHER: %.2f |  ", employees_array[i].id, employees_array[i].name, employees_array[i].position, employees_array[i].salary, employees_array[i].voucher);
		printf("STATUS: %s\n", employees_array[i].status == ATIVO ? "ATIVO" : "INATIVO");
			
		if(contador % 20 == 0 && i + 1 != tam_array){
			clear_buffer();
			flag_return = walk_pags(&contador, &pag, max_pags);
			if(flag_return == RETORNAR_SUBMENU){
				printf("\nRETORNANDO AO MENU FUNCIONARIOS...\n");
				free(employees_array);
				return RETORNAR_SUBMENU;
			}
			else if(flag_return == RETORNAR_MENU_PRINCIPAL){
				printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
				free(employees_array);
				return RETORNAR_MENU_PRINCIPAL;
			}	
			else if(flag_return == RETORNAR_FUNCAO)
				printf("\nFuncao Lista de Funcionarios.\n");
				
				clear_buffer();
				printf("\nPara acessar o painel de filtros digite 'F'");
				i = ((pag - 1) * 20) - 1;//troca o valor do i para caminhar entre paginas
				flag_filter = getchar();

	            if(flag_filter != '\n') 
	            	clear_buffer();
				
	        	flag_filter = toupper(flag_filter);
	        	
	        	if(flag_filter == 'F'){
	        		
	        		flag_return = filters_employees(employees_array, tam_array);
        			if(flag_return == RETORNAR_SUBMENU){
						printf("\nRETORNANDO AO MENU FUNCIONARIOS...\n\n");
						free(employees_array);
						return RETORNAR_SUBMENU;	
					}
					else if(flag_return == RETORNAR_FUNCAO)
						printf("\nFuncao Lista de Funcionarios.\n");
					else if(flag_return == RETORNAR_MENU_PRINCIPAL){
						free(employees_array);
						return RETORNAR_MENU_PRINCIPAL;
					}	
        			else if(flag_return == FILTRO_BEM_SUCEDIDO){
        				printf("\n--- Fim dos registros. Saindo da funcao\n\n");
        				free(employees_array);
        				return 0;
					}
				}//if 'F'		
				printf("\n\n----- Pagina %ld ----\n\n", pag);
		}//end contador	

	}//end for para impressao da lista
   	printf("\n--- Fim dos registros.\n\n");
   	free(employees_array);
	return 0;//retorna a ultima função
		
}//end function list_employees

	int filters_employees(Employee array[], size_t tam_array){
		
		int option_filter, option_filter_intern, flag_return, contador;
		long i;
		
		//variables og_array
		long pag = 1;
		long max_pags = tam_array / 20;
			if (tam_array % 20 != 0)
			    max_pags++;
		           
		printf("\nFILTRAR POR:\n\t[1] = ATIVO\\INATIVO\n\t[2] = ID.DECRESCENTE\n\t[3] = ORDEM.ALFABETICA\n\t[4] = RETORNAR A FUNCAO ANTERIOR\n\t[5] = RETORNAR AO MENU DE FUNCIONARIOS\n\t[6] = RETORNAR AO MENU PRINCIPAL\n\nDIGITE A OPCAO DESEJADA: ");
		do{
			scanf("%d", &option_filter);
			
			switch(option_filter){
				case 1:
				flag_return = status_filter_employees(array, tam_array);
					if(flag_return == RETORNAR_SUBMENU)
						return RETORNAR_SUBMENU;
					else if(flag_return == FILTRO_BEM_SUCEDIDO)
						return FILTRO_BEM_SUCEDIDO;
					else if(flag_return == RETORNAR_MENU_PRINCIPAL)
						return RETORNAR_MENU_PRINCIPAL;
				case 2: printf("\n----- LISTA DE FUNCIONARIOS ---- \t\t[%ld] NUMEROS DE PAGINA\n", max_pags);
					printf("\n\n----- Pagina %ld ----\n\n", pag);
				   	for(i = tam_array - 1; i >= 0; i--, contador++){
				   		
				   		printf("ID: %.6d | NOME: %s | CARGO: %s | SALARIO: %.2f | VOUCHER: %.2f | ", array[i].id, array[i].name, array[i].position, array[i].salary, array[i].voucher);
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
				case 3: flag_return = alphabetical_filter_employees(array, tam_array, max_pags);
					if(flag_return == RETORNAR_SUBMENU)
						return RETORNAR_SUBMENU;
					else if(flag_return == FILTRO_BEM_SUCEDIDO)
						return FILTRO_BEM_SUCEDIDO;
				case 4: return RETORNAR_FUNCAO;
				case 5: return RETORNAR_SUBMENU;
				case 6: return RETORNAR_MENU_PRINCIPAL;
				default: printf("\nOPCAO INVALIDA ...\nDIGITE UMAS DAS OPCOES: [1] - [2] - [3] - [4] - [5] - [6]\n\n");
					break;
			}//end switch option_filter
		}while(option_filter >= 1 && option_filter <= 6);//end do-while switch (option_filter)
		
	}//end function filters_employees

		int status_filter_employees(Employee array[], size_t tam_array){
			
			size_t i, j;
			int status_option, contador = 1, flag_return, flag_filter;
			
			//variables og_array
			long pag = 1;
			long max_pags = tam_array / 20;
			if (tam_array % 20 != 0)
			    max_pags++;
			//variables inactive_array
			size_t qtd_inactive_employees = 0;
			
			for(i = 0; i < tam_array; i++){//for para preenchimento de vetor de produtos desativados
				if(array[i].status == INATIVO)
					qtd_inactive_employees++;
			}
			long pag_inactive = 1;
			long max_pags_inactive = qtd_inactive_employees / 20;
			if(qtd_inactive_employees % 20 != 0)
				   max_pags_inactive++;
			size_t qtd_active_employees = tam_array - qtd_inactive_employees;
			
			long pag_active = 1;
			long max_pags_active = qtd_active_employees / 20;
			if (qtd_active_employees % 20 != 0)
				   max_pags_active++;
			
			printf("\nFILTRAR POR:\n\t[1] = ATIVO\n\t[2] = INATIVO\n\t[3] = AMBOS\n\t[4] = RETORNAR AO MENU FUNCIONARIOS\n\t[5] = RETORNAR AO MENU PRINCIPAL\n\nDIGITE A OPCAO DESEJADA: ");
			
			do{
		        scanf("%d", &status_option);
		        
		        switch(status_option){
		        	case 1: if(qtd_active_employees == 0){	
		        		printf("\nNAO HA FUNCIONARIOS ATIVOS NA LISTA\nRETORNANDO AO MENU FUNCIONARIOS\n");
		        			return RETORNAR_SUBMENU;
						}
						printf("\n----Lista filtro ATIVO---- \t\t[%ld] NUMEROS DE PAGINA\n", max_pags_active);
						printf("\n\n----- Pagina %ld ----\n\n", pag_active);
		        		Employee *employees_active = malloc(qtd_active_employees * sizeof(Employee));
		        		
		        		j = 0;
		        		
		      			for(i = 0; i < tam_array; i++){
	        				if(array[i].status == ATIVO){
	        					employees_active[i] = array[i];
	        					j++;
							}
        				}//end for para preenchimento do vetor de ativos
		        		
	        			for(i = 0; i < qtd_active_employees; i++, contador++){
		        				
							printf("ID: %.6d | NOME: %s | CARGO: %s | SALARIO: %.2f | VOUCHER: %.2f | STATUS: ATIVO", employees_active[i].id, employees_active[i].name, employees_active[i].position, employees_active[i].salary, employees_active[i].voucher);
						
							if(contador % 20 == 0 && i + 1 != qtd_active_employees){
								clear_buffer(); 
								flag_return = walk_pags(&contador, &pag_active, max_pags_inactive);
								if(flag_return == RETORNAR_SUBMENU){
									free(employees_active);
									return RETORNAR_SUBMENU;
								}
									
								else if(flag_return == RETORNAR_FUNCAO)
									printf("\nFuncao Lista de Funcionarios > Filtro de Status.\n");
								printf("\n\n----- Pagina %ld ----\n\n", pag_active);
								i = ((pag_active - 1) * 20) - 1;//troca o valor do i para caminhar entre paginas
							}//end contador
							
						}//end for para impressao
							
						free(employees_active);
						
						printf("\n-------------------\n");
										
						return FILTRO_BEM_SUCEDIDO;
		        	case 2: if(qtd_inactive_employees == 0){	
		        		printf("\nNAO HA FUNCIONARIOS INATIVOS NA LISTA\nRETORNANDO AO MENU FUNCIONARIOS\n");
		        		return RETORNAR_SUBMENU;
						}
					
					 	printf("\n----Lista filtro INATIVO----\t\t[%ld] NUMEROS DE PAGINA\n", max_pags_inactive);
						printf("\n\n----- Pagina %ld ----\n\n", pag_inactive);
		        		Employee *employees_inactive = malloc(qtd_inactive_employees * sizeof(Employee));
		        		
		        		j = 0;
		        		
		      			for(i = 0; i < tam_array; i++){
	        				if(array[i].status == INATIVO){
	        					employees_inactive[i] = array[i];
	        					j++;
							}
        				}//end for para preenchimento do vetor de inativos
		        		
	        			for(i = 0; i < qtd_inactive_employees; i++, contador++){
	        					
							printf("ID: %.6d | NOME: %s | CARGO: %s | SALARIO: %.2f | VOUCHER: %.2f | STATUS: INATIVO", employees_inactive[i].id, employees_inactive[i].name, employees_inactive[i].position, employees_inactive[i].salary, employees_inactive[i].voucher);
								
							if(contador % 20 == 0 && i + 1 != qtd_inactive_employees){
								clear_buffer();
								flag_return = walk_pags(&contador, &pag_inactive, max_pags_inactive);
								if(flag_return == RETORNAR_SUBMENU){
									free(employees_inactive);
									return RETORNAR_SUBMENU;
								}
								else if(flag_return == RETORNAR_FUNCAO)
									printf("\nFuncao Lista de Funcionarios > Filtro de Status.\n");
								printf("\n\n----- Pagina %ld ----\n\n", pag_inactive);
								i = ((pag_inactive - 1) * 20) - 1;//troca o valor do i para caminhar entre paginas
							}//end contador
									
	        			}//end for para impressao		
						
						free(employees_inactive);
						printf("\n-------------------\n");
	        			return FILTRO_BEM_SUCEDIDO;
		        	case 3: printf("\n----Lista AMBOS Status---- \t\t[%ld] NUMEROS DE PAGINA\n", max_pags);
						printf("\n\n----- Pagina %ld ----\n\n", pag);
						for(i = 0; i < tam_array; i++, contador++){
			        		
							printf("ID: %.6d | NOME: %s | CARGO: %s | SALARIO: %.2f | VOUCHER: %.2f | ", employees_inactive[i].id, employees_inactive[i].name, employees_inactive[i].position, employees_inactive[i].salary, employees_inactive[i].voucher);
							printf(" STATUS: %s\n",array[i].status == ATIVO ? "ATIVO" : "INATIVO");
							
							if(contador % 20 == 0 && i + 1 != tam_array){
								clear_buffer();
								flag_return = walk_pags(&contador, &pag, max_pags);
								if(flag_return == RETORNAR_SUBMENU)
									return RETORNAR_SUBMENU;
								else if(flag_return == RETORNAR_FUNCAO)
									printf("\nFuncao Lista de Funcionarios > Filtro de Status.\n");	
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
				
		}//end function status_filter_employees

	int alphabetical_filter_employees(Employee array[], size_t tam_array, long max_pags){
		
		int contador = 1, flag_return;
		long i, pag = 1;
		
		qsort(array, tam_array, sizeof(Employee), comparar_nomes_employees);
	
		printf("\n----- LISTA DE FUNCIONARIOS ---- \t\t[%ld] NUMEROS DE PAGINA\n", max_pags);
		printf("\n\n----- Pagina %ld ----\n", pag);
		for(i = 0; i < tam_array; i++, contador++){
			
	   		printf("ID: %.6d | NOME: %s | CARGO: %s | SALARIO: %.2f | VOUCHER: %.2f | ", array[i].id, array[i].name, array[i].position, array[i].salary, array[i].voucher);
			printf(" STATUS: %s\n",array[i].status == ATIVO ? "ATIVO" : "INATIVO");
			
			if(contador % 20 == 0){
				flag_return = walk_pags(&contador, &pag, max_pags);
				clear_buffer();
				if(flag_return == RETORNAR_SUBMENU)
					return RETORNAR_SUBMENU;
				else if(flag_return == RETORNAR_FUNCAO)
					printf("\nFuncao Lista de Funcionarios > Filtro de Ordem Alfabetica.\n");
				printf("\n\n----- Pagina %ld ----\n\n", pag);
				i = ((pag - 1) * 20) - 1;//troca o valor do i para caminhar entre paginas
			}//end contador
	
		}//end for para impressao
		return FILTRO_BEM_SUCEDIDO;
	}//end function alphabetical_filter_employees

		int comparar_nomes_employees(const void *n1, const void *n2){
			
			const Employee *nome_1 = (Employee *)n1;
			const Employee *nome_2 = (Employee *)n2;
			
			return _stricmp(nome_1->name, nome_2->name);
		}//end function comparar_nomes_employees

void new_employee(){
	
	FILE *p_arq = fopen(ARQ_EMPLOYEES, "ab+");
	Employee record_employee;
	int loop = 0;
	int flag_salarys, flag_return;
	
	if(p_arq){
		
		do{//verificações do nome do funcionario
			record_employee.id = get_next_id_group(ARQ_EMPLOYEES, KEY_EMPLOYEES);
			
			clear_buffer();
			printf("DIGITE O NOME DO NOVO FUNCIONARIO: ");
			fgets(record_employee.name, MAX_GROUP_NAME, stdin);
			record_employee.name[strcspn(record_employee.name, "\n")] = 0;
			if(loop = check_empty_text(record_employee.name))
				continue;			
			if(loop = check_burst_buffer(record_employee.name, MAX_EMPLOYEE_NAME))
				continue;
			
			if(warning_duplicate_name_employees(record_employee.name)){
			    printf("\nERRO: FUNCIONARIO com NOME ja existente! Cadastro cancelado.\n");
			    fclose(p_arq);
			    return;
			}
			
		}while(loop == 1);
		
		clear_buffer();
		printf("\nPara acessar salarios, cargos e vouchers ja existentes, digite 'A'\n");
		flag_salarys = getchar();

        if(flag_salarys != '\n')
            clear_buffer();
		
    	flag_salarys = toupper(flag_salarys);
    	
    	if(flag_salarys == 'A')
        		list_salarys_employees();
						
		do{//verificações do salario do funcionario
			printf("\nDIGITE O SALARIO DO FUNCIONARIO: ");
			scanf("%f", &record_employee.salary);
			loop = validate_price(record_employee.salary);
		}while(loop == 1);
		
		do{//verificações do cargo do funcionario
			clear_buffer();
			printf("DIGITE O CARGO DO NOVO FUNCIONARIO: ");
			fgets(record_employee.position, MAX_POSITION_NAME, stdin);
			record_employee.position[strcspn(record_employee.position, "\n")] = 0;
			if(loop = check_empty_text(record_employee.position))
				continue;	
			if(loop = check_burst_buffer(record_employee.position, MAX_POSITION_NAME))
				continue;
				
			if (warning_similar_names_position_employees(record_employee.position) > 0) {
			    char confirma;
			    printf("\nO cargo '%s' parece com os itens acima.", record_employee.position);
			    printf("\nDeseja cadastrar mesmo assim? [S/N]: ");
			    scanf(" %c", &confirma); 
			    clear_buffer(); // Limpa buffer
			
			    if (toupper(confirma) != 'S') {
			        printf("\nCadastro cancelado pelo usuario.\n");
			        fclose(p_arq);
			        return;
			    }
			}
			
		}while(loop == 1);
		
		do{//verificações do voucher do funcionario
			printf("\nDIGITE O VOUCHER DO FUNCIONARIO: ");
			scanf("%f", &record_employee.voucher);
			if(record_employee.voucher <= 0)
				record_employee.voucher = 0;
			clear_buffer();//case user digit letters
		}while(loop == 1);
		
		record_employee.status = ATIVO;
		
		clear_buffer();
		printf("\nPara confirmar o novo funcionario digite 'C'\n");
		char validate_employee = getchar();

        if(validate_employee != '\n')
            clear_buffer();
		
    	validate_employee = toupper(validate_employee);
    	
    	if(validate_employee == 'C'){
		
			if(fwrite(&record_employee, sizeof(Employee), 1, p_arq)){
				printf("\n\nGravacao concluida com exito\n\n");
				fclose(p_arq);
				return;
			}
			else{
				printf("\n\nHouve um erro na gravacao do arquivo. Fechando programa.\n");
				fclose(p_arq);
				exit(EXIT_FAILURE);
			}
		}
		else{
			printf("\nNao houve confirmacao do usuario, cancelando novo funcionario\n");
			fclose(p_arq);
			return;
		}
					
	}// end if p_arq	
	else{
		printf("Nao foi possivel criar o arquivo! fechando o programa!\n");
		exit(EXIT_FAILURE);
	}//end else
		
}//end fuction new_employee	
	
	void list_salarys_employees(){
		
		FILE *p_arq = fopen(ARQ_EMPLOYEES, "rb");
		int id = 0, ja_impresso, num;
		
		if(p_arq == NULL){
			printf("\nNao foi possivel abrir o arquivo. Fechando programa.");
			exit(EXIT_FAILURE);
		}
		
		long tam_bytes_arq;
		size_t tam_array = 0, i, j;
	
		fseek(p_arq, 0, SEEK_END);
		
		if(ftell(p_arq) != 0){
			tam_bytes_arq = ftell(p_arq);
			tam_array = (size_t)tam_bytes_arq / sizeof(Employee);
		}
		else{
			fclose(p_arq);
			return;// nao ha conteudo no arquivo
		}
			
	
		Employee *employees_array = malloc(tam_array * sizeof(Employee));
		
		if(employees_array == NULL){
			printf("\nNao foi possivel alocar memoria.Verifique a capacidade maxima de RAM do computador\n");
			printf("\nFechando programa.");
			fclose(p_arq);
			free(employees_array);
			exit(EXIT_FAILURE);
		}
		
		rewind(p_arq);
		
		tam_array = fread(employees_array, sizeof(Employee), tam_array, p_arq);
		
		for(i = 0; i < tam_array; i++){
			ja_impresso = 0;
			
			for(j = 0; j < i; j++){
				if(employees_array[i].salary == employees_array[j].salary && strcmp(employees_array[i].position, employees_array[j].position) == 0){
					ja_impresso = 1;
					break;
				}//end if
					
			}//end for j
			
			if(ja_impresso == 0)
				printf("ID: %d | CARGO: %s | SALARIO: %.2f | VOUCHER: %.2f\n", employees_array[i].id , employees_array[i].position , employees_array[i].salary, employees_array[i].voucher);
				
		}//end for i
		
		free(employees_array);
		fclose(p_arq);
		return;
		
	}//end function list_salarys	
	
int desativate_employee(){
	
	int search_option, id;
	
	printf("\nQUAL FUNCIONARIO DESEJA ALTERAR?");
	printf("\n[1] = BUSCAR POR ID\n[2] = BUSCAR PELA LISTA\n[3] = BUSCAR POR NOME\n[4] = RETORNAR AO MENU FUNCIONARIOS\n[5] = RETORNAR AO MENU PRINCIPAL\n\nDIGITE A OPCAO DESEJADA: ");
	
	do{
		scanf("%d", &search_option);
		
		switch(search_option){
			case 1: id = search_id_generic(ARQ_EMPLOYEES, KEY_EMPLOYEES);
				if(id == 0){
					printf("\nFUNCIONARIO NAO ENCONTRADO. RETORNANDO AO MENU FUNCIONARIOS...\n\n");
					return 0;
				}//end if(id == 0)
				
				edit_status(ARQ_EMPLOYEES, KEY_EMPLOYEES, id);
				printf("\nFUNCIONARIO DESATIVADO COM SUCESSO\n\nRETORNANDO AO MENU FUNCIONARIOS...\n\n");
					return 0;				
			case 2: id = search_id_generic_list(KEY_EMPLOYEES);
			
				if(id == 0){
					printf("\nFUNCIONARIO NAO ENCONTRADO. RETORNANDO AO MENU FUNCIONARIOS...\n\n");
					return 0;
				}//end if(id == 0)
				if(id == RETORNAR_SUBMENU){
					printf("\nRETORNANDO AO MENU FUNCIONARIOS...\n");
					return RETORNAR_SUBMENU;
				}//end if(id == 0)
				if(id == RETORNAR_MENU_PRINCIPAL){
					printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
					return RETORNAR_MENU_PRINCIPAL;
				}//end if(id == 0)
				edit_status(ARQ_EMPLOYEES, KEY_EMPLOYEES, id);
				printf("\nFUNCIONARIO DESATIVADO COM SUCESSO\n\nRETORNANDO AO MENU FUNCIONARIOS...\n\n");
					return 0;		
			case 3: id = search_name_employee();
			
				if(id == 0){
					printf("\nFUNCIONARIO NAO ENCONTRADO. RETORNANDO AO MENU FUNCIONARIOS...\n\n");
					return RETORNAR_SUBMENU;
				}//end if(id == 0)
			
				edit_status(ARQ_EMPLOYEES, KEY_EMPLOYEES, id);
				printf("\nFUNCIONARIO DESATIVADO COM SUCESSO\n\nRETORNANDO AO MENU FUNCIONARIOS...\n\n");
					return 0;		
			case 4: printf("\nRETORNANDO AO MENU FUNCIONARIOS...\n");
				return RETORNAR_SUBMENU;
			case 5: printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
				return RETORNAR_MENU_PRINCIPAL;
			default:  printf("\nOPCAO INVALIDA ...\nDIGITE UMAS DAS OPCOES: [1] - [2] - [3] - [4] - [5]\n\n");
				break;			
		}//end switch option_search
		
	}while(search_option >= 1 && search_option <= 5);//end do-while switch(search_option)
	
}//end function desativate_employee

int edit_employee(){
	
	long id;
	int search_option, edit_option, loop;
	
	printf("QUAL FUNCIONARIO DESEJA ALTERAR?");
	printf("\n[1] = BUSCAR POR ID\n[2] = BUSCAR PELA LISTA\n[3] = BUSCAR POR NOME\n[4] = RETORNAR AO MENU FUNCIONARIOS\n[5] = RETORNAR AO MENU PRINCIPAL\n\nDIGITE A OPCAO DESEJADA: ");
	
	do{
		scanf("%d", &search_option);
		
		switch(search_option){
			
			case 1:
				id = search_id_generic(ARQ_EMPLOYEES, KEY_EMPLOYEES);
				
				if(id == 0){
					printf("\nFUNCIONARIO NAO ENCONTRADO. RETORNANDO AO MENU FUNCIONARIOS...\n\n");
					return 0;
				}//end if(id == 0)
				
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
				
				break;//break case 1 (search_option)
			case 2: id = search_id_generic_list(KEY_EMPLOYEES);
			
				if(id == 0){
					printf("\nFUNCIONARIO NAO ENCONTRADO. RETORNANDO AO MENU FUNCIONARIOS...\n\n");
					return 0;
				}//end if(id == 0)
				if(id == RETORNAR_SUBMENU){
					printf("\nRETORNANDO AO MENU FUNCIONARIOS...\n");
					return RETORNAR_SUBMENU;
				}//end if(id == 0)
				if(id == RETORNAR_MENU_PRINCIPAL){
					printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
					return RETORNAR_MENU_PRINCIPAL;
				}//end if(id == 0)
					
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
					
				break;//break case 2 (search_option)
			case 3: id = search_name_employee();
			
				if(id == 0){
					printf("\nFUNCIONARIO NAO ENCONTRADO. RETORNANDO AO MENU FUNCIONARIOS...\n\n");
					return RETORNAR_SUBMENU;
				}//end if(id == 0)
				
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
				
				break;//break case 3 (search_option)
			case 4:	("\nRETORNANDO AO MENU FUNCIONARIOS...\n");
				return RETORNAR_SUBMENU;
			case 5: printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
				return RETORNAR_MENU_PRINCIPAL;
			default: printf("\nOPCAO INVALIDA ... \nDIGITE UMAS DAS OPCOES: [1] - [2] - [3] - [4] - [5]\n\n");
				break;
		}//end switch search_option
			
	}while(search_option >= 1 && search_option <= 5);//end do_while(swicth(search_option)
	
}//end fuction edit_employee
	
	int edit_position_employee(int id_employee){
	
		FILE *p_arq = fopen(ARQ_EMPLOYEES, "rb+");
		Employee alter_employee;
		
		int loop;
		
		if(p_arq == NULL){//file failure open check
			printf("\nNao foi possivel abrir o arquivo. Fechando programa.");
			exit(EXIT_FAILURE);
		}//end if(file failure open check)
		
		while (fread(&alter_employee, sizeof(Employee), 1, p_arq) != 0 && id_employee != alter_employee.id){}//continua lendo até achar ou acabar
								
		do{//verificações do cargo do funcionario		
			clear_buffer();
			printf("DIGITE O CARGO NOVO DO FUNCIONARIO: ");
			fgets(alter_employee.position, MAX_POSITION_NAME, stdin);
			alter_employee.position[strcspn(alter_employee.position, "\n")] = 0;
			if(loop = check_empty_text(alter_employee.position))
				continue;			
			if(loop = check_burst_buffer(alter_employee.position, MAX_POSITION_NAME))
				continue;
			
			if (warning_similar_names_position_employees(alter_employee.position) > 0) {
			    char confirma;
			    printf("\nO cargo '%s' parece com os itens acima.", alter_employee.position);
			    printf("\nDeseja Editar mesmo assim? [S/N]: ");
			    scanf(" %c", &confirma); 
			    clear_buffer(); // Limpa buffer
			
			    if (toupper(confirma) != 'S') {
			        printf("\nEdicao cancelado pelo usuario.\n");
			        fclose(p_arq);
			        return 0;
			    }
			}
			
		}while(loop == 1);
			
		clear_buffer();					
		printf("\nPara confirmar a alteracao digite 'C'\n");
		char validate_employee = getchar();

        if(validate_employee != '\n')
            clear_buffer();
		
    	validate_employee = toupper(validate_employee);
    	
    	if(validate_employee == 'C'){
			
			if(fseek(p_arq, (id_employee - 1) * sizeof(Employee), SEEK_SET) ==  0){
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
		
	}//end function edit_sale_price_employee
	
	int edit_salary_employee(int id_employee){
	
		FILE *p_arq = fopen(ARQ_EMPLOYEES, "rb+");
		Employee alter_employee;
		
		int loop;
		
		if(p_arq == NULL){//file failure open check
			printf("\nNao foi possivel abrir o arquivo. Fechando programa.");
			exit(EXIT_FAILURE);
		}//end if(file failure open check)
		
		while (fread(&alter_employee, sizeof(Employee), 1, p_arq) != 0 && id_employee != alter_employee.id){}//continua lendo até achar ou acabar
		
		do{
			printf("\nDIGITE O NOVO SALARIO DO FUNCIONARIO: ");
			scanf("%f", &alter_employee.salary);
			loop = validate_price(alter_employee.salary);
		}while(loop == 1);
		
		clear_buffer();
		printf("\nPara confirmar a alteracao digite 'C'\n");
		char validate_employee = getchar();

        if(validate_employee != '\n')
            clear_buffer();
		
    	validate_employee = toupper(validate_employee);
    	
    	if(validate_employee == 'C'){
		
			if(fseek(p_arq, (id_employee - 1) * sizeof(Employee), SEEK_SET) ==  0){
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
		
	}//end function edit_purchase_price_employee

	int edit_voucher_employee(int id_employee){
		
		FILE *p_arq = fopen(ARQ_EMPLOYEES, "rb+");
		Employee alter_employee;
		
		if(p_arq == NULL){//file failure open check
			printf("\nNao foi possivel abrir o arquivo. Fechando programa.");
			exit(EXIT_FAILURE);
		}//end if(file failure open check)
		
		while (fread(&alter_employee, sizeof(Employee), 1, p_arq) != 0 && id_employee != alter_employee.id){}//continua lendo até achar ou acabar
		
		printf("\nDIGITE O NOVO VOUCHER DO FUNCIONARIO: ");
		scanf("%f", &alter_employee.voucher);
		if(alter_employee.voucher <= 0)
			alter_employee.voucher = 0;
	
		clear_buffer();
		printf("\nPara confirmar a alteracao digite 'C'\n");
		char validate_employee = getchar();

        if(validate_employee != '\n')
            clear_buffer();
		
    	validate_employee = toupper(validate_employee);
    	
    	if(validate_employee == 'C'){
		
			if(fseek(p_arq, (id_employee - 1) * sizeof(Employee), SEEK_SET) ==  0){
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
	}//end function edit_voucher_employee

int search_employee(){
	
	FILE *p_arq = fopen("employees.dat", "rb");
	Employee employee;
	
	if(p_arq == NULL){//file failure open check
		printf("\nNao foi possivel abrir o arquivo. Fechando programa.");
		exit(EXIT_FAILURE);
	}//end if(file failure open check)
	
	int id;
	int search_option, edit_option, loop;
	
	printf("QUAL FUNCIONARIO DESEJA VISUALIZAR?\n");
	printf("[1] = BUSCAR POR ID\n[2] = BUSCAR PELA LISTA\n[3] = BUSCAR POR NOME\n[4] = RETORNAR AO MENU FUNCIONARIOS\n[5] = RETORNAR AO MENU PRINCIPAL\n\nDIGITE A OPCAO DESEJADA: ");
	
	do{
		scanf("%d", &search_option);
		
		switch(search_option){
			
			case 1:
				id = search_id_generic(ARQ_EMPLOYEES, KEY_EMPLOYEES);
				
				if(id == 0){
					printf("\nFUNCIONARIO NAO ENCONTRADO. RETORNANDO AO MENU FUNCIONARIOS...\n\n");
					fclose(p_arq);
					return 0;
				}//end if(id == 0)
				
				if(fseek(p_arq, (id - 1) * sizeof(Employee), SEEK_SET) ==  0){
					if(fread(&employee, sizeof(Employee), 1, p_arq)){
						printf("ID: %.6d\nNOME: %s\nCARGO: %s\nSALARIO: %.2f\nVOUCHER:%.2f\n", employee.id, employee.name, employee.position, employee.salary, employee.voucher);
						printf("STATUS: %s\n", employee.status == ATIVO ? "ATIVO" : "INATIVO");
						fclose(p_arq);
						
						clear_buffer();
						printf("\nCaso queria editar alguma das informações digite 'E'\n");
						char flag_edit = getchar();
				
				        if(flag_edit != '\n')
				            clear_buffer();
						
				    	flag_edit = toupper(flag_edit);
				    	
				    	if(flag_edit == 'E'){
				    		
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
							
						}//end if 'E'
				        else{
				        	printf("\nRETORNANDO AO MENU...\n\n");
				        	return RETORNAR_SUBMENU;
						}
					}//end if fread
					else{
						printf("\nERRO: Houve um erro na leitura do arquivo. Fechando programa.\n");
						fclose(p_arq);
		        		exit(EXIT_FAILURE);
					}
				}//if fseek
			//end case 1
			case 2: id = search_id_generic_list(KEY_EMPLOYEES);
			
				if(id == 0){
					printf("\nFUNCIONARIO NAO ENCONTRADO. RETORNANDO AO MENU...\n\n");
					fclose(p_arq);
					return 0;
				}//end if(id == 0)
				if(id == RETORNAR_SUBMENU){
					printf("\nRETORNANDO AO MENU FUNCIONARIOS...\n");
					fclose(p_arq);
					return RETORNAR_SUBMENU;
				}//end if(id == 0)
				if(id == RETORNAR_MENU_PRINCIPAL){
					printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
					fclose(p_arq);
					return RETORNAR_MENU_PRINCIPAL;
				}//end if(id == 0)
				
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
							
						}//end if 'E'
				        else{
				        	printf("\nRETORNANDO AO MENU...\n\n");
				        	return RETORNAR_SUBMENU;
						}
					}//end if fread
					else{
						printf("\nERRO: Houve um erro na leitura do arquivo. Fechando programa.\n");
						fclose(p_arq);
		        		exit(EXIT_FAILURE);
					}
				}//if fseek
			//end case 2
			case 3: id = search_name_product();
			
				if(id == 0){
					printf("\nFUNCIONARIO NAO ENCONTRADO. RETORNANDO AO MENU...\n\n");
					fclose(p_arq);
					return 0;
				}//end if(id == 0)
				
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
							
						}//end if 'E'
				        else{
				        	printf("\nRETORNANDO AO MENU...\n\n");
				        	return RETORNAR_SUBMENU;
						}
					}//end if fread
					else{
						printf("\nERRO: Houve um erro na leitura do arquivo. Fechando programa.\n");
						fclose(p_arq);
		        		exit(EXIT_FAILURE);
					}
				}//if fseek
			//end case 3
			case 4:	printf("\nRETORNANDO AO MENU FUNCIONARIOS...\n");
				fclose(p_arq);
				return RETORNAR_SUBMENU;
			case 5: printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
				fclose(p_arq);
				return RETORNAR_MENU_PRINCIPAL;
			default: printf("\nOPCAO INVALIDA ... \nDIGITE UMAS DAS OPCOES: [1] - [2] - [3] - [4] - [5]\n\n");
				break;
		}//end switch search_option
			
	}while(search_option >= 1 && search_option <= 5);
	
}//end fuction search-a-employee

int update_valors(){
	
	FILE *p_arq = fopen("ARQ_EMPLOYEES", "rb+");
	Employee employee_old;
	
	if(p_arq == NULL){//file failure open check
		printf("\nNao foi possivel abrir o arquivo. Fechando programa.");
		exit(EXIT_FAILURE);
	}//end if(file failure open check)
	
	int edit_option, position_id, loop;
	Employee update;
	
	//variaveis auxiliares para alocação dinamica
	long tam_bytes_arq;
	size_t tam_array = 0, i = 0;
	
	fseek(p_arq, 0, SEEK_END);
	
	if(ftell(p_arq) != 0){
		tam_bytes_arq = ftell(p_arq);
		tam_array = (size_t)tam_bytes_arq / sizeof(Employee);
	}
	else{
		printf("\nNenhum funcionario cadastrado.\n");
    	fclose(p_arq);
    	return 0;
	}
	
	Employee *employees_array = malloc(tam_array * sizeof(Employee));
	
	if(employees_array == NULL){
		printf("\nNao foi possivel alocar memoria.Verifique a capacidade maxima de RAM do computador\n");
		printf("\nFechando programa.");
		exit(EXIT_FAILURE);
	}
	
	rewind(p_arq);
	
	tam_array = fread(employees_array, sizeof(Employee), tam_array, p_arq);
	
	do{
		printf("\nQUAL PARAMETRO DESEJA ATUALIZAR?");
		printf("\n\t[1] = SALARIO POR CARGO\n\t[2] = VOUCHER POR CARGO\n\t[3] = NOME DO CARGO \n\t[4] = RETORNAR AO MENU FUNCIONARIOS\n\t[5] = RETORNAR AO MENU PRINCIPAL\n\nDIGITE A OPCAO DESEJADA: ");
		scanf("%d", &edit_option);
		
		switch(edit_option){
			case 1: printf("\nQUAL O CARGO TERA O SALARIO ALTERADO?\n");
				list_salarys_employees();
				printf("Digite o ID que apareceu na lista: ");
				scanf("%d", &position_id);
				
				if(fseek(p_arq, (position_id - 1) * sizeof(Employee), SEEK_SET) ==  0){
					if(fread(&employee_old, sizeof(Employee), 1, p_arq)){
											
						do{
							printf("\nQUAL O NOVO VALOR DO SALARIO PARA O CARGO?\n");
							scanf("%f", &update.salary);
							loop = validate_price(update.salary);
						}while(loop == 1);
						
						for(i = 0; i < tam_array; i++){
							if(strcmp(employees_array[i].position, employee_old.position) == 0){
				                
				                employees_array[i].salary = update.salary;
				                
				                if(fseek(p_arq, i * sizeof(Employee), SEEK_SET) == 0){
				                    
				                    if(fwrite(&employees_array[i], sizeof(Employee), 1, p_arq) != 1){
				                        printf("\n\nHouve um erro na gravacao do item ID [%d].\n", employees_array[i].id);
				                        fclose(p_arq);
                   						free(employees_array);
				                        exit(EXIT_FAILURE);
				                    }
				                }
								else {
				                    printf("\nNao foi possivel posicionar o ponteiro.\n");
				                    fclose(p_arq);
				                    free(employees_array);
				                    exit(EXIT_FAILURE);
				                }
				            }//end if compare strings
						}//end for
						
						printf("\nAlteraçao concluida com exito.\n");
						printf("\nRETORNANDO AO MENU FUNCIONARIOS...\n");
						fclose(p_arq);
						free(employees_array);
						return RETORNAR_SUBMENU;
					}
				}//end fseek read old employee
								
			//end case 1
			case 2: printf("\nQUAL O CARGO TERA O VOUCHER ALTERADO?\n");
				list_salarys_employees();
				printf("Digite o ID que apareceu na lista: ");
				scanf("%d", &position_id);
						
				if(fseek(p_arq, (position_id - 1) * sizeof(Employee), SEEK_SET) ==  0){
					if(fread(&employee_old, sizeof(Employee), 1, p_arq)){
						
						printf("\nQUAL O NOVO VALOR DO VOUCHER PARA O CARGO?\n");
						scanf("%f", &update.voucher);
						if(update.voucher <= 0)
							update.voucher = 0;
						
						for(i = 0; i < tam_array; i++){
							if(strcmp(employees_array[i].position, employee_old.position) == 0){
				                
				                employees_array[i].voucher = update.voucher;
				                
				                if(fseek(p_arq, i * sizeof(Employee), SEEK_SET) == 0){
				                    
				                    if(fwrite(&employees_array[i], sizeof(Employee), 1, p_arq) != 1){
				                        printf("\n\nHouve um erro na gravacao do item ID [%d].\n", employees_array[i].id);
				                        fclose(p_arq);
                   						free(employees_array);
				                        exit(EXIT_FAILURE);
				                    }
				                } else {
				                    printf("\nNao foi possivel posicionar o ponteiro.\n");
				                    fclose(p_arq);
				                    free(employees_array);
				                    exit(EXIT_FAILURE);
				                }
				            }//end if compare strings
						}//end for
						
						printf("\nAlteraçao concluida com exito.\n");
						printf("\nRETORNANDO AO MENU FUNCIONARIOS...\n");
						fclose(p_arq);
						free(employees_array);
						return RETORNAR_SUBMENU;
					}
				}//end fseek read old employee
			//end case 2
			case 3: printf("\nQUAL O CARGO TERA O NOME DO CARGO ALTERADO?\n");
				list_salarys_employees();
				printf("Digite o ID que apareceu na lista: ");
				scanf("%d", &position_id);
				
				if(fseek(p_arq, (position_id - 1) * sizeof(Employee), SEEK_SET) ==  0){
					if(fread(&employee_old, sizeof(Employee), 1, p_arq)){
						
						do{//verificações do cargo do funcionario
							clear_buffer();
							printf("\nQUAL O NOVO NOME DO CARGO?\n");
							fgets(update.position, MAX_POSITION_NAME, stdin);
							update.position[strcspn(update.position, "\n")] = 0;
							if(loop = check_empty_text(update.position))
								continue;			
							if(loop = check_burst_buffer(update.position, MAX_POSITION_NAME))
								continue;
							
							if (warning_similar_names_position_employees(update.position) > 0) {
							    char confirma;
							    printf("\nO cargo '%s' parece com os itens acima.", update.position);
							    printf("\nDeseja Editar mesmo assim? [S/N]: ");
							    scanf(" %c", &confirma); 
							    clear_buffer(); // Limpa buffer
							
							    if (toupper(confirma) != 'S') {
							        printf("\nEdicao cancelado pelo usuario.\n");
							        fclose(p_arq);
				                    free(employees_array);
							        return 0;
							    }
							}
							
						}while(loop == 1);
						
						for(i = 0; i < tam_array; i++){
							if(strcmp(employees_array[i].position, employee_old.position) == 0){
				                
				                strcpy(employees_array[i].position, update.position);
				                
				                if(fseek(p_arq, i * sizeof(Employee), SEEK_SET) == 0){
				                    
				                    if(fwrite(&employees_array[i], sizeof(Employee), 1, p_arq) != 1){
				                        printf("\n\nHouve um erro na gravacao do item ID [%d].\n", employees_array[i].id);
				                        fclose(p_arq);
                   						free(employees_array);
				                        exit(EXIT_FAILURE);
				                    }
				                } else {
				                    printf("\nNao foi possivel posicionar o ponteiro.\n");
				                    fclose(p_arq);
				                    free(employees_array);
				                    exit(EXIT_FAILURE);
				                }
				            }//end if compare strings
						}//end for
						
						printf("\nAlteraçao concluida com exito.\n");
						printf("\nRETORNANDO AO MENU FUNCIONARIOS...\n");
						fclose(p_arq);
						free(employees_array);
						return RETORNAR_SUBMENU;
					}
				}//end fseek read old employee
				
			//end case 3
			case 4:printf("\nRETORNANDO AO MENU FUNCIONARIOS...\n");
				fclose(p_arq);
				free(employees_array);
				return RETORNAR_SUBMENU;
			case 5: printf("\nRETORNANDO AO MENU PRINCIPAL...\n\n");
				fclose(p_arq);
				free(employees_array);
				return RETORNAR_MENU_PRINCIPAL;
		}
	}while(edit_option >= 1 && edit_option <= 5);
	
}//end function update_valor

int search_name_employee(){
	
	FILE *p_arq = fopen("employees.dat", "rb");
    Employee p;
    
    if(p_arq == NULL){
        printf("\nERRO: Nao foi possivel abrir o arquivo. Fechando programa.");
        exit(EXIT_FAILURE);
    }

    char termo_busca[MAX_EMPLOYEE_NAME];    // O que o usuario digitou
    char busca_min[MAX_EMPLOYEE_NAME];      // Versao minuscula do que o usuario digitou
    char nome_employee_min[MAX_EMPLOYEE_NAME]; // Versao minuscula do nome do funcionario no arquivo
    
    int encontrou_algum = 0;
    int id_escolhido = 0;
    int loop;

    // 1. CAPTURA DO TERMO DE BUSCA
    do{
        printf("\n--- BUSCA INTELIGENTE ---\n");
        printf("Digite parte do nome (ex: 'Joao'): ");
        
        // Limpeza de buffer básica se necessario
        // fflush(stdin); 
        
        fgets(termo_busca, MAX_EMPLOYEE_NAME, stdin);
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
    printf("%-5s | %-30s | %-15s | %-10s\n", "ID", "NOME", "CARGO", "SALARIO");
	printf("--------------------------------------------------------------------------\n");

    // Converte o que o usuário digitou para minúsculo
    texto_minusculo(busca_min, termo_busca);

    // 2. O LOOP "GOOGLE" (VARREDURA)
    while(fread(&p, sizeof(Employee), 1, p_arq)){
        
        // Converte o nome do produto atual para minúsculo numa variável temporária
        texto_minusculo(nome_employee_min, p.name);

        // A MÁGICA: strstr verifica se a busca existe DENTRO do nome
       if(strstr(nome_employee_min, busca_min) != NULL){
        // %03d para ID, %-30.30s para nome, %-15s para cargo, %.2f para salário
        printf("%03d   | %-30.30s | %-15s | R$ %.2f\n", p.id, p.name, p.position, p.salary);
        encontrou_algum++;
    	}
    }

    // 3. DECISÃO FINAL
    if(encontrou_algum == 0){
        printf("\nNenhum funcionario encontrado com esse termo.\n");
        fclose(p_arq);
        return 0;
        
    } 
	else {
        printf("----------------------------------------------------\n");
        printf("\nForam encontrados %d funcionarios.\n", encontrou_algum);
        printf("Digite o ID do produto que deseja SELECIONAR (ou 0 para cancelar): ");
        scanf("%d", &id_escolhido);
        
        if(id_escolhido > 0){
        	printf("\nO usuario digitou '0', retornando a ULTIMA funcao\n");
		}
        	return 0;
        
        // Limpa buffer pós-scanf para não travar o menu lá fora
        // fflush(stdin); 
        clear_buffer(); 

        fclose(p_arq);
        return id_escolhido; // Retorna o ID que o usuário escolheu na lista
    }
	
}//end function search_name