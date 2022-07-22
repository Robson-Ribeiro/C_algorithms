#include<windows.h>         //DENTRE V�RIA FUN��ES, PERMITE MUDAR A COR DO TEXTO COM O QUAL O USU�RIO TEM CONTATO. N�O FOI APLICADO POR GERAR PROBLEMAS COM O COMANDO SCANF().
#include<ctype.h>          //CONT�M DECLARA��ES PARA MANIPULA��O DE CARACTERES. EX: isdigit().
#include<conio.h>         //getch(), getchar() & getche().
#include<string.h>       //CONT�M UMA S�RIE DE FUN��ES PARA MANIPULAR STRINGS, VINDO DELA O COMANDO "strcmp()" QUE COMPARA STRINGS.
#include<stdlib.h>      //BIBLIOTECA PADR�O QUE TRAZ DIVERSOS COMANDOS, COMO "system("cls");" QUE FOI UTILIZADO NESTE ALGORITIMO PARA LIMPAR O PROMPT. 
#include<locale.h>     //LOCALIZA��O DE PROGRAMAS E ACENTUA��O.
#include<stdio.h>     //BIBLIOTECA DE ENTRADA (scanf(), fgets(), etc.) E SA�DA (printf()).

// Declara��o
char nomeDestino[30], nomeDestinoVerif, statusLugar[200];
int qntAssentos, idadeComprador, numMenu, i, numAssento, numReserva=0, listaReserva[200], cancelamentoReserva, parametroCancelamento, efetivaReserva, parametroEfetivacao;
int contadorR, contadorC=0, contadorD=0, flag = 1;
float valorPassagem, valorTotalReserva, valorReservas[200], valorEfetivadas[200], valorTotalEfetivada;

// PROTOTIPA��O
void showSeats(int c);

