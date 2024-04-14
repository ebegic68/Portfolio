//TP 2022/2023: Zadaća 2, Zadatak 3
#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>
#include <stdexcept>
#include <vector>
#include <iomanip>
/*std::string f(std::string a, std::string b){  
    return a+" "+b;                              // funkija za nadovezivanje dva stringa
}*/
std::string operator*(std::string a, std::string b){
    return a+ "*"+b;
}
template<typename Tip, typename Tip1, typename Tip2> 
auto GeneraliziraniMatricniProizvod(const std::vector<std::vector<Tip>>&A, const std::vector<std::vector<Tip>>&B, Tip1 f, Tip2 g){
   if(A.empty() || B.empty() || A.at(0).size()!=B.size()){
        throw std::domain_error("Matrice nisu saglasne za mnozenje");
    }
    std::vector<std::vector<decltype(g(Tip(),Tip()))>>rez(A.size(), std::vector<decltype(g(Tip(),Tip()))>(B.at(0).size())); //kreiran novi niz u kojem se smjesta suma 
     try{
         for(size_t i=0; i<A.size();i++){
             for(size_t j=0;j<B.at(0).size();j++){
                 rez.at(i).at(j)=f(g(A.at(i).at(0),B.at(0).at(j)), g(A.at(i).at(1), B.at(1).at(j)));
                  for(size_t k=2; k<A.at(0).size();k++){
                     rez.at(i).at(j)=f(rez.at(i).at(j), g(A.at(i).at(k), B.at(k).at(j)));
                 }
            
             }
         }
     }catch(...){
         throw std::runtime_error("Neocekivani problemi pri racunanju");
     }
     return rez;
}

int main ()
{ int n, m,v;
std::cout<<"Unesite broj redova prve matrice: ";
std::cin>>m;
std::cout<<"Unesite broj kolona prve matrice, ujedno broj redova druge matrice: ";
std::cin>>n;
std::cout<<"Unesite broj kolona druge matrice: "<<std::endl;
std::cin>>v;
std::vector<std::vector<std::string>>A(m, std::vector<std::string>(n));
std::vector<std::vector<std::string>>B(n, std::vector<std::string>(v));
try{
std::cout<<"Unesite elemente prve matrice: "<<std::endl;
for(auto i=0; i<m;i++){
    for(auto j=0; j<n; j++){
        std::cin>>A.at(i).at(j);
    }
}
std::cout<<"Unesite elemente druge matrice: "<<std::endl;
for(auto i=0; i<n;i++){
    for(auto j=0; j<v;j++){
        std::cin>>B.at(i).at(j);
    }
}}
catch(const std::exception&e){
    std::cout<<e.what()<<std::endl;
}

 auto f1=[](const std::string& a, const std::string& b){
        return a+"+"+b;
    };
    auto f2= [](const std::string& a, const std::string& b){
         return a+"*"+b;
    };
   // auto rez=GeneraliziraniMatricniProizvod(A,B,f1,f2);
try{
   
    
   
    std::cout<<"\nMatricni proizvod: "<<std::endl;
    auto rez=GeneraliziraniMatricniProizvod(A,B,f1,f2);
       size_t sirina=0;
       for(const auto& red:rez){
           for(const auto& el:red){
                sirina=std::max(sirina, el.size());
           }
       }
    
   for(const auto& red:rez){
        for(const auto& el:red){
            std::cout<<std::left<<std::setw(sirina+1)<<el<<" ";
        }
        std::cout<<std::endl;
    }
    
}catch(...){
     //std::cout<<message.what()<<std::endl;
     //std::cout<<"Matrice nisu saglasne za mnozenje"<<std::endl;
}


	return 0;
}
