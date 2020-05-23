using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace 迪杰斯特拉1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        static int M = 9999;          //最大距离，表示达不到
        static int n = 10;            //顶点个数，随时可以修改
        static int[] f = new int[10]; //0表示未访问过，1表示访问过
        static int[] d = new int[10]; //最短路径，存放算出的路径长度
        static char[,] path = new char[10,10]; //记录路径，因为顶点都是字母，所以用char类型
        static int[,] a =new int[10,10]{
		    { 0 , 6 , M , 5 , M , M , M , M , M , M },
		    { 6 , 0 , 7 , M , M , M , 7 ,10 , M , M },
		    { M , 7 , 0 , 8 , 2 , 6 , 5 , M , M , M },
		    { 5 , M , 8 , 0 , 9 , M , M , M , M , M },
		    { M , M , 2 , 9 , 0 , 3 , M , M , M ,10 },
		    { M , M , 6 , M , 3 , 0 , 4 , 9 , 8 , 6 },
		    { M , 7 , 5 , M , M , 4 , 0 , 8 , M , M },
		    { M ,10 , M , M , M , 9 , 8 , 0 , 7 , M },
		    { M , M , M , M , M , 8 , M , 7 , 0 , 7 },
		    { M , M , M , M ,10 , 6 , M , M , 7 , 0 }
        };   //矩阵化图，其实可以一个个输入，只不过太麻烦，所以就直接存放进去,自身是0，到不了是M，其他的放成权值

        MGraph G = new MGraph();           //一个自定义的类，用来表示图这个类型，本来是想用C语言数据结构中的struct
                                           //但是发现C#中类的功能其实是一样的并且更加的简洁，所以就用了类，是根据数据结构书的启发吧

        MGraph initMGraph(MGraph G)                  //初始化，将所有的信息存放进去，写成函数是比较简洁的，方便随时修改调用
                                                     //相当于模块化吧，一块一块的组合成一个程序，哪一块出问题直接修改，也不会
                                                     //产生牵一发而动全身
        {  //初始化图,将a赋值到邻接矩阵中
            int i, j;
            char char_a = 'A';     //顶点从A开始
            for (i = 0; i < 10; i++)
            {     //依次构建所有顶点的名称
                G.vexs[i] = (char)((int)char_a + i);
            }

            for (i = 0; i < 10; i++)
            {   //存入数据
                for (j = 0; j < 10; j++)
                {
                    G.arcs[i, j] = a[i, j];     //将a矩阵对应的数据赋值给G
                }
            }
            G.vexnum = 10;
            return G;     //返回存放完数据
        }

        int mininum(ref int[] d)                  //还是模块化思想，将比较大小也写成一个函数，
        {    //返回最小权值的下标
            int i, min = M, min_i=0;
            for (i = 0; i < n; i++)
            {
                if (d[i] != 0 && d[i] < min && f[i] != 1)
                {  //不是自身，没被访问过，并且能达到
                    min = d[i];
                    min_i = i;
                }
            }
            if (min == M)
                return -1;
            return min_i;
        }

        void DJST(MGraph G, char u)             //最重要的，最核心的算法
        {
            int i, j, k, min_i, path_p, count, s = -1;
            char v;

            for (i = 0; i < G.vexnum; i++)
            {    //记录原点位置
                if (G.vexs[i] == u)
                    s = i;
            }

            for (i = 0; i < G.vexnum; i++) //因为下边的循环从1开始，所有先放置原点和下一个点的信息
            {
                f[i] = 0;         //全部设置成未访问，初始化
                d[i] = G.arcs[s,i];  //放入原点所在行的所有权值
                v = G.vexs[i];  //所有权值对应的顶点
                if (d[i] < M && d[i] != 0) 
                {
                    path[i,0] = u;    
                    path[i,1] = v;    
                }
            }

            //初始化从原点到原点的路径为0，并将原点设置为已访问
            d[s] = 0;
            f[s] = 1;
            for (i = 1; i < G.vexnum; i++)  //跳过原点
            {
                min_i = mininum(ref d);      //记录最小权值的下标
                //不相联通的直接跳过
                if (min_i == -1)
                    break;
                f[min_i] = 1;
                //以这个新加入的顶点为中间点看看，有没有更短的路径，如果有则更新
                for (k = 0; k < G.vexnum; k++)
                {
                    if (G.arcs[min_i,k] != 0)
                    {
                        if ((d[min_i] + G.arcs[min_i, k]) < d[k])     //如果以此为中间点，到达的路径更短，就直接更新
                        {
                            d[k] = d[min_i] + G.arcs[min_i, k];       //更新数值
                            for (path_p = 0; path[min_i,path_p] != 0; path_p++)  //更新顶点
                                path[k,path_p] = path[min_i,path_p];
                            path[k,path_p] = G.vexs[k];
                        }
                    }
                }
            }
            //输出路径
            for (count = 0; count < G.vexnum; count++)
            {
                for (j = 0; j < G.vexnum; j++)
                    richTextBox1.Text += path[count, j] + "->";   
                if (d[count] == 0 || d[count] == M)
                    continue;
                richTextBox1.Text += "  最短路径长度为:" + d[count] + "\r\n";
            }
        }


        private void btn_k_Click(object sender, EventArgs e)
        {
            richTextBox1.Clear();  //开始前，先清空数据，可以不要
            char v;        //原点
            G = initMGraph(G); //图
            v = char.Parse(textBox1.Text);
            if (v < 'A' || v > 'J')  //报错机制
            {
                DialogResult dr = MessageBox.Show("输入错误！请重新输入","错误",MessageBoxButtons.OK);
                if(dr == DialogResult.OK)
                {
                    textBox1.Clear();
                    textBox1.Focus();
                }
            }
            else
            {
                DJST(G, v);
                btn_k.Enabled = false;
            }
        }

        private void button1_Click(object sender, EventArgs e) //刷新程序，因为运行的时候有Bug，数据刷新有问题
        {
            Application.ExitThread();
            Application.Restart();
        }
    }
}
