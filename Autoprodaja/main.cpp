#include <iostream>
#include<string.h>
#include <fstream>
#include <stdio.h>
//#include <process.h>
//#include <dos.h>

class Autoprodaja{
 private:
     char model_auta[50];
     float cijena_auta;
     int godiste_auta;
     long int br_sasije;
     float kilometraza;
     bool ostecenje;
     std::string stepen_ostecenja;
 public:
    void unos_Auta();
    void prikaz_Auta();
    long int DajBrojSasije(){
    return br_sasije;
    }
};
void Autoprodaja::unos_Auta(){
 std::cout<<"Unesi model auta: "<<std::endl;
 std::cin>>model_auta;
 std::cout<<"Unesi broj sasije auta: "<<std::endl;
 std::cin>>br_sasije;
 std::cout<<"Kolika je cijena vašeg vozila? "<<std::endl;
 std::cin>>cijena_auta;
 std::cout<<"Koje je godište automobil? "<<std::endl;
 std::cin>>godiste_auta;
 std::cout<<"Kolika je kilometraža vozila? "<<std::endl;
 std::cin>>kilometraza;
 std::cout<<"Da li je vozilo osteceno? (odgovor sa Da:1 ili Ne:0): ";
 std::cin>>ostecenje;
 std::cout<<std::endl;
 if(ostecenje){
    std::cout<<"Na kojim djelovima je auto osteceno? ";
    std::cin.ignore();
    std::getline(std::cin, stepen_ostecenja);
    std::cout<<std::endl;
 }

 std::cout<<"-----------------------"<<std::endl;
}
void Autoprodaja::prikaz_Auta(){
std::cout<<"Model auta: "<<model_auta<<std::endl;
std::cout<<"Broj šasije: "<<br_sasije<<std::endl;
std::cout<<"Cijena auta: "<<cijena_auta<<std::endl;
std::cout<<"Godište auta: "<<godiste_auta<<std::endl;
std::cout<<"Kilometraža auta: "<<kilometraza<<std::endl;
std::cout<<"Ostecenje: "<<(ostecenje ? "Da":"Ne")<<std::endl;
if(ostecenje){
    std::cout<<"Auto je ostecen na: "<<stepen_ostecenja<<std::endl;
}



}

//using namespace std;

int main()
{
    std::cin.clear();
    //for(int i=0;i<10;i++){
       // std::cout<<"-"<<std::endl;
    //}
    std::cout<<"DOBRO DOSLI U AUTOPRODAJNI SISTEM"<<std::endl;
    std::cin.clear();
    std::ofstream prva;
    Autoprodaja a;
    int n, a1;
    char a2;
    prva.open("auto.dat", std::ios::out|std::ios::binary);
    std::cout<<"Koliko zelite pohraniti podataka? "<<std::endl;
    std::cin>>n;
    for(int i=0;i<n;i++){
        a.unos_Auta();
        prva.write((char*)&a,sizeof(a));
    }
    prva.close();
    do{
        std::cin.clear();
        std::cout<<std::endl;
        std::cout<<"Opcija 1: Dodaj"<<std::endl;
         std::cout<<"Opcija 2: Prepravi"<<std::endl;
          std::cout<<"Opcija 3: Pretrazi"<<std::endl;
           std::cout<<"Opcija 4: Obriši"<<std::endl;
            std::cout<<"Opcija 5: Prikaži"<<std::endl;
             std::cout<<"Opcija 6: Izaði"<<std::endl;
             std::cout<<"Odaberi opciju po brojevima: " <<std::endl;
             std::cin>>a1;
             switch(a1){
         case 1:
            {
                prva.open("auto.dat", std::ios::app| std::ios::binary);
                a.unos_Auta();
                prva.write((char*)&a, sizeof(a));
                prva.close();
                break;
            }
         case 2:
            {
                std::ofstream druga;
                druga.open("auto.dat", std::ios::out|std::ios::ate|std::ios::binary);
                int n1;
                std::cout<<"Unesi podatke koji moraju biti izmijenjeni: ";
                std::cin>>n1;
                int pomak=(n1-1)*sizeof(a);
                druga.seekp(pomak,std::ios::beg); //ios::beg sam morao staviti da mi racuna pomak od pocetka datoteke
                a.unos_Auta();
                druga.write((char*)&a, sizeof(a));
                druga.close();
                break;
            }
         case 3:
            {
                std::ifstream treca;
                bool provjera=false;
                treca.open("auto.dat", std::ios::in|std::ios::binary);
                treca.seekg(0,std::ios::beg);
                long int broj;
                std::cout<<"Unesi broj šasije auta: ";
                std::cin>>broj;
                while(treca.read((char*)&a,sizeof(a))){
                    if(a.DajBrojSasije()==broj){
                        a.prikaz_Auta();
                        provjera=true;
                    }
                }
                if(provjera==false){
                    std::cout<<"Broj šasije ne postoji!"<<std::endl;
                }
                treca.close();
                break;
                }
         case 4:
            {
                std::ofstream cetvrta1;
                std::ifstream cetvrta2;
                long int broj;
                cetvrta2.open("auto.dat", std::ios::in| std::ios::binary);
                cetvrta1.open("novoauto.dat", std::ios::out|std::ios::app|std::ios::binary);
                cetvrta2.seekg(0, std::ios::beg);
                std::cout<<"Unesi broj šasije auta: ";
                std::cin>>broj;
                while(cetvrta2.read((char*)&a,sizeof(a))){
                    if(broj!=a.DajBrojSasije()){
                        cetvrta1.write((char*)&a,sizeof(a));
                    }
                    std::remove("auto.dat");
                    std::rename("novoauto.dat","auto.dat");
                    cetvrta1.close();
                    cetvrta2.close();
                    break;
                }
            }
         case 5:
            {
                std::ifstream peta;
                peta.open("auto.dat",std::ios::in|std::ios::binary);
                peta.seekg(0,std::ios::beg);
                while(peta.read((char*)&a,sizeof(a)))
                    a.prikaz_Auta();
                peta.close();
                break;
            }
         case 6:
            {
                std::cin.clear();
                std::cout<<"      Hvala što se koristili Autoprodajni sistem"<<std::endl;
                break;
            }

            }
    }while(a1=='Y' ||a1=='y');
    //cout << "Hello world!" << endl;
    return 0;
}
