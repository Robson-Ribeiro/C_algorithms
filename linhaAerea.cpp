#include<windows.h>         //DENTRE VÁRIA FUNÇÕES, PERMITE MUDAR A COR DO TEXTO COM O QUAL O USUÁRIO TEM CONTATO. NÃO FOI APLICADO POR GERAR PROBLEMAS COM O COMANDO SCANF().
#include<ctype.h>          //CONTÉM DECLARAÇÕES PARA MANIPULAÇÃO DE CARACTERES. EX: isdigit().
#include<conio.h>         //getch(), getchar() & getche().
#include<string.h>       //CONTÉM UMA SÉRIE DE FUNÇÕES PARA MANIPULAR STRINGS, VINDO DELA O COMANDO "strcmp()" QUE COMPARA STRINGS.
#include<stdlib.h>      //BIBLIOTECA PADRÃO QUE TRAZ DIVERSOS COMANDOS, COMO "system("cls");" QUE FOI UTILIZADO NESTE ALGORITIMO PARA LIMPAR O PROMPT. 
#include<locale.h>     //LOCALIZAÇÃO DE PROGRAMAS E ACENTUAÇÃO.
#include<stdio.h>     //BIBLIOTECA DE ENTRADA (scanf(), fgets(), etc.) E SAÍDA (printf()).

// Declaração
char nomeDestino[30], nomeDestinoVerif, statusLugar[200];
int qntAssentos, idadeComprador, numMenu, i, numAssento, numReserva=0, listaReserva[200], cancelamentoReserva, parametroCancelamento, efetivaReserva, parametroEfetivacao;
int contadorR, contadorC=0, contadorD=0, flag = 1;
float valorPassagem, valorTotalReserva, valorReservas[200], valorEfetivadas[200], valorTotalEfetivada;

// PROTOTIPAÇÃO
void showSeats(int c);

