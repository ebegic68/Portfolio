//TP 2022/2023: Zadaća 4, Zadatak 3
#include <iostream>
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <iomanip>
#include <vector>
#include <string>
#include <initializer_list>
class Polazak{
    private:
    std::string odrediste;
    std::string oznaka_voznje;
    int brperona;
    int hpolaska;
    int mpolaska;
    int tvoznje;
    int kasnjenje;
   
    
 public:
  static int VrijemePolaska(const Polazak& polazak) {
        return polazak.hpolaska * 60 + polazak.mpolaska;
    }
 Polazak(std::string odrediste, std::string oznaka_voznje, int broj_perona,
 int sat_polaska, int minute_polaska, int trajanje_voznje);
void PostaviKasnjenje(int kasnjenje);
bool DaLiKasni() const;
int DajTrajanje() const;
void OcekivanoVrijemePolaska(int &sati, int &minute) const;
void OcekivanoVrijemeDolaska(int &sati, int &minute) const;
void Ispisi() const;
};
Polazak::Polazak(std::string odrediste, std::string oznaka_voznje, int broj_perona, 
int sat_polaska, int minute_polaska, int trajanje_voznje):odrediste(odrediste), oznaka_voznje(oznaka_voznje), brperona(broj_perona),hpolaska(sat_polaska), mpolaska(minute_polaska), tvoznje(trajanje_voznje), kasnjenje(0){
    if(sat_polaska<0 ||sat_polaska>23 || minute_polaska<0 ||minute_polaska>59 || trajanje_voznje<=0 || broj_perona<1 ||broj_perona>15){
        throw std::domain_error("Besmislene vrijednosti parametara");
        
    }
}
void Polazak::PostaviKasnjenje(int kasnjenje){
    if(kasnjenje<0){
        this->kasnjenje=0;
        std::cout<<"Neregularna vrijednost kasnjenja."<<std::endl;
    }else{
        this->kasnjenje=kasnjenje;
    }
    
   

}
bool Polazak::DaLiKasni() const{
    return kasnjenje>0;
}
int Polazak::DajTrajanje() const{
    return tvoznje;
}

void Polazak::OcekivanoVrijemePolaska(int &sati, int& minute) const{
    
    sati=hpolaska;
    minute=mpolaska + kasnjenje;
    if(minute>=60){
        sati+=minute/60;
        minute%=60;
    }
    if(sati>=24)
        sati%=24;
}
void Polazak::OcekivanoVrijemeDolaska(int &sati, int &minute) const{
    
    sati= hpolaska +(mpolaska+tvoznje+kasnjenje)/60;
    minute=(mpolaska+tvoznje+kasnjenje)%60;
    if(sati>=24)
        sati%=24;
    
}

    /*int ukupno=hpolaska *60+mpolaska+kasnjenje+tvoznje;
    sati=ukupno/60;
    minute=ukupno%60;*/
    //sati=hpolaska;
   // minute=mpolaska;


void Polazak::Ispisi() const {
   int hpolaska,mpolaska;
   OcekivanoVrijemePolaska(hpolaska,mpolaska);
    //std::cout<<std::left<<std::setw(10)<<oznaka_voznje<<std::setw(30)<<odrediste<<std::setw(10)<<std::setfill('O')<<hpolaska<<":"<<std::setw(2)<<std::setfill('O')<<mpolaska<<std::setfill(' ')<<" "<<std::setw(2)<<std::setfill('O')<<OcekivanoVrijemeDolaska(hdolaska,mdolaska)<<std::setw(2)<<std::setfill('O')<<OcekivanoVrijemeDolaska()<<" "<<std::setw(8)<<std::setfill(' ')<<brperona;
    std::cout<<std::setw(10)<<std::left<<oznaka_voznje;
    std::cout<<std::setw(30)<<odrediste<<std::right;
    std::cout<<std::setw(7)<<std::setfill(' ')<<hpolaska<<":"<<std::setw(2)<<std::setfill('0')<<mpolaska;
     
    if(DaLiKasni()==0){
    OcekivanoVrijemeDolaska(hpolaska,mpolaska);
    std::cout<<std::setw(7)<<std::setfill(' ')<</*hpolaska+tvoznje/60*/hpolaska<<":"<<std::setw(2)<<std::setfill('0')<</*mpolaska+tvoznje%60*/mpolaska;
    std::cout<<std::setw(8)<<std::setfill(' ')<<brperona<<std::endl;
    }else
    {
        std::cout<<" "<<"(Planirano "<<hpolaska<<":"<<std::setfill('0')<<std::setw(2)<<mpolaska-kasnjenje<<", Kasni "<<kasnjenje<<" min)"<<std::setfill(' ')<<std::endl;

    }
   // std::cout<<std::endl;
}
class Polasci{
private: 
int broj;
 int max;
 std::vector<Polazak*> polasci;
     

