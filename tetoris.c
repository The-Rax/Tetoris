#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define FIELD_H 22  //�t�B�[���h�c��
#define FIELD_W 12  //�t�B�[���h����
#define MINO_H 4    //�~�m�c��
#define MINO_W 4    //�~�m����

char field[FIELD_H][FIELD_W];       //�t�B�[���h�p
char displaybuf[FIELD_H][FIELD_W];  //�\���p

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

int next [5] = {};  //���̌�̃~�m�̎��
int now;            //�~�m�X�V�p�̉��ꏊ
int stock;          //�X�g�b�N�p
int isstock = 0;    //�X�g�b�N��������
int canstock = 1;   //�X�g�b�N�\������

int minoX = 5, minoY = -1;  //����Ώۂ̃~�m�̌��ݒn
int minoT = 0, minoA = 0;  //����Ώۂ̃~�m�̎�ނƊp�x

void display() {  //�\���p�֐�
 memcpy(displaybuf, field, sizeof(field));  

  for (int i = 0; i < MINO_H; i ++)  //�~�m�ɂ���ʍX�V
    for (int j = 0; j < MINO_W; j ++)
      displaybuf[minoY + i][minoX + j] |= minoS[minoT][minoA][i][j];
      
      
  system("cls");  //��ʃ��Z�b�g
      
  for (int i = 0; i < FIELD_H; i++){
    if (i == 0){                       //�X�g�b�N��ʕ\��
      printf("����������");
    }else if (i < 5 && isstock == 1){
      for(int j = 0; j < 4; j++){
        printf(minoS[stock][0][i - 1][j] ? "��" : "�@");
      }

      printf("�@");
    }else{
      printf("�@�@�@�@�@");
    }

    for (int j = 0; j < FIELD_W; j++){ //�t�B�[���h�\��
      printf(displaybuf[i][j] ? "��" : "�@");
    }

    if(i < 21){                        //���̌�̃~�m�\��
      printf("�@");
      for (int j = 0; j < MINO_W; j++){
        printf(minoS[next[i / MINO_H]][0][i % MINO_H][j] ? "��" : "�@");
      }
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

void newmino(){  //�~�m����
  minoX = 5; minoY = -1;
  minoT = rand() % MINO_T_MAX;
  minoA = 0;
}
void main (){
  memset (field, 0, sizeof(field));  //�t�B�[���h������

  for (int i = 0; i < FIELD_H; i++)  //�ǐ���
    field[i][0]  = field[i][FIELD_W - 1] = 1; 
  for (int i = 0; i < FIELD_W; i ++)
    field[FIELD_H - 1][i] = 1; 

  
  for (int i = 0; i < 5; i++){       //���̌�̃~�m����
  newmino();
  next[i] = minoT;
  }

  newmino();                        //����Ώۂ̃~�m����

  time_t t = time(NULL);            //���ԊǗ��p�ϐ�

  while (1) {                       //�I������
    if(ishit(minoX, minoY, minoT, minoA)){
      printf("game over\n");
      break;
    }

    if(_kbhit()) {                 //�W�����͎��̏���
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
        case 'h' :                                                                  //�X�g�b�N
        if (canstock){        //�X�g�b�N�\������
          if (isstock){       //�X�g�b�N��������
            now = stock;
            stock = minoT;
            newmino();
            minoT = now;
          }else{
            stock = minoT;    //�X�g�b�N�����̃~�m�ōX�V

            now = next[0];    //���̌�̃~�m�X�V
            for(int i = 0; i < 4; i++){
              next[i] = next[i + 1];
            }
            newmino();
            next[4] = minoT;
            minoT = now;

            isstock = 1;     //�X�g�b�N������ɍX�V
          }
          canstock = 0;      //1��x�X�g�b�N�����̂ŃX�g�b�N�s�ɍX�V
        }
      }

      display();
    };
    if (t != time(NULL)){  //1�b�o��
      t = time(NULL);  //���Ԃ̊�_�X�V

      if (ishit(minoX, minoY + 1, minoT, minoA)){  //�~�m���n�ʂɐڐG�����Ƃ�
        for (int i = 0; i < MINO_H; i ++){
          for (int j = 0; j < MINO_W; j ++){
            field[minoY + i][minoX + j] |= minoS[minoT][minoA][i][j];  //�t�B�[���h���~�m�ōX�V
          }
        };

        for (int i = 0 ; i < FIELD_H - 1; i++){  
          bool line = true;
          for (int j = 1;  j < FIELD_W - 1; j++){
            if (!field[i][j])  //�����S���l�܂��Ă��邩����
            line = false;
          }
          if(line){
           /*  for (int j = 1; j < FIELD_W - 1; j ++)
            field[i][j] = 0;
             */

            for(int j = i; 0 <= j; j--)
            memcpy(field[j], field[j - 1], FIELD_W);  //��̃}�X���R�s�[
          }
        }

        now = next[0];                //�~�m�X�V
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
