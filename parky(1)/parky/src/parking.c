#include "parking.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



int ajouter(char *filename, Parking p) {
FILE *f = fopen(filename, "a");
if (f != NULL) {
fprintf(f, "%s %s %d %d %f %d %s %d %d %d %d %d %d \n", p.id_parking, p.location, p.totalSpaces, p.availableSpaces, p.price, p.state, p.state_text, p.spforCars, p.spforMotorcycles, p.spforTrucks, p.openingDate.day, p.openingDate.month, p.openingDate.year);
fclose(f);
return 1;
}
else {
 return 0;
}
}
int afficher(char * filename) {
Parking p;
FILE * f=fopen(filename, "r");
if(f!=NULL) {
printf("List of Parkings: \n");
printf("ID | Location | Total spaces | Available spaces | Price |state |Spaces for cars |Spaces for motor cycles | Spaces for trucks |Opening Date \n");
while(fscanf(f, "%s %s %d %d %f %d %s %d %d %d %d %d %d \n", p.id_parking, p.location, &p.totalSpaces, &p.availableSpaces, &p.price, &p.state, p.state_text, &p.spforCars, &p.spforMotorcycles, &p.spforTrucks, &p.openingDate.day, &p.openingDate.month, &p.openingDate.year)!= EOF){
printf("%s %s %d %d %f %d %s %d %d %d %d %d %d \n", p.id_parking, p.location, p.totalSpaces, p.availableSpaces, p.price, p.state, p.state_text, p.spforCars, p.spforMotorcycles, p.spforTrucks, p.openingDate.day, p.openingDate.month, p.openingDate.year);
}
fclose(f);
return 1;
}
else {
printf("Error: Could not open file %s\n", filename);
return 0;
}
}


int modifier(char *filename, char *id_parking, Parking nouv) {
int tr = 0;
Parking p;
FILE * f=fopen(filename, "r");
FILE * f2=fopen("nouv.txt" , "w");
if (f != NULL && f2 != NULL) {
while (fscanf(f, "%s %s %d %d %f %d %s %d %d %d %d %d %d \n", p.id_parking, p.location, &p.totalSpaces, &p.availableSpaces, &p.price, &p.state, p.state_text, &p.spforCars, &p.spforMotorcycles, &p.spforTrucks, &p.openingDate.day, &p.openingDate.month, &p.openingDate.year)!= EOF){
if (strcmp(p.id_parking, id_parking) == 0) {
fprintf(f2, "%s %s %d %d %f %d %s %d %d %d %d %d %d \n", p.id_parking, nouv.location, nouv.totalSpaces, nouv.availableSpaces, nouv.price, nouv.state,nouv.state_text, nouv.spforCars, nouv.spforMotorcycles, nouv.spforTrucks, nouv.openingDate.day, nouv.openingDate.month, nouv.openingDate.year);
tr=1;
}
else {
fprintf(f2, "%s %s %d %d %f %d %s %d %d %d %d %d %d \n", p.id_parking, p.location, p.totalSpaces, p.availableSpaces, p.price, p.state, p.state_text, p.spforCars, p.spforMotorcycles, p.spforTrucks, p.openingDate.day, p.openingDate.month, p.openingDate.year);
}
}
fclose(f);
fclose(f2);
remove(filename);
rename("nouv.txt", filename);
return tr;
} else {
return 0;
}
}


int supprimer(char *filename, char *id_parking) {
int tr=0;
Parking p;
FILE * f=fopen(filename, "r");
FILE * f2=fopen("nouv.txt", "w");
if(f!=NULL && f2!=NULL){
while(fscanf(f, "%s %s %d %d %f %d %s %d %d %d %d %d %d \n", p.id_parking, p.location, &p.totalSpaces, &p.availableSpaces, &p.price, &p.state, p.state_text, &p.spforCars, &p.spforMotorcycles, &p.spforTrucks, &p.openingDate.day, &p.openingDate.month, &p.openingDate.year)!= EOF){
if (strcmp(p.id_parking, id_parking) == 0){
tr =1;
}
else {
fprintf(f2, "%s %s %d %d %.2f %d %s %d %d %d %d %d %d \n", p.id_parking, p.location, p.totalSpaces, p.availableSpaces, p.price, p.state, p.state_text, p.spforCars, p.spforMotorcycles, p.spforTrucks, p.openingDate.day, p.openingDate.month, p.openingDate.year);
}
}
fclose(f);
fclose(f2);
remove(filename);
rename("nouv.txt", filename);
}
return tr;
}


Parking chercher(char * filename, char*id_parking) {
Parking p;
int tr=0;
FILE * f=fopen(filename, "r");
if(f!=NULL) {
while(tr==0 && fscanf(f,"%s %s %d %d %f %d %s %d %d %d %d %d %d \n", p.id_parking, p.location, &p.totalSpaces, &p.availableSpaces, &p.price, &p.state, p.state_text, &p.spforCars, &p.spforMotorcycles, &p.spforTrucks, &p.openingDate.day, &p.openingDate.month, &p.openingDate.year)!= EOF){
if (strcmp(p.id_parking, id_parking) == 0) {
tr=1;
}
}
fclose(f);
}
if(tr==0){
strcpy(p.id_parking, "-1");
}
return p;
}

int affecter(char * filename, char *parkingId, Agent agent) {
Parking p;
int tr=0;
FILE * f=fopen(filename, "r");
FILE * f2=fopen("nouv.txt" , "w");
if(f!=NULL && f2!=NULL){
while(fscanf(f,"%s %s %d %d %f %d %s %d %d %d %d %d %d \n", p.id_parking, p.location, &p.totalSpaces, &p.availableSpaces, &p.price, &p.state, p.state_text, &p.spforCars, &p.spforMotorcycles, &p.spforTrucks, &p.openingDate.day, &p.openingDate.month, &p.openingDate.year)!= EOF){
if (strcmp(p.id_parking, parkingId) == 0) {
tr=1;
fprintf(f2, "%s %s %d %d %f %d %s %d %d %d %d %d %d %s %s %s %s \n", p.id_parking, p.location, p.totalSpaces, p.availableSpaces, p.price, p.state,p.state_text, p.spforCars, p.spforMotorcycles, p.spforTrucks, p.openingDate.day, p.openingDate.month, p.openingDate.year,agent.id_agent, agent.last_name, agent.first_name, agent.address);
}
}
fclose(f);
fclose(f2);
remove(filename);
rename("nouv.txt", filename);
}
return tr;
}








 
 





 
 

