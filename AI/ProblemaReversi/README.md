## Cerința: Jocul “Reversi”  

- Jocul este intre doi jucatori. Unul din ei joaca cu alb, celalalt cu negru (putem considera
  pentru piese simbolurile a si n).
  • Tabla de joc este un grid de dimensiune 8X8. Consideram liniile si coloanele numerotate de la 0 la 7. In centru sunt pozitionate doua piese albe (linia 3 coloana 3 respectiv linia 4 coloana 4) si doua negre (linia 3 coloana 4, respectiv linia 4 coloana 3).
  • Un jucator poate pune o singura piesa (de culoarea cu care a ales sa joace) cand ii vine
  randul, intr-o locatie libera pe tabla.
  • Jucatorul cu piese negre muta primul.
  • Un jucator J poate pozitiona o piesa P1 numai in locatiile care respecta urmatoarea
  conditie: locatia sa fie libera si sa se afle pe aceeasi linie, coloana sau diagonala cu cel putin o alta piesa P2 a jucatorului J, iar toate locatiile dintre cele doua pozitii (pozitia unde J vrea sa plaseze piesa si pozitia piesei existente), pe acea linie, coloana sau diagonala, sa fie ocupate in totalitate de piese adversare. In momentul in care jucatorul J plaseaza piesa, toate piesele dintre P1 si orice alta piesa P2 (pot fi mai multe) care respecta conditia de mai sus capata culoarea lui J (clarificare: piesele adversare isi schimba culoarea numai daca avem doar piese adversare intre piesa noua si piesa existenta; deci fara locatii libere si fara alte piese ale jucatorului J).
  • Daca un jucator nu poate plasa nicio piesa, pierde randul (si jucatorul opus muta mai
  departe)
  • Jocul se termina cand niciun jucator nu mai poate plasa piese (deci se poate termina si
  inainte de se umple gridul).
  • Castiga jucatorul cu cele mai multe piese pe tabla..
  Exemplu de afisare a gridului (puteti alege un alt mod de afisare atat timp cat se poate intelege usor configuratia tablei din afisare). Simbolul # este folosit pentru locatii libere, a si n pentru piesele albe si negre.
- a b c d e f g h
  \---------------
  0 |# # # # # # # #
  1 |# # # # # # # #
  2 |# # # # # # # #
  3 |# # # a n # # #
  4 |# # # n a # # #
  5 |# # # # # # # #
  6 |# # # # # # # #
  7 |# # # # # # # #
- Utilizatorul ar raspunde cu un numar de la 0 la 7 si o litera de la a la h (linia si coloana) pentru fiecare mutare.
  Tabla initiala nu trebuie citita din fisier, deoarece are mereu aceeasi forma.  