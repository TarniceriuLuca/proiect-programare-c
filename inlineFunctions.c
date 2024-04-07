#include "inlineFunctions.h"



int checkAccountDB(char** argv)
{
    int isSignedUp = 0;

    FILE *accountsFile;
    accountsFile = fopen("textFiles/accountDB.txt", "r");
    char nameText[nameSize];

    while(fgets(nameText, nameSize, accountsFile) && isSignedUp == 0)
    {
        if(strstr(nameText, argv[2]) != NULL && strstr(nameText, argv[3]) != NULL)
        {
            //se citesc numele care au conturi pe rand.
            //daca deja exista un cont cu numele respectiv, 
            //functia returneaza 1 pentru isSignedUp
            
            isSignedUp = 1;
        }
    }
    //daca se citesc toate numele si nu s-a gasit 
    //numele cerut pentru inregistrare, isSignedUp va ramane 0

    fclose(accountsFile);
    return isSignedUp;
}

void help()
{
    FILE *helpFile;
    helpFile = fopen("textFiles/helpFile.txt", "r");
    char helpText[helpSize];
    while(fgets(helpText, helpSize, helpFile))
    {
        printf("%s", helpText);
    }
    fclose(helpFile);
}

void signup(char** argv)
{
    int isSignedUp = checkAccountDB(argv);
    
    if(isSignedUp == 0)
    {
        //daca nu exista contul la care se cere inregistrare
        //acesta se va adauga in fisier si se va crea folderul contului

        char name[nameSize] = "", userFileLocation[nameSize] = ""; 
        //crearea stringului cu numele utilizatorului
        strcat(name, argv[2]); 
        strcat(name, "_");
        strcat(name, argv[3]);
        strcat(name, "\n");

        FILE *accountsFile;
        accountsFile = fopen("textFiles/accountDB.txt", "a");
        fprintf(accountsFile, name);
        fclose(accountsFile);

        //crearea stringului cu pathul spre fisierul utilizatorului
        strcat(userFileLocation, "userFiles/");
        strcat(userFileLocation, argv[2]);
        strcat(userFileLocation, "_");
        strcat(userFileLocation, argv[3]);
        strcat(userFileLocation, ".txt");


        FILE *ordersFile;
        ordersFile = fopen(userFileLocation, "w");
        fprintf(ordersFile, "");
        fclose(ordersFile);

        printf("cont creeat cu succes!");
    }
    else
        printf("Contul deja exista");


}

void login(char** argv)
{
    int isSignedUp = checkAccountDB(argv);
    char userFileLocation[nameSize] = "";

    strcat(userFileLocation, "userFiles/");
    strcat(userFileLocation, argv[2]);
    strcat(userFileLocation, "_");
    strcat(userFileLocation, argv[3]);
    strcat(userFileLocation, ".txt");

    if(isSignedUp == 1)
        menu(userFileLocation);
    else
        printf("Acest cont nu exista");
}


void cmdLine(int argc, char** argv)
{
    if(argc == 1)
    {
        printf("Nu au fost introduse argumentele pe linia de comanda");
    }
    else
    {
        if(strcmp(argv[1], "help") == 0)
            help();
        
        if(strcmp(argv[1], "login") == 0)
            login(argv);

        if(strcmp(argv[1], "signup") == 0)
            signup(argv);
    }
}