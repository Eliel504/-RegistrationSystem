#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#define CAD_FUN 10
#define IDADE_MIN 16
#define CAD_PASC 10
#define CAD_MED 10
#define SENHA_MIN 5
#define SENHA_MAX 12
#define CRM_MAX 10
#define CRM_MIN 4
#define MAX_AGEN 10

/*FUNÇÕES*/
char le_val_menu_bv();
char le_val_cad_func();
char le_val_op_continuar_cad();
int le_val_dia(int c);
int le_val_mes(int c);
int le_val_ano(int c, int ano_at);
char le_val_dados_corretos();
char le_val_op_continuar_login();
char le_valida_op_menu_principal();
char le_val_op_cadastro();
char le_valida_sexo(int c);
char le_val_op_sair();
int le_valida_dias_trab(int c);
char le_val_select_unidade();
char le_valida_continuar_agend();
char le_valida_op_excluir();
char le_valida_continuar_cancelamento_agend();
char le_valida_op_relatorio();
char le_valida_relatorio_cad();
char le_valida_op_relatorio_cad_fun();
char le_valida_continuar_filtragem();
char le_valida_op_relatorio_cad_agend();
char le_valida_op_faturamento();
/*PROCEDIMENTOS*/
void bem_vindo();
void menu_bem_vindo();
void faixada();
void erro();
void dados_invalidos();
void cadastro_func();
void guara();
void contagem_fun_guara(int c);
void tagua();
void contagem_pas(int c);
void ac();
void contagem_med(int c);
void ja_possui_cad();
void cad_limite();
void cpf_invalido();
void idade_invalida(); 
void cpf_valido();
void login();
void login_encontrado();
void login_erro();
void senha_erro();
void senha_existente();
void sem_usuarios();
void cad_limite_pas();
void program_encerrado();
void senha_menor(int c);
void senha_maior(int c);
void cad_limite_med();
void crm_menor(int c);
void crm_maior(int c);
void crm_existente();
void agendamento();
void paciente_encontrado();
void sem_pasciente();
void dia_indisponivel();
void dia_invalido();
void cpf_nao_encontrado();
void possui_agendamento();
void horario_indisponivel();
void agend_realizado();
void sem_agendamento();
void cancelamento();
void paciente_nao_possui_agendamento();
void relatorios();
void relatorio_cadastro();
void funcionario_cadastro();
void funcionario_nao_encontrado();
void paciente_nao_encontrado();
void paciente_cadastro();
void sistema_sem_paciente();
void sistema_sem_medico();
void medico_cadastro();
void medico_nao_encontrado();
void relatorio_agendamento();
void agendamento_guara();
void agendamento_tagua();
void agendamento_ac();
void agendamento_nao_encontrado();
void faturamento();
void sem_faturamento();
/*FUNÇÃO PRINCIPAL*/
int main(){
	setlocale(LC_ALL, "Portuguese");
	
	SYSTEMTIME str_t;
	GetSystemTime(&str_t);	

/*STRUCTS*/
struct str_cad_fun{ /*formulário cadastro de funcionários*/
	char cpf[15] ;
	char nome_fun[50];
	char sexo;
	int dia;
	int mes;
	int ano;
	int idade;
	char cargo[20];
	char senha[10];
	char hora[15];
	char data[15];
};struct str_cad_fun cad_fun[CAD_FUN] = {' '};  

struct str_cad_pas{ /*formulário cadastro de paciente*/
	char cpf[15];
	char nome[50];
	char sexo;
	int dia;
	int mes;
	int ano;
	int idade;
	char telefone[15];
	char hora[15];
	char data[15];
	int unidade;
	int id_agend;
	bool agendamento;
}; struct str_cad_pas cad_pas[CAD_PASC] = {' '};

struct str_cad_med{  /*formulário cadastro do médico*/
	char cpf[15];
	char nome[50];
	char sexo;
	char crm [10]; 	
	int dia;
	int mes;
	int ano;
	int idade;
	int dia_trab;
	char hora[15];
	char data[15];			
};struct str_cad_med cad_med[CAD_MED]= {' '};

/*CONTROLE DE DIAS UNIDADE GUARÁ-----------------------------------------*/
struct strhorarios_guara{
  char hr[9];
};

struct strmes_guara{
  struct strhorarios_guara horarios_guara[11];
};struct strmes_guara dias_guara[30];

/*CONTROLE DE DIAS UNIDADE TAGUATINGA ------------------------------------*/

struct strhorarios_tagua{
  char hr[9];
};

struct strmes_tagua{
  struct strhorarios_tagua horarios_tagua[11];
};struct strmes_tagua dias_tagua[30];

/*CONTROLE DE DIAS ÁGUAS CLARAS ------------------------------------*/
struct strhorarios_ac{
  char hr[9];
};

struct strmes_ac{
  struct strhorarios_ac horarios_ac[11];
};struct strmes_ac dias_ac[30];


struct str_cad_agend_guara{ /*Formulário de agendamento da unidade GUARÁ*/
	char cpf[15];
	char nome[50];
	int idade;
	int sexo;
	int dia_ag;
	int mes_ag;
	int ano_ag;
	char hora_agend[15];
	int pos_hora_agend;
	char telefone[15];
	char hora[15];
	char data[15];
};struct str_cad_agend_guara cad_agend_guara[MAX_AGEN] = {' '};

struct str_cad_agend_tagua{ /*Formulario de agendamento da unidade Taguatinga*/
	char cpf[15];
	char nome[50];
	int idade;
	int sexo;
	int dia_ag;
	int mes_ag;
	int ano_ag;
	char hora_agend[15];
	int pos_hora_agend;
  char telefone[15];
	char hora[15];
	char data[15];
};struct str_cad_agend_tagua cad_agend_tagua[MAX_AGEN] = {' '};

struct str_cad_agend_ac{ /*Formulário de agendamento da unidade Águas claras*/
	char cpf[15];
	char nome[50];
	int idade;
	int sexo;
	int dia_ag;
	int mes_ag;
	int ano_ag;
	char hora_agend[15];
	int pos_hora_agend;
  	char telefone[15];
	char hora[15];
	char data[15];
};struct str_cad_agend_ac cad_agend_ac[MAX_AGEN] = {' '};
/*VARIÁVEIS

COMEÇANDO COM:
op -> variável de opção
c -> variável de contagem
tam -> variável de tamanho*/  
	int soma_cpf = 0, numero_cpf = 0, resultado_cpf = 0, c_func = 0, c = 0, j = 0, c_pas = 0, c_med = 0, c_agend_guara = 0, c_agend_tagua = 0, c_agend_ac = 0,
	tot_agend = 0, tam_cpf = 0, tam = 0, tam_nasc = 0, tam_nome = 0, tam_crm = 0, tam_cargo = 0, tam_senha = 0, fun_senha = 0, dimensao_nome = 0, 
	primeiro_espaco = 0, cpf_pas_encotrado = 0,  dia_atual = str_t.wDay, mes_atual = str_t.wMonth, ano_atual = str_t.wYear, dia_agendamento = 0, 
	qtd_mulher_fun = 0, qtd_homem_fun = 0, qtd_mulher_pas = 0, qtd_homem_pas = 0, qtd_homem_med = 0, qtd_mulher_med = 0, total_agend = 0, num_agend_mais = 0 , 
	ag_dia_guara = 0, ag_dia_tagua = 0, ag_dia_ac = 0;
	
	float fat_dia_guara = 0, fat_mes_guara = 0, fat_dia_tagua = 0, fat_mes_tagua = 0, fat_dia_ac = 0, fat_mes_ac = 0, fat_total = 0, fat_total_d, por_cento_guara = 0, 
	por_cento_ac = 0, por_cento_tagua = 0;
	
	char log[15] = {0}, senha_log[15] = {0}, primeiro_nome_fun[20] = {' '}, primeiro_nome_med[20] = {' '}, primeiro_nome_pas[20] = {' '}, crm[15] = {0}, digito10, digito11, 
	data[20], hora[20], horario_agendamento[7] = {0}, cpf_fun[11] = {0}, cpf_pas[11] = {0}, cpf_med[11] = {0}, cpf_ag[11] = {0}, unidade_mais_atende[20] = {0},
	op_cad = ' ', op_continuar = ' ', op_excluir = ' ', op_dados= ' ',op_benvindo = ' ', op = ' ', op_pasc = ' ', op_sair = ' '; /*variáveis para comparação*/
	
	bool valid, cpf_encontrado, valid_cpf, valid_horario;
	time_t agora;
	
	for(c = 0; c <= 30; c++){ /*COLETANDO OS HORÁRIOS DA UNIDADE GUARA*/
	    strcpy(dias_guara[c].horarios_guara[0].hr, "09:00");
	    strcpy(dias_guara[c].horarios_guara[1].hr, "10:00");
	    strcpy(dias_guara[c].horarios_guara[2].hr, "11:00");   
	    strcpy(dias_guara[c].horarios_guara[3].hr, "12:00");
	    strcpy(dias_guara[c].horarios_guara[4].hr, "13:00"); 
	    strcpy(dias_guara[c].horarios_guara[5].hr, "14:00");
	    strcpy(dias_guara[c].horarios_guara[6].hr, "15:00");
	    strcpy(dias_guara[c].horarios_guara[7].hr, "16:00");
	    strcpy(dias_guara[c].horarios_guara[8].hr, "17:00");
	    strcpy(dias_guara[c].horarios_guara[9].hr, "18:00");
	}

	for(c = 0; c <= 30; c++){ /*COLETANDO OS HORÁRIOS DA UNIDADE TAGUATINGA*/
	    strcpy(dias_tagua[c].horarios_tagua[0].hr, "09:00");
	    strcpy(dias_tagua[c].horarios_tagua[1].hr, "10:00");
	    strcpy(dias_tagua[c].horarios_tagua[2].hr, "11:00");   
	    strcpy(dias_tagua[c].horarios_tagua[3].hr, "12:00");
	    strcpy(dias_tagua[c].horarios_tagua[4].hr, "13:00");
	    strcpy(dias_tagua[c].horarios_tagua[5].hr, "14:00");
	    strcpy(dias_tagua[c].horarios_tagua[6].hr, "15:00");
	    strcpy(dias_tagua[c].horarios_tagua[7].hr, "16:00");
	    strcpy(dias_tagua[c].horarios_tagua[8].hr, "17:00");
	    strcpy(dias_tagua[c].horarios_tagua[9].hr, "18:00");
	}

	for(c = 0; c <= 30; c++){ /*COLETANDO OS HORÁRIOS DA UNIDADE AGUAS CLARAS*/
	    strcpy(dias_ac[c].horarios_ac[0].hr, "09:00");
	    strcpy(dias_ac[c].horarios_ac[1].hr, "10:00");
	    strcpy(dias_ac[c].horarios_ac[2].hr, "11:00");   
	    strcpy(dias_ac[c].horarios_ac[3].hr, "12:00");
	    strcpy(dias_ac[c].horarios_ac[4].hr, "13:00");
	    strcpy(dias_ac[c].horarios_ac[5].hr, "14:00");
	    strcpy(dias_ac[c].horarios_ac[6].hr, "15:00");
	    strcpy(dias_ac[c].horarios_ac[7].hr, "16:00");
	    strcpy(dias_ac[c].horarios_ac[8].hr, "17:00");
	    strcpy(dias_ac[c].horarios_ac[9].hr, "18:00");
	}
		
bem_vindo();/*TELA DE BEM VINDO*/

do{
	do{
		system("cls");		
		menu_bem_vindo();
		op_benvindo = le_val_menu_bv();
		switch(op_benvindo){
			case '1': /*MENU INICIAL*/
				do{
					system("cls");
					cadastro_func();
					op_cad = le_val_cad_func();
					switch(op_cad){
						case '1': /*AQUI COMEÇA A OPÇÃO DE CADASTRAR FINCIONÁRIO*/
							if(c_func == CAD_FUN){/*verificando se o número de cadastros de funcionários diponiveis chegou ao limite*/
								system("cls");
								cad_limite();		
							}else{
								op_continuar = '1';
								while(op_continuar == '1' && c_func < CAD_FUN){
									do{									
										system("cls");	/*AQUI VAI LER O CPF DO FUNCIONÁRIO, que servirá como identificador*/
										faixada();
										contagem_fun_guara(c_func); 											
										strcpy(cad_fun[c_func].cpf," "); /*formatando a variável*/
										printf("CPF:  "); 																				
										scanf("%s", cpf_fun); 																										
										fflush(stdin);
										tam_cpf = strlen(cpf_fun);
										soma_cpf = 0;										
										
										for(c = 0; c < 9; c++){ /*AQUI VAI COMEÇAR A VALIDAÇÃO*/
											numero_cpf = cpf_fun[c] - 48; /*analizando o digito 10*/
											soma_cpf = soma_cpf + (numero_cpf * (10-c));
										}										
										resultado_cpf = 11 - (soma_cpf%11);										
											if(resultado_cpf == 10 || resultado_cpf == 11){/*verificando se o digito 10 é igual a 11 ou 10*/
												digito10 = '0';
											}else{
												digito10 = resultado_cpf + 48;
											}										
										soma_cpf = 0;
										
										for(c = 0; c < 10; c++){ /*analizando o digito 11*/
											numero_cpf = cpf_fun[c] - 48;
											soma_cpf = soma_cpf +(numero_cpf * (11-c));
										}
										
										resultado_cpf = 11 - (soma_cpf%11);
										
											if(resultado_cpf == 10 || resultado_cpf == 11){ /*verificando se o digito 11 é igual a 11 ou 10*/
												digito11 = '0';										
											}else{
												digito11 = resultado_cpf + 48;
											}																					
											if(cpf_fun[9] != digito10 || cpf_fun[10] != digito11 || tam_cpf != 11){ /*se qual quer um dos dois forem diferentes*/
												do{
													system("cls");
													cpf_invalido();
													printf("DIGITE NOVAMENTE (ex: 12345678901): ");
													fflush(stdin);
													gets(cpf_fun);			
													tam_cpf = strlen(cpf_fun);
													soma_cpf = 0;																								
													for(c = 0; c < 9; c++){
														numero_cpf = cpf_fun[c] - 48;
														soma_cpf = soma_cpf + (numero_cpf * (10-c));
													}
													
													resultado_cpf = 11 - (soma_cpf%11);													
														if(resultado_cpf == 10 || resultado_cpf == 11){
															digito10 = '0';
														}else{
															digito10 = resultado_cpf + 48;
														}													
													soma_cpf = 0;
													
													for(c = 0; c < 10; c++){
														numero_cpf = cpf_fun[c] - 48;
														soma_cpf = soma_cpf +(numero_cpf * (11-c));
													}													
													resultado_cpf = 11 - (soma_cpf%11);													
														if(resultado_cpf == 10 || resultado_cpf == 11){
															digito11 = '0';													
														}else{
															digito11 = resultado_cpf + 48;
														}
												}while(cpf_fun[9] != digito10 || cpf_fun[10] != digito11 || tam_cpf != 11);	
											}																																	
										/*soma_cpf = 0, numero_cpf = 0, resultado_cpf = 0*/										
											for(c = 0; c <= c_func; c++){ /*verificando se ja existe o cpf*/																																																																																																														
												if(strcmp(cpf_fun, cad_fun[c].cpf) == 0){
													do{	
														system("cls");
														ja_possui_cad();
														printf("INFORME OUTRO CPF (ex: 00000000000): ");
														scanf("%s", cpf_fun);
														fflush(stdin);
														tam_cpf = strlen(cpf_fun);
														soma_cpf = 0;																								
														for(c = 0; c < 9; c++){
															numero_cpf = cpf_fun[c] - 48;
															soma_cpf = soma_cpf + (numero_cpf * (10-c));
														}
														
														resultado_cpf = 11 - (soma_cpf%11);													
															if(resultado_cpf == 10 || resultado_cpf == 11){
																digito10 = '0';
															}else{
																digito10 = resultado_cpf + 48;
															}													
														soma_cpf = 0;
														
														for(c = 0; c < 10; c++){
															numero_cpf = cpf_fun[c] - 48;
															soma_cpf = soma_cpf +(numero_cpf * (11-c));
														}													
														resultado_cpf = 11 - (soma_cpf%11);													
															if(resultado_cpf == 10 || resultado_cpf == 11){
																digito11 = '0';													
															}else{
																digito11 = resultado_cpf + 48;
															}																																																									
													}while(strcmp(cpf_fun, cad_fun[c].cpf) == 0);															
														while(cpf_fun[9] != digito10 || cpf_fun[10] != digito11 || tam_cpf != 11){
															system("cls");
															cpf_invalido();
															printf("DIGITE NOVAMENTE (ex: 12345678901): ");															
															scanf("%[^\n]s", cpf_fun);			
															fflush(stdin);
															tam_cpf = strlen(cpf_fun);
															
															soma_cpf = 0;																								
															for(c = 0; c < 9; c++){
																numero_cpf = cpf_fun[c] - 48;
																soma_cpf = soma_cpf + (numero_cpf * (10-c));
															}
															
															resultado_cpf = 11 - (soma_cpf%11);													
																if(resultado_cpf == 10 || resultado_cpf == 11){
																	digito10 = '0';
																}else{
																	digito10 = resultado_cpf + 48;
																}													
															soma_cpf = 0;
															
															for(c = 0; c < 10; c++){
																numero_cpf = cpf_fun[c] - 48;
																soma_cpf = soma_cpf +(numero_cpf * (11-c));
															}													
															resultado_cpf = 11 - (soma_cpf%11);													
																if(resultado_cpf == 10 || resultado_cpf == 11){
																	digito11 = '0';													
																}else{
																	digito11 = resultado_cpf + 48;
																}
														}	
														c = 0;
													}																																	
												}																																																																							
										strcpy(cad_fun[c_func].cpf, cpf_fun);
										
										system("cls"); /*AQUI VAI LER O NOME DO FUNCIONÁRIO*/
										cpf_valido();
										contagem_fun_guara(c_func);
										printf("NOME: ");			
										scanf("%[^\n]s", cad_fun[c_func].nome_fun);
										fflush(stdin);
										tam_nome = strlen(cad_fun[c_func].nome_fun);
										for(c = 0 ;c <= tam_nome;c++){
											cad_fun[c_func].nome_fun[c] = toupper(cad_fun[c_func].nome_fun[c]); /*PASSANDO O NOME PARA MAIÚSCULO*/
										}
										
										system("cls");	/*AQUI VAI LER O SEXO DO FUNCIONÁRIO*/
										faixada();
										contagem_fun_guara(c_func);	
										cad_fun[c_func].sexo = le_valida_sexo(c_func);
										
										system("cls");	/*AQUI VAI LER A DATA DE NASCIMENTO DO FUNCIONÁRIO*/
										faixada();
										contagem_fun_guara(c_func); 
										printf("\n");
										printf("DATA DE NASCIMENTO: \n\n");
										cad_fun[c_func].dia = le_val_dia(c_func); /*dia*/
										cad_fun[c_func].mes = le_val_mes(c_func); /*mês*/
										cad_fun[c_func].ano = le_val_ano(c_func, ano_atual); /*ano*/
										cad_fun[c_func].idade = ano_atual - cad_fun[c_func].ano; /*COLETANDO A IDADE*/
										
										system("cls");	/*AQUI VAI LER O CARGO DO FUNCIONÁRIO*/
										faixada();
										contagem_fun_guara(c_func); 									
										printf("CARGO: "); 										
										scanf("%s", cad_fun[c_func].cargo);
										fflush(stdin);
										
										tam_cargo = strlen(cad_fun[c_func].cargo);	
										for(c = 0; c <= tam_cargo; c++){
											cad_fun[c_func].cargo[c] = toupper(cad_fun[c_func].cargo[c]); /*PASSANDO PARA MAIÚSCULO*/
										}												
																				
										system("cls");	/*AQUI VAI LER A SENHA, que servirá, além do CPF, como identificador*/
										faixada();
										contagem_fun_guara(c_func); 
										strcpy(cad_fun[c_func].senha," " );
										printf("SENHA: ");
										scanf("%[^\n]s", senha_log);
										fflush(stdin);
										tam_senha = strlen(senha_log);																																
											if(strcmp(senha_log, "00000000000") == 0){ /*validando a senha*/
												do{
													system("cls");
													senha_erro();
													contagem_fun_guara(c_func);
													printf("DIGITE NOVAMENTE: ");
													scanf("%s", senha_log);
													fflush(stdin);
													tam_senha = strlen(senha_log);		
												}while(strcmp(senha_log, "00000000000") == 0);	
											}																																																			
										for(c = 0; c < c_func;c++){																	 /*Verificando se a senha ja existe*/													
												while(strcmp(senha_log, cad_fun[c].senha) == 0  || tam_senha < SENHA_MIN || tam_senha > SENHA_MAX){												
													if(strcmp(senha_log, cad_fun[c].senha) == 0){
														do{
															system("cls");
															senha_existente();
															printf("INFORME OUTRA SENHA: ");															
															scanf("%[^\n]s", senha_log);
															fflush(stdin);
															tam_senha = strlen(senha_log);	
														}while(strcmp(senha_log, cad_fun[c].senha) == 0);	
													}
													if(tam_senha < SENHA_MIN || tam_senha > SENHA_MAX){ /*validando a quantidade de caracteres da senha*/
														do{
															if(tam_senha < SENHA_MIN){ /*se for menor que 6 caractere*/
																do{
																	system("cls");
																	senha_menor(SENHA_MIN);
																	contagem_fun_guara(c_func);
																	printf("DIGITE NOVAMENTE: ");
																	scanf("%[^\n]s", senha_log);
																	fflush(stdin);
																	tam_senha = strlen(senha_log);
																}while(tam_senha < SENHA_MIN);
															}
															if (tam_senha > SENHA_MAX){ /*se for maior que 10 caracteres*/
																do{
																	system("cls");
																	senha_maior(SENHA_MAX);
																	contagem_fun_guara(c_func);
																	printf("DIGITE NOVAMENTE: ");
																	scanf("%[^\n]s", senha_log);
																	fflush(stdin);
																	tam_senha = strlen(senha_log);		
																}while(tam_senha > SENHA_MAX);	
															}																																				
														}while(tam_senha < SENHA_MIN || tam_senha > SENHA_MAX);																																	
													}	
												}
											}																						
										strcpy(cad_fun[c_func].senha, senha_log);
										
										system("cls");	/*AQUI VAI APRESENTAR OS DADOS DIGITADOS PELO FUNCIONÁRIO*/
										faixada();
										agora = time(NULL);
										
										strftime(cad_fun[c_func].data, sizeof(cad_fun[c_func].data), "%d/%m/%y", localtime(&agora));
										strftime( cad_fun[c_func].hora, sizeof(cad_fun[c_func].hora), "%H:%M:%S", localtime(&agora));
																				
										printf("CPF: ...................%s\n", cad_fun[c_func].cpf);
										printf("NOME: ..................%s\n", cad_fun[c_func].nome_fun);
											if(cad_fun[c_func].sexo == '1'){
												printf("SEXO: ..................MASCULINO\n");
											}else{
												printf("SEXO: ..................FEMININO\n");
											}																			
										printf("DATA DE NASCIMENTO......%d/%d/%d\n", cad_fun[c_func].dia, cad_fun[c_func].mes, cad_fun[c_func].ano);
										printf("IDADE...................%d ANOS\n", cad_fun[c_func].idade);
										printf("CARGO:..................%s\n", cad_fun[c_func].cargo);
										printf("SENHA:..................%s\n", cad_fun[c_func].senha);
										printf("________________________________________________________________________________\n");										
										printf("                      DATA: %s          HORA: %s\n",cad_fun[c_func].data, cad_fun[c_func].hora);
										printf("________________________________________________________________________________\n\n");
										op_dados = le_val_dados_corretos(); /*vai perguntar se os dados então corretos*/
									}while(op_dados != '1');
									
									dimensao_nome = strlen(cad_fun[c_func].nome_fun);
									
									for(c = dimensao_nome - 1; c >= 0; c-- ){ /*AQUI VAI PASSAR O PRIMEIRO NOME DO FUNCIONÁRIO PARA MAIÚSCULO*/
										if(cad_fun[c_func].nome_fun[c] == ' '){/*encontarndo o primeiro espaço*/
											primeiro_espaco = c;
										}
									}
									for(c = 0; c <= primeiro_espaco; c++){
										primeiro_nome_fun[c] = toupper(cad_fun[c_func].nome_fun[c]);/*transferindo o primeiro nome pra outra variável*/
									}
										if(cad_fun[c_func].sexo == '1'){ /*SE OS DADOS ESTIVEREM CORRETOS, AQUI VAI MOSTRAR QUE O FUNCIONÁRIO FOI CADASTRADO*/
											printf("\n\n"); /*se for homem*/
											printf("-------------------------------------------------------------------------------\n");
											printf("             O Funcionário, %s, foi cadastrado com Sucesso!!\n", primeiro_nome_fun);
											printf("-------------------------------------------------------------------------------\n\n");
											qtd_homem_fun += 1; /*coletando a qtd de homens*/
										}else{
											printf("\n\n"); /*se for mulher*/
											printf("-------------------------------------------------------------------------------\n");
											printf("             A funcionária, %s, foi cadastrada com Sucesso!!\n", primeiro_nome_fun);
											printf("-------------------------------------------------------------------------------\n\n");
											qtd_mulher_fun += 1; /*coletando a qtd de mulheres*/
										}
										c_func += 1;	
										
										if(c_func == CAD_FUN){ /*AQUI VAI VERIFICAR SE O LIMITE DE CADASTROS FORAM ATINGIDOS*/
											op_continuar = '2';
											printf("                      LIMITE DE CADASTROS ATINGIDOS\n");
											printf("________________________________________________________________________________\n\n");
											system("PAUSE");
										}else{ /*SE NÃO FOREM, AQUI VAI PERGUNTAR SE ELE DESEJA CONTINUAR CADASTRANDO*/
											op_continuar = le_val_op_continuar_cad();
										}	
								}
							}
						break;
					}
				}while(op_cad != '2'); /*AQUI TERMINA A OPÇÃO DE CADASTRO DE FUNCIONÁRIO*/	
			break;
			case '2': /*AQUI COMEÇA A OPÇÃO DE LOGIN*/
				if(c_func == 0){
					system("cls"); /*AQUI VAI VERIFICAR SE NO SISTEMA EXISTE FUNCIONÁRIOS CADASTRADOS*/
					sem_usuarios();
				}else{
					system("cls"); /*AQUI VAI LER O USUÁRIO*/
					login();
					printf("USUÁRIO: ");
					fflush(stdin);
					gets(log);
					while(strcmp(log, "clinica123") != 0){ /*validando o usuário*/
						system("cls");
						login_erro();
						printf("DIGITE NOVAMENTE: ");
						fflush(stdin);
						gets(log);
					}
					system("cls"); /*AQUI VAI LER A SENHA*/
					login_encontrado();
					printf("SENHA: ");
					fflush(stdin);
					gets(senha_log);					
					for (c = 0; c <= c_func; c++){ /*verificando se a senha estar cadastrada no sistema*/
						if(strcmp(senha_log, cad_fun[c].senha) == 0){
							valid = true; 
							fun_senha = c; /*coletando o indice do formulário do funcionário que teve a senha validada*/
						}
					}
						if(valid != true){
							do{
								system("cls");
								senha_erro();
								printf("DIGITE NOVAMENTE: ");
								fflush(stdin);
								gets(senha_log);
								for (c = 0; c <= c_func; c++){
									if(strcmp(senha_log, cad_fun[c].senha) == 0){
										valid = true;
										fun_senha = c;
									}		
								}	
							}while(valid != true);	
						}
					dimensao_nome = strlen(cad_fun[fun_senha].nome_fun);									
					
					for(c = dimensao_nome - 1; c >= 0; c-- ){ /*PASSANDO O PRIMEIRO NOME DO FUNCIONÁRIO QUE FEZ O LOGIN PARA MAÍUSCULO*/
						if(cad_fun[fun_senha].nome_fun[c] == ' '){
						primeiro_espaco = c;
						}
					}
					for(c = 0; c <= primeiro_espaco; c++){
						primeiro_nome_fun[c] = toupper(cad_fun[fun_senha].nome_fun[c]);
					}	
					do{ /*AQUI COMEÇA O MENU PRINCIPAL*/						
						system("cls");
						faixada();
							if(cad_fun[fun_senha].sexo == '1'){
								printf("                            SEJA BEM VINDO, %s! \n", primeiro_nome_fun); 
								printf("________________________________________________________________________________\n\n");	
							}else{
								printf("                            SEJA BEM VINDA, %s! \n", primeiro_nome_fun); 
								printf("________________________________________________________________________________\n\n");	
							}
						op = le_valida_op_menu_principal();	
						switch(op){
							case '1':/* AQUI COMEÇA A OPÇÃO DE CADASTRO*/
								do{
									system("cls");
									cadastro_func();
									op_pasc = le_val_op_cadastro();											
									switch(op_pasc){
										case '1': /*AQUI COMEÇA A OPÇÃO DE CADASTRAR PACIENTE*/
											if( c_pas == CAD_PASC){ /*Conferindo se o numero de cadastros disponíveis chegou ao limite*/
												system("cls");
												cad_limite_pas();													
											}else{
												op_continuar = '1';
												while(op_continuar == '1' && c_pas < CAD_PASC){
													do{														
														system("cls");	/*AQUI VAI LER O CPF DO PACIENTE,  que servirá como identificador*/
														faixada();
														contagem_pas(c_pas);											
														strcpy(cad_pas[c_pas].cpf," "); /*formatando a variável*/
														printf("CPF:  ");
														scanf("%s", cpf_pas); 
														fflush(stdin);
														tam_cpf = strlen(cpf_pas);
														soma_cpf = 0;										
										
														for(c = 0; c < 9; c++){
															numero_cpf = cpf_pas[c] - 48;
															soma_cpf = soma_cpf + (numero_cpf * (10-c));
														}										
														resultado_cpf = 11 - (soma_cpf%11);										
															if(resultado_cpf == 10 || resultado_cpf == 11){
																digito10 = '0';
															}else{
																digito10 = resultado_cpf + 48;
															}										
														soma_cpf = 0;
														
														for(c = 0; c < 10; c++){
															numero_cpf = cpf_pas[c] - 48;
															soma_cpf = soma_cpf +(numero_cpf * (11-c));
														}														
														resultado_cpf = 11 - (soma_cpf%11);
														
															if(resultado_cpf == 10 || resultado_cpf == 11){
																digito11 = '0';										
															}else{
																digito11 = resultado_cpf + 48;
															}																					
															if(cpf_pas[9] != digito10 || cpf_pas[10] != digito11 || tam_cpf != 11){
																do{
																	system("cls");
																	cpf_invalido();
																	printf("DIGITE NOVAMENTE (ex: 12345678901): ");
																	printf("CPF:  ");
																	scanf("%s", cpf_pas); 			
																	fflush(stdin);
																	tam_cpf = strlen(cpf_pas);
																	soma_cpf = 0;																								
																	for(c = 0; c < 9; c++){
																		numero_cpf = cpf_pas[c] - 48;
																		soma_cpf = soma_cpf + (numero_cpf * (10-c));
																	}
																	
																	resultado_cpf = 11 - (soma_cpf%11);													
																		if(resultado_cpf == 10 || resultado_cpf == 11){
																			digito10 = '0';
																		}else{
																			digito10 = resultado_cpf + 48;
																		}													
																	soma_cpf = 0;
																	
																	for(c = 0; c < 10; c++){
																		numero_cpf = cpf_pas[c] - 48;
																		soma_cpf = soma_cpf +(numero_cpf * (11-c));
																	}													
																	resultado_cpf = 11 - (soma_cpf%11);													
																		if(resultado_cpf == 10 || resultado_cpf == 11){
																			digito11 = '0';													
																		}else{
																			digito11 = resultado_cpf + 48;
																		}
																}while(cpf_pas[9] != digito10 || cpf_pas[10] != digito11 || tam_cpf != 11);	
															}																																	
														/*soma_cpf = 0, numero_cpf = 0, resultado_cpf = 0*/										
															for(c = 0; c <= c_pas; c++){ /*verificando se ja existe o cpf*/																																																																																																														
																if(strcmp(cpf_pas, cad_pas[c].cpf) == 0){
																	do{	
																		system("cls");
																		ja_possui_cad();
																		printf("INFORME OUTRO CPF (ex: 00000000000): ");																
																		scanf("%s", cpf_pas); 
																		tam_cpf = strlen(cpf_pas);			
																		fflush(stdin);
																		
																		soma_cpf = 0;																								
																		for(c = 0; c < 9; c++){
																			numero_cpf = cpf_pas[c] - 48;
																			soma_cpf = soma_cpf + (numero_cpf * (10-c));
																		}
																		
																		resultado_cpf = 11 - (soma_cpf%11);													
																			if(resultado_cpf == 10 || resultado_cpf == 11){
																				digito10 = '0';
																			}else{
																				digito10 = resultado_cpf + 48;
																			}													
																		soma_cpf = 0;
																		
																		for(c = 0; c < 10; c++){
																			numero_cpf = cpf_pas[c] - 48;
																			soma_cpf = soma_cpf +(numero_cpf * (11-c));
																		}													
																		resultado_cpf = 11 - (soma_cpf%11);													
																			if(resultado_cpf == 10 || resultado_cpf == 11){
																				digito11 = '0';													
																			}else{
																				digito11 = resultado_cpf + 48;
																			}																																																									
																	}while(strcmp(cpf_pas, cad_pas[c].cpf) == 0);															
																		while(cpf_pas[9] != digito10 || cpf_pas[10] != digito11 ||  tam_cpf != 11){
																			system("cls");
																			cpf_invalido();
																			printf("DIGITE NOVAMENTE (ex: 12345678901): ");																			
																			scanf("%s", cpf_pas); 			
																			tam_cpf = strlen(cpf_pas);
																			fflush(stdin);			
																			
																			soma_cpf = 0;																								
																			for(c = 0; c < 9; c++){
																				numero_cpf = cpf_pas[c] - 48;
																				soma_cpf = soma_cpf + (numero_cpf * (10-c));
																			}
																			
																			resultado_cpf = 11 - (soma_cpf%11);													
																				if(resultado_cpf == 10 || resultado_cpf == 11){
																					digito10 = '0';
																				}else{
																					digito10 = resultado_cpf + 48;
																				}													
																			soma_cpf = 0;
																			
																			for(c = 0; c < 10; c++){
																				numero_cpf = cpf_pas[c] - 48;
																				soma_cpf = soma_cpf +(numero_cpf * (11-c));
																			}													
																			resultado_cpf = 11 - (soma_cpf%11);													
																				if(resultado_cpf == 10 || resultado_cpf == 11){
																					digito11 = '0';													
																				}else{
																					digito11 = resultado_cpf + 48;
																				}
																		}	
																		c = 0;
																	}																																	
																}	
														strcpy(cad_pas[c_pas].cpf, cpf_pas);
														
														system("cls"); /*AQUI VAI LER O NOME DO PACIENTE*/
														cpf_valido();
														contagem_pas(c_pas); 
														printf("NOME: ");
														scanf("%[^\n]s", cad_pas[c_pas].nome);
														fflush(stdin);
														tam_nome = strlen(cad_pas[c_pas].nome);
														for(c = 0 ;c <= tam_nome;c++){
															cad_pas[c_pas].nome[c] = toupper(cad_pas[c_pas].nome[c]); /*PASSANDO PARA MAIÚSCULO*/
														}
														
														system("cls");	/*AQUI VAI LER O SEXO DO PACIENTE*/
														faixada();
														contagem_pas(c_pas); 
														cad_pas[c_pas].sexo = le_valida_sexo(c_pas);
			
														system("cls");	/*AQUI VAI LER A DATA DE NASCIMENTO DO PACIENTE*/
														faixada();
														contagem_pas(c_pas); 
														printf("\n");
														printf("DATA DE NASCIMENTO: \n\n"); 
														cad_pas[c_pas].dia = le_val_dia(c_pas); /*dia*/ 
														cad_pas[c_pas].mes = le_val_mes(c_pas); /*mês*/
														cad_pas[c_pas].ano = le_val_ano(c_pas, ano_atual); /*ano*/
														cad_pas[c_pas].idade = ano_atual - cad_pas[c_pas].ano; /*COLETANDO A IDADE*/
														
														system("cls");	/*AQUI VAI LER O TELEFONE DO PACIENTE*/
														faixada();
														contagem_pas(c_pas); 
														printf("TELEFONE: "); 														
														scanf("%s", cad_pas[c_pas].telefone);												
														fflush(stdin);															
														
														system("cls");	/*IMPRIMINDO OS DADOS DO PACIENTE QUE FORAM DIGITADOS*/
														faixada();
																												
														agora = time(NULL); /*COLETANDO A HORA E DATA DO SISTEMA EM STRING*/
														
														strftime(cad_pas[c_pas].data, sizeof(cad_pas[c_pas].data), "%d/%m/%y", localtime(&agora)); /*data*/
														strftime(cad_pas[c_pas].hora, sizeof(cad_pas[c_pas].hora), "%H:%M:%S", localtime(&agora)); /*hora*/
														
														printf("CPF: ...................%s\n", cad_pas[c_pas].cpf); /*Apresentando os dados digitados*/
														printf("NOME: ..................%s\n", cad_pas[c_pas].nome);
															if(cad_pas[c_pas].sexo == '1'){
																printf("SEXO: ..................MASCULINO\n");
															}else{
																printf("SEXO: ..................FEMININO\n");
															}
														printf("DATA DE NASCIMENTO......%d/%d/%d\n", cad_pas[c_pas].dia, cad_pas[c_pas].mes, cad_pas[c_pas].ano);
														printf("IDADE...................%d ANOS\n", cad_pas[c_pas].idade);
														printf("TELEFONE:...............%s\n", cad_pas[c_pas].telefone);
														printf("________________________________________________________________________________\n");										
														printf("                      DATA: %s          HORA: %s\n", cad_pas[c_pas].data, cad_pas[c_pas].hora);														
														printf("________________________________________________________________________________\n\n");
														op_dados = le_val_dados_corretos();	/*PERGUNTA SE OD DADOS ENTÃO CORRETOS*/
													}while(op_dados != '1');
													
													dimensao_nome = strlen(cad_pas[c_pas].nome);
													
													for(c = dimensao_nome - 1; c >= 0; c-- ){ /*PASSANDO O PRIMEIRO NOME DO PACIENTE PARA MAÍUSCULO*/
														if(cad_pas[c_pas].nome[c] == ' '){
															primeiro_espaco = c;
														}
													}
													for(c = 0; c <= primeiro_espaco; c++){
														primeiro_nome_pas[c] = toupper(cad_pas[c_pas].nome[c]);
													}										
														if(cad_pas[c_pas].sexo == '1'){ /*SE OS DADOS ESTIVEREM CORRETOS, AQUI VAI MOSTRAR QUE O PACIENTE FOI CADASTRADO*/
															printf("\n\n");/*se for homem*/
															printf("-------------------------------------------------------------------------------\n");
															printf("             O paciente, %s, foi cadastrado com Sucesso!!\n", primeiro_nome_pas);
															printf("-------------------------------------------------------------------------------\n\n");
															qtd_homem_pas += 1; /*coletando a qtd de homens*/
														}else{
															printf("\n\n");/*se for mulher*/
															printf("-------------------------------------------------------------------------------\n");
															printf("             A paciente, %s, foi cadastrada com Sucesso!!\n", primeiro_nome_pas);
															printf("-------------------------------------------------------------------------------\n\n");
															qtd_mulher_pas += 1;/*coletando a qtd de mulheres*/
														}
														cad_pas[c_pas].agendamento = false;
														c_pas += 1;	
														if(c_pas == CAD_PASC){ /*AQUI VAI VERIFICAR SE O NUMERO MÁXIMO DE CADASTROS FORAM ATINGIDOS*/
															op_continuar = '2';
															printf("                      LIMITE DE CADASTROS ATINGIDOS\n");
															printf("________________________________________________________________________________\n\n");
															system("PAUSE");														
														}else{
															op_continuar = le_val_op_continuar_cad(); /*SE NÃO FORAR, AQUI VAI PERGUNTAR SE O USUÁRIO DESEJA CONTINUARCADASTRANDO*/
														}				
												}
											}																								
										break; /*AQUI TERMINA A OPÇÃO CADASTRAR PACIENTE*/
										
										case '2':/* AQUI COMEÇA A OPÇÃO DE CADASTRAR MÉDICO*/
											if(c_med == CAD_MED){
												system("cls");
												cad_limite_med();	
											}else{
												op_continuar = '1';
												while(op_continuar == '1' && c_med < CAD_MED){
													do{
														strcpy(cpf_pas,"   ");
														system("cls");	/*AQUI VAI LER O CPF DO MÉDICO,  que servirá como identificador*/
														faixada();
														contagem_med(c_med);											
														strcpy(cad_med[c_med].cpf," ");
														strcpy(cad_med[c_med].crm," "); /*formatando a variável*/
														printf("CPF:  ");
														scanf("%s", cpf_med);
														tam_cpf = strlen(cpf_med); 											
														fflush(stdin);
														
														soma_cpf = 0;										
														
														for(c = 0; c < 9; c++){
															numero_cpf = cpf_med[c] - 48;
															soma_cpf = soma_cpf + (numero_cpf * (10-c));
														}										
														resultado_cpf = 11 - (soma_cpf%11);										
															if(resultado_cpf == 10 || resultado_cpf == 11){
																digito10 = '0';
															}else{
																digito10 = resultado_cpf + 48;
															}										
														soma_cpf = 0;
														
														for(c = 0; c < 10; c++){
															numero_cpf = cpf_med[c] - 48;
															soma_cpf = soma_cpf +(numero_cpf * (11-c));
														}														
														resultado_cpf = 11 - (soma_cpf%11);														
															if(resultado_cpf == 10 || resultado_cpf == 11){
																digito11 = '0';										
															}else{
																digito11 = resultado_cpf + 48;
															}																					
															if(cpf_med[9] != digito10 || cpf_med[10] != digito11 || tam_cpf != 11){
																do{
																	system("cls");
																	cpf_invalido();
																	printf("DIGITE NOVAMENTE (ex: 12345678901): ");
																	scanf("%s", cpf_med); 	
																	tam_cpf = strlen(cpf_med);										
																	fflush(stdin);																				
																	soma_cpf = 0;																								
																	
																	for(c = 0; c < 9; c++){
																		numero_cpf = cpf_med[c] - 48;
																		soma_cpf = soma_cpf + (numero_cpf * (10-c));
																	}																	
																	resultado_cpf = 11 - (soma_cpf%11);													
																		if(resultado_cpf == 10 || resultado_cpf == 11){
																			digito10 = '0';
																		}else{
																			digito10 = resultado_cpf + 48;
																		}													
																	soma_cpf = 0;
																	
																	for(c = 0; c < 10; c++){
																		numero_cpf = cpf_med[c] - 48;
																		soma_cpf = soma_cpf +(numero_cpf * (11-c));
																	}													
																	resultado_cpf = 11 - (soma_cpf%11);													
																		if(resultado_cpf == 10 || resultado_cpf == 11){
																			digito11 = '0';													
																		}else{
																			digito11 = resultado_cpf + 48;
																		}
																}while(cpf_med[9] != digito10 || cpf_med[10] != digito11  || tam_cpf != 11);	
															}																																	
														/*soma_cpf = 0, numero_cpf = 0, resultado_cpf = 0*/										
															for(c = 0; c <= c_med; c++){ /*verificando se ja existe o cpf*/																																																																																																														
																if(strcmp(cpf_med, cad_med[c].cpf) == 0){
																	do{	
																		system("cls");
																		ja_possui_cad();
																		printf("INFORME OUTRO CPF (ex: 00000000000): ");
																		scanf("%s", cpf_med);
																		tam_cpf = strlen(cpf_med);											
																		fflush(stdin);
																		soma_cpf = 0;																								
																		
																		for(c = 0; c < 9; c++){
																			numero_cpf = cpf_med[c] - 48;
																			soma_cpf = soma_cpf + (numero_cpf * (10-c));
																		}	
																		resultado_cpf = 11 - (soma_cpf%11);													
																			if(resultado_cpf == 10 || resultado_cpf == 11){
																				digito10 = '0';
																			}else{
																				digito10 = resultado_cpf + 48;
																			}													
																		soma_cpf = 0;
																		
																		for(c = 0; c < 10; c++){
																			numero_cpf = cpf_med[c] - 48;
																			soma_cpf = soma_cpf +(numero_cpf * (11-c));
																		}													
																		resultado_cpf = 11 - (soma_cpf%11);													
																			if(resultado_cpf == 10 || resultado_cpf == 11){
																				digito11 = '0';													
																			}else{
																				digito11 = resultado_cpf + 48;
																			}																																																									
																	}while(strcmp(cpf_med, cad_med[c].cpf) == 0);															
																	
																	while(cpf_med[9] != digito10 || cpf_med[10] != digito11  || tam_cpf != 11){
																		system("cls");
																		cpf_invalido();
																		printf("DIGITE NOVAMENTE (ex: 12345678901): ");
																		scanf("%s", cpf_med); 
																		tam_cpf = strlen(cpf_med);											
																		fflush(stdin);																					
																		soma_cpf = 0;																								
																		
																		for(c = 0; c < 9; c++){
																			numero_cpf = cpf_med[c] - 48;
																			soma_cpf = soma_cpf + (numero_cpf * (10-c));
																		}																		
																		resultado_cpf = 11 - (soma_cpf%11);													
																			if(resultado_cpf == 10 || resultado_cpf == 11){
																				digito10 = '0';
																			}else{
																				digito10 = resultado_cpf + 48;
																			}													
																		soma_cpf = 0;
																		
																		for(c = 0; c < 10; c++){
																			numero_cpf = cpf_med[c] - 48;
																			soma_cpf = soma_cpf +(numero_cpf * (11-c));
																		}													
																		resultado_cpf = 11 - (soma_cpf%11);													
																			if(resultado_cpf == 10 || resultado_cpf == 11){
																				digito11 = '0';													
																			}else{
																				digito11 = resultado_cpf + 48;
																			}
																	}	
																	c = 0;
																}																																	
															}	
														strcpy(cad_med[c_med].cpf, cpf_med);
														
														system("cls"); /*AQUI VAI LER O NOME DO MÉDICO*/
														cpf_valido();
														contagem_med(c_med); 
														printf("NOME: ");
														scanf("%[^\n]s", cad_med[c_med].nome);
														fflush(stdin);
														tam_nome = strlen(cad_med[c_med].nome);
														
														for(c = 0 ;c <= tam_nome;c++){
															cad_med[c_med].nome[c] = toupper(cad_med[c_med].nome[c]); /*PASSANDO PARA MAIÚSCULO*/
														}														
														system("cls");	/*AQUI VAI LER O SEXO DO MÉDICO*/
														faixada();
														contagem_med(c_med); 
														cad_med[c_med].sexo = le_valida_sexo(c_med);
																										
														system("cls");	/*AQUI VAI LER A DATA DE NASCIMENTO DO MÉDICO*/
														faixada();
														contagem_med(c_med); 
														printf("\n");
														printf("DATA DE NASCIMENTO: \n\n"); 
														cad_med[c_med].dia = le_val_dia(c_med); /*dia*/ 
														cad_med[c_med].mes = le_val_mes(c_med); /*mês*/
														cad_med[c_med].ano = le_val_ano(c_med, ano_atual); /*ano*/
														cad_med[c_med].idade = ano_atual - cad_med[c_med].ano; /*COLETANDO A IDADE*/
																												
														system("cls");	/*AQUI VAI LER O CRM DO MÉDICO*/
														faixada();
														contagem_med(c_med); 
														strcpy(cad_med[c_med].crm, " ");
														printf("CRM: "); 
														scanf("%s", crm);														
														fflush(stdin);
														tam_crm = strlen(crm);
																
														for(c = 0; c <= c_med;c++){																	 												
															while(strcmp(crm, cad_med[c].crm) == 0  || tam_crm < CRM_MIN || tam_crm > CRM_MAX){												
																if(strcmp(crm, cad_med[c].crm) == 0){ /*Verificando se o CRM ja existe*/	
																	do{
																		system("cls");
																		crm_existente();
																		contagem_med(c_med);
																		printf("DIGITE NOVAMENTE: ");
																		scanf("%s", crm);														
																		fflush(stdin);
																		tam_crm = strlen(crm);	
																	}while(strcmp(crm, cad_med[c].crm) == 0);	
																}
																if(tam_crm < CRM_MIN || tam_crm > CRM_MAX){ /*validando a quantidade de caracteres dao CRM*/
																	do{
																		if(tam_crm < CRM_MIN){ /*se for menor que a qtd mínima  de caractere*/
																			do{
																				system("cls");
																				crm_menor(CRM_MIN);
																				contagem_med(c_med);
																				printf("DIGITE NOVAMENTE: ");
																				scanf("%s", crm);														
																				fflush(stdin);
																				tam_crm = strlen(crm);
																			}while(tam_crm < CRM_MIN);
																		}
																		if (tam_crm > CRM_MAX){ /*se for maior que a qtd máxima de caracteres*/
																			do{
																				system("cls");
																				crm_maior(CRM_MAX);
																				contagem_med(c_med);
																				printf("DIGITE NOVAMENTE: ");
																				scanf("%s", crm);														
																				fflush(stdin);
																				tam_crm = strlen(crm);		
																			}while(tam_crm > CRM_MAX);	
																		}																																				
																	}while(tam_crm < CRM_MIN || tam_crm > CRM_MAX);																																	
																}	
															}
														}														
														strcpy(cad_med[c_med].crm, crm);	
														system("cls"); /*AQUI VAI LER OS DIAS TRABALHADOS DO MÉDICO*/
														faixada();
														contagem_med(c_med);
														cad_med[c_med].dia_trab = le_valida_dias_trab(c_med);											
																													
														system("cls");	/*IMPRIMINDO OS DADOS DO MÉDICO QUE FORAM DIGITADOS*/
														faixada();
														agora = time(NULL); /*COLETANDO A DATA E HORA ATUAL EM STRING*/
														
														strftime(cad_med[c_med].data, sizeof(cad_med[c_med].data), "%d/%m/%y", localtime(&agora)); /*data*/
														strftime(cad_med[c_med].hora, sizeof(cad_med[c_med].hora), "%H:%M:%S", localtime(&agora)); /*hora*/
														
														printf("CPF: ...................%s\n", cad_med[c_med].cpf); /*Apresentando os dados digitados*/
														printf("NOME: ..................%s\n", cad_med[c_med].nome);
															if(cad_med[c_med].sexo == '1'){
																printf("SEXO: ..................MASCULINO\n");
															}else{
																printf("SEXO: ..................FEMININO\n");
															}
														printf("DATA DE NASCIMENTO......%d/%d/%d\n", cad_med[c_med].dia, cad_med[c_med].mes, cad_med[c_med].ano);
														printf("IDADE...................%d ANOS\n", cad_med[c_med].idade);
														printf("CRM:....................%s\n", cad_med[c_med].crm);
														printf("________________________________________________________________________________\n");										
														printf("                      DATA: %s          HORA: %s\n", cad_med[c_med].data, cad_med[c_med].hora);	
														printf("________________________________________________________________________________\n\n");
														op_dados = le_val_dados_corretos();	/*PERGUNTA SE OD DADOS ENTÃO CORRETOS*/
													}while(op_dados != '1');
													
													dimensao_nome = strlen(cad_med[c_med].nome);
													
													for(c = dimensao_nome - 1; c >= 0; c-- ){ /*PASSANDO O PRIMEIRO NOME DO MÉDICO PARA MAÍUSCULO*/
														if(cad_med[c_med].nome[c] == ' '){
															primeiro_espaco = c;
														}
													}
													for(c = 0; c <= primeiro_espaco; c++){
														primeiro_nome_med[c] = toupper(cad_med[c_med].nome[c]);
													}										
														if(cad_med[c_med].sexo == '1'){ /*SE OS DADOS ESTIVEREM CORRETOS, AQUI VAI MOSTRAR QUE O MÉDICO FOI CADASTRADO*/
															printf("\n\n");/*se for homem*/
															printf("-------------------------------------------------------------------------------\n");
															printf("             O médico, %s, foi cadastrado com Sucesso!!\n", primeiro_nome_med);
															printf("-------------------------------------------------------------------------------\n\n");
															qtd_homem_med +=1; /*coletando q qtd de homens*/
														}else{
															printf("\n\n");/*se for mulher*/
															printf("-------------------------------------------------------------------------------\n");
															printf("             A médica, %s, foi cadastrada com Sucesso!!\n", primeiro_nome_med);
															printf("-------------------------------------------------------------------------------\n\n");
															qtd_mulher_med +=1; /*coletando a qtd de mulheres*/
														}
														c_med += 1;	
														if(c_med == CAD_MED){ /*AQUI VAI VERIFICAR SE O NUMERO MÁXIMO DE CADASTROS FORAM ATINGIDOS*/
															op_continuar = '2';
															printf("                      LIMITE DE CADASTROS ATINGIDOS\n");
															printf("________________________________________________________________________________\n\n");
															system("PAUSE");														
														}else{
															op_continuar = le_val_op_continuar_cad(); /*SE NÃO FORAR, AQUI VAI PERGUNTAR SE O USUÁRIO DESEJA CONTINUARCADASTRANDO*/
														}				
												}
											}												
										break; /*AQUI TERMINA A OPÇÃO DE CADASTRAR MÉDICO*/
									}
								}while(op_pasc != '3');
							break;
							
							case '2':/*QUI COMEÇA A SESSÃO DE AGENDAMENTO*/
								if(c_pas == 0){
									system("cls"); /*verificando de o sistema possui agendamentos*/
									sem_pasciente();
								}else{
									do{								
										system("cls");
										agendamento(); /*lendo o cpf para verificar se o paciente possui cadastro e agendamento marcado*/
										printf("CPF: ");	
										scanf("%s", cpf_ag);
										tam_cpf = strlen(cpf_ag);										
										fflush(stdin);
										soma_cpf = 0;										
										
										for(c = 0; c < 9; c++){ /*validação do cpf*/
											numero_cpf = cpf_ag[c] - 48;
											soma_cpf = soma_cpf + (numero_cpf * (10-c));
										}										
										resultado_cpf = 11 - (soma_cpf%11);										
											if(resultado_cpf == 10 || resultado_cpf == 11){
												digito10 = '0';
											}else{
												digito10 = resultado_cpf + 48;
											}										
										soma_cpf = 0;
										
										for(c = 0; c < 10; c++){
											numero_cpf = cpf_ag[c] - 48;
											soma_cpf = soma_cpf +(numero_cpf * (11-c));
										}										
										resultado_cpf = 11 - (soma_cpf%11);
										
											if(resultado_cpf == 10 || resultado_cpf == 11){
												digito11 = '0';										
											}else{
												digito11 = resultado_cpf + 48;
											}																					
											if(cpf_ag[9] != digito10 || cpf_ag[10] != digito11 || tam_cpf != 11){
												do{
													system("cls");
													cpf_invalido();
													printf("DIGITE NOVAMENTE (ex: 12345678901): ");
													scanf("%s", cpf_ag);
													tam_cpf = strlen(cpf_ag);										
													fflush(stdin);																
													soma_cpf = 0;																								
													
													for(c = 0; c < 9; c++){
														numero_cpf = cpf_ag[c] - 48;
														soma_cpf = soma_cpf + (numero_cpf * (10-c));
													}													
													resultado_cpf = 11 - (soma_cpf%11);													
														if(resultado_cpf == 10 || resultado_cpf == 11){
															digito10 = '0';
														}else{
															digito10 = resultado_cpf + 48;
														}													
													soma_cpf = 0;
													
													for(c = 0; c < 10; c++){
														numero_cpf = cpf_ag[c] - 48;
														soma_cpf = soma_cpf +(numero_cpf * (11-c));
													}													
													resultado_cpf = 11 - (soma_cpf%11);													
														if(resultado_cpf == 10 || resultado_cpf == 11){
															digito11 = '0';													
														}else{
															digito11 = resultado_cpf + 48;
														}
												}while(cpf_ag[9] != digito10 || cpf_ag[10] != digito11 || tam_cpf != 11);	
											}																																				
										cpf_pas_encotrado = 0; /*reiniciando variáveis*/
										cpf_encontrado = false;
										valid_cpf = false;							
										for(c = 0; c <= c_pas; c++){ /*AQUI VAI VERIFICAR SE O CPF DO PACIENTE EXISTE*/
											if(strcmp(cpf_ag, cad_pas[c].cpf) == 0){
												cpf_encontrado = true;
												cpf_pas_encotrado = c;							
											}	
										}					
											if(cpf_encontrado != true){ /*SE NÃO EXISTIR O CPF*/
												system("cls");
												cpf_nao_encontrado();	
											}else{												
												if(cad_pas[cpf_pas_encotrado].agendamento != true){ /*SE EXISTIR O CPF, VAI VERIFICAR SE O PACIENTE JA POSSUI AGENDAMENTO*/
													valid_cpf = true;																	
												}																																																	
												if(valid_cpf != true){ /*SE NÃO EXISTIR AGENDAMENTO*/
													system("cls");
													possui_agendamento();	
												}else{
													do{
														system("cls"); /*SE EXISTIR AGENDAMENTO*/
														agendamento();
														op = le_val_select_unidade();														
														switch(op){ /*AQUI COMEÇA O AGENDAMENTO PARA UNIDADE GUARÁ*/
															case '1':
																strcpy(cad_agend_guara[c_agend_guara].cpf, cad_pas[cpf_pas_encotrado].cpf);	/*transferindo os dados do formulário de paciente para o formulário de agendamento*/
																strcpy(cad_agend_guara[c_agend_guara].nome, cad_pas[cpf_pas_encotrado].nome);
																cad_agend_guara[c_agend_guara].idade = cad_pas[cpf_pas_encotrado].idade;
																cad_agend_guara[c_agend_guara].sexo = cad_pas[cpf_pas_encotrado].sexo;
																
																system("cls");
																agendamento();
																printf("Nome do paciente: %s\n", cad_pas[cpf_pas_encotrado].nome);
																printf("________________________________________________________________________________\n");
																printf("DIA DO AGENDAMENTO: "); /*coletando o dia do agendamento*/
																scanf("%d", &dia_agendamento);																													   																																											
																	if(dia_agendamento < dia_atual || dia_agendamento < 1 || dia_agendamento > 31){ /*validação do dia*/
																		do{																										
																			if(dia_agendamento < 1 || dia_agendamento > 31){
																				system("cls");
																				dia_invalido();
																				printf("Nome do paciente: %s\n", cad_pas[cpf_pas_encotrado].nome);
																				printf("________________________________________________________________________________\n");
																				printf("INFORME OUTRO DIA: ");
																				scanf("%d", &dia_agendamento);		
																			}																																						
																			if(dia_agendamento < dia_atual){
																				system("cls");
																				dia_indisponivel();
																				printf("Nome do paciente: %s\n", cad_pas[cpf_pas_encotrado].nome);
																				printf("________________________________________________________________________________\n");
																				printf("INFORME OUTRO DIA: ");
																				scanf("%d", &dia_agendamento);	
																			}																		
																		}while(dia_agendamento < dia_atual || dia_agendamento > 31);																	
																	}																
																cad_agend_guara[c_agend_guara].dia_ag = dia_agendamento; /*coletando a data de agendamento */
																cad_agend_guara[c_agend_guara].mes_ag = mes_atual;
																cad_agend_guara[c_agend_guara].ano_ag = ano_atual;	
																
																system("cls");
																agendamento();
																printf("Nome do paciente: %s\n", cad_pas[cpf_pas_encotrado].nome);
																printf("________________________________________________________________________________\n\n");																
																for(c = 0; c <= 9; c++){ /*Aapresentando os horários disponíveis para o agendamento*/
																	printf("| %s ", dias_guara[dia_agendamento].horarios_guara[c].hr);												
																}
																printf("\n");
																printf("________________________________________________________________________________\n\n");																
																printf("INFORME O HORÁRIO: ");
																scanf("%s", horario_agendamento);
																fflush(stdin); /*validando o horário informado*/
																	if(strcmp(horario_agendamento, "09:00")  && strcmp(horario_agendamento, "10:00")  && strcmp(horario_agendamento, "11:00")  && strcmp(horario_agendamento, "12:00")  && strcmp(horario_agendamento, "13:00")  && strcmp(horario_agendamento, "14:00")  && strcmp(horario_agendamento, "15:00") && strcmp(horario_agendamento, "16:00") && strcmp(horario_agendamento, "17:00") && strcmp(horario_agendamento, "18:00") != 0){
																		do{
																			system("cls");
																			dados_invalidos();
																			printf("Nome do paciente: %s\n", cad_pas[cpf_pas_encotrado].nome);
																			printf("________________________________________________________________________________\n\n");																			
																			for(c = 0; c <= 9; c++){
																				printf("| %s ", dias_guara[dia_agendamento].horarios_guara[c].hr);												
																			}
																			printf("\n");
																			printf("________________________________________________________________________________\n\n");
																			printf("DIGITE NOVAMENTE (EX: 15:00): ");
																			scanf("%s", horario_agendamento);
																			fflush(stdin);
																		}while(strcmp(horario_agendamento, "09:00")  && strcmp(horario_agendamento, "10:00")  && strcmp(horario_agendamento, "11:00")  && strcmp(horario_agendamento, "12:00")  && strcmp(horario_agendamento, "13:00")  && strcmp(horario_agendamento, "14:00")  && strcmp(horario_agendamento, "15:00") && strcmp(horario_agendamento, "16:00") && strcmp(horario_agendamento, "17:00") && strcmp(horario_agendamento, "18:00") != 0);
																	}																
																valid_horario = false; /*reiniciando a variável*/																
																for(c = 0; c <=9; c++){ /*verificando se o horário informado estar disponível e coletando o seu indice*/
																	if(strcmp(horario_agendamento,dias_guara[dia_agendamento].horarios_guara[c].hr ) == 0){
																		valid_horario = true;
																		strcpy(dias_guara[dia_agendamento].horarios_guara[c].hr, "-----");
																		strcpy(cad_agend_guara[c_agend_guara].hora_agend, horario_agendamento);	
																		cad_agend_guara[c_agend_guara].pos_hora_agend = c;
																	}
																}											
																	if(valid_horario != true){ /*VAI INFORMAR QUE O HORÁRIO JA ESTAR MARCADO*/
																		do{
																			system("cls");
																			horario_indisponivel();
																			printf("Nome do paciente: %s\n", cad_pas[cpf_pas_encotrado].nome);
																			printf("________________________________________________________________________________\n\n");																			
																			for(c = 0; c <= 9; c++){
																				printf("| %s ", dias_guara[dia_agendamento].horarios_guara[c].hr);												
																			}
																			printf("\n");
																			printf("________________________________________________________________________________\n\n");																			
																			printf("INFORME OUTRO HORÁRIO: ");
																			scanf("%s", horario_agendamento);
																			fflush(stdin);																			
																				if(strcmp(horario_agendamento, "09:00")  && strcmp(horario_agendamento, "10:00")  && strcmp(horario_agendamento, "11:00")  && strcmp(horario_agendamento, "12:00")  && strcmp(horario_agendamento, "13:00")  && strcmp(horario_agendamento, "14:00")  && strcmp(horario_agendamento, "15:00") && strcmp(horario_agendamento, "16:00") && strcmp(horario_agendamento, "17:00") && strcmp(horario_agendamento, "18:00") != 0){
																					do{
																						system("cls");
																						dados_invalidos();
																						printf("Nome do paciente: %s\n", cad_pas[cpf_pas_encotrado].nome);
																						printf("________________________________________________________________________________\n\n");
																						
																						for(c = 0; c <= 9; c++){
																						printf("| %s ", dias_guara[dia_agendamento].horarios_guara[c].hr);												
																						}
																						printf("\n");
																						printf("________________________________________________________________________________\n\n");
																						printf("DIGITE NOVAMENTE (EX: 15:00): ");
																						scanf("%s", horario_agendamento);
																						fflush(stdin);
																					}while(strcmp(horario_agendamento, "09:00")  && strcmp(horario_agendamento, "10:00")  && strcmp(horario_agendamento, "11:00")  && strcmp(horario_agendamento, "12:00")  && strcmp(horario_agendamento, "13:00")  && strcmp(horario_agendamento, "14:00")  && strcmp(horario_agendamento, "15:00") && strcmp(horario_agendamento, "16:00") && strcmp(horario_agendamento, "17:00") && strcmp(horario_agendamento, "18:00") != 0);
																				}																			
																			valid_horario = false;																			
																				for(c = 0; c <=9; c++){
																					if(strcmp(horario_agendamento,dias_guara[dia_agendamento].horarios_guara[c].hr ) == 0){
																						valid_horario = true;
																						strcpy(dias_guara[dia_agendamento].horarios_guara[c].hr, "-----");
																						strcpy(cad_agend_guara[c_agend_guara].hora_agend, horario_agendamento);	
																					}
																			}																											
																		}while(valid_horario != true);	/*vai se repetir ate o usuário informar um horario válido*/
																	}																		
																	if(dia_agendamento == dia_atual ){ /*assim que o horário for registrado, aqui vai armazenar o valor da consulta*/
																		fat_dia_guara += 70.00;
																		fat_total_d += 70.00;
																		ag_dia_guara +=1;
																	}																	
																	fat_mes_guara += 70.00;
																	fat_total += 70.00;
																																
																agora = time(NULL);																
																strftime(cad_agend_guara[c_agend_guara].data, sizeof(cad_agend_guara[c_agend_guara].data), "%d/%m/%y", localtime(&agora));/*AQUI VAI COLETAR ADATA QUE FOI REALIZADO O AGENDAMENTO*/
																strftime(cad_agend_guara[c_agend_guara].hora, sizeof(cad_agend_guara[c_agend_guara].hora), "%H:%M:%S", localtime(&agora)); /*AQUI VAI COLETAR O HORARIO QUE FOI REALIZADP P AGENDAMENTO AGENDAMENTO*/
																
																system("cls");
																agend_realizado();																
																for(c = 0; c <= 9; c++){
																	printf("| %s ", dias_guara[dia_agendamento].horarios_guara[c].hr);												
																}
																printf("|\n"); /*Apresentando os dados informados*/
																printf("________________________________________________________________________________\n\n");											
																printf("CPF:......................%s\n", cad_agend_guara[c_agend_guara].cpf);
																printf("NOME:.....................%s\n", cad_agend_guara[c_agend_guara].nome);
																printf("IDADE.....................%d ANOS\n",cad_agend_guara[c_agend_guara].idade);	
																	if(cad_agend_guara[c_agend_guara].sexo == '1'){
																		printf("SEXO:.....................MASCULINO\n");
																	}else{
																		printf("SEXO:.....................FEMININO\n");
																	}
																printf("DATA DO AGENDAMENTO.......%d/%d/%d\n", cad_agend_guara[c_agend_guara].dia_ag, cad_agend_guara[c_agend_guara].mes_ag, cad_agend_guara[c_agend_guara].ano_ag);
																printf("HORÁRIO DO AGENDAMENTO....%s\n", cad_agend_guara[c_agend_guara].hora_agend);
																printf("TELEFONE:.................%s\n", cad_pas[cpf_pas_encotrado].telefone);
																printf("________________________________________________________________________________\n");	
																printf("VALOR DA CUNSULTA : R$ 70,00\n\n");
																printf("________________________________________________________________________________\n");										
																printf("                      DATA: %s          HORA: %s\n", cad_agend_guara[c_agend_guara].data, cad_agend_guara[c_agend_guara].hora);														
																printf("________________________________________________________________________________\n\n\n");																
																system("PAUSE");													
																
																cad_pas[cpf_pas_encotrado].id_agend = c_agend_guara; /*coletando a posição em que o paciente estar no formulário de agendamento */
																cad_pas[cpf_pas_encotrado].agendamento = true; /*vai servir para registrar q o paciente ja possui agendamento*/
																cad_pas[cpf_pas_encotrado].unidade = 1; /*servirá como identificador da unidade q o pacienete estar cadastrado*/										
																tot_agend ++;
																c_agend_guara ++;																
																op = '4';															
															break;
															case '2':  /*AQUI COMEÇA O AGENDAMENTO PARA UNIDADE TAGUATINGA*/
																
																strcpy(cad_agend_tagua[c_agend_tagua].cpf, cad_pas[cpf_pas_encotrado].cpf);	/*transferindo os dados do formulário de paciente para o formulário de agendamento*/
																strcpy(cad_agend_tagua[c_agend_tagua].nome, cad_pas[cpf_pas_encotrado].nome);
																cad_agend_tagua[c_agend_tagua].idade = cad_pas[cpf_pas_encotrado].idade;
																cad_agend_tagua[c_agend_tagua].sexo = cad_pas[cpf_pas_encotrado].sexo;
																
																system("cls");
																agendamento();
																printf("Nome do paciente: %s\n", cad_pas[cpf_pas_encotrado].nome);
																printf("________________________________________________________________________________\n");
																printf("DIA DO AGENDAMENTO: "); /*coletando o dia do agendamento*/
																scanf("%d", &dia_agendamento);																													   																																											
																	if(dia_agendamento < dia_atual || dia_agendamento < 1 || dia_agendamento > 31){ /*validação do dia*/
																		do{																										
																			if(dia_agendamento < 1 || dia_agendamento > 31){
																				system("cls");
																				dia_invalido();
																				printf("Nome do paciente: %s\n", cad_pas[cpf_pas_encotrado].nome);
																				printf("________________________________________________________________________________\n");
																				printf("INFORME OUTRO DIA: ");
																				scanf("%d", &dia_agendamento);		
																			}																			
																			
																			if(dia_agendamento < dia_atual){
																				system("cls");
																				dia_indisponivel();
																				printf("Nome do paciente: %s\n", cad_pas[cpf_pas_encotrado].nome);
																				printf("________________________________________________________________________________\n");
																				printf("INFORME OUTRO DIA: ");
																				scanf("%d", &dia_agendamento);	
																			}																		
																		}while(dia_agendamento < dia_atual || dia_agendamento > 31);																	
																	}																
																cad_agend_tagua[c_agend_tagua].dia_ag = dia_agendamento;/*coletando a data de agendamento */
																cad_agend_tagua[c_agend_tagua].mes_ag = mes_atual;
																cad_agend_tagua[c_agend_tagua].ano_ag = ano_atual;	
																
																system("cls");
																agendamento();
																printf("Nome do paciente: %s\n", cad_pas[cpf_pas_encotrado].nome);
																printf("________________________________________________________________________________\n\n");																
																for(c = 0; c <= 9; c++){/*Aapresentando os horários disponíveis para o agendamento*/
																	printf("| %s ", dias_tagua[dia_agendamento].horarios_tagua[c].hr);												
																}
																printf("\n");
																printf("________________________________________________________________________________\n\n");																
																printf("INFORME O HORÁRIO: ");
																scanf("%s", horario_agendamento);/*coletando o horário*/
																fflush(stdin);
																	 /*validando o horário informado*/
																	if(strcmp(horario_agendamento, "09:00")  && strcmp(horario_agendamento, "10:00")  && strcmp(horario_agendamento, "11:00")  && strcmp(horario_agendamento, "12:00")  && strcmp(horario_agendamento, "13:00")  && strcmp(horario_agendamento, "14:00")  && strcmp(horario_agendamento, "15:00") && strcmp(horario_agendamento, "16:00") && strcmp(horario_agendamento, "17:00") && strcmp(horario_agendamento, "18:00") != 0){
																		do{
																			system("cls");
																			dados_invalidos();
																			printf("Nome do paciente: %s\n", cad_pas[cpf_pas_encotrado].nome);
																			printf("________________________________________________________________________________\n\n");
																			
																			for(c = 0; c <= 9; c++){
																				printf("| %s ", dias_tagua[dia_agendamento].horarios_tagua[c].hr);												
																			}
																			printf("\n");
																			printf("________________________________________________________________________________\n\n");
																			printf("DIGITE NOVAMENTE (EX: 15:00): ");
																			scanf("%s", horario_agendamento);
																			fflush(stdin);
																		}while(strcmp(horario_agendamento, "09:00")  && strcmp(horario_agendamento, "10:00")  && strcmp(horario_agendamento, "11:00")  && strcmp(horario_agendamento, "12:00")  && strcmp(horario_agendamento, "13:00")  && strcmp(horario_agendamento, "14:00")  && strcmp(horario_agendamento, "15:00") && strcmp(horario_agendamento, "16:00") && strcmp(horario_agendamento, "17:00") && strcmp(horario_agendamento, "18:00") != 0);
																	}																
																valid_horario = false;																
																for(c = 0; c <=9; c++){
																	if(strcmp(horario_agendamento,dias_tagua[dia_agendamento].horarios_tagua[c].hr ) == 0){ /*verificando se o horário informado estar disponível e coletando o seu indice*/
																		valid_horario = true;
																		strcpy(dias_tagua[dia_agendamento].horarios_tagua[c].hr, "-----");
																		strcpy(cad_agend_tagua[c_agend_tagua].hora_agend, horario_agendamento);	
																		cad_agend_tagua[c_agend_tagua].pos_hora_agend = c;
																	}
																}											
																	if(valid_horario != true){ /*VAI INFORMAR QUE O HORÁRIO JA ESTAR MARCADO*/
																		do{
																			system("cls");
																			horario_indisponivel();
																			printf("Nome do paciente: %s\n", cad_pas[cpf_pas_encotrado].nome);
																			printf("________________________________________________________________________________\n\n");
																			
																			for(c = 0; c <= 9; c++){
																				printf("| %s ", dias_tagua[dia_agendamento].horarios_tagua[c].hr);												
																			}
																			printf("|\n");
																			printf("________________________________________________________________________________\n\n");																			
																			printf("INFORME OUTRO HORÁRIO: ");
																			scanf("%s", horario_agendamento);
																			fflush(stdin);																			
																				if(strcmp(horario_agendamento, "09:00")  && strcmp(horario_agendamento, "10:00")  && strcmp(horario_agendamento, "11:00")  && strcmp(horario_agendamento, "12:00")  && strcmp(horario_agendamento, "13:00")  && strcmp(horario_agendamento, "14:00")  && strcmp(horario_agendamento, "15:00") && strcmp(horario_agendamento, "16:00") && strcmp(horario_agendamento, "17:00") && strcmp(horario_agendamento, "18:00") != 0){
																					do{
																						system("cls");
																						dados_invalidos();
																						printf("Nome do paciente: %s\n", cad_pas[cpf_pas_encotrado].nome);
																						printf("________________________________________________________________________________\n\n");
																						
																						for(c = 0; c <= 9; c++){
																						printf("| %s ", dias_tagua[dia_agendamento].horarios_tagua[c].hr);												
																						}
																						printf("|\n");
																						printf("________________________________________________________________________________\n\n");
																						printf("DIGITE NOVAMENTE (EX: 15:00): ");
																						scanf("%s", horario_agendamento);
																						fflush(stdin);
																					}while(strcmp(horario_agendamento, "09:00")  && strcmp(horario_agendamento, "10:00")  && strcmp(horario_agendamento, "11:00")  && strcmp(horario_agendamento, "12:00")  && strcmp(horario_agendamento, "13:00")  && strcmp(horario_agendamento, "14:00")  && strcmp(horario_agendamento, "15:00") && strcmp(horario_agendamento, "16:00") && strcmp(horario_agendamento, "17:00") && strcmp(horario_agendamento, "18:00") != 0);
																				}																			
																			valid_horario = false;																			
																				for(c = 0; c <=9; c++){
																					if(strcmp(horario_agendamento,dias_tagua[dia_agendamento].horarios_tagua[c].hr ) == 0){
																						valid_horario = true;
																						strcpy(dias_tagua[dia_agendamento].horarios_tagua[c].hr, "-----");
																						strcpy(cad_agend_tagua[c_agend_tagua].hora_agend, horario_agendamento);	
																					}
																			}																											
																		}while(valid_horario != true);		/*vai se repetir ate o usuário informar um horario válido*/
																	}																																	
																	if(dia_agendamento == dia_atual ){ /*assim que o horário for registrado, aqui vai armazenar o valor da consulta*/
																		fat_dia_tagua += 70.00;
																		fat_total_d += 70.00;
																		ag_dia_tagua +=1;
																	}																	
																fat_mes_tagua += 70.00;
																fat_total += 70.00;
																														
																agora = time(NULL);																
																strftime(cad_agend_tagua[c_agend_tagua].data, sizeof(cad_agend_tagua[c_agend_tagua].data), "%d/%m/%y", localtime(&agora));/*AQUI VAI COLETAR ADATA QUE FOI REALIZADO O AGENDAMENTO*/
																strftime(cad_agend_tagua[c_agend_tagua].hora, sizeof(cad_agend_tagua[c_agend_tagua].hora), "%H:%M:%S", localtime(&agora)); /*AQUI VAI COLETAR O HORARIO QUE FOI REALIZADP P AGENDAMENTO AGENDAMENTO*/
																
																system("cls");
																agend_realizado();
																
																for(c = 0; c <= 9; c++){
																	printf("| %s ", dias_tagua[dia_agendamento].horarios_tagua[c].hr);												
																}
																printf("\n");
																printf("________________________________________________________________________________\n\n"); /*Apresentando os dados informados*/									
																printf("CPF:......................%s\n", cad_agend_tagua[c_agend_tagua].cpf);
																printf("NOME:.....................%s\n", cad_agend_tagua[c_agend_tagua].nome);
																printf("IDADE.....................%d ANOS\n",cad_agend_tagua[c_agend_tagua].idade);	
																	if(cad_agend_guara[c_agend_tagua].sexo == '1'){
																		printf("SEXO:.....................MASCULINO\n");
																	}else{
																		printf("SEXO:.....................FEMININO\n");
																	}
																printf("DATA DO AGENDAMENTO.......%d/%d/%d\n", cad_agend_tagua[c_agend_tagua].dia_ag, cad_agend_tagua[c_agend_tagua].mes_ag, cad_agend_tagua[c_agend_tagua].ano_ag);
																printf("HORÁRIO DO AGENDAMENTO....%s\n", cad_agend_tagua[c_agend_tagua].hora_agend);
																printf("TELEFONE:.................%s\n", cad_pas[cpf_pas_encotrado].telefone);
																printf("________________________________________________________________________________\n");	
																printf("VALOR DA CUNSULTA : R$ 70,00\n\n");
																printf("________________________________________________________________________________\n");										
																printf("                      DATA: %s          HORA: %s\n", cad_agend_tagua[c_agend_tagua].data, cad_agend_tagua[c_agend_tagua].hora);														
																printf("________________________________________________________________________________\n\n\n");																
																system("PAUSE");													
																
																cad_pas[cpf_pas_encotrado].id_agend = c_agend_tagua; /*coletando a posição em que o paciente estar no formulário de agendamento */
																cad_pas[cpf_pas_encotrado].agendamento = true; /*vai servir para registrar q o paciente ja possui agendamento*/
																cad_pas[cpf_pas_encotrado].unidade = 2;  /*servirá como identificador da unidade q o pacienete estar cadastrado*/
																c_agend_tagua ++;
																tot_agend ++;
																op = '4'; 
															break;
															case '3':  /*AQUI COMEÇA O AGENDAMENTO PARA UNIDADE ÁGUAS CLARAS*/															
																strcpy(cad_agend_ac[c_agend_ac].cpf, cad_pas[cpf_pas_encotrado].cpf); /*transferindo os dados do formulário de paciente para o formulário de agendamento*/	
																strcpy(cad_agend_ac[c_agend_ac].nome, cad_pas[cpf_pas_encotrado].nome);
																cad_agend_ac[c_agend_ac].idade = cad_pas[cpf_pas_encotrado].idade;
																cad_agend_ac[c_agend_ac].sexo = cad_pas[cpf_pas_encotrado].sexo;
																
																system("cls");
																agendamento();
																printf("Nome do paciente: %s\n", cad_pas[cpf_pas_encotrado].nome);
																printf("________________________________________________________________________________\n");
																printf("DIA DO AGENDAMENTO: "); /*coletando o dia do agendamento*/
																scanf("%d", &dia_agendamento);																													   																																											
																	if(dia_agendamento < dia_atual || dia_agendamento < 1 || dia_agendamento > 31){ /*validação do dia*/
																		do{																										
																			if(dia_agendamento < 1 || dia_agendamento > 31){
																				system("cls");
																				dia_invalido();
																				printf("Nome do paciente: %s\n", cad_pas[cpf_pas_encotrado].nome);
																				printf("________________________________________________________________________________\n");
																				printf("INFORME OUTRO DIA: ");
																				scanf("%d", &dia_agendamento);		
																			}																																						
																			if(dia_agendamento < dia_atual){
																				system("cls");
																				dia_indisponivel();
																				printf("Nome do paciente: %s\n", cad_pas[cpf_pas_encotrado].nome);
																				printf("________________________________________________________________________________\n");
																				printf("INFORME OUTRO DIA: ");
																				scanf("%d", &dia_agendamento);	
																			}																		
																		}while(dia_agendamento < dia_atual || dia_agendamento > 31);																	
																	}
																
																cad_agend_ac[c_agend_ac].dia_ag = dia_agendamento; /*coletando a data de agendamento */
																cad_agend_ac[c_agend_ac].mes_ag = mes_atual;
																cad_agend_ac[c_agend_ac].ano_ag = ano_atual;																	
																system("cls");
																agendamento();
																printf("Nome do paciente: %s\n", cad_pas[cpf_pas_encotrado].nome);
																printf("________________________________________________________________________________\n\n");																
																for(c = 0; c <= 9; c++){ /*Aapresentando os horários disponíveis para o agendamento*/
																	printf("| %s ", dias_ac[dia_agendamento].horarios_ac[c].hr);												
																}
																printf("\n");
																printf("________________________________________________________________________________\n\n");																
																printf("INFORME O HORÁRIO: ");
																scanf("%s", horario_agendamento);/*coletando o horário*/
																fflush(stdin);
																	/*validando horário*/
																	if(strcmp(horario_agendamento, "09:00")  && strcmp(horario_agendamento, "10:00")  && strcmp(horario_agendamento, "11:00")  && strcmp(horario_agendamento, "12:00")  && strcmp(horario_agendamento, "13:00")  && strcmp(horario_agendamento, "14:00")  && strcmp(horario_agendamento, "15:00") && strcmp(horario_agendamento, "16:00") && strcmp(horario_agendamento, "17:00") && strcmp(horario_agendamento, "18:00") != 0){
																		do{
																			system("cls");
																			dados_invalidos();
																			printf("Nome do paciente: %s\n", cad_pas[cpf_pas_encotrado].nome);
																			printf("________________________________________________________________________________\n\n");
																			
																			for(c = 0; c <= 9; c++){
																				printf("| %s ", dias_ac[dia_agendamento].horarios_ac[c].hr);												
																			}
																			printf("\n");
																			printf("________________________________________________________________________________\n\n");
																			printf("DIGITE NOVAMENTE (EX: 15:00): ");
																			scanf("%s", horario_agendamento);
																			fflush(stdin);
																		}while(strcmp(horario_agendamento, "09:00")  && strcmp(horario_agendamento, "10:00")  && strcmp(horario_agendamento, "11:00")  && strcmp(horario_agendamento, "12:00")  && strcmp(horario_agendamento, "13:00")  && strcmp(horario_agendamento, "14:00")  && strcmp(horario_agendamento, "15:00") && strcmp(horario_agendamento, "16:00") && strcmp(horario_agendamento, "17:00") && strcmp(horario_agendamento, "18:00") != 0);
																	}																
																valid_horario = false;																
																for(c = 0; c <=9; c++){
																	if(strcmp(horario_agendamento,dias_ac[dia_agendamento].horarios_ac[c].hr ) == 0){ /*verificando se o horário informado estar disponível e coletando o seu indice*/
																		valid_horario = true;
																		strcpy(dias_ac[dia_agendamento].horarios_ac[c].hr, "-----");
																		strcpy(cad_agend_ac[c_agend_ac].hora_agend, horario_agendamento);
																		cad_agend_ac[c_agend_ac].pos_hora_agend = c;	
																	}
																}											
																	if(valid_horario != true){ /*VAI INFORMAR QUE O HORÁRIO JA ESTAR MARCADO*/
																		do{
																			system("cls");
																			horario_indisponivel();
																			printf("Nome do paciente: %s\n", cad_pas[cpf_pas_encotrado].nome);
																			printf("________________________________________________________________________________\n\n");																			
																			for(c = 0; c <= 9; c++){
																				printf("| %s ", dias_ac[dia_agendamento].horarios_ac[c].hr);												
																			}
																			printf("|\n");
																			printf("________________________________________________________________________________\n\n");																			
																			printf("INFORME OUTRO HORÁRIO: ");
																			scanf("%s", horario_agendamento);
																			fflush(stdin);																			
																				if(strcmp(horario_agendamento, "09:00")  && strcmp(horario_agendamento, "10:00")  && strcmp(horario_agendamento, "11:00")  && strcmp(horario_agendamento, "12:00")  && strcmp(horario_agendamento, "13:00")  && strcmp(horario_agendamento, "14:00")  && strcmp(horario_agendamento, "15:00") && strcmp(horario_agendamento, "16:00") && strcmp(horario_agendamento, "17:00") && strcmp(horario_agendamento, "18:00") != 0){
																					do{
																						system("cls");
																						dados_invalidos();
																						printf("Nome do paciente: %s\n", cad_pas[cpf_pas_encotrado].nome);
																						printf("________________________________________________________________________________\n\n");
																						
																						for(c = 0; c <= 9; c++){
																						printf("| %s ", dias_ac[dia_agendamento].horarios_ac[c].hr);												
																						}
																						printf("|\n");
																						printf("________________________________________________________________________________\n\n");
																						printf("DIGITE NOVAMENTE (EX: 15:00): ");
																						scanf("%s", horario_agendamento);
																						fflush(stdin);
																					}while(strcmp(horario_agendamento, "09:00")  && strcmp(horario_agendamento, "10:00")  && strcmp(horario_agendamento, "11:00")  && strcmp(horario_agendamento, "12:00")  && strcmp(horario_agendamento, "13:00")  && strcmp(horario_agendamento, "14:00")  && strcmp(horario_agendamento, "15:00") && strcmp(horario_agendamento, "16:00") && strcmp(horario_agendamento, "17:00") && strcmp(horario_agendamento, "18:00") != 0);
																				}																			
																			valid_horario = false;																			
																				for(c = 0; c <=9; c++){
																					if(strcmp(horario_agendamento,dias_ac[dia_agendamento].horarios_ac[c].hr ) == 0){
																						valid_horario = true;
																						strcpy(dias_ac[dia_agendamento].horarios_ac[c].hr, "-----");
																						strcpy(cad_agend_ac[c_agend_ac].hora_agend, horario_agendamento);	
																					}
																			}																											
																		}while(valid_horario != true);	/*vai se repetir ate o usuário informar um horario válido*/
																	}																
																if(dia_agendamento == dia_atual ){ /*assim que o horário for registrado, aqui vai armazenar o valor da consulta*/
																	fat_dia_ac += 70.00;
																	fat_total_d += 70.00;
																	ag_dia_guara +=1;
																}																	
																fat_mes_ac += 70.00;
																fat_total += 70.00;
																																	
																agora = time(NULL);																
																strftime(cad_agend_ac[c_agend_ac].data, sizeof(cad_agend_ac[c_agend_ac].data), "%d/%m/%y", localtime(&agora));/*AQUI VAI COLETAR ADATA QUE FOI REALIZADO O AGENDAMENTO*/
																strftime(cad_agend_ac[c_agend_ac].hora, sizeof(cad_agend_ac[c_agend_ac].hora), "%H:%M:%S", localtime(&agora)); /*AQUI VAI COLETAR O HORARIO QUE FOI REALIZADP P AGENDAMENTO AGENDAMENTO*/																
																system("cls");
																agend_realizado();
																
																for(c = 0; c <= 9; c++){
																	printf("| %s ", dias_ac[dia_agendamento].horarios_ac[c].hr);												
																}
																printf("|\n"); /*Apresentando os dados informados*/
																printf("________________________________________________________________________________\n\n");											
																printf("CPF:......................%s\n", cad_agend_ac[c_agend_ac].cpf);
																printf("NOME:.....................%s\n", cad_agend_ac[c_agend_ac].nome);
																printf("IDADE.....................%d ANOS\n",cad_agend_ac[c_agend_ac].idade);	
																	if(cad_agend_ac[c_agend_ac].sexo == '1'){
																		printf("SEXO:.....................MASCULINO\n");
																	}else{
																		printf("SEXO:.....................FEMININO\n");
																	}
																printf("DATA DO AGENDAMENTO.......%d/%d/%d\n", cad_agend_ac[c_agend_ac].dia_ag, cad_agend_ac[c_agend_ac].mes_ag, cad_agend_ac[c_agend_ac].ano_ag);
																printf("HORÁRIO DO AGENDAMENTO....%s\n", cad_agend_ac[c_agend_ac].hora_agend);
																printf("TELEFONE:.................%s\n", cad_pas[cpf_pas_encotrado].telefone);
																printf("________________________________________________________________________________\n");	
																printf("VALOR DA CUNSULTA : R$ 70,00\n\n");
																printf("________________________________________________________________________________\n");										
																printf("                      DATA: %s          HORA: %s\n", cad_agend_ac[c_agend_ac].data, cad_agend_ac[c_agend_ac].hora);														
																printf("________________________________________________________________________________\n\n\n");																
																system("PAUSE");													
																
																cad_pas[cpf_pas_encotrado].id_agend = c_agend_ac; /*coletando a posição em que o paciente estar no formulário de agendamento */
																cad_pas[cpf_pas_encotrado].agendamento = true; /*vai servir para registrar q o paciente ja possui agendamento*/
																cad_pas[cpf_pas_encotrado].unidade = 3;  /*servirá como identificador da unidade q o pacienete estar cadastrado*/
																c_agend_ac ++;
																tot_agend ++;
																op = '4';																
															break;
														}															
													}while(op != '4');	
												}
											}
											system("cls");
											agendamento();
											op_continuar = le_valida_continuar_agend();
									/*AQUI VAI PERGUNTAR SE DESEJA CONTINUAR*/
									}while(op_continuar != '2');												
								}								
							break;
							
							case '3':/* AQUI COMEÇA A SESSÃO DE CANCELAMENTO DE AGENDAMENTO*/
									if(tot_agend == 0){ /*verificando se existe agendamentos*/
										system("cls");
										sem_agendamento();
									}else{
										do{
											strcpy(cpf_ag,"   ");
											system("cls");
											cancelamento();
											printf("CPF: ");											
											scanf("%s", cpf_ag);
											tam_cpf = strlen(cpf_ag); /*lendo o cpf para procurar o agendamento marcado*/
											fflush(stdin);
											
											soma_cpf = 0;										
											
											for(c = 0; c < 9; c++){ /*validação do cpf*/
												numero_cpf = cpf_ag[c] - 48;
												soma_cpf = soma_cpf + (numero_cpf * (10-c));
											}										
											resultado_cpf = 11 - (soma_cpf%11);										
												if(resultado_cpf == 10 || resultado_cpf == 11){
													digito10 = '0';
												}else{
													digito10 = resultado_cpf + 48;
												}										
											soma_cpf = 0;
											
											for(c = 0; c < 10; c++){
												numero_cpf = cpf_ag[c] - 48;
												soma_cpf = soma_cpf +(numero_cpf * (11-c));
											}										
											resultado_cpf = 11 - (soma_cpf%11);
											
												if(resultado_cpf == 10 || resultado_cpf == 11){
													digito11 = '0';										
												}else{
													digito11 = resultado_cpf + 48;
												}																					
												if(cpf_ag[9] != digito10 || cpf_ag[10] != digito11 || tam_cpf != 11){
													do{
														system("cls");
														cpf_invalido();
														printf("DIGITE NOVAMENTE (ex: 12345678901): ");
														scanf("%s", cpf_ag);
														tam_cpf = strlen(cpf_ag);
														fflush(stdin);																
														soma_cpf = 0;																								
														
														for(c = 0; c < 9; c++){
															numero_cpf = cpf_ag[c] - 48;
															soma_cpf = soma_cpf + (numero_cpf * (10-c));
														}													
														resultado_cpf = 11 - (soma_cpf%11);													
															if(resultado_cpf == 10 || resultado_cpf == 11){
																digito10 = '0';
															}else{
																digito10 = resultado_cpf + 48;
															}													
														soma_cpf = 0;
														
														for(c = 0; c < 10; c++){
															numero_cpf = cpf_ag[c] - 48;
															soma_cpf = soma_cpf +(numero_cpf * (11-c));
														}													
														resultado_cpf = 11 - (soma_cpf%11);													
															if(resultado_cpf == 10 || resultado_cpf == 11){
																digito11 = '0';													
															}else{
																digito11 = resultado_cpf + 48;
															}
													}while(cpf_ag[9] != digito10 || cpf_ag[10] != digito11 || tam_cpf != 11);	
												}																											
											cpf_pas_encotrado = 0;
											cpf_encontrado = false;
											valid_cpf = false;
																						
											for(c = 0; c <= c_pas; c++){ /*AQUI VAI VERIFICAR SE O CPF DO PACIENTE EXISTE*/
												if(strcmp(cpf_ag, cad_pas[c].cpf) == 0){
													cpf_encontrado = true;
													cpf_pas_encotrado = c;							
												}	
											}					
												if(cpf_encontrado != true){ /*SE NÃO EXISTIR O CPF*/
													system("cls");
													cpf_nao_encontrado();	
												}else{
													if(cad_pas[cpf_pas_encotrado].agendamento == false){ /*SE NÃO TIVER AGENDAMENTO*/
														system("cls");
														paciente_nao_possui_agendamento();
													}else{
														switch(cad_pas[cpf_pas_encotrado].unidade){ /*SE TIVER AGENDAMENTO*/
															case 1: /*caso o paciente tiver agendamento na unidade GUARÁ*/
																system("cls");
																cancelamento(); /*Apresentando os dados do agendamento do paciente encontrado*/														
																printf("________________________________________________________________________________\n\n");											
																printf("CPF:......................%s\n", cad_agend_guara[cad_pas[cpf_pas_encotrado].id_agend].cpf);
																printf("NOME:.....................%s\n", cad_agend_guara[cad_pas[cpf_pas_encotrado].id_agend].nome);
																printf("IDADE.....................%d ANOS\n",cad_agend_guara[cad_pas[cpf_pas_encotrado].id_agend].idade);	
																	if(cad_agend_guara[cad_pas[cpf_pas_encotrado].id_agend].sexo == '1'){
																		printf("SEXO:.....................MASCULINO\n");
																	}else{
																		printf("SEXO:.....................FEMININO\n");
																	}
																printf("DATA DO AGENDAMENTO.......%d/%d/%d\n", cad_agend_guara[cad_pas[cpf_pas_encotrado].id_agend].dia_ag, cad_agend_guara[cad_pas[cpf_pas_encotrado].id_agend].mes_ag, cad_agend_guara[cad_pas[cpf_pas_encotrado].id_agend].ano_ag);
																printf("HORÁRIO DO AGENDAMENTO....%s\n", cad_agend_guara[cad_pas[cpf_pas_encotrado].id_agend].hora_agend);
																printf("TELEFONE:.................%s\n\n", cad_pas[cpf_pas_encotrado].telefone);	
																
																op_excluir = le_valida_op_excluir(); /*perguntando se realmente deseja excluir*/
																	if(op_excluir == '1'){																		
																		switch (cad_agend_guara[cad_pas[cpf_pas_encotrado].id_agend].pos_hora_agend){ /*Devolvendo o horário pro dia que estava agendado*/
																			case 0:
																				strcpy(dias_guara[cad_agend_guara[cad_pas[cpf_pas_encotrado].id_agend].dia_ag].horarios_guara[0].hr, "09:00" );
																			break;
																			
																			case 1:
																				strcpy(dias_guara[cad_agend_guara[cad_pas[cpf_pas_encotrado].id_agend].dia_ag].horarios_guara[1].hr, "10:00");
																			break;
																			
																			case 2:
																				strcpy(dias_guara[cad_agend_guara[cad_pas[cpf_pas_encotrado].id_agend].dia_ag].horarios_guara[2].hr, "11:00");
																			break;
																			
																			case 3:
																				strcpy(dias_guara[cad_agend_guara[cad_pas[cpf_pas_encotrado].id_agend].dia_ag].horarios_guara[3].hr, "12:00");
																			break;
																			
																			case 4:
																				strcpy(dias_guara[cad_agend_guara[cad_pas[cpf_pas_encotrado].id_agend].dia_ag].horarios_guara[4].hr, "13:00");
																			break;
																			
																			case 5:
																				strcpy(dias_guara[cad_agend_guara[cad_pas[cpf_pas_encotrado].id_agend].dia_ag].horarios_guara[5].hr, "14:00");
																			break;
																			
																			case 6:
																				strcpy(dias_guara[cad_agend_guara[cad_pas[cpf_pas_encotrado].id_agend].dia_ag].horarios_guara[6].hr, "15:00");
																			break;
																			
																			case 7:
																				strcpy(dias_guara[cad_agend_guara[cad_pas[cpf_pas_encotrado].id_agend].dia_ag].horarios_guara[7].hr, "16:00");
																			break;
																			
																			case 8:
																				strcpy(dias_guara[cad_agend_guara[cad_pas[cpf_pas_encotrado].id_agend].dia_ag].horarios_guara[8].hr, "17:00");
																			break;
																			
																			case 9:
																				strcpy(dias_guara[cad_agend_guara[cad_pas[cpf_pas_encotrado].id_agend].dia_ag].horarios_guara[9].hr, "18:00");
																			break;
																		}		
																																			
																		if(fat_dia_guara != 0){ /*Como o agendamento foi exluido, aqui vai subtrair o faturamento diário, mensal e qtd de agendamentos*/
																			if(cad_agend_guara[cad_pas[cpf_pas_encotrado].id_agend].dia_ag == dia_atual ){
																				fat_dia_guara -= 70.00;
																				fat_total_d -= 70.00;
																				ag_dia_guara -=1;
																			}			
																		}	
																		if(fat_mes_guara != 0){
																			fat_mes_guara -= 70.00;	
																		}															
																		if(fat_total != 0){
																			fat_total -= 70.00;		
																		}			
																		/*Apagando os dados do formulário*/
																		memset(&cad_agend_guara[cad_pas[cpf_pas_encotrado].id_agend], 0,sizeof cad_agend_guara[cad_pas[cpf_pas_encotrado].id_agend]);																		
																	
																		j = cpf_pas_encotrado;
																		for(c = cad_pas[cpf_pas_encotrado].id_agend; c < c_agend_guara; c++){ /*realocando a posição do formulário de agendamento*/
																			cad_agend_guara[c] = cad_agend_guara[c + 1];
																				if(cad_pas[j].unidade == 1){
																					cad_pas[j].id_agend -= 1;	
																				}
																				j += 1;													
																		}																		
																		c_agend_guara -= 1;
																		tot_agend -= 1;	
															
																	memset(&cad_pas[cpf_pas_encotrado].unidade, 0,sizeof cad_pas[cpf_pas_encotrado].unidade); /*formatando os dados do paciente que teve seu agendamento cancelado*/
																	memset(&cad_pas[cpf_pas_encotrado].id_agend, 0, sizeof cad_pas[cpf_pas_encotrado].id_agend);
																	cad_pas[cpf_pas_encotrado].agendamento = false;																						
																	}	
															break;														
															case 2:  /*caso o paciente tiver agendamento na unidade TAGUATINGA*/
																system("cls");
																cancelamento();
																/*Apresentando os dados do agendamento do paciente encontrado*/
																printf("CPF:......................%s\n", cad_agend_tagua[cad_pas[cpf_pas_encotrado].id_agend].cpf);
																printf("NOME:.....................%s\n", cad_agend_tagua[cad_pas[cpf_pas_encotrado].id_agend].nome);
																printf("IDADE.....................%d ANOS\n",cad_agend_tagua[cad_pas[cpf_pas_encotrado].id_agend].idade);	
																	if(cad_agend_tagua[cad_pas[cpf_pas_encotrado].id_agend].sexo == '1'){
																		printf("SEXO:.....................MASCULINO\n");
																	}else{
																		printf("SEXO:.....................FEMININO\n");
																	}
																printf("DATA DO AGENDAMENTO.......%d/%d/%d\n", cad_agend_tagua[cad_pas[cpf_pas_encotrado].id_agend].dia_ag, cad_agend_tagua[cad_pas[cpf_pas_encotrado].id_agend].mes_ag, cad_agend_tagua[cad_pas[cpf_pas_encotrado].id_agend].ano_ag);
																printf("HORÁRIO DO AGENDAMENTO....%s\n", cad_agend_tagua[cad_pas[cpf_pas_encotrado].id_agend].hora_agend);
																printf("TELEFONE:.................%s\n\n", cad_pas[cpf_pas_encotrado].telefone);
															
															op_excluir = le_valida_op_excluir();  /*perguntando se realmente deseja excluir*/
																	if(op_excluir == '1'){																		
																		switch (cad_agend_tagua[cad_pas[cpf_pas_encotrado].id_agend].pos_hora_agend){  /*Devolvendo o horário pro dia que estava agendado*/
																			case 0:
																				strcpy(dias_tagua[cad_agend_tagua[cad_pas[cpf_pas_encotrado].id_agend].dia_ag].horarios_tagua[0].hr, "09:00");
																			break;
																			
																			case 1:
																				strcpy(dias_tagua[cad_agend_tagua[cad_pas[cpf_pas_encotrado].id_agend].dia_ag].horarios_tagua[1].hr, "10:00");
																			break;
																			
																			case 2:
																				strcpy(dias_tagua[cad_agend_tagua[cad_pas[cpf_pas_encotrado].id_agend].dia_ag].horarios_tagua[2].hr, "11:00");
																			break;
																			
																			case 3:
																				strcpy(dias_tagua[cad_agend_tagua[cad_pas[cpf_pas_encotrado].id_agend].dia_ag].horarios_tagua[3].hr, "12:00");
																			break;
																			
																			case 4:
																				strcpy(dias_tagua[cad_agend_tagua[cad_pas[cpf_pas_encotrado].id_agend].dia_ag].horarios_tagua[4].hr, "13:00");
																			break;
																			
																			case 5:
																				strcpy(dias_tagua[cad_agend_tagua[cad_pas[cpf_pas_encotrado].id_agend].dia_ag].horarios_tagua[5].hr, "14:00");
																			break;
																			
																			case 6:
																				strcpy(dias_tagua[cad_agend_tagua[cad_pas[cpf_pas_encotrado].id_agend].dia_ag].horarios_tagua[6].hr, "15:00");
																			break;
																			
																			case 7:
																				strcpy(dias_tagua[cad_agend_tagua[cad_pas[cpf_pas_encotrado].id_agend].dia_ag].horarios_tagua[7].hr, "16:00");
																			break;
																			
																			case 8:
																				strcpy(dias_tagua[cad_agend_tagua[cad_pas[cpf_pas_encotrado].id_agend].dia_ag].horarios_tagua[8].hr, "17:00");
																			break;
																			
																			case 9:
																				strcpy(dias_tagua[cad_agend_tagua[cad_pas[cpf_pas_encotrado].id_agend].dia_ag].horarios_tagua[9].hr, "18:00");
																			break;
																		}																				
																		if(fat_dia_tagua != 0){ /*Como o agendamento foi exluido, aqui vai subtrair o faturamento diário, mensal e qtd de agendamentos*/
																			if(cad_agend_tagua[cad_pas[cpf_pas_encotrado].id_agend].dia_ag == dia_atual ){
																				fat_dia_tagua -= 70.00;
																				fat_total_d -= 70.00;
																				ag_dia_tagua -=1;
																			}			
																		}																		
																		if(fat_mes_tagua != 0){
																			fat_mes_tagua -= 70.00;	
																		}																																	
																		if(fat_total != 0){
																			fat_total -= 70.00;		
																		}
																		/*Apagando os dados do formulário*/
																		memset(&cad_agend_tagua[cad_pas[cpf_pas_encotrado].id_agend], 0,sizeof cad_agend_tagua[cad_pas[cpf_pas_encotrado].id_agend]);
																																				
																		j = cpf_pas_encotrado;
																		for(c = cad_pas[cpf_pas_encotrado].id_agend; c < c_agend_tagua; c++){ /*realocando a posição do formulário de agendamento*/
																			cad_agend_tagua[c] = cad_agend_tagua[c + 1];
																				if(cad_pas[j].unidade == 2){
																					cad_pas[j].id_agend -= 1;	
																				}
																				j += 1;													
																		}																																			
																		c_agend_tagua -= 1;
																		tot_agend -= 1;					
																	
																	memset(&cad_pas[cpf_pas_encotrado].unidade, 0,sizeof cad_pas[cpf_pas_encotrado].unidade); /*formatando os dados do paciente que teve seu agendamento cancelado*/
																	memset(&cad_pas[cpf_pas_encotrado].id_agend, 0, sizeof cad_pas[cpf_pas_encotrado].id_agend);						
																	cad_pas[cpf_pas_encotrado].agendamento = false;					
																	}																
															break;
															
															case 3:  /*caso o paciente tiver agendamento na unidade TAGUATINGA*/
																system("cls");
																cancelamento();
																	/*Apresentando os dados do agendamento do paciente encontrado*/
																printf("CPF:......................%s\n", cad_agend_ac[cad_pas[cpf_pas_encotrado].id_agend].cpf);
																printf("NOME:.....................%s\n", cad_agend_ac[cad_pas[cpf_pas_encotrado].id_agend].nome);
																printf("IDADE.....................%d ANOS\n",cad_agend_ac[cad_pas[cpf_pas_encotrado].id_agend].idade);	
																	if(cad_agend_ac[cad_pas[cpf_pas_encotrado].id_agend].sexo == '1'){
																		printf("SEXO:.....................MASCULINO\n");
																	}else{
																		printf("SEXO:.....................FEMININO\n");
																	}
																printf("DATA DO AGENDAMENTO.......%d/%d/%d\n", cad_agend_ac[cad_pas[cpf_pas_encotrado].id_agend].dia_ag, cad_agend_ac[cad_pas[cpf_pas_encotrado].id_agend].mes_ag, cad_agend_ac[cad_pas[cpf_pas_encotrado].id_agend].ano_ag);
																printf("HORÁRIO DO AGENDAMENTO....%s\n", cad_agend_ac[cad_pas[cpf_pas_encotrado].id_agend].hora_agend);
																printf("TELEFONE:.................%s\n\n", cad_pas[cpf_pas_encotrado].telefone);
																
																op_excluir = le_valida_op_excluir();  /*perguntando se realmente deseja excluir*/
																	if(op_excluir == '1'){							
																		switch (cad_agend_ac[cad_pas[cpf_pas_encotrado].id_agend].pos_hora_agend){  /*Devolvendo o horário pro dia que estava agendado*/
																			case 0:
																				strcpy(dias_ac[cad_agend_ac[cad_pas[cpf_pas_encotrado].id_agend].dia_ag].horarios_ac[0].hr, "09:00");
																			break;
																			
																			case 1:
																				strcpy(dias_ac[cad_agend_ac[cad_pas[cpf_pas_encotrado].id_agend].dia_ag].horarios_ac[1].hr, "10:00");
																			break;
																			
																			case 2:
																				strcpy(dias_ac[cad_agend_ac[cad_pas[cpf_pas_encotrado].id_agend].dia_ag].horarios_ac[2].hr, "11:00");
																			break;
																			
																			case 3:
																				strcpy(dias_ac[cad_agend_ac[cad_pas[cpf_pas_encotrado].id_agend].dia_ag].horarios_ac[3].hr, "12:00");
																			break;
																			
																			case 4:
																				strcpy(dias_ac[cad_agend_ac[cad_pas[cpf_pas_encotrado].id_agend].dia_ag].horarios_ac[4].hr, "13:00");
																			break;
																			
																			case 5:
																				strcpy(dias_ac[cad_agend_ac[cad_pas[cpf_pas_encotrado].id_agend].dia_ag].horarios_ac[5].hr, "14:00");
																			break;
																			
																			case 6:
																				strcpy(dias_ac[cad_agend_ac[cad_pas[cpf_pas_encotrado].id_agend].dia_ag].horarios_ac[6].hr, "15:00");
																			break;
																			
																			case 7:
																				strcpy(dias_ac[cad_agend_ac[cad_pas[cpf_pas_encotrado].id_agend].dia_ag].horarios_ac[7].hr, "16:00");
																			break;
																			
																			case 8:
																				strcpy(dias_ac[cad_agend_ac[cad_pas[cpf_pas_encotrado].id_agend].dia_ag].horarios_ac[8].hr, "17:00");
																			break;
																			
																			case 9:
																				strcpy(dias_ac[cad_agend_ac[cad_pas[cpf_pas_encotrado].id_agend].dia_ag].horarios_ac[9].hr, "18:00");
																			break;
																		}		
																		if(fat_dia_ac != 0){ /*Como o agendamento foi exluido, aqui vai subtrair o faturamento diário, mensal e qtd de agendamentos*/
																			if(cad_agend_ac[cad_pas[cpf_pas_encotrado].id_agend].dia_ag == dia_atual ){
																				fat_dia_ac -= 70.00;
																				fat_total_d -= 70.00;
																				ag_dia_ac -=1;
																			}			
																		}	
																		if(fat_mes_ac != 0){
																			fat_mes_ac -= 70.00;	
																		}																																	
																		if(fat_total != 0){
																			fat_total -= 70.00;		
																		}	
																			/*Apagando os dados do formulário*/
																		memset(&cad_agend_ac[cad_pas[cpf_pas_encotrado].id_agend], 0,sizeof cad_agend_ac[cad_pas[cpf_pas_encotrado].id_agend]);
																		
																		j = cpf_pas_encotrado;  /*realocando a posição do formulário de agendamento*/
																		for(c = cad_pas[cpf_pas_encotrado].id_agend; c < c_agend_ac; c++){
																			cad_agend_ac[c] = cad_agend_ac[c + 1];
																				if(cad_pas[j].unidade == 1){
																					cad_pas[j].id_agend -= 1;	
																				}
																				j += 1;													
																		}																																				
																		c_agend_ac -= 1;
																		tot_agend -= 1;					
																	
																	memset(&cad_pas[cpf_pas_encotrado].unidade, 0,sizeof cad_pas[cpf_pas_encotrado].unidade); /*formatando os dados do paciente que teve seu agendamento cancelado*/
																	memset(&cad_pas[cpf_pas_encotrado].id_agend, 0, sizeof cad_pas[cpf_pas_encotrado].id_agend);
																	cad_pas[cpf_pas_encotrado].agendamento = false;							
																	}							
															break;
														}	
													}	
												}																	
											system("cls");
											cancelamento();
											op_continuar = le_valida_continuar_cancelamento_agend(); /*Pergunta se deseja cancelar outro agendamento*/
										}while(op_continuar != '2');								
									}									
							break;
							
							case '4':/*AQUI COMEÇA A SESSÃO DE RELATÓRIOS*/
								do{
									op_continuar = 0;
									system("cls");
									relatorios();
									op_continuar = le_valida_op_relatorio();
									switch(op_continuar){
										case '1': /*RELATÓRIO CADASTRO*/
											do{
												op_sair = 0;
												system("cls");
												relatorio_cadastro();
												op_sair = le_valida_relatorio_cad();
												switch(op_sair){
													case '1': /*RELATÓRIO DE CADASTRO DE FUNCIONÁRIOS*/
														do{
															system("cls");
															funcionario_cadastro();
															op_continuar = le_valida_op_relatorio_cad_fun();
															switch(op_continuar){
																case '1': /*FILTRAR CADASTRO DE FUNCIONÁRIOS*/
																	do{
																		system("cls");
																		funcionario_cadastro();		
																		printf("CPF: ");
																		scanf("%s", cpf_fun);
																		tam_cpf = strlen(cpf_fun);
																		fflush(stdin);
																		soma_cpf = 0;										
										
																		for(c = 0; c < 9; c++){ /*AQUI VAI COMEÇAR A VALIDAÇÃO*/
																			numero_cpf = cpf_fun[c] - 48; /*analizando o digito 10*/
																			soma_cpf = soma_cpf + (numero_cpf * (10-c));
																		}										
																		resultado_cpf = 11 - (soma_cpf%11);										
																			if(resultado_cpf == 10 || resultado_cpf == 11){/*verificando se o digito 10 é igual a 11 ou 10*/
																				digito10 = '0';
																			}else{
																				digito10 = resultado_cpf + 48;
																			}										
																		soma_cpf = 0;
																		
																		for(c = 0; c < 10; c++){ /*analizando o digito 11*/
																			numero_cpf = cpf_fun[c] - 48;
																			soma_cpf = soma_cpf +(numero_cpf * (11-c));
																		}
																		
																		resultado_cpf = 11 - (soma_cpf%11);
																		
																			if(resultado_cpf == 10 || resultado_cpf == 11){ /*verificando se o digito 11 é igual a 11 ou 10*/
																				digito11 = '0';										
																			}else{
																				digito11 = resultado_cpf + 48;
																			}																					
																			if(cpf_fun[9] != digito10 || cpf_fun[10] != digito11 || tam_cpf != 11){ /*se qual quer um dos dois forem diferentes*/
																				do{
																					system("cls");
																					cpf_invalido();
																					printf("DIGITE NOVAMENTE (ex: 12345678901): ");
																					fflush(stdin);
																					gets(cpf_fun);
																					tam_cpf = strlen(cpf_fun);			
																					
																					soma_cpf = 0;																								
																					for(c = 0; c < 9; c++){
																						numero_cpf = cpf_fun[c] - 48;
																						soma_cpf = soma_cpf + (numero_cpf * (10-c));
																					}
																					
																					resultado_cpf = 11 - (soma_cpf%11);													
																						if(resultado_cpf == 10 || resultado_cpf == 11){
																							digito10 = '0';
																						}else{
																							digito10 = resultado_cpf + 48;
																						}													
																					soma_cpf = 0;
																					
																					for(c = 0; c < 10; c++){
																						numero_cpf = cpf_fun[c] - 48;
																						soma_cpf = soma_cpf +(numero_cpf * (11-c));
																					}													
																					resultado_cpf = 11 - (soma_cpf%11);													
																						if(resultado_cpf == 10 || resultado_cpf == 11){
																							digito11 = '0';													
																						}else{
																							digito11 = resultado_cpf + 48;
																						}
																				}while(cpf_fun[9] != digito10 || cpf_fun[10] != digito11 || tam_cpf != 11);	
																			}
																			
																			valid_cpf = false;
																			cpf_pas_encotrado = 0;
																			for(c = 0; c < c_func; c++){ /*Verificando se o cpf existe no formulário*/
																				if(strcmp(cad_fun[c].cpf, cpf_fun) == 0){
																					cpf_pas_encotrado = c;
																					valid_cpf = true;
																				}
																			}																			
																			if(valid_cpf != true){ /*SE NÃO EXISTIR*/
																				system("cls");
																				funcionario_nao_encontrado();
																			}else{
																				agora = time(NULL);	/*SE EXISTEIR*/															
																				strftime(data, sizeof(data), "%d/%m/%y", localtime(&agora));/*AQUI VAI COLETAR A DATA E HORA ATUAL*/
																				strftime(hora, sizeof(hora), "%H:%M:%S", localtime(&agora));
																				
																				system("cls");
																				funcionario_cadastro();	/*Apresentando os dados digitados do paciente*/
																				printf("                  DATA: %s        HORA: %s\n\n", data, hora);
																				printf("================================================================================\n");
																				printf("CPF: ...................%s\n", cad_fun[cpf_pas_encotrado].cpf);
																				printf("NOME: ..................%s\n", cad_fun[cpf_pas_encotrado].nome_fun);
																				if(cad_fun[cpf_pas_encotrado].sexo == '1'){
																						printf("SEXO: ..................MASCULINO\n");
																					}else{
																						printf("SEXO: ..................FEMININO\n");
																					}																			
																				printf("DATA DE NASCIMENTO......%d/%d/%d\n", cad_fun[cpf_pas_encotrado].dia, cad_fun[cpf_pas_encotrado].mes, cad_fun[cpf_pas_encotrado].ano);
																				printf("IDADE...................%d ANOS\n", cad_fun[cpf_pas_encotrado].idade);
																				printf("CARGO:..................%s\n\n", cad_fun[cpf_pas_encotrado].cargo);	
																				printf("================================================================================\n\n\n");
																				system("PAUSE");
																			}
																		system("cls");
																		funcionario_cadastro();																														
																		op = le_valida_continuar_filtragem(); /*perguntaa se deseja continuar a filtragem*/
																	}while( op != '2');
																break;
																
																case '2': /*TODOS OS CADASTROS DE FUNCIONÁRIOS*/
																	agora = time(NULL);																
																	strftime(data, sizeof(data), "%d/%m/%y", localtime(&agora));/*AQUI VAI COLETAR A DATA E HORA ATUAL*/
																	strftime(hora, sizeof(hora), "%H:%M:%S", localtime(&agora));															
																	system("cls");
																	funcionario_cadastro();	/*Apresentando os dados digitados pelo funcionário, porém, de todos*/
																	printf("                  DATA: %s        HORA: %s\n\n", data, hora);
																	for(c = 0; c < c_func;c++){											
																		printf("================================================================================\n");
																		printf("                              %dº FUNCIONÁRIO\n\n\n", c + 1);
																		printf("CPF: ...................%s\n", cad_fun[c].cpf);
																		printf("NOME: ..................%s\n", cad_fun[c].nome_fun);
																		if(cad_fun[c].sexo == '1'){
																				printf("SEXO: ..................MASCULINO\n");
																			}else{
																				printf("SEXO: ..................FEMININO\n");
																			}																			
																		printf("DATA DE NASCIMENTO......%d/%d/%d\n", cad_fun[c].dia, cad_fun[c].mes, cad_fun[c].ano);
																		printf("IDADE...................%d ANOS\n", cad_fun[c].idade);
																		printf("CARGO:..................%s\n\n", cad_fun[c].cargo);
																	}
																	printf("================================================================================\n\n");																	
																	printf("QUANTIDADE DE FUNCIONÁRIOS CADASTRADOS....... %d\n\n", c_func); /*apresentando a quantidade de cadastros totais, de homens e de mulheres*/
																	printf("HOMENS........................................%d\n\n", qtd_homem_fun);
																	printf("MULHERES......................................%d\n\n\n", qtd_mulher_fun);									
																	system("PAUSE");
																break;
															}															
														}while(op_continuar != '3');
													break;
													
													case '2':/* RELATÓRIO DE CADASTRO DE PACIENTES*/
														if(c_pas == 0){/*verificando se existe pacientes cadastrados*/
															system("cls");
															sistema_sem_paciente();
														}else{
															do{ /*se existir pacientes cadastrados*/
																system("cls");
																paciente_cadastro();
																op_continuar = le_valida_op_relatorio_cad_fun();
																switch(op_continuar){
																	case '1': /*FILTRAR CADASTROS DE PACIENTES*/
																		do{																		
																			system("cls");	/*AQUI VAI LER O CPF DO PACIENTE,  que servirá como identificador*/
																			paciente_cadastro();
																			printf("CPF:  ");
																			scanf("%s", cpf_pas); 
																			tam_cpf = strlen(cpf_pas);
																			fflush(stdin);
																			soma_cpf = 0;										
															
																			for(c = 0; c < 9; c++){
																				numero_cpf = cpf_pas[c] - 48;
																				soma_cpf = soma_cpf + (numero_cpf * (10-c));
																			}										
																			resultado_cpf = 11 - (soma_cpf%11);										
																				if(resultado_cpf == 10 || resultado_cpf == 11){
																					digito10 = '0';
																				}else{
																					digito10 = resultado_cpf + 48;
																				}										
																			soma_cpf = 0;
																			
																			for(c = 0; c < 10; c++){
																				numero_cpf = cpf_pas[c] - 48;
																				soma_cpf = soma_cpf +(numero_cpf * (11-c));
																			}
																			
																			resultado_cpf = 11 - (soma_cpf%11);
																			
																				if(resultado_cpf == 10 || resultado_cpf == 11){
																					digito11 = '0';										
																				}else{
																					digito11 = resultado_cpf + 48;
																				}																					
																				if(cpf_pas[9] != digito10 || cpf_pas[10] != digito11 || tam_cpf != 11){
																					do{
																						system("cls");
																						cpf_invalido();
																						printf("DIGITE NOVAMENTE (ex: 12345678901): ");
																						printf("CPF:  ");
																						scanf("%s", cpf_pas); 
																						tam_cpf = strlen(cpf_pas);			
																						fflush(stdin);
																						soma_cpf = 0;																								
																						for(c = 0; c < 9; c++){
																							numero_cpf = cpf_pas[c] - 48;
																							soma_cpf = soma_cpf + (numero_cpf * (10-c));
																						}
																						
																						resultado_cpf = 11 - (soma_cpf%11);													
																							if(resultado_cpf == 10 || resultado_cpf == 11){
																								digito10 = '0';
																							}else{
																								digito10 = resultado_cpf + 48;
																							}													
																						soma_cpf = 0;
																						
																						for(c = 0; c < 10; c++){
																							numero_cpf = cpf_pas[c] - 48;
																							soma_cpf = soma_cpf +(numero_cpf * (11-c));
																						}													
																						resultado_cpf = 11 - (soma_cpf%11);													
																							if(resultado_cpf == 10 || resultado_cpf == 11){
																								digito11 = '0';													
																							}else{
																								digito11 = resultado_cpf + 48;
																							}
																					}while(cpf_pas[9] != digito10 || cpf_pas[10] != digito11 || tam_cpf != 11);	
																				}																		
																															
																				valid_cpf = false;
																				cpf_pas_encotrado = 0;
																				for(c = 0; c < c_pas; c++){ /*Verificando se o cpf do paciente existe no formulário*/
																					if(strcmp(cad_pas[c].cpf, cpf_pas) == 0){
																						cpf_pas_encotrado = c;
																						valid_cpf = true;
																					}
																				}																				
																				if(valid_cpf != true){ /*SE NÃO EXISTIR*/
																					system("cls");
																					paciente_nao_encontrado();
																				}else{ /*se existir*/
																					agora = time(NULL);																
																					strftime(data, sizeof(data), "%d/%m/%y", localtime(&agora));/*AQUI VAI COLETAR A DATA E HORA ATUAL*/
																					strftime(hora, sizeof(hora), "%H:%M:%S", localtime(&agora));																					
																					system("cls");
																					paciente_cadastro(); /*Apresentando os dados digitados do paciente*/	
																					printf("                  DATA: %s        HORA: %s\n\n", data, hora);
																					printf("================================================================================\n");																					
																					printf("CPF: ...................%s\n", cad_pas[cpf_pas_encotrado].cpf);
																					printf("NOME: ..................%s\n", cad_pas[cpf_pas_encotrado].nome);
																						if(cad_pas[cpf_pas_encotrado].sexo == '1'){
																							printf("SEXO: ..................MASCULINO\n");
																						}else{
																							printf("SEXO: ..................FEMININO\n");
																						}
																					printf("DATA DE NASCIMENTO......%d/%d/%d\n", cad_pas[cpf_pas_encotrado].dia, cad_pas[cpf_pas_encotrado].mes, cad_pas[cpf_pas_encotrado].ano);
																					printf("IDADE...................%d ANOS\n", cad_pas[cpf_pas_encotrado].idade);
																					printf("TELEFONE:...............%s\n\n", cad_pas[cpf_pas_encotrado].telefone);		
																					printf("================================================================================\n\n\n");
																					system("PAUSE");
																				}
																				system("cls");
																				paciente_cadastro();																														
																				op = le_valida_continuar_filtragem(); /*vai perguntar se deseja realizar outra filtragem*/
																		}while(op != '2');
																	break;
																	
																	case '2': /*TODOS OS PACIENTES CADASTRADOS*/
																		agora = time(NULL);																
																		strftime(data, sizeof(data), "%d/%m/%y", localtime(&agora));/*AQUI VAI COLETAR A DATA E HORA ATUAL*/
																		strftime(hora, sizeof(hora), "%H:%M:%S", localtime(&agora));																		
																		system("cls");
																		paciente_cadastro(); /*Apresentando os dados digitados do paciente, porém, de todos*/
																		printf("                  DATA: %s        HORA: %s\n\n", data, hora);
																		for(c = 0; c < c_pas; c ++){
																				printf("================================================================================\n");
																				printf("                              %dº PACIENTE\n\n\n", c + 1);
																				printf("CPF: ...................%s\n", cad_pas[c].cpf);
																				printf("NOME: ..................%s\n", cad_pas[c].nome);
																					if(cad_pas[c].sexo == '1'){
																						printf("SEXO: ..................MASCULINO\n");
																					}else{
																						printf("SEXO: ..................FEMININO\n");
																					}
																				printf("DATA DE NASCIMENTO......%d/%d/%d\n", cad_pas[c].dia, cad_pas[c].mes, cad_pas[c].ano);
																				printf("IDADE...................%d ANOS\n", cad_pas[cpf_pas_encotrado].idade);
																				printf("TELEFONE:...............%s\n\n", cad_pas[cpf_pas_encotrado].telefone);		
																		}
																		printf("================================================================================\n\n");																		
																		printf("QUANTIDADE DE PACIENTES CADASTRADOS...........%d\n\n", c_pas); /*apresentando a quantidade de cadastros totais, de homens e de mulheres*/
																		printf("HOMENS........................................%d\n\n", qtd_homem_pas);
																		printf("MULHERES......................................%d\n\n\n", qtd_mulher_pas);									
																		system("PAUSE");																	
																	break;
																}
															}while(op_continuar != '3');
														}
													break;
													
													case '3':/*RELATÓRIO DE CADASTRO DO MÉDICO*/
														if(c_med == 0){ /*verificanso se existe médicos cadastrados*/
															system("cls");
															sistema_sem_medico();
														}else{
															do{ /*se existir médicos cadastrados*/
																system("cls");
																medico_cadastro();
																op_continuar = le_valida_op_relatorio_cad_fun();
																switch(op_continuar){
																	case '1':/*FILTRAR MÉDICO CADASTRADO*/
																		do{
																			system("cls");
																			medico_cadastro();
																			printf("CPF: ");
																			scanf("%s", cpf_med);
																			tam_cpf = strlen(cpf_med); /*lendo o cpf para verificação*/
																			fflush(stdin);

																			soma_cpf = 0;										
																			
																			for(c = 0; c < 9; c++){ /*validação do cpf*/
																				numero_cpf = cpf_med[c] - 48;
																				soma_cpf = soma_cpf + (numero_cpf * (10-c));
																			}										
																			resultado_cpf = 11 - (soma_cpf%11);										
																				if(resultado_cpf == 10 || resultado_cpf == 11){
																					digito10 = '0';
																				}else{
																					digito10 = resultado_cpf + 48;
																				}										
																			soma_cpf = 0;
																			
																			for(c = 0; c < 10; c++){
																				numero_cpf = cpf_med[c] - 48;
																				soma_cpf = soma_cpf +(numero_cpf * (11-c));
																			}														
																			resultado_cpf = 11 - (soma_cpf%11);														
																				if(resultado_cpf == 10 || resultado_cpf == 11){
																					digito11 = '0';										
																				}else{
																					digito11 = resultado_cpf + 48;
																				}																					
																				if(cpf_med[9] != digito10 || cpf_med[10] != digito11 || tam_cpf != 11){
																					do{
																						system("cls");
																						cpf_invalido();
																						printf("DIGITE NOVAMENTE (ex: 12345678901): ");
																						scanf("%s", cpf_med); 
																						tam_cpf = strlen(cpf_med);											
																						fflush(stdin);																				
																						soma_cpf = 0;																								
																						
																						for(c = 0; c < 9; c++){
																							numero_cpf = cpf_med[c] - 48;
																							soma_cpf = soma_cpf + (numero_cpf * (10-c));
																						}																	
																						resultado_cpf = 11 - (soma_cpf%11);													
																							if(resultado_cpf == 10 || resultado_cpf == 11){
																								digito10 = '0';
																							}else{
																								digito10 = resultado_cpf + 48;
																							}													
																						soma_cpf = 0;
																						
																						for(c = 0; c < 10; c++){
																							numero_cpf = cpf_med[c] - 48;
																							soma_cpf = soma_cpf +(numero_cpf * (11-c));
																						}													
																						resultado_cpf = 11 - (soma_cpf%11);													
																							if(resultado_cpf == 10 || resultado_cpf == 11){
																								digito11 = '0';													
																							}else{
																								digito11 = resultado_cpf + 48;
																							}
																					}while(cpf_med[9] != digito10 || cpf_med[10] != digito11 || tam_cpf != 11);	
																				}

																			valid_cpf = false;
																			cpf_pas_encotrado = 0; /*Verificando se o cpf existe no formulário*/
																			for(c = 0; c < c_med; c++){
																				if(strcmp(cad_med[c].cpf, cpf_med) == 0){
																					cpf_pas_encotrado = c;
																					valid_cpf = true;
																				}
																			}																			
																			if(valid_cpf != true){ /*se não existir*/
																				system("cls");
																				medico_nao_encontrado();
																			}else{ /*se existir*/																
																				agora = time(NULL);																
																				strftime(data, sizeof(data), "%d/%m/%y", localtime(&agora));/*AQUI VAI COLETAR A  DATA E HORA ATUAL*/
																				strftime(hora, sizeof(hora), "%H:%M:%S", localtime(&agora));																				
																				system("cls");
																				medico_cadastro(); /*apresentando os dados digitados do médico*/
																				printf("                  DATA: %s        HORA: %s\n\n", data, hora);
																				printf("================================================================================\n");
																				printf("CPF: ...................%s\n", cad_med[cpf_pas_encotrado].cpf);
																				printf("NOME: ..................%s\n", cad_med[cpf_pas_encotrado].nome);
																					if(cad_med[cpf_pas_encotrado].sexo == '1'){
																						printf("SEXO: ..................MASCULINO\n");
																					}else{
																						printf("SEXO: ..................FEMININO\n");
																					}
																				printf("DATA DE NASCIMENTO......%d/%d/%d\n", cad_med[cpf_pas_encotrado].dia, cad_med[cpf_pas_encotrado].mes, cad_med[cpf_pas_encotrado].ano);
																				printf("IDADE...................%d ANOS\n", cad_med[cpf_pas_encotrado].idade);
																				printf("CRM:....................%s\n", cad_med[cpf_pas_encotrado].crm);	
																				printf("================================================================================\n\n\n");
																				system("PAUSE");
																			}					
																			system("cls");
																			medico_cadastro();
																			op = le_valida_continuar_filtragem(); /*perguntando se deseja continuar filtragem*/
																		}while(op != '2');
																	break;
																	
																	case '2':/*TODOS OS CADASTROS DO MÉDICO*/
																		agora = time(NULL);																
																		strftime(data, sizeof(data), "%d/%m/%y", localtime(&agora));/*AQUI VAI COLETAR A DATA E HORA ATUAL*/
																		strftime(hora, sizeof(hora), "%H:%M:%S", localtime(&agora));																		
																		system("cls");
																		medico_cadastro();/*Apresentando os dados de ditado dos médicos, porém, de todos*/
																		printf("                  DATA: %s        HORA: %s\n\n", data, hora);
																		for(c = 0; c < c_med; c++){
																			printf("================================================================================\n");
																			printf("                              %dº MÉDICO\n\n\n", c + 1);
																			printf("CPF: ...................%s\n", cad_med[c].cpf);
																			printf("NOME: ..................%s\n", cad_med[c].nome);
																				if(cad_med[c].sexo == '1'){
																					printf("SEXO: ..................MASCULINO\n");
																				}else{
																					printf("SEXO: ..................FEMININO\n");
																				}
																			printf("DATA DE NASCIMENTO......%d/%d/%d\n", cad_med[c].dia, cad_med[c].mes, cad_med[c].ano);
																			printf("IDADE...................%d ANOS\n", cad_med[c].idade);
																			printf("CRM:....................%s\n\n", cad_med[c].crm);		
																		}	
																		printf("================================================================================\n\n");
																		printf("QUANTIDADE DE MÉDICOS CADASTRADOS.............%d\n\n", c_med); /*apresentando a quantidade de cadastros totais, de homens e de mulheres*/
																		printf("HOMENS........................................%d\n\n", qtd_homem_med);
																		printf("MULHERES......................................%d\n\n\n", qtd_mulher_med);									
																		system("PAUSE");
																	break;
																}	
															}while(op_continuar != '3');
														}
													break;
												}
											}while(op_sair != '4');
										break;
										
										case '2':/*RELATÓRIO DE AGENDAMENTO*/
											if(tot_agend == 0){ /*verificando se existe agendamentos marcados*/
												system("cls");
												sem_agendamento();
											}else{
												do{ /*se existir agendamentos marcados*/
													system("cls");
													relatorio_agendamento();
													op_sair = le_val_select_unidade();
													switch(op_sair){
														case '1':/*RELATÓRIO DE AGENDAMENTO DA UNIDADE GUARÁ*/
															do{
																system("cls");
																agendamento_guara();
																op_continuar = le_valida_op_relatorio_cad_agend();
																switch(op_continuar){
																	case '1':/*FILTRAR AGENDAMENTOS*/
																		do{
																			system("cls");
																			agendamento_guara();
																			printf("CPF: ");
																			scanf("%s", cpf_ag); /*Lendo cpf para validação*/
																			tam_cpf = strlen(cpf_ag);
																			fflush(stdin);
																			soma_cpf = 0;										
										
																			for(c = 0; c < 9; c++){
																				numero_cpf = cpf_ag[c] - 48;
																				soma_cpf = soma_cpf + (numero_cpf * (10-c));
																			}										
																			resultado_cpf = 11 - (soma_cpf%11);										
																				if(resultado_cpf == 10 || resultado_cpf == 11){
																					digito10 = '0';
																				}else{
																					digito10 = resultado_cpf + 48;
																				}										
																			soma_cpf = 0;
																			
																			for(c = 0; c < 10; c++){
																				numero_cpf = cpf_ag[c] - 48;
																				soma_cpf = soma_cpf +(numero_cpf * (11-c));
																			}										
																			resultado_cpf = 11 - (soma_cpf%11);
																			
																				if(resultado_cpf == 10 || resultado_cpf == 11){
																					digito11 = '0';										
																				}else{
																					digito11 = resultado_cpf + 48;
																				}																					
																				if(cpf_ag[9] != digito10 || cpf_ag[10] != digito11 || tam_cpf != 11){
																					do{
																						system("cls");
																						cpf_invalido();
																						printf("DIGITE NOVAMENTE (ex: 12345678901): ");
																						scanf("%s", cpf_ag);										
																						tam_cpf = strlen(cpf_ag);
																						fflush(stdin);																
																						soma_cpf = 0;																								
																						
																						for(c = 0; c < 9; c++){
																							numero_cpf = cpf_ag[c] - 48;
																							soma_cpf = soma_cpf + (numero_cpf * (10-c));
																						}													
																						resultado_cpf = 11 - (soma_cpf%11);													
																							if(resultado_cpf == 10 || resultado_cpf == 11){
																								digito10 = '0';
																							}else{
																								digito10 = resultado_cpf + 48;
																							}													
																						soma_cpf = 0;
																						
																						for(c = 0; c < 10; c++){
																							numero_cpf = cpf_ag[c] - 48;
																							soma_cpf = soma_cpf +(numero_cpf * (11-c));
																						}													
																						resultado_cpf = 11 - (soma_cpf%11);													
																							if(resultado_cpf == 10 || resultado_cpf == 11){
																								digito11 = '0';													
																							}else{
																								digito11 = resultado_cpf + 48;
																							}
																					}while(cpf_ag[9] != digito10 || cpf_ag[10] != digito11 || tam_cpf != 11);	
																				}							
																												
																			valid_cpf = false;
																			cpf_pas_encotrado = 0;
																			for(c = 0; c < c_agend_guara; c++){ /*verificando se o cpf existe no formulário de agendamento*/
																				if(strcmp(cad_agend_guara[c].cpf, cpf_ag) == 0)
																					cpf_pas_encotrado = c;
																					valid_cpf = true;																																									
																			}																			
																			if(valid_cpf != true){ /*se não existir*/
																				system("cls");
																				agendamento_nao_encontrado();
																			}else{ /*se existir*/
																				agora = time(NULL);																
																				strftime(data, sizeof(data), "%d/%m/%y", localtime(&agora));/*AQUI VAI COLETAR A DATA E HORA ATUAL*/
																				strftime(hora, sizeof(hora), "%H:%M:%S", localtime(&agora));																				
																				system("cls");
																				agendamento_guara(); /*Aapresenatando os dados do agendamento*/
																				printf("                  DATA: %s        HORA: %s\n\n", data, hora);
																				printf("================================================================================\n");
																				printf("CPF:......................%s\n", cad_agend_guara[cpf_pas_encotrado].cpf);
																				printf("NOME:.....................%s\n", cad_agend_guara[cpf_pas_encotrado].nome);
																				printf("IDADE.....................%d ANOS\n",cad_agend_guara[cpf_pas_encotrado].idade);	
																					if(cad_agend_guara[cpf_pas_encotrado].sexo == '1'){
																						printf("SEXO:.....................MASCULINO\n");
																					}else{
																						printf("SEXO:.....................FEMININO\n");
																					}
																				printf("DATA DO AGENDAMENTO.......%d/%d/%d\n", cad_agend_guara[cpf_pas_encotrado].dia_ag, cad_agend_guara[cpf_pas_encotrado].mes_ag, cad_agend_guara[cpf_pas_encotrado].ano_ag);
																				printf("HORÁRIO DO AGENDAMENTO....%s\n\n", cad_agend_guara[cpf_pas_encotrado].hora_agend);
																				printf("================================================================================\n\n\n");
																				system("PAUSE");
																			}																				
																			system("cls");
																			agendamento_guara();
																			op = le_valida_continuar_filtragem(); /*pergunta se deseja continuar filtragem*/																			
																		}while(op != '2');
																	break;
																	
																	case '2':/*TODOS OS AGENDAMENTOS DA UNIDADE GUARÁ*/
																		agora = time(NULL);																
																		strftime(data, sizeof(data), "%d/%m/%y", localtime(&agora));/*AQUI VAI COLETAR A DATA E HORA ATUAL*/
																		strftime(hora, sizeof(hora), "%H:%M:%S", localtime(&agora));																		
																		system("cls");
																		agendamento_guara(); /*Apresentando os dados do agendamento, porém , de todos*/
																		printf("                  DATA: %s        HORA: %s\n\n", data, hora);
																		for(c = 0; c < c_agend_guara; c++){
																			printf("================================================================================\n");
																			printf("                              %dº AGENDAMENTO\n\n\n", c + 1);
																			printf("CPF:......................%s\n", cad_agend_guara[c].cpf);
																			printf("NOME:.....................%s\n", cad_agend_guara[c].nome);
																			printf("IDADE.....................%d ANOS\n",cad_agend_guara[c].idade);	
																				if(cad_agend_guara[c].sexo == '1'){
																					printf("SEXO:.....................MASCULINO\n");
																				}else{
																					printf("SEXO:.....................FEMININO\n");
																				}
																			printf("DATA DO AGENDAMENTO.......%d/%d/%d\n", cad_agend_guara[c].dia_ag, cad_agend_guara[c].mes_ag, cad_agend_guara[c].ano_ag);
																			printf("HORÁRIO DO AGENDAMENTO....%s\n\n", cad_agend_guara[c].hora_agend);																			
																		}
																		printf("================================================================================\n\n");															
																		printf("QUANTIDADE DE AGENDAMENTOS....................%d\n\n\n", c_agend_guara);																													
																		system("PAUSE");																		
																	break;
																}
															}while(op_continuar != '3');
														break;
														
														case '2':/*RELATÓRIO DE AGENDAMENTO DA UNIDADE TAGUATINGA*/
															do{
																system("cls");
																agendamento_tagua();
																op_continuar = le_valida_op_relatorio_cad_agend();
																switch(op_continuar){
																	case '1':/*FILTRAR AGENDAMENTOS*/
																		do{
																			system("cls");
																			agendamento_tagua();
																			printf("CPF: ");
																			scanf("%s", cpf_ag); /*lendo cpf para validação*/
																			tam_cpf = strlen(cpf_ag);
																			fflush(stdin);
																			soma_cpf = 0;										
										
																			for(c = 0; c < 9; c++){ /*validação do cpf*/
																				numero_cpf = cpf_ag[c] - 48;
																				soma_cpf = soma_cpf + (numero_cpf * (10-c));
																			}										
																			resultado_cpf = 11 - (soma_cpf%11);										
																				if(resultado_cpf == 10 || resultado_cpf == 11){
																					digito10 = '0';
																				}else{
																					digito10 = resultado_cpf + 48;
																				}										
																			soma_cpf = 0;
																			
																			for(c = 0; c < 10; c++){
																				numero_cpf = cpf_ag[c] - 48;
																				soma_cpf = soma_cpf +(numero_cpf * (11-c));
																			}										
																			resultado_cpf = 11 - (soma_cpf%11);
																			
																				if(resultado_cpf == 10 || resultado_cpf == 11){
																					digito11 = '0';										
																				}else{
																					digito11 = resultado_cpf + 48;
																				}																					
																				if(cpf_ag[9] != digito10 || cpf_ag[10] != digito11 || tam_cpf != 11){
																					do{
																						system("cls");
																						cpf_invalido();
																						printf("DIGITE NOVAMENTE (ex: 12345678901): ");
																						scanf("%s", cpf_ag);										
																						tam_cpf = strlen(cpf_ag);
																						fflush(stdin);																
																						soma_cpf = 0;																								
																						
																						for(c = 0; c < 9; c++){
																							numero_cpf = cpf_ag[c] - 48;
																							soma_cpf = soma_cpf + (numero_cpf * (10-c));
																						}													
																						resultado_cpf = 11 - (soma_cpf%11);													
																							if(resultado_cpf == 10 || resultado_cpf == 11){
																								digito10 = '0';
																							}else{
																								digito10 = resultado_cpf + 48;
																							}													
																						soma_cpf = 0;
																						
																						for(c = 0; c < 10; c++){
																							numero_cpf = cpf_ag[c] - 48;
																							soma_cpf = soma_cpf +(numero_cpf * (11-c));
																						}													
																						resultado_cpf = 11 - (soma_cpf%11);													
																							if(resultado_cpf == 10 || resultado_cpf == 11){
																								digito11 = '0';													
																							}else{
																								digito11 = resultado_cpf + 48;
																							}
																					}while(cpf_ag[9] != digito10 || cpf_ag[10] != digito11 || tam_cpf != 11);	
																				}							
																												
																			valid_cpf = false;
																			cpf_pas_encotrado = 0;
																			for(c = 0; c < c_agend_tagua; c++){ /*verificando se o cpf existe no formulário de agendamento*/
																				if(strcmp(cad_agend_tagua[c].cpf, cpf_ag) == 0)
																					valid_cpf = true;
																					cpf_pas_encotrado = c;																				
																			}																			
																			if(valid_cpf != true){ /*se não existir*/
																				system("cls");
																				agendamento_nao_encontrado();
																			}else{ /*se existir*/
																				agora = time(NULL);																
																				strftime(data, sizeof(data), "%d/%m/%y", localtime(&agora));/*AQUI VAI COLETAR A DATA E HORA ATUAL*/
																				strftime(hora, sizeof(hora), "%H:%M:%S", localtime(&agora));																																			
																				system("cls"); /*apresentado os dados digitados do agendamento*/
																				agendamento_tagua();
																				printf("                  DATA: %s        HORA: %s\n\n", data, hora);
																				printf("================================================================================\n\n");
																				printf("CPF:......................%s\n", cad_agend_tagua[cpf_pas_encotrado].cpf);
																				printf("NOME:.....................%s\n", cad_agend_tagua[cpf_pas_encotrado].nome);
																				printf("IDADE.....................%d ANOS\n",cad_agend_tagua[cpf_pas_encotrado].idade);	
																					if(cad_agend_tagua[cpf_pas_encotrado].sexo == '1'){
																						printf("SEXO:.....................MASCULINO\n");
																					}else{
																						printf("SEXO:.....................FEMININO\n");
																					}
																				printf("DATA DO AGENDAMENTO.......%d/%d/%d\n", cad_agend_tagua[cpf_pas_encotrado].dia_ag, cad_agend_tagua[cpf_pas_encotrado].mes_ag, cad_agend_tagua[cpf_pas_encotrado].ano_ag);
																				printf("HORÁRIO DO AGENDAMENTO....%s\n\n", cad_agend_tagua[cpf_pas_encotrado].hora_agend);
																				printf("================================================================================\n\n\n");
																				system("PAUSE");
																			}																				
																			system("cls");
																			agendamento_tagua();
																			op = le_valida_continuar_filtragem(); /*pergunta se deseja continuar filtragem*/																			
																		}while(op != '2');
																	break;
																	
																	case '2':/*TODOS OS AGENDAMENTOS*/
																		agora = time(NULL);																
																		strftime(data, sizeof(data), "%d/%m/%y", localtime(&agora));/*AQUI VAI COLETAR A DATA E HORA ATUAL*/
																		strftime(hora, sizeof(hora), "%H:%M:%S", localtime(&agora));																		
																		system("cls");
																		agendamento_tagua(); /*Apresentando os dados digitados do agendamento, porém, de todos*/
																		printf("                  DATA: %s        HORA: %s\n\n", data, hora);
																		for(c = 0; c < c_agend_tagua; c++){
																			printf("================================================================================\n");
																			printf("                              %dº AGENDAMENTO\n\n\n", c + 1);
																			printf("CPF:......................%s\n", cad_agend_tagua[c].cpf);
																			printf("NOME:.....................%s\n", cad_agend_tagua[c].nome);
																			printf("IDADE.....................%d ANOS\n",cad_agend_tagua[c].idade);	
																				if(cad_agend_tagua[c].sexo == '1'){
																					printf("SEXO:.....................MASCULINO\n");
																				}else{
																					printf("SEXO:.....................FEMININO\n");
																				}
																			printf("DATA DO AGENDAMENTO.......%d/%d/%d\n", cad_agend_tagua[c].dia_ag, cad_agend_tagua[c].mes_ag, cad_agend_tagua[c].ano_ag);
																			printf("HORÁRIO DO AGENDAMENTO....%s\n\n", cad_agend_tagua[c].hora_agend);																			
																		}
																		printf("================================================================================\n\n");															
																		printf("QUANTIDADE DE AGENDAMENTOS....................%d\n\n\n", c_agend_tagua);																													
																		system("PAUSE");																	
																	break;
																}
															}while(op_continuar != '3');	
														break;
														
														case '3':/*RELATÓRIO DE AGENDAMENTO DA UNIDADE ÁGUAS CLARAS*/
															do{
																system("cls");
																agendamento_ac();
																op_continuar = le_valida_op_relatorio_cad_agend();
																switch(op_continuar){
																	case '1':/*FILTRAR AGENDAMENTOS */
																		do{
																			system("cls");
																			agendamento_ac();
																			printf("CPF: ");
																			scanf("%s", cpf_ag); /*lendo cpf para validação*/
																			tam_cpf = strlen(cpf_ag);
																			fflush(stdin);
																			soma_cpf = 0;										
										
																			for(c = 0; c < 9; c++){ /*validando cpf*/
																				numero_cpf = cpf_ag[c] - 48;
																				soma_cpf = soma_cpf + (numero_cpf * (10-c));
																			}										
																			resultado_cpf = 11 - (soma_cpf%11);										
																				if(resultado_cpf == 10 || resultado_cpf == 11){
																					digito10 = '0';
																				}else{
																					digito10 = resultado_cpf + 48;
																				}										
																			soma_cpf = 0;
																			
																			for(c = 0; c < 10; c++){
																				numero_cpf = cpf_ag[c] - 48;
																				soma_cpf = soma_cpf +(numero_cpf * (11-c));
																			}										
																			resultado_cpf = 11 - (soma_cpf%11);
																			
																				if(resultado_cpf == 10 || resultado_cpf == 11){
																					digito11 = '0';										
																				}else{
																					digito11 = resultado_cpf + 48;
																				}																					
																				if(cpf_ag[9] != digito10 || cpf_ag[10] != digito11 || tam_cpf != 11){
																					do{
																						system("cls");
																						cpf_invalido();
																						printf("DIGITE NOVAMENTE (ex: 12345678901): ");
																						scanf("%s", cpf_ag);										
																						tam_cpf = strlen(cpf_ag);
																						fflush(stdin);																
																						soma_cpf = 0;																								
																						
																						for(c = 0; c < 9; c++){
																							numero_cpf = cpf_ag[c] - 48;
																							soma_cpf = soma_cpf + (numero_cpf * (10-c));
																						}													
																						resultado_cpf = 11 - (soma_cpf%11);													
																							if(resultado_cpf == 10 || resultado_cpf == 11){
																								digito10 = '0';
																							}else{
																								digito10 = resultado_cpf + 48;
																							}													
																						soma_cpf = 0;
																						
																						for(c = 0; c < 10; c++){
																							numero_cpf = cpf_ag[c] - 48;
																							soma_cpf = soma_cpf +(numero_cpf * (11-c));
																						}													
																						resultado_cpf = 11 - (soma_cpf%11);													
																							if(resultado_cpf == 10 || resultado_cpf == 11){
																								digito11 = '0';													
																							}else{
																								digito11 = resultado_cpf + 48;
																							}
																					}while(cpf_ag[9] != digito10 || cpf_ag[10] != digito11 || tam_cpf != 11);	
																				}																																			
																			valid_cpf = false;
																			cpf_pas_encotrado = 0;
																			for(c = 0; c < c_agend_ac; c++){ /*verificando se o cpf exixte no formulário de agendamento*/
																				if(strcmp(cad_agend_ac[c].cpf, cpf_ag) == 0)
																					valid_cpf = true;
																					cpf_pas_encotrado = c;																				
																			}																			
																			if(valid_cpf != true){ /*se não existir*/
																				system("cls");
																				agendamento_nao_encontrado();
																			}else{ /*se existir*/
																				agora = time(NULL);																
																				strftime(data, sizeof(data), "%d/%m/%y", localtime(&agora));/*AQUI VAI COLETAR A DATA E HORA ATUAL*/
																				strftime(hora, sizeof(hora), "%H:%M:%S", localtime(&agora));																		
																				system("cls");
																				agendamento_ac(); /*apresentando os dados digitados no agendamento*/
																				printf("                  DATA: %s        HORA: %s\n\n", data, hora);
																				printf("================================================================================\n");
																				printf("CPF:......................%s\n", cad_agend_ac[cpf_pas_encotrado].cpf);
																				printf("NOME:.....................%s\n", cad_agend_ac[cpf_pas_encotrado].nome);
																				printf("IDADE.....................%d ANOS\n",cad_agend_ac[cpf_pas_encotrado].idade);	
																					if(cad_agend_ac[cpf_pas_encotrado].sexo == '1'){
																						printf("SEXO:.....................MASCULINO\n");
																					}else{
																						printf("SEXO:.....................FEMININO\n");
																					}
																				printf("DATA DO AGENDAMENTO.......%d/%d/%d\n", cad_agend_ac[cpf_pas_encotrado].dia_ag, cad_agend_ac[cpf_pas_encotrado].mes_ag, cad_agend_ac[cpf_pas_encotrado].ano_ag);
																				printf("HORÁRIO DO AGENDAMENTO....%s\n\n", cad_agend_ac[cpf_pas_encotrado].hora_agend);
																				printf("================================================================================\n\n\n");
																				system("PAUSE");
																			}																				
																			system("cls");
																			agendamento_ac();
																			op = le_valida_continuar_filtragem(); /*perguntando se deseja continuar filtragem*/																			
																		}while(op != '2');
																	break;
																	
																	case '2':/*TODOS OS AGENDAMENTOS*/
																		agora = time(NULL);																
																		strftime(data, sizeof(data), "%d/%m/%y", localtime(&agora));/*AQUI VAI COLETAR A HORA ATUAL*/
																		strftime(hora, sizeof(hora), "%H:%M:%S", localtime(&agora));																		
																		system("cls");
																		agendamento_ac(); /*apresentando todos os dados digitados do agendamento*/
																		printf("                  DATA: %s        HORA: %s\n\n", data, hora);
																		for(c = 0; c < c_agend_ac; c++){
																			printf("================================================================================\n");
																			printf("                              %dº AGENDAMENTO\n\n\n", c + 1);
																			printf("CPF:......................%s\n", cad_agend_ac[c].cpf);
																			printf("NOME:.....................%s\n", cad_agend_ac[c].nome);
																			printf("IDADE.....................%d ANOS\n",cad_agend_ac[c].idade);	
																				if(cad_agend_ac[c].sexo == 1){
																					printf("SEXO:.....................MASCULINO\n");
																				}else{
																					printf("SEXO:.....................FEMININO\n");
																				}
																			printf("DATA DO AGENDAMENTO.......%d/%d/%d\n", cad_agend_ac[c].dia_ag, cad_agend_ac[c].mes_ag, cad_agend_ac[c].ano_ag);
																			printf("HORÁRIO DO AGENDAMENTO....%s\n\n", cad_agend_ac[c].hora_agend);																			
																		}
																		printf("================================================================================\n\n");																		
																		printf("QUANTIDADE DE AGENDAMENTOS....................%d\n\n\n", c_agend_ac);																													
																		system("PAUSE");
																	break;
																}
															}while(op_continuar != '3');	
														break;
													}
												}while(op_sair != '4');	
											}											
										break;
										
										case '3':/*RELATÓRIO DE FATURAMENTO*/
											if(fat_total == 0){ /*verificando se a rede possui faturamento*/
												system("cls");
												sem_faturamento();
											}else{
												do{ /*se tiver faturamento*/
													total_agend = c_agend_guara + c_agend_tagua + c_agend_ac; /*somando a qtd de agendamentos totais da rede*/
		
													if(c_agend_guara > c_agend_tagua && c_agend_tagua >= c_agend_ac){ /*verificando qual a unidade possui mais agendamento e coletando o nome e a qtd*/
														strcpy(unidade_mais_atende, "GUARÁ");
														num_agend_mais = c_agend_guara;
													}else if(c_agend_guara > c_agend_tagua && c_agend_tagua <= c_agend_ac){
														strcpy(unidade_mais_atende, "GUARÁ");
														num_agend_mais = c_agend_guara;
													}else if(c_agend_tagua > c_agend_guara && c_agend_guara <= c_agend_ac ){
														strcpy(unidade_mais_atende, "TAGUATINGA");
														num_agend_mais = c_agend_tagua;
													} else if(c_agend_tagua > c_agend_guara && c_agend_guara >= c_agend_ac ){
														strcpy(unidade_mais_atende, "TAGUATINGA");
														num_agend_mais = c_agend_tagua;
													}else if (c_agend_ac > c_agend_guara && c_agend_guara <= c_agend_tagua){
														strcpy(unidade_mais_atende, "AGUAS CLARAS");
														num_agend_mais = c_agend_tagua;
													}else if(c_agend_ac > c_agend_guara && c_agend_guara >= c_agend_tagua){
														strcpy(unidade_mais_atende, "AGUAS CLARAS");
														num_agend_mais = c_agend_tagua;
													}
													
													por_cento_guara = c_agend_guara * 100 / total_agend ; /*cálculos de porcentagem referente a qtd de agendamentos , de cada unidade*/
													por_cento_tagua = c_agend_tagua * 100 / total_agend ;
													por_cento_ac = c_agend_ac * 100 / total_agend ;
															
													system("cls");
													faturamento();
													op_sair = le_valida_op_faturamento();
													switch(op_sair){
														case '1': /*RELATÓRIO DE AGENDAMENTO DA REDE*/
															system("cls");
															faixada();
															agora = time(NULL);																
															strftime(data, sizeof(data), "%d/%m/%y", localtime(&agora));/*AQUI VAI COLETAR A DATA E HORA ATUAL*/
															strftime(hora, sizeof(hora), "%H:%M:%S", localtime(&agora));															
															printf("                  DATA: %s        HORA: %s\n\n", data, hora); /*apresentando os dados de faturamento da rede*/
															printf("================================================================================\n\n");
															printf("FATURAMENTO MENSAL:................................R$ %.2f\n\n",fat_total);
															printf("FATURAMENTO DIÁRIO:................................R$ %.2f\n\n", fat_total_d);
															printf("________________________________________________________________________________\n\n");
															printf("AGENDAMENTOS:......................................%d\n\n", total_agend);
															printf("UNIDADE GUARÁ......................................%.0f %%\n\n", por_cento_guara);
															printf("UNIDADE TAGUATINGA.................................%.0f %%\n\n", por_cento_tagua);
															printf("UNIDADE AGUAS CLARAS...............................%.0f %%\n\n", por_cento_ac);															
															printf("________________________________________________________________________________\n\n");
															printf("UNIDADE QUE MAIS ATENDE:...........................UNIDADE %s\n\n", unidade_mais_atende);
															printf("QUANTIDADE DE AGENDAMENTOS:........................%d\n\n", num_agend_mais);
															printf("================================================================================\n\n\n");															
															system("PAUSE");
														break;
														
														case '2': /* RELATÓRIO DE FATURAMENTO POR UNIDADE*/
															do{
																system("cls");			
																faturamento();
																op_sair = le_val_select_unidade();
																switch(op_sair){
																	case '1': /*RELATÓRIO DE FATURAMENTO DA UNIDADE GUARA*/
																		system("cls");
																		faturamento();	
																		guara();
																		agora = time(NULL);																
																		strftime(data, sizeof(data), "%d/%m/%y", localtime(&agora));/*AQUI VAI COLETAR A DATA E HORA ATUAL*/
																		strftime(hora, sizeof(hora), "%H:%M:%S", localtime(&agora));
																		printf("                  DATA: %s        HORA: %s\n\n", data, hora); /*apresentando os dados do faturamento da unidade*/
																		printf("================================================================================\n\n");
																		printf("FATURAMENTO DIÁRIO:..........R$ %.2f \n\n",fat_dia_guara);
																		printf("FATURAMENTO MENSAL:..........R$ %.2f \n\n",fat_mes_guara);
																		printf("________________________________________________________________________________\n\n");
																		printf("TOTAL DE AGENDAMENTOS........%d\n\n", c_agend_guara);
																		printf("AGENDAMENTOS DIÁRIO..........%d\n\n", ag_dia_guara);
																		printf("================================================================================\n\n\n");
																		
																		system("PAUSE");
																	break;

																	case '2':/*RELATÓRIO DE FATURAMENTO DA UNIDADE TAGUATINGA*/
																		system("cls");
																		faturamento();
																		tagua();
																		agora = time(NULL);																
																		strftime(data, sizeof(data), "%d/%m/%y", localtime(&agora));/*AQUI VAI COLETAR A DATA E HORA ATUAL*/
																		strftime(hora, sizeof(hora), "%H:%M:%S", localtime(&agora));
																		printf("                  DATA: %s        HORA: %s\n\n", data, hora); /*apresentando os dados do faturamento da unidade*/
																		printf("================================================================================\n\n");
																		printf("FATURAMENTO DIÁRIO:..........R$ %.2f \n\n",fat_dia_tagua);
																		printf("FATURAMENTO MENSAL:..........R$ %.2f \n\n",fat_mes_tagua);
																		printf("________________________________________________________________________________\n\n");
																		printf("TOTAL DE AGENDAMENTOS........%d\n\n", c_agend_tagua);
																		printf("AGENDAMENTOS DIÁRIO..........%d\n\n", ag_dia_tagua);
																		printf("================================================================================\n\n\n");
																		system("PAUSE");	
																	break;
																	
																	case '3':/*RELATÓRIO DE FATURAMENTO DA UNIDADE AGUAS CLARAS*/
																		system("cls");
																		faturamento();
																		ac();
																		agora = time(NULL);																
																		strftime(data, sizeof(data), "%d/%m/%y", localtime(&agora));/*AQUI VAI COLETAR A DATA E HORA ATUAL*/
																		strftime(hora, sizeof(hora), "%H:%M:%S", localtime(&agora));
																		printf("                  DATA: %s        HORA: %s\n\n", data, hora); /*apresentando os dados do faturamento da unidade*/
																		printf("================================================================================\n\n");
																		printf("FATURAMENTO DIÁRIO:..........R$ %.2f \n\n",fat_dia_ac);
																		printf("FATURAMENTO MENSAL:..........R$ %.2f \n\n",fat_mes_ac);
																		printf("________________________________________________________________________________\n\n");
																		printf("TOTAL DE AGENDAMENTOS........%d\n\n", c_agend_ac);
																		printf("AGENDAMENTOS DIÁRIO..........%d\n\n", ag_dia_ac);
																		printf("================================================================================\n\n\n");
																		system("PAUSE");	
																	break;
																}
															}while(op_sair != '4'); 
														break;
													}													
												}while(op_sair != '3');		
											}																					
										break;
									}	
								}while(op_continuar != '4');
							break;										
						}
					}while(op != '5' );		
				}
			break;
		}/*swirch (Op_benvindo)*/	
	}while(op_benvindo != '3' ); /*opção sair*/
	
	op_sair = le_val_op_sair(); /*AQUI VAI PERGUNTAR SE O USUÁRIO REALMENTE DESEJA ENCERRAR O PROGRAMA*/
}while(op_sair == '2');	
	system("cls"); 
	program_encerrado();
	return 0;
}
/*FUNÇÕES*/

