//TP 2022/2023: Zadaća 5, Zadatak 2
#include <iostream>
#include <cmath>
#include <functional>
#include <algorithm>
#include <vector>
int pomocna;
class Padavine{
    
    int maks;
    std::vector<int> padavine;
    static bool VeciOd(int padavina){
        return padavina>pomocna;
    }
    static bool OpadajuciPoredak(int x, int y){
        return x>y;
    }
    static void Ispis(int temp){
        std::cout<<temp<<std::endl;
    }
    public:
    explicit Padavine(int maks):maks(maks), padavine(){
        if(maks<0){
            throw std::range_error("Ilegalna maksimalna kolicina");
        }
    }
    void RegistrirajPadavine(int kolicina) {
        if(kolicina<0 ||kolicina>maks)
        throw std::range_error("Ilegalna kolicina padavina");
        padavine.push_back(kolicina);
    }
    unsigned int DajBrojRegistriranihPadavina() const{
        return padavine.size();
    }
    void BrisiSve(){
        padavine.resize(0);
    }
    int DajMinimalnuKolicinuPadavina() const;
    int DajMaksimalnuKolicinuPadavina() const;
    int DajBrojDanaSaPadavinamaVecimOd(int t) const;
    void Ispisi() const;
    int operator[](int i) const{
        if(i<1 ||i>padavine.size())
        throw std::range_error("Neispravan indeks");
        return padavine[i-1];
    } 
    friend Padavine &operator++(Padavine &p);
    friend Padavine operator++(Padavine &p,int);
    friend Padavine operator+( const Padavine &p, const double t);
     friend Padavine operator-( const Padavine &p, const double t);
      friend Padavine operator+( const Padavine &p1, const Padavine &p2);
      friend Padavine operator-( const Padavine &p1, const Padavine &p2);
      Padavine &operator+=(const Padavine &p){
          *this=*this+p;
          return *this;
      }
      Padavine &operator-=(const Padavine &p){
          *this=*this-p;
          return *this;
      }
      Padavine &operator+=(const int t){
          *this=*this+t;
          return *this;
      }
      Padavine &operator-=(const int t){
          *this=*this-t;
          return *this;
      }
      Padavine operator-();
      friend bool operator==(const Padavine &p1, const Padavine &p2);
      friend bool operator!=(const Padavine &p1, const Padavine &p2);
};
bool operator!=(const Padavine &p1, const Padavine &p2){
    return !(p1==p2);
}
bool operator==(const Padavine &p1, const Padavine &p2){
    if(p1.padavine.size()!=p2.padavine.size())
    return false;
    return std::equal(p1.padavine.begin(), p1.padavine.end(),p2.padavine.begin());
    
}
int OduzmiOdMax(const int t){
    return pomocna-t;
}
Padavine Padavine::operator-(){
          Padavine temp(*this);
          pomocna=maks;
          transform(temp.padavine.begin(), temp.padavine.end(),temp.padavine.begin(), std::bind(OduzmiOdMax, std::placeholders::_1));
          return temp;
      }
      int Oduzmi(const int a, const int b){
          return a-b;
      }
      bool ManjiOd(const int t){
          return t<pomocna;
      }
      Padavine operator-( const Padavine &p1, const Padavine &p2){
          if(p1.padavine.size()<p2.padavine.size())
          throw std::domain_error("Nesaglasni operandi");
          Padavine temp(p1);
          transform(p1.padavine.begin(),p1.padavine.end(),p2.padavine.begin(), temp.padavine.begin(),Oduzmi);
          pomocna=0;
          if(count_if(temp.padavine.begin(),temp.padavine.end(),std::bind(ManjiOd, std::placeholders::_1))>0)
          throw std::domain_error("Nekorektan rezultat operacije");
          return temp;

      }
      int Saberi(const int a, const int b){
          return a+b;
      }
      Padavine operator+( const Padavine &p1, const Padavine &p2){
          Padavine temp(p1);
          temp.maks+=*max_element(p2.padavine.begin(),p2.padavine.end());
          transform(p1.padavine.begin(),p1.padavine.end(),p2.padavine.begin(), temp.padavine.begin(),Saberi);
          pomocna=0;
          if(count_if(temp.padavine.begin(),temp.padavine.end(),std::bind(ManjiOd, std::placeholders::_1))>0)
          throw std::domain_error("Nekorektan rezultat operacije");
          return temp;
      }
      void UvecajZa(int &padavina){
          padavina+=pomocna;
      }
      Padavine operator-( const Padavine &p, const double t){
          Padavine temp(p);
          pomocna=-t;
          for_each(temp.padavine.begin(),temp.padavine.end(), UvecajZa);
          pomocna=0;
          if(count_if(temp.padavine.begin(),temp.padavine.end(),std::bind(ManjiOd, std::placeholders::_1))>0)
          throw std::domain_error("Nekorektan rezultat operacije");
          return temp;
      }
      Padavine operator+( const Padavine &p, const double t){
         Padavine temp(p);
         pomocna=t;
         temp.maks+=t;
         for_each(temp.padavine.begin(), temp.padavine.end(),UvecajZa);
         return temp;
      }
      Padavine operator++(Padavine &p,int){
          Padavine temp(p);
          ++p;
          return temp;
      }
      void UvecajZaJedan(int &t){
          t+=1;
      }
      Padavine &operator++(Padavine &p){
          for_each(p.padavine.begin(), p.padavine.end(), UvecajZaJedan);
               p.maks++;
               return p;
        }
                void Padavine::Ispisi() const{
                    std::vector<int>temp(padavine);
                    sort(temp.begin(), temp.end(), OpadajuciPoredak);
                    for_each(temp.begin(),temp.end(), Ispis);
                }
                int Padavine::DajBrojDanaSaPadavinamaVecimOd(int t) const{
                    if(padavine.size()==0)
                    throw std::range_error("Nema registriranih padavina");
                    pomocna=t;
                    return count_if(padavine.begin(), padavine.end(), std::bind(VeciOd, std::placeholders::_1));
                }
                int Padavine::DajMaksimalnuKolicinuPadavina() const{
                    if(padavine.size()==0)
                    throw std::range_error("Nema registriranih padavina");
                    return *max_element(padavine.begin(), padavine.end());
                }
                int Padavine::DajMinimalnuKolicinuPadavina() const{
                    if(padavine.size()==0)
                    throw std::range_error("Nema registriranih padavina");
                    return *min_element(padavine.begin(), padavine.end());
                }



int main ()
{
  

	return 0;
}
