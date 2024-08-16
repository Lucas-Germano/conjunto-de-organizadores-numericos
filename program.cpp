#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

void SwitchCase();
void ImprimirVetor(int qtd, int vezes);
void QuickSort(int qtd);

float tempo;
int vezes, tamanho;
int *vetor;

void ZerarVariavel(){
	vezes=0;
	tempo=NULL;
}

void entradaRand(int qtd){
	ZerarVariavel();
	
    vetor = (int*) malloc(qtd * sizeof(int));
    if (vetor == NULL) {
        printf("Erro de alocacao de memoria\n");
        exit(1);
    }
    
    srand(time(NULL));
    
    for(int i = 0; i < qtd; i++){
        vetor[i] = (rand() * (rand() %10)+ rand()) % 1000001;
        printf("{numero %i} ",vetor[i]);
        for(int j = 0; j < i; j++){
            if(vetor[i] == vetor[j]){
                vetor[i] = (rand() * (rand() %10)+ rand()) % 1000001;
                j = -1; 
            }
        }
    }
    tamanho = qtd;
    printf("\nNumeros gerados corretamente");
}

void entradaManual(int qtd){
	ZerarVariavel();
	
	float temp;
	
	vetor = (int*) malloc(qtd * sizeof(int));
	if (vetor == NULL){
		printf("Erro de alocacao de memoria\n");
		exit(1);
	}
	
	for(int i=0; i < qtd; i++){
		printf("Digeite o %i numero do vetor: ",i+1);
		
		if(scanf("%f", &temp) != 1 || (int)temp != temp){
	    	printf("\nErro: Entrada invalida, digite um numero inteiro!!\n");
			while(getchar() != '\n');
			i--;
		}
		else{
			vetor[i] = (int)temp;
		}
	}
	tamanho = qtd;
}

void ImprimirVetor(int qtd, int vezes){
	printf("\n");
	printf("{");
	for (int i=0; i<qtd; i++){
		printf("%i", vetor[i]);
		if (i != qtd - 1) {
        printf(", ");
    	}
	}
	printf("}");
	if(vezes != 0 && tempo  == NULL){
		printf(" (%i operacoes)",vezes);
	}
	if(vezes != 0 && tempo != NULL){
		printf(" (%i operacoes) em %.4f milisegundos",vezes,tempo);
	}

}

void BubleSort(int qtd){
	ZerarVariavel();
	
	clock_t inicio = clock();
	
	int temp;
	for(int i=0; i<qtd - 1; i++){
		for (int j = 0; j <qtd - 1 - i; j++) {
            if (vetor[j] > vetor[j + 1]) {
                temp = vetor[j + 1];
                vetor[j + 1] = vetor[j]; 
                vetor[j] = temp;
                vezes++;
            }
        }
	}
	
	clock_t fim = clock();
	tempo = (((float) (fim - inicio)) / CLOCKS_PER_SEC)*1000;
}

void SelectionSort(int qtd){
	ZerarVariavel();
	
	clock_t inicio = clock();
	
	int temp;
	for(int i=0; i<qtd - 1; i++){
		for (int j = i + 1; j <qtd; j++) {
            if (vetor[j] < vetor[i]) {
                temp = vetor[j];
                vetor[j] = vetor[i]; 
                vetor[i] = temp;
                vezes++;
            }
        }
	}
	
	clock_t fim = clock();
	tempo = (((float) (fim - inicio)) / CLOCKS_PER_SEC)*1000;
}

void InsertionSort(int qtd){
	ZerarVariavel();
	
	clock_t inicio = clock();
	
    int j, temp;
    for (int i = 1; i < qtd; i++) {
        temp = vetor[i];
        j = i - 1;

        while (j >= 0 && vetor[j] > temp) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = temp;
        vezes++;
    }
    
    clock_t fim = clock();
    tempo = (((float) (fim - inicio)) / CLOCKS_PER_SEC)*1000;
}

void Quick(int esquerda, int direita) {
    int i, j;
    float pivo, temp;
    i = esquerda;
    j = direita;
    pivo = vetor[(esquerda + direita) / 2];
    while(i <= j) {
        while(vetor[i] < pivo && i < direita) {
            i++;
        }
        while(vetor[j] > pivo && j > esquerda) {
            j--;
        }
        if(i <= j) {
            temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
            i++;
            j--;
            vezes++;
        }
    }
    if(j > esquerda) {
        Quick(esquerda, j);
    }
    if(i < direita) {
        Quick(i, direita);
    }
}

void QuickSort(int qtd) {
	ZerarVariavel();
	
	clock_t inicio = clock();
    
	Quick(0, qtd-1);
	
	clock_t fim = clock();
    tempo = (((float) (fim - inicio)) / CLOCKS_PER_SEC)*1000;
    
    printf("\nNumeros ordenados corretamente\n");
}

