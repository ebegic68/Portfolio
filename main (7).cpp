//TP 2022/2023: Zadaća 3, Zadatak 1
#include <iostream>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <functional>
 
 double t=0;
std::function<double(double)> LagrangeovaInterpolacija(const std::vector<std::pair<double, double>> &cvor){
   
    for(int i=0;i<cvor.size();i++){
        for(int j=i+1;j<cvor.size();j++){
    if(cvor[i].first==cvor[j].first){
        throw std::domain_error("Neispravni cvorovi");
    }
    }
}
   // double t=0;
    double min=cvor[0].first;
    double max=cvor[0].first;
    double ep=1e-5;
    for(int i=1;i<cvor.size();i++){
        if(max-cvor[i].first<ep){
            max=cvor[i].first;
        }
        if(min-cvor[i].first>ep){
            min=cvor[i].first;}
    }
    return [=](double x){ 
                 if(((x-max)>ep)||(x-min)<ep){
                
                t=1;
                 }
                 
    double rez=0.0;
    for(int i=0;i<cvor.size();i++){
        double l=cvor[i].second;
        for(int j=0;j<cvor.size();j++){
                if(i!=j){
                    l*=(x-cvor[j].first)/(cvor[i].first-cvor[j].first);
            }
        }
        rez+=l;
    }
    return rez;
    };
}
double f(double x){
    return std::pow(x,2)+std::sin(x)+std::log(x+1);
}
std::function<double(double)> LagrangeovaInterpolacija(std::function<double(double)> funkcija, double poc, double kraj, double kr){
    if(kraj<poc || kr<=0){
        throw std::domain_error("Nekorektni parametri");
    }
    
    std::vector<std::pair<double, double>>cvor((kraj-poc)/kr+1);
    double t=poc;
   // while(t<=kraj){
       for(int i=0;i<cvor.size();i++){
           cvor[i].first=t;
          cvor[i].second=funkcija(t);
       // cvor.push_back(std::make_pair(t,funkcija(t)));
        t+=kr;
    }
    auto L=LagrangeovaInterpolacija(cvor);
    return L;
}
int main ()
{
    int n=0;
    try{
    
    std::cout<<"Odaberite opciju (1 - unos cvorova, 2 - aproksimacija): ";
    std::cin>>n;
    //do{
    if(n==1){
        int brcvor=0;
        std::cout<<"Unesite broj cvorova: ";
        std::cin>>brcvor;
        if(brcvor<0){
            std::cout<<"Neispravan broj cvorova."<<std::endl;
            return 0;
        }
        std::vector<std::pair<double, double>>cvor(brcvor);
        std::cout<<"Unesite cvorove kao parove x y: ";
        for(int i=0;i<brcvor;i++){
            double x,y;
            std::cin>>x>>y;
            cvor[i]=(std::make_pair(x,y));
        }
        
         auto L=LagrangeovaInterpolacija(cvor);
         double arg=0;
        while(true){
            std::cout<<"Unesite argument (ili \"kraj\" za kraj): ";
            std::cin>>arg;
            std::string m;
           std::cin>> m;
           if(m=="kraj"){
                std::cin.clear();
                break;
            }
            if(!std::cin){
                std::cin.clear();
                break;
            }
            arg=std::stod(m);
           
        std::cout<<"f("<<arg<<") = "<<L(arg);
        if(t){
            std::cout<<" [ekstrapolacija]";
            t=0;
        }
        std::cout<<std::endl;
        }
         //std::cout<<"f("<<arg<<") ="<<<<std::endl;
    }else if(n==2){
        double poc, kraj, kr;
        std::cout<<"Unesite krajeve intervala i korak: ";
        std::cin>>poc>>kraj>>kr;
         
                auto L=LagrangeovaInterpolacija(f, poc,kraj,kr);
                 double arg=0;
        while(true){
            std::cout<<"Unesite argument (ili \"kraj\" za kraj): ";
            std::cin>>arg;
            //std::string t;
           // std::cin>> t;
            if(!std::cin){
                std::cin.clear();
                break;
            }
            //arg=std::stod(t);
           
        std::cout<<"f("<<arg<<") = "<<f(arg)<<" P("<<arg<<") = "<<L(arg);
        if(t){
            std::cout<<" [ekstrapolacija]";
            t=0;
        }
        std::cout<<std::endl;
        }
               
            
    }
   
//}while(n==1 ||n==2);
 }catch(const std::domain_error& w){
                std::cout<<w.what()<<std::endl;
            } 


	return 0;
}