char le_val_select_unidade(){ /*FUNÇÃO PARA SELECIONAR A UNIDADE*/
	char op2 = ' ';
	
	printf("[ 1 ] UNIDADE GUARÁ\n");
	printf("[ 2 ] UNIDADE TAGUATINGA\n");
	printf("[ 3 ] UNIDADE ÁGUAS CLARAS\n");
	printf("[ 4 ] SAIR\n\n");
	printf("OPÇÃO: ");
	scanf(" %c", &op2);
		if( op2 != '1' && op2 != '2' && op2 != '3' && op2 != '4'){
			do{
				system("cls");
				erro();
				printf("[ 1 ] UNIDADE GUARÁ\n");
				printf("[ 2 ] UNIDADE TAGUATINGA\n");
				printf("[ 3 ] UNIDADE ÁGUAS CLARAS\n");
				printf("[ 4 ] SAIR\n\n");
				printf("DIGITE NOVAMENTE: ");
				scanf(" %c", &op2);
			}while( op2 != '1' && op2 != '2' && op2 != '3' && op2 != '4');
		}
	return op2;	
}

char le_val_menu_bv(){ /*VALIDANDO AS OPÇÕES DO MENU INCIAL*/
	char op2 = ' ';
	
	scanf(" %c", &op2);
		if( op2 != '1' && op2 != '2' && op2 != '3'){
			do{
				system("cls");
				erro();
				printf("[ 1 ] CADASTRO\n");
				printf("[ 2 ] LOGIN\n");
				printf("[ 3 ] SAIR\n\n");
				printf("DIGITE NOVAMENTE: ");
				scanf(" %c", &op2);
			}while( op2 != '1' && op2 != '2' && op2 != '3');
		}		
	return op2;
}

