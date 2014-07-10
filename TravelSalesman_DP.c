//solved by DP
//input
// ./a.out input.csv 5


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N 256
#define maxArray 2048
#define INF 1000000


float locateArray[maxArray][2];
int count=1;
float dp[1<<64][maxArray];

//距離を計算
float calcDist(float x1, float x2, float y1, float y2){
	return sqrt(pow((x1-y1),2)
					+pow((x2-y2),2));
}

//return less value
float min(float a, float b){
	return a<b?a:b;
}


//要素数がnum、集合がS、現在地がv
//Sは集合。ビット演算でこれを示す
float searchWay(int num, int S, int v){
	int u; float ans=INF;
	//訪問済みなら計算済みなので、その値を返す
	if(dp[S][v] >= 0){
		return dp[S][v];
	}

	//Sは集合なので、2^n-1と値が等しければ、全ての都市を訪問した事となるので、0を返せば良い
	if( (1<<num)-1 == S && v==0) 
		return dp[S][v]=0;

	for(u=0; u<num; u++){
		if(!(S >> u & 1 )){ //uが訪問済みがどうか検証
			ans = min(ans, searchWay(num, S | 1<<u, u)+calcDist(locateArray[v][0], locateArray[v][1],
						locateArray[u][0], locateArray[u][1] ));
			
		}
	}

	return dp[S][v]=ans;

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

    memset(dp,-1,sizeof(dp));
	
    printf("%f\n ", searchWay(num,0,0));


}