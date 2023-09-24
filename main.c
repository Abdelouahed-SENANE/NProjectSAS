#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// int count = 0;

struct deadline
{
  int j;
  int m;
  int a;
};
// Fontions caculate time 
// convert date to seconds 
long long calcEpoqueTime(int year, int month, int day) {
    struct tm timeStruct;
    timeStruct.tm_year = year - 1900; 
    timeStruct.tm_mon = month - 1; 
    timeStruct.tm_mday = day; 
    timeStruct.tm_hour = 0; 
    timeStruct.tm_min = 0;
    timeStruct.tm_sec = 0; 
    timeStruct.tm_isdst = -1; 

    time_t epochTime = mktime(&timeStruct);

    if (epochTime == -1) {
        printf("Error converting time");
        return -1;
    }

    return (long long)epochTime;
}

// get current time by second 
long long getCurrentEpochTime() {
    time_t currentEpoch;
    time(&currentEpoch);
    return (long long)currentEpoch;
}
// caculate diffrence entre deadline et current time 
long long differenceInjrs(long long deadlineEpoch, long long systemEpoch){
long long differenceInSeconds = deadlineEpoch - systemEpoch;

    return differenceInSeconds / (3600 * 24 );
}
/*-------------------------  Menu --------------------------------*/
void menu()
{
  printf("\n");
  printf("_____________________________________________MENU____________________________________________\n");
  printf("|                                                                                            |\n");
  printf("|\t1 - : Ajouter une nouvelle tache                                                     |\n");
  printf("|\t2 - : Ajouter plusieurs taches                                                       |\n");
  printf("|\t3 - : Afficher la liste de toutes les taches                                         |\n");
  printf("|\t4 - : Modifier une tache                                                             |\n");
  printf("|\t5 - : Supprimer une tache par identifiant                                            |\n");
  printf("|\t6 - : Rechercher les taches                                                          |\n");
  printf("|\t7 - : Statistiques                                                                   |\n");
  printf("|\t0 - : Quitter le programms                                                           |\n");
  printf("|____________________________________________________________________________________________|");
  printf("\n");
}

/*Structure Tache*/
struct tache 
{
  int id;
  char titre[50];
  char desc[50];
  struct deadline time;
  char satut[50];
};

int ajouterTache(struct tache listTaches[], int count)
{
  char titre[50];
  char desc[50];
  char statut[50];
  int j, m, a;
  int lastId = 0;

  for (int i = 0; i < count; i++)
  {
    if (lastId < listTaches[i].id)
    {
      lastId = listTaches[i].id;
    }
    
  }
  

  int id = lastId; // Use the current count as the task ID
  printf("Titre %i : ", id + 1);
  scanf(" %49[^\n]", titre);
  printf("\n");
  printf("Description %i : ", id + 1);
  scanf(" %49[^\n]", desc);
  printf("\n");
  printf("Jour  : ");
  scanf("%i", &j);
  while (j > 31 || j == 0)
  {
    printf("Veuillez saisir un jour inferieure ou egale a 31 et superieure a 0\n");
    printf("Jour : ");
    scanf("%i", &j);
  }
  printf("Mois  : ");
  scanf("%i", &m);
  while (m > 12 || m == 0)
  {
    printf("Veuillez saisir un mois inferieure a 12 et superieure a 0\n");
    printf("Mois  : ");
    scanf("%i", &m);
  }
  printf("donner l'annee  : ");
  scanf("%i", &a);
  while (a < 2023)
  {
    printf("le programms accept une date a partir de l'annee 2023 \n");
    printf("L'annee : ");
    scanf("%i", &a);
  }
  printf("Statut %i (C'est dire etat de la tache {To Do} , { Doing } , {Done})  : ", id + 1);
  scanf(" %49[^\n]", statut);

  while (strcmp(statut , "To Do") != 0 && strcmp(statut , "Doing") != 0 &&  strcmp(statut , "Done") != 0)
  {
    printf("Veuillez saisir l'etat correct de la tache : ");
    scanf(" %49[^\n]", statut);
  }
  


  listTaches[count].id = id + 1;
  strcpy(listTaches[count].titre, titre);
  strcpy(listTaches[count].desc, desc);
  listTaches[count].time.j= j;
  listTaches[count].time.m = m;
  listTaches[count].time.a = a;
  strcpy(listTaches[count].satut, statut);


  return count + 1;
}

