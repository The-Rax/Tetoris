#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define FIELD_H 22  //フィールド縦幅
#define FIELD_W 12  //フィールド横幅
#define MINO_H 4    //ミノ縦幅
#define MINO_W 4    //ミノ横幅

char field[FIELD_H][FIELD_W];       //フィールド用
char displaybuf[FIELD_H][FIELD_W];  //表示用

enum {            //ミノの種類
  MINO_T_I,
  MINO_T_O,
  MINO_T_S,
  MINO_T_Z,
  MINO_T_J,
  MINO_T_L,
  MINO_T_T,
  MINO_T_MAX
};

enum {           //角度の種類
  MINO_A_0,
  MINO_A_1,
  MINO_A_2,
  MINO_A_3,
  MINO_A_MAX
};

char minoS[MINO_T_MAX][MINO_A_MAX][MINO_H][MINO_W] = {   //ミノ
  //MINO_T_I
  {
    //MINO_A_0
    {
      0,0,0,0,
      0,0,0,0,
      1,1,1,1,
      0,0,0,0,
    },
    //MINO_A_1
    {
      0,0,1,0,
      0,0,1,0,
      0,0,1,0,
      0,0,1,0,
    },
    //MINO_A_2
    {
      0,0,0,0,
      1,1,1,1,
      0,0,0,0,
      0,0,0,0,
    },
    //MINO_A_3
    {
      0,1,0,0,
      0,1,0,0,
      0,1,0,0,
      0,1,0,0,
    },
  },
  //MINO_T_O
  {
    //MINO_A_0
    {
      0,0,0,0,
      0,1,1,0,
      0,1,1,0,
      0,0,0,0,
    },
    //MINO_A_1
    {
      0,0,0,0,
      0,1,1,0,
      0,1,1,0,
      0,0,0,0,
    },
    //MINO_A_2
    {
      0,0,0,0,
      0,1,1,0,
      0,1,1,0,
      0,0,0,0,
    },
    //MINO_A_3
    {
      0,0,0,0,
      0,1,1,0,
      0,1,1,0,
      0,0,0,0,
    },
  },
  //MINO_T_S
  {
    //MINO_A_0
    {
      0,0,0,0,
      0,1,1,0,
      1,1,0,0,
      0,0,0,0,
    },
    //MINO_A_1
    {
      0,1,0,0,
      0,1,1,0,
      0,0,1,0,
      0,0,0,0,
    },
    //MINO_A_2
    {
      0,0,0,0,
      0,0,1,1,
      0,1,1,0,
      0,0,0,0,
    },
    //MINO_A_3
    {
      0,0,0,0,
      0,1,0,0,
      0,1,1,0,
      0,0,1,0,
    },
  },
  //MINO_T_Z
  {
    //MINO_A_0
    {
      0,0,0,0,
      1,1,0,0,
      0,1,1,0,
      0,0,0,0,
    },
    //MINO_A_1
    {
      0,0,0,0,
      0,0,1,0,
      0,1,1,0,
      0,1,0,0,
    },
    //MINO_A_2
    {
      0,0,0,0,
      0,1,1,0,
      0,0,1,1,
      0,0,0,0,
    },
    //MINO_A_3
    {
      0,0,1,0,
      0,1,1,0,
      0,1,0,0,
      0,0,0,0,
    },
  },
  //MINO_T_J
  {
    //MINO_A_0
    {
      0,0,0,0,
      0,1,0,0,
      0,1,1,1,
      0,0,0,0,
    },
    //MINO_A_1
    {
      0,0,1,0,
      0,0,1,0,
      0,1,1,0,
      0,0,0,0,
    },
    //MINO_A_2
    {
      0,0,0,0,
      1,1,1,0,
      0,0,1,0,
      0,0,0,0,
    },
    //MINO_A_3
    {
      0,0,0,0,
      0,1,1,0,
      0,1,0,0,
      0,1,0,0,
    },
  },
  //MINO_T_L
  {
    //MINO_A_0
    {
      0,0,0,0,
      0,0,1,0,
      1,1,1,0,
      0,0,0,0,
    },
    //MINO_A_1
    {
      0,0,0,0,
      0,1,1,0,
      0,0,1,0,
      0,0,1,0,
    },
    //MINO_A_2
    {
      0,0,0,0,
      0,1,1,1,
      0,1,0,0,
      0,0,0,0,
    },
    //MINO_A_3
    {
      0,1,0,0,
      0,1,0,0,
      0,1,1,0,
      0,0,0,0,
    },
  },
  //MINO_T_T
  {
    //MINO_A_0
    {
      0,0,0,0,
      0,0,1,0,
      0,1,1,1,
      0,0,0,0,
    },
    //MINO_A_1
    {
      0,0,1,0,
      0,1,1,0,
      0,0,1,0,
      0,0,0,0,
    },
    //MINO_A_2
    {
      0,0,0,0,
      1,1,1,0,
      0,1,0,0,
      0,0,0,0,
    },
    //MINO_A_3
    {
      0,0,0,0,
      0,1,0,0,
      0,1,1,0,
      0,1,0,0,
    },
  }
};

int next [5] = {};  //この後のミノの種類
int now;            //ミノ更新用の仮場所
int stock;          //ストック用
int isstock = 0;    //ストック中か判定
int canstock = 1;   //ストック可能か判定

