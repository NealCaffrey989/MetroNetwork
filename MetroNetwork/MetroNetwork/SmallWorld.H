#include "Rand.h"
#include "Version.h"
#include <math.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>  
#include <math.h>
#include <cassert>
#include <windows.h>
typedef double WORLDFEATURE;

using namespace std;

class SmallWorld_T
{
private: 
	int Node, K;
	double Probability;

	vector<WORLDFEATURE> *World;

	int arcNum;			//边数
	WORLDFEATURE netDegree;	//度
	WORLDFEATURE netMinRouteLen;		//平均路径长度
	WORLDFEATURE netClusteringCoefficient;		//聚类系数
	WORLDFEATURE netEfficiency;		//效率
	WORLDFEATURE netBetweenness;		//介数

	enum {ORIGINAL=0,ACTUAL=1};
	int worldType;

private:
	void readWorldType(void){
		cout<<"Please select a World Type."<<endl;
		cout<<"If your already have a Network message, please select type 1.Or you can select 2 to fabricate a world you like"<<endl;
		do{
			cout<<"world type=";
			cin>>this->worldType;
			if(readCin()==TRUE)
				if(this->worldType>0&&this->worldType<3)
					break;
		}while(1);
		cout<<endl;
	}
	void readNode(void){
		cout<<"Your need input node number.(node>0)"<<endl;
		do{
			cout<<"Node=";
			cin>>this->Node;
			if(readCin()==TRUE&&this->Node>=0)
				break;
		}while(1);
		cout<<endl;
	}
	void readProbability(void){
		cout<<"Your need input prabability to create NT Small World.(1>probability>0)"<<endl;
		do{
			cout<<"Probability=";
			cin>>this->Probability;
			if(readCin()==TRUE)
				if(this->Probability>=0&&this->Probability<=1)
					break;
		}while(1);
		cout<<endl;
	}
	void readK(void){
		cout<<"Your need input K to create NT Small World.(K can be devisible by 2)"<<endl;
		do{
			cout<<"K=";
			cin>>this->K;
			if(readCin()==TRUE)
				if(this->K%2==0&&this->K>0)
					break;
		}while(1);
		cout<<endl;
	}
	
	void readArcNum(void){
		this->arcNum=0;
		for(int i=0;i<this->Node-1;i++)
			for(int j=i+1;j<this->Node;j++)
				if(World[i][j]>0)
					this->arcNum++;
	}
	void readKm(vector<WORLDFEATURE> const *pWorld){
		vector<WORLDFEATURE> k;
		this->netDegree=0;
		for(int i=0;i<this->Node;i++){
			int temp=1;
			for(int j=0;j<this->Node;j++)
				if(pWorld[i][j]>0)
					temp++;
			k.push_back(temp);
		}
		for(vector<WORLDFEATURE>::const_iterator iter=k.begin();iter!=k.end();++iter)
			this->netDegree+=*iter;
		this->netDegree=this->netDegree/this->Node;
	}
	void readLm(vector<WORLDFEATURE> const *pWorld){
		vector<WORLDFEATURE> l;
		this->netMinRouteLen=0;
		for(int i=0;i<this->Node-1;i++)
			for(int j=i+1;j<this->Node;j++)
				l.push_back(pWorld[i][j]);
		for(vector<WORLDFEATURE>::const_iterator iter=l.begin();iter!=l.end();++iter)
			this->netMinRouteLen+=*iter;
		this->netMinRouteLen=2.0*this->netMinRouteLen/this->Node/(this->Node+1);
	}
	void readCm(vector<WORLDFEATURE> const *pWorld){
		vector<WORLDFEATURE> c;
		netClusteringCoefficient=0;
		double TEi,ki;
		for(int i=0;i<this->Node;i++){
			TEi=0;
			ki=0;
			for(int j=0;j<this->Node;j++)
				if(World[i][j]>0)
					ki++;
			for(int j=0;j<this->Node;j++)
				if(pWorld[i][j]>0)
					for(int z=0;z<this->Node;z++)
						if(World[j][z]>0)
							ki++;
			ki=ki/2;
			for(int j=0;j<this->Node;j++)
				if(pWorld[i][j]>0)
					TEi++;
			if(ki>1)
				c.push_back((double)(2.0*TEi/(ki*(ki-1))));
			else if(ki==1)
				c.push_back(1);
		}
		for(vector<WORLDFEATURE>::const_iterator iter=c.begin();iter!=c.end();++iter)
			this->netClusteringCoefficient+=*iter;
		this->netClusteringCoefficient=this->netClusteringCoefficient/this->Node;
	}
	void readEm(vector<WORLDFEATURE> const *pWorld){
		vector<WORLDFEATURE> e;
		this->netEfficiency=0;
		for(int i=0;i<this->Node;i++){
			double temp=0;
			for(int j=0;j<this->Node;j++)
				if(pWorld[i][j]>0)
					temp++;
			e.push_back(temp);
		}
		for(vector<WORLDFEATURE>::const_iterator iter=e.begin();iter!=e.end();++iter)
			this->netEfficiency+=*iter;
		this->netEfficiency=this->netEfficiency/this->Node;
	}
	void readBm(vector<WORLDFEATURE> const *pWorld){
		vector<WORLDFEATURE> b;
		this->netBetweenness=0;
		int g=0,gi=0;

		vector<double> distance(Node,0);  
		vector<int> preVertex(Node,0);
		for (int i =0 ; i < Node; ++i ){  
			Dijkstra(Node, i, distance, preVertex);  
			for(int j =0; j < Node; ++j) {  
				int index = j;  
				stack<double> trace;  
				while (preVertex[index] != -1) {  
					trace.push(preVertex[index]);  
					index = preVertex[index];  
				}  
				if(!trace.empty()){
					while (!trace.empty()){  
						cout<<trace.top()<<" -- ";  
						trace.pop();  
					}  
					cout <<j;  
					cout <<"-->"<<distance[j]<<endl;  
				}
			 }
		}
		for (int i =0 ; i < Node; ++i ){
			for (int j =0 ; j < Node; ++j )
				cout<<World[i][j]<<"        ";
			cout<<endl;
		}









		
		for(vector<WORLDFEATURE>::const_iterator iter=b.begin();iter!=b.end();++iter)
			this->netBetweenness+=*iter;
		this->netBetweenness=this->netBetweenness/this->Node;
	}