 //Polazak **polasci;
 public:
 static int VrijemePolaska(const Polazak& polazak);
 explicit Polasci(int max_broj_polazaka);
Polasci(std::initializer_list<Polazak> lista_polazaka);
~Polasci();
Polasci(const Polasci &polasci);
Polasci(Polasci &&polasci);
Polasci &operator =(const Polasci &polasci);
Polasci &operator =(Polasci &&polasci);
void RegistrirajPolazak(std::string odrediste, std::string oznaka_voznje,
 int broj_perona, int sat_polaska, int minute_polaska, int trajanje_voznje);
void RegistrirajPolazak(Polazak *polazak);
int DajBrojPolazaka() const;
int DajBrojPolazakaKojiKasne() const;
Polazak &DajPrviPolazak();
Polazak DajPrviPolazak() const;
Polazak &DajPosljednjiPolazak();
Polazak DajPosljednjiPolazak() const;
void Ispisi() const;
void IsprazniKolekciju();

};
Polasci::Polasci(int max_broj_polazaka): max(max_broj_polazaka){}
Polasci::Polasci(std::initializer_list<Polazak> lista_polazaka):max(lista_polazaka.size()){
    for(const Polazak& polazak:lista_polazaka){
        polasci.push_back(new Polazak(polazak));
    }
    
}
Polasci::~Polasci(){
    for(Polazak *polazak: polasci){
        delete polazak;
    }
}
Polasci::Polasci(const Polasci &polasci):max(polasci.max){
    for(const Polazak* polazak:polasci.polasci){
        this->polasci.push_back(new Polazak(*polazak));
    }

}
Polasci::Polasci(Polasci &&polasci):max(polasci.max), polasci(std::move(polasci.polasci)){
    polasci.max=0;

}
Polasci& Polasci::operator =(const Polasci &polasci){
  if(this==&polasci){
      return *this;
  }
  for(Polazak* polazak:this->polasci){
      delete polazak;
  }
  this->polasci.clear();
  max=polasci.max;
  for(const Polazak* polazak:polasci.polasci){
      this->polasci.push_back(new Polazak(*polazak));
  }
  return *this;
} 
Polasci &Polasci::operator =(Polasci &&polasci){
    if(this==&polasci){
        return *this;
    }
    for(Polazak* polazak:this->polasci){
        delete polazak;
    }
    this->polasci.clear();
    max=polasci.max;
    this->polasci=std::move(polasci.polasci);
    polasci.max=0;
    return *this;
}
     

