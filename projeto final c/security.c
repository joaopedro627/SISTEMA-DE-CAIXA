#include "MODEL_MAIN.H"

void clear_buffer(){
    int caractere;
    while ((caractere = getchar()) != '\n' && caractere != EOF);//Consumes characters until EOF
}//end function clear_buffer

int check_digit(const char *string){

    for(int i = 0; i < strlen(string); i++){
       
       //'!' inverts logic: If it is NOT a digit, return
        if (!isdigit(string[i])){//isdigit returns true if char is '0' through '9'
            printf("ERRO: Nao pode haver letra ou simbolo. Tente novamente.\n");// Found letter or symbol
			 return 1;//return 1 for true loop 
        }
    }
    return 0;//Contains only digits
}//end function check_digit

int verify_duplicate_name_product(char *new_name){
    FILE *products_p = fopen("products.dat", "rb");
    Products p;
    
    // Se o arquivo não existe, não há duplicatas
    if (products_p == NULL) return 0; 

    char busca_min[MAX_PRODUCT_NAME];
    char nome_arquivo_min[MAX_PRODUCT_NAME];

    // Prepara o nome que o usuário digitou para comparação (tudo minusculo)
    texto_minusculo(busca_min, new_name);

    // Varredura silenciosa
    while (fread(&p, sizeof(Products), 1, products_p)) {
        texto_minusculo(nome_arquivo_min, p.name);

        // strcmp retorna 0 se as strings forem EXATAMENTE iguais
        if (strcmp(nome_arquivo_min, busca_min) == 0) {
            fclose(products_p);
            return 1; // Encontrou um "espelho"!
        }
    }

    fclose(products_p);
    return 0; // Nome está limpo, pode cadastrar
    
}//end function verify_duplicate_name_product

int check_similar_names_product(char *new_name){
    FILE *products_p = fopen("products.dat", "rb");
    Products p;
    if (products_p == NULL) return 0;

    char busca_min[MAX_PRODUCT_NAME];
    char nome_arq_min[MAX_PRODUCT_NAME];
    int parecidos = 0;

    texto_minusculo(busca_min, new_name);

    while (fread(&p, sizeof(Products), 1, products_p)) {
        texto_minusculo(nome_arq_min, p.name);

        // Se "Coca 600" está dentro de "Coca 600ml" OU vice-versa
        if (strstr(nome_arq_min, busca_min) != NULL || strstr(busca_min, nome_arq_min) != NULL) {
            if (parecidos == 0) printf("\n[!] ALERTA: Produtos similares encontrados:\n");
            printf(" -> ID: %ld | Nome: %s\n", p.id, p.name);
            parecidos++;
        }
    }

    fclose(products_p);
    return parecidos;
}//end function check_similar_names

int validate_full_name(const char *string){ 
    int encontrou_letra = 0;//flag ensures that there is useful content
    
    for (int i = 0; string[i] != '\0'; i++) {
        char caractere = (unsigned char)string[i];
        
        if (!isalpha(caractere) && !isspace(caractere)) {//Check if non-alphabetic and not whitespace
            printf("ERRO: O nome nao pode conter numeros ou simbolos (%c).\n", caractere);
            return 1;//Returns 1 (true) to continue execution.
        }
        
        if (isalpha(caractere)) {//check the content
            encontrou_letra = 1;///Found a valid letter
        }
    }//end For
    
    if (encontrou_letra == 0) {//Check for empty string or whitespace
        printf("ERRO: O nome deve conter pelo menos uma letra.\n");
        return 1;//Returns 1 (true) to continue execution.
    }
    
    return 0;
}//end function validate_full_name

int check_empty_text(const char *text){
    //strlen returns the length. If it is 0, the string is empty
    if(strlen(text) == 0){
        printf("ERRO: Este campo nao pode ficar em branco. Tente novamente.\n");
        return 1;//empty = error
    }
    return 0;//String is not empty
}//end function check_void_text

int validate_price(float price){
	if(price <= 0){
		printf("ERRO: O valor tem quer maior que R$0,00. Tente novamente.");
		clear_buffer();
		return 1;//return 1 for true loop
	}
	else
		return 0;//Price is valid
}

