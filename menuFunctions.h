#pragma once

#define menuSize 400
#define nameSize 100
#define productSize 100
#define productDB "textFiles/productDB.txt"

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

struct DateProdus{
    int cantitate, pret;
    long int id;
    char name[nameSize];
};
typedef struct DateProdus prod;

struct NodProdus{
    prod dateProdus;
    struct NodProdus *next;
};
typedef struct NodProdus nod;

struct ListaProduse{
    nod *first;
    nod *last;
    int size;
};
typedef struct ListaProduse lista;

const char* nodeToChar(nod*, int);

void plasareComanda(char[], lista*);

void vanzareProduse();

void vizualizareComenzi(char[]);

void cautareProduse();

void menu(char[]);

void logout();
