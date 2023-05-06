//
//  Double Link functions.h
//  ECE Final Project draft
//
//  Created by Franco Barra on 4/27/23.
//

#ifndef Double_Link_functions_h
#define Double_Link_functions_h

#include <stdio.h>
#include "functions.h"


void deleteMember(card *p, card **hl, card **hr);
void addMember2(card *p, card **hl, card **hr);
void copyCardToPlayer(card deck[], card **hr);
void printList(card *head);

//New Functions
void PlayersTurnActions(card **playerCardsL, card **playerCardsR, card **centerLineL, card **centerLineR, int bonusActions[]);  //all actions taken by 1 player in 1 turn
int countNumCards(card *head);  // counts the number of cards in a link
card *LocationCard(card *headLeft, int position);   // iterates througha a loop "position" times, then returns the adress of the correspoinding node
int checkMatch(card *playercard, card *playercard2, card *centerLine);  // checks if cards match and returns 0 for no match, 1 for # match, 2 for single color match and 3 for double color match
void doBonusActions(int bonusActions[],int size1, card **currentPlayerL, card **currentPlayerR, card **otherPlayerL, card **otherPlayerR, card deck[], int *deckIndex, card **centerLineLeft, card **centerLineRight);
   //performs bonuses
void copyPointerToPointer(card **destination, card *source);
void checkCenterLine(int *centerLineNumCards, int *deckIndex, card deck[], card **centerLineLeft, card **centerLineRight);  // checks if centerline is at least 2, if not, it adds from deck to centerline
card *positionOfFirstMatchHand1vsHand2(card *hand1L, card *hand2L); // returns the adress of the first match between 2 links
void PlayerNoActionsTurn(card deck[], int *deckIndex, int bonusActions[], int size1, card **currentPlayerL, card **currentPlayerR, card **otherPlayerL, card **otherPlayerR, card **centerLineLeft, card **centerLineRight);    //perform all starting actions for the current player
void countRoundPoints(int playerNum, card *otherPlayerL);   //returns points for the round






#endif /* Double_Link_functions_h */
