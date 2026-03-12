#ifndef MODEL_MAIN_H
#define MODEL_MAIN_H

//libraries
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//owner settings
#define FILTRO_BEM_SUCEDIDO 1
#define NAO_ENCONTRADA -1
#define RETORNAR_MENU_PRINCIPAL -5
#define RETORNAR_SUBMENU -4
#define RETORNAR_FUNCAO -1
#define SAIR_PROGRAMA -404
#define ATIVO 1
#define INATIVO -1

int options_menu();

#define ARQ_PRODUCTS "products.dat"
#define MAX_PRODUCT_NAME 40
#define KEY_PRODUCTS 1

typedef struct{
	long id;
	char name[MAX_PRODUCT_NAME];
	float purchase_price;
	float sale_price;
	int stock;
	int group;
	int status;
} Products;

#define ARQ_EMPLOYEES "employees.dat"
#define MAX_EMPLOYEE_NAME 40
#define MAX_POSITION_NAME 30
#define KEY_EMPLOYEES 2

typedef struct {
    int id;
    float voucher;
    float salary;
    char name[MAX_EMPLOYEE_NAME];
    char position[MAX_POSITION_NAME];
    int status;
} Employee;

#define ARQ_GROUPS "groups.dat"
#define MAX_ITENS_GROUP 30
#define MAX_GROUP_NAME 20
#define KEY_GROUPS 3

typedef struct {
    int id;
    char name [MAX_GROUP_NAME];
    long id_products[MAX_ITENS_GROUP];
    float sales_products[MAX_ITENS_GROUP];
    int quant_products;
    int status;
} Group;

//prototype generic_functions
int	walk_pags(int *contador, long *pag, long max_pags);
long get_next_id(const char name_arq[], const int key_ship);
long search_id_generic(const char name_arq[], const int part_ship);
long search_id_generic_list(const int key_ship);

//prototype edit_functions
int edit_name(const char name_arq[], const int key_ship, const long id);
int edit_status(const char name_arq[], const int key_ship, const long id);

//prototype products
int options_product();
	int list_products();
	//prototype functions of list_products
		int filters(Products array[], size_t tam_array);	
			int status_filter(Products array[], size_t tam_array);
			int price_filter(Products array[], size_t tam_array, long max_pags);
				int comparar_sale_price_dec(const void *p1, const void *p2);
				int comparar_sale_price_cre(const void *p1, const void *p2);
			int alphabetical_filter(Products array[], size_t tam_array, long max_pags);
				int comparar_nomes(const void *n1, const void *n2);					
	void new_product();
	int desativate_product();
	int edit_product();
	//prototype functions of edit_product
		int edit_sale_price_product(long id_product);
		int edit_purchase_price_product(long id_product);
		int edit_stock_product(long id_product);
	int search_product();
	int update_valors();
	//prototype functions of search
		long search_name_product();
	
//prototype employees
int options_employees();
	int list_employees();
	//prototype functions of list_employees
		int filters_employees(Employee array[], size_t tam_array);
			//utiliza walk_pags do product
			int status_filter_employees(Employee array[], size_t tam_array);
			int alphabetical_filter_employees(Employee array[], size_t tam_array, long max_pags);
				int comparar_nomes_employees(const void *n1, const void *n2);
	void new_employee();
		void list_salarys_employees();
	int desativate_employee();
	int edit_employee();
	//prototype functions of edit_employee
		int edit_position_employee(int id_employee);
		int edit_salary_employee(int id_employee);
		int edit_voucher_employee(int id_employee);
	int search_employee();
	//prototype functions of search	
	int search_name_employee();
	
//prototype groups
/*
int options_groups_products();
	int list_groups();
		void itens_group(int id);
		int filters_groups(Group array[], size_t tam_array);
		int status_filter_groups(Group array[], size_t tam_array);
	void new_group();
	int edit_interface_groups();
	int edit_group();
	int search_group();*/
		
//prototype security
void clear_buffer();
int check_digit(const char *string);
int check_empty_text(const char *text);
int check_burst_buffer(char *string, int size_string);
int validate_full_name(const char *string);
int validate_price(float price);
void texto_minusculo(char *destino, const char *origem);
int check_similar_names_product(char *new_name);
int verify_duplicate_name_product(char *new_name);
int warning_similar_names_position_employees(char *new_name);
int warning_duplicate_name_employees(char *new_name);
int verify_duplicate_name_group(char *new_name);

#endif