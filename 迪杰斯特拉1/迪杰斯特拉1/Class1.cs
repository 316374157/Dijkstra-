using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 迪杰斯特拉1
{
    public class MGraph
    {
        public char[] vexs = new char[10]; //顶点名称
        public int[,] arcs = new int[10, 10];    //邻接矩阵
        public int vexnum;  //顶点个数
    }
  
}
