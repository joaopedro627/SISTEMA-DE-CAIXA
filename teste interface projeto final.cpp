#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_NAME_GROUP 20

void clear_buffer(){
    int caractere;
    while ((caractere = getchar()) != '\n' && caractere != EOF);//Consumes characters until EOF
}//end function clear_buffer

int contar_caracteres(char *frase) {
    // Retorna o tamanho da string
    // Subtraímos 1 se quisermos ignorar o '\n' do fgets
    int tamanho = strlen(frase);

    if (frase[tamanho - 1] == '\n') {
        tamanho--;
    }

    return tamanho;
}

int main(){
	//----- GRUPO 01 -----			----- GRUPO 02 -----
	//   MAX_NAME_GROUP				   MAX_NAME_GROUP
	//--------------------			--------------------

	//variaveis do modelo
	char titulo[] = "TITULO RASCUNHO TEST";
	char up_char_model[] = "-----";
	char dn_char_model[] = "--------------------";
	int option_y = 3, option_x;
	//variaveis da interface
	char name_group[MAX_NAME_GROUP];
	int tam_str, i, j, group_id = 1, num_itens_group = 8;
	char name_product[] = "SORVETE DE FLOCOS COM COBERTURA DE CHOCOLATE";
	int product_id = 5;
	float product_price = 7452.52;
	//source itens do grupo
	int tam_up_char_itens_group = ( (20 * option_y) + ( (option_y - 1) * 8) ) - 16;//20 = max_string, option - 1 = espaçamentos, 8 = \t, 16 = ITENS GRUPO 00
	
	printf("DIGITE O QUANTO DE COLUNAS DESEJA NA SUA INTERFACE: ");
	scanf("%d", &option_y);
	printf("DIGITE O QUANTO DE LINHAS DESEJA NA SUA INTERFACE: ");
	scanf("%d", &option_x);

	printf("\n\nVOCE DIGITOU O MODO %dX%d\nEXEMPLO DO MODO DIGITADO\n\n", option_y, option_x);
	for(i = 0; i < option_x; i++){
		for(j = 0; j < option_y; j++){
			printf("%s GRUPO 00 %s\t", up_char_model, up_char_model);
		}
		printf("\n");
		for(j = 0; j < option_y; j++){
			printf("%s\t", titulo);
		}
		printf("\n");
		for(j = 0; j < option_y; j++){
			printf("%s\t", dn_char_model);
		}
		printf("\n");
	}
	clear_buffer();
	
	printf("\nDIGITE O NOME DO GRUPO QUE DESEJA ADCIONAR: ");
	fgets(name_group, MAX_NAME_GROUP, stdin);
	name_group[strcspn(name_group, "\n")] = 0;

	for(i = 0; i < num_itens_group; i++){
	    int space_encontrado = 0, endereco_space = 0; // Reseta a flag para cada item

	    printf("ID = %.6d | ", product_id); // Padrão de 6 dígitos que você usa no ERP

	    if(contar_caracteres(name_product) > 20){
	        for(j = 0; j < contar_caracteres(name_product); j++){
	            printf("%c", name_product[j]);

	            // Se achar o espaço após o 8º char e ainda não quebrou a linha
	            if(name_product[j] == ' ' && j > 8 && space_encontrado == 0){
	                printf("\n");
	                if(num_itens_group > 1){
	                	endereco_space = j;
	                	printf("ID = %.6d | ", product_id);
					}
	                // COMPENSAÇÃO: Imprime espaços para alinhar com o início do nome na linha de baixo
	                printf("%*s", 13, ""); // 13 espaços (tamanho do "ID = 000000 ")
	                space_encontrado = 1;
	            }
	        }
	    } else {
	        printf(": %-20s ", name_product); // Alinha à esquerda com 20 espaços fixos
	    }

	    // Se houve quebra, o preço sairá na linha 3 do item. Se não, na linha 2.
	    printf("\n%*sR$%10.2f\n", 13, "", product_price);
	}



	return 0;
}

	