	void createActualWorld(void){
		cout<<"I Don't make it!"<<endl;
	}
	void createVirtutalWorld(void){
		cout<<"Now! Start to build a VirtutalWorld"<<endl;
		readNode();
		readProbability();
		readK();
		readTime("Building VirtutalWorld Time:");
		createNTSmallWorld();
		readTime("Building VirtutalWorld End Time:");
		printWorld(World);
		
		findWorldFeature();
		printFeature();
	}
	void createNTSmallWorld(){
		World=new vector<WORLDFEATURE>[this->Node];
		Random rm;
		for(int i=0;i<this->Node;i++)
			for(int j=0;j<this->Node;j++)
				World[i].push_back(0);
		for(int i=0;i<this->Node;i++){
			if((i-K/2)<0&&World[i][i-K/2+this->Node]==0){
				World[i][i-K/2+this->Node]=rm.getNormal(10,0.2);
				World[i-K/2+this->Node][i]=World[i][i-K/2+this->Node];
			}
			else	if((i-K/2)>=0&&World[i-K/2][i]==0){
				World[i-K/2][i]=rm.getNormal(10,0.2);	
				World[i][i-K/2]=World[i-K/2][i];
			}
		}
		for(int i=0;i<Node;i++){
			if(rm.getUniform(0,1)<=Probability){
				int m=(int)rm.getUniform(0,Node-1);
				int z=(int)rm.getUniform(0,Node-1);
				if(m<z&&World[m][z]==0){
					World[m][z]=rm.getNormal(10,0.2);
					World[z][m]=World[m][z];
				}
			}
		}
	}
	void createConnectedWorld(vector<WORLDFEATURE> *pWorld){
		vector<WORLDFEATURE> *b=new vector<WORLDFEATURE>[this->Node];
		int temp=0;
		for(int i=0;i<this->Node;i++)
			for(int j=0;j<this->Node;j++)
				if(pWorld[i][j]>0&&j!=i)
					for(int z=0;z<this->Node;z++)
						if(pWorld[j][z]>0&&z!=i&&z!=j&&(pWorld[i][z]>pWorld[i][j]+pWorld[j][z]||pWorld[i][z]==0)){
							pWorld[i][z]=pWorld[i][j]+pWorld[j][z];
							pWorld[z][i]=pWorld[i][z];
						}
	}

