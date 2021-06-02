#pragma once

#include <iostream>
#include <list>
#include <windows.h>
#include <conio.h>

#define edgex 60  //X�b���
#define edgey 28  //y�b���

using namespace std;

list<int> snakex;  //�O���Dx�y�Ъ�list
list<int> snakey;  //�O���Dy�y�Ъ�list
char kbinput;  //������L��J����
int endgame,score;  //�����O�_�����C���M����

typedef struct f{  //�ŧi�s�񭹪��y�Ъ�struct
    int x,y;
}foodtyp;

foodtyp food;

void to(int x, int y){  //�]�m���
    COORD pos;
    HANDLE hOutput;
    pos.X = x;
    pos.Y = y;
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput, pos);
}

void print(){  //�L�X�D������
               //�M��x�y�Ъ�list�Py�y�Ъ�list
    auto x=snakex.begin();
    auto y=snakey.begin();
    for(;x!=snakex.end();x++,y++){  
        to(*x,*y);  //�]�m��Ш�x,y
        cout << "��";  //�L�X����
    }  
}

void creatfood(){  //�гy����
    int checkfood=1;  //���������O�_�X�z
    while(true){
        food.x=(rand()%(edgex-1))+1;  //�H�����ͭ�����x�y��
        food.y=(rand()%(edgey-1))+1;  //�H�����ͭ�����y�y��
        if(food.x%2!=0) continue;  //�ˬd������x�O�_������
                                   //�ˬd�����O�_�M�D�����魫�|
        for(auto itx=snakex.begin(),ity=snakey.begin();itx!=snakex.end();itx++,ity++){
            if(*itx==food.x&&*ity==food.y){
                checkfood=0;  //�����|���ܴN��checkfood�]��0
                break;
            } 
        }  
        if(checkfood) break;  //�p�G�ŦX����Nbreak,�_�h�N���s����
    }
    to(food.x,food.y);  //�]�m��Ш쭹����x�Py
    cout << "��";  //�L�X����
}

void setup(){  //��l��
    int dx[]={2,0,-2,0,0};
    int dy[]={0,1,0,-1,0};
    int x=0,y=0,p=0;
    kbinput='a',endgame=score=0;
    //�L�X���
    while(p!=4){
        to(x,y);
        cout << "��";
        if(x+dx[p]>edgex||y+dy[p]>edgey||x+dx[p]<0||y+dy[p]<0){
            //�p�G�U�@�ӶW�X��ɴN���t�@�Ӥ�V
            p++;
        }
        x+=dx[p],y+=dy[p];  //�C��x��y�[�@
    }  
    //�]�w�D����l��m
    for(int i=0;i<=10;i+=2){
        snakex.push_back(24+i);  //��D��x�y�Щ�JList
        snakey.push_back(20);  //��D��y�y�Щ�JList
    }  
    print();  //�L�X�D
    to(80,12),cout << "Score = " << score;  //�L�X��l����
    srand(time(NULL));  //�]�w�ü�
    creatfood();  //�гy����
}

void getmove(){  //Ū����L��J����
    if(kbinput!='s'&&GetAsyncKeyState(VK_UP)) kbinput='w';
    if(kbinput!='w'&&GetAsyncKeyState(VK_DOWN)) kbinput='s';
    if(kbinput!='a'&&GetAsyncKeyState(VK_RIGHT)) kbinput='d';
    if(kbinput!='d'&&GetAsyncKeyState(VK_LEFT)) kbinput='a';
}

int check(int x,int y){  //�T�{�D�O�_�I����ɩΪ̸I��ۤv
    if(x==0||x==edgex||y==0||y==edgey) return 1;  //�p�G�I����ɴN�^��1
    for(auto cx=snakex.begin(),cy=snakey.begin();cx!=snakex.end();cx++,cy++){
        if(*cx==x&&*cy==y) return 1;  //�p�G�I��ۤv�N�^��1
    }  
    return 0;  //�_�h�^��0
}

void movesnake(){
    int movex=snakex.front();  //���X�D��x�Y�y��
    int movey=snakey.front();  //���X�D��y�Y�y��
                               //�w���D�n������m
    if(kbinput=='w') movey--;  //�p�G���W,y�N-1
    if(kbinput=='a') movex-=2;  //�p�G����,x�N-2
    if(kbinput=='s') movey++;  //�p�G���U,y�N+1
    if(kbinput=='d') movex+=2;  //�p�G���U,x�N+2
    if(check(movex,movey)){  //�P�_���S���ŦX�W�h
        endgame=1;  //�p�G���ŦX�W�h�N�C������
        return;
    }
    snakex.push_front(movex);  //��s��x�y�Щ�Jlist��
    snakey.push_front(movey);  //��s��y�y�Щ�Jlist��
    if(snakex.front()==food.x&&snakey.front()==food.y){  //�P�_���S���Y�쭹��
        to(88,12),cout << ++score;  //�L�X�s������
        creatfood();  //�гy�s������
    }else{  //�S�����ܭn�R���̫�@�Ӹ`�I,�_�h�|�d�b�ù��W
        to(snakex.back(),snakey.back());  //�]�m��Ш�D�̫�@�Ӹ`�I����m
        cout << "  ";  //��쥻�� �� �л\��
        snakex.pop_back();  //�����̫�@��x
        snakey.pop_back();  //�����̫�@��y
    }
    print();  //�L�X�D
}
void snake_ex1() {
    setup();
    while(endgame==0){
        getmove();
        movesnake();
        Sleep(100);
    }
    to(80,14),cout << "Game Over!";
    to(80,16),system("pause");
}
