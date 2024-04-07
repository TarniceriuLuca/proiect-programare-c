#include "menuFunctions.h"

const char* nodeToChar(nod *nod, int hasQuantity)
{

    char *comanda = (char*)malloc(sizeof(char) * productSize);
    if(hasQuantity == 1)
        snprintf(comanda, sizeof(char)*productSize, "%ld %s %d %d\n", nod->dateProdus.id, nod->dateProdus.name, nod->dateProdus.cantitate, nod->dateProdus.pret);
    else
        snprintf(comanda, sizeof(char)*productSize, "%ld %s %d\n", nod->dateProdus.id, nod->dateProdus.name,  nod->dateProdus.pret);
    return comanda;
}

void plasareComanda(char userFileLocation[nameSize], lista *l)
{
    int endFunction = -1, reachedEnd = 0, cantitate;
    long int id;

    system("cls");
    
     //afisare meniu
        FILE *menuFile;
        menuFile = fopen("textFiles/orderMenuFile.txt", "r");
        char menuText[menuSize];
        while(fgets(menuText, menuSize, menuFile))
            printf("%s", menuText);
        printf("\n    Introduceti id-ul produsului: ");
    //sfarsit afisare

    scanf("%ld", &id);
    if(id == -1)
    {
        system("cls");
        return;
    }


    nod *index = l->first;
    while(index->dateProdus.id != id && reachedEnd == 0)
    {
        if(index == l->last)
            reachedEnd = 1;
        if(reachedEnd == 0)
            index = index->next;
    }
    if(reachedEnd == 1 && index->dateProdus.id != id)
    {
        system("cls");
        printf("Produsul cu acest id nu exista!\n");
        return;
    }



    printf("    Introduceti cantitatea dorita:");scanf("%d", &cantitate);
    if(cantitate == -1)
    {
        system("cls");
        return;
    }
    if(cantitate < -1 || cantitate == 0)
    {
        system("cls");
        printf("nu puteti cumpara o cantitate negativa sau nula de produse\n");
        return;
    }
    
    if(index->dateProdus.cantitate == 0)
    {
        printf(" Acest produs nu mai este in stoc\n Pentru revenire la meniu introduceti '1'\n");
        scanf("%d", &endFunction);
        system("cls");
        return;
    }

    if(index->dateProdus.cantitate < cantitate)
    {
        printf(" In stoc mai sunt doar %d produse\n Pentru a continua cu %d produse introduceti '2'\n Pentru revenire la meniu introduceti '1'\n", index->dateProdus.cantitate, index->dateProdus.cantitate);
        scanf("%d", &endFunction);
        if(endFunction == 1)
        {
            system("cls");
            return;
        }
        else
            cantitate = index->dateProdus.cantitate;
    }

    printf(" nume produs: %s\n pret produs: %d\n disponibilitate: %d\n\n", index->dateProdus.name, index->dateProdus.pret, index->dateProdus.cantitate);
    printf(" Pentru confirmarea comenzii introduceti: '2'\n");
    printf(" Pentru anulare introduceti: '1'\n");
    scanf("%d", &endFunction);

    if(endFunction == 2)
    {
        system("cls");
        printf(" comanda a fost acceptata\n");
        index->dateProdus.cantitate -= cantitate;
        nod *comanda = (nod*)malloc(sizeof(nod));
        *comanda = *index;
        comanda->dateProdus.cantitate = cantitate;

        //adaugare comanda in fisierul utilizatorului
        FILE *userFile;

        userFile = fopen(userFileLocation, "a");
        fprintf(userFile, "%s", nodeToChar(comanda, 1));
        fclose(userFile);


        //modificare productDB
        FILE *productFile;
        productFile = fopen(productDB, "w");
        nod *rewriter = l->first;
        while(rewriter != NULL)
        {
            fprintf(productFile, "%s", nodeToChar(rewriter, 1));      
            rewriter = rewriter->next;
        }
        fclose(productFile);

    }
    if(endFunction == 0)
    {
        system("cls");
        printf(" La revedere!");
        exit(0);
    }
    if(endFunction == 1)
        system("cls");

    
    
    
}

