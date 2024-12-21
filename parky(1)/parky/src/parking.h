#ifndef PARKING_H_INCLUDED
#define PARKING_H_INCLUDED

// définition de la structure parking


typedef struct {
int day;
int month;
int year;
}Date;

typedef struct {
    char id_parking[20];
    char location[100];
    int totalSpaces;
    int availableSpaces;
    float price;
    int state;
    char state_text[20];
    Date openingDate;
    int spforCars;
    int spforMotorcycles;
    int spforTrucks;
    char types[100];

} Parking;

typedef struct {
    char id_agent[20];
    char last_name[20];
    char first_name[20];
    char address[50];
   
}Agent;


// Déclaration des fonctions

 int ajouter(char *filename, Parking p);
 int afficher(char *filename);
 int modifier(char *filename, char *id_parking, Parking nouv);
 int supprimer(char *filename, char *id_parking);
 Parking chercher(char *filename, char* id_parking);
 int affecter(char *filename, char *parkingId, Agent agent);

 #endif // PARKING_H_INCLUDED


