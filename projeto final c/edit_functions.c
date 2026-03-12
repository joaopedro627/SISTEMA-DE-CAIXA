#include "MODEL_MAIN.H"

int edit_name(const char name_arq, const int key_ship, const long id){

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
			
			while(fread(&alter_product, sizeof(Products), 1, products_p) != 0 && id != alter_product.id){}//continua lendo até achar ou acabar

			do{	
				printf("DIGITE O NOVO NOME DO PRODUTO: ");
				fgets(alter_product.name, MAX_PRODUCT_NAME, stdin);
				alter_product.name[strcspn(alter_product.name, "\n")] = 0;
				if(loop = check_empty_text(alter_product.name))
					continue;
				if(loop = check_burst_buffer(alter_product.name, MAX_PRODUCT_NAME))
					continue;
				if(verify_duplicate_name_product(alter_product.name)){
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
				if(fseek(products_p, (id - 1) * sizeof(Products), SEEK_SET) ==  0){
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
		case KEY_EMPLOYEE: {
			
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
				
				if(warning_duplicate_name_employees(alter_employee.name)){
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
		case KEY_GROUP: {
			
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
				
				if(warning_duplicate_name_employees(alter_group.name)){
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