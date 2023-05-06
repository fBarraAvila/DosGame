//
//  Double Link functions.c
//  ECE Final Project draft
//
//  Created by Franco Barra on 4/27/23.
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#include "Double Link functions.h"
#include "functions.h"

void deleteMember(card *p, card **hl, card **hr){ // deletes node from link at adress *p
    if (p == *hl){
        *hl = p->next;
    }
    else{
        p->previous->next = p->next;
    }
    if (p == *hr){
        *hr = p->previous;
    }
    else{
        p->next->previous = p->previous;
    }
}
void addMember2(card *p, card **hl, card **hr){ //  adds node to link at adress *p
    card *temp;
    temp = (card*)malloc(sizeof(card));
//    printf("Enter the name:");
//    scanf("%s", temp->name);
//    printf("Enter the age:");
//    scanf("%*c%d", &temp->age);
    
    if (*hl == NULL){             // if list is empty
        *hl = temp;
        *hr = temp;
        temp->next = NULL;
        temp->previous = NULL;
    }
    else if(p->next == NULL){     // add a node at the end of the list
        //temp->previous = p;
        //temp->next = NULL;
        //p->next = temp;
        p->next = temp;
        temp->previous = p;
        *hr = temp;
        temp->next = NULL;
    }
    else{                         // add a node somwhere in the middle
//        temp->previous = p;
//        temp->next = p->next;
//        p->next->previous = temp;
//        p->next = temp;               //temp-> 3
        temp->next = p->next;           //[1,2,3]  [2]
        p->next->previous = temp;
        temp->previous = p;
        p->next = temp;
    }
}

void copyCardToPlayer(card deck[], card **hr){  //copies array element to node
    strcpy((*hr)->color, deck->color);
    (*hr)->value = deck->value;
    strcpy((*hr)->action, deck->action);
    
}

void printList(card *head){                     // prints link, staring from *head position
    while(head !=NULL){
        if(head->value == 11 ){
            printf("[# %s], ", head->color);
        }
        else if(head->value == 2){
            printf("[%d multicolor], ", head->value);
        }
        else{
            printf("[%d %s], ", head->value, head->color);
        }
        head = head->next;
    }

}

//New functions
int countNumCards(card *head){  // counts the number of cards in a link
    int count = 0;
    while(head != NULL){
        count++;
        head = head->next;
    }
    return count;
}
card *LocationCard(card *headLeft, int position){   // iterates througha a loop "position" times, then returns the adress of the correspoinding node
    card *temp = headLeft;
    for(int i = 0; i < position; i++){
        temp = temp->next;
    }
    return temp;
}

int checkMatch(card *playercard, card *playercard2, card *centerLine){  // function recives as arguments 3 nodes, and check if they match contents
    //return 0 if they dont match
    //return 1 if they match #'s
    //return 2 if they match #'s AND colors(single color match)
    //return 3 if 2 cards, when added up, match centerline card # and color
    
    
    //2 anycolor
    // #(11) color
    
    int numMatch = 0;
    int colorMatch = 0;
    //if player only chooses 1 card
    if( playercard2 == NULL){
        if(playercard->value == centerLine->value || strcmp(playercard->action, "anynumber") == 0){
            numMatch = 1;
            if((strcmp(playercard->color, centerLine->color) == 0) || (strcmp(playercard->action, "anycolor") == 0) || (strcmp(centerLine->action, "anycolor") == 0)){
                colorMatch = 1;
            }
//            else if((strcmp(playercard->action, "anycolor") == 0)){
//                colorMatch = 1;
//            }
        }
    }
    
    //if player chooses 2 cards
    else{
        //check if sum of 2 cards sum = centerline
        //check if colors of 2 cards are equal to centerline
        
        //if both cards are anynumber AND centerline is greater than 1
        if(strcmp(playercard->action, "anynumber")== 0 && strcmp(playercard2->action, "anynumber")== 0 && centerLine->value != 1){
            numMatch = 1;
        }
        //if at leadt 1 card is anynuber AND the centerline card is greater than card with number vallue
        else if((strcmp(playercard->action, "anynumber") == 0 && playercard2->value < centerLine->value) || (strcmp(playercard2->action, "anynumber") == 0 && playercard->value < centerLine->value)){
            numMatch = 1;
        }
        else{
            if(playercard->value + playercard2->value == centerLine->value){
                numMatch = 1;
            }
        }
        if(numMatch > 0){   //FIXME!!! 2 multicolor + 6 yellow != 8 yellow???
            if(((strcmp(playercard->color, centerLine->color) == 0) && (strcmp(playercard2->color, centerLine->color) == 0)) || ((strcmp(playercard->action, "anycolor") == 0) && (strcmp(playercard2->action, "anycolor") == 0)) || ((strcmp(playercard->action, "anycolor") == 0) && strcmp(playercard2->color, centerLine->color) == 0) || ((strcmp(playercard2->action, "anycolor") == 0) && strcmp(playercard->color, centerLine->color) == 0)        ){
                colorMatch = 2;
            }
//            else if(((strcmp(playercard->action, "anycolor") == 0) && strcmp(playercard2->color, centerLine->color))){
//                colorMatch = 2;
//            }
//            else if(((strcmp(playercard2->action, "anycolor") == 0) && strcmp(playercard->color, centerLine->color) == 0)){
//                colorMatch = 2;
//            }
        }
    }
    return numMatch + colorMatch;
}


