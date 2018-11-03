#ifndef KURSSIKIRJANPITO_H
#define KURSSIKIRJANPITO_H

struct opiskelija {
      int opnro;
      char *etunimi;
      char *sukunimi;
      int pisteet[6];
      int pisteet_yhteensa;
 };

int lisaa_opiskelija(struct opiskelija *db, char *str1, char *str2, char *str3);

int tulosta_opiskelijat(struct opiskelija *db);

int paivita_pisteet(struct opiskelija *db, char *str1, char *str2, char *str3);

int lataa_tulokset(struct opiskelija *db, char *str1);

int tallenna_tulokset(struct opiskelija *db, char *str1);

int vapauta_muisti(struct opiskelija *db);


#endif /* KURSSIKIRJANPITO_H */
