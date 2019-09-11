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
      0,1,0,0,
      0,1,0,0,
      0,1,0,0,
      0,1,0,0,
    },
    //MINO_A_1
    {
      0,0,0,0,
      0,0,0,0,
      1,1,1,1,
      0,0,0,0,
    },
    //MINO_A_2
    {
      0,0,1,0,
      0,0,1,0,
      0,0,1,0,
      0,0,1,0,
    },
    //MINO_A_3
    {
      0,0,0,0,
      1,1,1,1,
      0,0,0,0,
      0,0,0,0,
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
      0,0,1,0,
      0,0,1,0,
      0,1,1,0,
      0,0,0,0,
    },
    //MINO_A_1
    {
      0,0,0,0,
      1,1,1,0,
      0,0,1,0,
      0,0,0,0,
    },
    //MINO_A_2
    {
      0,0,0,0,
      0,1,1,0,
      0,1,0,0,
      0,1,0,0,
    },
    //MINO_A_3
    {
      0,0,0,0,
      0,1,0,0,
      0,1,1,1,
      0,0,0,0,
    },
  },
  //MINO_T_L
  {
    //MINO_A_0
    {
      0,1,0,0,
      0,1,0,0,
      0,1,1,0,
      0,0,0,0,
    },
    //MINO_A_1
  {
      0,0,0,0,
      0,0,1,0,
      1,1,1,0,
      0,0,0,0,
    },
    //MINO_A_2
    {
      0,0,0,0,
      0,1,1,0,
      0,0,1,0,
      0,0,1,0,
    },
    //MINO_A_3
    {
      0,0,0,0,
      0,1,1,1,
      0,1,0,0,
      0,0,0,0,
    },
  },
  //MINO_T_T
  {
    //MINO_A_0
    {
      0,0,0,0,
      1,1,1,0,
      0,1,0,0,
      0,0,0,0,
    },
    //MINO_A_1
    {
      0,0,0,0,
      0,1,0,0,
      0,1,1,0,
      0,1,0,0,
    },
    //MINO_A_2
    {
      0,0,0,0,
      0,0,1,0,
      0,1,1,1,
      0,0,0,0,
    },
    //MINO_A_3
    {
      0,0,1,0,
      0,1,1,0,
      0,0,1,0,
      0,0,0,0,
    },
  }
};

int minoT = 0, minoA = 0;
int minoX = 5, minoY = 0;

void display() {  //表示用関数
 memcpy(displaybuf, field, sizeof(field));  

      for (int i = 0; i < MINO_H; i ++)  //ミノによる画面更新
        for (int j = 0; j < MINO_W; j ++)
        displaybuf[minoY + i][minoX + j] |= minoS[minoT][minoA][i][j];
      
      
      system("cls");  //画面リセット
      
      for (int i = 0; i < FIELD_H; i++){  
        for (int j = 0; j < FIELD_W; j++)
          printf(displaybuf[i][j] ? "■" : "　");
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
  minoX = 5; minoY = 0;
  minoT = rand() % MINO_T_MAX;
  minoA = rand() % MINO_A_MAX;
}
void main (){
  memset (field, 0, sizeof(field));  //フィールド初期化

  for (int i = 0; i < FIELD_H; i++)  //壁生成
    field[i][0]  = field[i][FIELD_W - 1] = 1; 
  for (int i = 0; i < FIELD_W; i ++)
    field[FIELD_H - 1][i] = 1; 

  newmino();

  time_t t = time(NULL);  
  while (1) {
    if(_kbhit()) {  //標準入力時の処理
      switch (_getch()){
        case 'w' : while (!ishit(minoX, minoY + 1, minoT, minoA)){minoY++;}; break;
        case 's' : if (!ishit(minoX, minoY + 1, minoT, minoA)){minoY++;}; break;
        case 'a' : if (!ishit(minoX - 1, minoY, minoT, minoA)){minoX--;}; break;
        case 'd' : if (!ishit(minoX + 1, minoY, minoT, minoA)){minoX++;}; break;
        case 'k' : if (!ishit(minoX, minoY, minoT, (minoA + 1)%MINO_A_MAX)){minoA = (minoA + 1) % MINO_A_MAX;};
        case 'l' : if (!ishit(minoX, minoY, minoT, (minoA - 1)%MINO_A_MAX)){minoA = (minoA - 1) % MINO_A_MAX;};
      }
      display();
    };
    if (t != time(NULL)){  //1秒経過
      t = time(NULL);

      if (ishit(minoX, minoY + 1, minoT, minoA)){
        for (int i = 0; i < MINO_H; i ++){
          for (int j = 0; j < MINO_W; j ++){
            field[minoY + i][minoX + j] |= minoS[minoT][minoA][i][j];  //フィールドをミノで更新
          }
        };

        for(int i = 0 ; i < FIELD_H - 1; i++){  
          bool line = true;
          for (int j = 1;  j < FIELD_W - 1; j++){
            if (!field[i][j])  //横幅全部詰まっているか判定
            line = false;
          }
          if(line){
           /*  for (int j = 1; j < FIELD_W - 1; j ++)
            field[i][j] = 0;
             */

            for(int j = i; 0<= j; j--)
            memcpy(field[j], field[j - 1], FIELD_W);  //上のマスをコピー
          }
        }
        
        newmino();
      }
      else{
        minoY++;
        };
      display();
    } 
  }

  _getch();
}