int check_burst_buffer(char *string, int size_string){
    int size = strlen(string);//size = size of string
	
	//size - 1 because of '\0' at the end of the string			//ESSE COMENTARIO NAO FOI MODIFICADO
	if(size == size_string - 1 && string[size - 1] != '\n'){//cpf[14] diferente de \n, indica que o usuario ultrapassou o limite da array           !!!!!
        printf("ERRO: Limite de caracteres excedido (%d max). Tente novamente.\n", size_string - 1);
        
        clear_buffer();//Clear input buffer to prevent skipping the next field
        return 1;//return 1 for true loop
    }
    return 0;//Limit not exceeded
}//end function check_burst_buffer

void texto_minusculo(char *destino, const char *origem) {
    int i = 0;
    while (origem[i]) {
        destino[i] = tolower((unsigned char)origem[i]);
        i++;
    }
    destino[i] = '\0'; // Finaliza a string
}

int warning_similar_names_position_employees(char *new_name){
    FILE *p_arq = fopen("emeployees.dat", "rb");
    Employee temp_employee;
    if (p_arq == NULL) return 0;

    char busca_min[MAX_POSITION_NAME];
    char nome_arq_min[MAX_POSITION_NAME];
    int parecidos = 0;

    texto_minusculo(busca_min, new_name);

    while (fread(&temp_employee, sizeof(Employee), 1, p_arq)) {
        texto_minusculo(nome_arq_min, temp_employee.position);

        // Se "Auxiliar" está dentro de "Auxiliar de Limpeza" OU vice-versa
        if (strstr(nome_arq_min, busca_min) != NULL || strstr(busca_min, nome_arq_min) != NULL) {
            if (parecidos == 0) printf("\n[!] ALERTA: Funções similares encontradas:\n");
            printf(" -> ID: %ld | Nome: %s\n", temp_employee.id, temp_employee.position);
            parecidos++;
        }
    }

    fclose(p_arq);
    return parecidos;
}//end function check_similar_names

int warning_duplicate_name_employees(char *new_name){
    FILE *p_arq = fopen("employees.dat", "rb");
    Employee temp_employee;
    
    // Se o arquivo não existe, não há duplicatas
    if (p_arq == NULL) return 0; 

    char busca_min[MAX_EMPLOYEE_NAME];
    char nome_arquivo_min[MAX_EMPLOYEE_NAME];

    // Prepara o nome que o usuário digitou para comparação (tudo minusculo)
    texto_minusculo(busca_min, new_name);

    // Varredura silenciosa
    while (fread(&temp_employee, sizeof(Employee), 1, p_arq)) {
        texto_minusculo(nome_arquivo_min, temp_employee.name);

        // strcmp retorna 0 se as strings forem EXATAMENTE iguais
        if (strcmp(nome_arquivo_min, busca_min) == 0) {
            fclose(p_arq);
            clear_buffer();
            return 1; // Encontrou um "espelho"!
        }
    }

    fclose(p_arq);
    return 0; // Nome está limpo, pode cadastrar
    
}//end function verify_duplicate_name_employee

int verify_duplicate_name_group(char *new_name){
    FILE *groups_p = fopen("groups.dat", "rb");
    Group temp_group;
    
    // Se o arquivo não existe, não há duplicatas
    if (groups_p == NULL) return 0; 

    char busca_min[MAX_GROUP_NAME];
    char nome_arquivo_min[MAX_GROUP_NAME];

    // Prepara o nome que o usuário digitou para comparação (tudo minusculo)
    texto_minusculo(busca_min, new_name);

    // Varredura silenciosa
    while (fread(&temp_group, sizeof(Group), 1, groups_p)) {
        texto_minusculo(nome_arquivo_min, temp_group.name);

        // strcmp retorna 0 se as strings forem EXATAMENTE iguais
        if (strcmp(nome_arquivo_min, busca_min) == 0) {
            fclose(groups_p);
            return 1; // Encontrou um "espelho"!
        }
    }

    fclose(groups_p);
    return 0; // Nome está limpo, pode cadastrar
    
}//end function verify_duplicate_name_product