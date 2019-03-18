//ManipulatorPathGenerator.h
#ifndef __LIBMANIPULATORPATHGENERATOR_H__
#define __LIBMANIPULATORPATHGENERATOR_H__


//数学定数の使用
#define _USE_MATH_DEFINES

/********* includeファイル *********/
//#include <cmath>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector> 


class ManipPath{
 private:
  
  //private変数の宣言
 
 public:
 //コンストラクタ
 ManipPath();

 void pathPlan(double startPos, double goalPos, std::vector<double>& path, double time,double updateCycle);
 void pathPlanIncludeViaPos(double startPos, double goalPos, std::vector<double> viaPos, std::vector<double>& path, std::vector<double> time,double updateCycle);

};

extern ManipPath m_path;

#endif//__LIBMANIPULATORPATHGENERATOR_H__
