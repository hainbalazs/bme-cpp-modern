#include <iostream>


int main(){
///      Ha egyetlen egy mondatban kell megfogalmaznod, hogy mi a közük C-ben a pointereknek a tömbökhöz, mi lesz az az egy mondat?

/* A tömb valójában a tömböt alkotó elemkre mutató pointerek halmaza / egymásutánja */

///      Hány bájtos egy referencia?    ///

/*mivel egy referencia csak egy álnévként (alias) szolgál,
a memóriában nem kell neki külön helyet foglalni, hiszen bármi módosítás történik
az az eredeti referált típuson is végben megy
--> 0 bájtos, nyilván valahol kell tárolni egy összerendelést típus - referencia közt*/

int a = 5;
int & ref = a;
std::cout << (sizeof(int&) == sizeof(int)) << std::endl; //  <-- megadja az adott típus méretét
std::cout << (&ref == &a);

///      Létezik-e referenciák tömbje? Vajon miért?     ///
/*Nem létezik, mert ..*/
int& arr[] = new int[]; // <-- array of reference is not allowed

/*.. ha igaz amit mondtam, hogy 0 bájtos egy referencia, akkor nyilvánvalóan nem létezik
n*0 bájtos lenne a tömb, legkisebb indexelhető egység 1 bájtosával történne.., ha nem ->
akkor láthatjuk, hogy a referencia ugyanazon a memória címen "helyezkedik el" mint a referált típus,
így nyilván nem lehetne 2x leképezni a memóriába, mivel a tömb elemei arr -pointertől kezdve 
sorfolytonosan leképezi az elemeit a memóriára.

amúgy ha létezne, nem lenne semmilyen használati jelentőssége
*/

    return 0;
}