int main(){                                                                                                                                                                       //FUNÇÃO PRINCIPAL DE UM PROGRAMA EM C/C++. É ONDE O PROGRAMA COMEÇA.
	setlocale(LC_ALL, "Portuguese");                                                                                                                                              //AJUSTA O PROGRAMA PARA PORTUGUÊS.
	
	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);                                                                                                                            
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;                                                                                                                                       //CÓDIGOS ADVINDOS DA BIBLIOTECA WINDOWS.H QUE PERMITEM ALTERAR A COR DOS DADOS DE SAÍDA.
    WORD saved_attributes;                                                                                                                                                        //LOCAL QUE IRÁ ARMAZENAR A CONFIGURAÇÃO PADRÃO DE CORES.

    /* Salvar estado atual da configuração das cores*/
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;                                                                                                                                   //SALVA A CONFIGURAÇÃO PADRÃO DE CORES.
	
	//system("color 0D");                             
	//SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);                                                                                                                          //MUDA A COR DO TEXTO PRINTADO PARA VERDE.
	printf("+----------------------------------------------------------------------------------------------------------------------+");
	printf("|--------------------------------------BEM VINDO À EMPRESA EMIRATES LINHAS AÉREAS!-------------------------------------|");                                           //BOAS VINDAS.
	printf("+----------------------------------------------------------------------------------------------------------------------+\n");
	SetConsoleTextAttribute(hConsole, saved_attributes);                                                                                                                          //RETORNA PARA A CONFIGURAÇÃO PADRÃO DE CORES.

	
	for(i=0;i<=200;i++){                                                                                                                                                           //ESTRUTURAS DE REPETIÇÃO FOR UTILIZADAS PARA POPULAR TODOS OS VALORES DE DETERMINADOS VETORES.
		statusLugar[i] = 'D';
		listaReserva[i] = 0;
		valorReservas[i] = 0;
		valorEfetivadas[i] = 0;
	}

	
	//ENTRADA
	do{                                                                                                                                                                             //COLETA O NOME DO DESTINO DA VIAGEM, ALÉM DE REALIZAR AS DEVIDAS VALIDAÇÕES E INFORMAR QUANDO O VALOR FOR INVÁLIDO.
		printf("INFORME O NOME DO DESTINO PARA O QUAL DESEJA VIAJAR: ");
		fgets(nomeDestino, 30, stdin);
		fflush(stdin);
		nomeDestinoVerif = nomeDestino[0];
		if(strcmp(("%s", nomeDestino), "") == 0 or isspace(nomeDestinoVerif) == 8){
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);                                                                                                                      //MUDA A COR DO TEXTO PRINTADO PARA VERMELHO.
			printf("\nNOMES NULOS SÃO INVÁLIDOS!\n\n");
			SetConsoleTextAttribute(hConsole, saved_attributes);                                                                                                                    //RETORNA PARA A CONFIGURAÇÃO PADRÃO DE CORES.
		}
	}while(strcmp(("%s", nomeDestino), "") == 0 or isspace(nomeDestinoVerif) == 8);
	
	
	for(i=0;i<30;i++){
		nomeDestino[i] = toupper(nomeDestino[i]);                                                                                                                                   //DETERMINA TODOS OS CARACTERES DA VARIÁVEL NOMEDESTINO COMO MAIÚSCULOS.	
	}
	
	
	do{                                                                                                                                                                             //COLETA O VALOR DA PASSAGEM, ALÉM DE REALIZAR AS DEVIDAS VALIDAÇÕES E INFORMAR QUANDO O VALOR FOR INVÁLIDO.
		printf("\nINFORME O VALOR DA PASSAGEM: ");
		scanf("%f", &valorPassagem);
		fflush(stdin);
		if(valorPassagem <= 0){
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			printf("\nESSE VALOR É INVÁLIDO!\n");
			SetConsoleTextAttribute(hConsole, saved_attributes);
		}
	}while(valorPassagem <= 0);
	
	
	do{                                                                                                                                                                             //COLETA O NÚMERO DE ASSENTOS EXISTENTES, ALÉM DE REALIZAR AS DEVIDAS VALIDAÇÕES E INFORMAR QUANDO O VALOR FOR INVÁLIDO.
		printf("\nQUAL É A QUANTIDADE DE ASSENTOS EXISTENTES PARA O AVIÃO SELECIONADO PARA O SEU DESTINO? ");
		scanf("%d", &qntAssentos);
		fflush(stdin);
		if(qntAssentos < 90 or qntAssentos > 200){
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			printf("\nA QUANTIDADE DE ASSENTOS DOS AVIÕES DA EMPRESA SERÁ SEMPRE MAIOR OU IGUAL A 90 ASSENTOS, MAS NÃO ULTRAPASSARÁ 200!\n");
			SetConsoleTextAttribute(hConsole, saved_attributes);
		}
	}while(qntAssentos < 90 or qntAssentos > 200);
	
	
	printf("\n");
	system("pause");                                                                                                                                                                //PAUSA O SISTEMA ATÉ QUE SE APERTE UMA TECLA QUALQUER.
	
	
	//MENU
	do{                                                                                                                                                                             //GARANTE A CONTINUIDADE NO MENU ATÉ QUE SE INSIRA O DÍGITO 9 NO PRÓXIMO SCANF().
		system("cls");                                                                                                                                                              //COMANDO PARA LIMPAR A JANELA (PROMPT DE COMANDO).
		printf("DIGITE UM NÚMERO CORRELATO COM A FUNCIONALIDADE QUE DESEJA USAR:\n\n1-VERIFICAR A OCUPAÇÃO DO VOÔ\n \n2-EFETUAR UMA RESERVA POR MEIO DO FORNECIMENTO DO NÚMERO DO ASSENTO DISPONÍVEL\n \n3-REALIZAR O CANCELAMENTO DE UMA RESERVA POR MEIO DO FORNECIMENTO DE SEU NÚMERO ÚNICO DE IDENTIFICAÇÃO\n \n4-EFETIVAR A CONFIRMAÇÃO DE VENDA\n \n5-MOSTRAR A QUANTIDADE DE ASSENTOS COM RESERVAS, COM VENDAS CONFIRMADAS E DISPONÍVEIS, ALÉM DO VALOR TOTAL EM REAIS COM AS VENDAS JÁ CONFIRMADAS\n \n9-FINALIZAR!\n");
		scanf("%d", &numMenu);                                                                                                                                                      //CAPTURA UM VALOR INTEIRO PARA numMenu.
		fflush(stdin);                                                                                                                                                              
		if(numMenu!=1 and numMenu!=2 and numMenu!=3 and numMenu!=4 and numMenu!=5 and numMenu!=9){                                                                                  //INFORMA SE O VALOR ATRIBUÍDO PARA numMenu FOR INVÁLIDO.
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			printf("\nNÚMERO INVÁLIDO!\n\n");	
			SetConsoleTextAttribute(hConsole, saved_attributes);
			system("pause");
		}
			else if (numMenu==9)                                                                                                                                                    //CASO numMenu SEJA IGUAL A 9, O PROGRAMA SAIRÁ DO MENU.
				break;
				
		switch(numMenu){                                                                                                                                                            //SWITCH CASE UTILIZADO PARA CONSTRUIR O MENU.
			
			case 1:                                                                                                                                                                 //APRESENTAÇÃO DO MAPA DOS LUGARES PARA O DESTINO SELECIONADO. 
				system("cls");
				printf("O VOÔ PARA %s APRESENTA A SEGUINTE DISPONIBILIADE:\n\n", nomeDestino);
				printf("                      +-------------------------------------------+");
				if(qntAssentos % 2 == 0) {                                                                                                                                           //TABELA PARA UMA QUANTIDADE PAR DE ASSENTOS.
					flag = 0;                                                                                                                                                   //FUNÇÃO QUE IRÁ MOSTRAR OS ASSENTOS.
				}
				showSeats(flag);
				printf("\n\n");
				system("pause");
				break;
				
				
			case 2:                                                                                                                                                                 //EFETUA A RESERVA DE ASSENTOS DISPONÍVEIS ATRAVÉS DE SEUS NÚMEROS.
				system("cls");
				do{                                                                                                                                                                 //CAPTURA E VALIDA O NÚMERO DO ASSENTO, ALÉM DE INFORMAR QUANDO ESTE FOR INVÁLIDO.
					printf("FORNEÇA O NÚMERO DO ASSENTO DISPONÍVEL PARA EFETUAR A RESERVA DO MESMO: ");
					scanf("%d", &numAssento);
					fflush(stdin);
					if(numAssento < 0 or numAssento > qntAssentos or statusLugar[numAssento-1] != 'D'){
						SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
						printf("\nASSENTO INVÁLIDO PARA EFETUAR RESERVA!\n\n");                                                                                                     //INTERAÇÃO COM O USUÁRIO PRA INFORMAR QUE O ASSENTO É INVÁLIDO PARA SER RESERVADO.
						SetConsoleTextAttribute(hConsole, saved_attributes);
					}
				}while(numAssento < 0 or numAssento > qntAssentos or statusLugar[numAssento-1] != 'D');
				statusLugar[numAssento-1] = 'R';                                                                                                                                    //O VETOR statusLugar RECEBE R EM UMA POSIÇÃO EQUIPARADA AO NÚMERO DO ASSENTO ESCOLHIDO.
				numReserva++;                                                                                                                                                       //O NÚMERO ÚNICO DE IDENTIFICAÇÃO É GERADO.
				listaReserva[numAssento-1] = numReserva;                                                                                                                            //O VETOR listaReserva RECEBE O NÚMERO ÚNICO DE IDENTIFICAÇÃO EM UMA POSIÇÃO TAMBÉM EQUIPARADA AO NÚMERO DO ASSENTO ESCOLHIDO.
				
				
				do{                                                                                                                                                                 //COLETA E VALIDA A IDADE DO TITULAR DA PASSAGEM, ALÉM DE POSSIVELMENTE REDUZIR O SEU VALOR EM 50% A DEPENDER DA IDADE DO TITULAR.
					printf("\nQUAL É A IDADE DO TITULAR DA PASSAGEM? ");
					scanf("%d", &idadeComprador);
					fflush(stdin);
					if(idadeComprador<=0 or idadeComprador>124){
						SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
						printf("\nIDADE INVÁLIDA!\n");                                                                                                                              //INTERAÇÃO COM O USUÁRIO PRA INFORMAR QUE A IDADE É INVÁLIDA.
						SetConsoleTextAttribute(hConsole, saved_attributes);
					}
						else if(idadeComprador <= 5){
							valorReservas[numAssento-1] = valorPassagem * 0.5;                                                                                                      //CASO A IDADE SEJA MENOR OU IGUAL A 5, 50% DO VALOR DA PASSAGEM É ARMAZENADO NO VETOR valorReservas EM UM ÍNDICE PAREÁVEL AO ASSENTO E NÚMERO ÚNICO DE IDENTIFICAÇÃO.
							SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
							printf("\nEM RAZÃO DA IDADE, O VALOR DA PASSAGEM RECEBE UM DESCONTO de 50%% E PASSA A SER %.2f.\n", valorPassagem * 0.5);                               
							SetConsoleTextAttribute(hConsole, saved_attributes);
						}
							else{                                                                                                                                                   //CASO A IDADE SEJA MAIOR QUE 5, O VALOR DA PASSAGEM É ARMAZENADO NO VETOR valorReservas EM UM ÍNDICE PAREÁVEL AO ASSENTO E NÚMERO ÚNICO DE IDENTIFICAÇÃO.
								valorReservas[numAssento-1] = valorPassagem;
							}
				}while(idadeComprador<=0 or idadeComprador>124);
				
				contadorR=0;                                                                                                                                                        //ATRIBUI VALOR NULO PARA A VARIAVEL contadorR.
				for(i=0;i<qntAssentos;i++){                                                                                                                                         //CONTA A QUANTIDADE DE ASSENTOS RESERVADOS.
					if(statusLugar[i] == 'R')
						contadorR++;
					}
				
				valorTotalReserva = 0;                                                                                                                                              //ATRIBUI VALOR NULO PARA A VARIAVEL valorTotalReserva.
				for(i=0;i<qntAssentos;i++){                                                                                                                                         //SOMA O VALOR DE TODAS AS RESERVAS E GUARDA O RESULTADO NA VARIALVEL valorTotalReserva.
					valorTotalReserva += valorReservas[i]; 
				}
				
				printf("\nO ASSENTO %d FOI RESERVADO! O NÚMERO DA SUA RESERVA É %d.\n", numAssento, numReserva);                                                                    //INFORMA SOBRE O NÚMERO DO ASSENTO E SEU NÚMERO ÚNICO DE RESERVA.
				if(contadorR > 1)
					printf("\nO CLIENTE TEM %d ASSENTOS RESERVADOS, OS QUAIS IRÃO CUSTAR %2.f R$.\n\n", contadorR, valorTotalReserva);                                              //INFORMA O NÚMERO DE ASSENTOS RESERVADOS E O VALOR TOTAL DESSAS RESERVAS PENDENTES.                                               
					else
						printf("\nO CLIENTE TEM %d ASSENTO RESERVADO, O QUAL IRÁ CUSTAR %2.f R$.\n\n", contadorR, valorTotalReserva);                                               //INFORMA O NÚMERO DE ASSENTOS RESERVADOS E O VALOR TOTAL DE UMA RESERVA PENDENTE.
					
				system("pause");
				break;
				
				
			case 3:                                                                                                                                                                 //PERMITE CANCELAR AS RESERVAS.
				system("cls");
				do{                                                                                                                                                                 //CAPTURA E VALIDA O NÚMERO DA RESERVA QUE IRÁ SER CANCELADA, ALÉM DE INFORMAR QUANDO ESTE FOR INVÁLIDO.
					do{
						printf("INSIRA O NÚMERO DA RESERVA A QUAL DESEJA CANCELAR: ");
						scanf("%d", &cancelamentoReserva);
						fflush(stdin);
					}while(cancelamentoReserva <= 0);
					parametroCancelamento = 10000;
					for(i=0;i<200;i++){                                                                                                                                             //ENCONTRA O ÍNDICE NO QUAL O NÚMERO DA RESERVA ESTÁ LOCALIZADO NO VETOR listaReserva.
						if(cancelamentoReserva == listaReserva[i]){
							parametroCancelamento = i;
							break;
						}
					}
					
					
					if(parametroCancelamento == 10000 or statusLugar[parametroCancelamento] != 'R'){                                                                                //INTERAÇÃO COM O USUÁRIO PARA OS CASOS EM QUE O NÚMERO DE RESERVA FOR INVÁLIDO.
						SetConsoleTextAttribute(hConsole, FOREGROUND_RED); 
						printf("\nINFORME UM NÚMERO DE RESERVA EXISTENTE!\n\n");
						SetConsoleTextAttribute(hConsole, saved_attributes);
					}
						else{
							statusLugar[parametroCancelamento] = 'D';                                                                                                               //O ASSENTO PASSA A SER DISPONÍVEL.
							valorReservas[parametroCancelamento] = 0;                                                                                                               //O VALOR DA RESERVA CANCELADA DEIXA DE SER COMPUTADO.
							SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);                                                                                                     
							printf("\nA RESERVA FOI CANCELADA!\n\n");                                                                                                               //CONFIRMAÇÃO DO CANCELAMENTO.
							SetConsoleTextAttribute(hConsole, saved_attributes);							
						}
				}while(parametroCancelamento == 10000 or statusLugar[parametroCancelamento] != 'D');
				
				system("pause");
				break;
				
				
			case 4:                                                                                                                                                                 //PERMITE EFETIVAR A CONFIRMAÇÃO DAS RESERVAS.
				system("cls");
				do{                                                                                                                                                                 //CAPTURA E VALIDA O NÚMERO DA RESERVA QUE IRÁ SER CONFIRMADA, ALÉM DE INFORMAR QUANDO ESTE FOR INVÁLIDO.
					do{
						printf("INSIRA O NÚMERO DA RESERVA A QUAL DESEJA EFETIVAR A CONFIRMAÇÃO: ");
						scanf("%d", &efetivaReserva);
						fflush(stdin);
					}while(efetivaReserva <= 0);
					parametroEfetivacao = 10000;
					for(i=0;i<200;i++){                                                                                                                                             //ENCONTRA O ÍNDICE NO QUAL O NÚMERO DA RESERVA ESTÁ LOCALIZADO NO VETOR listaReserva.
						if(efetivaReserva == listaReserva[i]){
							parametroEfetivacao = i;
							break;
						}
					}
					if(parametroEfetivacao == 10000 or statusLugar[parametroEfetivacao] != 'R'){                                                                                    //INTERAÇÃO COM O USUÁRIO PARA OS CASOS EM QUE O NÚMERO DE RESERVA FOR INVÁLIDO.
						SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
						printf("\nINFORME UM NÚMERO DE RESERVA EXISTENTE!\n\n");
						SetConsoleTextAttribute(hConsole, saved_attributes);
					}
						else{
							statusLugar[parametroEfetivacao] = 'C';                                                                                                                 //O ASSENTO PASSA A SER CONFIRMADO.
							valorEfetivadas[parametroEfetivacao] = valorReservas[parametroEfetivacao];                                                                              //OS VALORES DAS RESERVAS CONFIRMADAS SÃO ARMAZENADOS NO VETOR valorEfetivadas.
							valorReservas[parametroEfetivacao] = 0;                                                                                                                 //O VALOR DA RESERVA CONFIRMADA DEIXA DE SER COMPUTADO COMO VALOR DE UMA RESERVA.
							SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
							printf("\nA RESERVA FOI EFETIVADA!\n\n");
							SetConsoleTextAttribute(hConsole, saved_attributes);
						}
				}while(parametroEfetivacao == 10000 or statusLugar[parametroEfetivacao] != 'C');
				
				system("pause");
				break;
				
				
			case 5:                                                                                                                                                                  //FORNECE INFORMAÇÕES SOBRE O ESTADO DOS ASSENTOS E O VALOR TOTAL DAS VENDAS CONFIRMADAS.
				system("cls");
				contadorR=0;                                                                                                                                                         
				contadorD=0;                                                                                                                                                         //OS CONTADORES SÃO ZERADOS.
				contadorC=0;
				for(i=0;i<qntAssentos;i++){                                                                                                                                          //CONTA A QUANTIDADE DE ASSENTOS DISPONÍVEIS, RESERVADOS E CONFIRMADOS.
					if(statusLugar[i] == 'D')
						contadorD++;
						else if(statusLugar[i] == 'R')
							contadorR++;
							else
								contadorC++;
				}
				
				valorTotalEfetivada = 0;
				for(i=0;i<qntAssentos;i++){                                                                                                                                          //SOMA O VALOR DE TODAS AS RESERVAS EFETIVADAS E ARMAZENA O RESULTADO DENTRO DA VARIÁVEL valorTotalEfetivada. 
					if(valorEfetivadas[i] != 0){
						valorTotalEfetivada = valorTotalEfetivada + valorEfetivadas[i]; 
				}
				}
				
				printf("QUANTIDADE DE ASSENTOS DISPONÍVEIS: %d\n \nQUANTIDADE DE ASSENTOS COM RESERVA: %d\n \nQUANTIDADE DE ASSENTOS COM VENDAS CONFIRMADAS: %d\n \n", contadorD, contadorR, contadorC);
				printf("O VALOR TOTAL EM REAIS COM AS VENDAS JÁ CONFIRMADAS PARA %s É %.2f R$.\n\n", nomeDestino, valorTotalEfetivada);

				system("pause");
				break;
		}
	}while(numMenu!=9);
	
	system("cls");
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);                                                                                                                          
	printf("+----------------------------------------------------------------------------------------------------------------------+");
	printf("|-------------------------------OBRIGADO POR UTILIZAR OS NOSSOS SERVIÇOS, VOLTE SEMPRE!--------------------------------|");                                                //DESPEDIDA DESTINADA AO USUÁRIO.
	printf("+----------------------------------------------------------------------------------------------------------------------+\n");
	SetConsoleTextAttribute(hConsole, saved_attributes);                                                                            
	
	return 0;                                                                                                                                                                          //RETORNA 0 AO FIM DA FUNÇÃO int main(), EVITANDO BUGS COM O ENCERRAMENTO DO PROGRAMA.
}

