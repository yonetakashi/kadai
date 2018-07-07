//201611210_米澤凌司_必須課題5-3_2018/6/11提出
#include<stdio.h>
#include<stdbool.h>
#define N 9//N×Nの盤
#define M 9
//入力可能な数字1~9

int array[N][N];//盤の状態
int cte[81];//
//int nec=0;//num empty cell
double cost=0;//計算コスト
int count=0;//解の数
void Sudoku(int s,int t);
bool check_line(int n,int x);//行をチェック
bool check_row(int n, int y);//列をチェック
bool check_block(int n, int x, int y);//3×3の枠内をチェック
bool check(int n, int x, int y);
int found_next(int m);


int main(int argc,char *argv[]){
 FILE *fp;
 int i=0,j=0,k,ch;
 int nec=0;//num empty cell
 //テキストファイルの読み込み
 fp=fopen(argv[1],"r");
 while((ch=getc(fp))!=EOF){
  if(ch!=32){//スペースは無視
   array[i][j++]=ch-48;//盤の状態を記憶
   if(ch==10){//改行したら次の配列に
    i++;
    j=0;
   }
  }
 }
fclose(fp);
 
 //マスをリスト化
 k=0;
 for(i=0;i<N;i++){
  for(j=0;j<N;j++){
   if(array[i][j]==0){
    nec++;//空白のマスの総数を数える
    cte[k++]=array[i][j];
   }else
   cte[k++]=-array[i][j];//数字が与えられているマスは負の値にしておく
  }
 }
 //問題の盤を出力
 printf("問題--空きマス：%d\n",nec);
 for(i=0;i<N;i++){
  for(j=0;j<N;j++){
   printf(" %d",array[i][j]);
  }
  printf("\n");
 }

 Sudoku(nec,found_next(0));//Sudoku開始
 printf("count：%d, cost:%f\n",count,cost);//解の数と計算コストを出力
 return 0;
}

//Sudoku
void Sudoku(int s,int t){
 int i,j,k,f,x,y;
 //1~9で入力可能な数字をチェック
 for(f=1;f<=9;f++){//printf("c");
  x=t/9;//行の座標に変換
  y=t%9;//列の座標に変換
  if(check(f,x,y)){//進行条件を確認
　//値を代入
   array[x][y]=f;
   cte[t]=f;
   cost++;//実行回数を記憶
   if(s-1==0){//解を発見
    count++;//解の数を記録
    //解の盤を出力
    printf(" 解\n");
    for(i=0;i<N;i++){
     for(j=0;j<N;j++){
      printf(" %d",array[i][j]);
     }
     printf("\n");
    }
   }
   else{
    k=found_next(t+1);//空きマスを探す
    Sudoku(s-1,k);//再帰関数
   }
   //数字を入力しなかったので初期値0に戻す
   array[x][y]=0;
   cte[t]=0;   
  }
 }
}

//x行目にnと同じ数字がないか確認
bool check_line(int n,int x){
int i;
 for(i=0;i<N;i++){
  if(array[x][i]==n)return false;
 }
 return true;
}
//y列目にnと同じ数字がないか確認
bool check_row(int n, int y){
int i;
 for(i=0;i<N;i++){
  if(array[i][y]==n)return false;
 }
 return true;
}
//3×3の枠内をチェック
bool check_block(int n, int x, int y){
int i,j,nx,ny;
 nx=x-(x%3);
 ny=y-(y%3);
 for(i=0;i<3;i++){
  for(j=0;j<3;j++){
   if(array[nx+i][ny+j]==n)return false;
  }
 }
 return true;
}
//進行条件のチェック
bool check(int n, int x, int y){
check_line(n,x)&&check_row(n,y)&&check_block(n,x,y);
}

//空きマスを探す
int found_next(int m){
 int k;
 for(k=m;k<81;k++){
  if(cte[k]==0){
   return k;
  }
 }
}
//苦労した点：
//arrayの初期化をしないと、代入した値がうまくいかずに再帰関数が戻ってきた時に進行条件がうまく機能しなっかった点。
//このプログラムでは終了条件をs-1=0にしないといけないことに気が付かなかったてん。
