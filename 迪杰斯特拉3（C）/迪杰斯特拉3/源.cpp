#include<stdio.h>
#include<stdlib.h>
#define M 9999  //最大
int n = 10; //顶点个数
int f[10]; //0表示未访问过，1表示访问过
int d[10]; //最短路径
char path[10][10]; //记录路径
int a[10][10] = {
		{ M , 6 , M , 5 , M , M , M , M , M , M },
		{ 6 , M , 7 , M , M , M , 7 ,10 , M , M },
		{ M , 7 , M , 8 , 2 , 6 , 5 , M , M , M },
		{ 5 , M , 8 , M , 9 , M , M , M , M , M },
		{ M , M , 2 , 9 , M , 3 , M , M , M ,10 },
		{ M , M , 6 , M , 3 , M , 4 , 9 , 8 , 6 },
		{ M , 7 , 5 , M , M , 4 , M , 8 , M , M },
		{ M ,10 , M , M , M , 9 , 8 , M , 7 , M },
		{ M , M , M , M , M , 8 , M , 7 , M , 7 },
		{ M , M , M , M ,10 , 6 , M , M , 7 , M }
};   //矩阵化图
typedef struct {
	char vexs[10]; //顶点名称
	int arcs[10][10];    //邻接矩阵
	int vexnum;  //顶点个数
}MGraph;

MGraph initMGraph(MGraph G) {  //初始化图,将a赋值到邻接矩阵中
	int i, j;
	char char_a = 'A';
	for (i = 0; i < 10; i++) {     //依次构建A,B,C,D..顶点
		G.vexs[i] = (char)((int)char_a + i);
	}

	for (i = 0; i < 10; i++) {   //存入数据
		for (j = 0; j < 10; j++) {
			G.arcs[i][j]= a[i][j];
		}
	}
	G.vexnum = 10;
	return G;
}

int mininum(int* d) {    //返回最小权值的下标
	int i, min = M, min_i;
	for (i = 0; i < n; i++) {
		if (d[i] != 0 && d[i] < min && f[i] != 1) {  //没被访问过，并且能达到
			min = d[i];
			min_i = i;
		}
	}
	if (min == M)
		return -1;
	return min_i;
}

void DJST(MGraph G, char u) {
	int i, j, k, min_i, path_p, count, s = -1;
	char v;

	for (i = 0; i < G.vexnum; i++) {    //记录原点位置
		if (G.vexs[i] == u)
			s = i;
	}

	for (i = 0; i < G.vexnum; i++) {
		f[i] = 0;         //全部设置成未访问 
		d[i] = G.arcs[s][i];
		v = G.vexs[i];
		if (d[i] < M && d[i] != 0) {
			path[i][0] = u;     
			path[i][1] = v;    
		}
	}

	//初始化从原点到原点的路径为0，并将原点设置为已访问
	d[s] = 0;
	f[s] = 1;
	for (i = 1; i < G.vexnum; i++) {
		min_i = mininum(d);
		//不相联通的直接跳过
		if (min_i == -1)
			break;
		f[min_i] = 1;
		//更新其他顶点的信息
		for (k = 0; k < G.vexnum; k++) {
			if (G.arcs[min_i][k] != 0) {
				if ((d[min_i] + G.arcs[min_i][k]) < d[k]) {
					d[k] = d[min_i] + G.arcs[min_i][k];
					for (path_p = 0; path[min_i][path_p] != 0; path_p++)
						path[k][path_p] = path[min_i][path_p];
					path[k][path_p] = G.vexs[k];
				}
			}
		}
	}
	//输出路径
	for (count = 0; count < G.vexnum; count++) {
		for (j = 0; j < G.vexnum; j++)
			if (path[count][j] && path[count][j] != path[count][j - 1])
				printf("%c->", path[count][j]);
		if (d[count] == 0 || d[count] == M)
			continue;
		printf("  最短路径长度为:%d\n", d[count]);
	}
}

int main(void) {
	char v;
	MGraph G = { 0 };
	G = initMGraph(G);
	for (int i = 0;;) {
		printf("输入原点为:");
		v = getchar();
		if (v == '\n' || v == '\r' || v<'A' || v>'J')
			continue;
		DJST(G, v);
	}
	return 0;
}
