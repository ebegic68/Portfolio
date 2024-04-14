//TP 2022/2023: Zadaća 3, Zadatak 4
#include <iostream>
#include <cmath>
#include <list>
#include <algorithm>
#include <vector>
int Poglavica(int N, int M, bool provjera=false){
    if(N<=0 || M<=0){
    return 0;
    }
    if(N==1){
    return 1;
    }
   /* if(M==1){
        if(provjera){
            int i=1;
            while(i<N){
                std::cout<<i<<" ";
                i++;
            }
        }
        return N;
    }*/
    std::list<int> lista;
    
    for(int i=1;i<=N;i++){
        lista.push_back(i);
    }
    if(M>N){M=N;}
    int p=0;
    auto pomocna=lista.begin();
    std::vector<int> vektor; 
    while(lista.size()>1){
    for(int i=1;i<M;i++){
        //std::advance(pomocna, M-1);
        pomocna++;
         if(pomocna==lista.end()){
            pomocna=lista.begin();
        }
    }
     //ppomocna;
      /*if(provjera){
            std::cout<<p<<", ";
            }*/
        
  auto brisanje=pomocna++;
    if(pomocna==lista.end()){
       pomocna=lista.begin();
    }
    lista.erase(brisanje);
}
if(provjera){
        for(int i=0;i<vektor.size();i++){
        std::cout<<vektor[i];
        if(i<=(vektor.size()-1))
        std::cout<<", ";
        }
    }
return *lista.begin();
}
/*int SigurnoMjesto(int M, int N1, int N2) {
    if(M<=0 ||N1<=0 || N2<=0) return 0;
  std::vector<int> vektor;
  for (int i = N1; i <= N2; i++) {
    vektor.push_back(Poglavica(i, M));
  }
  for (int i = N1; i <= N2; i++) {
    auto pomocna = std::count(vektor.begin(), vektor.end(), i);
    if (pomocna == 0)
      return i;
  }
  return 0;
}*/
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
            //}
            /*else{
            provjera=false;
            return j;
         
            }*/
            
          
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
   // mjesto=mjesto-1;
    if(mjesto==0){
         // }else{
        std::cout<<"Zao mi je Mbebe Mgogo, ali nema sigurnog mjesta."<<std::endl;
    }
     else{
         std::cout<<"Mbebe Mgogo, stani na sigurno mjesto "<<mjesto<<" da ne bi bio poglavica!"<<std::endl;
     }
	return 0;
}
