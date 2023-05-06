//
//  functions.c
//  ECE Final Project draft
//
//  Created by Franco Barra on 4/25/23.
//
#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include <time.h>
#include <string.h>

#include "functions.h"

void printFullDeck(card deck[], int size){
    for(int i = 0; i < size; i++){
        printf("%s %d %s\n", deck[i].color, deck[i].value, deck[i].action);
    }
}

void createDeckAndShuffle(card deck[], int size){
    readFromFile(deck, size);
    shuffle(deck, size, 1000);
}

void readFromFile(card deck[], int size){
    FILE* inp = NULL;
    inp = fopen("finaldecktestday.txt", "r");
    if(inp == NULL){
        printf("Can't find file Deck.txt\n");
    }
    int i;
    for (i = 0; i < size; i++){
        fscanf(inp, "%s %d %s", deck[i].color, &deck[i].value, deck[i].action);
    }
    fclose(inp);
}

int rand_gen(int count){
    double frac;
    frac = (double)rand()/((double)RAND_MAX+1); // gives a different frac every time is executed
    return floor(count * frac); //random index in [0, max]
}

void swap(card deck[], int i, int j){
    // find index i and j
    card temp;
    temp = deck[i];
    deck[i] = deck[j];
    deck[j] = temp;
//    for (int k = 0; k < i; k++){
//        temp = deck
//    }
}

void shuffle(card deck[],int sizeDeck, int swaptimes){
    srand((int)time(NULL));
    //int swapCount = 10000,
    int i, element1, element2;
    for(i = 0; i < swaptimes; i++){
            element1 = rand_gen(sizeDeck);
            element2 = rand_gen(sizeDeck);
            swap(deck, element1, element2);
    }
}

void printCard(char color[], int cardNumber, int printTimes, char action[]){
    for(int i = 0; i < printTimes; i++){
        printf("%s %d %s\n", color, cardNumber, action);
    }
}

void PrintDeck(void){  
    int i;
    for(i = 0; i < 4; i++){
        if(i == 0){ //use for loop i = 0, i <= 11
            printCard("yellow", 1, 3, "none");
            printCard("yellow", 2, 3, "anycolor");
            printCard("yellow", 3, 3, "none");
            printCard("yellow", 4, 3, "none");
            printCard("yellow", 5, 3, "none");
            printCard("yellow", 6, 2, "none");
            printCard("yellow", 7, 2, "none");
            printCard("yellow", 8, 2, "none");
            printCard("yellow", 9, 2, "none");
            printCard("yellow", 10, 2, "none");
            printCard("yellow", 11, 2, "anynumber");
        }
        else if(i == 1){
            printCard("red", 1, 3, "none");
            printCard("red", 2, 3, "anycolor");
            printCard("red", 3, 3, "none");
            printCard("red", 4, 3, "none");
            printCard("red", 5, 3, "none");
            printCard("red", 6, 2, "none");
            printCard("red", 7, 2, "none");
            printCard("red", 8, 2, "none");
            printCard("red", 9, 2, "none");
            printCard("red", 10, 2, "none");
            printCard("red", 11, 2, "anynumber");
        }
        else if(i == 2){
            printCard("green", 1, 3, "none");
            printCard("green", 2, 3, "anycolor");
            printCard("green", 3, 3, "none");
            printCard("green", 4, 3, "none");
            printCard("green", 5, 3, "none");
            printCard("green", 6, 2, "none");
            printCard("green", 7, 2, "none");
            printCard("green", 8, 2, "none");
            printCard("green", 9, 2, "none");
            printCard("green", 10, 2, "none");
            printCard("green", 11, 2, "anynumber");
        }
        else if(i == 3){
            printCard("blue", 1, 3, "none");
            printCard("blue", 2, 3, "anycolor");
            printCard("blue", 3, 3, "none");
            printCard("blue", 4, 3, "none");
            printCard("blue", 5, 3, "none");
            printCard("blue", 6, 2, "none");
            printCard("blue", 7, 2, "none");
            printCard("blue", 8, 2, "none");
            printCard("blue", 9, 2, "none");
            printCard("blue", 10, 2, "none");
            printCard("blue", 11, 2, "anynumber");
        }
    }
}

void printDashOrAsterisk(int value){        //
    if(value == 1){
        printf("\n-------------------------------------------------------------\n");
    }
    else{
        printf("\n**************************************************************\n");
        printf("**************************************************************\n");
    }
}

void printPlayerWins(int value){
    printf("\n**************************************************************\n");
    printf("***********************PLAYER %d WINS****************************\n", value);
    printf("**************************************************************\n");
}
