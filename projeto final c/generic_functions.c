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

