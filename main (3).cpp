//TP 2022/2023: Zadaća 1, Zadatak 4
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <stdexcept>
#include <cctype>
#include <iomanip>

bool NumerickiSlovaBrojevi(char broj){ // je i slovo ili broj
  

  return (broj>='A' && broj<='Z') || (broj>='a'&&broj<='z')||(broj>='0' && broj<='9');
    
}
bool ProvjeraRecenice( std::string s, int pocetak, int kraj){
    for(int i=pocetak;i<=kraj;i++){
        if(!NumerickiSlovaBrojevi(s.at(i)))
        return false;
        
    }
    return true;
}
bool UsporedbaRijeci(std::string str1, int pocetak1, int kraj1, std::string str2){
    if(kraj1-pocetak1+1!=str2.length()){
        return false;
    }
    for(int i=pocetak1; i<=kraj1;i++){
        if(tolower(str1.at(i))!=tolower(str2.at(i-pocetak1))){
            return false;
        }
    }
    return true;
}
std::string Cenzura(std::string recenica, std::vector<std::string> zabranjene_rijeci){
    for(auto zabranjena_rijec:zabranjene_rijeci){
        for(int i=0; i<zabranjena_rijec.size();i++)
        if(!NumerickiSlovaBrojevi(zabranjena_rijec.at(i))){
            throw std::logic_error("Neispravna riječ");
        } 
    }
 std::string rez=" ";
 int i=0;
 while(i<recenica.length()){
     if(NumerickiSlovaBrojevi(recenica.at(i))){
         int pocetak=i;
         while(i<recenica.length() && NumerickiSlovaBrojevi(recenica.at(i))){
             i++;
         }
         int kraj=i-1;
         std::string rijec=recenica.substr(pocetak, kraj-pocetak+1);
         if(ProvjeraRecenice(recenica, pocetak, kraj)){
             bool zabranjena=false;
             for(std::string zabranjena_rijec:zabranjene_rijeci){
                 if(UsporedbaRijeci(recenica,pocetak, kraj,zabranjena_rijec)){
                     zabranjena=true;
                     break;
                 }
             }
             if(zabranjena){
                 std::string zamjena(rijec.size(), '*');
                 rez+=zamjena;
             }else{
                 rez+=recenica.substr(pocetak, kraj-pocetak+1);
             }
         }else{
             rez+=recenica.substr(pocetak,kraj-pocetak+1);

         }
     }else{
         rez+=recenica.at(i);
         i++;
     }
 }  
 return rez;
}
int main ()
{
    std::string recenica;
    std::cout<<"Unesite recenicu: "<<std::endl;
    std::getline(std::cin, recenica);
    std::vector<std::string>zabranjena_rijec;
    std::cout<<"Unesite zabranjene rijeci (. za kraj): "<<std::endl;
    while(true){
        std::string rijec;
        std::cin>>rijec;
        if(rijec==".")
        break;
        zabranjena_rijec.push_back(rijec);
    }
    try{
        std::string cenzura=Cenzura(recenica, zabranjena_rijec);
        std::cout<<"Cenzurisana recenica:"<<cenzura<<std::endl;
    }catch(std::logic_error &e){
        std::cout<<"GRESKA: "<<e.what()<<std::endl;
    }


	return 0;
}
