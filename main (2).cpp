//TP 2022/2023: Zadaća 1, Zadatak 3
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
std::vector<std::vector<int>> KreirajSpiralnuMatricu(int red, int kolona, int k, bool smjer){
 if(red<=0 || kolona <=0){
     return std::vector<std::vector<int>> ();//prazna matrica
 }
 std::vector<std::vector<int>>mat(red, std::vector<int>(kolona));
 int gornjag=0, donjag=red-1, lijevag=0,desnag=kolona-1, rez=k;
if(smjer)
 while( lijevag<=desnag){
     //if(lijevo){ 
         for(int i=lijevag;i<=desnag;i++){
             mat.at(gornjag).at(i)=rez++;
         }
         gornjag++;
         for(int i=gornjag;i<=donjag;i++){
             mat.at(i).at(desnag)=rez++;
         }
         desnag--;
         
         for(int i=desnag;i>=lijevag;i--){
             mat.at(donjag).at(i)=rez++;
         }
         donjag--;
         //lijeva spiralna matrica
         for(int i=donjag;i>=gornjag;i--){
             mat.at(i).at(lijevag)=rez++;
         }
         lijevag++;
        
   
 
 }
 else {
      while( lijevag<=desnag){
     //if(lijevo){ 
          for(int i=gornjag;i<=donjag;i++){
             mat.at(i).at(lijevag)=rez++;
         }
         lijevag++;
         for(int i=lijevag;i<=desnag;i++){
             mat.at(donjag).at(i)=rez++;
         }
         donjag--;
        for(int i=donjag;i>=gornjag;i--){
             mat.at(i).at(desnag)=rez++;
         }
         desnag--;
         
         for(int i=desnag;i>=lijevag;i--){
             mat.at(gornjag).at(i)=rez++;
         }
         gornjag++;
         //lijeva spiralna matrica
        
 }

 }

      
 return mat;

}
bool DaLiJeSpiralnaMatrica( std::vector<std::vector<int>> mat){
    if(mat.size()==0 || mat[0].size()==0){
        return true; //ako je spiralna matrica
    }else if(mat.size()<0 || mat[0].size()<0){
        return false;
    }
    int red=mat.size();
   
    int kolona=mat[0].size();
    
    int gornja=0, donja=red-1, lijevo=0, desno=kolona-1;
    int brelem=red*kolona;
    int brojac=0;
    while(brojac<brelem){
        for(int i=lijevo; i<=desno &&brojac<brelem;i++){//desno
            if(mat.at(gornja).at(i)!=brojac+1)
            return false;
            brojac++;
            }
        gornja++;
        for(int i=gornja; i<=donja &&brojac<brelem;i++){//donja
            if(mat.at(i).at(desno)!=brojac+1)
            return false;
            brojac++;
        }
        desno--;
        if(gornja<=donja){
        for(int i=desno; i>=lijevo && brojac<brelem;i--){//lijevo
           if(mat.at(donja).at(i)!=brojac+1)
           return false;
           brojac++;
            
        }
        donja--;
        }
        if(lijevo<=desno){
        for(int i=donja; i>=gornja&& brojac<brelem;i--){//gornja
           if(mat.at(i).at(lijevo)!=brojac+1)
           return false;
           brojac++;
        }
        lijevo++;
        }
    }
   /*for(int i=0; i<red; i++){
       for(int j=0; j<kolona; j++){
           if(mat.at(i).at(j)!=i*kolona+j+1){
               return false;
           }
       }
   }*/
return true;
}


int main ()
{
    int m,n,k;
    char smjer;
    std::cout<<"Unesite broj redova i kolona matrice: ";
    std::cin>>m>>n;
    std::cout<<"Unesite pocetnu vrijednost: ";
    std::cin>>k;
    std::cout<<"Unesite L za lijevu, a D za desnu spiralnu matricu: "<<std::endl;
    std::cin>>smjer;
    std::vector<std::vector<int>> mat=KreirajSpiralnuMatricu(m,n, k,(smjer=='D' || smjer=='d')); //kreiranje matirce i ispis na ekran
   /* if(DaLiJeSpiralnaMatrica(mat))
    std::cout<<"Jeste spiralna."<<std::endl;
    else
    std::cout<<"Nije spiralna."<<std::endl;*/
    int sirina=1;
    for(int i=0; i<m;i++){
        for(int j=0;j<n;j++){
            sirina=std::max(sirina, (int)std::to_string(mat.at(i).at(j)).length());
            
        }
    }
   std::cout<<"Kreirana spiralna matrica: "<<std::endl;
      
        for(int i=0; i<m;i++){
            for(int j=0; j<n;j++){
                std::cout<<std::setw(sirina)<<mat.at(i).at(j)<<" ";
            }
            std::cout<<std::endl;
        }
    
   

   
	return 0;
}