void LinearTime(int qtd, int max) {
    int *contador = (int*)calloc(max + 1, sizeof(int));
    int *saida = (int*)malloc(qtd * sizeof(int));
    
    if (contador == NULL || saida == NULL) {
        printf("Erro de alocacao de memoria\n");
        exit(1);
    }

    for (int i = 0; i < qtd; i++) {
        contador[vetor[i]]++;
        vezes++;
    }
    
    for (int i = 1; i <= max; i++) {
        contador[i] += contador[i - 1];
        vezes++;
    }
    
    for (int i = qtd - 1; i >= 0; i--) {
        saida[contador[vetor[i]] - 1] = vetor[i];
        contador[vetor[i]]--;
        vezes++;
    }
    
    for (int i = 0; i < qtd; i++) {
        vetor[i] = saida[i];
        vezes++;
    }
    
    free(contador);
    free(saida);
}

void LinearTimeSort(int qtd){
	ZerarVariavel();
	
	clock_t inicio = clock();
	
	int max = vetor[0];
    for (int i = 1; i < qtd; i++) {
        if (vetor[i] > max) {
            max = vetor[i];
        }
    }
	LinearTime(qtd, max);
	
	clock_t fim = clock();
    tempo = (((float) (fim - inicio)) / CLOCKS_PER_SEC)*1000;
}

void desorganizarVetor(int qtd){
	ZerarVariavel();
	
	int j;
	int temp;
    for (int i = 0; i < qtd; i++){
        j = rand() % qtd;
        temp = vetor[i];
        vetor[i] = vetor[j];
        vetor[j] = temp;
    }
}

void LimparVetor(int qtd){
	for(int i=0; i<qtd; i++){
		vetor[i] = 0;
	}
}

int ImprimirMenu(){
	
	int qtd;
	float temp;
	
	printf("=========================");
	printf("\n    Menu de escolhas");
	printf("\n01) - Gerar numeros aleatorios no vetor.");
	printf("\n02) - Digitar manualmente os numeros no vetor.");
	printf("\n03) - Desorganizar vetor.");
	printf("\n04) - Limpar vetor.");
	printf("\n05) - Imprimir vetor.");
	printf("\n06) - Organizar vetor por Buble Sort.");
	printf("\n07) - Organizar vetor por Insertion Sort.");
	printf("\n08) - Organizar vetor por Selection Sort.");
	printf("\n09) - Organizar vetor por Quick Sort.");
	printf("\n10) - Organizar vetor por Linear Time Sort.");
	printf("\n11) - Sair do programa.");
	printf("\n=========================");
	
	printf("\n\nDigite a opcao desejada: ");
	if(scanf("%f", &temp) != 1 || (int)temp != temp){
    	printf("\n\nErro: Entrada invalida, digite um numero inteiro!!\n\n");
		while(getchar() != '\n');
		qtd = ImprimirMenu();
	}
	else{
		qtd = (int)temp;
	}
	
	return (qtd);
}

int main(){
	SwitchCase();
}

void limpaTela() {
    #ifdef _WIN32
    	sleep(1);
        system("cls");
    #else
    	sleep(1);
        system("clear");
    #endif
}

void retorno(){
	int resposta;
	printf("\n\nSe deseja retornar ao menu digite 1: ");
	scanf("%i",&resposta);
	if (resposta == 1){
		limpaTela();
		SwitchCase();
	}
	else{
		printf("\n\nObrigado por usar meu software!!!");
	}
}

void SwitchCase(){
	int opcao;
	opcao = ImprimirMenu();
	
	switch(opcao){
		
		case 1:{//entrada de numeros aleatorios
			float temp;
			int qtd;
		    printf("Digite a quantidade de numeros desejados: ");
		    if(scanf("%f", &temp) != 1 || (int)temp != temp){
		    	printf("\n\nErro: Entrada invalida, digite um numero inteiro!!\n\n");
				while(getchar() != '\n');
			}
			else{
				qtd = (int)temp;
		    	entradaRand(qtd);
			}
		    retorno();
			break;
		}
		case 2:{//entrada de numeros manuais
			float temp;
			int qtd;
		    printf("Digite a quantidade de numeros desejados: ");
		    if(scanf("%f", &temp) != 1 || (int)temp != temp){
		    	printf("\n\nErro: Entrada invalida, digite um numero inteiro!!\n\n");
				while(getchar() != '\n');
			}
			else{
				qtd = (int)temp;
				entradaManual(qtd);
			}
		    
		    retorno();
			break;
		}
		case 3:{//desorganizar vetor
			desorganizarVetor(tamanho);
			retorno();
			break;
		}
		case 4:{//limpa o vetor 
			LimparVetor(tamanho);
			retorno();
			break;
		}
		case 5:{//imprime o vetor com ou sem a quantidade de operações 
			ImprimirVetor(tamanho,vezes);
			retorno();
			break;
		}
		case 6:{//organiza o vetor por buble sort
			BubleSort(tamanho);
			retorno();
			break;
		}
		case 7:{//organiza o vetor por insertion sort
			InsertionSort(tamanho);
			retorno();
			break;
		}
		case 8:{//organiza o vetor por selection sort
			SelectionSort(tamanho);
			retorno();
			break;
		}
		case 9:{//organiza o vetor por quick sort
			QuickSort(tamanho);
			retorno();
			break;
		}
		case 10:{//organiza o vetor por linear time sort
			LinearTimeSort(tamanho);
			retorno();
			break;
		}
		case 11:{
			printf("\n\nObrigado por usar nosso software!!!");
			break;
		}
		default:{
			printf("\n\nEscolha uma opcao valida!!!");
			SwitchCase();
			break;
		}
	}
}
