//TP 2022/2023: Zadaća 4, Zadatak 1
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <iterator>
const double e=1e-10;
const double pi=4*atan(1);
class Krug{
    private:
    std::pair<double, double> c;
    double r;
    public:
explicit Krug(double poluprecnik = 0);
explicit Krug(const std::pair<double, double> &centar, double poluprecnik = 0);
std::pair<double, double> DajCentar() const;
double DajPoluprecnik() const;
double DajObim() const;
double DajPovrsinu() const;
Krug &PostaviCentar(const std::pair<double, double> &centar);
Krug &PostaviPoluprecnik(double poluprecnik);
void Ispisi() const;
Krug &Transliraj(double delta_x, double delta_y);
Krug &Rotiraj(double alpha);
Krug &Rotiraj(const std::pair<double, double> &centar_rotacije, double alpha);
static double RastojanjeCentara(const Krug &k1, const Krug &k2);
static bool DaLiSuIdenticni(const Krug &k1, const Krug &k2);
static bool DaLiSuPodudarni(const Krug &k1, const Krug &k2);
static bool DaLiSuKoncentricni(const Krug &k1, const Krug &k2);
static bool DaLiSeDodirujuIzvani(const Krug &k1, const Krug &k2);
static bool DaLiSeDodirujuIznutri(const Krug &k1, const Krug &k2);
static bool DaLiSePreklapaju(const Krug &k1, const Krug &k2);
static bool DaLiSeSijeku(const Krug &k1, const Krug &k2);
bool DaLiSadrzi(const Krug &k) const;
friend Krug TransliraniKrug(const Krug &k, double delta_x, double delta_y);
friend Krug RotiraniKrug(const Krug &k, double alpha);
friend Krug RotiraniKrug(const Krug &k,
 const std::pair<double, double> &centar_rotacije, double alpha);
 };
    Krug::Krug(double poluprecnik):c({0,0}), r(poluprecnik){
         if(poluprecnik<0){
             throw std::domain_error("Nedozvoljen poluprecnik");
         }
    }
    Krug::Krug(const std::pair<double, double> &centar, double poluprecnik):c(centar), r(poluprecnik){
        if(poluprecnik<0){
            throw std::domain_error("Nedozvoljen poluprecnik");
        }

    }
    std::pair<double,double>Krug::DajCentar() const{
        return c;
    }
    double Krug::DajPoluprecnik() const{
        return r;
    }
    double Krug::DajObim() const{
       return 2*pi*r;
    }
    double Krug::DajPovrsinu() const{
        return pi*pow(r,2);
    }
    Krug& Krug::PostaviCentar(const std::pair<double, double> &centar){
        this->c=centar;
        return *this;
    }
    Krug& Krug::PostaviPoluprecnik(double poluprecnik){
        if(poluprecnik<0){
            throw std::domain_error("Nedozvoljen poluprecnik");
        }
        this->r=poluprecnik;
        return *this;
    }
    void Krug::Ispisi() const{
        std::cout<<"{("<<c.first<<","<<c.second<<"),"<<r<<"}";
    }
    Krug& Krug::Transliraj(double delta_x, double delta_y){
        c.first+=delta_x;
        c.second+=delta_y;
        return *this;
    }
    Krug& Krug::Rotiraj(double alpha){
        double x=c.first*cos(alpha)-c.second*sin(alpha);
        double y=c.first*sin(alpha)+c.second*cos(alpha);
        c.first=x;
        c.second=y;
        return *this;
    }
    Krug &Krug::Rotiraj(const std::pair<double, double> &centar_rotacije, double alpha){
        double x=centar_rotacije.first+(c.first-centar_rotacije.first)*cos(alpha)-(c.second-centar_rotacije.second)*sin(alpha);
        double y=centar_rotacije.second+(c.first-centar_rotacije.first)*sin(alpha)+(c.second-centar_rotacije.second)*cos(alpha);
        c.first=x;
        c.second=y;
        return *this;
    }
    double Krug::RastojanjeCentara(const Krug&k1, const Krug&k2){
        double dx=k2.c.first-k1.c.first;
        double dy=k2.c.second-k1.c.second;
        return std::sqrt(dx*dx+dy*dy);
    }
     bool Krug::DaLiSuIdenticni(const Krug& k1, const Krug& k2){
          return k1.c==k2.c && k1.r==k2.r;
    }
    bool Krug::DaLiSuPodudarni(const Krug& k1, const Krug& k2){
        double rastojanje_centara=RastojanjeCentara(k1,k2);
        return std::abs(k1.r-k2.r)<1e-10 && std::abs(k1.r-rastojanje_centara)<e;
    }
    bool Krug::DaLiSuKoncentricni(const Krug& k1, const Krug& k2){
        return k1.c==k2.c && k1.r!=k2.r;

    }
    bool Krug::DaLiSeDodirujuIzvani(const Krug& k1, const Krug& k2){
        double rastojanje_centara=RastojanjeCentara(k1,k2);
        //return rastojanje_centara==k1.r+k2.r;
        return std::abs(k1.r+k2.r-rastojanje_centara)<e;
    }
    bool Krug::DaLiSeDodirujuIznutri(const Krug& k1, const Krug& k2){
       // if(!DaLiSuIdenticni(k1,k2))
        //return true;
        double rastojanje_centara=RastojanjeCentara(k1,k2);
        //return rastojanje_centara+k2.r==k1.r;
        return std::abs(k1.r-k2.r-rastojanje_centara)<1e-10 && k1.r>k2.r && !DaLiSuIdenticni(k1,k2);
    }
    bool Krug::DaLiSePreklapaju(const Krug& k1, const Krug& k2){
        double rastojanje_centara=RastojanjeCentara(k1,k2);
        return rastojanje_centara<k1.r+k2.r && rastojanje_centara>std::abs(k1.r-k2.r) && DaLiSuKoncentricni(k1,k2);
    }
    bool Krug::DaLiSeSijeku(const Krug& k1, const Krug& k2){
        double rastojanje_centara=RastojanjeCentara(k1,k2);
        if(DaLiSuIdenticni(k1,k2))
        return false;
        if(k1.DaLiSadrzi(k2) || k2.DaLiSadrzi(k1))
        return false;
        return rastojanje_centara<k1.r+k2.r && rastojanje_centara>1e-10 && !DaLiSuPodudarni(k1,k2) ;
    }
    bool Krug::DaLiSadrzi(const Krug& k) const{
        double rastojanje_centara=RastojanjeCentara(*this,k);
        return rastojanje_centara+k.r<r && r-k.r>=0;
    }
 Krug TransliraniKrug(const Krug &k, double delta_x, double delta_y){
     Krug rez=k;
     rez.Transliraj(delta_x,delta_y);
     return rez;
 }
 Krug RotiraniKrug(const Krug &k, double alpha){
     Krug rez=k;
     rez.Rotiraj(alpha);
     return rez;
 }
  Krug RotiraniKrug(const Krug &k, const std::pair<double, double> &centar_rotacije, double alpha){
    Krug rez=k;
    rez.Rotiraj(centar_rotacije,alpha);
    return rez;
 }


