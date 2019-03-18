
#include "LibManipulatorPathGenerator.h"

ManipPath m_path;

ManipPath::ManipPath()
{
 
}

/************************************************

        void pathPlan(double startPos, double goalPos, std::vector<double>& path, double time,double updateCycle)

	概要：関節空間法での関節位置軌道を生成する

	引数：double startPos・・・動作開始位置[deg]
              double goalPos・・・動作終了位置[deg]
              std::vector<double>& path・・・パスを格納する配列
              double time・・・動作時間[s]
              double updateCycle・・・経路更新周期

	戻り値：なし

*************************************************/
void ManipPath::pathPlan(double startPos, double goalPos, std::vector<double>& path, double time,double updateCycle)
{
  std::cout << "pathPlan" << std::endl;
  double a0;
  double a1;
  double a2;
  double a3;
  double pathNumber; 
  double pathtime;
  //デバッグ用=========================
  //std::ofstream ofs("OutputFile.csv");
  //ofs << "path,time" << std::endl;
  //==================================

  pathNumber = (time)*updateCycle;
  pathtime = 0;
  a0 = startPos;
  a1 = 0;
  a2 = (3/(time*time))*(goalPos-startPos);
  a3 = (-2/(time*time*time))*(goalPos-startPos);

  path.clear();

  for(int i=0;i<pathNumber;i++)
    {
      path.push_back(a0 + a1*pathtime + a2*pathtime*pathtime + a3*pathtime*pathtime*pathtime);
      pathtime += time/pathNumber;
      //ofs << path[i] << "," << pathtime << std::endl;
    }
}