void showSeats(int c) {
	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);                                                                                                                            
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;                                                                                                                                       
    WORD saved_attributes;                                                                                                                                                        

    /* Salvar estado atual da configuração das cores*/
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;                                                                                                                                 
	
	for(i=1;i<qntAssentos + c;i+=2){                                                                                                                                  
		printf("\n                      |     LUGAR %d: ", i);
		if(statusLugar[i-1] == 'D'){                                                                                                                                
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
			printf("%c ", statusLugar[i-1]);
			SetConsoleTextAttribute(hConsole, saved_attributes);
		}
			else if(statusLugar[i-1] == 'R'){                                                                                                                       //OS LUGARES RESERVADOS SERÃO APRESENTADOS NA COR VERMELHA.
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
				printf("%c ", statusLugar[i-1]);
				SetConsoleTextAttribute(hConsole, saved_attributes);
			}
				else{                                                                                                                                               //OS LUGARES CONFIRMADOS SERÃO APRESENTADOS NA COR AZUL.
					SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
					printf("%c ", statusLugar[i-1]);
					SetConsoleTextAttribute(hConsole, saved_attributes);
				}
								
						
		if(i < 10)                                                                                                                                                  //ORGANIZANDO E CRIANDO OS COMPONENTES DA TABELA.		
			printf("     ||    LUGAR %d: ", i+1);
			else if(i > qntAssentos - 1 and i < 100)	
				printf("    ||                ");
				else if(i < 100)
					printf("    ||    LUGAR %d: ", i+1);
					else if(i == 100)
						printf("   ||    LUGAR %d: ", i+1);
						else if(i > qntAssentos - 1)
							printf("   ||                 ");
							else
								printf("   ||    LUGAR %d: ", i+1);	
										
											
		if( i < qntAssentos ) {
			if(statusLugar[i] == 'D'){                                                                                                                                  //OS LUGARES DISPONÍVEIS SERÃO APRESENTADOS NA COR VERDE.
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
			printf("%c ", statusLugar[i]);
			SetConsoleTextAttribute(hConsole, saved_attributes);
			}
				else if(statusLugar[i] == 'R'){                                                                                                                         //OS LUGARES RESERVADOS SERÃO APRESENTADOS NA COR VERMELHA.
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
					printf("%c ", statusLugar[i]);
					SetConsoleTextAttribute(hConsole, saved_attributes);
				}
					else{                                                                                                                                               //OS LUGARES CONFIRMADOS SERÃO APRESENTADOS NA COR AZUL.
						SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
						printf("%c ", statusLugar[i]);
						SetConsoleTextAttribute(hConsole, saved_attributes);
					}
		}									
			
								
		if(i+1 < 9)                                                                                                                                                 //ORGANIZANDO E CRIANDO OS COMPONENTES DA TABELA.
			printf("     |");
			else if(i+1 == 10)
				printf("    |");
				else if(i+1 < 100)
					printf("    |");
					else if(i+1 == 100)
						printf("   |");
						else
							printf("   |");	
						
						printf("\n                      +-------------------------------------------+");
	}
}

