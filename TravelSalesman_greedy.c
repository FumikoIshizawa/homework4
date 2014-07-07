//greedy program
//input
// ./a.out input.csv 5


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define N 256
#define maxArray 2048

float locateArray[maxArray][2];
int route[maxArray];



//calclate distance
float calcDist(float x1, float x2, float y1, float y2){
	return sqrt(pow((x1-y1),2)
					+pow((x2-y2),2));
}

void swap(int a, int b){
	float temp0=locateArray[a][0];
	float temp1=locateArray[a][1];
	locateArray[a][0]=locateArray[b][0];
	locateArray[a][1]=locateArray[b][1];
	locateArray[b][0]=temp0;
	locateArray[b][1]=temp1;
}

int GetRandom(int min,int max)
{
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}



void searchCity(int num, int min){
	float mindist=4000, result=0;
	int i, minLoc=min+1;
	
	for(i=min+1; i<num; i++){
		result = calcDist(locateArray[min][0], locateArray[min][1],
								locateArray[i][0], locateArray[i][1]);

		//値が最小値より小さい時、採用	
		if(result<mindist){
			mindist=result; minLoc=i;
		}  
	}	

	swap(min+1, minLoc);	

}


void searchWay(int num){
	int next=1, current=0;
	int i=0, j=0;
	int randA, randB, temp;
	float distance=0, distanceTemp=0;
	srand((unsigned int)time(NULL));

	// for(i=0; i<num; i++){
	// 	printf("%f\t", locateArray[i][0]/100);
	// }
	// printf("\n");


	//距離計算  -- greedy
 	for(i=0; i<num-1; i++){
		searchCity(num, i); 
		distance += calcDist(locateArray[i][0], locateArray[i][1],
								locateArray[i+1][0], locateArray[i+1][1]);		
	}
	distance += calcDist(locateArray[i][0], locateArray[i][1],
								locateArray[0][0], locateArray[0][1]);

	printf("%f\n", distance);


	//改善 -- 500回繰り返し
	for(i=0; i<500; i++){
		distanceTemp=0;
		randA=GetRandom(1,num-1);
		randB=GetRandom(1,num-1);
		swap(randA, randB);

		for(j=0; j<num; j++){
			distanceTemp += calcDist(locateArray[j][0], locateArray[j][0],
						locateArray[j+1][1], locateArray[j+1][1]);
		}
		distanceTemp += calcDist(locateArray[j][0], locateArray[j][1],
								locateArray[0][0], locateArray[0][1]);

		if(distanceTemp<distance)
			distance=distanceTemp;


		printf("  %f  -  %f\n", distanceTemp, distance);
	}


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