/*Ajouter plusieurs tache*/
int ajouterTaches(struct tache listTaches[], int count)
{
  int size;

  printf("Ajouter les nombre des taches tu veux remplir : ");
  scanf("%i", &size);

  for (int i = 0; i < size; i++)
  {
    count = ajouterTache(listTaches, count);
  }
  return count;
}
//Afficher les taches
  void afficherListTache (struct tache listTaches[], int count) {
    if (count == 0)
  {
    printf("La liste des taches est vide.\n");
    return;
  }
  printf("\n_____________________________Liste des taches_____________________________\n");
  for (int i = 0; i < count; i++)
  {

    printf("\n");
    printf("+______________________________ Taches %i ______________________________ +\n", listTaches[i].id);
    printf("|                                                                       \n");
    printf("|      ID  : %i                                                          \n",listTaches[i].id);
    printf("|      Titre : %s                                                     \n",listTaches[i].titre);
    printf("|      Description : %s                                             \n",listTaches[i].desc);
    printf("|      Deadline : %i-%i-%i                                               \n",listTaches[i].time.j,listTaches[i].time.m,listTaches[i].time.a);
    printf("|      Statut : %s                                                    \n",listTaches[i].satut);
    printf("+_______________________________________________________________________+\n");

  }
  printf("\n_________________________________________________________________________\n\n");

  }

