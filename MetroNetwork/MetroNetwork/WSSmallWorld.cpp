// WSSmallWorld.cpp : �������̨Ӧ�ó������ڵ㡣
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
 
// �����鶼���±�1��ʼ
int dist[maxnum];     // ��ʾ��ǰ�㵽Դ������·������
int prevl[maxnum];     // ��¼��ǰ���ǰһ�����
int c[maxnum][maxnum];   // ��¼ͼ�������·������
int n, line;             // ͼ�Ľ������·����
 
// n -- n nodes
// v -- the source node
// dist[] -- the distance from the ith node to the source node
// prev[] -- the previous node of the ith node
// c[][] -- every two nodes' distance
void Dijkstra(int n, int v, int *dist, int* prev, int c[maxnum][maxnum])
{
	bool s[maxnum];    // �ж��Ƿ��Ѵ���õ㵽S������
	for(int i=1; i<=n; ++i)
	{
		dist[i] = c[v][i];
		s[i] = 0;     // ��ʼ��δ�ù��õ�
		if(dist[i] == maxint)
			prev[i] = 0;
		else
			prev[i] = v;
	}
	dist[v] = 0;
	s[v] = 1;
 
	// ���ν�δ����S���ϵĽ���У�ȡdist[]��Сֵ�Ľ�㣬������S��
	// һ��S����������V�ж��㣬dist�ͼ�¼�˴�Դ�㵽������������֮������·������
         // ע���Ǵӵڶ����ڵ㿪ʼ����һ��ΪԴ��
	for(int i=2; i<=n; ++i)
	{
		int tmp = maxint;
		int u = v;
		// �ҳ���ǰδʹ�õĵ�j��dist[j]��Сֵ
		for(int j=1; j<=n; ++j)
			if((!s[j]) && dist[j]<tmp)
			{
				u = j;              // u���浱ǰ�ڽӵ��о�����С�ĵ�ĺ���
				tmp = dist[j];
			}
		s[u] = 1;    // ��ʾu���Ѵ���S������
 
		// ����dist
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
 
// ���Ҵ�Դ��v���յ�u��·���������
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
	// �����鶼���±�1��ʼ
 
	// ��������
	cin >> n;
	// ����·����
	cin >> line;
	int p, q, len;          // ����p, q���㼰��·������
 
	// ��ʼ��c[][]Ϊmaxint
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			c[i][j] = maxint;
 
	for(int i=1; i<=line; ++i)  
	{
		cin >> p >> q >> len;
		if(len < c[p][q])       // ���ر�
		{
			c[p][q] = len;      // pָ��q
			c[q][p] = len;      // qָ��p��������ʾ����ͼ
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
 
	// ���·������
	cout << "Դ�㵽���һ����������·������: " << dist[n] << endl;
 
	// ·��
	cout << "Դ�㵽���һ�������·��Ϊ: ";
	searchPath(prevl, 2, n);
	system("pause");
}*/

#include <iostream>  
#include <vector>  
#include <stack>  
using namespace std;  
  
  
double map[][5] = {                     //��������ͼ  
    {0,  0, 10, 0, 0},  
    {0, 0,  0, 10,0},  
    {0, 0, 0, 0, 10},  
    {0,0,0, 0, 0},  
    {0,0,0, 0, 0}
};  
  
void Dijkstra(const int numOfVertex,  const int startVertex, double (map)[][5], vector<double> &distance,  vector<int> &prevVertex){
//*	const int numOfVertex,    /*�ڵ���Ŀ*/  
//              const int startVertex,    /*Դ�ڵ�*/ 
//			  double (map)[][5],          /*����ͼ�ڽӾ���*/  
//              vector<double> &distance,            /*�����ڵ㵽��Դ�ڵ�ľ���*/  
//              vector<int> &prevVertex           /*�����ڵ��ǰһ���ڵ�*/
	vector<bool> isInS;                 //�Ƿ��Ѿ���S������  
    isInS.reserve(0);  
    isInS.assign(numOfVertex, false);   //��ʼ�������еĽڵ㶼����S������  
      
    /*��ʼ��distance��prevVertex����*/  
    for(int i =0; i < numOfVertex; ++i){  
        distance[ i ] = map[ startVertex ][ i ];  
        if(map[ startVertex ][ i ] > 0)  
            prevVertex[ i ] = startVertex;  
        else  
            prevVertex[ i ] = -1;       //��ʾ����֪��ǰһ���ڵ���ʲô  
    }  
    prevVertex[ startVertex ] = -1;  
      
    /*��ʼʹ��̰��˼��ѭ��������S�����е�ÿһ���ڵ�*/  
    isInS[startVertex] = true;          //��ʼ�ڵ����S������  
      
      
    int u = startVertex;  
      
    for (int i = 1; i < numOfVertex; i ++)      //����ѭ����1��ʼ����Ϊ��ʼ�ڵ��Ѿ������S���ˣ�����numOfVertex-1���ڵ�Ҫ����  
    {  
          
        /*ѡ��distance��С��һ���ڵ�*/  
        int nextVertex = u;  
        double tempDistance = INT_MAX;  
        for(int j = 0; j < numOfVertex; ++j)  
        {  
            if((isInS[j] == false) && (distance[j] < tempDistance))//Ѱ�Ҳ���S�����е�distance��С�Ľڵ�  
            {  
                nextVertex = j;  
                tempDistance = distance[j];  
            }  
        }  
        isInS[nextVertex] = true;//����S������  
        u = nextVertex;//��һ��Ѱ�ҵĿ�ʼ�ڵ�  
          
          
        /*����distance*/  
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
