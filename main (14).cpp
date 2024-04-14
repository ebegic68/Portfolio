// TP 2022/2023: Zadaća 5, Zadatak 1
#include <cmath>
#include <complex>
#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>

const double eps = 1e-8;
//const double pi = atan(1) * 4;
 static double pi = atan(1) * 4;
class Sinusoida {
 double ampl;
  double frekv;
  double faza;
  
 static void Normiraj(Sinusoida& fi){
        while(fi.ampl<0){
            fi.ampl*=-1;
            fi.faza+=pi;
        }
        while(fi.frekv<0){
            fi.frekv*=-1;
            fi.faza=(-1)*fi.faza+pi;
        }
        while(fi.faza<-pi)
        fi.faza+=2*pi;
        while(fi.faza>pi)
        fi.faza-=2*pi;
    }
    public: 
    explicit Sinusoida(double ampl, double frekv , double faza):ampl(ampl),frekv(frekv),faza(faza){
        Normiraj(*this);
    }
  
  double DajAmplitudu() const { return ampl; }
  double DajFrekvenciju() const { return frekv; }
  double DajFazu() const { return faza; }
  std::tuple<double, double, double> DajParametre() const {
    return std::make_tuple(ampl, frekv, faza);
  }
  Sinusoida& PostaviAmplitudu(double newampl) {
    //this->ampl=std::fabs(newampl);
    ampl=newampl;
    Normiraj(*this);
    return *this;
   
  }
  Sinusoida& PostaviFrekvenciju(double newfrekv) {
     //this->frekv=std::fabs(newfrekv);
    frekv=newfrekv;
     Normiraj(*this);
    return *this;
  }
  Sinusoida& PostaviFazu(double newfaza) {
     // this->faza=newfaza-(newfaza/(2*pi))*(2*pi);
     faza=newfaza;
     Normiraj(*this);
    return *this;
  }
  Sinusoida &PostaviParametre(std::tuple<double,double,double> param) {
     ampl=std::get<0>(param);
     frekv=std::get<1>(param);
     faza=std::get<2>(param);
     Normiraj (*this);
    return *this;
  }
  Sinusoida operator-() const { 
       Sinusoida rez(-ampl, frekv, faza);
  Normiraj(rez);
  return rez;
   }
  Sinusoida operator+(const Sinusoida &s) const {
    if (frekv != s.frekv) {
      throw std::domain_error("Razlicite frekvencije");
    }
    double newampl = ampl + s.ampl;
    double sumafaza=faza+s.faza;
    return Sinusoida(newampl, frekv, sumafaza);
  }
  Sinusoida operator-(const Sinusoida &s) const {
    if (frekv != s.frekv) {
      throw std::domain_error("Razlicite frekvencije");
    }
    double newampl = ampl - s.ampl;
    double sumafaza=faza-s.faza;
    return Sinusoida(newampl, frekv, sumafaza);
  }
  Sinusoida operator*(double broj) {
     //double newampl=ampl*broj;
      Sinusoida rez(ampl, frekv, faza);
       rez*=broj;
       Normiraj(rez);
       return rez;
  }
  friend Sinusoida operator*(double broj,const Sinusoida& s){
     /* if (frekv != s.frekv) {
      throw std::domain_error("Razlicite frekvencije");
    }
    double newampl = ampl * s.ampl;
    double sumafaza=faza+s.faza;*/
    Sinusoida rez(s.ampl, s.frekv, s.faza);
    rez*=broj;
    Normiraj(rez);
    return rez;
  }
  Sinusoida operator/(double broj) const{
      if(std::fabs(broj)<eps){
          throw std::domain_error("Dijeljenje sa nulom");
      }
      double newampl=ampl/broj;
      return Sinusoida(newampl, frekv,faza);
  }
  Sinusoida& operator+=(const Sinusoida& s){
      if(frekv!=s.frekv){
          throw std::domain_error("Razlicite frekvenije");
      }
      ampl+=s.ampl;
      faza+=s.faza;
      Normiraj(*this);
      return *this;
  }
  Sinusoida& operator-=(const Sinusoida& s){
      if(frekv!=s.frekv){
          throw std::domain_error("Razlicite frekvenije");
      }
       ampl-=s.ampl;
      faza-=s.faza;
      Normiraj(*this);
      return *this;
  }
  Sinusoida operator*=(double broj){
  ampl*=broj;
  Normiraj(*this);
  return *this;
  }
  Sinusoida& operator*=( Sinusoida& s){
       if(frekv!=s.frekv){
           throw std::domain_error("Razlicite frekvencije");
       }
       ampl*=s.ampl;
       faza=faza*s.ampl+s.faza;
      Normiraj(*this);
      return *this;
    //  ampl*=broj;
     // return *this;
  }
  Sinusoida& operator/=(double broj){
      if(std::abs(broj)<eps){
          throw std::domain_error("Dijeljenje sa nulom");
      }
      ampl/=broj;
      return *this;
       
  }
  double operator()(double t) const{
      return ampl*std::sin(frekv*t+faza);
  }
  double operator[](const std::string& parametar) const{
      if(parametar=="A"){
          return ampl;
      }else if(parametar=="omega"|| parametar=="w"){
          return frekv;
      }else if(parametar=="phi" || parametar=="fi"){
          return faza;
      }else{
          throw std::domain_error("Neispravan naziv parametra");
      }
  }
};

int main() { return 0; }



