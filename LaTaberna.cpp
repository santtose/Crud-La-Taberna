#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>
#include "auxiliar.h"
#define MAX 20

typedef struct{ //struct de produtos
	char nome[50], descricao[200], cor[20], fornecedor[50], efeito[50];
	int categoria, ativo;
	float valor;
}Cadastro;
Cadastro cadastros[MAX];

typedef struct{ //struct de itens do pedido
	char nome[50];
	int id, quantidade, ativo;
	float valor;
}Venda;
Venda v[MAX];

//declaracao de todas as funcoes
void cadastroAutomatico();
void menu();
void venda();
void cadastrar();
void remover();
void pesquisar();
void listar();
void listarCat(int cat);
float carrinho(int item);
void aguardandoPagamento();

int main()
{
	cadastroAutomatico();// funcao que cadastra alguns itens pra que a lista nao fique vazia
	menu();// funcao menu chamada logo que inicia o sistema
	return 0;
}

// funcado menu chamada logo que inicia o sistema
void menu(){
	int op;
	do{
		system("cls");
		printf("######################################################################\n");
		printf("#                                                                    #\n");
		printf("#        LLL           AAAAA                                         #\n");
		printf("#        LLL          AAA  AAA                                       #\n");
		printf("#        LLL         AAA    AAA                                      #\n");
		printf("#        LLL         AAA    AAA                                      #\n");
		printf("#        LLL         AAAAAAAAAA                                      #\n");
		printf("#        LLL         AAAAAAAAAA                                      #\n");
		printf("#        LLLLLLLLL   AAA    AAA                                      #\n");
		printf("#        LLLLLLLLL   AAA    AAA                                      #\n");
		printf("#                                                                    #\n");
		printf("#           TTTTTTT  AAAAA   BBBBB   EEEEEE RRRRR  NN   NN   AAAAA   #\n");
		printf("#             TT    AA   AA  BB  BB  EE     RR  RR NNN  NN  AA   AA  #\n");
		printf("#             TT    AAAAAAA  BBBBBB  EEE    RRRR   NN N NN  AAAAAAA  #\n");
		printf("#             TT    AA   AA  BB   BB EE     RR RR  NN  NNN  AA   AA  #\n");
		printf("#             TT    AA   AA  BBBBBB  EEEEEE RR  RR NN   NN  AA   AA  #\n");
		printf("#                                                                    #\n");
		printf("#   1 - Cadastrar produto                                            #\n");
		printf("#   2 - Remover produto                                              #\n");
		printf("#   3 - Pesquisar produto                                            #\n");
		printf("#   4 - Listar produtos                                              #\n");
		printf("#   5 - Fazer uma Venda                                              #\n");
		printf("#                                                                    #\n");
		printf("#   0 - Sair                                                         #\n");
		printf("#                                                                    #\n");
		printf("#                                                                    #\n");
		printf("#                                                                    #\n");
		printf("######################################################################\n");
		scanf("%i",&op); //Captura opção do usuario
		getchar();  //Limpa buffer
		switch(op){
			case 1:
				cadastrar();
			break;
			case 2:
				remover();
			break;
			case 3:
				pesquisar();
			break;
			case 4:
				listar();
			break;
			case 5:
				venda();
			break;
			case 0:
				system("cls");
				printf("Obrigado por utilizar nosso sistema!");
				Sleep(3000);
			break;
			default:
				system("cls");
				printf("Opção não reconhecida, tente digitar 0 se quiser sair!");
				Sleep(3000);
			break;
		}
	}while(op!=0);
}