void PlayersTurnActions(card **playerCardsL, card **playerCardsR, card **centerLineL, card **centerLineR, int bonusActions[]){
    /*
     recives as arguments the current players turn, the centerline and an array "bonusAction", that will hold a value(0-3). The function iterates as many times as there are cards in the center line. Then asks the player how many cards and which cards they want to play on the current centerline card. It deletes acconrdinly and prints out the current centerline and player's card
     */
    
    //HEADL OR R = CENTERLINE     PLAYERL OR R = PLAYER CARD
    card *tempCent = *centerLineL; // center line
    //card *tempPlayer = playerLeft;
    card *deleteLocation = NULL, *deleteLocation2 = NULL;
    int numCardsToPlay, selectedCardNum, selectedCardNum2;
    //countNumCards counts the number of cards
    int centerLineNum = countNumCards(*centerLineL);    //reads the number of cards in the centerline to create a loop that will iterate that many times
    int cardsLeftInHand = countNumCards(*playerCardsL);
    int timesPlayerSkipCenterline = 0;
    //int bonusActions[centerLineNum]; //FIXME!!!!reset the array
    // 1st)
    for(int i = 0; i < centerLineNum; i++){
        card *selectedCLCardMatchL =NULL,  *selectedCLCardMatchR = NULL;
        addMember2(selectedCLCardMatchL, &selectedCLCardMatchL, &selectedCLCardMatchL);
        copyPointerToPointer(&selectedCLCardMatchL,tempCent);
        
        
        if(cardsLeftInHand == 0){
            //printf("Player WINS!!");
            break;
        }
        bonusActions[i] = 0;
        printf("\n\n");
        printf("How many cards do you want to play on ");
        printf("%s %d: ", tempCent->color, tempCent->value);
        scanf("%d", &numCardsToPlay);
        
        
        card *temp = positionOfFirstMatchHand1vsHand2(*playerCardsL, selectedCLCardMatchL);
        //FIXME!!! check that #cards to be play is <= cardsLeftInHand
        if(temp == NULL){
            while(numCardsToPlay != 0){
                printf("NO cards match choose 0\n");
                scanf("%d", &numCardsToPlay);
            }
        }
        else{
            while(numCardsToPlay > cardsLeftInHand || numCardsToPlay > 2){
                printf("Max number of cards that can be play is 2. Check your hand and choose less\n");
                scanf("%d", &numCardsToPlay);
            }
        }
        
        
        
        //player chooses 0 cards to be played
        if(numCardsToPlay == 0){
            //DO NOTHING
            //GO TO NEXT CARD
            //continue;
            /* keep track of number of times the player decides to skip, if they skip all iterations of the loop, it means that they dont have a card to match and they need to draw a card. 2 OPTIONS
             1) THE CARD MATCHES AND THE PLAYER CAN EITHER PLAY IT OR HOLD IT
             2) THE CARD DOESNT MATCH AND THE PLAYER ADDS IT TO THE CENTERLINE
             */
            timesPlayerSkipCenterline++;
            
        }
        
        //player chooses 1 cards to be played
        else if(numCardsToPlay == 1){
            printf("\nSelect a card from 1-%d: ",cardsLeftInHand);
            scanf("%d", &selectedCardNum);
            //new
            while(selectedCardNum > cardsLeftInHand){
                printf("Incorrect input, Select a card from 1-%d: ", cardsLeftInHand);
                scanf("%d", &selectedCardNum);
                //FIXME!!! check if they can even match a number of cards
            }
            //

            deleteLocation = LocationCard(*playerCardsL, selectedCardNum - 1);   //passing location of node to be deleted      //changing from tempPlayer to playerleft
            
            
            //FIXME!!! check that at least card # matches centerLine card
            bonusActions[i] = checkMatch(deleteLocation, NULL, tempCent);
            while(bonusActions[i] == 0){
                printf("Cards don't match choose again a card from 1-%d: \n",cardsLeftInHand);
                scanf("%d", &selectedCardNum);
                deleteLocation = LocationCard(*playerCardsL, selectedCardNum - 1);
                bonusActions[i] = checkMatch(deleteLocation, NULL, tempCent);
            }

            
            //Discards card from hand and centerline
            deleteMember(deleteLocation, &(*playerCardsL), &(*playerCardsR));    //deletes card from players hand
            printf("Player's hand is\n");
            printList(*playerCardsL);  //prints hand
            
            printf("\nCenterline\n");
            deleteMember(tempCent, &(*centerLineL), &(*centerLineR));  //deletes centerline card
            printList(*centerLineL);
        }
        
        //player chooses 2 cards to be played
        else if(numCardsToPlay == 2){
            printf("\nSelect a card from 1-%d: ",cardsLeftInHand);
            scanf("%d,%d", &selectedCardNum, &selectedCardNum2);
            //new
            while(selectedCardNum > cardsLeftInHand){
                printf("Incorrect input, select 2 cards from 1-%d: ", cardsLeftInHand);
                scanf("%d,%d", &selectedCardNum, &selectedCardNum2);
            }

            //
            deleteLocation = LocationCard(*playerCardsL, selectedCardNum - 1);   //passing location of node to be deleted
            deleteLocation2 = LocationCard(*playerCardsL, selectedCardNum2 - 1);  //passing second location of node to be deleted
            
            //checks if cards are the same
            //1)location1 == location2
            //2) location 1 != location 2  BUT checkMatch = 0

            if(deleteLocation != deleteLocation2){
                bonusActions[i] = checkMatch(deleteLocation, deleteLocation2, tempCent);
            }
            while(bonusActions[i] == 0){
                printf("Cards don't match choose again a card from 1-%d: \n",cardsLeftInHand);
                scanf("%d,%d", &selectedCardNum, &selectedCardNum2);
                deleteLocation = LocationCard(*playerCardsL, selectedCardNum - 1);
                deleteLocation2 = LocationCard(*playerCardsL, selectedCardNum2 - 1);
                //check that card 1 and 2 are not the same
                if(deleteLocation != deleteLocation2){
                    bonusActions[i] = checkMatch(deleteLocation, deleteLocation2, tempCent);
                }
            }
            
            
            //Discards cards from hand and card from center line
            deleteMember(deleteLocation, &(*playerCardsL), &(*playerCardsR));    //deletes card from players hand
            deleteMember(deleteLocation2, &(*playerCardsL), &(*playerCardsR));    //deletes 2nd card from players hand
            printf("\nPlayers hand is:\n");
            printList(*playerCardsL);
            
            printf("\nCenterline\n");
            deleteMember(tempCent, &(*centerLineL), &(*centerLineR));  //deletes centerline card
            printList(*centerLineL);
        }
        tempCent = tempCent->next;
        cardsLeftInHand = countNumCards(*playerCardsL);
    }
}