int main(){                                                                                                                                                                       //FUN��O PRINCIPAL DE UM PROGRAMA EM C/C++. � ONDE O PROGRAMA COME�A.
	setlocale(LC_ALL, "Portuguese");                                                                                                                                              //AJUSTA O PROGRAMA PARA PORTUGU�S.
	
	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);                                                                                                                            
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;                                                                                                                                       //C�DIGOS ADVINDOS DA BIBLIOTECA WINDOWS.H QUE PERMITEM ALTERAR A COR DOS DADOS DE SA�DA.
    WORD saved_attributes;                                                                                                                                                        //LOCAL QUE IR� ARMAZENAR A CONFIGURA��O PADR�O DE CORES.

    /* Salvar estado atual da configura��o das cores*/
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;                                                                                                                                   //SALVA A CONFIGURA��O PADR�O DE CORES.
	
	//system("color 0D");                             
	//SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);                                                                                                                          //MUDA A COR DO TEXTO PRINTADO PARA VERDE.
	printf("+----------------------------------------------------------------------------------------------------------------------+");
	printf("|--------------------------------------BEM VINDO � EMPRESA EMIRATES LINHAS A�REAS!-------------------------------------|");                                           //BOAS VINDAS.
	printf("+----------------------------------------------------------------------------------------------------------------------+\n");
	SetConsoleTextAttribute(hConsole, saved_attributes);                                                                                                                          //RETORNA PARA A CONFIGURA��O PADR�O DE CORES.

	
	for(i=0;i<=200;i++){                                                                                                                                                           //ESTRUTURAS DE REPETI��O FOR UTILIZADAS PARA POPULAR TODOS OS VALORES DE DETERMINADOS VETORES.
		statusLugar[i] = 'D';
		listaReserva[i] = 0;
		valorReservas[i] = 0;
		valorEfetivadas[i] = 0;
	}

	
	//ENTRADA
	do{                                                                                                                                                                             //COLETA O NOME DO DESTINO DA VIAGEM, AL�M DE REALIZAR AS DEVIDAS VALIDA��ES E INFORMAR QUANDO O VALOR FOR INV�LIDO.
		printf("INFORME O NOME DO DESTINO PARA O QUAL DESEJA VIAJAR: ");
		fgets(nomeDestino, 30, stdin);
		fflush(stdin);
		nomeDestinoVerif = nomeDestino[0];
		if(strcmp(("%s", nomeDestino), "") == 0 or isspace(nomeDestinoVerif) == 8){
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);                                                                                                                      //MUDA A COR DO TEXTO PRINTADO PARA VERMELHO.
			printf("\nNOMES NULOS S�O INV�LIDOS!\n\n");
			SetConsoleTextAttribute(hConsole, saved_attributes);                                                                                                                    //RETORNA PARA A CONFIGURA��O PADR�O DE CORES.
		}
	}while(strcmp(("%s", nomeDestino), "") == 0 or isspace(nomeDestinoVerif) == 8);
	
	
	for(i=0;i<30;i++){
		nomeDestino[i] = toupper(nomeDestino[i]);                                                                                                                                   //DETERMINA TODOS OS CARACTERES DA VARI�VEL NOMEDESTINO COMO MAI�SCULOS.	
	}
	
	
	do{                                                                                                                                                                             //COLETA O VALOR DA PASSAGEM, AL�M DE REALIZAR AS DEVIDAS VALIDA��ES E INFORMAR QUANDO O VALOR FOR INV�LIDO.
		printf("\nINFORME O VALOR DA PASSAGEM: ");
		scanf("%f", &valorPassagem);
		fflush(stdin);
		if(valorPassagem <= 0){
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			printf("\nESSE VALOR � INV�LIDO!\n");
			SetConsoleTextAttribute(hConsole, saved_attributes);
		}
	}while(valorPassagem <= 0);
	
	
	do{                                                                                                                                                                             //COLETA O N�MERO DE ASSENTOS EXISTENTES, AL�M DE REALIZAR AS DEVIDAS VALIDA��ES E INFORMAR QUANDO O VALOR FOR INV�LIDO.
		printf("\nQUAL � A QUANTIDADE DE ASSENTOS EXISTENTES PARA O AVI�O SELECIONADO PARA O SEU DESTINO? ");
		scanf("%d", &qntAssentos);
		fflush(stdin);
		if(qntAssentos < 90 or qntAssentos > 200){
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			printf("\nA QUANTIDADE DE ASSENTOS DOS AVI�ES DA EMPRESA SER� SEMPRE MAIOR OU IGUAL A 90 ASSENTOS, MAS N�O ULTRAPASSAR� 200!\n");
			SetConsoleTextAttribute(hConsole, saved_attributes);
		}
	}while(qntAssentos < 90 or qntAssentos > 200);
	
	
	printf("\n");
	system("pause");                                                                                                                                                                //PAUSA O SISTEMA AT� QUE SE APERTE UMA TECLA QUALQUER.
	
	
	//MENU
	do{                                                                                                                                                                             //GARANTE A CONTINUIDADE NO MENU AT� QUE SE INSIRA O D�GITO 9 NO PR�XIMO SCANF().
		system("cls");                                                                                                                                                              //COMANDO PARA LIMPAR A JANELA (PROMPT DE COMANDO).
		printf("DIGITE UM N�MERO CORRELATO COM A FUNCIONALIDADE QUE DESEJA USAR:\n\n1-VERIFICAR A OCUPA��O DO VO�\n \n2-EFETUAR UMA RESERVA POR MEIO DO FORNECIMENTO DO N�MERO DO ASSENTO DISPON�VEL\n \n3-REALIZAR O CANCELAMENTO DE UMA RESERVA POR MEIO DO FORNECIMENTO DE SEU N�MERO �NICO DE IDENTIFICA��O\n \n4-EFETIVAR A CONFIRMA��O DE VENDA\n \n5-MOSTRAR A QUANTIDADE DE ASSENTOS COM RESERVAS, COM VENDAS CONFIRMADAS E DISPON�VEIS, AL�M DO VALOR TOTAL EM REAIS COM AS VENDAS J� CONFIRMADAS\n \n9-FINALIZAR!\n");
		scanf("%d", &numMenu);                                                                                                                                                      //CAPTURA UM VALOR INTEIRO PARA numMenu.
		fflush(stdin);                                                                                                                                                              
		if(numMenu!=1 and numMenu!=2 and numMenu!=3 and numMenu!=4 and numMenu!=5 and numMenu!=9){                                                                                  //INFORMA SE O VALOR ATRIBU�DO PARA numMenu FOR INV�LIDO.
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			printf("\nN�MERO INV�LIDO!\n\n");	
			SetConsoleTextAttribute(hConsole, saved_attributes);
			system("pause");
		}
			else if (numMenu==9)                                                                                                                                                    //CASO numMenu SEJA IGUAL A 9, O PROGRAMA SAIR� DO MENU.
				break;
				
		switch(numMenu){                                                                                                                                                            //SWITCH CASE UTILIZADO PARA CONSTRUIR O MENU.
			
			case 1:                                                                                                                                                                 //APRESENTA��O DO MAPA DOS LUGARES PARA O DESTINO SELECIONADO. 
				system("cls");
				printf("O VO� PARA %s APRESENTA A SEGUINTE DISPONIBILIADE:\n\n", nomeDestino);
				printf("                      +-------------------------------------------+");
				if(qntAssentos % 2 == 0) {                                                                                                                                           //TABELA PARA UMA QUANTIDADE PAR DE ASSENTOS.
					flag = 0;                                                                                                                                                   //FUN��O QUE IR� MOSTRAR OS ASSENTOS.
				}
				showSeats(flag);
				printf("\n\n");
				system("pause");
				break;
				
				
			case 2:                                                                                                                                                                 //EFETUA A RESERVA DE ASSENTOS DISPON�VEIS ATRAV�S DE SEUS N�MEROS.
				system("cls");
				do{                                                                                                                                                                 //CAPTURA E VALIDA O N�MERO DO ASSENTO, AL�M DE INFORMAR QUANDO ESTE FOR INV�LIDO.
					printf("FORNE�A O N�MERO DO ASSENTO DISPON�VEL PARA EFETUAR A RESERVA DO MESMO: ");
					scanf("%d", &numAssento);
					fflush(stdin);
					if(numAssento < 0 or numAssento > qntAssentos or statusLugar[numAssento-1] != 'D'){
						SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
						printf("\nASSENTO INV�LIDO PARA EFETUAR RESERVA!\n\n");                                                                                                     //INTERA��O COM O USU�RIO PRA INFORMAR QUE O ASSENTO � INV�LIDO PARA SER RESERVADO.
						SetConsoleTextAttribute(hConsole, saved_attributes);
					}
				}while(numAssento < 0 or numAssento > qntAssentos or statusLugar[numAssento-1] != 'D');
				statusLugar[numAssento-1] = 'R';                                                                                                                                    //O VETOR statusLugar RECEBE R EM UMA POSI��O EQUIPARADA AO N�MERO DO ASSENTO ESCOLHIDO.
				numReserva++;                                                                                                                                                       //O N�MERO �NICO DE IDENTIFICA��O � GERADO.
				listaReserva[numAssento-1] = numReserva;                                                                                                                            //O VETOR listaReserva RECEBE O N�MERO �NICO DE IDENTIFICA��O EM UMA POSI��O TAMB�M EQUIPARADA AO N�MERO DO ASSENTO ESCOLHIDO.
				
				
				do{                                                                                                                                                                 //COLETA E VALIDA A IDADE DO TITULAR DA PASSAGEM, AL�M DE POSSIVELMENTE REDUZIR O SEU VALOR EM 50% A DEPENDER DA IDADE DO TITULAR.
					printf("\nQUAL � A IDADE DO TITULAR DA PASSAGEM? ");
					scanf("%d", &idadeComprador);
					fflush(stdin);
					if(idadeComprador<=0 or idadeComprador>124){
						SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
						printf("\nIDADE INV�LIDA!\n");                                                                                                                              //INTERA��O COM O USU�RIO PRA INFORMAR QUE A IDADE � INV�LIDA.
						SetConsoleTextAttribute(hConsole, saved_attributes);
					}
						else if(idadeComprador <= 5){
							valorReservas[numAssento-1] = valorPassagem * 0.5;                                                                                                      //CASO A IDADE SEJA MENOR OU IGUAL A 5, 50% DO VALOR DA PASSAGEM � ARMAZENADO NO VETOR valorReservas EM UM �NDICE PARE�VEL AO ASSENTO E N�MERO �NICO DE IDENTIFICA��O.
							SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
							printf("\nEM RAZ�O DA IDADE, O VALOR DA PASSAGEM RECEBE UM DESCONTO de 50%% E PASSA A SER %.2f.\n", valorPassagem * 0.5);                               
							SetConsoleTextAttribute(hConsole, saved_attributes);
						}
							else{                                                                                                                                                   //CASO A IDADE SEJA MAIOR QUE 5, O VALOR DA PASSAGEM � ARMAZENADO NO VETOR valorReservas EM UM �NDICE PARE�VEL AO ASSENTO E N�MERO �NICO DE IDENTIFICA��O.
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
				
				printf("\nO ASSENTO %d FOI RESERVADO! O N�MERO DA SUA RESERVA � %d.\n", numAssento, numReserva);                                                                    //INFORMA SOBRE O N�MERO DO ASSENTO E SEU N�MERO �NICO DE RESERVA.
				if(contadorR > 1)
					printf("\nO CLIENTE TEM %d ASSENTOS RESERVADOS, OS QUAIS IR�O CUSTAR %2.f R$.\n\n", contadorR, valorTotalReserva);                                              //INFORMA O N�MERO DE ASSENTOS RESERVADOS E O VALOR TOTAL DESSAS RESERVAS PENDENTES.                                               
					else
						printf("\nO CLIENTE TEM %d ASSENTO RESERVADO, O QUAL IR� CUSTAR %2.f R$.\n\n", contadorR, valorTotalReserva);                                               //INFORMA O N�MERO DE ASSENTOS RESERVADOS E O VALOR TOTAL DE UMA RESERVA PENDENTE.
					
				system("pause");
				break;
				
				
			case 3:                                                                                                                                                                 //PERMITE CANCELAR AS RESERVAS.
				system("cls");
				do{                                                                                                                                                                 //CAPTURA E VALIDA O N�MERO DA RESERVA QUE IR� SER CANCELADA, AL�M DE INFORMAR QUANDO ESTE FOR INV�LIDO.
					do{
						printf("INSIRA O N�MERO DA RESERVA A QUAL DESEJA CANCELAR: ");
						scanf("%d", &cancelamentoReserva);
						fflush(stdin);
					}while(cancelamentoReserva <= 0);
					parametroCancelamento = 10000;
					for(i=0;i<200;i++){                                                                                                                                             //ENCONTRA O �NDICE NO QUAL O N�MERO DA RESERVA EST� LOCALIZADO NO VETOR listaReserva.
						if(cancelamentoReserva == listaReserva[i]){
							parametroCancelamento = i;
							break;
						}
					}
					
					
					if(parametroCancelamento == 10000 or statusLugar[parametroCancelamento] != 'R'){                                                                                //INTERA��O COM O USU�RIO PARA OS CASOS EM QUE O N�MERO DE RESERVA FOR INV�LIDO.
						SetConsoleTextAttribute(hConsole, FOREGROUND_RED); 
						printf("\nINFORME UM N�MERO DE RESERVA EXISTENTE!\n\n");
						SetConsoleTextAttribute(hConsole, saved_attributes);
					}
						else{
							statusLugar[parametroCancelamento] = 'D';                                                                                                               //O ASSENTO PASSA A SER DISPON�VEL.
							valorReservas[parametroCancelamento] = 0;                                                                                                               //O VALOR DA RESERVA CANCELADA DEIXA DE SER COMPUTADO.
							SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);                                                                                                     
							printf("\nA RESERVA FOI CANCELADA!\n\n");                                                                                                               //CONFIRMA��O DO CANCELAMENTO.
							SetConsoleTextAttribute(hConsole, saved_attributes);							
						}
				}while(parametroCancelamento == 10000 or statusLugar[parametroCancelamento] != 'D');
				
				system("pause");
				break;
				
				
			case 4:                                                                                                                                                                 //PERMITE EFETIVAR A CONFIRMA��O DAS RESERVAS.
				system("cls");
				do{                                                                                                                                                                 //CAPTURA E VALIDA O N�MERO DA RESERVA QUE IR� SER CONFIRMADA, AL�M DE INFORMAR QUANDO ESTE FOR INV�LIDO.
					do{
						printf("INSIRA O N�MERO DA RESERVA A QUAL DESEJA EFETIVAR A CONFIRMA��O: ");
						scanf("%d", &efetivaReserva);
						fflush(stdin);
					}while(efetivaReserva <= 0);
					parametroEfetivacao = 10000;
					for(i=0;i<200;i++){                                                                                                                                             //ENCONTRA O �NDICE NO QUAL O N�MERO DA RESERVA EST� LOCALIZADO NO VETOR listaReserva.
						if(efetivaReserva == listaReserva[i]){
							parametroEfetivacao = i;
							break;
						}
					}
					if(parametroEfetivacao == 10000 or statusLugar[parametroEfetivacao] != 'R'){                                                                                    //INTERA��O COM O USU�RIO PARA OS CASOS EM QUE O N�MERO DE RESERVA FOR INV�LIDO.
						SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
						printf("\nINFORME UM N�MERO DE RESERVA EXISTENTE!\n\n");
						SetConsoleTextAttribute(hConsole, saved_attributes);
					}
						else{
							statusLugar[parametroEfetivacao] = 'C';                                                                                                                 //O ASSENTO PASSA A SER CONFIRMADO.
							valorEfetivadas[parametroEfetivacao] = valorReservas[parametroEfetivacao];                                                                              //OS VALORES DAS RESERVAS CONFIRMADAS S�O ARMAZENADOS NO VETOR valorEfetivadas.
							valorReservas[parametroEfetivacao] = 0;                                                                                                                 //O VALOR DA RESERVA CONFIRMADA DEIXA DE SER COMPUTADO COMO VALOR DE UMA RESERVA.
							SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
							printf("\nA RESERVA FOI EFETIVADA!\n\n");
							SetConsoleTextAttribute(hConsole, saved_attributes);
						}
				}while(parametroEfetivacao == 10000 or statusLugar[parametroEfetivacao] != 'C');
				
				system("pause");
				break;
				
				
			case 5:                                                                                                                                                                  //FORNECE INFORMA��ES SOBRE O ESTADO DOS ASSENTOS E O VALOR TOTAL DAS VENDAS CONFIRMADAS.
				system("cls");
				contadorR=0;                                                                                                                                                         
				contadorD=0;                                                                                                                                                         //OS CONTADORES S�O ZERADOS.
				contadorC=0;
				for(i=0;i<qntAssentos;i++){                                                                                                                                          //CONTA A QUANTIDADE DE ASSENTOS DISPON�VEIS, RESERVADOS E CONFIRMADOS.
					if(statusLugar[i] == 'D')
						contadorD++;
						else if(statusLugar[i] == 'R')
							contadorR++;
							else
								contadorC++;
				}
				
				valorTotalEfetivada = 0;
				for(i=0;i<qntAssentos;i++){                                                                                                                                          //SOMA O VALOR DE TODAS AS RESERVAS EFETIVADAS E ARMAZENA O RESULTADO DENTRO DA VARI�VEL valorTotalEfetivada. 
					if(valorEfetivadas[i] != 0){
						valorTotalEfetivada = valorTotalEfetivada + valorEfetivadas[i]; 
				}
				}
				
				printf("QUANTIDADE DE ASSENTOS DISPON�VEIS: %d\n \nQUANTIDADE DE ASSENTOS COM RESERVA: %d\n \nQUANTIDADE DE ASSENTOS COM VENDAS CONFIRMADAS: %d\n \n", contadorD, contadorR, contadorC);
				printf("O VALOR TOTAL EM REAIS COM AS VENDAS J� CONFIRMADAS PARA %s � %.2f R$.\n\n", nomeDestino, valorTotalEfetivada);

				system("pause");
				break;
		}
	}while(numMenu!=9);
	
	system("cls");
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);                                                                                                                          
	printf("+----------------------------------------------------------------------------------------------------------------------+");
	printf("|-------------------------------OBRIGADO POR UTILIZAR OS NOSSOS SERVI�OS, VOLTE SEMPRE!--------------------------------|");                                                //DESPEDIDA DESTINADA AO USU�RIO.
	printf("+----------------------------------------------------------------------------------------------------------------------+\n");
	SetConsoleTextAttribute(hConsole, saved_attributes);                                                                            
	
	return 0;                                                                                                                                                                          //RETORNA 0 AO FIM DA FUN��O int main(), EVITANDO BUGS COM O ENCERRAMENTO DO PROGRAMA.
}

