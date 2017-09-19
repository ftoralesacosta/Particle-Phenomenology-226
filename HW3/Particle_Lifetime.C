#include <iostream>
#include <TCanvas.h>
#include <TGraph.h>
#include <fstream>


using namespace std;

void Particle_Lifetime() {

  Float_t A = 1;
  Float_t B = 2;
  Float_t Lambda = 2;
  Float_t R_max = A+B;
  Float_t t_max = 3;
  Float_t t_i;
  
  int N = 100; //number of events

  TRandom *r2 = new TRandom2();
  vector <Float_t> Good_events;
  

//a)

  for (int i = 0; i < N; i++)
    {
      t_i = t_max*r2->Rndm();
      Float_t y_i = R_max*r2->Rndm();

      if (y_i <= A+B*pow(M_E,(-Lambda*t_i))) Good_events.push_back(t_i);
      //      cout<<t_i<<endl;
    }


  //I was naively expecting e^-2 fraction of events to be kept. 
  //Is actually ~ 44%
  
  Float_t event_percent = 100*(Good_events.size())/N;
  cout<<event_percent<<"\% of events kept "<<endl;



//b)
//see mathematica


  Float_t k = 0.5;
  Float_t t;
  Float_t f = (Lambda*(pow(M_E,(-t*Lambda)))+k)/(1-pow(M_E,(-3*Lambda))+3*Lambda*k); //if I were to do this again, I would use TF2 or something

  Float_t negLL = 0;

  for(int i = 0; i < Good_events.size(); i++)
    {
      t = Good_events[i];
      
      //      cout<<"t = "<<t<<endl;
      
      negLL+= -1*(Lambda*(pow(M_E,(-(Good_events[i])*Lambda)))+k)/(1-pow(M_E,(-3*Lambda))+3*Lambda*k);
  
      //      cout<<"L = "<<negLL<<endl;
    }
  negLL = negLL*(-1);
  cout<<negLL<<endl;

  // I get 11.1373 for the negative log liklihood


//c)

  int Npoints = 100;
  Float_t kmax = 1;
  Float_t kmin = 0; //region of true value
  Float_t  dk = (kmax-kmin)/Npoints;
  Float_t Lmax = 3;
  Float_t Lmin = 1;
  Float_t dL = (Lmax-Lmin)/Npoints;
  
//     TH2F *varryk = new TH2F("varryk", "Log Liklihood varrying k", 10,-1,1, 10, 10, 12);
   
//   for (int n =0; n < Npoints; n++)
//     {
//       kmin+=dk;
//       Float_t negLL = 0;
      
//       for(int i = 0; i < Good_events.size(); i++)
// 	{
// 	  t = Good_events[i];
// 	  negLL+= (Lambda*(pow(M_E,(-(Good_events[i])*Lambda)))+kmin)/(1-pow(M_E,(-3*Lambda))+3*Lambda*kmin); 
// 	}
//         varryk->Fill(kmin,negLL);
//     }
//    varryk->SetMarkerSize(30);
//     varryk->Draw("H");
    //  commented out to swich plots quickly

  TH2F *varryL = new TH2F("varryL", "Log Liklihood varrying L", 10,-1,10, 10, 0, 12);

  for (int n =0; n < Npoints; n++)
    {
      kmin+=dk;
      Float_t negLL = 0;

      for(int i = 0; i < Good_events.size(); i++)
        {
          t = Good_events[i];
          negLL+= (Lmin*(pow(M_E,(-(Good_events[i])*Lmin)))+k)/(1-pow(M_E,(-3*Lmin))+3*Lmin*k);
        }
      varryL->Fill(Lmin,negLL);
    }
  varryL->SetMarkerSize(30);
  varryL->Draw("H");



}

