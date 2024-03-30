#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct date
{
  int j, m, a;
};
typedef struct date date;
struct mouvement
{
  int quantMvt;
  date dateMvt;
  char typeMvt;
  struct mouvement *suivant;
};
typedef struct mouvement *mouvement;
struct produit
{
  int code;
  char libelle[10];
  int quantDisp;
  float prix;
  int seuil;
  struct mouvement *listeMvt;
  struct produit *suivant;
};
typedef struct produit *liste;
liste rechercherProduitParCode(liste l, int code)
{
  liste p = l;
  while (p != NULL && (code != p->code))
    p = p->suivant;
  return p;
}
liste rechercherProduitParLibelle(liste l, char libelle[])
{
  liste p = l;
  while (p != NULL && (strcmp(p->libelle, libelle) != 0))
    p = p->suivant;
  return p;
}
// **********************************************************************************************
// affichage ************7titha mel fo9 belkol bech ken st7a9inaha fi ay blasa dima mawjoda *****
void afficherMouvement(mouvement m)
{
  printf("================ Liste des Mouvement  ================\n");
  mouvement p = m;
  if (p == NULL)
    printf("la liste est vide \n");
  while (p)
  {
    printf("Quantite : %d, Date : %d/%d/%d, Type : %c\n", p->quantMvt, p->dateMvt.j, p->dateMvt.m, p->dateMvt.a, p->typeMvt);
    p = p->suivant;
  }
  printf("=================================================\n");
}
void afficherListes(liste l, int afficheMouvementAussi, int afficheUneSeulFois)
{
  liste p = l;
  if (p == NULL)
    printf("la list est vide ");
  while (p != NULL)
  {
    printf("\n code : %d \n", p->code);
    printf("\n libelle de produit :%s \n", p->libelle);
    printf("\n La quantit disponible en stock:%d \n", p->quantDisp);
    printf("\n Prix Unitaire:%f \n", p->prix);
    printf("\n Le seuil minimal en stock:%d \n\n", p->seuil);
    if (afficheMouvementAussi == 1)
      afficherMouvement(p->listeMvt);
    if (afficheUneSeulFois == 1)
      p = NULL;
    else
      p = p->suivant;
  }
}
// ********************************************************************************************************
// les menus lkol *****************************************************************************************
// block mt3 munuAjouter ------------------------------ Munu Maj -> choix 1 : Ajouter un nouveau produit
liste allocationDuListe()
{
  liste nouvList = malloc(sizeof(struct produit));
  printf("\n\n donner le code : ");
  scanf("%d", &nouvList->code);
  printf("donner Libelle de produit : ");
  scanf("%s", &nouvList->libelle);
  printf("Donner la  quantite disponible en stock : ");
  scanf("%d", &nouvList->quantDisp);
  printf("donner Prix unitaire : ");
  scanf("%f", &nouvList->prix);
  printf("donner le seuil minimal de realiser :");
  scanf("%d", &nouvList->seuil);
  return nouvList;
}
liste AjoutTete(liste l)
{
  liste nouv = allocationDuListe();
  nouv->listeMvt = NULL;
  nouv->suivant = l;
  l = nouv;
  return l;
}
liste AjoutQueue(liste l)
{
  liste nouv = allocationDuListe();
  nouv->listeMvt = NULL;
  nouv->suivant = NULL;
  if (l == NULL)
    l = nouv;
  else
  {
    liste p = l;
    while (p->suivant != NULL)
      p = p->suivant;
    p->suivant = nouv; // p w l 3andhom nafes address ma3naha kif nbadel p , l bech ttbadel  zeda
  }
  return l;
}
liste MenuAjouter(liste tete)
{
  int choix;
  while (choix != 3)
  {
    printf("\n\n--------> Menu Ajouter <--------\n");
    printf("\n 1.Ajouter en tete \n");
    printf("\n 2.Ajouter en queue \n");
    printf("\n 3.Quitter \n");
    printf(" \n Donner votre choix En Menu Ajouter SVP:");
    scanf("%d", &choix);
    printf("\n---------------------------------------------------------\n");
    switch (choix)
    {
    case 1:
      tete = AjoutTete(tete);
      break;
    case 2:
      tete = AjoutQueue(tete);
      break;
    case 3:
      break;
    default:
      printf("\n %d n'exist pas dans le menu\n", choix);
      printf("---------------------------------------------------------\n");
    }
  }
  return tete;
}
//--------------------------------------------------
// block mt3 MenuConsultation ----------------choix 4 : Consultation des produits
void RechercherUnProduitParCode(l)
{
  int codeProduit;
  printf("Entrez le code du produit pour lequel vous souhaitez chercher : ");
  scanf("%d", &codeProduit);
  liste produit = rechercherProduitParCode(l, codeProduit);
  afficherListes(produit, 0, 1);
}
void RechercherUnProduitParLibelle(l)
{
  char libelleProduit[20];
  printf("Entrez le libelle du produit pour lequel vous souhaitez chercher : ");
  scanf(" %s", libelleProduit);
  liste produit = rechercherProduitParLibelle(l, libelleProduit);
  afficherListes(produit, 0, 1);
}
void MenuConsultation(l)
{
  int choix;
  while (choix != 4)
  {
    printf("\n\n-----> Menu Consultation <-----\n");
    printf("\n 1.Liste des produits avec ses mouvements \n");
    printf("\n 2.Rechercher un produit par code \n");
    printf("\n 3.Rechercher un produit par libelle \n");
    printf("\n 4.Quitter \n");
    printf(" \n Donner votre choix En Menu Consultation SVP:");
    scanf("%d", &choix);
    printf("\n---------------------------------------------------------");
    switch (choix)
    {
    case 1:
      afficherListes(l, 1, 0);
      break;
    case 2:
      RechercherUnProduitParCode(l);
      break;
    case 3:
      RechercherUnProduitParLibelle(l);
      break;
    case 4:
      break;
    default:
      printf("\n %d n'exist pas dans le menu\n", choix);
      printf("---------------------------------------------------------\n");
    }
  }
}
// menu mt3 MenuModification ------------- Menu Maj -> choix 3 :Modifier les donn�es d�un produit
liste modificationParLibelle(liste l)
{
  int code;
  char text[40];
  printf(" \n donner le code de produit \n ");
  scanf("%d", &code);
  liste produit = rechercherProduitParCode(l, code);
  if (produit == NULL)
  {
    printf("Produit non trouve.\n");
    return l;
  }
  printf(" \n donner le  nouveau libelle \n ");
  scanf("%s", text);
  strcpy(produit->libelle, text);
  afficherListes(produit, 0, 1);
  return l;
};
liste modificationParPrixUnitaire(liste l)
{
  int code;
  float prixUnitaire;
  printf(" \n donner le code de produit \n ");
  scanf("%d", &code);
  liste produit = rechercherProduitParCode(l, code);
  if (produit == NULL)
  {
    printf("Produit non trouve.\n");
    return l;
  }
  printf(" \n donner le  nouveau prixUnitaire \n ");
  scanf("%f", &prixUnitaire);
  produit->prix = prixUnitaire;
  afficherListes(produit, 0, 1);
  return l;
};
liste modificationParLeSeuil(liste l)
{
  int code;
  int nouvSeuil;
  printf(" \n donner le code de produit \n ");
  scanf("%d", &code);
  liste produit = rechercherProduitParCode(l, code);
  if (produit == NULL)
  {
    printf("Produit non trouve.\n");
    return l;
  }
  printf(" \n donner le  nouveau seuil \n ");
  scanf("%d", &nouvSeuil);
  produit->seuil = nouvSeuil;
  afficherListes(produit, 0, 1);
  return l;
};
liste MenuModification(liste tete)
{
  int choix;
  while (choix != 4)
  {
    printf("\n\n----> Menu Modification <----\n");
    printf("\n 1.Libelle \n");
    printf("\n 2.Prix unitaire \n");
    printf("\n 3.le seuil \n");
    printf("\n 4.Quitter \n");
    printf(" \n Donner votre choix En Menu Modification SVP:");
    scanf("%d", &choix);
    printf("\n---------------------------------------------------------");
    switch (choix)
    {
    case 1:
      tete = modificationParLibelle(tete);
      break;
    case 2:
      tete = modificationParPrixUnitaire(tete);
      break;
    case 3:
      tete = modificationParLeSeuil(tete);
      break;
    case 4:
      break;
    default:
      printf("\n %d n'exist pas dans le menu\n", choix);
      printf("---------------------------------------------------------\n");
    }
  }
  return tete;
}
// block mt3 mouvements
mouvement ajoutMouvement(mouvement m)
{
  mouvement nouv = malloc(sizeof(struct mouvement));
  printf("\n Entrer La Quantite Du Mouvement \n");
  scanf("%d", &nouv->quantMvt);
  printf("\n Entrer Le jour \n");
  scanf("%d", &nouv->dateMvt.j);
  printf("\n Entrer Le Mois \n");
  scanf("%d", &nouv->dateMvt.m);
  printf("\n Entrer L annee \n");
  scanf("%d", &nouv->dateMvt.a);
  printf("\n Entrer Le  Type \n");
  scanf(" %c", &nouv->typeMvt);
  nouv->suivant = m;
  m = nouv;
  return m;
}
liste genererMouvements(liste l)
{
  char reponse;
  int codeProduit;
  printf("Entrez le code du produit pour lequel vous souhaitez ajouter un mouvement : ");
  scanf("%d", &codeProduit);
  liste produitDuMouv = rechercherProduitParCode(l, codeProduit);
  if (produitDuMouv == NULL)
  {
    printf("Produit non trouve.\n");
    return l;
  }
  produitDuMouv->listeMvt = ajoutMouvement(produitDuMouv->listeMvt);
  do
  {
    printf("\n Voulez-vous ajouter un nouveau mouvement ? (Y/N)");
    scanf(" %c", &reponse);
    if (reponse == 'y' || reponse == 'Y')
      produitDuMouv->listeMvt = ajoutMouvement(produitDuMouv->listeMvt);
  } while (reponse == 'y' || reponse == 'Y');
  afficherMouvement(produitDuMouv->listeMvt);
  return l;
}
// block mt3 MenuSuppression --------------- Menu MAJ -> choix 2 : Supprimer un produit
liste SuppressionTete(liste l)
{
  liste p = l;
  if (l != NULL)
  {
    l = l->suivant;
    free(p);
  }
  // afficherListe(l, 0);
  return l;
};
liste SuppressionQueue(liste l)
{
  liste p = l;
  if (p->suivant == NULL)
  {
    free(p);
    return NULL;
  }
  while (p->suivant->suivant != NULL)
    p = p->suivant;
  free(p->suivant);
  p->suivant = NULL;
  afficherListes(l, 0, 0);
  return l;
};
liste SuppressionSpecifique(liste l)
{
  int codeProduit;
  printf("donner le code pour supprimer :");
  scanf("%d", &codeProduit);
  liste produitDuMouv = rechercherProduitParCode(l, codeProduit);
  if (produitDuMouv == NULL)
  {
    printf("Produit non trouve.\n");
    return l;
  }
  if (l->code == codeProduit)
  {
    liste NoeudAsupprimer = l;
    l = l->suivant;
    free(NoeudAsupprimer);
  }
  else
  {
    liste precedent = l;        // hedi l'adresse de la deuxieme Noeud
    liste courant = l->suivant; // hedi l'adresse de la premiere Noeud
    while (courant != NULL)
    {
      if (courant->code == codeProduit)
      {
        precedent->suivant = courant->suivant;
        free(courant);
      }
      else
      {
        courant = courant->suivant;
        precedent = precedent->suivant;
      }
    }
  }
  afficherListes(l, 0, 0);
  return l;
};
liste MenuSuppression(liste tete)
{
  int choix;
  while (choix != 4)
  {
    printf("\n\n----> Menu Suppression <----\n");
    printf("\n 1.Suppression en tete \n");
    printf("\n 2.Suppression en queue \n");
    printf("\n 3.Suppression d un produit donne \n");
    printf("\n 4.Quitter \n");
    printf(" \n Donner votre choix En Menu Suppression SVP:");
    scanf("%d", &choix);
    printf("\n---------------------------------------------------------");
    switch (choix)
    {
    case 1:
      tete = SuppressionTete(tete);
      break;
    case 2:
      tete = SuppressionQueue(tete);
      break;
    case 3:
      tete = SuppressionSpecifique(tete);
      break;
    case 4:
      break;
    default:
      printf("\n %d n'exist pas dans le menu\n", choix);
      printf("---------------------------------------------------------\n");
    }
  }
  return tete;
}
// ------------------------------choix :2.Mise a jour de la liste des produits du stock
liste MenuMaj(liste tete)
{
  int choix;
  while (choix != 4)
  {
    printf("\n\n ---------> Menu Maj <---------\n");
    printf("\n 1.Ajouter un nouveau produit\n");
    printf("\n 2.Supprimer un produit \n");
    printf("\n 3.Modifier les donnees d un produit\n ");
    printf("\n 4.Quitter\n\n");
    printf(" \n Donner votre choix En Menu MAJ SVP:");
    scanf("%d", &choix);
    printf("\n---------------------------------------------------------");
    switch (choix)
    {
    case 1:
      tete = MenuAjouter(tete);
      break;
    case 2:
      tete = MenuSuppression(tete);
      break;
    case 3:
      tete = MenuModification(tete);
      break;
    case 4:
      break;
    default:
      printf("\n %d n'exist pas dans le menu\n", choix);
      printf("\n---------------------------------------------------------\n");
    }
  }
  return tete;
}
// block mt3 SaisieProduit -------------------- choix : 1.Creation du stock
liste SaisieProduit(l)
{
  int nbProduit;
  do
  {
    printf("===========> donner le nombre du produit <=========== :");
    scanf("%d", &nbProduit);
  } while (nbProduit < 0);
  for (int i = 0; i < nbProduit; i++)
    l = AjoutQueue(l);
  afficherListes(l, 0, 0);
  return l;
};
// mise a jour du stock
liste MiseAJourDuStock(l)
{
  liste p = l;
  while (p)
  {
    while (p->listeMvt)
    {
      if (p->listeMvt->typeMvt == 'e')
        p->quantDisp += p->listeMvt->quantMvt;
      else
        p->quantDisp -= p->listeMvt->quantMvt;
      p->listeMvt = p->listeMvt->suivant;
    }
    free(p->listeMvt);
    p = p->suivant;
  }
  return l;
}
// Generer Commande De Produits
void GenererCommandeDeProduits(liste l)
{
  liste p = l;
  int quantiteMinimale;
  if (p == NULL)
    printf("votre stock est vide");
  else
  {
    while (p != NULL)
    {
      p->quantDisp >= p->seuil ? printf("votre stock n est pas au dessous de la seuil\n") : printf("la quantite minimale a commande est %d \n", p->seuil - p->quantDisp);
      p = p->suivant;
    }
  }
}
// ----------------------------------------------------
void main()
{
  liste tete = NULL;
  int choix;
  while (choix != 7)
  {
    printf("\n\n ---------------> Menu general <---------------\n");
    printf("\n 1.Creation du stock\n");
    printf("\n 2.Mise a jour de la liste des produits du stock\n");
    printf("\n 3.Mouvements\n");
    printf("\n 4.Consultation des produits\n");
    printf("\n 5.Mise a jour du stock\n");
    printf("\n 6.Generer commande de produits\n");
    printf("\n 7.Quitter \n\n");
    printf(" \n Donner votre choix SVP: ");
    scanf("%d", &choix);
    switch (choix)
    {
    case 1:
      tete = SaisieProduit(tete);
      break;
    case 2:
      tete = MenuMaj(tete);
      break;
    case 3:
      tete ? genererMouvements(tete) : printf("il n'ya pas des produits ");
      break;
    case 4:
      tete ? MenuConsultation(tete) : printf("il n'ya pas des produits ");
      break;
    case 5:
      tete = MiseAJourDuStock(tete);
      break;
    case 6:
      GenererCommandeDeProduits(tete);
      break;
    case 7:
      break;
    default:
      printf("\n %d n'exist pas dans le menu \n", choix);
      printf("---------------------------------------------------------\n");
    }
  }
}