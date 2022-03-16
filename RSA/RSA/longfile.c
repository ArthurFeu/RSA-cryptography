#include <stdio.h>
#include <stdlib.h>

int main(){
	int y;
	printf("Digite o valor y\n");
	scanf("%d", &y);
	long long int x[y];
	FILE* out;
	printf("Digite o valor a ser escrito no file:\n");
	for(int i=0;i<y;i++){
	scanf("%lld", &x[i]);
	}

	out = fopen("data.out","w");
	for(int i=0;i<y;i++){
	fprintf(out, "%lld - ", x[i]);
	}

	return 0;
}