// opcao 5 do menu principal
void venda(){
	char nome[50];
	int quantidade, op, it, finaliza;
	float valor, valorTotal;
	
	setlocale(LC_ALL,"portuguese");
	
	system("cls");
		printf("####################################################################\n");
		printf("#                                                                  #\n");
		printf("#                                                                  #\n");
		printf("#                                                                  #\n");
		printf("#     ------------Escolha uma categoria de produtos-------------   #\n");
		printf("#                                                                  #\n");
		printf("#   1 - Bebidas                                                    #\n");
		printf("#   2 - Comidas                                                    #\n");
		printf("#   3 - Poções Mágicas                                             #\n");
		printf("#                                                                  #\n");
		printf("#   0 - Sair                                                       #\n");
		printf("#                                                                  #\n");
		printf("#                                                                  #\n");
		printf("#                                                                  #\n");
		printf("####################################################################\n");
		scanf("%i",&op);
		getchar();  //Limpa buffer
	do{
		listarCat(op); // lista somente itens da categoria escolhida
		printf("\nEscolha pelo ID do item ou 0 para voltar ao menu anterior: \n");
		scanf("%i", &it);
		valorTotal = valorTotal + carrinho(it);//funcao do carrinho que adiciona itens e faz o calculo do saldo devedor pra mostrar na sequencia
		
		system("cls");
		printf("####################################################################\n");
		printf("------------Seu carrinho até o momento esta em R$ %.2f------------- \n", valorTotal); //mostra valor gasto ate agora e da menu de opcoes novamente
		printf("####################################################################\n");
		printf("####################################################################\n");
		printf("#                                                                  #\n");
		printf("#                                                                  #\n");
		printf("#                                                                  #\n");
		printf("#     ------------Escolha uma categoria de produtos-------------   #\n");
		printf("#                                                                  #\n");
		printf("#   1 - Bebidas                                                    #\n");
		printf("#   2 - Comidas                                                    #\n");
		printf("#   3 - Poções Mágicas                                             #\n");
		printf("#                                                                  #\n");
		printf("#   0 - Sair e Finalizar                                           #\n");
		printf("#                                                                  #\n");
		printf("#                                                                  #\n");
		printf("#                                                                  #\n");
		printf("####################################################################\n");
		scanf("%i",&op);
		getchar();  //Limpa buffer
	}while(op!=0);
	
	if(valorTotal != 0){
		printf("Deseja finalizar a compra 1 para Sim ou 2 para Não?\n");
		scanf("%i", &finaliza);
		if(finaliza == 1 ){
			//imprimir lista de itens
			system("cls");
			printf("####################################################################\n");
			printf("#                    Sua lista de compras:                         #\n");
			printf("####################################################################\n");
			for(int i=0; i<MAX; i++){
				if(v[i].ativo==1){
					fflush(stdin);
					printf("Item: %i Nome: %s -- qtd: %i -- vlr un.: %.2f \n",v[i].id, v[i].nome, v[i].quantidade, v[i].valor);
				}
			}
			printf("\nTOTAL ----------------- %.2f\n", valorTotal);
			printf("####################################################################\n");
			Sleep(10000);
			aguardandoPagamento(); //funcao apenas pra animacao de aguardando pagamento
			for(int j=0; j<MAX; j++){
				if(v[j].ativo==1){
					v[j].ativo = 0;
				}
			}
		}else{
			//limpando array de struct
			printf("Finalizando carrinho sem efetuar a compra\n");
			for(int j=0; j<MAX; j++){
				if(v[j].ativo==1){
					v[j].ativo = 0;
				}
			}
			Sleep(5000);
		}
	}
}

//funcao que mostra o item escolhido, com detalhes e pergunta a quantidade desejada.
float carrinho(int item){
	char nome[50];
	int quant, id, op;
	float valor;
	item = item-1;
	system("cls");
	printf("Produto:\n %s, de cor %s, fornecido por %s \n Descrição: %s\n Valor: R$ %.2f ", cadastros[item].nome, cadastros[item].cor, cadastros[item].fornecedor, cadastros[item].descricao, cadastros[item].valor);
	printf("\n\nEfeito: %s \n", cadastros[item].efeito);
	printf("______________________________________________________");
	printf("\nDigite a quantidade desejada:\n ");
	scanf("%i", &quant);
	valor = quant * cadastros[item].valor;
	strcpy(nome, cadastros[item].nome);
	
	for(int i=0; i<MAX; i++){ //encontra o próximo item do array livre, grava o produto e sai no "break".
		if(v[i].ativo==0)
		{
			strcpy(v[i].nome, nome);
			v[i].quantidade = quant;
			v[i].valor = valor;
			v[i].id = i+1;
			v[i].ativo = 1;
			break;
		}
	}
	return valor;
}

