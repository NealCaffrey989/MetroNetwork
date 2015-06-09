// WSSmallWorld.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "SmallWorld.H"
/*
int _tmain(int argc, _TCHAR* argv[])
{
	SmallWorld_T world;
	world.SmallWorldStart();
	system("pause");
	return EXIT_SUCCESS;
}*/
/*
#include <iostream>
using namespace std;
 
const int maxnum = 100;
const int maxint = 999999;
 
// 各数组都从下标1开始
int dist[maxnum];     // 表示当前点到源点的最短路径长度
int prevl[maxnum];     // 记录当前点的前一个结点
int c[maxnum][maxnum];   // 记录图的两点间路径长度
int n, line;             // 图的结点数和路径数
 
// n -- n nodes
// v -- the source node
// dist[] -- the distance from the ith node to the source node
// prev[] -- the previous node of the ith node
// c[][] -- every two nodes' distance
void Dijkstra(int n, int v, int *dist, int* prev, int c[maxnum][maxnum])
{
	bool s[maxnum];    // 判断是否已存入该点到S集合中
	for(int i=1; i<=n; ++i)
	{
		dist[i] = c[v][i];
		s[i] = 0;     // 初始都未用过该点
		if(dist[i] == maxint)
			prev[i] = 0;
		else
			prev[i] = v;
	}
	dist[v] = 0;
	s[v] = 1;
 
	// 依次将未放入S集合的结点中，取dist[]最小值的结点，放入结合S中
	// 一旦S包含了所有V中顶点，dist就记录了从源点到所有其他顶点之间的最短路径长度
         // 注意是从第二个节点开始，第一个为源点
	for(int i=2; i<=n; ++i)
	{
		int tmp = maxint;
		int u = v;
		// 找出当前未使用的点j的dist[j]最小值
		for(int j=1; j<=n; ++j)
			if((!s[j]) && dist[j]<tmp)
			{
				u = j;              // u保存当前邻接点中距离最小的点的号码
				tmp = dist[j];
			}
		s[u] = 1;    // 表示u点已存入S集合中
 
		// 更新dist
		for(int j=1; j<=n; ++j)
			if((!s[j]) && c[u][j]<maxint)
			{
				int newdist = dist[u] + c[u][j];
				if(newdist < dist[j])
				{
					dist[j] = newdist;
					prev[j] = u;
				}
			}
	}
}
 
// 查找从源点v到终点u的路径，并输出
void searchPath(int* prev,int v, int u)
{
	int que[maxnum];
	int tot = 1;
	que[tot] = u;
	tot++;
	int tmp = prev[u];
	while(tmp != v)
	{
		que[tot] = tmp;
		tot++;
		tmp = prev[tmp];
	}
	que[tot] = v;
	for(int i=tot; i>=1; --i)
		if(i != 1)
			cout << que[i] << " -> ";
		else
			cout << que[i] << endl;
}
 
int main()
{
//	freopen("input.txt", "r", stdin);
	// 各数组都从下标1开始
 
	// 输入结点数
	cin >> n;
	// 输入路径数
	cin >> line;
	int p, q, len;          // 输入p, q两点及其路径长度
 
	// 初始化c[][]为maxint
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			c[i][j] = maxint;
 
	for(int i=1; i<=line; ++i)  
	{
		cin >> p >> q >> len;
		if(len < c[p][q])       // 有重边
		{
			c[p][q] = len;      // p指向q
			c[q][p] = len;      // q指向p，这样表示无向图
		}
	}
 
	for(int i=1; i<=n; ++i)
		dist[i] = maxint;
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=n; ++j)
			printf("%8d", c[i][j]);
		printf("\n");
	}
 
	Dijkstra(n, 1, dist, prevl, c);
 
	// 最短路径长度
	cout << "源点到最后一个顶点的最短路径长度: " << dist[n] << endl;
 
	// 路径
	cout << "源点到最后一个顶点的路径为: ";
	searchPath(prevl, 2, n);
	system("pause");
}*/

#include <iostream>  
#include <vector>  
#include <stack>  
using namespace std;  
  
  
double map[][5] = {                     //定义有向图  
    {0,  0, 10, 0, 0},  
    {0, 0,  0, 10,0},  
    {0, 0, 0, 0, 10},  
    {0,0,0, 0, 0},  
    {0,0,0, 0, 0}
};  
  
