#pragma once
#ifndef Version_H
#define Version_H

#include <iostream>
#include <windows.h>
#include <string>
using std::cout;
using std::string;
using std::endl;
void version(string GramName, string Version)
{/**//// <summary>
	/// APP Version
	/// </summary>
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	cout<<"Welcome to use"<<GramName<<endl;
	cout<<"Version: "<<Version<<endl;
	cout<<"Copyright (C) "<<sys.wYear<<", lib.systematic engineering"<<endl;
	cout<<"Corporation and others.  All Rights Reserved."<<endl<<endl;
}
void readTime(){
	SYSTEMTIME sys;
	GetLocalTime(&sys);
}
#endif