//funcao para cadastro de novo item
void cadastrar(){
	char nome[50], descricao[200], cor[20], fornecedor[50], efeito[50];
	int categoria;
	float valor;
	int op;
	setlocale(LC_ALL,"portuguese");
	do{
		system("cls");
		printf("\nNome: ");
		fgets(nome,sizeof(nome),stdin); //Calcula automáticamente o tamanho da string.
		printf("\nDescrição: ");
		fgets(descricao,sizeof(descricao),stdin);
		printf("\nCor: ");
		fgets(cor,sizeof(cor),stdin);
		printf("\nFornecedor: ");
		fgets(fornecedor,sizeof(fornecedor),stdin);
		printf("\nEfeito: ");
		fgets(efeito,sizeof(efeito),stdin);
		printf("\nCategoria: ");
		scanf("%i",&categoria);
		fflush(stdin);
		printf("\nValor: ");
		scanf("%f",&valor);
		for(int i=0; i<MAX; i++) //encontra o próximo item do array limpo, grava e sai no "break"
		{
			if(cadastros[i].ativo==0)
			{
				strcpy(cadastros[i].nome, nome); // Copia o nome corretamente, se fosse escrito da forma "normal" (cadastros[i].nome...) não funcionaria, traria só a pimeira letra
				strcpy(cadastros[i].descricao, descricao); 
				strcpy(cadastros[i].cor, cor); 
				strcpy(cadastros[i].fornecedor, fornecedor); 
				strcpy(cadastros[i].efeito, efeito); 
				cadastros[i].categoria = categoria;
				cadastros[i].valor = valor;
				cadastros[i].ativo=1;
				break;
			}
		}
		printf("\n1 - Continuar\n0 - Sair\n");
		scanf("%i",&op);
		fflush(stdin);
	}while(op!=0);
}

// funcao para removere um item
void remover(){
	int id;
	listar();
	printf("\n Digite o ID do produto a ser removido: ");
	scanf("%i",&id);
	--id; //subtrai um numero da váriavel, para quando for excluir o id 1 não excluir a posição 0;
	cadastros[id].ativo=0;
	printf("\nProduto excluido com sucesso\n");
	fflush(stdin);
}

//nao implementada, nao testei
void pesquisar(){
	char nome[50];
	int op;
	do{
		system("cls");
		printf("\nDigite o nome do produto para pesquisar: ");
		fgets(nome,sizeof(nome),stdin);
		for(int i=0; i<MAX; i++)
		{
			if(strstr(cadastros[i].nome,nome)!=NULL)/*Verifica se as strings são iguais*/
			{
				printf("Id: %i\n",i+1);
				printf("Nome: %s\n", cadastros[i].nome);
				printf("Descrição: %s\n", cadastros[i].descricao);
				printf("Cor: %s\n", cadastros[i].cor);
				printf("Fornecedor: %s\n", cadastros[i].fornecedor);
				printf("Efeito: %s\n", cadastros[i].efeito);
				printf("Categoria: %i\n", cadastros[i].categoria);
				printf("Valor: %.2f\n", cadastros[i].valor);
				printf("\n-----------------------------\n");
			}
		}
		printf("Digite 0 para sair ou 1 para nova pesquisa: ");
		scanf("%i",&op);
		getchar();
	}while(op!=0);
}

//lista todos os items
void listar(){
	system("cls");
	printf("\n LISTA DE PRODUTOS\n");
	for(int i=0; i<MAX; i++)
	{
		if(cadastros[i].ativo ==1){
			printf("Id: %i\n",i+1);
			printf("Nome: %s\n", cadastros[i].nome);
			printf("Descrição: %s\n", cadastros[i].descricao);
			printf("Cor: %s\n", cadastros[i].cor);
			printf("Fornecedor: %s\n", cadastros[i].fornecedor);
			printf("Efeito: %s\n", cadastros[i].efeito);
			printf("Categoria: %i\n", cadastros[i].categoria);
			printf("Valor: %.2f\n", cadastros[i].valor);
			printf("\n-----------------------------\n");
			
		}
	}
	printf("Aperte a tecla Enter pra sair e retornar ao menu de cadastro");
	getchar();
}

//lista somente os itens da categoria escolhida e com poucos detalhes
void listarCat(int cat){
	system("cls");
	printf("\n LISTA DE PRODUTOS\n");
	for(int i=0; i<MAX; i++)
	{
		if(cadastros[i].ativo ==1 && cadastros[i].categoria == cat){
			printf("Id: %i, %s, %s, R$ %.2f\n",i+1, cadastros[i].nome, cadastros[i].efeito, cadastros[i].valor);
		}
	}
}

