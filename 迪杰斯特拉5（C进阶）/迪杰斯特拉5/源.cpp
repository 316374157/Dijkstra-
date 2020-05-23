#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define MAXNUM 20       //��󶥵��� 
#define INF -1         //INF��ʾ����� 
typedef enum { DG, DN, UDG, UDN } GraphKind;
typedef int VRTYPE, InfoType;
typedef char VertexType;    //�������� 
typedef struct ArcCell
{
	VRTYPE  adj;                    //��ȨͼΪ0��1; ��ȨͼΪȨֵ
	InfoType *info;                //ָ��ߵ�ָ�� 
}ArcCell, AdjMatrix[MAXNUM][MAXNUM];
typedef struct
{
	AdjMatrix arcs;         //�ڽӾ��������������±�Ψһ��ʶÿ������
	int vexnum, arcnum;    //������ ,����
	GraphKind kind;
}MGraph;

void create_g(MGraph *g)
{
	int i, j;
	int v;
	int vexnum;
	printf("���붥����:\n");
	scanf_s("%d", &g->vexnum);
	printf("�������:\n");
	scanf_s("%d", &g->arcnum);
	for (int m = 0; m < g->vexnum; m++)
		for (int n = 0; n < g->vexnum; n++)
			g->arcs[m][n].adj = -1;
	printf("�밴�����š��յ�š���������ÿ��������Ϣ:\n");
	for (int k = 0; k < g->arcnum; k++)
	{
		scanf_s("%d%d%d", &i, &j, &v); //�л����ӵĶ�����Լ�����Ȩ��,����iָ��j
		g->arcs[i][j].adj = v;
		g->arcs[j][i].adj = v;
	}
}
void show_g(MGraph g)                //չʾ�������ڽӾ���
{
	printf("\n�������ڽӾ���\n");
	for (int i = 0; i < g.vexnum; i++)
	{
		for (int j = 0; j < g.vexnum; j++)
			if (g.arcs[i][j].adj == INF)
				printf("%3s", "��");
			else
				printf("%3d", g.arcs[i][j].adj);
		printf("\n");
	}
	printf("\n");
}
void ppath(int path[], int i, int v) //ǰ��ݹ����·���ϵĶ���
{
	int k;
	k = path[i];
	if (k == v)  return;          //�ҵ�������򷵻�
	ppath(path, k, v);            //�Ҷ���k��ǰһ������
	printf("%d,", k);            //�������k
}
void DisPath(int dist[], int path[], int S[], int n, int v)  //��path�������·��
{
	int i;
	for (i = 0; i < n; i++)
		if (S[i] == 1)
		{
			if (i != v)
			{
				printf("��%d��%d�����·������Ϊ:%d\t·��Ϊ:", v, i, dist[i]);
				printf("%d,", v);    //���·���ϵ����
				ppath(path, i, v);    //���·���ϵ��м��
				printf("%d\n", i);   //���·���ϵ��յ�
			}
		}
		else
			printf("��%d��%d������·��\n", v, i);
}
void ShortestPath_DIJ(MGraph g, int v)         //���·�㷨
{
	int dist[MAXNUM];
	int path[MAXNUM];
	int S[MAXNUM];
	int n = g.vexnum, i, j, u, min;
	for (i = 0; i < n; i++)
	{
		dist[i] = g.arcs[v][i].adj;//�����ʼ�� 
		S[i] = 0;  //��ʼ��û���ù��õ�
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
		for (j = 0; j < n; j++)        //�ҳ���ǰ�ض������·�ĵ�
			if (S[j] == 0 && dist[j] < min)
			{
				u = j; min = dist[j];
			}
		S[u] = 1;  //����u���뵽S�� 
		for (j = 0; j < n; j++)
			if (S[j] == 0)      //����
				if (g.arcs[u][j].adj < INF &&(dist[u] + g.arcs[u][j].adj) < dist[j])
				{
					dist[j] = dist[u] + g.arcs[u][j].adj;
					path[j] = u;    //u��j��ǰ�� 
				}
	}
	printf("%d\n", dist[3]);
	printf("\n���·����\n");
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
