
# TEMA 2

**Cerințe globale și obligatorii**

•	Alocare dinamică a memoriei;
•	Separarea declarației unei clase de implementarea acesteia;
•	Crearea de constructori (folosind lista de inițializare) și destructori;
•	Utilizare supraîncărcării operatorilor, unde este cazul;
•	Indentarea și comentarea adecvată a codului;
•	Utilizarea unei convenții de denumire a variabilelor, metodelor și claselor, cu specificarea acesteia;
•	Utilizarea variabilelor și metodelor *const*, unde este cazul;
•	Utilizarea claselor abstracte și metodelor virtuale în rezolvarea cerinței;
•	Tema  trebuie  să  compileze  fără  a  utiliza  anumite  flag-uri  de  compilare (cu  excepția  cazurilor în  care  pentru  compilare  este  necesară  o  anumită versiune de C++) și să respecte standardele C++ pentru sintaxă;
•	Pentru punctaj maxim nu trebuie să se foleseacă verificări de tipuri.  Pentru a genstiona mai multe tipuri de date în acelasi bloc de instrucțiuni se vor folosi clase abstracte și metode virtuale;
•	Strategia folosită pentru mutarea agentilor trebuie să fie deterministă;
Tipurile de agenți trebuie să difere cel puțin prin funcționalitățile oferite de suprascrierea metodelor virtuale;

## SURVIVAL GAME

Avem o hartă pe care sunt distribuiți o serie de agenți.  Fiecare agent își poate modifica  poziția  pe  hartă.   Dacă  poziția  nou  aleasă  este  deja  ocupată,  atunci va  exista  o  confruntare  și  unul  dintre  agenți  va  fi  eliminat.    Fiecare  poziție neocupată pe hartă poate conține un item care conferă avantaje agentului care îl găsește.  Aceste acțiuni pot fi efectuate până când pe hartă rămâne un singur agent.  Cerințe:

•	Creare a minim 3 tipuri de agenți;
•	Creare de itemi care să ofere agenților diverse capabilități;
•	Crearea unei hărți de minim 15 x 15;
•	Distribuirea a cel puțin 7 agenți de fiecare tip;
•	Creare unei clase care sa gestioneze harta și desfășurarea unei runde;
•	Crearea  unei  modalități  de  a  alege  simularea  succesivă  a  rundelor  sau oprirea simulării la stadiul curent, cu afișarea configurației hărții la sfârșitul unei runde simulate;
•	Afișarea detaliilor despre ce modificări au avut loc asupra hărții;

