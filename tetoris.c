#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define FIELD_H 22  //�t�B�[���h�c��
#define FIELD_W 12  //�t�B�[���h����
#define STOCK_H 4   //�X�g�b�N�c��
#define STOCK_W 5   //�X�g�b�N����
#define MINO_H 4    //�~�m�c��
#define MINO_W 4    //�~�m����

char field[FIELD_H][FIELD_W] = {""};                              //�t�B�[���h�p
char displaybuf[FIELD_H][FIELD_W + STOCK_W + MINO_W + 1] = {""};  //�\���p
int fieldcolor[FIELD_H][FIELD_W] = {};                            //�t�B�[���h�F�p
int color[FIELD_H][FIELD_W + STOCK_W + MINO_W + 1] = {};          //�\���F�p

enum {            //�~�m�̎��
  MINO_T_I,
  MINO_T_O,
  MINO_T_S,
  MINO_T_Z,
  MINO_T_J,
  MINO_T_L,
  MINO_T_T,
  MINO_T_MAX
};
enum {           //�p�x�̎��
  MINO_A_0,
  MINO_A_1,
  MINO_A_2,
  MINO_A_3,
  MINO_A_MAX
};

char minoS[MINO_T_MAX][MINO_A_MAX][MINO_H][MINO_W] = {   //�~�m
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

int next[5] = {};   //���̌�̃~�m�̎��
int stock;          //�X�g�b�N�~�m
int isstock = 0;    //�X�g�b�N��������
int canstock = 1;   //�X�g�b�N�\������

int minoX = 5, minoY = -0;  //����Ώۂ̃~�m�̌��ݒn
int minoT = 0, minoA = 0;  //����Ώۂ̃~�m�̎�ނƊp�x

void change(int* x, int* y){    //����
  int z = *x;
  *x = *y;
  *y = z;
}

void display() {                         //�\���p�֐�
  if(isstock)
    for(int i = 0; i < STOCK_H; i ++){      //�X�g�b�N�X�V
      memcpy(displaybuf[i], minoS[stock][0][i], STOCK_W - 1);
      for (int j = 0; j < (STOCK_W - 1); j ++){
        color[i][j] = minoS[stock][0][i][j] * (stock + 1);
      }
    }

  for(int i = 0; i < FIELD_H; i ++){     //�t�B�[���h�X�V
    memcpy(displaybuf[i] + STOCK_W, field[i], FIELD_W);
    for (int j = 0; j < FIELD_W; j ++){
        color[i][j + STOCK_W] = fieldcolor[i][j];
    }
  }

  for(int i = 0; i < MINO_H * 5; i ++){  //���̌�̃~�m�X�V
    memcpy(displaybuf[i] + STOCK_W + FIELD_W + 1, minoS[next[i / MINO_H]][0][i % MINO_H], MINO_W);
    for (int j = 0; j < MINO_W; j ++){
        color[i][j + STOCK_W + FIELD_W + 1] = minoS[next[i / MINO_H]][0][i % MINO_H][j] * (next[i / MINO_H] + 1);
    }
  }
  
  for (int i = 0; i < MINO_H; i ++){  //�~�m�̈ʒu�X�V
    for (int j = 0; j < MINO_W; j ++){
      displaybuf[minoY + i][minoX + STOCK_W + j] |= minoS[minoT][minoA][i][j];
      color[minoY + i][minoX + STOCK_W + j] += minoS[minoT][minoA][i][j] * (minoT + 1);
    }
  }

  system("cls");  //��ʃ��Z�b�g
      
  printf("\x1b[0m");
  printf("����������\n");

  for (int i = 0; i < FIELD_H; i++){
    for (int j = 0; j < FIELD_W + STOCK_W + MINO_W + 1; j++){ //�t�B�[���h�\��
      printf(displaybuf[i][j] ? "\x1b[3%xm" "��": "�@", color[i][j]);
    }

    printf("\n");
  }
}

bool ishit(int _minoX, int _minoY, int _minoT, int _minoA) {  //�����蔻��
  for (int i = 0; i < MINO_H; i ++){
    for (int j = 0; j < MINO_W; j ++){
      if (minoS[_minoT][_minoA][i][j] && field[_minoY + i][_minoX + j]){
      return true;
      }
    }
  }
}

void defomino(){  //�~�m��l
  minoX = 5; minoY = -0;
  minoA = 0;
}

int newmino(){    //�V�~�m����
  return rand() % MINO_T_MAX;
}

void updatemino(){               //�~�m�X�V
  minoT = next[0];               //����~�m�X�V
  defomino();
  for (int i = 0; i < 4; i ++){  //���̌�̃~�m�X�V
    next[i] = next[i + 1];
  }
  next[4] = newmino();
}

void main (){
  for (int i = 0; i < FIELD_H; i++){  //�ǐ���
    field[i][0]  = field[i][FIELD_W - 1] = 1;
    fieldcolor[i][0] = fieldcolor[i][FIELD_W - 1] = 7;
  }
  for (int i = 0; i < FIELD_W; i++){
    field[FIELD_H - 1][i] = 1; 
    fieldcolor[FIELD_H - 1][i] = 7;
  }

  
  for (int i = 0; i < 5; i++){      //���̌�̃~�m����
    next[i] = newmino();
  }
  minoT = newmino();                //����Ώۂ̃~�m����

  time_t t = time(NULL);            //���ԊǗ��p�ϐ�

  while (1) {                      
    if(ishit(minoX, minoY, minoT, minoA)){ //�I������
      printf("\x1b[1m" "game over! press any key!\n");
      break;
    }

    if(_kbhit()) {                  //�W�����͎��̏���
      switch (_getch()){
        case 'w' : while (!ishit(minoX, minoY + 1, minoT, minoA)){minoY++;}; break;  //��
        case 's' : if (!ishit(minoX, minoY + 1, minoT, minoA)){minoY++;}; break;     //��
        case 'a' : if (!ishit(minoX - 1, minoY, minoT, minoA)){minoX--;}; break;     //��
        case 'd' : if (!ishit(minoX + 1, minoY, minoT, minoA)){minoX++;}; break;     //�E
        case 'k' :                                                                   //����]
        if (!ishit(minoX, minoY, minoT, (minoA + 1)%MINO_A_MAX)){minoA = (minoA + 1) % MINO_A_MAX;}; 
        break;
        case 'l' :                                                                   //�E��]
        if (!ishit(minoX, minoY, minoT, (minoA + 3)%MINO_A_MAX)){minoA = (minoA + 3) % MINO_A_MAX;}; 
        break;
        case 'j' :                                                                  //�X�g�b�N
        if (canstock){        //�X�g�b�N�\������
          if (isstock){       //�X�g�b�N��������
            change(&stock, &minoT);
            defomino();
          }else{
            stock = minoT;    //�X�g�b�N�����̃~�m�ōX�V
            updatemino();

            isstock = 1;     //�X�g�b�N������ɍX�V
          }
          canstock = 0;      //��x�X�g�b�N�����̂ŃX�g�b�N�s�ɍX�V
        }
      }

      display();
    };
    if (t != time(NULL)){  //1�b�o��
      t = time(NULL);      //���Ԃ̊�_�X�V

      if (ishit(minoX, minoY + 1, minoT, minoA)){  //�~�m���n�ʂɐڐG�����Ƃ�
        for (int i = 0; i < MINO_H; i ++){
          for (int j = 0; j < MINO_W; j ++){
            field[minoY + i][minoX + j] |= minoS[minoT][minoA][i][j];  //�t�B�[���h���~�m�ōX�V
            fieldcolor[minoY + i][minoX + j] += minoS[minoT][minoA][i][j] * (minoT + 1);
          }
        };

        for (int i = 0 ; i < FIELD_H - 1; i++){  //�����S���l�܂��Ă��邩����
          bool line = true;
          for (int j = 1;  j < FIELD_W - 1; j++){
            if (!field[i][j])  
            line = false;
          }
          if(line){
            for(int j = i; 0 < j; j--){
              memcpy(field[j], field[j - 1], FIELD_W);  //��̃}�X���R�s�[
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
