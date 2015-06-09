#pragma once
#ifndef Network_H
#define Network_H

#include "Node.h"
#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class METRONETWORK{
private:
	void netAnalyse(void){
		readTime("Netwoke Analyse START Time:");
		Degree();
		Betweenness();
		readTime("Netwoke Analyse END Time:");
	}
	void netVulnerabilityAnalyse(void){
		readTime("Netwoke Vulnerability Analyse START Time:");

		readTime("Netwoke Analyse END Time:");
	}
private:
	void readNodeData(void){
		ifstream datfile;
		string path = "E:\\Program\\C++\\MetroNetwork\\Data\\name.dat";
		datfile.open(path);
		int n;
		datfile >> n;
		for (int i = 0; i < n; i++){
			NODE node;
			int num, linenum, flow;
			vector<int>line;
			datfile >> num >> linenum >> flow;
			node.number(num);
			line.push_back(linenum);
			node.linenumber(line);////////////////////////////////////////////////////////////////////////////////
			node.flow(flow);
			netNode.push_back(node);
		}
		datfile.close();
	}
	void readNodeLineData(void){
		ifstream datfile;
		string path = "E:\\Program\\C++\\MetroNetwork\\Data\\len.dat";
		datfile.open(path);
		World = new vector<double>[netNode.size()];
		for (int i = 0; i < netNode.size(); ++i){
			for (int j = 0; j < netNode.size(); ++j){
				double num;
				datfile >> num;
				World[i].push_back(num);
				if (num>0){
					LINE x;
					x.linelen(num);
					vector<NODE> y;
					if (i <= j){
						y.push_back(NODE(i + 1));
						y.push_back(NODE(j + 1));
					}
					else{
						y.push_back(NODE(j + 1));
						y.push_back(NODE(i + 1));
					}
					x.linenode(y);
					netLine.push_back(x);
				}
			}
		}
		datfile.close();
		for (int i = 0; i < netNode.size(); ++i)
		for (int j = 0; j < i; ++j)
			World[i][j] = World[j][i];
	}

	void Degree(void){
		netDegree = 0;
		for (int i = 0; i < netNode.size(); i++){
			int count = 0;
			for (int j = 0; j < netNode.size(); j++){
				if (World[i][j]>0){
					count++;
				}
			}
			netNode[i].degree(count);
		}
		for (int i = 0; i < netNode.size(); i++)
			netDegree += netNode[i].degree();

		netDegree = netDegree / netNode.size();
	}
	void Betweenness(void){
		netBetweenness = 0;
		int count = 0, k = 1;
		while (count<netNode.size()){
			for (int i = 0; i < netNode.size(); i++){
				if (netNode[i].betweenness() == 0 && netNode[i].degree() == 1){
					netNode[i].betweenness(2.0 / netNode.size());
					count++;
					cout << "i=" << i << "     " << netNode[i].degree() << "     " << netNode[i].betweenness() << endl;
				}
				else if (netNode[i].betweenness() == 0 && netNode[i].degree() == 2){
					for (int j = 0; j < netNode.size(); j++){
						if (World[i][j]>0 && netNode[j].betweenness() > 0){
							netNode[i].betweenness(netNode[j].betweenness() + 2.0*(netNode.size() - k) / (netNode.size()*(netNode.size() - 1)));
							count++;
							cout << "i=" << i << "     " << netNode[i].degree() << "     " << netNode[i].betweenness() << endl;
							break;
						}
					}
				}
				else if (netNode[i].betweenness() == 0 && netNode[i].degree() >= 3){
					for (int j = 0; j < netNode.size(); j++){
						if (World[i][j]>0){

						}
						/*					vector<double> x;
						for (int j = 0; j < netNode.size(); j++){
						if (World[i][j]>0 && netNode[j].betweenness() > 0){
						x.push_back(netNode[j].betweenness());
						}
						}
						if (netNode[i].betweenness() > 0)
						count--;
						//					if ()*/
					}
					count++;
				}
			}
			k++;
		}
		printNodeData();
	}

	void readTime(string const meg){
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		cout << meg << sys.wMonth << "/" << sys.wDay << "/" << sys.wYear << "  " << sys.wHour << ":" << sys.wMinute << endl;
	}
	void readData(void){
		cout << "First Read The Data!" << endl;
		readNodeData();
		readNodeLineData();
		readTime("Metro Data read over time:");
		//		printNodeData();
		printLineData();
		//		printWorld(World);
	}

	void printNodeData(void){
		cout << MetroName << "Metor " << netNode.size() << "NODE like this:" << endl;
		for (int i = 0; i < netNode.size(); i++){
			cout << setiosflags(ios::right) << setw(8);
			cout << netNode[i].number() << " ";
			cout << " " << netNode[i].flow() << " ";
			cout << netNode[i].degree() << " ";
			cout << netNode[i].betweenness() << " ";
			for (int i = 0; i < netNode[i].linenumber().size(); i++)
				cout << netNode[i].linenumber()[i];
			cout << endl;
		}
	}
	void printLineData(void){
		cout << MetroName << "Metor " << netLine.size() << "LINE like this:" << endl;
		for (int i = 0; i < netLine.size(); i++){
			cout << setiosflags(ios::right) << setw(8);
			cout << netLine[i].linenode()[0].number() << " " << netLine[i].linenode()[1].number() << " " << netLine[i].linelen() << endl;
		}
	}
	void printWorld(vector<double> const *pWorld){
		for (int i = 0; i <= netNode.size(); i++)
			cout << setiosflags(ios::right) << setw(8) << i;
		cout << endl;
		for (int i = 0; i<netNode.size(); i++){
			cout << setiosflags(ios::right) << setw(8) << i + 1;
			for (int j = 0; j<netNode.size(); j++)
				cout << setiosflags(ios::fixed) << setiosflags(ios::right) << setw(8) << setprecision(4) << pWorld[i][j];
			cout << endl;
		}
	}