void doBonusActions(int bonusActions[],int size1, card **currentPlayerL, card **currentPlayerR, card **otherPlayerL, card **otherPlayerR, card deck[], int *deckIndex, card **centerLineLeft, card **centerLineRight){
    /*
     This function takes as arguments the bonusAciton array, which holds the type of bonus action that will be perform. Then the fuction iterates as many times as the length of the bonusActions array. Then if the bonusaction[i] is greater than 1, it will ask the player to add a card from their hand to the center list. Then if the bonusaction[i] ==3, it will perform an additional task of adding a card to the otherPlayer hand
     */
    int cardsLeftInHand =countNumCards(*currentPlayerL);
    int selectedCardNum;
    card *deleteLocation = NULL;
    for(int i = 0; i < size1; i++ ){
        cardsLeftInHand =countNumCards(*currentPlayerL);
        //SINGLE MATCH
        if(bonusActions[i] >= 2){
            printf("You color matched one card from the center row\n");
            printf("Select one additional card from 1-%d to place to the center row:", cardsLeftInHand);
            scanf("%d", &selectedCardNum);
            
            while(selectedCardNum > cardsLeftInHand){
                printf("Incorrect input, select one additional card from 1-%d to place to the center row:", cardsLeftInHand);
                scanf("%d", &selectedCardNum);
            }
            
            //delete card from player. add card to centerline
            deleteLocation = LocationCard(*currentPlayerL, selectedCardNum - 1);
            deleteMember(deleteLocation, &(*currentPlayerL), &(*currentPlayerR));
            addMember2(*centerLineRight, &(*centerLineLeft), &(*centerLineRight)); //add to the end of centerline [1,2,3,4]
            copyPointerToPointer(&(*centerLineRight), deleteLocation);
            printf("\nPlayers hand is:\n");
            printList(*currentPlayerL);     //new
            
        }
        if(bonusActions[i] == 3){
            *deckIndex = *deckIndex + 1;
            addMember2(*otherPlayerR, &(*otherPlayerL), &(*otherPlayerR));
            copyCardToPlayer(&(deck[*deckIndex]), &(*otherPlayerR));
        }
    }
}