char le_val_cad_func(){ /*VALIDANDO AS OPÇÕES DO CADASTRO DE FUNCIONÁRIO*/
	char op2 = ' ';
	
	printf("[ 1 ] CADASTRAR\n");
	printf("[ 2 ] SAIR\n\n");
	printf("OPÇÃO: ");
	scanf(" %c", &op2);
		if( op2 != '1' && op2 != '2'){
			do{
				system("cls");
				erro();
				printf("[ 1 ] CADASTRAR\n");
				printf("[ 2 ] SAIR\n\n");
				printf("DIGITE NOVAMENTE: ");
				scanf(" %c", &op2);
			}while( op2 != '1' && op2 != '2');
		}
	return op2;	
}

char le_valida_continuar_agend(){ /*VALIDANDO AS OPÇÕES DO MENU QUE PERGUNTA SE O USUÁRIO DESEJA CONTINUAR*/
	char op2 = ' ';

	printf("DESEJA REALIZAR OUTRO AGENDAMENTO?\n\n");
	printf("[ 1 ] SIM\n");
	printf("[ 2 ] NÃO\n\n");
	printf("OPÇÃO: ");
	scanf(" %c", &op2);
		if( op2 != '1' && op2 != '2'){
			do{
				system("cls");
				erro();
				printf("DESEJA REALIZAR OUTRO AGENDAMENTO? \n\n");
				printf("[ 1 ] SIM\n");
				printf("[ 2 ] NÃO\n\n");
				printf("DIGITE NOVAMENTE: ");
				scanf(" %c", &op2);
			}while( op2 != '1' && op2 != '2');
		}
	return op2;
}