int unusedId(lista *l)
{
    long int max = 0;
    nod *index = l->first;
    while(index != NULL)
    {
        if(index->dateProdus.id > max)
            max = index->dateProdus.id;
        index = index->next;
    }
    return max+1;

}

void vanzareProduse(lista *l)
{
    nod *sellProduct = (nod*)malloc(sizeof(nod));
    getchar();
    system("cls");


    //afisare meniu
        FILE *menuFile;
        menuFile = fopen("textFiles/sellMenuFile.txt", "r");
        char menuText[menuSize];
        while(fgets(menuText, menuSize, menuFile))
            printf("%s", menuText);
    //sfarsit afisare
    printf("\n    Introduceti numele produsului:");



    char nameChar[nameSize];
    fgets(nameChar, sizeof(nameChar), stdin); 
    if(!strcmp(nameChar, "-1"))
        {
            system("cls");
            return;
        }
    for(int i = 0; i < strlen(nameChar); i++)
    {
        if(nameChar[i] == ' ')
        {
            nameChar[i] = '_';
        }
    }
    nameChar[strlen(nameChar)-1] = '\0';
    strcpy(sellProduct->dateProdus.name, nameChar);
    printf("    Introduceti cantitatea vanduta:"); scanf("%d", &sellProduct->dateProdus.cantitate);
    if(sellProduct->dateProdus.cantitate == -1)
    {
        system("cls");
        return;
    }
    if(sellProduct->dateProdus.cantitate <= 0)
    {
        system("cls");
        printf("nu puteti vinde o cantitate de produse mai mica decat 1\n");
        free(sellProduct);
        return;
    }
    printf("    Introduceti pretul produsului:"); scanf("%d", &sellProduct->dateProdus.pret);
    if(sellProduct->dateProdus.pret == -1)
    {
        system("cls");
        return;
    }
    if(sellProduct->dateProdus.pret <= 0)
    {
        system("cls");
        printf("nu puteti vinde produse cu pretul mai mic decat 1\n");
        free(sellProduct);
        return;
    }

    nod *index = l->first;
    while(index != NULL)
    {
        if(strcmp(index->dateProdus.name, sellProduct->dateProdus.name) == 0 && index->dateProdus.pret == sellProduct->dateProdus.pret)
        {
            index->dateProdus.cantitate += sellProduct->dateProdus.cantitate;
            system("cls");
            printf("\n Produs: <%d:%s, %d, %d> adaugat cu succes\n", sellProduct->dateProdus.id, sellProduct->dateProdus.name, sellProduct->dateProdus.cantitate,sellProduct->dateProdus.pret);
            //modificare productDB
                FILE *productFile;
                productFile = fopen(productDB, "w");
                nod *rewriter = l->first;
                while(rewriter != NULL)
                {
                    fprintf(productFile, "%s", nodeToChar(rewriter, 1));
                    rewriter = rewriter->next;
                }
                fclose(productFile);
            free(sellProduct);
            return;
        }
        index = index->next;
    }
    index = l->first;
    sellProduct->dateProdus.id = unusedId(l);
    sellProduct->next = NULL;
    l->last->next = sellProduct;
    l->last = sellProduct;
    l->size++;
    system("cls");
    printf("\n Produs: <%d:%s, %d, %d> inregistrat cu succes\n", sellProduct->dateProdus.id, sellProduct->dateProdus.name, sellProduct->dateProdus.cantitate,sellProduct->dateProdus.pret);
    //modificare productDB
        FILE *productFile;
        productFile = fopen(productDB, "w");
        nod *rewriter = l->first;
        while(rewriter != NULL)
        {
            fprintf(productFile, "%s", nodeToChar(rewriter, 1)); 
            rewriter = rewriter->next;
        }
        fclose(productFile);

}

