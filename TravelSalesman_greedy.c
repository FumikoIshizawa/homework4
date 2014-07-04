//greedy program
//input
// ./a.out input.csv 5


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N 256
#define maxArray 2048

float locateArray[maxArray][2];
//訪問済みかどうかのflag: 1が訪問済み 0が未訪問
int locateComp[maxArray];
int route[maxArray];



//calclate distance
float calcDist(float x1, float x2, float y1, float y2){
	return sqrt(pow((x1-y1),2)
					+pow((x2-y2),2));
}


int searchCity(int num, int current){
	float mindist=4000, result=0;
	int i=0, minLoc=1;
	
	for(i=0; i<num; i++){
		if(locateComp[i]==1) continue;
		result = calcDist(locateArray[current][0], locateArray[current][1],
							locateArray[i][0], locateArray[i][1]);
		if(result<mindist){
			mindist=result; minLoc=i;
		}  
	}
	locateComp[minLoc]=1;
	return minLoc;
}



void searchWay(int num){
	int next=1, current=0;
	int i=0;
	float distance=0;
	locateComp[0]=1; route[0]=0;

	for(i=0; i<num-1; i++){
		next=searchCity(num, current); route[i+1]=next;
		distance += calcDist(locateArray[current][0], locateArray[current][1],
								locateArray[next][0], locateArray[next][1]);
		current=next;		
	}

	distance += calcDist(locateArray[current][0], locateArray[current][1],
								locateArray[0][0], locateArray[0][1]);

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

    printf("%d %d %d \n", route[0], route[1], route[2]);


}