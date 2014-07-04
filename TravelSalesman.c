//most simple program!
//input
// ./a.out input.csv 5


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N 256
#define maxArray 2048

float locateArray[maxArray][2];
int count=1;


int searchCity(){
	return count++;
}



void searchWay(int num){
	int next=1, current=0;
	int i=0;
	float distance=0;

	for(i=0; i<num-1; i++){
		next=searchCity();
		distance += sqrt(pow((locateArray[current][0]-locateArray[next][0]),2)
					+pow((locateArray[current][1]-locateArray[next][1]),2));
		current=next;		
	}

	distance += sqrt(pow((locateArray[current][0]-locateArray[0][0]),2)
					+pow((locateArray[current][1]-locateArray[0][1]),2));

	printf("%f\n", distance);

}




int main(int argc, char *argv[]){ 
	//ファイル読み込み
	FILE *fp; int i=0; 
	char *filename = argv[1];
	char readline[N]={'\0'};
	int num=atoi(argv[2]);
	

	printf("%s, %d\n", filename, num );


	if((fp=fopen(filename, "r"))==NULL){
		fprintf(stderr, "Open error in %s.\n", filename);
        exit(EXIT_FAILURE);
    }

    //1行目読み込み
    fgets(readline, N, fp);
    //その後の行を読み込む
	while (fscanf(fp, "%f,%f", &locateArray[i][0], &locateArray[i][1])!=EOF) {
    	i++;
    }
	
    searchWay(num);


}