// sous menu afficher 
int sous_menuAfficher() {
    int choix;

    printf("+____________________________________ TRI par ___________________________________________+\n");
    printf("|                                                                                        |\n");
    printf("|   1 - Trier les taches par ordre alphabetique.                                         |\n");
    printf("|   2 - Trier les taches par deadline.                                                   |\n");
    printf("|   3 - Afficher les taches dont le deadline est dans 3 jours ou moins.                  |\n");
    printf("|   0 - Retour.                                                                          |\n");
    printf("+________________________________________________________________________________________+\n");

    printf("Choisissez une option : ");
    scanf("%d", &choix);

    return choix;
}
/*Afficher une les taches*/
int afficherTaches(struct tache listTaches[], int count)
{


  int choix = sous_menuAfficher();
  while (choix == 0)
  {
    break;
  }
  switch (choix)
  {
      //Tri par order alphabetique
      case 1:
        struct tache swip;
      for (int i = 0; i < count - 1; i++)
      {
        for (int j = i + 1; j < count ; j++)
        {
          if (strcmp(listTaches[i].titre, listTaches[j].titre) > 0)
          {
            swip = listTaches[i];
            listTaches[i] = listTaches[j];
            listTaches[j] = swip;
          }
          
        }
      }
      printf("\n\n");
      printf("La liste apres le TRI Alphabetique : \n");
      afficherListTache(listTaches , count);
      break;


      //Tri par Deadline 
      case 2:
      struct tache swip1;
      for (int i = 0; i < count - 1; i++)
      {
        for (int j = i + 1; j < count; j++)
        {
          if (listTaches[i].time.a > listTaches[j].time.a )
          {
            swip = listTaches[i];
            listTaches[i] = listTaches[j];
            listTaches[j] = swip;
          }else if (listTaches[i].time.a == listTaches[j].time.a) {
            if (  listTaches[i].time.m > listTaches[j].time.m )
            {
              swip = listTaches[i];
              listTaches[i] = listTaches[j];
              listTaches[j] = swip;
            }else if (listTaches[i].time.m == listTaches[j].time.m) {
                if (  listTaches[i].time.j > listTaches[j].time.j )
            {
              swip = listTaches[i];
              listTaches[i] = listTaches[j];
              listTaches[j] = swip;
            }
            
          }

          }
          
        }
        
      }  
  break;
  case 3:
  long long currentTime =  getCurrentEpochTime(); 
  for (int i = 0; i < count; i++)
  {
    long long saveCaculateDeadline = calcEpoqueTime(listTaches[i].time.a, listTaches[i].time.m, listTaches[i].time.j);
    long long JoursRestTache = differenceInjrs(saveCaculateDeadline, currentTime);
    if (JoursRestTache <= 3)
    {
    printf("\n");
    printf("+______________________________ Taches %i ______________________________ +\n", listTaches[i].id);
    printf("|                                                                       \n");
    printf("|      ID  : %i                                                          \n",listTaches[i].id);
    printf("|      Titre : %s                                                     \n",listTaches[i].titre);
    printf("|      Description : %s                                             \n",listTaches[i].desc);
    printf("|      Deadline : %i-%i-%i                                               \n",listTaches[i].time.j,listTaches[i].time.m,listTaches[i].time.a);
    printf("|      Statut : %s                                                    \n",listTaches[i].satut);
    printf("+_______________________________________________________________________+\n");
    }
    
  }
  break;


  }
}
/*fonction retourne indice by ID*/
int indexById(int id, struct tache listTaches[], int count)
{

  for (int i = 0; i < count; i++)
  {
    if (listTaches[i].id == id)
    {
      return i;
    }
  }
  return -1;
}
/*fonction retourne  indice by titre*/
int indiceTitre(char titre[50], struct tache listTaches[], int count)
{

  for (int i = 0; i < count; i++)
  {
    int result = strcmp(titre, listTaches[i].titre);
    if (result == 0)
    {
      return i;
    }
  }
  return -1;
}
/*Sous menu Recherche*/
int sous_menuRecherche() {

    printf("+____________________________________ Rechercher par ___________________________________________+\n");
    printf("|                                                                                               |\n");
    printf("|   1 - Rechercher une tache par son Identifiant.                                               |\n");
    printf("|   2 - Rechercher une tache par son Titre.                                                     |\n");
    printf("|   0 - Retour.                                                                                 |\n");
    printf("+_______________________________________________________________________________________________+\n");
    int choix;
    printf("Modifier la tache par : ");
    scanf("%i", &choix);
    return choix;

}
/*Fonctions Rechercher*/
int recherche(struct tache listTaches[], int count) {

int choix = sous_menuRecherche();

while (choix == 0)
{
  break;
}

switch (choix)
{
case 1:
int id;
printf("Entre ID : ");
scanf("%i", &id);
int i = indexById( id, listTaches,  count);

if (i != -1)
{
  printf("\n\t\t\t\t\t\tTache %i \n", i + 1);
    printf("___________________________________________________________________________________________________\n");
    printf("\n");
    printf("| - ID : %d || Titre : %s || Description : %s  ||  Deadline : %i-%i-%i  ||  Statut : %s |", listTaches[i].id, listTaches[i].titre, listTaches[i].desc, listTaches[i].time.j, listTaches[i].time.m, listTaches[i].time.a, listTaches[i].satut);
    printf("\n");
    printf("___________________________________________________________________________________________________\n");
    printf("\n_________________________________________________________________________________________________\n");
    printf("\n");
}else {
  printf("\nla tache n'existe pas\n");
}

  break;
case 2 :
char titre[50];
printf("Entre Titre : ");
scanf(" %49[^\n]", titre);
int index = indiceTitre( titre,  listTaches,  count);

if (index != -1)
{
  printf("\n\t\t\t\t\t\tTache %i \n", index + 1);
    printf("___________________________________________________________________________________________________\n");
    printf("\n");
    printf("| - ID : %d || Titre : %s || Description : %s  ||  Deadline : %i-%i-%i  ||  Statut : %s |", listTaches[index].id, listTaches[index].titre, listTaches[index].desc, listTaches[index].time.j, listTaches[index].time.m, listTaches[index].time.a, listTaches[index].satut);
    printf("\n");
    printf("___________________________________________________________________________________________________\n");
    printf("\n_________________________________________________________________________________________________\n");
    printf("\n");
}else {
  printf("la tache n'existe pas");
}

  break;
default:
  break;
}
}
/*Sous menu de Modifier */
int sous_menuModifier()
{
    printf("+____________________________________ Modification le ___________________________________________+\n");
    printf("|                                                                                                |\n");
    printf("|   1 - Modifier la description d'une tache                                                      |\n");
    printf("|   2 - Modifier le statut d'une tache                                                           |\n");
    printf("|   3 - Modifier le Deadline d'une tache                                                         |\n");
    printf("|   0 - Retour.                                                                                  |\n");
    printf("+________________________________________________________________________________________________+\n");

  int choix;
  printf("Modifier la tache par : ");
  scanf("%i", &choix);
  return choix;
}
int menu_typeRecherche()
{
    printf("+____________________________________ Modification le ___________________________________________+\n");
    printf("|                                                                                                |\n");
    printf("|   1 - Rechercher sur la tache par ID.                                                          |\n");
    printf("|   2 - Rechercher sur la tache par Titre.                                                       |\n");
    printf("|   0 - Retour.                                                                                  |\n");
    printf("+________________________________________________________________________________________________+\n");
  int choix;
  printf("tape le type de recherche : ");
  scanf("%i", &choix);
  return choix;
}
/*Fonctions Modifier les Taches  */
int Modifier(struct tache listTaches[], int count)
{

  int choix_1 = sous_menuModifier();
  while (choix_1 == 0)
  {   
     break;
  }
  switch (choix_1)
  {
    /*Case 1 Modifier  Description*/
  case 1:
    int choix_2 = menu_typeRecherche();
    while (choix_2 == 0)
    {
      sous_menuModifier();
      break;
    }
          switch (choix_2)
          {

          // Modifier description par ID;
          case 1:
            int id;
            printf("Entre ID : ");
            scanf("%i", &id);

            int index1 = indexById(id, listTaches, count);

            if (index1 != -1)
            {
              char nvDesc[50];
              printf("Entre la nouveau description de la tache %i : ", index1 + 1);
              scanf(" %49[^\n]", nvDesc);
              strcpy(listTaches[index1].desc, nvDesc);
            }
            else
            {
              printf("Cette tache n'existe pas\n");
            }
            break;
    // Modifier description par Titre;
          case 2:
          char titre[50];
          printf("Entre Titre : ");
          scanf(" %49[^\n]", titre);

          int index2 = indiceTitre(titre, listTaches, count);

          if (index2 != -1)
          {
            char nvDesc[50];
            printf("Entre la nouveau titre de la tache %i : ", index2 + 1);
            scanf(" %49[^\n]", nvDesc);
            strcpy(listTaches[index2].desc, nvDesc);
          }
          else
          {
            printf("Cette tache n'existe pas\n");
          }
          break;
        default:
          break;
    }
    break;
  // fin modification par Description
  // Modification par Statut
  case 2:
        int choix_3 = menu_typeRecherche();
        while (choix_3 == 0)
        {
          sous_menuModifier();
          break;
        }

          switch (choix_3)
          {
          // Modifier statut par ID;
          case 1:
            int id;
            printf("Entre ID : ");
            scanf("%i", &id);

            int index3 = indexById(id, listTaches, count);

            if (index3 != -1)
            {
              char nvStatut[50];
              printf("Entre la nouveau statut de la tache %i : ", index3 + 1);
              scanf(" %49[^\n]", nvStatut);
                while (strcmp(nvStatut , "To Do") != 0 && strcmp(nvStatut , "Doing") != 0 &&  strcmp(nvStatut , "Done") != 0)
                {
                  printf("Veuillez saisir l'etat correct de la tache : ");
                  scanf(" %49[^\n]", nvStatut);
                }
              strcpy(listTaches[index3].satut, nvStatut);
            }
            else
            {
              printf("Cette tache n'existe pas\n");
            }
            break;
          // Modifier statut par Titre;
          case 2:
            char titre[50];
            printf("Entre Titre : ");
            scanf(" %49[^\n]", titre);

            int index4 = indiceTitre(titre, listTaches, count);

            if (index4 != -1)
            {
              char nvStatut[50];
              printf("Entre la nouveau statut de la tache %i : ", index4 + 1);
              scanf(" %49[^\n]", nvStatut);
                while (strcmp(nvStatut , "To Do") != 0 && strcmp(nvStatut , "Doing") != 0 &&  strcmp(nvStatut , "Done") != 0)
                {
                  printf("Veuillez saisir l'etat correct de la tache : ");
                  scanf(" %49[^\n]", nvStatut);
                }
              strcpy(listTaches[index4].satut, nvStatut);
            }
            else
            {
              printf("Cette tache n'existe pas\n");
            }
            break;
          default:
            break;
          }
    // fin modification par statut

    // Modification par Deadline
  case 3:
        int choix_4 = menu_typeRecherche();
        while (choix_4 == 0)
        {
          sous_menuModifier();
          break;
        }

          switch (choix_4)
          {
          // Modifier Deadline par ID;
          case 1:
            int id;
            printf("Entre ID : ");
            scanf("%i", &id);

            int index3 = indexById(id, listTaches, count);

            if (index3 != -1)
            {
              int jj,mm ,a;
            printf("Jour : ");
            scanf("%i", &jj);
            while (jj > 31 || jj == 0)
            {
              printf("Veuillez saisir un jour inferieure ou egale a 31 et superieure a 0\n");
              printf("Jour  : ");
              scanf("%i", &jj);
            }
            listTaches[index3].time.j = jj;
            printf("Mois : ");
            scanf("%i", &mm);
            while (mm > 12 || mm == 0)
            {
              printf("Veuillez saisir un mois inferieure a 12 et superieure a 0\n");
              printf("donner le mois  : ");
              scanf("%i", &mm);
            }
            listTaches[index3].time.m = mm;
            printf("Annee : ");
            scanf("%i", &a);
            while (a > 25 || a < 22)
            {
              printf("le programms accept un delai limite de 2 ans \n");
              printf("L'annee : ");
              scanf("%i", &a);
            }
            listTaches[index3].time.a = a;
            }
            
            else
            {
              printf("Cette tache n'existe pas\n");
            }
            break;
          // Modifier statut par Titre;
          case 2:
            char titre[50];
            printf("Entre Titre : ");
            scanf(" %49[^\n]", titre);

            int index4 = indiceTitre(titre, listTaches, count);

            if (index4 != -1)
            {
              char nvStatut[50];
              printf("Entre la nouveau statut de la tache %i : ", index4 + 1);
              scanf(" %49[^\n]", nvStatut);

              strcpy(listTaches[index4].satut, nvStatut);
            }
            else
            {
              printf("Cette tache n'existe pas\n");
            }
            break;
          default:
            break;
          }
    default:
    break;
  }
  
}