void vizualizareComenzi(char userFileLocation[nameSize])
{
    int hasAny = 0;
    system("cls");
    FILE *ordersFile;
    ordersFile = fopen(userFileLocation, "r");
    char ordersText[menuSize];
    printf(" id,    nume,    cantitate,    pret\n");
    while(fgets(ordersText, productSize, ordersFile))
    {
        printf(" %s", ordersText);
        hasAny = 1;
    }
    if(hasAny == 0)
        printf(" Nu exista comenzi.\n");
    int endFunction;
    printf(" \n Pentru intoarcere la meniu, introduceti: '1' \n Pentru inchidere aplicatie introduceti: '0'\n");
    scanf("%d", &endFunction);
    if(endFunction == 0)
    {
        system("cls");
        printf(" La revedere!");
        exit(0);
    }
    else
        system("cls");
}

void cautareProduse(lista *l)
{
    int option;
    char search[nameSize], check[nameSize];
    int pretMin, pretMax;

    nod *prod = l->first;
    system("cls");

    //afisare meniu
        FILE *menuFile;
        menuFile = fopen("textFiles/searchMenuFile.txt", "r");
        char menuText[menuSize];
        while(fgets(menuText, menuSize, menuFile))
            printf("%s", menuText);
        printf("\n Introduceti numarul instructiunii dorite: ");
    //sfarsit afisare

    scanf("%d", &option);
    getchar();

    switch (option)
    {
    case 1:
        printf("    Cautare: ");
        fgets(search, nameSize, stdin);
        printf("\n");
        search[strlen(search)-1] = '\0';
        if(!strcmp(search, "-1"))
        {
            system("cls");
            return;
        }


        while(prod != NULL)
        {

            strcpy(check, prod->dateProdus.name);
            for(int i = 0; i < strlen(check); i++)
            {
                check[i] = tolower(check[i]);
            }

            for(int i = 0; i < strlen(search); i++)
            {
                search[i] = tolower(search[i]);
            }

            if(strstr(check, search))
            {
                printf("%s", nodeToChar(prod, 1));
            }
            prod = prod->next;
        }
        break;
    case 2:
        printf("    minim:"); scanf("%d", &pretMin);
        if(pretMin == -1)
        {
            system("cls");
            return;
        }

        printf("    maxim:"); scanf("%d", &pretMax); 
        if(pretMax == -1)
        {
            system("cls");
            return;
        }

        getchar();
        if(pretMin > pretMax)
        {
            int aux = pretMin;
            pretMin = pretMax;
            pretMax = aux;
        }

        printf("\n");

        while(prod != NULL)
        {
            if(prod->dateProdus.pret >= pretMin && prod->dateProdus.pret <= pretMax)
            {
                printf("%s", nodeToChar(prod, 1));
            }
            prod = prod->next;
        }
        break;

    case 3:
        printf("    Cautare: ");
        fgets(search, nameSize, stdin);
        search[strlen(search)-1] = '\0';

        if(!strcmp(search, "-1"))
        {
            system("cls");
            return;
        }

        printf("    minim:"); scanf("%d", &pretMin);
        if(pretMin == -1)
        {
            system("cls");
            return;
        }

        printf("    maxim:"); scanf("%d", &pretMax); 
        if(pretMax == -1)
        {
            system("cls");
            return;
        }

        getchar();
        printf("\n");

        while(prod != NULL)
        {

            strcpy(check, prod->dateProdus.name);
            for(int i = 0; i < strlen(check); i++)
            {
                check[i] = tolower(check[i]);
            }

            if(strstr(check, search) && prod->dateProdus.pret >= pretMin && prod->dateProdus.pret <= pretMax)
            {
                printf(" %s", nodeToChar(prod, 1));
            }
            prod = prod->next;
        }

        break;
    default:
        system("cls");
        return;
        break;
    }

    printf(" \n Pentru a reincepe cautarea, introduceti: '2' \n Pentru intoarcere la meniu, introduceti: '1' \n Pentru inchidere aplicatie introduceti: '0'\n");
    int endFunction;
    scanf("%d", &endFunction);
    if(endFunction == 0)
    {
        system("cls");
        printf(" La revedere!");
        exit(0);
    }
    if(endFunction == 2)
    {
        cautareProduse(l);
    }
    else
        system("cls");
}

