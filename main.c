//
//  main.c
//  ECE Final Project draft
//
//  Created by Franco Barra on 4/25/23.
//

#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include <time.h>
#include <string.h>

#define SIZEDECK 108

#include "functions.h"
#include "Double Link functions.h"

//void checkCenterLine(int *centerLineNumCards, int *deckIndex, card deck[], card **centerLineLeft, card **centerLineRight){
//    while(*centerLineNumCards < 2){
//        //FIXME: check if there are any more cards to add
//        *deckIndex = *deckIndex + 1;
//        addMember2(*centerLineRight, &(*centerLineLeft), &(*centerLineRight));
//        copyCardToPlayer(&deck[*deckIndex], &(*centerLineRight));
//        *centerLineNumCards = *centerLineNumCards + 1;
//    }
//}


int main(int argc, const char * argv[]) {
    // insert code here...
    
    
    
    /* GAME STARTS!!!!!*/
    printf("Let's Play a Game of DOS\n");
    printf("Press 1 to shuffle the DOS deck or 2 to load a deck from a file:\n");
    int shuffleOrload;
    scanf("%d%*c", &shuffleOrload);
    while(shuffleOrload != 1 && shuffleOrload != 2){
        printf("Press 1 to shuffle the DOS deck or 2 to load a deck from a file:\n");
        scanf("%d%*c", &shuffleOrload);
    }
    card deck[SIZEDECK];
    /* if player presses 1, file is created and shuffle, else its load*/
    if(shuffleOrload == 1){
        //shuffle function
        printf("The deck is shuffled. Press any key to deal cards\n");
        createDeckAndShuffle(deck, SIZEDECK);
    }
    else if(shuffleOrload == 2){
        //read deck from file
        printf("The deck is loaded. Press any key to deal cards\n");
        readFromFile(deck, SIZEDECK);
    }
    
    printf("Press ENTER to continue...");    //FIXME needs to be any key
    //system("pause");
    getchar();
    
    //TESTING
    //print FULL DECK
    printFullDeck(deck, SIZEDECK);
    int count = 0;
    for(int i = 0; i < SIZEDECK; i++){
        count++;
    }
//    printf("\nCount: %d\n", count);
    
    
    
    /*
     deftype struct player{
        card *headL, *headR
     }
     //how many players = numOfPlayers
     player Players[numOfPlayers]
     
     */
    
    
    /*
     *
     *
     SET UP THE PLAYER'S HAND AND CENTER LINE
     *
     *
     */
    //create plaers hand
    card *player1HandLeft = NULL, *player1HandRight = NULL;
    card *player2HandLeft = NULL, *player2HandRight = NULL;
    int deckIndex = 0, j;
    //TOTAL cards dealt to players = 14. 7 per player
    int player1NumCards = 0, player2NumCards = 0;
    for(j = 0; j < 14; j++){    //7 * numOfPlayers
        deckIndex = j;
        if(j % 2 == 0){
            //Player 1
            addMember2(player1HandRight, &player1HandLeft, &player1HandRight);
            copyCardToPlayer(&deck[deckIndex], &player1HandRight);
            player1NumCards++;
        }
        else{
            //Player 2
            addMember2(player2HandRight, &player2HandLeft, &player2HandRight);
            copyCardToPlayer(&deck[deckIndex], &player2HandRight);
            player2NumCards++;
        }
    }
    
    /*
     *
     *
     ROUNG STARTS
     *
     *
     */
    card *centerLineLeft = NULL, *centerLineRight = NULL;
    int centerLineNumCards = 0; //int playersTurn = 1;

    //start loop for game. game will be played as long as every player has at leat 1 card in their hand
    while(player1NumCards != 0 && player2NumCards != 0){   //&& deckIndex != 108
        
        printDashOrAsterisk(2);
        printf("Player 1 turn begins\n\n");
        //create cdnter line. check if center line has a minimun of 2 cards
        checkCenterLine(&centerLineNumCards, &deckIndex, deck, &centerLineLeft, &centerLineRight);
        //centerLineNumCards = countNumCards(centerLineLeft);
//        int *bonusActions = (int*)malloc(centerLineNumCards * sizeof(int));
        int bonusActions[centerLineNumCards];
        int bonusActionsLength = centerLineNumCards;
        
        
        //PlayersTurnActions()
        //void PlayersTurnActions(card **playerCardsL, card **playerCardsR, card **centerLineL, card **centerLineR);  //all actions taken by 1 player in 1 turn
        //print centerline and player hand
        printf("Centerline is:\n");
        printList(centerLineLeft);
        printf("\n\n");
        printf("Players hand is:\n");
        //if (playersturn = 1)
        printList(player1HandLeft);
        PlayersTurnActions(&player1HandLeft, &player1HandRight, &centerLineLeft, &centerLineRight, bonusActions);
        //count cards in the centerline and players hand
        centerLineNumCards = countNumCards(centerLineLeft);
        player1NumCards = countNumCards(player1HandLeft);
        if(player1NumCards == 0){
            printPlayerWins(1);
            //FIXME!!! count players point
            countRoundPoints(1, player2HandLeft);
            break;
        }
        checkCenterLine(&centerLineNumCards, &deckIndex, deck, &centerLineLeft, &centerLineRight);

//        printf("\n\n\nCenter line num: %d\n", centerLineNumCards);
        
        int bonusActionSum = 0;
        for(int k = 0; k < bonusActionsLength; k++ ){
            bonusActionSum = bonusActionSum + bonusActions[k];
        }
        
        // if -> Part 2 checks for player no action
        //PlayerNoActionsTurn(card deck[], int *deckIndex, int bonusActions[], int size1, card **currentPlayerL, card **currentPlayerR, card **otherPlayerL, card **otherPlayerR, card **centerLineLeft, card **centerLineRight)
        if(bonusActionSum == 0){
            PlayerNoActionsTurn(deck, &deckIndex, bonusActions, bonusActionsLength, &player1HandLeft, &player1HandRight, &player2HandLeft, &player2HandRight, &centerLineLeft, &centerLineRight);
            
        }
        //else -> 3rd part
        //doBonusActions(int bonusActions[], card **currentPlayerL, card **currentPlayerR, card **otherPlayerL, card **otherPlayerR, card deck[], int *deckIndex, card **centerLineLeft, card **centerLineRight)
        else{
            doBonusActions(bonusActions, bonusActionsLength, &player1HandLeft, &player1HandRight, &player2HandLeft, &player2HandRight, deck, &deckIndex, &centerLineLeft, &centerLineRight);
        }
        centerLineNumCards = countNumCards(centerLineLeft);
        player1NumCards = countNumCards(player1HandLeft);
        if(player1NumCards == 0){
            printPlayerWins(1);
            countRoundPoints(1, player2HandLeft);
            break;
        }
        
        printf("\n");
        printf("Centerline is:\n");
        printList(centerLineLeft);
        printf("\n\n");
//        printf("Players hand is:\n");
//        printList(player1HandLeft);
        // FIXME!!! SAY DOS IN PALYER ACTIOSN
        printf("\nEnd of turn\n\n");
        
        
        
        
        
        
        /*
         *
         PLAYER 2 TURN
         *
         */
        
        
        
    
        
        
        printDashOrAsterisk(2);
        printf("Player 2 turn begins\n");
         //create cdnter line. check if center line has a minimun of 2 cards
         checkCenterLine(&centerLineNumCards, &deckIndex, deck, &centerLineLeft, &centerLineRight);
         //centerLineNumCards = countNumCards(centerLineLeft);
 //        int *bonusActions = (int*)malloc(centerLineNumCards * sizeof(int));
        int bonusActionsPlayer2[centerLineNumCards];
         int bonusActionsLengthPlayer2 = centerLineNumCards;
         
         
         //PlayersTurnActions()
         //void PlayersTurnActions(card **playerCardsL, card **playerCardsR, card **centerLineL, card **centerLineR);  //all actions taken by 1 player in 1 turn
         //print centerline and player hand
         printf("Centerline is:\n");
         printList(centerLineLeft);
         printf("\n\n");
         printf("Players hand is:\n");
         printList(player2HandLeft);
         PlayersTurnActions(&player2HandLeft, &player2HandRight, &centerLineLeft, &centerLineRight, bonusActionsPlayer2);
         //count cards in the centerline and players hand
         centerLineNumCards = countNumCards(centerLineLeft);
        player2NumCards = countNumCards(player2HandLeft);
         if(player2NumCards == 0){
             printPlayerWins(2);
             countRoundPoints(2, player1HandLeft);
             break;
         }
         checkCenterLine(&centerLineNumCards, &deckIndex, deck, &centerLineLeft, &centerLineRight);

         printf("\n\n\nCenter line num: %d\n", centerLineNumCards);
         
         int bonusActionSumPlayer2 = 0;
         for(int k = 0; k < bonusActionsLengthPlayer2; k++ ){
             bonusActionSumPlayer2 = bonusActionSumPlayer2 + bonusActionsPlayer2[k];
         }
         
         // if -> Part 2 checks for player no action
         //PlayerNoActionsTurn(card deck[], int *deckIndex, int bonusActions[], int size1, card **currentPlayerL, card **currentPlayerR, card **otherPlayerL, card **otherPlayerR, card **centerLineLeft, card **centerLineRight)
         if(bonusActionSumPlayer2 == 0){
             PlayerNoActionsTurn(deck, &deckIndex, bonusActionsPlayer2, bonusActionsLengthPlayer2, &player2HandLeft, &player2HandRight, &player1HandLeft, &player1HandRight, &centerLineLeft, &centerLineRight);
             
         }
         //else -> 3rd part
         //doBonusActions(int bonusActions[], card **currentPlayerL, card **currentPlayerR, card **otherPlayerL, card **otherPlayerR, card deck[], int *deckIndex, card **centerLineLeft, card **centerLineRight)
         else{
             doBonusActions(bonusActionsPlayer2, bonusActionsLengthPlayer2, &player2HandLeft, &player2HandRight, &player1HandLeft, &player1HandRight, deck, &deckIndex, &centerLineLeft, &centerLineRight);
         }
         centerLineNumCards = countNumCards(centerLineLeft);
        player2NumCards = countNumCards(player2HandLeft);
        if(player2NumCards == 0){
            printPlayerWins(2);
            countRoundPoints(2, player1HandLeft);
            break;
        }
         
         printf("Centerline is:\n");
         printList(centerLineLeft);
         printf("\n\n");
         printf("Players hand is:\n");
        printList(player2HandLeft);
        printf("\nEnd of turn\n\n");
         
        
        
        
        
        
        
        

    }
    printf("GAME ENDS");

    
    return 0;
}
