//TP 2022/2023: ===TITLE===
#include <iostream>
#include <cmath>
#include <fstream>
#include <functional>
#include <stdexcept>
#include <vector>
#include <algorithm>
template<typename TipElemenata>
class DatotecniKontejner{
    std::fstream tok;
    //std::string ime_datoteke;
    public:
    DatotecniKontejner(const std::string& ime_datoteke){
        tok.open(ime_datoteke, std::ios::binary | std::ios::in |std::ios::out  );
        if(!tok){
            tok.clear();
            tok.open(ime_datoteke, std::ios::binary|std::ios::out);
            if(!tok){
                throw std::logic_error("Problemi prilikom otvaranja ili kreiranja datoteke");
            }
            tok.close();
            tok.open(ime_datoteke, std::ios::binary | std::ios::in| std::ios::out);
        }
    }
    
    void DodajNoviElement(const TipElemenata& element){
        tok.seekp(0, std::ios::end);
        int bajti=tok.tellp();
        tok.write(reinterpret_cast<const char*>(&element), sizeof(TipElemenata));
        if(!tok){
            throw std::logic_error("Problemi prilikom pristupanja datoteci");
        }
        tok.seekg(0, std::ios::end);
        bajti=tok.tellp();
        if(bajti==-1){
            throw std::logic_error("Problemi prilikom pristupanja datoteci");
        }
        
       
       
    }
    int DajBrojElemenata(){
       tok.seekg(0, std::ios::end);
       int bajti=tok.tellg();
       if(bajti==-1){
           throw std::logic_error("Problemi prilikom pristupanja datoteci");
       }
       //int brbajta=static_cast<int>(bajti);
       return bajti/sizeof(TipElemenata);
    }
    TipElemenata DajElement(int pozicija){
        if(pozicija<0 ||pozicija>=DajBrojElemenata()){
            throw std::range_error("Neispravna pozicija");
        }
        tok.seekg(pozicija*sizeof(TipElemenata), std::ios::beg);
        TipElemenata element;
        tok.read(reinterpret_cast<char*>(&element), sizeof(TipElemenata));
        if(!tok){
            throw std::logic_error("Problemi prilikom pristupanja datoteci");
        }
        return element;
    }
    void IzmijeniElement(int pozicija, const TipElemenata& element){
        if(pozicija<0 || pozicija >=DajBrojElemenata()){
            throw std::range_error("Neispravna pozicija");
        }
        
        tok.seekp(pozicija *sizeof(TipElemenata), std::ios::beg);
        tok.write(reinterpret_cast< const char*>(&element), sizeof(TipElemenata));
        if(!tok){
            throw std::logic_error("Problemi prilikom pristupanja datoteci");
        }
       
    }
    void Sortiraj(std::function<bool(const TipElemenata&, const TipElemenata&)> kriterij=std::less<TipElemenata>()){
        int br_elemenata=DajBrojElemenata();
        std::vector<TipElemenata> vektor;
        for(int i=0;i<br_elemenata;i++){
            vektor.push_back(DajElement(i));
            /*for(int j=0;j<br_elemenata-i-1;j++){
                TipElemenata elem1=DajElement(j);
                TipElemenata elem2=DajElement(j+1);
                if(!kriterij(elem1, elem2)){
                    IzmijeniElement(j,elem2);
                    IzmijeniElement(j+1,elem1);
                   // std::swap(elem1,elem2);
                }
            }*/
        }
        std::sort(vektor.begin(),vektor.end(),kriterij);
        for(int i=0;i<br_elemenata;i++){
            IzmijeniElement(i,vektor[i]);
        }

    }
};

int main ()
{


	return 0;
}
