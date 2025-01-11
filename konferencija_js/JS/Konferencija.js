
let Konferencija = (function () {
    //privatni atributi modula
    let programLista = [];
    let govorniciLista = [];

    //implementacija metoda
   // let init=function(programLista, govorniciLista){
    
   let init = function (program, govornici) {
        programLista=program;
        govorniciLista=govornici;
    }

    let dodajDan = function (dan, datum, sesije) {
        // dodajte kod
        if(dan==null|| datum==null||sesije==null){
            return "Neispravni parametri!";
        }
        for(let sesija of sesije){
            if(!sesija.vrijeme || !sesija.naziv || !sesija.govornik){
                return "Neispravni parametri!";
            }
        }
        programLista.push({dan, datum, sesije
        });
        return "Uspjesno dodavanje!"
    }

    let filtrirajGovornike = function (ime, prezime) {
        // dodajte kod
        let rezultat=[];
        for(let govornik of govorniciLista){
             if(ime===null && prezime===null){
                rezultat.push(govornik);//ovdje ne filtira sve dodaje
            }else if(ime===null && govornik.prezime===prezime){
                   rezultat.push(govornik);//ako prezime odgovara dodaje
            }else if(prezime===null && govornik.ime===ime){
                rezultat.push(govornik);//ako ime odgovara dodaje
            }else if(govornik.ime===ime && govornik.prezime===prezime){
                rezultat.push(govornik);
            }
        }
        return rezultat; 
    }


    let pretraziProgram = function (kljucnaRijec) {
        // dodajte kod
        let rezultat=[];
        for(let dan of programLista){
            for(let sesija of dan.sesije){
                let naziv=sesija.naziv;
                let nadjeno=1;
                let i;
                for(i=0; i<=naziv.length-kljucnaRijec.length;i++){
                    let prolazi=0;
                    let j;
                    for(j=0;j<kljucnaRijec.length;j++){
                        if(naziv[i+j]!==kljucnaRijec[j]){
                            prolazi=1;
                            break;
                        }
                    }
                  /*  if(!prolazi){
                        prolazi=0;
                        break;
                    }*/
                //}
                if(nadjeno){
                    rezultat.push(sesija);
                    break;
                }
              }
            }
        }
            return rezultat;
        }
    

    let agregirajGovornike = function () {
        // dodajte kod
        let agregacija={};
        let i;
        for(i=0; i<govorniciLista.length;i++){
            let govornik=govorniciLista[i];
            let prezime=govornik.prezime;
            if(agregacija[prezime]){
                agregacija[prezime]++;//poceva za 1 ako postoji
            }else{
                agregacija[prezime]=1;
            }
        }
        return agregacija;
    }


    let generisiIzvjestaj = function () {
        // dodajte kod
        if(programLista.length===0){
            return{
                brojDana: 0, brojSesija:0, brojGovornika:govorniciLista.length,
                
            };
        }
        let ukupnoSesija=0;
        let i;
        for ( i=0; i<programLista.length;i++){
            let dan=programLista[i]; //ukupni broj sesija svaki dan
            ukupnoSesija=ukupnoSesija+dan.sesije.length;
         }
        return {
            brojDana: programLista.length, brojSesija:ukupnoSesija, brojGovornika: govorniciLista.length,
        };
    }

    return {
        init: init,
        dodajDan: dodajDan,
        filtrirajGovornike: filtrirajGovornike,
        pretraziProgram: pretraziProgram,
        agregirajGovornike: agregirajGovornike,
        generisiIzvjestaj: generisiIzvjestaj,
    }
})();
// Pocetni podaci
const programLista = [
    {
        dan: 1,
        datum: "26-12-2024",
        sesije: [
            {
                vrijeme: "09:00",
                naziv: "Otvaranje konferencije",
                govornik: "Dr. John Smith"
            },
            {
                vrijeme: "11:00",
                naziv: "Predavanje o AI",
                govornik: "Dr. Jane Doe"
            },
            {
                vrijeme: "14:00",
                naziv: "Panel diskusija",
                govornik: "Panel eksperti"
            },
        ],
    },
    {
        dan: 2,
        datum: "27-12-2024",
        sesije: [
            {
                vrijeme: "10:00",
                naziv: "Radionica o mašinskom učenju",
                govornik: "Alice Johnson"
            },
            {
                vrijeme: "12:00",
                naziv: "Primjene blockchaina",
                govornik: "Bob Anderson"
            },
        ],
    },
];

const govorniciLista = [
    {
        ime: "John",
        prezime: "Smith",
        biografija: "Ekspert u oblasti tehnologija."
    },
    {
        ime: "Jane",
        prezime: "Doe",
        biografija: "Predavač i istraživač u oblasti AI."
    },
    {
        ime: "Alice",
        prezime: "Johnson",
        biografija: "Autor knjige o mašinskom učenju."
    },
    {
        ime: "Bob",
        prezime: "Anderson",
        biografija: "Ekspert u blockchain tehnologijama."
    },
    {
        ime: "Emily",
        prezime: "White",
        biografija: "Direktorica instituta za inovacije."
    },
];

// Test 1: Inicijalizacija
Konferencija.init(programLista, govorniciLista);
const izvjestaj = Konferencija.generisiIzvjestaj();
console.log("Test 1: Inicijalizacija modula");
console.log("Očekivano: { brojDana: 2, brojSesija: 5, brojGovornika: 5 }");
console.log("Dobiveno:", izvjestaj);

// Test 2: Dodavanje novog dana
const rezultatDodavanja = Konferencija.dodajDan(3, "28-12-2024", [
    { vrijeme: "09:00", naziv: "Završna riječ", govornik: "Dr. Emily White" },
]);
console.log("Test 2: Dodavanje novog dana");
console.log("Očekivano: Uspjesno dodavanje!");
console.log("Dobiveno:", rezultatDodavanja);

// Test 3: Filtriranje govornika po imenu
const filtriraniGovornici = Konferencija.filtrirajGovornike("Jane", null);
console.log("Test 3: Filtriranje govornika po imenu");
console.log("Očekivano: [{ ime: 'Jane', prezime: 'Doe', biografija: 'Predavač i istraživač u oblasti AI.' }]");
console.log("Dobiveno:", filtriraniGovornici);

// Test 4: Pretraga programa po ključnoj riječi
const pretraga = Konferencija.pretraziProgram("Predavanje");
console.log("Test 4: Pretraga programa po ključnoj riječi");
console.log("Očekivano: [{ vrijeme: '11:00', naziv: 'Predavanje o AI', govornik: 'Dr. Jane Doe' }]");
console.log("Dobiveno:", pretraga);

// Test 5: Agregacija govornika
const agregacija = Konferencija.agregirajGovornike();
console.log("Test 5: Agregacija govornika po prezimenima");
console.log("Očekivano: { Smith: 1, Doe: 1, Johnson: 1, Anderson: 1, White: 1 }");
console.log("Dobiveno:", agregacija);

// Test 6: Generisanje izvještaja
const izvjestajNakonDodavanja = Konferencija.generisiIzvjestaj();
console.log("Test 6: Generisanje izvještaja nakon dodavanja dana");
console.log("Očekivano: { brojDana: 3, brojSesija: 6, brojGovornika: 5 }");
console.log("Dobiveno:", izvjestajNakonDodavanja);