/************************************************

        void ManipPath::pathPlanIncludeViaPos(double startPos, double goalPos, std::vector<double> viaPos, std::vector<double>& path, std::vector<double> time,double updateCycle)

	概要：関節空間法での経由点をなめらかに通過する関節位置軌道を生成する

	引数：double startPos・・・動作開始位置[deg]
              double goalPos・・・動作終了位置[deg]
              std::vector<double> viaPos・・・経由点[deg]
              std::vector<double>& path・・・パスを格納する配列
              std::vector<double> time・・・動作時間[s]
              double updateCycle・・・経路更新周期

	戻り値：なし

*************************************************/
void ManipPath::pathPlanIncludeViaPos(double startPos, double goalPos, std::vector<double> viaPos, std::vector<double>& path, std::vector<double> time,double updateCycle)
{
  
  std::vector<double> viaSpeed;
  std::vector<double> lineMoveSpeed;
  double a0,a1,a2,a3;
  std::vector<double> pathNumber; 
  double pathtime;
  int numberViaPos;
  double startSpeed = 0;
  double goalSpeed = 0;
  //デバッグ用===========================
  //double sumtime = 0;
  //std::ofstream ofs("OutputFile.csv");
  //ofs << "path,time" << std::endl;
  //====================================

  numberViaPos = viaPos.size();
  viaSpeed.resize(numberViaPos);
  lineMoveSpeed.resize(numberViaPos+1);
  pathNumber.resize(numberViaPos+1);
  path.clear();

  //点と点の傾き(速度)の計算
  lineMoveSpeed[0] = (viaPos[0] - startPos)/time[0];
  int j = 0;
  if(numberViaPos>1)
    {
      for(int i=1;i<numberViaPos;i++)
	{
	  lineMoveSpeed[i] = (viaPos[i] - viaPos[i-1])/time[i];
	  j=i;
	}
      lineMoveSpeed[numberViaPos] = (goalPos - viaPos[j])/time[numberViaPos];
    }
  else
    {
      lineMoveSpeed[numberViaPos] = (goalPos - viaPos[0])/time[0];
    }
  
  //経由点を通過する速度計算
  for(int m=0;m<numberViaPos;m++)
    {
      if(lineMoveSpeed[m]>0 && lineMoveSpeed[m+1]>0)
	{
	  viaSpeed[m] = (lineMoveSpeed[m] + lineMoveSpeed[m+1])/2;
	}
      else if(lineMoveSpeed[m]*lineMoveSpeed[m+1]<0 || (lineMoveSpeed[m]==0 && lineMoveSpeed[m+1]==0))
	{
	  viaSpeed[m] = 0;
	}
      else if(lineMoveSpeed[m]<0 && lineMoveSpeed[m+1]<0)
	{
	  viaSpeed[m] = (lineMoveSpeed[m] + lineMoveSpeed[m+1])/2;
	}
    }

  //点間のpathの数を計算する
  for(int l=0;l<=numberViaPos;l++)
    {
      pathNumber[l] = (time[l])*updateCycle;
      //std::cout << "time["<<l<<"] = "<<time[l]<<std::endl;
      //std::cout << "updateCycle = " << updateCycle << std::endl;
      //std::cout << "pathNumber["<<l<<"] = "<<pathNumber[l]<<std::endl;
    }

  //startPosから一つ目の経由点のpath計算
  pathtime = 0;
  a0 = startPos;
  a1 = 0;
  a2 = (3/(time[0]*time[0]))*(viaPos[0]-startPos) - (2/time[0])*startSpeed - (1/time[0])*viaSpeed[0];
  a3 = (-2/(time[0]*time[0]*time[0]))*(viaPos[0]-startPos) + (1/(time[0]*time[0]))*(viaSpeed[0] + startSpeed);
  for(int k=0;k<pathNumber[0];k++)
    {
      path.push_back(a0 + a1*pathtime + a2*pathtime*pathtime + a3*pathtime*pathtime*pathtime);
      pathtime += time[0]/pathNumber[0];
      //sumtime += time[0]/pathNumber[0];
      //ofs << path[path.size()-1] << "," << sumtime << std::endl;
    }
  
  //経由点が2個以上ある場合経由点間のpath計算
  if(numberViaPos>1)
    {
      for(int h=1;h<numberViaPos;h++)
	{
	  pathtime = 0;
	  a0 = viaPos[h-1];
	  a1 = viaSpeed[h-1];
	  a2 = (3/(time[h]*time[h]))*(viaPos[h]-viaPos[h-1]) - (2/time[h])*viaSpeed[h-1] - (1/time[h])*viaSpeed[h];
	  a3 = (-2/(time[h]*time[h]*time[h]))*(viaPos[h]-viaPos[h-1]) + (1/(time[h]*time[h]))*(viaSpeed[h] + viaSpeed[h-1]);
	  for(int k=0;k<pathNumber[h];k++)
	    {
	      path.push_back(a0 + a1*pathtime + a2*pathtime*pathtime + a3*pathtime*pathtime*pathtime);
	      pathtime += time[h]/pathNumber[h];
	      //sumtime += time[0]/pathNumber[0];
	      //ofs << path[path.size()-1] << "," << sumtime << std::endl;
	    }
	}
      //最後の経由点とgoalPos間のpath計算
      pathtime = 0;
      a0 = viaPos[numberViaPos-1];
      a1 = viaSpeed[numberViaPos-1];
      a2 = (3/(time[numberViaPos]*time[numberViaPos]))*(goalPos-viaPos[numberViaPos-1]) - (2/time[numberViaPos])*viaSpeed[numberViaPos-1] - (1/time[numberViaPos])*goalSpeed;
      a3 = (-2/(time[numberViaPos]*time[numberViaPos]*time[numberViaPos]))*(goalPos-viaPos[numberViaPos-1]) + (1/(time[numberViaPos]*time[numberViaPos]))*(goalSpeed + viaSpeed[numberViaPos-1]);
      for(int f=0;f<pathNumber[numberViaPos];f++)
	{
	  path.push_back(a0 + a1*pathtime + a2*pathtime*pathtime + a3*pathtime*pathtime*pathtime);
	  pathtime += time[numberViaPos]/pathNumber[numberViaPos];
	  //sumtime += time[0]/pathNumber[0];
	  //ofs << path[path.size()-1] << "," << sumtime << std::endl;
	}
    }
  else
    {
      //最後の経由点とgoalPos間のpath計算
      pathtime = 0;
      a0 = viaPos[0];
      a1 = viaSpeed[0];
      a2 = (3/(time[1]*time[1]))*(goalPos-viaPos[0]) - (2/time[1])*viaSpeed[0] - (1/time[1])*goalSpeed;
      a3 = (-2/(time[1]*time[1]*time[1]))*(goalPos-viaPos[0]) + (1/(time[1]*time[1]))*(goalSpeed + viaSpeed[0]);
      for(int g=0;g<pathNumber[1];g++)
	{
	  path.push_back(a0 + a1*pathtime + a2*pathtime*pathtime + a3*pathtime*pathtime*pathtime);
	  pathtime += time[1]/pathNumber[1];
	  //sumtime += time[0]/pathNumber[0];
	  //ofs << path[path.size()-1] << "," << sumtime << std::endl;
	}
    }
  
}