char le_valida_continuar_cancelamento_agend(){ /*VALIDANDO AS OPÇÕES DO MENU QUE PERGUNTA SE O USUÁRIO DESEJA CONTINUAR*/
	char op2 = ' ';

	printf("DESEJA CANCELAR OUTRO AGENDAMENTO?\n\n");
	printf("[ 1 ] SIM\n");
	printf("[ 2 ] NÃO\n\n");
	printf("OPÇÃO: ");
	scanf(" %c", &op2);
		if( op2 != '1' && op2 != '2'){
			do{
				system("cls");
				erro();
				printf("DESEJA CANCELAR OUTRO AGENDAMENTO? \n\n");
				printf("[ 1 ] SIM\n");
				printf("[ 2 ] NÃO\n\n");
				printf("DIGITE NOVAMENTE: ");
				scanf(" %c", &op2);
			}while( op2 != '1' && op2 != '2');
		}
	return op2;
}

char le_val_op_continuar_cad(){ /*VALIDANDO AS OPÇÕES DO MENU QUE PERGUNTA SE O USUÁRIO DESEJA CONTINUAR*/
	char op2 = ' ';
	
	printf("________________________________________________________________________________\n");
	printf("DESEJA CONTINUAR CADASTRANDO?\n\n");
	printf("[ 1 ] SIM\n");
	printf("[ 2 ] NÃO\n\n");
	printf("OPÇÃO: ");
	scanf(" %c", &op2);
		if(op2 != '1' && op2 != '2'){
			do{
				system("cls");
				erro();
				printf("________________________________________________________________________________\n");
				printf("DESEJA CONTINUAR CADASTRANDO? \n\n");
				printf("[ 1 ] SIM\n");
				printf("[ 2 ] NÃO\n\n");
				printf("DIGITE NOVAMENTE: ");
				scanf(" %c", &op2);
			}while(op2 != '1' && op2 != '2');
		}
	return op2;
}

