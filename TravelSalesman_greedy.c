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
float route[maxArray];



//距離を計算
float calcDist(float x1, float x2, float y1, float y2){
	return sqrt(pow((x1-y1),2)
					+pow((x2-y2),2));
}

//配列の要素入れ替え
void swap(int a, int b){
	float temp0=locateArray[a][0];
	float temp1=locateArray[a][1];
	locateArray[a][0]=locateArray[b][0];
	locateArray[a][1]=locateArray[b][1];
	locateArray[b][0]=temp0;
	locateArray[b][1]=temp1;
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


void longReplace(int num){
	int cnt=0,i,j,i2,j2,k,total=0;
	float l1,l2,l3,l4;

	while(1){
		cnt=0;
		//iとi2の組み合わせに対してjとj2の組み合わせを全て試してみる		
		for(i=0; i<num-2; i++){
			i2=i+1;
			for(j=i+2; j<num; j++){
				if(j==num-1){
					//jがnum-1の時、j2は最初のノードをさせばよい
					j2=0;
				} else {
					j2=j+1;
				}
				//それぞれ長さを計算、比較して交換するかどうかを考える
				l1=calcDist(locateArray[i][0],locateArray[i][1],locateArray[i2][0],locateArray[i2][1]);
				l2=calcDist(locateArray[j][0],locateArray[j][1],locateArray[j2][0],locateArray[j2][1]);
				l3=calcDist(locateArray[i][0],locateArray[i][1],locateArray[j][0],locateArray[j][1]);
				l4=calcDist(locateArray[i2][0],locateArray[i2][1],locateArray[j2][0],locateArray[j2][1]);

				//もしl1+l2のほうがl3+l4より長いなら、l3+l4に結び変える方が良い
				//配列を入れ替える作業を繰り返す
				if(l1+l2>l3+l4){
					for(k=0; k<=(j-i2)/2; k++){
						swap(i2+k, j-k);
					}
					cnt++;
				}
			}
		}

		//カウントが0の時、入れ替えるものがなかったので終了
		if(cnt==0) break;
	}

}

void searchWay(int num){
	int next=1, current=0;
	int i=0, j=0;
	int randA, randB, temp;
	float distance=0, distanceTemp=0;
	srand((unsigned int)time(NULL));

	//距離計算  -- greedy
 	for(i=0; i<num-1; i++){
		searchCity(num, i); 
		distance += calcDist(locateArray[i][0], locateArray[i][1],
								locateArray[i+1][0], locateArray[i+1][1]);	
	}
	distance += calcDist(locateArray[i][0], locateArray[i][1],
								locateArray[0][0], locateArray[0][1]);

	printf("answer: %f\n", distance);


	//結び変える
	//距離が長いところ、交差しているところを入れ替える
	longReplace(num);

	//再度距離計算
	distance=0;
	for(i=0; i<num-1; i++){
		distance += calcDist(locateArray[i][0], locateArray[i][1],
								locateArray[i+1][0], locateArray[i+1][1]);	
	}
	distance += calcDist(locateArray[i][0], locateArray[i][1],
								locateArray[0][0], locateArray[0][1]);

	printf("\n2-opt answer: %f\n\n", distance);
	

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

