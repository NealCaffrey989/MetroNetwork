#pragma once
#ifndef Node_H
#define Node_H
#include <string>
#include <vector>
using namespace std;

class NODE{
public:
	double degree(void){
		return this->nodeDegree;
	}
	void degree(double num){
		this->nodeDegree = num;
	}
	double betweenness(void){
		return this->nodeBetweenness;
	}
	void betweenness(double num){
		this->nodeBetweenness = num;
	}
	int number(void){
		return this->nodeNumber;
	}
	void number(int num){
		this->nodeNumber = num;
	}
	vector<int> linenumber(void){
		return this->lineNumber;
	}
	void linenumber(vector<int> num){
		if (num.size()<=2)
			this->lineNumber = num;
	}
	double flow(void){
		return this->nodeFlow;
	}
	void flow(double num){
		this->nodeFlow = num;
	}
public:
	NODE(void){
		nodeNumber = 0;
		initNODE();
	}
	NODE(int n){
		number(n);
		initNODE();
	}
	~NODE(){}
private:
	void initNODE(void){
		lineNumber.clear();
		nodeDegree = 0;
		nodeBetweenness = 0;
		nodeFlow = 0;
		noedVulnerability = 0;
	}
private:
	int nodeNumber;	//节点号
	vector<int> lineNumber;	//线路号
	double nodeDegree;	//度
	double nodeBetweenness;		//介数
	double nodeFlow;	//客流
	double noedVulnerability;		//脆弱值
};

class LINE{
public:
	void linenode(vector<NODE> num){
		if (num.size() == 2){
			lineNode = num;
		}
	}
	vector<NODE> linenode(void){
		return lineNode;
	}
	void linelen(double num){
		lineLen = num;
	}
	double linelen(void){
		return lineLen;
	}
private:
	vector<NODE> lineNode;	//节点
	double lineLen;
	bool lineStatue = true;
};
/*
class METRONODE:public NODE{
public:
	string name(void){
		return nodeName;
	};
	void name(string str){
		nodeName = str;
	}
	int number(void){
		return nodeNumber;
	};
	void number(int num){
		nodeNumber = num;
	}
	double flow(void){
		return nodeFlow;
	}
	void flow(double num){
		nodeFlow = num;
	}
	double vulnerability(void){
		this->noedVulnerability = alph*nodeFlow + (1-alph)*betweenness();
		return noedVulnerability;
	}
private:
	string nodeName;	//节点名称
	int nodeNumber;	//节点编号
	double nodeFlow;	//客流
	double noedVulnerability;		//脆弱值
	double alph;	//客流选择概率
	bool nodeStatue = true;
	int nodeVScore;	//脆弱值排序
public:
	METRONODE(double num){
		alph = num;
		if (alph<0 || alph>1)
			nodeStatue = false;
	}
	~METRONODE(){}
};

class METROLINE{
public:
	double vulnerability(void){
		return lineVulnerability;
	}
private:
	double lineVulnerability;		//脆弱值
};
*/
#endif