void copyPointerToPointer(card **destination, card *source){    // copies content of pointer to another pointer
    strcpy((*destination)->color, source->color);
    (*destination)->value = source->value;
    strcpy((*destination)->action, source->action);
}

void checkCenterLine(int *centerLineNumCards, int *deckIndex, card deck[], card **centerLineLeft, card **centerLineRight){  //checks if centerline has a mininum of 2 cards. if not, it takes from deck and adds it to the centerline
    while(*centerLineNumCards < 2){
        *deckIndex = *deckIndex + 1;
        addMember2(*centerLineRight, &(*centerLineLeft), &(*centerLineRight));
        copyCardToPlayer(&deck[*deckIndex], &(*centerLineRight));
        *centerLineNumCards = *centerLineNumCards + 1;
    }
}

card *positionOfFirstMatchHand1vsHand2(card *hand1L, card *hand2L){ // gives the adress of the first match. it compares when player tries to match 1 OR 2 cards
    //int hand2Num =countNumCards(hand2L);
    
    /*
     FIXME!!!! Change function to take an extra argument, 1 OR 2, then create an if-else statement to check if the player chose 1 card or 2 cards
     */
    
    card *temp1 = hand1L;
    card *temp2 = hand2L;
    int match = 0;
    while(temp1 != NULL){  //players hand
        while(temp2 != NULL){  //centerline
            match = checkMatch(temp1, NULL, temp2);     //return temp1 here
            if(match > 0){
                break;
            }
            temp2 = temp2->next;
        }
        temp2 = hand2L;
        if(match > 0){
            break;
        }
        temp1 = temp1->next;
    }
    
    //checks for 2
    card *temp3 = hand1L;
    card *temp4 = hand2L;
    while(temp3 != NULL){  //players hand
        temp4 = hand2L;
        while(temp4 != NULL){  //centerline
            card *temp5 = hand1L;
            while (temp5 != NULL) {
                if(temp3 != temp5 && checkMatch(temp3, temp5, temp4) > 0){  //return temp3 here
                    return temp3;
                }
                temp5 = temp5->next;
            }
            temp4 = temp4->next;
        }
        temp3 = temp3->next;
        
    }
    /*
     int checkMatch(card *playercard, card *playercard2, card *centerLine){
         //return 0 if they dont match
         //return 1 if they match #'s
         //return 2 if they match #'s AND colors(single color match)
         //return 3 if 2 cards, when added up, match centerline card # and color
     */
    return temp1;
}