int le_val_dia(int c){ /*VALIDANDO O DIA DE NASCIMENTO DIGITADO PELO USUÁRIO*/
	int dia = 0;
	
	printf("DIA: ");
	scanf("%d", &dia);
		if(dia < 1 || dia > 31){
			do{
				system("cls");
				dados_invalidos();
	
				printf("INFORME O DIA NOVAMENTE: ");
				scanf("%d", &dia);
			}while(dia < 0 || dia > 31);		
		}
	return dia;	
}

int le_val_mes(int c){ /*VALIDANDO O MES DE NASCIMENTO DIGITADO PELO USUÁRIO*/
	int mes = 0;
	
	printf("MÊS: ");
	scanf("%d", &mes);
		if(mes < 1 || mes > 12){
			do{
				system("cls");
				dados_invalidos();

				printf("INFORME O MÊS NOVAMENTE  (ex: 3): ");
				scanf("%d", &mes);		
			}while(mes < 1 || mes > 12);	
		}
	return mes;
}

int le_val_ano(int c, int ano_at){ /*VALIDANDO O ANO DE NASCIMENTO DIGITADO PELO USUÁRIO*/
	int ano = 0;
	int idade = 0;
	
	printf("ANO: ");
	scanf("%d", &ano);
		if(ano < 1900 || ano > ano_at){ 
			do{
				system("cls");
				dados_invalidos();

				printf("iNFORME O ANO NOVAMENTE  (ex: 1996): ");
				scanf("%d", &ano);		
			}while(ano < 1900 || ano > ano_at);	
		}		
	idade = ano_at - ano;
		if(idade < IDADE_MIN){ /*verificando a idade*/
			do{
				system("cls");
				idade_invalida();

				printf("iNFORME O ANO NOVAMENTE: ");
				scanf("%d", &ano);
					while(ano < 1900 || ano > ano_at){
						system("cls");
						dados_invalidos();

						printf("iNFORME O ANO NOVAMENTE: ");
						scanf("%d", &ano);		
					}	
				idade = ano_at - ano;
			}while(idade < IDADE_MIN);	
		}		
	return ano;		
}

