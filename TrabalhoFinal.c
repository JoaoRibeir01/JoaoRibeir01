/* Jogo de basket criado em C, com múltiplas melhorias na posição do jogador e na pontuação adquirida.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <locale.h>



/* .As velocidades escritas em m/s;
.O angulo de lancamento em graus;
.Utilizar setlocale para permitir todo o tipo de linguagem portuguesa;
*/

typedef struct lancamento{  //struct lancamento
	float hSalto;  //altura do salto
	float theta;  
	float vb;  //velocidade inicial da bola
	float v1; //velocidade do salto
}Lancamento;

typedef struct ronda{    //struct ronda
	int f; //falhas
	int p;
	int fs; //falhas seguidas 
	Lancamento l[5]; //numero de tentativas numa ronda
	int pont; 
}Ronda;

typedef struct jogadores{ //struct dados jogadores
	float h; //altura
	Ronda r[3];
	float d; 
}Jogadores;

void wJogadores(){ //ficheiro com dados dos jogadores
	int num;	
	FILE * arcplayers;
	arcplayers = fopen ("arcplayers.txt","wb");
	if (arcplayers == NULL){
		printf ("Erro ao abrir o arquivo");
		exit (1);
	}else{
		printf ("Número de jogadores: ");
		scanf ("%d",&num);
		}
	fwrite(&num,sizeof(int),1,arcplayers);
	Jogadores j[num];
	int i;
	for (i=0;i<num;i++){
		printf ("Jogador %d\nAltura, em metros: ",i+1);
		scanf ("%f",&j[i].h);
		fwrite(&j[i].h,sizeof(float),1,arcplayers);
		}
	fclose(arcplayers);
}

void wAreas(){ //ficheiro com areas inteiras geradas pelo utilizador
	int i;
	float c1,c2,x,y;
	int num;	
	FILE * areas;
	areas = fopen ("areas.txt","wb");
	if (areas == NULL){
		printf ("Erro ao abrir o arquivo");
		exit(1);
	}else{
		printf ("Comprimento do campo:14m\n");
		for (i=0;i<1;i++){
			printf ("Limite da area 1: \n");
			scanf ("%f",&x);
			if (x<=0||x>=14||(x!=(int)x)){
				printf ("Valor inválido.\n");
				i--;
			}else{
				c1=x;
				fwrite(&c1,sizeof(float),1,areas);	
			}
		}
		for (i=0;i<1;i++){
			printf ("Limite da area 2: \n");
			scanf ("%f",&y);
			if (y<=c1||y>=14||(y!=(int)y)){
				printf ("Valor inválido.\n");
				i--;
			}else{
				c2=y;
				fwrite(&c2,sizeof(float),1,areas);
			}
		}
	}
	fclose(areas);
	system ("PAUSE");
}


int gerarAreas(){ //ficheiro para definir variaveis para limite de areas
	float f;
	int pos;
	float c1,c2;
	
	FILE * areas;
	areas = fopen ("areas.txt","rb");
	if (areas == NULL){
	printf ("Erro ao abrir o arquivo.");
	exit(1);
	}else{
	fread(&c1,sizeof(float),1,areas);
	fread(&c2,sizeof(float),1,areas);
	}
	fclose(areas);
	
	if (f>0&&f<=c1)
		pos=1;
	else if (f>c1&&f<=c2)
		pos=2;
	else 
		pos=3;
	return pos;
}

float gerarPosicao(){ //gerar uma posicao aleatoria
	int n;
	int d;
	float distancia,c1,c2;
	FILE * areas;
	areas = fopen ("areas.txt","rb");
	if (areas == NULL){
	printf ("Error opening file.");
	exit(1);
	}else{
	fread(&c1,sizeof(float),1,areas);
	fread(&c2,sizeof(float),1,areas);
	}
	fclose(areas);
	
	srand(time(0));
	int l1 = (int)((c1*100)-57+1);
	int l2 = (int)((c2*100)-(c1*100)+1);
	int l3 = (int)((28*100)-(c2*100)+1);
	if (n==1){
		d = 57 + (rand() % l1);
		distancia = (float)d/100;
		}
	else if (n==2){
		d = ((c1*100)+1) + (rand() % l2);
		distancia = (float)d/100;
		}
	else{
		d = ((c2*100)+1) + (rand() % l3);
		distancia = (float)d/100;
		} 
	return distancia;
}

float altura(){ //fincao altura
	float d,theta,s;
	float g= 9.8;
	float pi=3.1416;
	float rad = (theta*pi)/180;
	float alt = (d * tan(rad)) - ((g*pow(d,2))/(2*pow(s,2)*pow(cos(rad),2)));
	return alt;	
}

void print(int k){
	if (k==1)
		printf ("1 tentativa realizada, 4 restantes\n");
	else printf ("%d tentativas realizadas, %d restantes\n",k,(5-k));
}

float alturaSalto (){ //funcao altura do salto do jogador
	float v1;
	float g=9.8;
	float hSalto=pow(v1,2)/(2*g);
	return hSalto;
}

