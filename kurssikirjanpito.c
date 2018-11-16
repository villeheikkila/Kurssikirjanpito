#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kurssikirjanpito.h"

// Määritetään globaali muuttuja, joka pitää kirjaa opiskelijoiden määrästä.
int op = 0;

int lisaa_opiskelija(struct opiskelija *db, char *str1, char *str2, char *str3) {
      int opnro;
      char sukunimi, etunimi;
      sscanf(str1, "%d", &opnro);
      sscanf(str2, "%s", &sukunimi);
      sscanf(str3, "%s", &etunimi);
      if (strlen(str1) > 6) {
            printf("Virhe! Opiskelijanumero on liian pitka!\n");
      }
      else if (strlen(str2) > 20 || strlen(str3) > 20) {
            printf("Virhe! Nimi on liian pitka!\n");
      }
      else {
            db[op].opnro = opnro;
            db[op].etunimi = malloc(sizeof(char)*strlen(str3) + 1);       // Varataan muisti etunimelle.
            db[op].sukunimi = malloc(sizeof(char)*strlen(str1) + 1);      // Varataan muisti sukunimelle.
            strcpy(db[op].etunimi, etunimi);
            strcpy(db[op].sukunimi, sukunimi);
            db[op].pisteet_yhteensa = 0;
            for (int a = 0; a < 6; a++){
                  db[op].pisteet[a] = 0;
            }
            printf("Opiskelija %s %s lisatty onnistuneesti!\n", db[op].sukunimi, db[op].etunimi);
            op++;
    }
    return 0;
 }


 int tulosta_opiskelijat(struct opiskelija *db) {
      // Järjestetään opiskelijat kokonaispistemäärän mukaan.
      int *list = malloc(op * sizeof(int));
      for (int i = 0; i < op; i++) {
            list[i] = db[i].pisteet_yhteensa;
      }
      for (int i = 0; i < op; i++) {
            for (int j = 0; j < op; j++) {
          	       if (list[j] < list[i]) {
          				       int muisti = list[i];
          			         list[i] = list[j];
          				       list[j] = muisti;
          			   }
            }
      }
      // Tulostetaan opisjelijat oikeassa järjestyksessä.
      for (int i = 0; i < op; i++) {
            for (int j = 0; j < op; j++) {
                  if (list[i] == db[j].pisteet_yhteensa) {
                        printf("Opiskelijanumero: %d Nimi: %s %s Yhteensa: %d Kierrokset: ", db[j].opnro, db[j].sukunimi, db[j].etunimi, db[j].pisteet_yhteensa);
                        for (int k = 0; k < 6; k++){
                              printf("%d ", db[j].pisteet[k]);
                        }
                  printf("\n");
                  }
            }
      }
      free(list);
      return 0;
 }

int paivita_pisteet(struct opiskelija *db, char *str1, char *str2, char *str3) {
      int opnro, kierros, pisteet, yhteensa;
      int indeksi = 0;
      int listassa = 0;
      // Muunnetaan komennot oikean tyyppisiksi.
      sscanf(str1, "%d", &opnro);
      sscanf(str2, "%d", &kierros);
      sscanf(str3, "%d", &pisteet);
      // Lisätään pisteet oikealle opiskelijalle. Tallennetaan opiskelijan indeksi muuttujaan "a".
      while (indeksi < op) {
            if (db[indeksi].opnro == opnro) {
                  db[indeksi].pisteet[kierros] = pisteet;
                  listassa = 1;
                  break;
            }
            indeksi++;
      }
      // Tarkistetaan löytyikö opiskelijaa listasta.
      if (listassa == 0) {
            printf("Virhe! Opiskelijaa ei ole listassa!\n");
      }
      else {
            // Lasketaan opiskelijan kokonaispistemärä.
            for (int i = 0; i < 6; i++) {
                  yhteensa += db[indeksi].pisteet[i];
            }
            db[indeksi].pisteet_yhteensa = yhteensa;
            printf("Pisteet paivitetty onnistuneesti!\n");
    }
    return 0;
}

int lataa_tulokset(struct opiskelija *db, char *str1) {
      int yhteensa, opnro, p1, p2, p3, p4, p5, p6;
      char sukunimi, etunimi, sijainti;
      sscanf(str1, "%s", &sijainti);
      op = 0; // Nollataan globaali muuttuja.
      // Avataan tiedosto str1 osoittamalla nimellä.
      FILE *f = fopen(sijainti, "r");
      if (f == NULL) {
            printf("Virhe! Tiedosto on tyhja!\n");
      }
      else {
            // Luetaan tiedosto ja päivitetään tiedot tietokantaan.
            char str[100];
            while(fgets(str, 100, f)) {
                  sscanf(str, "%d %s %s %d %d %d %d %d %d %d", &opnro, &sukunimi, &etunimi, &yhteensa, &p1, &p2, &p3, &p4, &p5, &p6);
                  db[op].opnro = opnro;
                  db[op].etunimi = malloc(sizeof(char)*strlen(etunimi) + 1);
                  db[op].sukunimi = malloc(sizeof(char)*strlen(sukunimi) + 1);
                  strcpy(db[op].etunimi, etunimi);
                  strcpy(db[op].sukunimi, sukunimi);
                  db[op].pisteet_yhteensa = yhteensa;
                  db[op].pisteet[0] = p1;
                  db[op].pisteet[1] = p2;
                  db[op].pisteet[2] = p3;
                  db[op].pisteet[3] = p4;
                  db[op].pisteet[4] = p5;
                  db[op].pisteet[5] = p6;
                  op++;
      }
      printf("Tulokset ladattu onnistuneesti tiedostosta: %s\n", sijainti);
    }
    fclose(f);      // Suljetaan tiedosto.
    return 0;
}