//cadastro automatico de itens para nao ficar vazio
void cadastroAutomatico(){
	strcpy(cadastros[0].nome, "Shopex");
	strcpy(cadastros[0].descricao, "Fabricado com lepulo, cereais meltados e agua pura."); 
	strcpy(cadastros[0].cor, "Dourado"); 
	strcpy(cadastros[0].fornecedor, "Ambov"); 
	strcpy(cadastros[0].efeito, "Felicidade instantânea"); 
	cadastros[0].categoria = 1;
	cadastros[0].valor = 4.5;
	cadastros[0].ativo=1;
	
	strcpy(cadastros[1].nome, "Wiskent");
	strcpy(cadastros[1].descricao, "Aguardente, com gosto de dipironeitor"); 
	strcpy(cadastros[1].cor, "Dourado"); 
	strcpy(cadastros[1].fornecedor, "Daniel Jack"); 
	strcpy(cadastros[1].efeito, "Visão em dobro"); 
	cadastros[1].categoria = 1;
	cadastros[1].valor = 10.2;
	cadastros[1].ativo=1;
	
	strcpy(cadastros[2].nome, "Sodax");
	strcpy(cadastros[2].descricao, "Bebida com gosto de limão."); 
	strcpy(cadastros[2].cor, "Transparente"); 
	strcpy(cadastros[2].fornecedor, "PèKsiCola"); 
	strcpy(cadastros[2].efeito, "Faz a comida ruim descer melhor"); 
	cadastros[2].categoria = 1;
	cadastros[2].valor = 2.5;
	cadastros[2].ativo=1;
	
	strcpy(cadastros[3].nome, "Carne de Onça");
	strcpy(cadastros[3].descricao, "Carne crua com iguarias."); 
	strcpy(cadastros[3].cor, "Vermelho"); 
	strcpy(cadastros[3].fornecedor, "Frifelino"); 
	strcpy(cadastros[3].efeito, "Sacia a Fome"); 
	cadastros[3].categoria = 2;
	cadastros[3].valor = 15;
	cadastros[3].ativo=1;
	
	strcpy(cadastros[4].nome, "Carne de Veado");
	strcpy(cadastros[4].descricao, "Assado feito com carne de caça."); 
	strcpy(cadastros[4].cor, "Vermelho escuro"); 
	strcpy(cadastros[4].fornecedor, "Caçador higiênico"); 
	strcpy(cadastros[4].efeito, "Sacia muito a fome"); 
	cadastros[4].categoria = 2;
	cadastros[4].valor = 4.5;
	cadastros[4].ativo=1;
	
	strcpy(cadastros[5].nome, "Mana");
	strcpy(cadastros[5].descricao, "Frasco brilhante, com ingredientes secretos."); 
	strcpy(cadastros[5].cor, "Azul"); 
	strcpy(cadastros[5].fornecedor, "Raul, O vampiro doidão"); 
	strcpy(cadastros[5].efeito, "Restaura pontos de magia"); 
	cadastros[5].categoria = 3;
	cadastros[5].valor = 129,99;
	cadastros[5].ativo=1;
	
	strcpy(cadastros[6].nome, "Vida");
	strcpy(cadastros[6].descricao, "Frasco opaco, feito com lagimas de ogro e sangue de carneiro."); 
	strcpy(cadastros[6].cor, "Vermelho"); 
	strcpy(cadastros[6].fornecedor, "Finn, o Humano"); 
	strcpy(cadastros[6].efeito, "Restaura pontos de vida"); 
	cadastros[6].categoria = 3;
	cadastros[6].valor = 99.99;
	cadastros[6].ativo=1;
	
	strcpy(cadastros[7].nome, "Ajax");
	strcpy(cadastros[7].descricao, "Frasco estranho com uma privada no rótulo."); 
	strcpy(cadastros[7].cor, "Dourado"); 
	strcpy(cadastros[7].fornecedor, "Pato"); 
	strcpy(cadastros[7].efeito, "Supostamente purifica banheiros"); 
	cadastros[7].categoria = 3;
	cadastros[7].valor = 149.5;
	cadastros[7].ativo=1;
}