void lancamento(int r,int l){
	float maior;
	int i,num,jog;
	int rond,lanc,*add,v,var;
	
	FILE * arcplayers;
	arcplayers = fopen ("arcplayers.txt","rb");
	if (arcplayers == NULL){
	printf ("Erro ao abrir o arquivo.");
	exit(1);
	}else{
	fread(&num,sizeof(int),1,arcplayers);
	}
	Jogadores j[num];
	for (i=0;i<num;i++){
		fread(&j[i].h,sizeof(float),1,arcplayers);
		}
	fclose(arcplayers);
	
	float h = 2.80;
	float rb = 0.250;
	float rc = 0.270;
	float dc = 0.540;
	for (rond=0;rond<r;rond++){
		for (i=0;i<num;i++){
			j[i].r[rond].fs=0;
			j[i].r[rond].f=0;
			j[i].r[rond].p=0;
			float dist = gerarPosicao(rond+1); 
			j[i].d=dist;
		}
		for (lanc=0;lanc<l;lanc++){
			for (jog=0;jog<num;jog++){
				int area = gerarAreas(j[jog].d);
				rond;
				print(lanc);
				printf ("NÍVEL %d\n",rond+1);
				printf ("JOGADOR %d\n",jog+1);
				printf ("Área de lançamento: %d\n",area);
				printf ("Velocidade inicial do salto(componente vertical): ");
				scanf ("%f",&j[jog].r[rond].l[lanc].v1);
				printf ("Ângulo de lançamento da bola, entre 0 e 80 graus: ");
				scanf ("%f",&j[jog].r[rond].l[lanc].theta);
				printf ("Velocidade inicial do lançamento: ");
				scanf ("%f",&j[jog].r[rond].l[lanc].vb);
				j[jog].r[rond].l[lanc].hSalto = alturaSalto(j[jog].r[rond].l[lanc].v1); //para  verificar s ebola entra
				float teta = j[jog].r[rond].l[lanc].theta;
				float s = j[jog].r[rond].l[lanc].vb;
				float hi = j[jog].r[rond].l[lanc].hSalto + j[jog].h + rb;
				float h1 = hi + altura((j[jog].d - rb),teta,s);
				float h2 = hi + altura((j[jog].d - dc+rb),teta,s);
				system("PAUSE");
				if (h1<=h && h<=h2){
					printf ("ACERTOU!\n");
					if (lanc==1){
							j[jog].r[rond].p+= gerarAreas(j[jog].d);
							if (gerarAreas(j[jog].d)==1)
								printf ("+1 PONTO\n");
							else
								printf ("+%d PONTOS\n",gerarAreas(j[jog].d));
							}else {
								printf("0 PONTOS\n");
							}
							j[jog].r[rond].fs=0;
						if (lanc==4)
							j[jog].d = gerarPosicao(rond+2);
						else
							j[jog].d = gerarPosicao(rond+1);
						}else {
							j[jog].r[rond].f++;
							j[jog].r[rond].fs++;
							printf ("Falhou.\n");
						}
					}
				}
			}
	printf ("Fim do jogo!\n");
	
	var=0;
	maior=0;
	add = (int*) malloc(num*sizeof(int));
	for (i=0;i<num;i++){
		add[i]=j[i].r[0].p + j[i].r[1].p + j[i].r[2].p;
		if (add[i]>maior){
			maior=add[i];
			v=i;
		}
	}
	for (i=0;i<num;i++){
		add[i]=j[i].r[0].p + j[i].r[1].p + j[i].r[2].p;
		if (add[i]==maior)
			var++;
	}
	if (var>1)
		printf ("Empate\n");
		
	else{
		if (num>1)
			printf ("O vencedor é o jogador %d com classificacao de %d",v+1,add[v]);
	}
	system("PAUSE");
	free(add);
	FILE * resultados;
		resultados = fopen ("resultados.txt","wb");
		if (resultados == NULL){
			printf ("Erro ao abrir o arquivo.");
			exit(1);
		}else{
		for (i=0;i<num;i++){
			for (rond=0;rond<3;rond++){
			fwrite(&j[i].r[rond].f,sizeof(int),1,resultados);
			fwrite(&j[i].r[rond].p,sizeof(int),1,resultados);
			}
		}
	}	
	fclose(resultados);
}

void classFinal() { //ficheiro com a classFinal de cada jogador
	int i,rond,num;
	FILE * arcplayers;
	arcplayers = fopen ("arcplayers.txt","rb");
	if (arcplayers == NULL){
		printf ("Erro ao abrir o arquivo."); 
		exit(1);
	}else{
		fread(&num,sizeof(int),1,arcplayers);
	}
	fclose(arcplayers);
	Jogadores j[num];
	FILE * resultados;
	resultados = fopen ("resultados.txt","rb");
	if (resultados == NULL){
			printf ("Erro ao abrir o arquivo.");
			exit(1);
	}
	else{
		for (i=0;i<num;i++){
			for (rond=0;rond<3;rond++){
			fread(&j[i].r[rond].f,sizeof(int),1,resultados);
			fread(&j[i].r[rond].p,sizeof(int),1,resultados);
			}
		}
	}
	fclose(resultados);
}

void novoJogo(){
	wJogadores();
	wAreas();
	lancamento(3,5);
	classFinal();	
}

void menu(){
	int acao;
	printf ("1.Novo jogo\n2.Sair\n");
	printf ("Selecione a opção: \n");
	scanf ("%d",&acao);
	if (acao==1)
	novoJogo();
	else 
	system("PAUSE");
}

int main() {
	setlocale(LC_ALL, "Portuguese");
	menu();
	return 0;
}







