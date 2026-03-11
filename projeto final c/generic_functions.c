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
	
	if(p_arq){
		printf("\nNao foi possivel abrir o arquivo. Fechando programa.");
		exit(EXIT_FAILURE);
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
		case KEY_PRODUCT: {
			
				Products alter_product;
				
				while (fread(&alter_product, sizeof(Products), 1, products_p) != 0 && id != alter_product.id){}//continua lendo até achar ou acabar
				
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
		case KEY_GROUP: {
			
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