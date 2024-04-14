//TP 2022/2023: Zadaća 3, Zadatak 5
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
struct Cvor{
    int redni_broj;
    Cvor *sljedeci;

};
int Poglavica(int N, int M, bool provjera=false){
    /*std::list<int> lista;
    
    for(int i=1;i<=N;i++){
        lista.push_back(i);
    }
    int p=0;
    auto pomocna=lista.begin();
   
    while(lista.size()>1){
    for(int i=1;i<M;i++){
        //std::advance(pomocna, M-1);
        pomocna++;
         if(pomocna==lista.end()){
            pomocna=lista.begin();
        }}// p=*pomocna;
      if(provjera){
            std::cout<<p<<", ";
            }pomocna=lista.erase(pomocna);
    if(pomocna==lista.end()){
       pomocna=lista.begin();
    }
    }return *lista.begin();}*/
     if(N<=0 || M<=0){
    return 0;
    }
    if(N==1){
    return 1;
    }
    Cvor* prvi=new Cvor;
    
    prvi->redni_broj=1;
    Cvor* trenutni=prvi;
    for(int i=2;i<=N;i++){
        trenutni->sljedeci=new Cvor;
        trenutni=trenutni->sljedeci;
        trenutni->redni_broj=i;
        
    }
    trenutni->sljedeci=prvi;
   // trenutni=prvi;
   
   int brojac=0;
   std::vector<int> clanovi;
    while(N>1){
        for(int i=1;i<M;i++){
            trenutni=trenutni->sljedeci;
        }
        
     
    
      Cvor* obrisi=trenutni->sljedeci;
        trenutni->sljedeci=trenutni->sljedeci->sljedeci;
               delete obrisi;
       brojac++;
       N--;
        
    }
    int p=trenutni->redni_broj;
    delete trenutni;
    if(provjera){
        for(int i=0;i<clanovi.size();i++){
        std::cout<<clanovi[i];
        if(i<=(clanovi.size()-1))
        std::cout<<", ";
        }
    }
    
    return p;

}
  int SigurnoMjesto(int N, int M,int K){
    if(N<=0 || M<=0 || K<=0)
    return 0;
std::vector<int> lista;
   for(int i=M;i<=K;i++){
       
       lista.push_back(Poglavica(i,N));
   }
        bool provjera=false;
        for(int j=M;j<=K;j++){
            if(std::count(lista.begin(), lista.end(), j)==0)
               provjera=true;
                //break;
                  if(provjera){
           return j;
                  }

            
          
        }
       
    
    
return 0;
}

  
int main ()
{
   int N,M,N1, N2;
    std::cout<<"Unesite broj punoljetnih clanova za odabir poglavice plemena Wabambe: ";
    std::cin>>N;
    std::cout<<"Unesite korak razbrajanja: ";
    std::cin>>M;
    std::cout<<"Unesite raspon za odabir (N1 i N2): ";
    std::cin>>N1>>N2;
    int poglavica=Poglavica(N,M,true);
    std::cout<<"Redni broj osobe koja postaje poglavica: "<<poglavica<<std::endl;
    int mjesto=SigurnoMjesto(M,N1,N2);
    
    if(mjesto==0){
         // }else{
        std::cout<<"Zao mi je Mbebe Mgogo, ali nema sigurnog mjesta."<<std::endl;
    }
     else{
         std::cout<<"Mbebe Mgogo, stani na sigurno mjesto "<<mjesto<<" da ne bi bio poglavica!"<<std::endl;
     }


	return 0;
}