char le_val_dados_corretos(){ /*VALIDANDO AS OPÇÕES DO MENU QUE PERGUNTA SE OS DADOS DIGITADOS ESTÃO CORRETOS*/
	char op2 = ' ';
	
	printf("OS DADOS ESTÃO CORRETOS? \n\n");
	printf("[ 1 ] SIM\n");
	printf("[ 2 ] NÃO\n\n");
	printf("OPÇÃO: ");
	scanf(" %c", &op2);
		while(op2 != '1' && op2 != '2'){
			system("cls");
			erro();
			printf("OS DADOS ESTÃO CORRETOS? \n\n");
			printf("[ 1 ] SIM\n");
			printf("[ 2 ] NÃO\n\n");
			printf("DIGITE NOVAMENTE: ");
			scanf(" %c", &op2);
		}
	return op2;
}


char le_valida_op_menu_principal(){ /*VALIDANDO AS OPÇÕES DO MENU PRINCIPAL*/
	char op2 = ' ';
	
	printf("[ 1 ] CADASTRO \n");
	printf("[ 2 ] AGENDAMENTO\n");
	printf("[ 3 ] CANCELAR AGENDAMENTO\n");
	printf("[ 4 ] RELATÓRIOS\n");
	printf("[ 5 ] SAIR\n\n");
	printf("OPÇÃO: ");
	scanf(" %c", &op2);
		if( op2 != '1' && op2 != '2' && op2 != '3' && op2 != '4' && op2 != '5'){
			do{
				system("cls");
				erro();
				printf("[ 1 ] CADASTRO \n");
				printf("[ 2 ] AGENDAMENTO\n");
				printf("[ 3 ] CANCELAR AGENDAMENTO\n");
				printf("[ 4 ] RELATÓRIOS\n");
				printf("[ 5 ] SAIR\n\n");
				printf("DIGITE NOVAMENTE: ");
				scanf(" %c", &op2);	
			}while(op2 != '1' && op2 != '2' && op2 != '3' && op2 != '4' && op2 != '5');
		}
	return op2;
}

