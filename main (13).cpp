//TP 2022/2023: Zadaća 4, Zadatak 4
#include <iostream>
#include <cmath>
#include <string>
#include <map>
#include <stdexcept>
#include <memory>
class Korisnik{
    private:
    int cl_broj;
    std::string ime_prezime;
    std::string adresa;
    std::string brtelef;
    public:
    Korisnik(int broj,  std::string ime_prezime,  std::string adres, std::string brojtel): cl_broj(broj), ime_prezime(ime_prezime), adresa(adres), brtelef(brojtel){}
    int DajClanskiBroj() const{
        return cl_broj;
    }
    std::string DajImeIPrezime() const{
        return ime_prezime;
    }
    std::string DajAdresu() const {
        return adresa;
    }
    std::string DajTelefon() const{
        return brtelef;
    }
    void Ispisi() const{
        std::cout<<"Clanski broj: "<<cl_broj<<std::endl;
        std::cout<<"Ime i prezime: "<<ime_prezime<<std::endl;
        std::cout<<"Adresa: "<<adresa<<std::endl;
        std::cout<<"Telefon: "<<brtelef<<std::endl;

    }
};
class Film{
    private:
    int evidencijski_br;
    bool nadvd;
    std::string ime_filma;
    std::string zanr;
    int god_produkcije;
    Korisnik* zaduzen;
    public:
    Film(int broj, bool dvd,  std::string ime,  std::string zanrf, int godina):evidencijski_br(broj), nadvd(dvd), ime_filma(ime), zanr(zanrf), god_produkcije(godina), zaduzen(nullptr){}
    int DajEvidencijskiBroj() const{
        return evidencijski_br;
    }
    std::string DajNaziv() const{
        return ime_filma;
    }
    std::string DajZanr() const{
        return zanr;
    }
    int DajGodinuProdukcije() const{
        return god_produkcije;
    }
    bool DaLiJeDVD() const{
        return nadvd;
    }
    void ZaduziFilm(Korisnik& korisnik){
        zaduzen=&korisnik;
    }
    void RazduziFilm(){
        zaduzen=nullptr;
    }
    bool DaLiJeZaduzen() const{
        return zaduzen!=nullptr;
    }
    Korisnik &DajKodKogaJe() const{
        if(!DaLiJeZaduzen()){
            throw std::domain_error("Film nije zaduzen");
        }
        return *zaduzen;
    }
    Korisnik &DajPokKodKogaJe() const{
        return *zaduzen;
    }
    void Ispisi() const{
        std::cout<<"Evidencijski broj: "<<evidencijski_br<<std::endl;
        std::cout<<"Medij: "<<(nadvd? "DVD":"Video traka")<<std::endl;
        std::cout<<"Naziv filma: "<<ime_filma<<std::endl;
        std::cout<<"Zanr: "<<zanr<<std::endl;
        std::cout<<"Godina produkcije: "<<god_produkcije<<std::endl;
        //if(DaLiJeZaduzen()){
          //  std::cout<<"Zaduzen za: "<<zaduzen->DajImeIPrezime()<<std::endl;
      //  }
        //std::cout<<std::endl;
    }
};
class Videoteka{
    private:
    std::map<int,std::shared_ptr<Korisnik>>korisnici;
    std::map<int, std::shared_ptr<Film>>filmovi;
    public:
   // Videoteka()=default;
   Videoteka(){}
    Videoteka(const Videoteka& broj){
        for(const auto& t:broj.korisnici){
            korisnici[t.first]=std::make_shared<Korisnik>(*t.second);
        }
        for(const auto& t:broj.filmovi){
            filmovi[t.first]=std::make_shared<Film>(*t.second);
            if(t.second->DaLiJeZaduzen()){
                int cl_broj=0;
                for(const auto &korisnik:korisnici){
                    //if(t.second->DajKodKogaJe()==korisnik.second.get()){
                        cl_broj=korisnik.first;
                        //break;
                    //}
                }
                filmovi[t.first]->ZaduziFilm(*korisnici[cl_broj].get());
            }
        }
    }
   // Videoteka(Videoteka&& broj):korisnici(broj.korisnici), filmovi(broj.filmovi){}
    Videoteka operator=(const Videoteka& broj){
        if(this!=&broj){
            korisnici.clear();
            filmovi.clear();
            for(const auto& t:broj.korisnici){
                korisnici[t.first]=std::make_shared<Korisnik>(*t.second);
            }
            for(const auto& t:broj.filmovi){
                filmovi[t.first]=std::make_shared<Film>(*t.second);
                if(t.second->DaLiJeZaduzen()){
                    int cl_broj=0;
                for(const auto &korisnik:korisnici){
                   // if(t.second->DajKodKogaJe()==korisnik.second.get()){
                        cl_broj=korisnik.first;
                       break;
                    //}
                }
                filmovi[t.first]->ZaduziFilm(*korisnici[cl_broj]);
                }
            }
        }
        return *this;
    }
    Videoteka operator=(Videoteka&& broj){
        if(this!=&broj){
            std::swap(korisnici,broj.korisnici);
            std::swap(filmovi,broj.filmovi);
        }
        return *this;
    }
    void RegistrirajNovogKorisnika(int broj, const std::string& ime_prezime, const std::string& adres, const std::string& brtelefona){
        auto rez=korisnici.find(broj);
        if(rez!=korisnici.end()){
            throw std::logic_error("Vec postoji korisnik s tim clanskim brojem");
        }else{
            korisnici[broj]=std::make_shared<Korisnik>(Korisnik{broj,ime_prezime, adres, brtelefona});
        }
    }
    void RegistrirajNoviFilm(int broj, bool dvd, const std::string &ime, const std::string& zanr, int godina){
        auto rez=filmovi.find(broj);
        if(rez!=filmovi.end()){
            throw std::logic_error("Film s tim evidencijskim brojem vec postoji");
        }else{
            filmovi[broj]=std::make_shared<Film>(Film{broj,dvd,ime,zanr,godina});
        
        }
    }
    Korisnik &NadjiKorisnika(int cl_broj){
        auto rez=korisnici.find(cl_broj);
        if(rez==korisnici.end()){
            throw std::logic_error("Korisnik nije nadjen");
        }
        return *(rez->second);
    }
    Film &NadjiFilm(int evidencijski_br){
        auto rez=filmovi.find(evidencijski_br);
        if(rez==filmovi.end()){
            throw std::logic_error("Film nije nadjen");
        }
        return *(rez->second);
    }
    void IzlistajKorisnike() const{
        for(const auto& t:korisnici){
            if(t.second){
            t.second->Ispisi();
            std::cout<<std::endl;
        }
        }
    }
    void IzlistajFilmove() const{
        for(const auto& t:filmovi){
            
            t.second->Ispisi();
            //std::cout<<std::endl;
            if(t.second->DaLiJeZaduzen()){
                std::cout<<"Zaduzen kod korisnika: "<<t.second->DajKodKogaJe().DajImeIPrezime()<<" ("<<t.second->DajKodKogaJe().DajClanskiBroj()<<")"<<std::endl;
                
            }
            std::cout<<std::endl;
        }
        
    }
    void ZaduziFilm(int evidencijski_br, int cl_broj){
        auto film=filmovi.find(evidencijski_br);
        auto korisnik1=korisnici.find(cl_broj);
        if(film==filmovi.end()){
            throw std::logic_error("Film nije nadjen");
        }
        if(korisnik1==korisnici.end()){
            throw std::logic_error("Korisnik nije pronadjen");
        }
        if(film->second->DaLiJeZaduzen()){
            throw std::logic_error("Film vec zaduzen");
        }
    
        film->second->ZaduziFilm(*(korisnik1->second));
    }
    void RazduziFilm(int evidencijski_br){
        auto film=filmovi.find(evidencijski_br);
        if(film==filmovi.end()){
            throw std::logic_error("Film nije nadjen");
        }
        if(!film->second->DaLiJeZaduzen()){
            throw std::logic_error("Film vec zaduzen");
        }
         film->second->RazduziFilm();
        
    }
    void PrikaziZaduzenja(int cl_broj) const {
        auto korisnik1=korisnici.find(cl_broj);
        if(korisnik1==korisnici.end()){
            throw std::logic_error("Korisnik nije nadjen");
        }
        
        bool zaduzenje=false;
        for(const auto& t:filmovi){
            if(t.second->DaLiJeZaduzen() && t.second->DajKodKogaJe().DajClanskiBroj()==cl_broj){
                t.second->Ispisi();
                std::cout<<std::endl;
                zaduzenje=true;
            }
        }
        if(!zaduzenje){
            std::cout<<"Korisnik nema zaduzenja";
        }
    }
    
};

int main ()
{
    



	return 0;
}