int tallenna_tulokset(struct opiskelija *db, char *str1) {
      // Avataan tiedosto str1 osoittamalla nimellä.
      char sijainti;
      sscanf(str1, "%s", &sijainti);
      FILE *f = fopen(sijainti, "w");
      // Järjestetään opiskelijat kokonaispistemäärän mukaan.
      int *list = malloc(op * sizeof(int));
      for (int i = 0; i < op; i++) {
            list[i] = db[i].pisteet_yhteensa;
      }
      for (int i = 0; i < op; i++) {
            for (int j = 0; j < op; j++) {
                  if (list[j] < list[i]) {
                        int muisti = list[i];
                        list[i] = list[j];
                        list[j] = muisti;
                  }
            }
      }
      // Kirjoitetaan tiedostoon oikeassa järjestyksessä.
      for (int i = 0; i < op; i++) {
            for (int j = 0; j < op; j++) {
                  if (db[j].pisteet_yhteensa == list[i]) {
                        fprintf(f, "%d %s %s %d ", db[j].opnro, db[j].sukunimi, db[j].etunimi, db[j].pisteet_yhteensa);
                        for (int k = 0; k < 6; k++){
                              fprintf(f, "%d ", db[j].pisteet[k]);
                        }
                  fprintf(f, "\n");
                  }
            }
      }
      fclose(f);
      free(list);
      printf("Tulokset tallenettiin tiedostoon nimelta: %s!\n", sijainti);
      return 0;
}

int vapauta_muisti(struct opiskelija *db) {
      // Vapautetaan muisti
      if (op != 0) {
            for (int i = 0; i < op; i++) {
                  free(db[i].sukunimi);
                  free(db[i].etunimi);
      }
      free(db);
      }
      return 0;
}

int main() {
      char tehtava, komento[300], str1, str2, str3;      // Varaudutaan pitkiin komentoihin.
      //struct opiskelija *lista = malloc(sizeof(struct opiskelija));     // Varataan muisti listalle opiskelijoista.
      struct opiskelija lista[100];
      while(fgets(komento, 300, stdin) != NULL) {
            sscanf(komento, "%s %s %s %s", &tehtava, &str1, &str2, &str3);      // Pilkotaan komento osiin.
            if (tehtava == 'A') {
                  // OPNRO sukuetunimi etuetunimi : Lisää opiskelija : Lisää opiskelijan tietokantaan. Alkutilassa opiskelijalla on koossa 0 pistettä. Esim: A 234567 Opiskelija Osmo
                  lisaa_opiskelija(lista, str1, str2, str3);
            }
            else if (tehtava == 'U') {
                  // Asettaa annetun opiskelijan (opiskelijanumeroltaan OPNRO) pisteet kierroksella "kierros". Voit olettaa että kierroksia on maksimissaan 6. Pisteet ilmaistaan kokonaislukuna. Mikäli annettua opiskelijaa ei löydy, tulostetaan virheilmoitus.
                  paivita_pisteet(lista, str1, str2, str3);
            }
            else if (tehtava == 'L') {
                  // Tulosta tilanne : Tulostaa tallennetut opiskelijat: opiskelijanumero, sukunimi ja etunimi, kunkin tehtäväkierroksen pisteet, sekä yhteenlasketun kokonaispistemäärän. Opiskelijat tulee listata kokonaispistemäärän mukaisessa järjestyksessä siten, että eniten pisteitä saanut listataan ensin.
                  tulosta_opiskelijat(lista);
            }
            else if (tehtava == 'W') {
                  // Tallenna tulokset : Tallentaa tulokset tiedostoon annetulla tiedostonnimellä
                  tallenna_tulokset(lista, str1);
            }
            else if (tehtava == 'O') {
                  // Lataa tulokset : Lataa tulokset tiedostosta, korvaten muistissa aiemmin olleen tilanteen
                  vapauta_muisti(lista);
                  lataa_tulokset(lista, str1);
            }
            else if (tehtava == 'Q') {
                  // Poistu ohjelmasta: Poistuu ohjelmasta ja vapauttaa kaiken käytetyn muistin. Tämä toiminto on pakko toteuttaa, jotta havaitset mahdolliset muistivuodot.
                  printf("Sovellus suljetaan.\n");
                  break;
            }
       }
      vapauta_muisti(lista);
      exit(0);
 }