void Dijkstra(const int numOfVertex,  const int startVertex, double (map)[][5], vector<double> &distance,  vector<int> &prevVertex){
//*	const int numOfVertex,    /*节点数目*/  
//              const int startVertex,    /*源节点*/ 
//			  double (map)[][5],          /*有向图邻接矩阵*/  
//              vector<double> &distance,            /*各个节点到达源节点的距离*/  
//              vector<int> &prevVertex           /*各个节点的前一个节点*/
	vector<bool> isInS;                 //是否已经在S集合中  
    isInS.reserve(0);  
    isInS.assign(numOfVertex, false);   //初始化，所有的节点都不在S集合中  
      
    /*初始化distance和prevVertex数组*/  
    for(int i =0; i < numOfVertex; ++i){  
        distance[ i ] = map[ startVertex ][ i ];  
        if(map[ startVertex ][ i ] > 0)  
            prevVertex[ i ] = startVertex;  
        else  
            prevVertex[ i ] = -1;       //表示还不知道前一个节点是什么  
    }  
    prevVertex[ startVertex ] = -1;  
      
    /*开始使用贪心思想循环处理不在S集合中的每一个节点*/  
    isInS[startVertex] = true;          //开始节点放入S集合中  
      
      
    int u = startVertex;  
      
    for (int i = 1; i < numOfVertex; i ++)      //这里循环从1开始是因为开始节点已经存放在S中了，还有numOfVertex-1个节点要处理  
    {  
          
        /*选择distance最小的一个节点*/  
        int nextVertex = u;  
        double tempDistance = INT_MAX;  
        for(int j = 0; j < numOfVertex; ++j)  
        {  
            if((isInS[j] == false) && (distance[j] < tempDistance))//寻找不在S集合中的distance最小的节点  
            {  
                nextVertex = j;  
                tempDistance = distance[j];  
            }  
        }  
        isInS[nextVertex] = true;//放入S集合中  
        u = nextVertex;//下一次寻找的开始节点  
          
          
        /*更新distance*/  
        for (int j =0; j < numOfVertex; j ++)  
        {  
            if (isInS[j] == false && map[u][j] < INT_MAX)  
            {  
                double temp = distance[ u ] + map[ u ][ j ];  
                if (temp < distance[ j ])  
                {  
                    distance[ j ] = temp;  
                    prevVertex[ j ] = u;  
                }  
            }  
        }  
    }  
}  
  
  
int main (int argc, const char * argv[])  
{  
	int Node=5;
   
	for (int i =0 ; i < 4; ++i )
		for (int j =i ; j < 5; ++j )
			map[j][i]=map[i][j];
	for (int i =0 ; i < 5; ++i ){
		for (int j =0 ; j < 5; ++j )
			cout<<map[i][j]<<"        ";
		cout<<endl;
	}
	vector<double> *World=new vector<double>[5], temp;
	for (int i =0 ; i < 5; ++i )
		for (int j =0 ; j < 5; ++j )
			World[i].push_back(double(map[i][j]));
	for (int i =0 ; i < 5; ++i ){
		for (int j =0 ; j < 5; ++j )
			cout<<World[i][j]<<"       ";
		cout<<endl;
	}

	vector<double> distance(Node,0);  
    vector<int> preVertex(Node,0);
    for (int i =0 ; i < Node; ++i ){  
        Dijkstra(Node, i, map, distance, preVertex);  
		for(int j =0; j < Node; ++j) {  
             int index = j;  
             stack<double> trace;  
             while (preVertex[index] != -1) {  
                 trace.push(preVertex[index]);  
                 index = preVertex[index];  
             }  
             if(!trace.empty()){
				while (!trace.empty()) {  
					cout<<trace.top()<<" -- ";  
					trace.pop();  
				}  
             cout <<j;  
			 cout <<"-->"<<distance[j]<<endl;  
			 }
         }
    }
	for (int i =0 ; i < 5; ++i ){
		for (int j =0 ; j < 5; ++j )
			cout<<map[i][j]<<"        ";
		cout<<endl;
	}/*	

	SmallWorld_T world;
	world.SmallWorldStart();
	*/
	system("pause");  
    return 0;  
}
