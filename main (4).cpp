//TP 2022/2023: Zadaća 2, Zadatak 2
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
void RastavaBroja(int n, int &p,int &q){
    if(n==0){
        p=0;
        q=1;
        return;
    }else{
        int N=abs(n);
        for(int i=sqrt(N);i>0;i--){
            if(N%(i*i)==0){
                q=n<0?i:i;
                 p=n/(i*i);
               break;
            }
        }
       
    }
}
    /*if(n<0){
        p=-1;
        n=-n;
    }else{
   */
   
       
    


int main ()
{ 
    int n, p,q;
    int suma=0;
  std::cout<<"Unesi broj: "<<std::endl;
  std::cin>>n;
  RastavaBroja(n,p,q);
  std::cout<<n<<" = "<<p<<"*"<<q<<"^2"<<std::endl;
  
	return 0;
}
