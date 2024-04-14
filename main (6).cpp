// TP 2022/2023: Zadaća 2, Zadatak 4
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

template <typename Tip> Tip proizvod(const std::vector<Tip> &v) {
  /*if(v.empty()){
      return Tip{};
  }*/
  Tip Proizvod = v.at(0);
  for (size_t i = 1; i < v.size(); i++) {
    Proizvod *= v.at(i);
  }
  return Proizvod;
}
template <typename Tip>
bool kriterij(const std::vector<Tip> &v1, const std::vector<Tip> &v2) {

  Tip proizvod1 = proizvod(v1);
  Tip proizvod2 = proizvod(v2);
  if (proizvod1 < proizvod2) {
    return true;
  } else if (proizvod1 > proizvod2) {
    return false;
  } else {
    return v1 < v2;
  }
}
template <typename Tip>
void SortirajPoProizvoduRedova(std::vector<std::vector<Tip>> &mat) {

  // std::sort(red.begin(), red.end()); //sortiranje trenutnog reeda

  std::sort(mat.begin(), mat.end(),
            kriterij<Tip>); // sortianje matrice po prvoj koloni
}

/*for(auto& red:mat){
    red.erase(red.begin());
}*/

int main() {
  std::vector<std::vector<int>> matrica;
  // while(true){
  std::cout
      << "Unesi elemente (* za kraj reda, * na pocetku reda za kraj unosa): "
      << std::endl;
      int unos=0;
  for(;;) {
    std::vector<int> red;
    for(;;){
        std::cin>>unos;
        if(!std::cin){
            std::cin.clear();
            std::cin.ignore(10000,'\n');
            break;
        }
 
    red.push_back(unos);
    }
   
    if(red.empty())
    break;
    /*std::cin.ignore(10000, '\n');
    std::string krajr;
    std::cin >> krajr;*/
    matrica.push_back(red);
    
  }

  SortirajPoProizvoduRedova(matrica);
  std::cout << "Matrica nakon sortiranja: " << std::endl;
  for (size_t i = 0; i < matrica.size(); i++) {
    for (const auto &elementi : matrica.at(i)) {
      std::cout << elementi << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "\nUnesite elemente sekvence koja se trazi (* za kraj reda): "
            << std::endl;
  std::vector<int> sekvenca;
  int broj;
  while (std::cin >> broj) {
    sekvenca.push_back(broj);
  }
  std::cin.clear();
  std::cin.ignore(10000, '\n');
  std::string kraj;
  std::getline(std::cin, kraj);
  auto iterator =
      std::lower_bound(matrica.begin(), matrica.end(), sekvenca, kriterij<int>);

  if (iterator != matrica.end() && *iterator == sekvenca) {
    std::cout << "Trazena sekvenca se nalazi u " << iterator - matrica.begin()+1
              << ". redu (nakon sortiranja)" << std::endl;
  } else {
    std::cout << "Trazena sekvenca se ne nalazi u matrici" << std::endl;
  }

  return 0;
}