void afisare(lista *l)
{
    system("cls");
    nod *index = l->first;
    printf(" id,    nume,    cantitate,    pret\n");
    while(index != NULL)
    {
        printf("%s", nodeToChar(index, 1));
        index = index->next;
    }
    //apasati return pentru revenire la meniu
    int endFunction;
    printf("\n Pentru intoarcere la meniu, introduceti: '1' \n Pentru inchidere aplicatie introduceti: '0'\n");
    scanf("%d", &endFunction);
    if(endFunction == 0)
    {
        system("cls");
        printf(" La revedere!");
        exit(0);
    }
    system("cls");

}

void logout()
{
    system("cls");
    printf(" La revedere!");
    exit(0);
}


void menu(char userFileLocation[nameSize])
{
    lista *lista;
    int load = 1;

    int answer = 0;
    system("cls");
    while(answer == 0)
    {

        { //afisare meniu
            
            FILE *menuFile;
            menuFile = fopen("textFiles/menuFile.txt", "r");
            char menuText[menuSize];
            while(fgets(menuText, menuSize, menuFile))
                printf("%s", menuText);
            printf(" Introduceti numarul instructiunii dorite: ");
            //sfarsit afisare
        }

        scanf("%d", &answer);


        
        if(load == 1)
        {
            //incarcare produse
            load = 0;
            FILE *productFile;
            char productText[productSize];
            productFile = fopen("textFiles/productDB.txt", "r");
            nod *firstNode = (nod*)malloc(sizeof(nod));

            if(fgets(productText, productSize, productFile))
            {
                //se imparte prima linie din fisierul de produse in subsiruri pentru fiecare atribut
                //si se asigneaza valorile noului nod

                char *atribut = strtok(productText, " ");
                int indexAtribut = 0;
                while(atribut != NULL)
                {
                    switch (indexAtribut)
                    {
                        case 0:
                            firstNode->dateProdus.id = atoi(atribut);
                            break;
                        case 1:
                            strcpy(firstNode->dateProdus.name, atribut);
                            break;
                        case 2:
                            firstNode->dateProdus.cantitate = atoi(atribut);
                            break;
                        case 3:
                            firstNode->dateProdus.pret = atoi(atribut);
                            break;
                    }
                    indexAtribut++;
                    atribut = strtok(NULL, " ");
                }
                firstNode->next = NULL;

                //se atribuie listei primul si ultimul nod, ca fiind singurul prezent la acest moment.
                lista->first = firstNode;
                lista->last = firstNode;
                lista->size = 1;
            }

            while(fgets(productText, productSize, productFile))
            {
                //repetarea procesului descris mai sus, pentru restul elementelor.

                nod *newNode = (nod*)malloc(sizeof(nod));

                char *atribut = strtok(productText, " ");
                int indexAtribut = 0;
                while(atribut != NULL)
                {
                    switch (indexAtribut)
                    {
                        case 0:
                            newNode->dateProdus.id = atoi(atribut);
                            break;
                        case 1:
                            strcpy(newNode->dateProdus.name, atribut);
                            break;
                        case 2:
                            newNode->dateProdus.cantitate = atoi(atribut);
                            break;
                        case 3:
                            newNode->dateProdus.pret = atoi(atribut);
                            break;
                    }
                    indexAtribut++;
                    atribut = strtok(NULL, " ");
                }
                newNode->next = NULL;
                lista->last->next = newNode;
                lista->last = newNode;
                lista->size++;
            }

            //sfarsit incarcare

        }
        
        switch (answer)
        {
            case 1: plasareComanda(userFileLocation, lista); load = 1; break;
            case 2: vanzareProduse(lista); load = 1; break;
            case 3: vizualizareComenzi(userFileLocation); break;
            case 4: cautareProduse(lista); break;
            case 5: afisare(lista); break;
            case 0: logout(); break;
        }
        answer = 0;
    }
}