void Polasci::RegistrirajPolazak(std::string odrediste, std::string oznaka_voznje,
 int broj_perona, int sat_polaska, int minute_polaska, int trajanje_voznje){
     if(polasci.size()>=max){
         throw std::range_error("Dostignut maksimalni broj polazaka.");
     }
     polasci.push_back(new Polazak(odrediste, oznaka_voznje,broj_perona,sat_polaska,minute_polaska,trajanje_voznje));

 }
 void Polasci::RegistrirajPolazak(Polazak *polazak){
     if(polasci.size()>=max){
         throw std::range_error("Dostignut maksimalni broj polazaka.");
     }
     polasci.push_back(polazak);
 }
 int Polasci::DajBrojPolazaka() const{
     return polasci.size();
 }
 int Polasci::DajBrojPolazakaKojiKasne() const{
     return std::count_if(polasci.begin(),polasci.end(),[](const Polazak* polazak){
         return polazak->DaLiKasni();
     });
 }
 Polazak &Polasci::DajPrviPolazak(){
     if(polasci.empty()){
         throw std::logic_error("Nema registriranih polazaka");
     }
     std::vector<Polazak*>sortvektor(polasci);
     return **std::min_element(polasci.begin(), polasci.end(),[](const Polazak *p1, const Polazak *p2){
           int sp1,mp1,sp2,mp2;
           p1->OcekivanoVrijemePolaska(sp1,mp1);
           p2->OcekivanoVrijemePolaska(sp2,mp2);
           if(p1==p2)
           return mp1<mp2;
           return sp1<sp2;
     });
//*polasci[0];
     /*std::min_element(polasci.begin(), polasci.end(),[](const Polazak*p1, const Polazak*p2){
         return p1->OcekivanoVrijemeDolaska()<p2->OcekivanoVrijemeDolaska();
     });*/
 }
 Polazak Polasci::DajPrviPolazak() const{
     if(polasci.empty()){
         throw std::logic_error("Nema registriranih polazaka");
     }
     return **std::min_element(polasci.begin(), polasci.end(),[](const Polazak *p1, const Polazak *p2){
           int sp1,mp1,sp2,mp2;
           p1->OcekivanoVrijemePolaska(sp1,mp1);
           p2->OcekivanoVrijemePolaska(sp2,mp2);
           if(p1==p2)
           return mp1<mp2;
           return sp1<sp2;
     });
     //*polasci[0];
 }
 Polazak & Polasci::DajPosljednjiPolazak(){
     if(polasci.empty()){
         throw std::logic_error("Nema registriranih polazaka");
     }
     return **std::max_element(polasci.begin(), polasci.end(),[](const Polazak *p1, const Polazak *p2){
           int sp1,mp1,sp2,mp2;
           p1->OcekivanoVrijemePolaska(sp1,mp1);
           p2->OcekivanoVrijemePolaska(sp2,mp2);
           if(p1==p2)
           return mp1<mp2;
           return sp1<sp2;
     });
     
    //*polasci.back();
     /**std::max_element(polasci.begin(), polasci.end(),[](const Polazak *p1, const Polazak *p2){

     });*/
 }
 Polazak Polasci::DajPosljednjiPolazak() const{
     if(polasci.empty()){
         throw std::logic_error("Nema registriranih polazaka");
     }
     return **std::max_element(polasci.begin(), polasci.end(),[](const Polazak *p1, const Polazak *p2){
           int sp1,mp1,sp2,mp2;
           p1->OcekivanoVrijemePolaska(sp1,mp1);
           p2->OcekivanoVrijemePolaska(sp2,mp2);
           if(p1==p2)
           return mp1<mp2;
           return sp1<sp2;
     });
     
     //*polasci.back();
     /* *std::max_element(polasci.begin(), polasci.end(),[](const Polazak *p1, const Polazak *p2){

     });*/
 }
 void Polasci::Ispisi() const{
     std::cout<<"   Voznja                  Odrediste   Polazak   Dolazak   Peron"<<std::endl;
     std::cout<<"----------------------------------------------------------------------"<<std::endl;
     auto rez=[]( Polazak *p1,  Polazak *p2){
         int sp1,mp1, sp2,mp2;
         p1->OcekivanoVrijemePolaska(sp1,mp1);
         p2->OcekivanoVrijemePolaska(sp2,mp2);
         if(p1==p2)
         return mp1<mp2;
         return sp1<sp2;
     };
     std::vector<Polazak*> sortiranipolazak(polasci);
     std::sort(sortiranipolazak.begin(),sortiranipolazak.end(),rez);
     for(const Polazak* polazak:sortiranipolazak){
         polazak->Ispisi();
     }
 }
 void Polasci::IsprazniKolekciju(){
     for(Polazak *polazak:polasci){
         delete polazak;
     }
     polasci.clear();
 }



int main ()
{
 
try{
    Polazak p("A", "B", 1,1,1,1);
    p.PostaviKasnjenje(-1);
}catch(std::invalid_argument& e){
    std::cout<<"Neregularna vrijednost kasnjenja."<<std::endl;
}

    try{
        Polasci p(1);
        p.RegistrirajPolazak("A", "B", 1,1,1,1);
        p.RegistrirajPolazak("C", "D", 2,2,2,2);
    }catch(std::range_error& e){
        std::cout<<"Dostignut maksimalni broj polazaka.";
    }
  return 0;
}
