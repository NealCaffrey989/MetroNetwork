#pragma once

#include "Rand.h"

#include <cmath>
#include <ctime>
#include <cstdlib>
class Random
{
public:
	void init(unsigned int seed)
	{
		lastNumber=0;
		srand(seed);
	}
	void init()
	{
		time_t t;
		time(&t);
		init((int)t);
	}
	Random()
	{
		init(0);
	}
	~Random()
	{

	}
	double getLast()
	{
		return lastNumber;
	}
	double getUniform(double from = 0,double to = 1)
	{
		lastNumber= uniform();
		lastNumber=lastNumber*(to-from)-from;
		return lastNumber;
	}
	double getGamma(double alpha=1,double beta=1)
	{
		if(alpha==1){
			lastNumber=getExponentail(1);
		}else if(alpha<1){
			double b=(exp(1.0)+alpha)/exp(1.0);
			do{
				double u1=uniform();
				double p=b*uniform();
				double y;
				if(p>1){
					y=-log((b-p)/alpha);
					if(u1<pow(y,alpha-1)){
						lastNumber=y;
						break;
					}
				}else{
					y=pow(p,1/alpha);
					if(u1<exp(-y)){
						lastNumber=y;
						break;
					}
				}
			}while(1);
		}else {
			while (1)
			{
				double u1=uniform();
				double u2=uniform();
				double v=sqrt(2*alpha-1)*log(u2/(1-u2));
				double t=alpha*exp(v);
				if(log(u1*u2*u2)<alpha-log(4.0)+(alpha+sqrt(2*alpha-1))*v-t){
					lastNumber=t;
					break;
				}
			}
		}
		lastNumber*=beta;
		return lastNumber;
	}
	double getBeta(double alpha1=1,double alpha2=1)
	{
		double u1=getGamma(alpha1,1);
		double u2=getGamma(alpha2,1);
		lastNumber=u1/(u1+u2);
		return lastNumber;
	}
	double getNormal(double mean=0,double std=1)
	{
		double v1,v2,w;
		do{
			v1=uniform()*2-1;
			v2=uniform()*2-1;
			w=v1*v1+v2*v2;
		}while(w>1);
		lastNumber=v1*sqrt(-2*log(w)/w);
		lastNumber=lastNumber*std+mean;
		return lastNumber;
	}
	double getExponentail(double lambda=1)
	{
		lastNumber=-log(1-uniform())/lambda;
		return lastNumber;
	}
	int getDiscreteUniform(int from=0,int to=1) 
	{
		int t=from+(int)((to-from+1)*uniform());
		lastNumber=t;
		return t;
	}
	int getGeometric(double p=0.5)
	{
		int t=(int)(log(1-uniform())/log(1-p));
		lastNumber=t;
		return t;
	}
	int getBinomial(int n=1,double p=0.5)
	{
		int s=0;
		for(int i=0;i<n;i++){
			if(uniform()<p)s++;
		}
		lastNumber=s;
		return s;
	}
	int getPoisson(double lambda=1)
	{
		int t=0;
		double p=exp(-lambda);
		double f=p;
		double u=uniform();
		while(1){
			if(f>u)break;
			t++;
			p=p*lambda/t;
			f+=p;
		}
		lastNumber=t;
		return t;
	}
private:
	double uniform()
	{
		return (double)rand()/(double)(RAND_MAX+1);
	}
private:
	double lastNumber;
};