char le_val_op_cadastro(){ /*VALIDANDO AS OPÇÕES DO MENU DE CADASTRO*/
	char op2 = ' ';
	
	printf("[ 1 ] PACIENTES\n");
	printf("[ 2 ] MEDICOS\n");
	printf("[ 3 ] SAIR\n\n");
	printf("OPÇÃO: ");
	scanf(" %c", &op2);
		if(op2 != '1' && op2 != '2' && op2 != '3'){
			do{
				system("cls");
				erro();
				printf("[ 1 ] PACIENTES\n");
				printf("[ 2 ] MEDICOS\n");
				printf("[ 3 ] SAIR\n\n");
				printf("DIGITE NOVAMENTE: ");
				scanf(" %c", &op2);
				
			}while(op2 != '1' && op2 != '2' && op2 != '3');
		}		
	return op2;
}

char le_valida_sexo(int c){ /*VALIDANDO AS OPÇÕES DO MENU QUE PERGUNTA O SEXO*/
	char sexo = ' ';
	
	printf("SEXO: \n\n");
	printf("[ 1 ] MASCULINO\n");
	printf("[ 2 ] FEMININO\n\n");
	printf("OPÇÃO: ");
	scanf(" %c", &sexo);
		if( sexo != '1' && sexo != '2'){
			do{
				system("cls");
				erro();
				contagem_fun_guara(c);
				printf("SEXO: \n\n");
				printf("[ 1 ] MASCULINO\n");
				printf("[ 2 ] FEMININO\n\n");
				printf("DIGITE NOVAMENTE: ");
				scanf(" %c", &sexo);
			}while(sexo != '1' && sexo != '2');
		}
	return sexo;
}

