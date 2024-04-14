//TP 2022/2023: Zadaća 1, Zadatak 2
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iomanip>
#include <vector>
std::vector<std::vector<double>> UsrednjavajuciFilter(const std::vector<std::vector<double>>&m, int N){
    //void UsrednjavajuciFilter(const std::vector<std::vector<double>>m, int N){
    if(N<=0){
        throw std::domain_error("Neispravan red filtriranja!");
    }
    int n=m.size();
    int v=m.at(0).size();
    std::vector<std::vector<double>> FiltriranaMatrica(n, std::vector<double>(v,0.0));
    for(int i=0; i<m.size();i++){
       
        for(int j=0;j<m.at(i).size();j++){
            double sum=0.0;
            int br_piksela=0;
            for(int k=std::max(i-N,0); k<=std::min((int)m.size()-1, i+N);k++){
                for(int l=std::max(j-N, 0);l<=std::min((int)m.at(k).size()-1, j+N);l++){
                    //if(k>=0 && k<n && l>=0 && l<v){
                    sum+=m.at(k).at(l);
                    br_piksela++;
                   // }
                }
            }
            FiltriranaMatrica.at(i).at(j)=sum/br_piksela;

        }
    }
    return FiltriranaMatrica;
}


int main ()
{ 
    int r,k,fil;
    std::cout<<"Unesite broj redova i kolona matrice: ";
    std::cin>>r>>k;
    std::cout<<"Unesite elemente matrice: "<<std::endl;
    std::vector<std::vector<double>>matrica(r, std::vector<double>(k,0));
    for(int i=0; i<r; i++){
        for(int j=0; j<k;j++){
            std::cin>>matrica.at(i).at(j);
        }
    }
    std::cout<<"Unesite red filtriranja: ";
    std::cin>>fil;
    try{
        std::vector<std::vector<double>>filtrirano=UsrednjavajuciFilter(matrica, fil);
        //std::vector<double> filtrirano=UsrednjavajuciFilter(matrica, fil);
        std::cout<<"Matrica nakon filtriranja: "<<std::endl;
        int sirinam=7;
        std::cout<<std::fixed<<std::setprecision(2);
        for(int i=0; i<filtrirano.size();i++){
            for(int j=0;j<filtrirano[i].size();j++){
                std::cout<<std::setw(sirinam)<<filtrirano.at(i).at(j);
            }
            std::cout<<std::endl;
        }

    }
    catch(std::domain_error &e){
        std::cout<<"GRESKA: "<<e.what()<<std::endl;
    }


	return 0;
}
