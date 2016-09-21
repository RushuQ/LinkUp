#pragma once
//algorithm
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>
#include "cocos2d.h"

using namespace std;

//
struct position
{
	int x;
	int y;
	position():x(-1),y(-1){}
};

struct PicNode
{
	position c;
	bool cross;

	PicNode(): cross(true){}
};

//
position change(int i);    //�ѵ�i��Ԫ��ת��Ϊpic������±�

//�ѳ���Ϊx����������������������
void random(int *p,int x=24);


class LU 
{
public:
	vector<position> path[13];
	int NumOfPath;

	void init();
	void UpdateNodecross(int *r);
	bool Straight(position b, position e);
	bool Acorner(int i,position b, position e);
	bool Tcorner(int i,position b, position e);
	void UpdatePath(int *p);
private:
	PicNode pic[6][9];
	
};