private:
	void createConnectedWorld(vector<int> *pWorld){
		bool sign = false;
		for (;;){
			for (int i = 0; i < netNode.size(); i++){
				for (int j = 0; j < netNode.size(); j++){
					for (int z = 0; z < netNode.size(); z++){
						if (pWorld[i][z]>pWorld[i][j] + pWorld[j][z] || pWorld[i][z] == -1){

						}
					}
				}
			}
		}
		//		vector<int> *b = new vector<int>[this->netNode.size()];
		//		int temp = 0;
		/*		for (int i = 0; i<this->netNode.size(); i++)
		for (int j = 0; j<this->netNode.size(); j++)
		if (pWorld[i][j]>0 && j != i)
		for (int z = 0; z<this->netNode.size(); z++)
		if (pWorld[j][z]>0 && z != i&&z != j && (pWorld[i][z]>pWorld[i][j] + pWorld[j][z] || pWorld[i][z] == -1)){
		pWorld[i][z] = pWorld[i][j] + pWorld[j][z];
		pWorld[z][i] = pWorld[i][z];
		}
		*/
	}

public:
	void printMetroData(void){
		cout << "We will Analyse ";
		cout << MetroName << " Metro Network!" << endl;
		cout << "It has " << netNode.size() << " Node, and has " << netLine.size() << " Line" << endl;
	}
	void metroVulnerabilityAnalyseStart(void){
		printMetroData();
		cout << endl;

		cout << "Now!We will START THE Metro Vulnerability Analyse!" << endl;
		readTime("Program START Time:");
		cout << endl;

		cout << "First! We will START Netwoke Analyse!" << endl;
		netAnalyse();

		cout << "Next! We will START Netwoke Vulnerability Analyse!" << endl;
		netVulnerabilityAnalyse();

		//		vector<int> *pWorld = new vector<int>[netNode.size()];
		//		for (int i = 0; i<this->netNode.size(); i++)
		//			for (int j = 0; j<this->netNode.size(); j++)
		//				pWorld[i].push_back(World[i][j]);

		//		cout << "Now! Need to  build a ConnectedWorld" << endl;
		//		readTime("Building ConnectedWorld Time:");
		//		createConnectedWorld(pWorld);

		//		printWorld(pWorld);
	}

public:
	METRONETWORK(void){
		MetroName = "A";
		readData();
	}
	METRONETWORK(string str){
		MetroName = str;
		readData();
	}
	~METRONETWORK(void){}

private:
	string MetroName;
	vector<NODE> netNode;
	vector<LINE> netLine;
	vector<double> *World;

private:
	double netDegree;
	double netBetweenness;
};


#endif;