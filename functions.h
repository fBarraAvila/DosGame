//
//  functions.h
//  ECE Final Project draft
//
//  Created by Franco Barra on 4/25/23.
//

#ifndef functions_h
#define functions_h

#include <stdio.h>

typedef struct card_s{
    char color[7];
    int value;
    char action[15];
    struct card_s *previous, *next;
} card;

void printCard(char color[], int cardNumber, int printTimes, char action[]);    //Prints individual card
void PrintDeck(void);                                                           // Prints deck as shown in image from project document. This is use to print out the deck and copy and paste it to .txt file
//void PrintOrganizeDeck1(void);                                                  //
void printFullDeck(card deck[], int size);                                      //Prints current game deck
void copyValuesToCard(card deck[], char color[], int value, char action[]);      // copies card color, number and action into an individual card
void CreateDeck(card deck[], int size); // creates deck as shown in image from project document
//*********int indexValue(card deck[], int index, char color[], int value, int times, char action[]);
void readFromFile(card deck[], int size); // read from file up to the size of the array
void createDeckAndShuffle(card deck[], int size); // creates a deck of size "size" and uses readFromFile() to create a deck. then uses shuffle() to shuffle
int rand_gen(int count); // obtain a random number in [0, count] (count is the length of the array) use the following function
void swap(card deck[], int i, int j); //swaps 2 the contents of the ith elementh with the jth element
void shuffle(card deck[],int sizeDeck, int swaptimes); // shuffles the cards swapTimes amount
void printDashOrAsterisk(int value);    //prints dash or asterisks
void printPlayerWins(int value);    //prints the player who won


#endif /* functions_h */