// Sous MEnu Statistique 

int sous_menu_statistique () {

    printf("+____________________________________ Statistique ___________________________________________+\n");
    printf("|                                                                                            |\n");
    printf("|   1 - Afficher le nombre total des taches                                                  |\n");
    printf("|   2 - Afficher le nombre des taches completes et incompletes                               |\n");
    printf("|   3 - Afficher le nombre de jours restant jusqu'au delai de chaque taches                  |\n");
    printf("|   0 - Retour.                                                                              |\n");
    printf("+____________________________________________________________________________________________+\n");
  int choix;
  printf("tape le type de recherche : ");
  scanf("%i", &choix);
  return choix;


}
int statistique(struct tache listTaches[], int count) {

  int choix = sous_menu_statistique();
  while (choix == 0)
  {
    break;
  }

  switch (choix)
  {
  case 1:
    printf("le nombre total des taches sont : %i \n\n", count);
    break;
  case 2 :
  int tacheComplete = 0;
  int tacheIncomplete = 0;
  for (int i = 0; i < count; i++)
  {
    if (strcmp(listTaches[i].satut, "Done") == 0)
    {
      tacheComplete += 1;
    }else
    {
      tacheIncomplete += 1;
    }
    
    
  }
  printf("Les taches completes sont : %i", tacheComplete);
  printf("\nLes taches incompletes sont : %i", tacheIncomplete);
  break;
  //Afficher le nombre de jours restant jusqu'au delai de chaque taches
  case 3:
  
  long long currentTime = getCurrentEpochTime();


  for (int i = 0; i < count; i++)
  {
    long long saveDeadlineInSec = calcEpoqueTime(listTaches[i].time.a,listTaches[i].time.m, listTaches[i].time.j);
    int jrsRestantTache = differenceInjrs(saveDeadlineInSec , currentTime);
    if (jrsRestantTache < 0)
    {

       printf("deadline de cette tache %i a ete deja passe de: %i jours\n", i + 1 , jrsRestantTache * -1);
    }
    else {
      printf("les jours restant de la tache ");
    printf("%i : %i jours\n", i + 1 , jrsRestantTache);
    }


  }
  break;
  default:
    break;
  }
  
}
//Suppression une tache 

