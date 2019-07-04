# TEMA 3

**Cerințe globale și obligatorii**

•	Alocare dinamică a memorie;
•	Indentare și comentarea adecvată a codului;
•	Utilizarea unei convenții de denumire a variabilelor, metodelor și claselor, cu specificarea acesteia;
•	Este interzisă folosirea STL-urilor dacă, prin folosirea lor, rezolvarea devine trivială;
•	Utilizarea variabilelor și metodelor *const* unde este cazul;
•	Utilizarea excepțiilor pentru tratarea situaților neprevăzute;
•	Utilizarea *assert* pentru testarea funcționalităților;
•	Tema  trebuie  să  compileze  fără  a  utiliza  anumite  flag-uri  de  compilare (cu  excepția  cazurilor în  care  pentru  compilare  este  necesară  o  anumită versiune de C++) și să respecte standardele C++ pentru sintaxă;

## DICTIONAR

**Dictionary <class K, class V>**

Implementați  o  clasă  pentru  un  dicționar  (perechi  cheie  valoare  salvate  ca arbori AVL sau arbori roșu-negru).  Clasa trebuie să ofere:
•	constructor fără parametrii care inițializează un dicționar gol;
•	constructor de copiere și operatorul de atribuire;
•	metodă  de  adăugare  a  unei  perechi  noi  cheie  valoare  (dacă  se  adaugă  o cheie care există deja în dicționar, se va suprascrie vechea valoare);
•	metodă pentru ștergerea unei perechi din dicționar (după cheie);
•	metodă de căutare după cheie;
•	metodă ce elimină toate elementele din dicționar;
•	supraîncărcarea  operatorului  []  pentru  obținerea  valorii  salvate  pentru  o anumită cheie;
