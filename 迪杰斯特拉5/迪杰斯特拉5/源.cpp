#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define MAXNUM 20       //最大顶点数 
#define INF -1         //INF表示无穷大 
typedef enum { DG, DN, UDG, UDN } GraphKind;
typedef int VRTYPE, InfoType;
typedef char VertexType;    //顶点类型 
typedef struct ArcCell
{
	VRTYPE  adj;                    //无权图为0或1; 带权图为权值
	InfoType *info;                //指向边的指针 
}ArcCell, AdjMatrix[MAXNUM][MAXNUM];
typedef struct
{
	AdjMatrix arcs;         //邻接矩阵，这里以数组下标唯一标识每个顶点
	int vexnum, arcnum;    //顶点数 ,边数
	GraphKind kind;
}MGraph;

void create_g(MGraph *g)
{
	int i, j;
	int v;
	int vexnum;
	printf("输入顶点数:\n");
	scanf_s("%d", &g->vexnum);
	printf("输入边数:\n");
	scanf_s("%d", &g->arcnum);
	for (int m = 0; m < g->vexnum; m++)
		for (int n = 0; n < g->vexnum; n++)
			g->arcs[m][n].adj = -1;
	printf("请按照起点号、终点号、弧长输入每条弧的信息:\n");
	for (int k = 0; k < g->arcnum; k++)
	{
		scanf_s("%d%d%d", &i, &j, &v); //有弧连接的顶点对以及弧的权重,弧从i指向j
		g->arcs[i][j].adj = v;
		g->arcs[j][i].adj = v;
	}
}
void show_g(MGraph g)                //展示创建的邻接矩阵
{
	printf("\n创建的邻接矩阵：\n");
	for (int i = 0; i < g.vexnum; i++)
	{
		for (int j = 0; j < g.vexnum; j++)
			if (g.arcs[i][j].adj == INF)
				printf("%3s", "∞");
			else
				printf("%3d", g.arcs[i][j].adj);
		printf("\n");
	}
	printf("\n");
}
void ppath(int path[], int i, int v) //前向递归查找路径上的顶点
{
	int k;
	k = path[i];
	if (k == v)  return;          //找到了起点则返回
	ppath(path, k, v);            //找顶点k的前一个顶点
	printf("%d,", k);            //输出顶点k
}
void DisPath(int dist[], int path[], int S[], int n, int v)  //由path计算最短路径
{
	int i;
	for (i = 0; i < n; i++)
		if (S[i] == 1)
		{
			if (i != v)
			{
				printf("从%d到%d的最短路径长度为:%d\t路径为:", v, i, dist[i]);
				printf("%d,", v);    //输出路径上的起点
				ppath(path, i, v);    //输出路径上的中间点
				printf("%d\n", i);   //输出路径上的终点
			}
		}
		else
			printf("从%d到%d不存在路径\n", v, i);
}
void ShortestPath_DIJ(MGraph g, int v)         //最短路算法
{
	int dist[MAXNUM];
	int path[MAXNUM];
	int S[MAXNUM];
	int n = g.vexnum, i, j, u, min;
	for (i = 0; i < n; i++)
	{
		dist[i] = g.arcs[v][i].adj;//距离初始化 
		S[i] = 0;  //初始都没有用过该点
		if (g.arcs[v][i].adj < INF)
			path[i] = v;
		else
			path[i] = -1;
	}
	S[v] = 1; path[v] = 0;
	for (i = 0; i < n; i++)
	{
		min = INF;
		u = -1;
		for (j = 0; j < n; j++)        //找出当前必定是最短路的点
			if (S[j] == 0 && dist[j] < min)
			{
				u = j; min = dist[j];
			}
		S[u] = 1;  //顶点u插入到S中 
		for (j = 0; j < n; j++)
			if (S[j] == 0)      //更新
				if (g.arcs[u][j].adj < INF &&(dist[u] + g.arcs[u][j].adj) < dist[j])
				{
					dist[j] = dist[u] + g.arcs[u][j].adj;
					path[j] = u;    //u是j的前驱 
				}
	}
	printf("%d\n", dist[3]);
	printf("\n输出路径：\n");
	DisPath(dist, path, S, n, v);
}
int main()
{
	MGraph g;
	create_g(&g);
	show_g(g);
	int path[MAXNUM], i, j, v = 0;
	ShortestPath_DIJ(g, v);

}
