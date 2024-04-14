//TP 2022/2023: ===TITLE===
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <fstream>
#include <initializer_list>
std::ostream &operator<<(std::ostream &tok, std::vector<int>vektor){
    for(int i=0;i<vektor.size();i++)
    if(i==(int)vektor.size()-1)
    tok<<vektor[i]<<" kg";
    else
    tok<<vektor[i]<<" kg, ";
    return tok;
}
class ApstraktnoVozilo{
    protected:
    int m;
    public:
    ApstraktnoVozilo(int m):m(m){}
    int DajTezinu() const{
        return m;
    }
    virtual int DajUkupnuTezinu() const=0;
    virtual ApstraktnoVozilo* DajKopiju() const=0;
    virtual void IspisiPodatke() const=0;
    virtual ~ApstraktnoVozilo(){}
};
class Automobil:public ApstraktnoVozilo{
    std::vector<int>mp;
    public:
    Automobil(int x, std::vector<int>y): ApstraktnoVozilo(x), mp(y){}
    int DajUkupnuTezinu() const override{
        int rez=m;
        for(int i:mp){
           rez+=i;
        }
        return rez;

    }
    Automobil* DajKopiju() const override{
        return new Automobil(*this);

    }
    void IspisiPodatke() const override{
        std::cout<<"Vrsta vozila: Automobil"<<std::endl;
        std::cout<<"Vlastita tezina: "<<DajTezinu()<<" kg"<<std::endl;
        std::cout<<"Tezine putnika: "<<mp<<std::endl;
        std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" kg"<<std::endl;
    }
    virtual ~Automobil() {}
};
class Kamion:public ApstraktnoVozilo{
    int mt;
    public:
    Kamion(int x,int y):ApstraktnoVozilo(x), mt(y){}
    int DajUkupnuTezinu() const override{
        return mt+m;
    }
    Kamion* DajKopiju() const override{
        return new Kamion(*this);
    }
    void IspisiPodatke() const override{
       // std::cout<<"Tezina vozila: "<<m<<", Ukupna tezina: "<<DajUkupnuTezinu()<<std::endl;
      std::cout<<"Vrsta vozila: Kamion"<<std::endl;
        std::cout<<"Vlastita tezina: "<<DajTezinu()<<" kg"<<std::endl;
        std::cout<<"Tezina tereta: "<<mt<<" kg"<<std::endl;
        std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" kg"<<std::endl;
      // std::cout<<DajUkupnuTezinu()<<std::endl;
    }
    virtual ~Kamion(){}
};
 class Autobus:public ApstraktnoVozilo{
     int br;
     double srm;
     public:
     Autobus (int x,int y,int z):ApstraktnoVozilo(x), br(y), srm(z){}
     int DajUkupnuTezinu() const override{
         return srm*br+m;
     }
     Autobus* DajKopiju() const override{
         return new Autobus(*this);
     }
     void IspisiPodatke() const override{
        // std::cout<<"Tezina vozila: "<<m<<", Ukupna tezina: "<<DajUkupnuTezinu()<<std::endl;
       std::cout<<"Vrsta vozila: Autobus"<<std::endl;
        std::cout<<"Vlastita tezina: "<<DajTezinu()<<" kg"<<std::endl;
        std::cout<<"Broj putnika: "<<br<<std::endl;
        std::cout<<"Prosjecna tezina putnika: "<<srm<<" kg"<<std::endl;
        std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" kg"<<std::endl;
       // std::cout<<DajUkupnuTezinu()<<std::endl;
     }
 };
 class Vozilo{
    ApstraktnoVozilo *av;
    public:
    Vozilo(): av(nullptr){}
    Vozilo(const Vozilo &v){
        if(v.av!=nullptr){
            av=v.av->DajKopiju();
        }else{
            av=nullptr;
        }
    }
    Vozilo(const Automobil& v){
        av=new Automobil(v);
    }
    Vozilo(const Kamion& v){
        av=new Kamion(v);
    }
    Vozilo(const Autobus& v){
        av=new Autobus(v);
    }
    Vozilo& operator=(const Vozilo& v){
        if(this==&v){
            return *this;
        }
        delete av;
        if(v.av!=nullptr){
            av=v.av->DajKopiju();
        }else{
            av=nullptr;
        }
        return *this;
    }
    int DajUkupnuTezinu() const{
        if(av!=nullptr){
            return av->DajUkupnuTezinu();
        }
        return 0;
    }
   int DajTezinu() const{
       if(av!=nullptr){
           return av->DajTezinu();
       }
       return 0;
   }
   void IspisiPodatke() const{
       if(av!=nullptr){
           av->IspisiPodatke();
       }
   }
   ~Vozilo(){
       delete av;
   }
 };


int main ()
{
 std::vector<Vozilo>vozilo;
 std::ifstream otvori("VOZILA.TXT");
 char t;
 if(!otvori){
     std::cout<<"Ne moze";
     return 1;
 }
 while(otvori>>t){
     if(t=='A'){
         int m, br;
         std::vector<int>mp;
         otvori>>m>>br;
         int x;
         for(int i=0;i<br;i++){
             otvori>>x;
             mp.push_back(x);
         }
         Automobil autom(m,mp);
         vozilo.push_back(autom);
     }else if(t=='K'){
         int mk, mt;
         otvori>>mk>>mt;
         Kamion kamion(mk,mt);
         vozilo.push_back(kamion);

     }else if(t=='B'){
        int mb, br, sr;
         otvori>>mb>>br>>sr;
         Autobus autobus(mb,br,sr);
         vozilo.push_back(autobus);
     }else{
         std::cout<<"Izuzetak: NEPOSTOJECE VOZILO!";
         return 1;
     }
 }
  if(otvori.bad()){
      std::cout<<"Datoteka je ostecena!"<<std::endl;
      return 1;
  }
  else if(!otvori.eof()){
      std::cout<<"Datoteka sadrzi neocekivane podatke"<<std::endl;
      return 1;
  }
  sort(vozilo.begin(),vozilo.end(),[](const Vozilo& x, const Vozilo& y){
      return x.DajUkupnuTezinu()<y.DajUkupnuTezinu();
  });
  for(const auto& i:vozilo){
      //i.IspisiPodatke();
      std::cout<<i.DajUkupnuTezinu()<<std::endl;
     //delete i;
  }
	return 0;
}
