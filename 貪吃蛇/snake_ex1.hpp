#pragma once

#include <iostream>
#include <list>
#include <windows.h>
#include <conio.h>

#define edgex 60  //X軸邊界
#define edgey 28  //y軸邊界

using namespace std;

list<int> snakex;  //記錄蛇x座標的list
list<int> snakey;  //記錄蛇y座標的list
char kbinput;  //紀錄鍵盤輸入的值
int endgame,score;  //紀錄是否結束遊戲和分數

typedef struct f{  //宣告存放食物座標的struct
    int x,y;
}foodtyp;

foodtyp food;

void to(int x, int y){  //設置游標
    COORD pos;
    HANDLE hOutput;
    pos.X = x;
    pos.Y = y;
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput, pos);
}

void print(){  //印出蛇的身體
               //遍歷x座標的list與y座標的list
    auto x=snakex.begin();
    auto y=snakey.begin();
    for(;x!=snakex.end();x++,y++){  
        to(*x,*y);  //設置游標到x,y
        cout << "■";  //印出身體
    }  
}

void creatfood(){  //創造食物
    int checkfood=1;  //紀錄食物是否合理
    while(true){
        food.x=(rand()%(edgex-1))+1;  //隨機產生食物的x座標
        food.y=(rand()%(edgey-1))+1;  //隨機產生食物的y座標
        if(food.x%2!=0) continue;  //檢查食物的x是否為偶數
                                   //檢查食物是否和蛇的身體重疊
        for(auto itx=snakex.begin(),ity=snakey.begin();itx!=snakex.end();itx++,ity++){
            if(*itx==food.x&&*ity==food.y){
                checkfood=0;  //有重疊的話就把checkfood設成0
                break;
            } 
        }  
        if(checkfood) break;  //如果符合條件就break,否則就重新產生
    }
    to(food.x,food.y);  //設置游標到食物的x與y
    cout << "■";  //印出食物
}

void setup(){  //初始化
    int dx[]={2,0,-2,0,0};
    int dy[]={0,1,0,-1,0};
    int x=0,y=0,p=0;
    kbinput='a',endgame=score=0;
    //印出邊界
    while(p!=4){
        to(x,y);
        cout << "■";
        if(x+dx[p]>edgex||y+dy[p]>edgey||x+dx[p]<0||y+dy[p]<0){
            //如果下一個超出邊界就換另一個方向
            p++;
        }
        x+=dx[p],y+=dy[p];  //每次x或y加一
    }  
    //設定蛇的初始位置
    for(int i=0;i<=10;i+=2){
        snakex.push_back(24+i);  //把蛇的x座標放入List
        snakey.push_back(20);  //把蛇的y座標放入List
    }  
    print();  //印出蛇
    to(80,12),cout << "Score = " << score;  //印出初始分數
    srand(time(NULL));  //設定亂數
    creatfood();  //創造食物
}

void getmove(){  //讀取鍵盤輸入的值
    if(kbinput!='s'&&GetAsyncKeyState(VK_UP)) kbinput='w';
    if(kbinput!='w'&&GetAsyncKeyState(VK_DOWN)) kbinput='s';
    if(kbinput!='a'&&GetAsyncKeyState(VK_RIGHT)) kbinput='d';
    if(kbinput!='d'&&GetAsyncKeyState(VK_LEFT)) kbinput='a';
}

int check(int x,int y){  //確認蛇是否碰到邊界或者碰到自己
    if(x==0||x==edgex||y==0||y==edgey) return 1;  //如果碰到邊界就回傳1
    for(auto cx=snakex.begin(),cy=snakey.begin();cx!=snakex.end();cx++,cy++){
        if(*cx==x&&*cy==y) return 1;  //如果碰到自己就回傳1
    }  
    return 0;  //否則回傳0
}

void movesnake(){
    int movex=snakex.front();  //取出蛇的x頭座標
    int movey=snakey.front();  //取出蛇的y頭座標
                               //預覽蛇要走的位置
    if(kbinput=='w') movey--;  //如果往上,y就-1
    if(kbinput=='a') movex-=2;  //如果往左,x就-2
    if(kbinput=='s') movey++;  //如果往下,y就+1
    if(kbinput=='d') movex+=2;  //如果往下,x就+2
    if(check(movex,movey)){  //判斷有沒有符合規則
        endgame=1;  //如果不符合規則就遊戲結束
        return;
    }
    snakex.push_front(movex);  //把新的x座標放入list裡
    snakey.push_front(movey);  //把新的y座標放入list裡
    if(snakex.front()==food.x&&snakey.front()==food.y){  //判斷有沒有吃到食物
        to(88,12),cout << ++score;  //印出新的分數
        creatfood();  //創造新的食物
    }else{  //沒有的話要刪除最後一個節點,否則會留在螢幕上
        to(snakex.back(),snakey.back());  //設置游標到蛇最後一個節點的位置
        cout << "  ";  //把原本的 ■ 覆蓋掉
        snakex.pop_back();  //移除最後一個x
        snakey.pop_back();  //移除最後一個y
    }
    print();  //印出蛇
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
