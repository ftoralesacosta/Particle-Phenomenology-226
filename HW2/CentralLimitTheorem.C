#include <iostream>
#include <TCanvas.h>
#include <TGraph.h>
#include <fstream>


using namespace std;

void CentralLimitTheorem()
{

  //Part B
  
  TRandom *r2 = new TRandom2();

  vector <double> nums;
  double sum;
  int n = 1000;

  for (int i = 0; i < n ;i++)
    {
      nums.push_back(r2->Rndm());
      sum += nums[i];
    }
  
  double mean = sum/n;
  cout<<mean<<endl;

  double var;

  for (int a = 0; a < nums.size(); a++)
    {
      var += pow((nums[a]-mean),2);
    }

  var = var/(n-1);
  cout<<var<<endl;

  double sigma = sqrt(var);
  cout<<sigma<<endl;


  //Part C

  TCanvas * c1 = new TCanvas();
  TH1D * h1 = new TH1D("h1","A thousand Random Numbers (TRandom2)",100,0,1);


  for (int i = 0; i < nums.size();i++)
    {
      h1->Fill(nums[i]);
    }

  h1->Draw("H");

  //Part D

  int N = 10; //N=2 and N=5 were also used for this assignment
  TCanvas * c2 = new TCanvas();
  TH1D * h2 = new TH1D("h2","Averages of Random Numbers for N=10",100,0,1);


  for (int i = 0; i<1000; i++)    
    {
      double S = 0;
      for (int j = 0; j <N; j++)
	{
	  S += r2->Rndm();
	}
      h2->Fill(S/N);
    }

  h2->Draw();

}//CetralLimitTheorem