void showSeats(int c) {
	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);                                                                                                                            
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;                                                                                                                                       
    WORD saved_attributes;                                                                                                                                                        

    /* Salvar estado atual da configura��o das cores*/
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;                                                                                                                                 
	
	for(i=1;i<qntAssentos + c;i+=2){                                                                                                                                  
		printf("\n                      |     LUGAR %d: ", i);
		if(statusLugar[i-1] == 'D'){                                                                                                                                
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
			printf("%c ", statusLugar[i-1]);
			SetConsoleTextAttribute(hConsole, saved_attributes);
		}
			else if(statusLugar[i-1] == 'R'){                                                                                                                       //OS LUGARES RESERVADOS SER�O APRESENTADOS NA COR VERMELHA.
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
				printf("%c ", statusLugar[i-1]);
				SetConsoleTextAttribute(hConsole, saved_attributes);
			}
				else{                                                                                                                                               //OS LUGARES CONFIRMADOS SER�O APRESENTADOS NA COR AZUL.
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
			if(statusLugar[i] == 'D'){                                                                                                                                  //OS LUGARES DISPON�VEIS SER�O APRESENTADOS NA COR VERDE.
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
			printf("%c ", statusLugar[i]);
			SetConsoleTextAttribute(hConsole, saved_attributes);
			}
				else if(statusLugar[i] == 'R'){                                                                                                                         //OS LUGARES RESERVADOS SER�O APRESENTADOS NA COR VERMELHA.
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
					printf("%c ", statusLugar[i]);
					SetConsoleTextAttribute(hConsole, saved_attributes);
				}
					else{                                                                                                                                               //OS LUGARES CONFIRMADOS SER�O APRESENTADOS NA COR AZUL.
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