int suppressionTache(struct tache listTaches[], int count) {

  int id;
  printf("Veuillez Saisir id de la tache a supprimer : ");
  scanf("%i" , &id);
  int maxId = 0;
    for (int i = 0; i < count; i++)
  {
    if (maxId < listTaches[i].id)
    {
      maxId = listTaches[i].id;
    }
    
  }

  while (id <= 0 || id > maxId)
  {
      printf("ID incorrect  : ");
      scanf("%i" , &id);
      
  }
  int index = indexById(id , listTaches , count); 

    for (int i = index; i < count - 1; i++)
    {
      
        listTaches[i] = listTaches[i + 1];
      
    }
    
  

  return count - 1;

}




//=========================================================================================================================
/*fonctions main */
int main()
{

  int count = 0;
  /*Declaration Variable */
  struct tache afaireList[100];
  int choix;

  int check = 1;
  while (check != 0)
  {
    menu();
    printf("choix : ");
    scanf("%i", &choix);

    switch (choix)
    {
    case 0:
      check = 0;
      printf("le programms est termine merci pour la visite");
      break;
    case 1:
      count = ajouterTache(afaireList, count);
      break;
    case 2:
      count = ajouterTaches(afaireList, count);
      break;
    case 3:
      afficherListTache(afaireList , count);
      afficherTaches(afaireList, count);
      break;
    case 4:
      Modifier(afaireList, count);
      afficherListTache(afaireList, count);
      break;
      case 5 :
      count = suppressionTache(afaireList,  count);
      afficherListTache(afaireList, count);
      break;

      case 6:
      recherche(afaireList,  count);
      break;
      case 7:
       statistique(afaireList,  count);
      break;
    default:
      break;
    }
  }

  return 0;
}