	void initWorld(void){
		if(worldType==TRUE)
			createActualWorld();
		else
			createVirtutalWorld();
	}
	void findWorldFeature(void){
		readArcNum();

		vector<WORLDFEATURE> *pWorld=new vector<WORLDFEATURE>[Node];
		for(int i=0;i<this->Node;i++)
			for(int j=0;j<this->Node;j++)
				pWorld[i].push_back(World[i][j]);
		
		cout<<"Now! Need to  build a ConnectedWorld"<<endl;
		readTime("Building ConnectedWorld Time:");
		createConnectedWorld(pWorld);
		readTime("Building ConnectedWorld End Time:");
		
//		printWorld(pWorld);
		readKm(pWorld);
		readLm(pWorld);
		readCm(pWorld);
		readEm(pWorld);
	}
	void readTime(string const meg){
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		cout<<meg<<sys.wMonth<<"/"<<sys.wDay<<"/"<<sys.wYear<<"  "<<sys.wHour<<":"<<sys.wMinute<<endl;
	}
	bool readCin(void){
		if (cin.rdstate()==ios_base::goodbit)
			return TRUE;
		else {//if(cin.rdstate()==ios_base::failbit){
//			cout<<"Input error,please input again!"<<endl;
			cin.clear();
			cin.ignore();
			return FALSE;
		}
	}

	void setArcNum(int num){
		arcNum=num;
	}
	void setNetDegree(WORLDFEATURE num){
		netDegree=num;
	}
	void setNetMinRouteLen(WORLDFEATURE num){
		netMinRouteLen=num;
	}
	void setNetClusteringCoefficient(WORLDFEATURE num){
		netClusteringCoefficient=num;
	}
	void setNetEfficiency(WORLDFEATURE num){
		netEfficiency=num;
	}
	void setNetBetweenness(WORLDFEATURE num){
		netBetweenness=num;
	}

	void printWorld(vector<WORLDFEATURE> const *pWorld){
		for(int i=0;i<=Node;i++)
			cout<<setiosflags(ios::right)<<setw(8)<<i;
		cout<<endl;
		for(int i=0;i<Node;i++){
			cout<<setiosflags(ios::right)<<setw(8)<<i+1;
			for(int j=0;j<Node;j++)
				cout<<setiosflags(ios::fixed)<<setiosflags(ios::right)<<setw(8)<<setprecision(4)<<pWorld[i][j];
			cout<<endl;
		}
	}
	void printFeature(void){
		cout<<setprecision(10)<<endl;
		cout<<"Now! There are some world feature to show:"<<endl;
		cout<<"The world have "<<this->Node<<" Node"<<endl;
		cout<<"have "<<this->arcNum<<" edge"<<endl;
		cout<<"The world's degree:"<<this->netDegree<<endl;
		cout<<"The world's minimize route length:"<<this->netMinRouteLen<<endl;
		cout<<"The world's clustering coefficient:"<<this->netClusteringCoefficient<<endl;
		cout<<"The world's efficiency:"<<this->netEfficiency<<endl;
		cout<<"The world's betweenness:"<<this->netBetweenness<<endl<<endl;
	};

	void Dijkstra(  
              const int numOfVertex,    /*节点数目*/  
              const int startVertex,    /*源节点*/  
              vector<double> &distance,            /*各个节点到达源节点的距离*/  
              vector<int> &prevVertex           /*各个节点的前一个节点*/  
              ){  
		vector<bool> isInS;                 //是否已经在S集合中  
		isInS.reserve(0);  
		isInS.assign(numOfVertex, false);   //初始化，所有的节点都不在S集合中  
      
		/*初始化distance和prevVertex数组*/  
		for(int i =0; i < numOfVertex; ++i){  
			distance[ i ] = World[ startVertex ][ i ];  
			if(World[ startVertex ][ i ] > 0)  
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
        for(int j = 0; j < numOfVertex; ++j){  
            if((isInS[j] == false) && (distance[j] < tempDistance))//寻找不在S集合中的distance最小的节点  
            {  
                nextVertex = j;  
                tempDistance = distance[j];  
            }  
        }  
        isInS[nextVertex] = true;//放入S集合中  
        u = nextVertex;//下一次寻找的开始节点  
          
          
        /*更新distance*/  
        for (int j =0; j < numOfVertex; j ++){  
            if (isInS[j] == false && World[u][j] > 0 ){  
                double temp = distance[ u ] + World[ u ][ j ];  
                if (temp < distance[ j ]){  
                    distance[ j ] = temp;  
                    prevVertex[ j ] = u;  
                }  
            }  
        }  
    }  
}  

public:
	void SmallWorldStart(void){
		cout<<"Now!We will START THE SMALL WORlD!"<<endl;
		readTime("Program START Time:");
		
		readWorldType();
		initWorld();

		readTime("Program END Time:");
	}
	explicit SmallWorld_T(void){		
		setArcNum(0);
		setNetDegree(0);
		setNetMinRouteLen(0);
		setNetClusteringCoefficient(0);
		setNetEfficiency(0);
		setNetBetweenness(0);
		version("Small-World","1.1");
	}
	~SmallWorld_T(void){
	}
};