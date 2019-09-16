#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define FIELD_H 22  //フィールド縦幅
#define FIELD_W 12  //フィールド横幅
#define STOCK_H 4   //ストック縦幅
#define STOCK_W 5   //ストック横幅
#define MINO_H 4    //ミノ縦幅
#define MINO_W 4    //ミノ横幅

char field[FIELD_H][FIELD_W] = {""};                              //フィールド用
char displaybuf[FIELD_H][FIELD_W + STOCK_W + MINO_W + 1] = {""};  //表示用
int fieldcolor[FIELD_H][FIELD_W] = {};                            //フィールド色用
int color[FIELD_H][FIELD_W + STOCK_W + MINO_W + 1] = {};          //表示色用

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

int next[5] = {};   //この後のミノの種類
int stock;          //ストックミノ
int isstock = 0;    //ストック中か判定
int canstock = 1;   //ストック可能か判定

int minoX = 5, minoY = -0;  //操作対象のミノの現在地
int minoT = 0, minoA = 0;  //操作対象のミノの種類と角度

void change(int* x, int* y){    //交換
  int z = *x;
  *x = *y;
  *y = z;
}

void display() {                         //表示用関数
  if(isstock)
    for(int i = 0; i < STOCK_H; i ++){      //ストック更新
      memcpy(displaybuf[i], minoS[stock][0][i], STOCK_W - 1);
      for (int j = 0; j < (STOCK_W - 1); j ++){
        color[i][j] = minoS[stock][0][i][j] * (stock + 1);
      }
    }

  for(int i = 0; i < FIELD_H; i ++){     //フィールド更新
    memcpy(displaybuf[i] + STOCK_W, field[i], FIELD_W);
    for (int j = 0; j < FIELD_W; j ++){
        color[i][j + STOCK_W] = fieldcolor[i][j];
    }
  }

  for(int i = 0; i < MINO_H * 5; i ++){  //この後のミノ更新
    memcpy(displaybuf[i] + STOCK_W + FIELD_W + 1, minoS[next[i / MINO_H]][0][i % MINO_H], MINO_W);
    for (int j = 0; j < MINO_W; j ++){
        color[i][j + STOCK_W + FIELD_W + 1] = minoS[next[i / MINO_H]][0][i % MINO_H][j] * (next[i / MINO_H] + 1);
    }
  }
  
  for (int i = 0; i < MINO_H; i ++){  //ミノの位置更新
    for (int j = 0; j < MINO_W; j ++){
      displaybuf[minoY + i][minoX + STOCK_W + j] |= minoS[minoT][minoA][i][j];
      color[minoY + i][minoX + STOCK_W + j] += minoS[minoT][minoA][i][j] * (minoT + 1);
    }
  }

  system("cls");  //画面リセット
      
  printf("\x1b[0m");
  printf("ｓｔｏｃｋ\n");

  for (int i = 0; i < FIELD_H; i++){
    for (int j = 0; j < FIELD_W + STOCK_W + MINO_W + 1; j++){ //フィールド表示
      printf(displaybuf[i][j] ? "\x1b[3%xm" "■": "　", color[i][j]);
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

void defomino(){  //ミノ基準値
  minoX = 5; minoY = -0;
  minoA = 0;
}

int newmino(){    //新ミノ生成
  return rand() % MINO_T_MAX;
}

void updatemino(){               //ミノ更新
  minoT = next[0];               //操作ミノ更新
  defomino();
  for (int i = 0; i < 4; i ++){  //この後のミノ更新
    next[i] = next[i + 1];
  }
  next[4] = newmino();
}

void main (){
  for (int i = 0; i < FIELD_H; i++){  //壁生成
    field[i][0]  = field[i][FIELD_W - 1] = 1;
    fieldcolor[i][0] = fieldcolor[i][FIELD_W - 1] = 7;
  }
  for (int i = 0; i < FIELD_W; i++){
    field[FIELD_H - 1][i] = 1; 
    fieldcolor[FIELD_H - 1][i] = 7;
  }

  
  for (int i = 0; i < 5; i++){      //この後のミノ生成
    next[i] = newmino();
  }
  minoT = newmino();                //操作対象のミノ生成

  time_t t = time(NULL);            //時間管理用変数

  while (1) {                      
    if(ishit(minoX, minoY, minoT, minoA)){ //終了判定
      printf("\x1b[1m" "game over! press any key!\n");
      break;
    }

    if(_kbhit()) {                  //標準入力時の処理
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
        case 'j' :                                                                  //ストック
        if (canstock){        //ストック可能か判定
          if (isstock){       //ストック中か判定
            change(&stock, &minoT);
            defomino();
          }else{
            stock = minoT;    //ストックを今のミノで更新
            updatemino();

            isstock = 1;     //ストック中判定に更新
          }
          canstock = 0;      //一度ストックしたのでストック不可に更新
        }
      }

      display();
    };
    if (t != time(NULL)){  //1秒経過
      t = time(NULL);      //時間の基準点更新

      if (ishit(minoX, minoY + 1, minoT, minoA)){  //ミノが地面に接触したとき
        for (int i = 0; i < MINO_H; i ++){
          for (int j = 0; j < MINO_W; j ++){
            field[minoY + i][minoX + j] |= minoS[minoT][minoA][i][j];  //フィールドをミノで更新
            fieldcolor[minoY + i][minoX + j] += minoS[minoT][minoA][i][j] * (minoT + 1);
          }
        };

        for (int i = 0 ; i < FIELD_H - 1; i++){  //横幅全部詰まっているか判定
          bool line = true;
          for (int j = 1;  j < FIELD_W - 1; j++){
            if (!field[i][j])  
            line = false;
          }
          if(line){
            for(int j = i; 0 < j; j--){
              memcpy(field[j], field[j - 1], FIELD_W);  //上のマスをコピー
              memcpy(fieldcolor[j], fieldcolor[j - 1], sizeof(int) * FIELD_W);
            }
            memset(field[0] + 1, 0, FIELD_W - 2);
            memset(fieldcolor[0] + 1, 0, sizeof(int) * (FIELD_W - 2));
          }
        }

        updatemino();

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
