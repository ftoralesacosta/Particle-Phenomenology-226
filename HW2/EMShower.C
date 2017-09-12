#include <iostream>
#include <TCanvas.h>
#include <TGraph.h>
#include <fstream>


using namespace std;

void EMShower()
{


  Float_t E_0 = 1000; //MeV
  Float_t X_0 = 8.9; //radiation length of PbWO4 in mm
  Float_t Ec = 9.64; //Critical energy of PbWO4 in MeV (approximating as same for e+ (~9.3))
  TRandom *r2 = new TRandom2();

  vector <pair<Float_t,int> > Particles (1000,make_pair(E_0,0)); //Initalize with E=E_0 and X=0
  vector <pair<Float_t,int> > Photons;



  int count = 0;
  cout<<Particles.size();
    for (int X = 0; X <= 230; X++) // 230mm = 23cm.  "dX" is 1mm
      { cout<<X<<endl;
	//electrons
	for (vector <pair<Float_t,int> >::iterator iter = Particles.begin(); iter != Particles.end(); iter++)
	  {	    
	    	    cout<<count<<endl;	    count++;
	    if (iter->first > Ec) 
	      {
		if (r2->Rndm() < 1/X_0)//dX = 1mm
		  {
		    iter->first = iter->first/2;
		    Photons.push_back(make_pair(iter->first/2,X));
		    //  cout<<"Bremsstrahlung!"<<endl;
		  }
		iter->second = X;
	      }
		//I grossly simplify things by stopping a particle's proggression in X when E<Ec
	  }

	//photons
	for (vector <pair<Float_t,int> >::iterator iter = Photons.begin(); iter != Photons.end();)
	  {
	    if (iter->first > 10 && r2->Rndm() < 9/(7*X_0)) //pair production dominates at > 10MeV
	      {
		Particles.push_back(make_pair(iter->first/2,X));
		Particles.push_back(make_pair(iter->first/2,X));
		iter = Photons.erase(iter);
		//cout<<"Pair Production!"<<endl;

	      }
	    else iter++;
	  }
      }


  TCanvas * c1 = new TCanvas();

  TH1I * h1 = new TH1I("h1","1 Gev Showers",230,0,230);

  //  for (vector <pair<Float_t,int> >::iterator iter = Particles.begin(); iter != Particles.end(); iter++)
  for (int i = 0; i < Particles.size(); i++)  
  {
      cout<<Particles[i].second<<endl;
      h1->Fill(Particles[i].second);
  }
  h1->Draw("H");

  cout<<"There are "<<Particles.size()<<"Particles";
}


