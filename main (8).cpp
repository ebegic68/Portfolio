//TP 2022/2023: Zadaća 3, Zadatak 2
#include <iostream>
#include <cmath>
#include <map>
#include <string>
#include <vector>
#include <stdexcept>
#include <set>
#include <tuple>
#include <algorithm>


typedef std::map<std::string, std::vector<std::string>> Knjiga;
typedef std::map<std::string, std::set<std::tuple<std::string,int,int>>> KnjigaPostavi;
typedef std::set<std::tuple<std::string, int,int>> setuj;
bool alfanumericki(char c){
    return ((c>='a' && c<='z')||(c>='A' && c<='Z')|| (c>='0' && c<='9'));
}
void zamijenimala(std::string &rijec){
   
    
    std::transform(rijec.begin(),rijec.end(),rijec.begin(),[](unsigned char c){
        return std::tolower(c);
    });
   
}

KnjigaPostavi KreirajIndeksPojmova( const Knjiga &knjiga){
   KnjigaPostavi index;
  
  std::vector<std::string> rijeci;
  
  for(auto i=knjiga.begin();i!=knjiga.end();i++){
        const std::string &poglavlje=i->first;
        const std::vector<std::string> &stranice=i->second;
        for(int j=0;j<stranice.size();j++){
            const std::string &stranica=stranice[j];
            std::string kopiraj_str=stranica;
            zamijenimala(kopiraj_str);
            int duzina=kopiraj_str.size();
            int mjesto=0;
            while(mjesto<duzina){
                 std::string rijec;
                 while(mjesto<duzina && alfanumericki(kopiraj_str[mjesto])){
                     rijec.push_back(kopiraj_str[mjesto]);
                     mjesto++;
                 }
                 if(!rijec.empty()){
                     if(std::find(rijeci.begin(),rijeci.end(),rijec)==rijeci.end()){
                         rijeci.push_back(rijec);
                     }
                     std::tuple<std::string,int,int> pozicija(poglavlje,j+1,mjesto-rijec.length());
                     index[rijec].insert(pozicija);
                 }
               mjesto++;
            }

        }
    }
    return index;
    
}
 setuj PretraziIndeksPojmova( std::string rijec,const KnjigaPostavi& index){
   //std::string kopija=rijec;
  zamijenimala(rijec);
   auto iterator=index.find(rijec);
   if(iterator!=index.end()){
      // return (iterator->second.begin(), iterator->second.end());
      return iterator->second;
    }else{
        throw std::logic_error("Pojam nije nadjen");
    }
  //return std::set<std::tuple<std::string, int,std::size_t>>();
}
  
void IspisiIndeksPojmova(const KnjigaPostavi &index){
    for(auto it=index.begin();it!=index.end();it++){
      std::cout<<it->first<<": ";
     // const std::vector<std::string> pozicije;
     auto pozicija=it->second.begin();
      for(int i=0;i<it->second.size();i++){
          std::cout<<std::get<0>(*pozicija)<<"/"<<std::get<1>(*pozicija)<<"/"<<std::get<2>(*pozicija);
           pozicija++;
           if(i < it->second.size()-1)
          std::cout<<", ";
    }
      std::cout<<std::endl;
    }
}
int main ()
{
   
    Knjiga book;
    std::string poglavlje;
    for(;;){
        std::cout<<"Unesite naziv poglavlja: "<<std::endl;
        std::getline(std::cin, poglavlje);
        if(poglavlje==".")
        break;
        std::vector<std::string> stranica;
        int i=0;
        while(true){
            std::cout<<"Unesite sadrzaj stranice "<<i+1<<": "<<std::endl;
            std::string sadrzaj;
            std::getline(std::cin, sadrzaj);
            if(sadrzaj==".")
            break;
            stranica.push_back(sadrzaj);
            i++;
        }
        book.insert({poglavlje, stranica});
    }
    std::cout<<"Kreirani indeks pojmova: "<<std::endl;
    auto pojam=KreirajIndeksPojmova(book);
    IspisiIndeksPojmova(pojam);
    for(;;){
        std::cout<<"Unesite rijec: "<<std::endl;
        std::string rijec;
        std::getline(std::cin, rijec);
        if(rijec==".")
        break;
        try{
            auto rez=PretraziIndeksPojmova(rijec, pojam);
            for(const auto& t:rez)
            std::cout<<std::get<0>(t)<<"/"<<std::get<1>(t)<<"/"<<std::get<2>(t)<<" ";
            std::cout<<std::endl;
        } catch(std::logic_error w){
            std::cout<<"Unesena rijec nije nadjena!"<<std::endl;
        }
    }
	return 0;
}