char le_val_op_sair(){ /*VALIDANDO A OPÇÃO DE MENU QUE VAI PERGUNTAR SE O USUÁSIO DESEJA SAIR*/
	char op2 = ' ';
	
	system("cls");
	faixada();
	printf("DESEJA REALMENTE SAIR? \n\n");
	printf("[ 1 ] SIM\n");
	printf("[ 2 ] NÃO\n\n");
	printf("OPÇÃO: ");
	scanf(" %c", &op2);
		if(op2 != '1' && op2 != '2'){
			do{
				system("cls");
				erro();
				printf("DESEJA REALMENTE SAIR? \n\n");
				printf("[ 1 ] SIM\n");
				printf("[ 2 ] NÃO\n\n");
				printf("DIGITE NOVAMENTE: ");
				scanf(" %c", &op2);				
			}while(op2 != '1' && op2 != '2');
		}
	return op2;
}

char le_valida_op_excluir(){ /*VALIDANDO AS OPÇÃOS QUE PERGUNATA SE O USUÁRIO DESEJA CANCELAR O AGENDAMENTO*/
	char op2 = ' ';
	
	printf("________________________________________________________________________________\n\n");
	printf("DESEJA REALMENTE CANCELAR O AGENDAMENTO? \n\n");
	printf("[ 1 ] SIM\n");
	printf("[ 2 ] NÃO\n\n");
	printf("OPÇÃO: ");
	scanf(" %c", &op2);
		if(op2 != '1' && op2 != '2'){
			do{
				system("cls");
				erro();
				printf("DESEJA REALMENTE CANCELAR O AGENDAMENTO? \n\n");
				printf("[ 1 ] SIM\n");
				printf("[ 2 ] NÃO\n\n");
				printf("DIGITE NOVAMENTE: ");
				scanf(" %c", &op2);				
			}while(op2 != '1' && op2 != '2');
		}
	return op2;
}

int le_valida_dias_trab(int c){ /*VALIDANDO A QTD DE DIAS TRABALHADOS*/
	int dia = 0;
	
	printf("DIAS TRABALHADOS NA SEMANA: ");
	scanf("%d", &dia);
		if(dia < 1 || dia > 7){
			do{
				system("cls");
				dados_invalidos();
				contagem_med(c);
				printf("DIGITE NOVAMENTE: ");
				scanf("%d", &dia);
			}while(dia < 1 || dia > 7);
		}
	return dia;
}

char le_valida_op_relatorio(){ /*VALIDANDO AS OPÇÕES DO MENU PRINCIPAL DO RELATÓRIO*/
	char op2 = ' ';
	
	printf("[ 1 ] CADASTRO \n");
	printf("[ 2 ] AGENDAMENTO\n");
	printf("[ 3 ] FATURAMENTO\n");
	printf("[ 4 ] SAIR\n\n");
	printf("OPÇÃO: ");
	scanf(" %c", &op2);
		if( op2 != '1' && op2 != '2' && op2 != '3' && op2 != '4'){
			do{
				system("cls");
				erro();
				printf("[ 1 ] CADASTRO \n");
				printf("[ 2 ] AGENDAMENTO\n");
				printf("[ 3 ] FATURAMENTO\n");
				printf("[ 4 ] SAIR\n\n");
				printf("DIGITE NOVAMENTE: ");
				scanf(" %c", &op2);	
			}while(op2 != '1' && op2 != '2' && op2 != '3' && op2 != '4');
		}
	return op2;	
}

char le_valida_relatorio_cad(){ /*VALIDANDO AS OPÇÕES DO RELATÓRIO DE CADASTROS*/
	char op2 = ' ';
	
	printf("[ 1 ] FUNCIONÁRIOS \n");
	printf("[ 2 ] PACIENTES\n");
	printf("[ 3 ] MÉDICOS\n");
	printf("[ 4 ] SAIR\n\n");
	printf("OPÇÃO: ");
	scanf(" %c", &op2);
		if( op2 != '1' && op2 != '2' && op2 != '3' && op2 != '4'){
			do{
				system("cls");
				erro();
				printf("[ 1 ] FUNCIONÁRIOS \n");
				printf("[ 2 ] PACIENTES\n");
				printf("[ 3 ] MÉDICOS\n");
				printf("[ 4 ] SAIR\n\n");
				printf("DIGITE NOVAMENTE: ");
				scanf(" %c", &op2);	
			}while(op2 != '1' && op2 != '2' && op2 != '3' && op2 != '4');
		}
	return op2;	
}

char le_valida_op_relatorio_cad_fun(){ /*VALIDANDO AS OPÇÕES DE FILTRAGEM*/
	char op2 = ' ';

	printf("[ 1 ] FILTRAR CADASTRO\n");
	printf("[ 2 ] TODOS OS CADASTROS\n");
	printf("[ 3 ] SAIR\n\n");
	printf("OPÇÃO: ");
	scanf(" %c", &op2);
		if(op2 != '1' && op2 != '2' && op2 != '3'){
			do{
				system("cls");
				erro();
				printf("[ 1 ] FILTRAR CADASTRO\n");
				printf("[ 2 ] TODOS OS CADASTROS\n");
				printf("[ 3 ] SAIR\n\n");
				printf("DIGITE NOVAMENTE: ");
				scanf(" %c", &op2);
				
			}while(op2 != '1' && op2 != '2' && op2 != '3');
		}		
	return op2;
}

char le_valida_continuar_filtragem(){ /*VALIDANDO AS OPÇÕES QUE PERGUNTA SE O USUÁRIO DESEJA CONTINUAR FILTRAGEM*/
	char op2 = ' ';
	
	printf("DESEJA CONTINUAR FILTRAGEM?\n\n");
	printf("[ 1 ] SIM\n");
	printf("[ 2 ] NÃO\n\n");
	printf("OPÇÃO: ");
	scanf(" %c", &op2);
		if(op2 != '1' && op2 != '2'){
			do{
				system("cls");
				erro();
				printf("________________________________________________________________________________\n");
				printf("DESEJA CONTINUAR FILTRAGEM? \n\n");
				printf("[ 1 ] SIM\n");
				printf("[ 2 ] NÃO\n\n");
				printf("DIGITE NOVAMENTE: ");
				scanf(" %c", &op2);
			}while(op2 != '1' && op2 != '2' );
		}
	return op2;	
}

char le_valida_op_relatorio_cad_agend(){ /*VALIDANDO OPÇÕES DE FILTRAGEM*/
	char op2 = ' ';
	
	printf("[ 1 ] FILTRAR AGENDAMENTO\n");
	printf("[ 2 ] TODOS OS AGENDAMENTOS\n");
	printf("[ 3 ] SAIR\n\n");
	printf("OPÇÃO: ");
	scanf(" %c", &op2);
		if(op2 != '1' && op2 != '2' && op2 != '3'){
			do{
				system("cls");
				erro();
				printf("[ 1 ] FILTRAR AGENDAMENTO\n");
				printf("[ 2 ] TODOS OS AGENDAMENTOS\n");
				printf("[ 3 ] SAIR\n\n");
				printf("DIGITE NOVAMENTE: ");
				scanf(" %c", &op2);
				
			}while(op2 != '1' && op2 != '2' && op2 != '3');
		}		
		return op2;
}

char le_valida_op_faturamento(){ /*VALIDANDO OPÇÕES DO RELATÓRIO DE FATURAMENTO*/
	char op2 = ' ';
	
	printf("[ 1 ] REDE\n");
	printf("[ 2 ] UNIDADE\n");
	printf("[ 3 ] SAIR\n\n");
	printf("OPÇÃO: ");
	scanf(" %c", &op2);
		if(op2 != '1' && op2 != '2' && op2 != '3'){
			do{
				system("cls");
				erro();
				printf("[ 1 ] REDE\n");
				printf("[ 2 ] UNIDADE\n");
				printf("[ 3 ] SAIR\n\n");
				printf("DIGITE NOVAMENTE: ");
				scanf(" %c", &op2);
				
			}while(op2 != '1' && op2 != '2' && op2 != '3');
		}		
	return op2;	
}


/*PROCEDIMENTOS*/
void bem_vindo(){
	printf("________________________________________________________________________________\n");
	printf("                                                                    \n");
	printf("                             Clínica VITTA BELLA                    \n");	
	printf("                                                                    \n");
	printf("________________________________________________________________________________\n\n");
	system("PAUSE");
}

void menu_bem_vindo(){
	printf("________________________________________________________________________________\n");
	printf("                                                                    \n");
	printf("                             Clínica VITTA BELLA                    \n");	
	printf("                                                                    \n");
	printf("________________________________________________________________________________\n\n");
	printf("[ 1 ] CADASTRO\n");
	printf("[ 2 ] LOGIN\n");
	printf("[ 3 ] SAIR\n\n");
	printf("OPÇÃO: ");
	
}

void faixada(){
	printf("________________________________________________________________________________\n");
	printf("                                                                    \n");
	printf("                             Clínica VITTA BELLA                    \n");	
	printf("                                                                    \n");
	printf("________________________________________________________________________________\n\n");

}
void erro(){
	printf("________________________________________________________________________________\n");
	printf("                                                                    \n");
	printf("                           [ERRO] OPÇÃO INVÁLIDA                    \n");	
	printf("                                                                    \n");
	printf("________________________________________________________________________________\n\n");

}


void dados_invalidos(){
	printf("________________________________________________________________________________\n");
	printf("                                                                    \n");
	printf("                  [ERRO] CORRIJA OS DADOS E DIGITE NOVAMENTE       \n");	
	printf("                                                                    \n");
	printf("________________________________________________________________________________\n\n");

}

void cadastro_func(){
	printf("________________________________________________________________________________\n");
	printf("                                                                    \n");
	printf("                                  CADASTRO                          \n");	
	printf("                                                                    \n");
	printf("________________________________________________________________________________\n\n");
	
}

void guara(){
	
	printf("                                 UNIDADE GUARÁ                          \n");	
	printf("________________________________________________________________________________\n\n");
	
}

void contagem_fun_guara(int c){
	printf("                                 %dº fUNCIONÁRIO \n", c + 1);
	printf("________________________________________________________________________________\n\n");	
}

void contagem_pas(int c){
	printf("                                 %dº PACIENTE \n", c + 1);
	printf("________________________________________________________________________________\n\n");	
}

void contagem_med(int c){
	printf("                                 %dº MÉDICO \n", c + 1);
	printf("________________________________________________________________________________\n\n");	
}

void tagua(){

	printf("                               UNIDADE TAGUATINGA                     \n");	
	printf("________________________________________________________________________________\n\n");
	
}


void ac(){

	printf("                              UNIDADE AGUAS CLARAS                   \n");	
	printf("________________________________________________________________________________\n\n");
	
}

void ja_possui_cad(){
	printf("________________________________________________________________________________\n");
	printf("                                                                    \n");
	printf("                              CPF INFORMADO JA EXISTE                \n");	
	printf("                                                                     \n");
	printf("________________________________________________________________________________\n\n");
	
}

void cpf_invalido(){
	printf("________________________________________________________________________________\n");
	printf("                                                                    \n");
	printf("                                [ERRO] CPF INVÁLIDO                \n");	
	printf("                                                                     \n");
	printf("________________________________________________________________________________\n\n");
	
}

void cpf_valido(){
	printf("________________________________________________________________________________\n");
	printf("                                                                    \n");
	printf("                                  CPF VALIDADO!                \n");	
	printf("                                                                     \n");
	printf("________________________________________________________________________________\n\n");
	
}

void cad_limite(){
	printf("________________________________________________________________________________\n");
	printf("                                                                    \n");
	printf("                      NÃO É POSSÍVEL CADASTRAR MAIS FUNCIONÁRIOS!   \n");	
	printf("                                                                    \n");
	printf("________________________________________________________________________________\n\n");
	system("PAUSE");
	
	
}


void cad_limite_pas(){
	printf("________________________________________________________________________________\n");
	printf("                                                                    \n");
	printf("                      NÃO É POSSÍVEL CADASTRAR MAIS PACIENTES!   \n");	
	printf("                                                                    \n");
	printf("________________________________________________________________________________\n\n");
	system("PAUSE");
		
}

void cad_limite_med(){
	printf("________________________________________________________________________________\n");
	printf("                                                                    \n");
	printf("                      NÃO É POSSÍVEL CADASTRAR MAIS MÉDICOS!   \n");	
	printf("                                                                    \n");
	printf("________________________________________________________________________________\n\n");
	system("PAUSE");
		
}

void idade_invalida(){
	printf("________________________________________________________________________________\n");
	printf("                                                                    \n");
	printf("       [ERRO] NÃO É PERMITIDO O CADASTRO DE USUÁRIOS MENORES DE 16 ANOS      \n");	
	printf("                                                                    \n");
	printf("________________________________________________________________________________\n\n");

}

void login(){
	printf("________________________________________________________________________________\n");
	printf("                                                                     \n");
	printf("                                    LOGIN                            \n");	
	printf("                                                                     \n");
	printf("________________________________________________________________________________\n\n");
	
}

void login_encontrado(){
	printf("________________________________________________________________________________\n");
	printf("                                                                    \n");
	printf("                              USUÁRIO ENCONTRADO                     \n");	
	printf("                                                                     \n");
	printf("________________________________________________________________________________\n\n");
	
}

void login_erro(){
	printf("________________________________________________________________________________\n");
	printf("                                                                         \n");
	printf("                          [ERRO] USUÁRIO NÃO ENCONTRADO                  \n");	
	printf("                                                                         \n");
	printf("________________________________________________________________________________\n\n");
	
}

void senha_erro(){
	printf("________________________________________________________________________________\n");
	printf("                                                                      \n");
	printf("                             [ERRO] SENHA INVÁLIDA                     \n");	
	printf("                                                                       \n");
	printf("________________________________________________________________________________\n\n");
} 


void senha_existente(){
	
	printf("________________________________________________________________________________\n");
	printf("                                                                      \n");
	printf("                             SENHA INFORMADA JA EXISTE                   \n");	
	printf("                                                                       \n");
	printf("________________________________________________________________________________\n\n");
 
}

void sem_usuarios(){
	printf("________________________________________________________________________________\n");
	printf("                                                                    \n");
	printf("     NÃO É POSSÍVEL FAZER O LOGIN, POIS NÃO HÁ FUNCIONÁRIOS CADASTRADOS   \n");	
	printf("                                                                    \n");
	printf("________________________________________________________________________________\n\n");
	system("PAUSE");
	
	
}

void sem_pasciente(){
	printf("________________________________________________________________________________\n");
	printf("                                                                    \n");
	printf("     NÃO É POSSÍVEL FAZER O AGENDAMENTO, POIS NÃO HÁ PACIENTES CADASTRADOS   \n");	
	printf("                                                                    \n");
	printf("________________________________________________________________________________\n\n");
	system("PAUSE");	
}

void sem_agendamento(){
	printf("________________________________________________________________________________\n");
	printf("                                                                    \n");
	printf("                      NÃO HÁ AGENDAMENTOS MARCADOS   \n");	
	printf("                                                                    \n");
	printf("________________________________________________________________________________\n\n");
	system("PAUSE");	
}

void paciente_nao_possui_agendamento(){
	printf("________________________________________________________________________________\n");
	printf("                                                                    \n");
	printf("                 PACIENTE NÃO POSSUI AGENDAMENTO MARCADO \n");	
	printf("                                                                    \n");
	printf("________________________________________________________________________________\n\n");
	system("PAUSE");	
}

void program_encerrado(){
	printf("________________________________________________________________________________\n");
	printf("                                                                    \n");
	printf("                             PROGRAMA ENCERRADO   \n");	
	printf("                                                                    \n");
	printf("________________________________________________________________________________\n\n");
	
	 
}

void senha_menor(int c){
	printf("________________________________________________________________________________\n");
	printf("                                                                    \n");
	printf("                 [ERRO] A SENHA PRECISA TER NO MINIMO %d CARACTERES   \n", c);	
	printf("                                                                    \n");
	printf("________________________________________________________________________________\n\n");
	
	 
}

void senha_maior(int c){
	printf("________________________________________________________________________________\n");
	printf("                                                                    \n");
	printf("                 [ERRO] A SENHA PRECISA TER NO MÁXIMO %d CARACTERES   \n", c);	
	printf("                                                                    \n");
	printf("________________________________________________________________________________\n\n");
	
	 
}

void crm_menor(int c){
	printf("________________________________________________________________________________\n");
	printf("                                                                    \n");
	printf("                 [ERRO] O CRM PRECISA TER NO MINIMO %d CARACTERES   \n", c);	
	printf("                                                                    \n");
	printf("________________________________________________________________________________\n\n");
	
	 
}

void crm_maior(int c){
	printf("________________________________________________________________________________\n");
	printf("                                                                    \n");
	printf("                 [ERRO] O CRM PRECISA TER NO MÁXIMO %d CARACTERES   \n", c);	
	printf("                                                                    \n");
	printf("________________________________________________________________________________\n\n");
	
	 
}

void crm_existente(){
	printf("________________________________________________________________________________\n");
	printf("                                                                      \n");
	printf("                             CRM INFORMADO JA EXISTE                   \n");	
	printf("                                                                       \n");
	printf("________________________________________________________________________________\n\n");
}


void agendamento(){
	printf("________________________________________________________________________________\n");
	printf("                                                                      \n");
	printf("                                  AGENDAMENTO                   \n");	
	printf("                                                                       \n");
	printf("________________________________________________________________________________\n\n");
}

void agendamento_guara(){
	printf("________________________________________________________________________________\n");
	printf("                                                                      \n");
	printf("                            AGENDAMENTO UNIDADE GUARÁ                 \n");	
	printf("                                                                       \n");
	printf("________________________________________________________________________________\n\n");
}

void agendamento_tagua(){
	printf("________________________________________________________________________________\n");
	printf("                                                                      \n");
	printf("                         AGENDAMENTO UNIDADE TAGUATINGA                  \n");	
	printf("                                                                       \n");
	printf("________________________________________________________________________________\n\n");
}

void agendamento_ac(){
	printf("________________________________________________________________________________\n");
	printf("                                                                      \n");
	printf("                        AGENDAMENTO UNIDADE AGUAS CLARAS                 \n");	
	printf("                                                                       \n");
	printf("________________________________________________________________________________\n\n");
}

void cancelamento(){
	printf("________________________________________________________________________________\n");
	printf("                                                                      \n");
	printf("                                  CANCELAMENTO                  \n");	
	printf("                                                                       \n");
	printf("________________________________________________________________________________\n\n");
}

void paciente_encontrado(){
	printf("________________________________________________________________________________\n");
	printf("                                                                      \n");
	printf("                             PACIENTE ENCONTRADO                  \n");	
	printf("                                                                       \n");
	printf("________________________________________________________________________________\n\n");
}

void dia_indisponivel(){
	printf("________________________________________________________________________________\n");
	printf("                                                                      \n");
	printf("                 ESSE DIA ESTAR INDISPONÍVEL PARA AGENDAMENTO         \n");	
	printf("                                                                       \n");
	printf("________________________________________________________________________________\n\n");
}

void dia_invalido(){
	printf("________________________________________________________________________________\n");
	printf("                                                                      \n");
	printf("                           [ERRO] DIA INVÁLIDO         \n");	
	printf("                                                                       \n");
	printf("________________________________________________________________________________\n\n");
}


void cpf_nao_encontrado(){
	printf("________________________________________________________________________________\n");
	printf("                                                                      \n");
	printf("                            CPF NÃO ENCONTRADO         \n");	
	printf("                                                                       \n");
	printf("________________________________________________________________________________\n\n");
	system("PAUSE");
}

void possui_agendamento(){
	printf("________________________________________________________________________________\n");
	printf("                                                                      \n");
	printf("                  PACIENTE JA POSSUI AGENDAMENTO MARCADO         \n");	
	printf("                                                                       \n");
	printf("________________________________________________________________________________\n\n");
	system("PAUSE");
}

void horario_indisponivel(){
	printf("________________________________________________________________________________\n");
	printf("                                                                      \n");
	printf("                        ESTE HORÁRIO JA ESTAR MARCADO         \n");	
	printf("                                                                       \n");
	printf("________________________________________________________________________________\n\n");
	
}

void agend_realizado(){
	printf("________________________________________________________________________________\n");
	printf("                                                                      \n");
	printf("                        AGENDAMENTO REALIZADO COM SUCESSO         \n");	
	printf("                                                                       \n");
	printf("________________________________________________________________________________\n\n");
	
}

void relatorios(){
	printf("________________________________________________________________________________\n");
	printf("                                                                      \n");
	printf("                                 RELATÓRIOS         \n");	
	printf("                                                                       \n");
	printf("________________________________________________________________________________\n\n");
	
}

void relatorio_cadastro(){
	printf("________________________________________________________________________________\n");
	printf("                                                                      \n");
	printf("                          RELATÓRIOS DE CADASTRO        \n");	
	printf("                                                                       \n");
	printf("________________________________________________________________________________\n\n");
	
}

void relatorio_agendamento(){
	printf("________________________________________________________________________________\n");
	printf("                                                                      \n");
	printf("                          RELATÓRIOS DE AGENDAMENTO        \n");	
	printf("                                                                       \n");
	printf("________________________________________________________________________________\n\n");
	
}

void funcionario_cadastro(){
	printf("________________________________________________________________________________\n");
	printf("                                                                      \n");
	printf("                          CADASTRO DE FUNCIONÁRIO        \n");	
	printf("                                                                       \n");
	printf("________________________________________________________________________________\n\n");
	
}

void funcionario_nao_encontrado(){
	printf("________________________________________________________________________________\n");
	printf("                                                                      \n");
	printf("                         FUNCIONÁRIO NÃO ENCONTRADO        \n");	
	printf("                                                                       \n");
	printf("________________________________________________________________________________\n\n");
	system("PAUSE");
	
}

void paciente_nao_encontrado(){
	printf("________________________________________________________________________________\n");
	printf("                                                                      \n");
	printf("                         PACIENTE NÃO ENCONTRADO        \n");	
	printf("                                                                       \n");
	printf("________________________________________________________________________________\n\n");
	system("PAUSE");
	
}

void paciente_cadastro(){
	printf("________________________________________________________________________________\n");
	printf("                                                                      \n");
	printf("                            CADASTRO DE PACIENTE         \n");	
	printf("                                                                       \n");
	printf("________________________________________________________________________________\n\n");
	
	
}
void medico_cadastro(){
	printf("________________________________________________________________________________\n");
	printf("                                                                      \n");
	printf("                             CADASTRO DE MÉDICO         \n");	
	printf("                                                                       \n");
	printf("________________________________________________________________________________\n\n");
	
	
}

void sistema_sem_paciente(){
	printf("________________________________________________________________________________\n");
	printf("                                                                      \n");
	printf("                  O SISTEMA NÃO POSSUI PACIENTES CADASTRADOS         \n");	
	printf("                                                                       \n");
	printf("________________________________________________________________________________\n\n");
	system("PAUSE");
	
}

void sistema_sem_medico(){
	printf("________________________________________________________________________________\n");
	printf("                                                                      \n");
	printf("                  O SISTEMA NÃO POSSUI MÉDICOS CADASTRADOS         \n");	
	printf("                                                                       \n");
	printf("________________________________________________________________________________\n\n");
	system("PAUSE");	
}

void medico_nao_encontrado(){
	printf("________________________________________________________________________________\n");
	printf("                                                                      \n");
	printf("                            MÉDICO NÃO ENCONTRADO         \n");	
	printf("                                                                       \n");
	printf("________________________________________________________________________________\n\n");
	system("PAUSE");	
}

void agendamento_nao_encontrado(){
	printf("________________________________________________________________________________\n");
	printf("                                                                      \n");
	printf("                         AGENDAMENTO NÃO ENCONTRADO        \n");	
	printf("                                                                       \n");
	printf("________________________________________________________________________________\n\n");
	system("PAUSE");
	
}


void faturamento(){
	printf("________________________________________________________________________________\n");
	printf("                                                                      \n");
	printf("                                FATURAMENTO        \n");	
	printf("                                                                       \n");
	printf("________________________________________________________________________________\n\n");
	
	
}

void sem_faturamento(){
	printf("________________________________________________________________________________\n");
	printf("                                                                      \n");
	printf("                       o SISTEMA NÃO POSSUI FATURAMENTO        \n");	
	printf("                                                                       \n");
	printf("________________________________________________________________________________\n\n");
	system("PAUSE");
	
}

