#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Nch 50


typedef struct
{
    int jour;
    int mois;
    int annee;
} date;

typedef struct
{
    int Numchambre ;
    int type;// 1=Individuelle, 2=A deux;
    int prix;
    int etat;//0=libre, Id=Occupée par le client Id;
} chambre;

typedef struct
{
    int Id;
    char NP[40];
    int Ntele;
    int Nchambre;
    date DT;  //[JJ,MM,AA]
    int nj;
} client;

void mdp()
{
    FILE *f;
    f=fopen("mot de passe.txt","r");
    char a[20];
    char b[20];
    fscanf(f,"%s",a);
    int c=0;
    int tentative=1;
    printf("\n\n\n\n\n\t\t\t\t\t\t    _________________________________________________________");
    printf("\n\t\t\t\t\t\t    |°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
    printf("\n");
    do
    {
        printf("\t\t\t\t\t\t\t\tSaisir votre mot de passe: ");
        scanf("%s",b);
        if(strcmp(a,b)==0)
        {
            Sleep(100);
            printf("\n\n\t\t\t\t\t\t\t         == mot de passe correct ==");
            c=1;
        }
        else
        {
            printf("\n\t\t\t\t\t\t    _________________________________________________________");
            printf("\n\t\t\t\t\t\t    |°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
            printf("\n\t\t\t\t\t\t\t\t* Mot de passe incorrect *\n ");
            tentative++;
        }
    }
    while(c==0 && tentative<7);

    fclose(f);
}
//************************************

void chambres()
{
    int n=Nch, i;
    FILE *f;
    chambre E;
    f = fopen("chambres.txt", "wb");
    for (i=1; i<n+1; i++)
    {
        E.Numchambre=i;
        if(i<26) E.type=1;
        else E.type=2;
        E.prix=(1200+i*(i/3))/5;
        E.etat=0;
        fwrite(&E, sizeof(chambre), 1, f);
    }
    fclose(f);
    f = fopen("cptchambre.txt", "w");
    fprintf(f, "%d", n);
    fclose(f);
    f = fopen("cptclient.txt", "w");
    fprintf(f, "%d", 0);
    fclose(f);
    f = fopen("cptId.txt", "w");
    fprintf(f, "%d", 0);
    fclose(f);
}
//************************************

void aff_vide()
{
    chambre E;
    FILE *f;
    int i;
    f = fopen("chambres.txt", "rb");
    for (i=0; i<Nch; i++)
    {
        fread(&E, sizeof(chambre), 1, f);
        if (E.etat==0)
        {
            printf("\n\t\t\t\t\t\t\t   ________________________________________________________");
            printf("\n\t\t\t\t\t\t\t   |°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
            printf("\n\n\t\t\t\t\t\t\t\t\t le numero de la chambre : %d", E.Numchambre);
            printf("\n\t\t\t\t\t\t\t\t\t le type de la chambre :");
            if (E.type==1) printf("Individuelle");
            if (E.type==2) printf("a deux");
            printf("\n\t\t\t\t\t\t\t\t\t le prix de la chambre : %d Dhs/j\n", E.prix);
        }
    }
    fclose(f);
}

//************************************
void affchambre()
{
    chambre E;
    FILE *f;
    int i;
    f = fopen("chambres.txt", "rb");
    for (i=0; i<Nch; i++)
    {
        fread(&E, sizeof(chambre), 1, f);
        printf("\n\n\t\t\t\t\t\t    _________________________________________________________");
        printf("\n\t\t\t\t\t\t    |°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
        printf("\n\n\t\t\t\t\t\t\t\tle numero de la chambre : %d", E.Numchambre);
        printf("\n\t\t\t\t\t\t\t\tle type de la chambre :");
        if (E.type==1) printf("Individuelle");
        else  printf("a deux");
        printf("\n\t\t\t\t\t\t\t\tla chambre est ");
        if(E.etat==0)printf("vide.");
        else printf("reservee.");
        printf("\n\t\t\t\t\t\t\t\tle prix de la chambre : %d Dhs/j", E.prix);
        printf("\n");
    }
    fclose(f);
}

//************************************
void reservation()
{
    int counter,id;
    FILE* f;
    FILE* g;
    FILE *h;
    client E;
    chambre C;

    f = fopen("cptclient.txt", "r");
    fscanf(f, "%d", &counter);
    fclose(f);
    h= fopen("cptId.txt", "r");
    fscanf(h, "%d", &id);
    fclose(h);


    g = fopen("clients.txt", "a");
    printf("\n\n\t\t\t\t\t\t        _________________________________________________________");
    printf("\n\t\t\t\t\t\t        |°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
    printf("\n\n\t\t\t\t\t\t\t\tSaisir votre nom complet: ");
    fflush(stdin);
    gets(&E.NP);
    printf("\t\t\t\t\t\t\t\tSaisir votre numero de telephone:(+212)");
    scanf("%d",&E.Ntele);
    printf("\t\t\t\t\t\t\t\tEntrer le numero de la chambre a reserver :");
    scanf("%d", &E.Nchambre);
    printf("\t\t\t\t\t\t\t\tQuand voulez vous commencer votre reservation ?");
    printf("\n\t\t\t\t\t\t\t\tDonnez le jour : ");
    scanf("%d", &E.DT.jour);
    printf("\t\t\t\t\t\t\t\tDonnez le mois : ");
    scanf("%d", &E.DT.mois);
    printf("\t\t\t\t\t\t\t\tDonnez l'annee : ");
    scanf("%d", &E.DT.annee);
    printf("\t\t\t\t\t\t\t\tNombre de jours a reserver: ");
    scanf("%d", &E.nj);
    E.Id=id+1;
    fwrite(&E, sizeof(client), 1, g);
    fclose(g);
    printf("\n\n\t\t\t\t\t\t        _________________________________________________________");
    printf("\n\t\t\t\t\t\t        |°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
    printf("\n\n\n\t\t\t\t\t\t\t\tVous avez reserve la chambre %d avec succes.\n\t\t\t\t\t\t\t\t\t  == Votre Id est %d ==",E.Nchambre,E.Id);
    f = fopen("cptclient.txt", "w");
    fprintf(f, "%d", counter+1);
    fclose(f);
    h = fopen("cptId.txt", "w");
    fprintf(h, "%d", id+1);
    fclose(h);
    f=fopen("chambres.txt","rb");
    g=fopen("tppp.txt","wb");
    do
    {
        fread(&C, sizeof(chambre), 1, f);
        if (C.Numchambre!=E.Nchambre) fwrite(&C, sizeof(chambre), 1, g);
    }
    while(C.Numchambre!=E.Nchambre);
    C.etat=E.Id;
    fwrite(&C, sizeof(chambre), 1, g);
    while(!feof(f))
    {
        fread(&C, sizeof(chambre), 1, f);
        fwrite(&C, sizeof(chambre), 1, g);
    }
    fclose(f);
    fclose(g);
    remove("chambres.txt");
    rename("tppp.txt","chambres.txt");
}
//**************************************
void modification(int m)
{

    char x;
    client E, F;
    FILE *f;
    FILE *g,*aa;
    int counter;
    f = fopen("clients.txt","rb");
    g = fopen("temp.txt","wb");
    aa = fopen("cptclient.txt", "r");
    fscanf(aa, "%d", &counter);
    fclose(aa);
    int i;
    for (i=1; i<=counter; i++)
    {
        fread(&E, sizeof(client), 1, f);
        if (E.Id!=m)
        {
            fwrite(&E, sizeof(client), 1, g);
        }
        else break;
    }

    F=E;
    printf("\n\n\t\t\t\t\t\t    _________________________________________________________");
    printf("\n\t\t\t\t\t\t    |°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
    printf("\n\n\t\t\t\t\t\t\tVoulez-vous modifier le nom et le prenom ? (o/n): ");
    fflush(stdin);
    scanf("%c",&x);
    if(x=='o')
    {
        printf("\t\t\t\t\t\t\tSaisir un nouveau nom et prenom: ");
        fflush(stdin);
        gets(F.NP);
    }


    printf("\n\t\t\t\t\t\t\tVoulez-vous modifier le numero de telephone ? (o/n): ");
    fflush(stdin);
    scanf("%c",&x);
    if(x=='o')
    {
        printf("\t\t\t\t\t\t\tSaisir un nouveau Num de tele: ");
        scanf("%d",&F.Ntele);
    }

    printf("\n\t\t\t\t\t\t\tVoulez-vous modifier la date du debut de la reservation ? (o/n): ");
    fflush(stdin);
    scanf("%c",&x);
    if(x=='o')
    {
        printf("\t\t\t\t\t\t\tSaisir une nouvelle date:\n");
        printf("\t\t\t\t\t\t\tDonnez le jour: ");
        scanf("%d", &F.DT.jour);
        printf("\t\t\t\t\t\t\tDonnez le mois: ");
        scanf("%d", &F.DT.mois);
        printf("\t\t\t\t\t\t\tDonnez l'annee: ");
        scanf("%d", &F.DT.annee);
    }


    printf("\n\t\t\t\t\t\t\tVoulez-vous modifier le nombre de jours a reserver ? (o/n): ");
    fflush(stdin);
    scanf("%c",&x);
    if(x=='o')
    {
        printf("\t\t\t\t\t\t\tSaisir une nouvelle duree: ");
        scanf("%d",&F.nj);
    }

    fwrite(&F, sizeof(client), 1, g);
    printf("\n\n\n\t\t\t\t\t\t\tVotre modification est effectuee avec succes.");
    do
    {
        fread(&E, sizeof(client), 1, f);
        fwrite(&E, sizeof(client), 1, g);
    }
    while (!feof(f));
    fclose(f);
    fclose(g);
    remove("clients.txt");
    int ret;
    ret = rename("temp.txt", "clients.txt");
}
//***********************************************
void suppression(int m)
{
    int counter, i, k;
    client E;
    chambre C;
    FILE *f=NULL;
    FILE *g=NULL;
    FILE *aa=NULL;
    aa = fopen("cptclient.txt", "r");
    fscanf(aa, "%d", &counter);
    fclose(aa);
    f = fopen("clients.txt","rb");
    g = fopen("temp.txt","wb");
    for (i=1; i<=counter; i++)
    {
        fread(&E, sizeof(client), 1, f);
        if (E.Id!=m)
        {
            fwrite(&E, sizeof(client), 1,g);
        }
        else k=E.Nchambre;
    }
    fclose(f);
    fclose(g);
    remove("clients.txt");
    rename("temp.txt", "clients.txt");
    printf("\n\n\n\n\t\t\t\t\t\t    _________________________________________________________");
    printf("\n\t\t\t\t\t\t    |°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
    printf("\n\n\t\t\t\t\t\t\tVotre reservation est supprimee avec succes");
    printf("\n\n\t\t\t\t\t\t    _________________________________________________________");
    printf("\n\t\t\t\t\t\t    |°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
    f = fopen("cptclient.txt", "w");
    fprintf(f, "%d", counter-1);
    fclose(f);
    f=fopen("chambres.txt","rb");
    g=fopen("ppp.txt","wb");
    do
    {
        fread(&C, sizeof(chambre), 1, f);
        if (C.Numchambre!=k) fwrite(&C, sizeof(chambre), 1, g);
    }
    while(C.Numchambre!=k);
    C.etat=0;
    fwrite(&C, sizeof(chambre), 1, g);
    while(!feof(f))
    {
        fread(&C, sizeof(chambre), 1, f);
        fwrite(&C, sizeof(chambre), 1, g);
    }
    fclose(f);
    fclose(g);
    remove("chambres.txt");
    rename("ppp.txt","chambres.txt");
}

//*******************************************
void met_reservation()
{
    int m;
    char Np[50];
    int i, w, counter;
    client E, F;
    FILE *f;
    FILE *ww;

    printf("\n\t\t\t\tBonjour, saisir votre Id et votre nom pour effectuer des modifications ou supprimer votre reservation: ");
h:
    printf("\n\t\t\t\tSaisir votre Id: ");
    scanf("%d", &m);
    printf("\t\t\t\tSaisir votre nom complet: ");
    fflush(stdin);
    gets(Np);
    f = fopen("clients.txt","rb");
    ww = fopen("cptclient.txt", "r");
    fscanf(ww, "%d", &counter);
    //tester si l'Id(m) est valide******************************************************************
    fclose(ww);
    for (i=1; i<=counter; i++)
    {
        fread(&E, sizeof(client), 1, f);
        if (E.Id==m && strcmp(E.NP,Np)==0) break;
    }
    printf("\n\n\t\t\t\t\t\t    _________________________________________________________");
    printf("\n\t\t\t\t\t\t    |°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
    printf("\n\n\t\t\t\t\t\t\t Salut cher client voici vos donnees initiales:\n\n");
    printf("\t\t\t\t\t\t\t ID: %d\n", E.Id);
    printf("\t\t\t\t\t\t\t Le nom et le prenom: %s\n", E.NP);
    printf("\t\t\t\t\t\t\t Numero de telephone: %d\n",E.Ntele);
    printf("\t\t\t\t\t\t\t Numero de chambre: %d\n",E.Nchambre);
    printf("\t\t\t\t\t\t\t Date du debut de la reservation: %d-%d-%d\n",E.DT.jour,E.DT.mois,E.DT.annee);
    printf("\t\t\t\t\t\t\t Nombre de jours: %d\n",E.nj);
    fclose(f);
    printf("\n\t\t\t\t\t\t    _________________________________________________________");
    printf("\n\t\t\t\t\t\t    |°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
    printf("\n\n\n\t\t\t\t\t\t\t\t    Que voulez-vous faire?");
    printf("\n\t\t\t\t\t\t\t\t 1-Modifier votre reservation.");
    printf("\n\t\t\t\t\t\t\t\t 2-Supprimer votre reservation.");
    printf("\n\t\t\t\t\t\t\t\t 3-Revenir au menu.");
    printf("\n\n\n\t\t\t\t\t\t\t\t     Choisir une option:");
start:
    scanf("%d",&w);
    if(w!=1&&w!=2&&w!=3)
    {
        printf("\n\t\t\t\t\t\tOption non valide, choisir une option valide:");
        goto start;
    }
    else if(w==3)
    {
        system("cls");
        menuC();
    }
    else if(w==1)
    {
        system("cls");
        printf("\n\n\t\t\t\t\t\t    _________________________________________________________");
        printf("\n\t\t\t\t\t\t    |°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
        printf("\n\n\t\t\t\t\t\t\t Salut cher client voici vos donnees initiales:\n\n");
        printf("\t\t\t\t\t\t\t ID: %d\n", E.Id);
        printf("\t\t\t\t\t\t\t Le nom et le prenom: %s\n", E.NP);
        printf("\t\t\t\t\t\t\t Numero de telephone: %d\n",E.Ntele);
        printf("\t\t\t\t\t\t\t Numero de chambre: %d\n",E.Nchambre);
        printf("\t\t\t\t\t\t\t Date du debut de la reservation: %d-%d-%d\n",E.DT.jour,E.DT.mois,E.DT.annee);
        printf("\t\t\t\t\t\t\t Nombre de jours: %d\n",E.nj);
        modification(m);
    }
    else
    {
        system("cls");
        suppression(m);
    }
}
//**************************************

void menuC()
{
    int a;
back:
    printf("\n\n\n\t\t\t\t\t\t  _________________________________________________________");
    printf("\n\t\t\t\t\t\t  |°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
    printf("\n\n\t\t\t\t\t\t\t\t  Bonjour cher client\n");
    printf("\t\t\t\t\t\t\t\t  Que voulez-vous faire?\n\n");
    printf("\n\t\t\t\t\t\t  _________________________________________________________");
    printf("\n\t\t\t\t\t\t  |°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
    printf("\n\n\t\t\t\t\t\t\t\t1- Reserver une chambre\n");
    printf("\t\t\t\t\t\t\t\t2- Mettre a jour une reservation\n");
    printf("\t\t\t\t\t\t\t\t3- Afficher les chambres vides\n");
    printf("\t\t\t\t\t\t\t\t4- Retour au menu\n\n\n");
    printf("\t\t\t\t\t\t\t\t  Choisir une option SVP: ");
l:
    scanf("%d", &a);
    switch(a)
    {
    case 1:
        system("cls");
        reservation();
        printf("\n\n\t\t\t\t\t\tCliquer sur n'importe qu'elle touche pour revenir au menu_client");
        getch();
        system("cls");
        goto back;
        break;
    case 2:
        system("cls");
        met_reservation();
        printf("\n\n\t\t\t\t\t\tCliquer sur n'importe qu'elle touche pour revenir au menu_client");
        getch();
        system("cls");
        goto back;
        break;
    case 3:
        system("cls");
        aff_vide();
        printf("\n\n\t\t\t\t\t\tCliquer sur n'importe qu'elle touche pour revenir au menu_client");
        getch();
        system("cls");
        goto back;
        break;
    case 4:
        system("cls");
        menu();
        break;
    default:
    {
        printf("\n\t\t\t\t\t\t\t\tVeuiller choisir une option valide: ");
        goto l;
    }
    }
}

void modif_reservation()
{
    int m;
    printf("\n\n\n\t\t\t\t\t\t  _________________________________________________________");
    printf("\n\t\t\t\t\t\t  |°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
    printf("\n\n\t\t\t\t\t\t\tEntrer l'Id du client reservant: ");
    scanf("%d", &m);
    char x;
    client E, F;
    FILE *f;
    FILE *g, *aa;
    int counter;
    f = fopen("clients.txt","rb");
    g = fopen("temp.txt","wb");
    aa = fopen("cptclient.txt", "r");
    fscanf(aa, "%d", &counter);
    fclose(aa);
    int i;
    for (i=1; i<=counter; i++)
    {
        fread(&E, sizeof(client), 1, f);
        if (E.Id!=m)
        {
            fwrite(&E, sizeof(client), 1, g);
        }
        else break;
    }

    F=E;

    printf("\n\n\n\t\t\t\t\t\tVoulez-vous modifier la date du debut de la reservation ? (o/n): ");
zz:
    fflush(stdin);
    scanf("%c",&x);
    if (x!='o' && x!='n')
    {
        printf("\t\t\t\t\t\t\tEntrer un choix valide: ");
        goto zz;
    }
    if(x=='o')
    {
        printf("\t\t\t\t\t\tSaisir une nouvelle date:\n");
        printf("\t\t\t\t\t\tDonnez le jour: ");
        scanf("%d", &F.DT.jour);
        printf("\t\t\t\t\t\tDonnez le mois: ");
        scanf("%d", &F.DT.mois);
        printf("\t\t\t\t\t\tDonnez l'annee: ");
        scanf("%d", &F.DT.annee);
    }


    printf("\n\t\t\t\t\t\tVoulez-vous modifier le nombre de jours a reserver ? (o/n): ");
rr:
    fflush(stdin);
    scanf("%c",&x);
    if (x!='o' && x!='n')
    {
        printf("\t\t\t\t\t\tEntrer un choix valide: ");
        goto rr;
    }
    if(x=='o')
    {
        printf("\t\t\t\t\t\tSaisir une nouvelle duree: ");
        scanf("%d",&F.nj);
    }

    fwrite(&F, sizeof(client), 1, g);
    printf("\n\n\n\t\t\t\t\t\t  _________________________________________________________");
    printf("\n\t\t\t\t\t\t  |°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
    printf("\n\n\n\t\t\t\t\t\t\t       Modification effectuee avec succes.");
    do
    {
        fread(&E, sizeof(client), 1, f);
        fwrite(&E, sizeof(client), 1, g);
    }
    while (!feof(f));
    fclose(f);
    fclose(g);
    remove("clients.txt");
    int ret;
    ret = rename("temp.txt", "clients.txt");
}

void met_reserv_admin()
{
    int x;
    printf("\n\n\n\t\t\t\t\t\t  _________________________________________________________");
    printf("\n\t\t\t\t\t\t  |°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
    printf("\n\n\t\t\t\t\t\t\t\t   Que voulez-vous faire?\n\n\n");
    printf("\t\t\t\t\t\t\t\t1-Ajouter un client\n");
    printf("\t\t\t\t\t\t\t\t2-Modifier une reservation\n");
    printf("\t\t\t\t\t\t\t\t3-Supprimer une reservation\n");
    printf("\n\n\n\t\t\t\t\t\t\t\t    Choisir une option: ");

re:
    scanf("%d",&x);
    int m;
    switch(x)
    {
    case 1:
        system("cls");
        reservation();
        break;
    case 2:
        system("cls");
        modif_reservation();
        break;
    case 3:
        system("cls");
        printf("\n\n\n\t\t\t\t\t\t  _________________________________________________________");
        printf("\n\t\t\t\t\t\t  |°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
        printf("\n\n\t\t\t\t\t\t\tSaisir l'Id du client que vous voulez supprimer: ");
        scanf("%d",&m);
        suppression(m);
        break;
    default:
        printf("\nChoisir une option valide:");
        goto re;
        break;
    }
}

void menuA()
{
k:
    printf("\n\n\n\t\t\t\t\t\t  _________________________________________________________");
    printf("\n\t\t\t\t\t\t  |°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
    printf("\n\n\t\t\t\t\t\t\t            *  *  *  *  *  *  *  *");
    printf("\n\n\t\t\t\t\t\t\t            *                    *");
    printf("\n\n\t\t\t\t\t\t\t            *    Hello Admin     *");
    printf("\n\n\t\t\t\t\t\t\t            *                    *");
    printf("\n\n\t\t\t\t\t\t\t            *  *  *  *  *  *  *  *");
    Sleep(700);
    printf("\n\n\t\t\t\t\t\t  _________________________________________________________");
    printf("\n\t\t\t\t\t\t  |°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
    printf("\n\t\t\t\t\t\t\t\t   == Que voulez faire? ==\n\n");
    printf("\t\t\t\t\t\t\t\t  1- Afficher les reservations\n");
    printf("\t\t\t\t\t\t\t\t  2- Mettre a jour une reservation\n");
    printf("\t\t\t\t\t\t\t\t  3- Afficher les chambres\n");
    printf("\t\t\t\t\t\t\t\t  4- Mettre a jour une chambre\n");
    printf("\t\t\t\t\t\t\t\t  5- Initialiser_DATA\n");
    printf("\t\t\t\t\t\t\t\t  6- Retour au menu\n");
    int a;
    printf("\n\n\t\t\t\t\t\t\t\t    Choisir une option SVP: ");
ll:
    scanf("%d", &a);
    switch(a)
    {
    case 1:
        system("cls");
        affclient();
        printf("\n\n\t\t\t\t\t\t  Cliquer sur n'importe qu'elle touche pour revenir au menu_Admin..");
        getch();
        system("cls");
        goto k;
        break;
    case 2:
        system("cls");
        met_reserv_admin();
        printf("\n\n\t\t\t\t\t\t  Cliquer sur n'importe qu'elle touche pour revenir au menu_Alient..");
        getch();
        system("cls");
        goto k;
        break;
    case 3:
        system("cls");
        affchambre();
        printf("\n\n\t\t\t\t\t\t  Cliquer sur n'importe qu'elle touche pour revenir au menu_Alient..");
        getch();
        system("cls");
        goto k;
        break;
    case 4:
        system("cls");
        met_chambre();
        printf("\n\n\t\t\t\t\t\t  Cliquer sur n'importe qu'elle touche pour revenir au menu_Alient..");
        getch();
        system("cls");
        goto k;
    case 5:
        system("cls");
        remove("clients.txt");
        remove("chambres.txt");
        remove("cptchambre.txt");
        remove("cptclient.txt");
        remove("cptId.txt");
        chambres();
        printf("\n\n\t\t\t\t\t\t\t   _________________________________________________________");
        printf("\n\t\t\t\t\t\t\t   |°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
        printf("\n\n\t\t\t\t\t\t\t      Toutes les reservations sont supprimees avec succes.\n\t\t\t\t\t\t\t   Toutes les chambres sont initialisees a leur etat initiale.");
        printf("\n\n\t\t\t\t\t\t\t   _________________________________________________________");
        printf("\n\t\t\t\t\t\t\t   |°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
        printf("\n\n\t\t\t\t\t\t\t  Cliquer sur n'importe qu'elle touche pour revenir au menu_Alient..");
        getch();
        system("cls");
        goto k;
    case 6:
        system("cls");
        menu();
        break;
    default:
    {
        printf("\n\t\t\t\t\t\t\t\t    choisir une option valide: ");
        goto ll;
        break;
    }
    }
}


void menu()
{

    printf("\n\n\t\t\t\t\t\t\t   _________________________________________________________");
    printf("\n\t\t\t\t\t\t\t   |°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
    printf(" \n\n\t\t\t\t\t\t\t\t           *  *  *  *  *  *  *  *");
    printf("\n\n\t\t\t\t\t\t\t\t           *                    *");
    printf("\n\n\t\t\t\t\t\t\t\t           *     Bienvenue      *");
    printf("\n\n\t\t\t\t\t\t\t\t           *                    *");
    printf("\n\n\t\t\t\t\t\t\t\t           *  *  *  *  *  *  *  *");
    Sleep(1000);
    printf("\n\n\t\t\t\t\t\t\t   ________________________________________________________");
    printf("\n\t\t\t\t\t\t\t   |°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
    printf("\n\n\t\t\t\t\t\t\tVoulez-vous se connecter en tant que Admin ou en tant que Client? ");
    printf("\n\n\t\t\t\t\t\t\t\t\t\t 1- Admin\n\t\t\t\t\t\t\t\t\t\t 2- Client");
    printf(" \n\n\t\t\t\t\t\t\t\t\t   Choisir une option(1/2):...");
    int o;
Restart:
    fflush(stdin);
    scanf("%d",&o);
    if(o==1)
    {
        system("cls");
        mdp();
        Sleep(2000);
        system("cls");
        menuA();
    }
    else if(o==2)
    {
        system("cls");
        menuC();
    }
    else
    {
        printf("\t\t\t\t\t\t\t\t\t   Choisir une option valide:.");
        goto Restart;
    }

    getch();


    return 0;
}


void affclient()
{
    client E;
    FILE *f;
    int counter, i;
    f= fopen("cptclient.txt", "r");
    fscanf(f, "%d", &counter);
    fclose(f);
    f = fopen("clients.txt", "rb");
    for (i=0; i<counter; i++)
    {
        fread(&E, sizeof(client), 1, f);
        printf("\n\n\t\t\t\t\t\t    _________________________________________________________");
        printf("\n\t\t\t\t\t\t    |°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
        printf("\n\n\t\t\t\t\t\t\t\t\t== Client %d ==", i+1);
        printf("\n\n\t\t\t\t\t\t\t\tID: %d", E.Id);
        printf("\n\t\t\t\t\t\t\t\tLe nom et le prenom: %s", E.NP);
        printf("\n\t\t\t\t\t\t\t\tNumero de telephone: (+212)%d",E.Ntele);
        printf("\n\t\t\t\t\t\t\t\tNumero de chambre: %d",E.Nchambre);
        printf("\n\t\t\t\t\t\t\t\tDate du debut de la reservation: %d-%d-%d",E.DT.jour,E.DT.mois,E.DT.annee);
        printf("\n\t\t\t\t\t\t\t\tNombre de jours: %d\n",E.nj);
    }
    fclose(f);
}

void met_chambre()
{
    int x;
    printf("\n\n\n\t\t\t\t\t\t  _________________________________________________________");
    printf("\n\t\t\t\t\t\t  |°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
    printf("\n\n\t\t\t\t\t\tSaisir le numero de la chambre que vous voulez mettre a jour:");
    scanf("%d",&x);
    FILE *f;
    FILE *g;
    chambre c;
    f=fopen("chambres.txt","rb");
    g=fopen("tempch.txt","wb");
    while(!feof(f) && c.Numchambre!=x)
    {
        fread(&c,sizeof(chambre),1,f);
        if(c.Numchambre!=x)fwrite(&c,sizeof(chambre),1,g);
    }
    char k;
    printf("\n\n\t\t\t\t\t\t\tVoulez-vous modifier le prix de la chambre?(o/n): ");
g:
    fflush(stdin);
    scanf("%c",&k);
    if(k!='o' && k!='n')
    {
        printf("\n\t\t\t\t\t\t\tchoisir une option valide: ");
        goto g;
    }
    else if(k=='o')
    {
        printf("\t\t\t\t\t\t\tSaisir le nouveau prix de la chambre:");
        scanf("%d",&c.prix);
    }
    printf("\n\t\t\t\t\t\t\tVoulez-vous modifier l'etat de la chambre?(o/n): ");
j:
    fflush(stdin);
    scanf("%c",&k);
    if(k!='o' && k!='n')
    {
        printf("\n\t\t\t\t\t\t\tchoisir une option valide: ");
        goto j;
    }
    else if(k=='o')
    {
        printf("\t\t\t\t\t\t\tSaisir la nouvelle etat de la chambre:");
        scanf("%d",&c.etat);
    }
    fwrite(&c,sizeof(chambre),1,g);
    printf("\n\n\n\t\t\t\t\t\t  _________________________________________________________");
    printf("\n\t\t\t\t\t\t  |°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
    printf("\n\n\t\t\t\t\t\t\tLa chambre est mise a jour avec succes.");
    while(!feof(f))
    {
        fread(&c,sizeof(chambre),1,f);
        fwrite(&c,sizeof(chambre),1,g);
    }
    fclose(f);
    fclose(g);
    remove("chambres.txt");
    rename("tempch.txt","chambres.txt");
}

void intro()
{
    //Changement de la couleur de l'arrière plan et du text.
    system("color F4");
    Sleep(1000);
    int i;

    printf("\n\n\t\t\t\t\t  ");
    for(i=0; i<74; i++)
    {
        printf("=");
        Sleep(20);
    }
    printf("\n\n\t\t\t\t\t  === Application de gestion de reservations des chambres dans un hotel ===");
    Sleep(500);

    printf("\n\n\t\t\t\t\t\t\t         === G.INFO Groupe 6 ===");
    Sleep(500);
    printf("\n\n\t\t\t\t\t\t\t\t  === Ifrah Youness ===");
    Sleep(500);
    printf("\n\n\t\t\t\t\t\t\t      === Bettaoui Saif Elislam ===");
    Sleep(500);
    printf("\n\n\t\t\t\t\t\t\t         === Benhlima Douaa ===");
    Sleep(500);
    printf("\n\n\t\t\t\t\t\t\t        === Tabarani Ibtihal ===");
    Sleep(500);
    printf("\n\n\t\t\t\t\t\t        === EMI:Ecole Mohammadia d'Ingenieurs ===\n\t\t\t");
    Sleep(500);
    printf("\n\t\t\t\t\t  ");
    for(i=0; i<74; i++)
    {
        printf("=");
        Sleep(20);
    }
    printf("\n\n\n\n\n\t\t\t\t\t\t  _________________________________________________________");
    printf("\n\t\t\t\t\t\t  |°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
    Sleep(200);
    printf("\n\t\t\t\t\t\t     Appuyez sur n'importe quelle touche pour continuer... ");
    getch();
    system("cls");
//Introduction
    printf("\n\n\t\t\t\t\t\t\t   ________________________________________________________");
    printf("\n\t\t\t\t\t\t\t   |°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°|");
    printf(" \n\n\n\t\t\t\t\t\t\t\t   <<< chargement, veuillez patienter >>>");

    printf("\n\t\t\t\t\t\t\t\t  ");
    for(i=0; i<41; i++)
    {
        printf(".");
        Sleep(40);
    }
    Sleep(500);
}

main()
{
    intro();
    menu();
}
