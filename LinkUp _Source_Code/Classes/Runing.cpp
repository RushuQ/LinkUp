#include "Runing.h"

USING_NS_CC;

position change(int i) {         //把传入的第i个元素转化成pic的下标
	position pos;
	int a, b, m;
	for (b = 0,m = 0; b < 7; b++) {
		for (a = 0; a < 4; a++) {
			if ((a == 0 || a == 3) && (b == 0 || b == 6)) continue;
			else if (m < i) m += 1;
			else {
				pos.x = a + 1;
				pos.y = b + 1;
				return pos;
			}
		}
	}
}

void random(int *p, int x) {
	int i,k,y,f;
	srand((int)time(0));
	for (i = 0; i < x; i++) {
		p[i] = i;
	}
	for (i = 0; i < x; i++) {
		y = rand() % x;
		k = p[i];
		p[i] = p[y];
		p[y] = k;
	}
	p = NULL;
}


void LU::init() {
	int i, j;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 6; j++) {
			pic[j][i].c.x = 120 * j + 60;
			pic[j][i].c.y = 1280 - 120 - 60 - (i * 120);
		}
	}
}

void LU::UpdateNodecross(int *r) {
	int i, j;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 6; j++) {
			pic[j][i].cross = true;
		}
	}
	position pos;
	for (i = 0; i < 24; i++) {
		if (r[i] >= 0) {
			pos = change(r[i]);
			pic[pos.x][pos.y].cross = false;
		}
	}
}

bool LU::Straight(position b, position e) {
	if (b.x == e.x ) {
		if (b.y < e.y) {
			for (int y = b.y + 1; y < e.y; y++) {
				if (pic[b.x][y].cross == false) return false;
			}
		}
		else {
			for (int y = e.y + 1; y < b.y; y++) {
				if (pic[b.x][y].cross == false) return false;
			}
		}
		return true;
	}
	else if (b.y == e.y) {
		if (b.x < e.x) {
			for (int x = b.x + 1; x < e.x; x++) {
				if (pic[x][b.y].cross == false) return false;
			}
		}
		else {
			for (int x = e.x + 1; x < b.x; x++) {
				if (pic[x][b.y].cross == false) return false;
			}
		}
		return true;
	}
	else return false;
}
bool LU::Acorner(int i,position b, position e) {
	position k;
	k.x = b.x, k.y = e.y;
	if (pic[k.x][k.y].cross && Straight(b, k) && Straight(k, e)) {
		path[i].push_back(pic[b.x][b.y].c);
		path[i].push_back(pic[k.x][k.y].c);
		path[i].push_back(pic[e.x][e.y].c);
		return true;
	}
	else {
		k.x = e.x, k.y = b.y;
		if (pic[k.x][k.y].cross && Straight(b, k) && Straight(k, e)) {
			path[i].push_back(pic[b.x][b.y].c);
			path[i].push_back(pic[k.x][k.y].c);
			path[i].push_back(pic[e.x][e.y].c);
			return true;
		}
	}
	return false;
}
bool LU::Tcorner(int j,position b, position e){
	position k1,k2;
    k1.y = b.y, k2.y = e.y;
	for (int i = 0; i < 6; i++) {
		k1.x = k2.x = i;
		if (pic[i][k1.y].cross &&pic[i][k2.y].cross) {
			if (Straight(b, k1) && Straight(k1, k2) && Straight(e, k2)) {
				path[j].push_back(pic[b.x][b.y].c);
				path[j].push_back(pic[k1.x][k1.y].c);
				path[j].push_back(pic[k2.x][k2.y].c);
				path[j].push_back(pic[e.x][e.y].c);
				return true;
			}
		}
	}
	k1.x = b.x, k2.x = e.x;
	for (int i = 0; i < 9; i++) {
		k1.y = k2.y = i;
		if (pic[k1.x][i].cross &&pic[k2.x][i].cross) {
			if (Straight(b, k1) && Straight(k1, k2) && Straight(e, k2)) {
				path[j].push_back(pic[b.x][b.y].c);
				path[j].push_back(pic[k1.x][k1.y].c);
				path[j].push_back(pic[k2.x][k2.y].c);
				path[j].push_back(pic[e.x][e.y].c);
				return true;
			}
		}
	}
	return false;
}

void LU::UpdatePath(int *p) {
	int i, j;
	position pos, b, e;
	UpdateNodecross(p);
	NumOfPath = 0;
	for (i = 0; i < 13; i++) path[i].clear();    //清除旧路径
	for (i = 0; i < 24; i+=2) {
		j = (i + 2) / 2;
		if (p[i] != -1) {
			b = change(p[i]);
			e = change(p[i+1]);
			if (Straight(b, e)) {
				path[j].push_back(pic[b.x][b.y].c);
				path[j].push_back(pic[e.x][e.y].c);
				NumOfPath++;
			}
			else if (Acorner(j, b, e)) { NumOfPath++; }
			else if (Tcorner(j, b, e)) { NumOfPath++; }
		}
	}
}