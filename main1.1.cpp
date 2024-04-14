//TP 2022/2023: Zadaća 1, Zadatak 1
#include <iostream>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <array>
enum class TretmanNegativnih{IgnorirajZnak, Odbaci, PrijaviGresku};
int MultiplikativniDigitalniKorijen(long long int n, int b){ //funkcija koja racuna multiplikativni digitalni korijen
    //int b(10);
    std::vector<int>v1;
    if(b<2)
    throw std::domain_error("Neispravna baza");
    //if(TretmanNegativnih::IgnorirajZnak){
    if(n<0){
     n=std::abs(n);
    }
    //}
    //if(n==0)
   // return 0;
    if(n<b){
        return n;
        
    }
    
    
   unsigned long long int korijen=1;
     bool nula=false;
    // racunanje multiplikativng korijena
    while(n>0){
        int cifra=n%b;
        if(cifra!=0){
            korijen*=cifra;

        }else{
            nula=true;
        }
        n/=b;
    
       
    }
    if(nula){
     return MultiplikativniDigitalniKorijen(n ,b);
    }
    
  
    //return MultiplikativniDigitalniKorijen(korijen,b);
   // }

    return MultiplikativniDigitalniKorijen(korijen,b);
    }


std::array<std::vector<long long int>,10> RazvrstajBrojeve(std::vector<long long int> brojevi, TretmanNegativnih tretman){ //funkcija koja razvrstava zadani vektor prema digitalnom korijenu
    std::array<std::vector<long long int>,10>rezultat;
     for(long long int broj: brojevi){//razvrstavanje brojeva prema korijenu
        if(broj<0){
         /*if(tretman==TretmanNegativnih::PrijaviGresku){
                 for(int i=0; i<brojevi.size();i++){
                     if(brojevi[i]<0){
                         std::cout<<"Nije podrzano razvrstavanje negativnih brojeva!"<<std::endl;
                        break;
                     }

                 }
             }
             */
         if(tretman==TretmanNegativnih::Odbaci){
             continue; //preskace broj
         }else if(tretman==TretmanNegativnih::PrijaviGresku){
             throw std::domain_error("Nije predvidjeno razvrstavanje negativnih brojeva");
         }
         broj=std::abs(broj);
     }
         
             int korijen =MultiplikativniDigitalniKorijen(broj,10);
             if(korijen>=0){
                 rezultat.at(korijen).push_back(broj);
             }
         
         
     }
return rezultat;
}

    

int main ()
{
    std::vector<long long int> brojevi;
    long long int broj;
    std::cout<<"Unesite brojeve (bilo koji ne-broj oznacava kraj): ";
    while(std::cin>>broj){
       // for(int i=0; i<brojevi.size();i++){
                     if(broj<0){
                         std::cout<<"Nije podrzano razvrstavanje negativnih brojeva!"<<std::endl;
                        return 0;
                     }

               //  }
        brojevi.push_back(broj);
    }
    try{
        std::array<std::vector<long long int>,10> rezultat=RazvrstajBrojeve(brojevi, TretmanNegativnih::PrijaviGresku);
        std::cout<<"Rezultati razvrstavanja po multiplikativnom digitalnom korijenu: "<<std::endl;
        for(int i=0; i<10;i++){
    
            if(rezultat[i].size()>0){
                std::cout<<i<<": ";
                for(long long int broj: rezultat[i]){
                    std::cout<<broj<<" ";
                
            }
                std::cout<<std::endl;
                }
                    
                }
            
            
            
        
            
        
}catch(std::domain_error e){
        std::cout<<e.what()<<std::endl;
    }


	return 0;
}