int main ()
{
   int br_kruga;
   std::cout<<"Unesite broj krugova: ";
   std::cin>>br_kruga;
   if(br_kruga<=0){
       std::cout<<"Uneseni broj nije prirodan!";
       return 0;
   }
   //std::vector<Krug>krugovi(br_kruga);
   Krug **krugovi;
   //try{
   krugovi=new Krug*[br_kruga];
   for(int i=0;i<br_kruga;i++){
       std::pair<double, double>c;
       double r;
       std::cout<<"Unesite centar "<<i+1<<". kruga: ";
       std::cin>>c.first>>c.second;
       if(!std::cin){
           std::cout<<"Neispravne koordinate centra! Pokusajte ponovo: "<<std::endl;
           i--;
           std::cin.clear();
           continue;
       }
       std::cout<<"Unesite poluprecnik "<<i+1<<". kruga: ";
       std::cin>>r;
       if(r<0){
           std::cout<<"Neispravan poluprecnik! Pokusajte ponovo: "<<std::endl;
           i--;
           continue;
           //std::cin>>r;
           
       }
   
      /* krugovi[i]=new Krug();
       krugovi[i]->PostaviCentar(c);
       krugovi[i]->PostaviPoluprecnik(r);*/
       try{
           Krug *krug=new Krug(c, r);
          krugovi[i]=krug;
       }catch(const std::bad_alloc&){
           for(int k=0;k<br_kruga;k++)
               delete krugovi[k];
               delete[] krugovi;
            throw;
       }
   }
     double dx,dy;
     std::cout<<"Unesite parametre translacije (delta_x,delta_y): ";
     std::cin>>dx>>dy;
     double alfa;
     std::cout<<"Unesite ugao rotacije oko tacke (0,0) u stepenima: ";
     std::cin>>alfa;
     alfa=alfa*M_PI/180.0;
     std::transform(krugovi, krugovi+br_kruga, krugovi,[dx,dy](Krug *k){
         k->Transliraj(dx,dy);
         return k;
     });
     std::for_each(krugovi,krugovi+br_kruga,[alfa](Krug* k){
         k->Rotiraj(alfa);
     });
     std::sort(krugovi,krugovi+br_kruga,[](Krug* k1, Krug *k2){
         return (*k1).DajPovrsinu() < (*k2).DajPovrsinu();
     });
     /*std::pair<double,double> c_rotacije;
     std::cout<<"Unesite koordinate centra rotacije: ";
     std::cin>>c_rotacije.first>>c_rotacije.second;*/
     std::cout<<"Parametri krugova nakon obavljene transformacije su:\n";
     std::for_each(krugovi, krugovi+br_kruga,[](Krug*k){
         k->Ispisi();
         std::cout<<std::endl;
     });
     //try{
         auto obim_kruga=std::max_element(krugovi,krugovi+br_kruga,[](Krug*k1, Krug* k2){
             return k1->DajObim()<k2->DajObim();
         });
         if(obim_kruga!=krugovi+br_kruga){
             std::cout<<"Krug sa najvecim obimom je: ";
             (*obim_kruga)->Ispisi();
             std::cout<<"\n";
         }
         
     bool sijekuse=false;
     std::vector<std::pair<Krug*, Krug*>>presjekkruga;
      std::for_each(krugovi,krugovi+br_kruga,[&](Krug* k1){
          std::for_each(krugovi, krugovi+br_kruga,[&](Krug* k2){
              if(Krug::DaLiSeSijeku(*k1,*k2)){
                  auto rez=std::find_if(presjekkruga.begin(), presjekkruga.end(),[k1,k2](const std::pair<Krug* , Krug*>&par){
                      return(par.first==k1 && par.second==k2)||(par.first==k2 && par.second==k1);
                  });
                  if(rez==presjekkruga.end()){
             presjekkruga.push_back(std::make_pair(k1,k2));
                 sijekuse=true;
                  std::cout<<"Presjecaju se krugovi: "<<std::endl;
                  k1->Ispisi();
                  std::cout<<" i ";
                  k2->Ispisi();
                  std::cout<<std::endl;
                  return;
            }
     }
        });
      });  
      /* if(!presjekkruga.empty()){
           std::cout<<"Presjecaju se krugovi: "<<std::endl;
           for(const auto& par:presjekkruga){
                  par.first->Ispisi();
                  std::cout<<" i ";
                  par.second->Ispisi();
                  std::cout<<std::endl;
           }
                 
       }else*/if(!sijekuse){
         std::cout<<"Ne postoje krugovi koji se presjecaju!"<<std::endl;
          
                  } 
      
     for(int i=0;i<br_kruga;i++){
         delete krugovi[i];
     }
     delete[] krugovi;


    
	return 0;
}