int minoX = 5, minoY = -1;  //操作対象のミノの現在地
int minoT = 0, minoA = 0;  //操作対象のミノの種類と角度

void display() {  //表示用関数
 memcpy(displaybuf, field, sizeof(field));  

  for (int i = 0; i < MINO_H; i ++)  //ミノによる画面更新
    for (int j = 0; j < MINO_W; j ++)
      displaybuf[minoY + i][minoX + j] |= minoS[minoT][minoA][i][j];
      
      
  system("cls");  //画面リセット
      
  for (int i = 0; i < FIELD_H; i++){
    if (i == 0){                       //ストック画面表示
      printf("ｓｔｏｃｋ");
    }else if (i < 5 && isstock == 1){
      for(int j = 0; j < 4; j++){
        printf(minoS[stock][0][i - 1][j] ? "■" : "　");
      }

      printf("　");
    }else{
      printf("　　　　　");
    }

    for (int j = 0; j < FIELD_W; j++){ //フィールド表示
      printf(displaybuf[i][j] ? "■" : "　");
    }

    if(i < 21){                        //この後のミノ表示
      printf("　");
      for (int j = 0; j < MINO_W; j++){
        printf(minoS[next[i / MINO_H]][0][i % MINO_H][j] ? "■" : "　");
      }
    }

    printf("\n");
  }
}

bool ishit(int _minoX, int _minoY, int _minoT, int _minoA) {  //あたり判定
  for (int i = 0; i < MINO_H; i ++){
    for (int j = 0; j < MINO_W; j ++){
      if (minoS[_minoT][_minoA][i][j] && field[_minoY + i][_minoX + j]){
      return true;
      }
    }
  }
}

void newmino(){  //ミノ生成
  minoX = 5; minoY = -1;
  minoT = rand() % MINO_T_MAX;
  minoA = 0;
}
void main (){
  memset (field, 0, sizeof(field));  //フィールド初期化

  for (int i = 0; i < FIELD_H; i++)  //壁生成
    field[i][0]  = field[i][FIELD_W - 1] = 1; 
  for (int i = 0; i < FIELD_W; i ++)
    field[FIELD_H - 1][i] = 1; 

  
  for (int i = 0; i < 5; i++){       //この後のミノ生成
  newmino();
  next[i] = minoT;
  }

  newmino();                        //操作対象のミノ生成

  time_t t = time(NULL);            //時間管理用変数

  while (1) {                       //終了判定
    if(ishit(minoX, minoY, minoT, minoA)){
      printf("game over\n");
      break;
    }

    if(_kbhit()) {                 //標準入力時の処理
      switch (_getch()){
        case 'w' : while (!ishit(minoX, minoY + 1, minoT, minoA)){minoY++;}; break;  //上
        case 's' : if (!ishit(minoX, minoY + 1, minoT, minoA)){minoY++;}; break;     //下
        case 'a' : if (!ishit(minoX - 1, minoY, minoT, minoA)){minoX--;}; break;     //左
        case 'd' : if (!ishit(minoX + 1, minoY, minoT, minoA)){minoX++;}; break;     //右
        case 'k' :                                                                   //左回転
        if (!ishit(minoX, minoY, minoT, (minoA + 1)%MINO_A_MAX)){minoA = (minoA + 1) % MINO_A_MAX;}; 
        break;
        case 'l' :                                                                   //右回転
        if (!ishit(minoX, minoY, minoT, (minoA + 3)%MINO_A_MAX)){minoA = (minoA + 3) % MINO_A_MAX;}; 
        break;
        case 'h' :                                                                  //ストック
        if (canstock){        //ストック可能か判定
          if (isstock){       //ストック中か判定
            now = stock;
            stock = minoT;
            newmino();
            minoT = now;
          }else{
            stock = minoT;    //ストックを今のミノで更新

            now = next[0];    //この後のミノ更新
            for(int i = 0; i < 4; i++){
              next[i] = next[i + 1];
            }
            newmino();
            next[4] = minoT;
            minoT = now;

            isstock = 1;     //ストック中判定に更新
          }
          canstock = 0;      //1一度ストックしたのでストック不可に更新
        }
      }

      display();
    };
    if (t != time(NULL)){  //1秒経過
      t = time(NULL);  //時間の基準点更新

      if (ishit(minoX, minoY + 1, minoT, minoA)){  //ミノが地面に接触したとき
        for (int i = 0; i < MINO_H; i ++){
          for (int j = 0; j < MINO_W; j ++){
            field[minoY + i][minoX + j] |= minoS[minoT][minoA][i][j];  //フィールドをミノで更新
          }
        };

        for (int i = 0 ; i < FIELD_H - 1; i++){  
          bool line = true;
          for (int j = 1;  j < FIELD_W - 1; j++){
            if (!field[i][j])  //横幅全部詰まっているか判定
            line = false;
          }
          if(line){
           /*  for (int j = 1; j < FIELD_W - 1; j ++)
            field[i][j] = 0;
             */

            for(int j = i; 0 <= j; j--)
            memcpy(field[j], field[j - 1], FIELD_W);  //上のマスをコピー
          }
        }

        now = next[0];                //ミノ更新
        for(int i = 0; i < 4; i++){
          next[i] = next[i + 1];
        }
        newmino();
        next[4] = minoT;
        minoT = now;
        
        canstock = 1;
      }
      else{
        minoY++;
      };

      display();
    } 
  }

  _getch();
}
