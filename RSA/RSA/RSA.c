#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct chave{
        int N;
        int E;
        int P;
        int Q;
        int D;
        int totiente;
}Chave;

typedef struct deschave{
	int d;
	int n;
}desChave;

int Divisor(int toti){
        int i, e, div;
        for(e=0;e<toti;e++){
                div=0;
                for(i=1;i<=toti;i++){
                        if(e%i==0 && toti%i==0){
                                div++;
                        }
                }
                if(div==1 && e!=1){
                        printf("%d\n", e);
                }
        }
return 0;
}

int Inverso(int E, int toti){
        int i, inter;
        for(i=0;1>0;i++){
                inter=i*E;
                if(inter%toti==1){
                        return i;
                }
        }
}

Chave Def_Chv(){
        Chave chv;
        int p, q;
        printf("Agora defineremos a chave para criptografar...\nDigite um número primo para P\n");
        scanf("%d", &chv.P);
        printf("Digite um número primo para Q\n");
        scanf("%d", &chv.Q);
        chv.N=chv.P*chv.Q;
        p=chv.P-1;
        q=chv.Q-1;
        chv.totiente=p*q;
        printf("Escolha E entre os seguintes númer-os: \n");
        Divisor(chv.totiente);
        scanf("%d", &chv.E);
        chv.D=Inverso(chv.E, chv.totiente);
return chv;
}

void Semi_Incrypt(long long qtd, char *txt, long long *semincrypt){
        int i;
        for(i=0;i<qtd;i++){
                semincrypt[i]=txt[i];
        }
}

void Translate(int qtd, int *DesIncrypted, char *txt){
        int i;
        for(i=0;i<qtd;i++){
                txt[i]=DesIncrypted[i];
        }
}

void Incrypt(){
        Chave chv;
        long long i, qtd, inter, *semIncrypt, *totalIncrypt;
        char *txt;
	FILE *out;
        printf("Informe o quantidade de caracteres a serem criptografados \n");
        scanf("%lld", &qtd);
        txt=(char *) malloc (qtd * sizeof(char));
        semIncrypt=(long long *) malloc ((qtd*3) * sizeof(long long));
        totalIncrypt=(long long *) malloc (qtd * sizeof(long long));
        setbuf(stdin, NULL);
        printf("Digite o texto a ser criptografado\n");
        scanf("%[^\n]s", txt);
        setbuf(stdin, NULL);
        Semi_Incrypt(qtd, txt, semIncrypt);
        chv=Def_Chv();
        for(i=0;i<qtd;i++){
                inter=pow(semIncrypt[i], chv.E);
                totalIncrypt[i]=inter%chv.N;
        }
	out = fopen("data.out","w");
        for(i=0;i<qtd;i++){
		setbuf(stdin,NULL);
                fprintf(out, "%lld - ", totalIncrypt[i]);
        }
	printf("\n %d \n", chv.D);
}

void Converte(int qtd, int *Incrypted2, char *Incrypted1){
        int i, j, h=0, inter[3];
        for(i=0;i<qtd*3;i+=3){
                for(j=0;j<3;j++){
                        inter[j]=Incrypted1[i+j];
                        inter[j]-=48;
                }
                if(h<qtd){
                        Incrypted2[h]=(inter[0]*100) + (inter[1]*10) + inter[2];
                        h++;
                }
        }
}

void DesIncrypt(int qtd, int *Incrypted2, int *DesIncrypted1, char *DesIncrypted2, desChave chv){
	int i, j, a, q, inter2=1;
	long long *inter;
	a=chv.d/5;
	printf("%d\n%d\n", chv.d, chv.n);
	if(chv.d%5!=0){
		inter=(long long *) malloc ((a+1) * sizeof(long long));
		for(i=0;i<qtd;i++){
			for(j=0;j<a;j++){
				inter[j]=pow(Incrypted2[i], 5);
			}
			q=chv.d%5;
                	inter[a]=pow(Incrypted2[i], q);
			for(j=0;j<a;j++){
				inter[j]=inter[j]%chv.n;
				printf("Inter(!=0)= %lld\n", inter[j]);
			}
			for(j=0;j<a;j++){
				inter2*=inter[j];
			}
			DesIncrypted1[i]=inter2;
			DesIncrypted2[i]=DesIncrypted1[i];
		}
	}
	else if(chv.d%5==0){
		inter=(long long *) malloc (a * sizeof(long long));
                for(i=0;i<qtd;i++){
                        for(j=0;j<a;j++){
                                inter[j]=pow(Incrypted2[i], 5);
				printf("%lld\n", inter[j]);
                        }
                        for(j=0;j<a;j++){
                                inter[j]=inter[j]%chv.n;
				printf("Inter(==0)= %lld\n", inter[j]);
                        }
                        for(j=0;j<a;j++){
                                inter2*=inter[j];
                        }
                        DesIncrypted1[i]=inter2;
                        DesIncrypted2[i]=DesIncrypted1[i];
                }
        }
	for(i=0;i<qtd;i++){
		setbuf(stdin,NULL);
		printf("%d", DesIncrypted1[i]);
		setbuf(stdin,NULL);
		printf("%c", DesIncrypted2[i]);
	}
}

void Des_Incrypt(){
        desChave chv;
        int qtd, *Incrypted2, *DesIncrypted1;
        char *txt, *Incrypted1, *DesIncrypted2;
        printf("Digite a chave para descriptografar\n");
        printf("Digite o valor de D\n");
        scanf("%d", &chv.d);
        printf("Digite o valor de N\n");
        scanf("%d", &chv.n);
        printf("Digite quantos caracteres devem ser descriptografados\n");
        scanf("%d", &qtd);
	printf("qtd=%d\n", qtd);
        txt=(char *) malloc (qtd * sizeof(char));
        Incrypted1=(char *) malloc ((qtd*3) * sizeof(char));
        Incrypted2=(int *) malloc (qtd * sizeof(int));
        DesIncrypted1=(int *) malloc (qtd * sizeof(int));
	DesIncrypted2=(char *) malloc (qtd * sizeof(char));
        setbuf(stdin, NULL);
        printf("Digite os caracteres criptografados(use sempre 3 digitos)\n");
        scanf("%[^\n]s", Incrypted1);
        setbuf(stdin, NULL);
        Converte(qtd, Incrypted2, Incrypted1);
        DesIncrypt(qtd, Incrypted2, DesIncrypted1, DesIncrypted2, chv);
}

int main(){
        int i;
	printf("Digite 0 para incriptar e 1 para desincriptar\n");
	scanf("%d", &i);
	if(i==0){
		Incrypt();
	}
        else if(i==1){
		Des_Incrypt();
	}
return 0;
}
