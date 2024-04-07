#pragma once

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>

#define helpSize 100
#define nameSize 100

int checkAccountDB(char**);

void help();

void signup(char**);

void login(char**);


void cmdLine(int, char**);