void PlayerNoActionsTurn(card deck[], int *deckIndex, int bonusActions[], int size1, card **currentPlayerL, card **currentPlayerR, card **otherPlayerL, card **otherPlayerR, card **centerLineLeft, card **centerLineRight){
    /*
     Checks the bonusActions[] array to see if player decidec OR couldnt play cards during their turn. If player couldnt play, it gives the player a card from the deck, chekcs if the new card can be use to play. if it can, it ask teh player if they want to play it, otherwise, it asks the player to put down a card to the centerline.
     if player decided not play a card during their turn, it stills gives the player a card from the deck and then it checks if they can make a match. if they can it ask the player if they want to. if they choose not to, the player needs to put down a card to the centerline
     */

    //CHECK TO SEE IF PLAYER COULDNT MATCH A CARD TO ANY OF THE CENTER DECK
    int sizeBonus = countNumCards(*centerLineLeft);
    int cardsLeftInHand = countNumCards(*currentPlayerL);
    int newBonus[sizeBonus];
    int checkForNoMatch = 0;
    int selectedCardNum;
    card *deleteLocation = NULL;
    int centerLineNumCards;
    char userInput;
    for(int i = 0; i < size1; i++){
        checkForNoMatch = checkForNoMatch + bonusActions[i];
    }
    if( checkForNoMatch == 0){
        //check if they skiped, but they do have a card that matches
        *deckIndex = *deckIndex + 1;
        printf("\nNew card from deck is : "); // deck[*deckIndex].value, deck[*deckIndex].color);
        if(deck[*deckIndex].value == 11 ){
            printf("[# %s] ", deck[*deckIndex].color);
        }
        else if(deck[*deckIndex].value == 2){
            printf("[%d multicolor] ", deck[*deckIndex].value);
        }
        else{
            printf("[%d %s] ", deck[*deckIndex].value, deck[*deckIndex].color);
        }
        printf("\n");
        
        addMember2(*currentPlayerR, &(*currentPlayerL), &(*currentPlayerR));
        copyCardToPlayer(&(deck[*deckIndex]), &(*currentPlayerR));
        cardsLeftInHand =countNumCards(*currentPlayerL);    //update players hand

        //1)they have a card that matches center line
        if(positionOfFirstMatchHand1vsHand2(*currentPlayerL, *centerLineLeft) != NULL){
            //ask player if they want to play y or n
            printf("\nDo you want to match a card\n (y/n)");
            scanf("%*c%c", &userInput);
            while (userInput != 'y' && userInput != 'n'){
                printf("\nDo you want to play a card\n (y/n)");
                scanf("%*c%c", &userInput);
            }
            //1) says yes
            if(userInput == 'y'){
                int temp =cardsLeftInHand;
                //player has to play a card. runs until player plays a card
                while(temp >=  cardsLeftInHand){
                    //PlayersTurnActions(card **playerCardsL, card **playerCardsR, card **centerLineL, card **centerLineR, int bonusActions[])  //????????
                    //1)PlayersTurnActions [0,1/2, , , , ]
                    PlayersTurnActions(&(*currentPlayerL), &(*currentPlayerR),&(*centerLineLeft), &(*centerLineRight), newBonus);
                    temp =countNumCards(*currentPlayerL);
                    //2)checkCenterLine
                    centerLineNumCards = countNumCards(*centerLineLeft);
                    checkCenterLine(&centerLineNumCards, &(*deckIndex), deck, &(*centerLineLeft), &(*centerLineRight));
                    //3)doBonusActions
                    doBonusActions(newBonus, sizeBonus, &(*currentPlayerL), &(*currentPlayerR), &(*otherPlayerL), &(*otherPlayerR), deck, &(*deckIndex), &(*centerLineLeft), &(*centerLineRight));
                    centerLineNumCards = countNumCards(*centerLineLeft);
                }
            }
            //2) says no
            else{
                printf("\nSelect a card from 1-%d put on centerline:",cardsLeftInHand);
                scanf("%d", &selectedCardNum);
                //
                while(selectedCardNum > cardsLeftInHand){
                    printf("Incorrect input, Select a card from 1-%d:", cardsLeftInHand);
                    scanf("%d", &selectedCardNum);
                }
                //
                deleteLocation = LocationCard(*currentPlayerL, selectedCardNum - 1);   //passing location of node to be deleted      //changing from tempPlayer to playerleft
                //delete from players hand
                deleteMember(deleteLocation, &(*currentPlayerL), &(*currentPlayerR));
                // add to centerline
                addMember2(*centerLineRight, &(*centerLineLeft), &(*centerLineRight)); //add to the end of centerline [1,2,3,4]
                copyPointerToPointer(&(*centerLineRight), deleteLocation);
            }

        }
        //2)they dont have a card that matches centerline, they need to play a card from their hand to the center line
        else if(positionOfFirstMatchHand1vsHand2(*currentPlayerL, *centerLineLeft) == NULL){
            printf("\nSelect a card from 1-%d:",cardsLeftInHand);
            scanf("%d", &selectedCardNum);
            //
            while(selectedCardNum > cardsLeftInHand){
                printf("Incorrect input, Select a card from 1-%d:", cardsLeftInHand);
                scanf("%d", &selectedCardNum);
            }
            //
            deleteLocation = LocationCard(*currentPlayerL, selectedCardNum - 1);   //passing location of node to be deleted      //changing from tempPlayer to playerleft
            //delete from players hand
            deleteMember(deleteLocation, &(*currentPlayerL), &(*currentPlayerR));
            // add to centerline
            addMember2(*centerLineRight, &(*centerLineLeft), &(*centerLineRight)); //add to the end of centerline [1,2,3,4]
            copyPointerToPointer(&(*centerLineRight), deleteLocation);

        }
    }
}

void countRoundPoints(int playerNum, card *otherPlayerL){   //counts the number of points for the player
    int sum = 0;
    while(otherPlayerL != NULL){
        if(otherPlayerL->value ==2){
            sum = sum + 20;
        }
        else if (otherPlayerL->value == 11){
            sum = sum + 40;
        }
        else{
            sum = sum + otherPlayerL->value;
        }
        otherPlayerL = otherPlayerL->next;
    }
    printf("\nPlayer %d score: %d", playerNum, sum);
}
