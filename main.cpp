/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Zachary Propert
 *
 * Created on March 8, 2016, 8:06 PM
 */
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <fstream>

using namespace std;

/*
 * Baccarat Game Simulator
 * 
 * Randomly generates cards and deals to the dealer and player. If the hand total
 * is 7 or 8 the a third card is not drawn. If the dealers hand is more than the players 
 * the dealer does not draw a third card. Starting balance is $1000, each hand $10 is bet.
 * 
 * 
 */
void play(ofstream &output,int &pCard1,int &pCard2,int &pCard3,int &dCard1,int &dCard2,int &dCard3,
        int &dScore,int &pScore,int &bal ,int &who, int &wins, int &ties, int &pWin, int &dWin, int &pTie);
int deal();
int Total(int Card1, int Card2);
int Decide(ofstream &output,int &dScore, int &pScore,int &dCard3, int &pCard3, int dCard1, int dCard2, int pCard1, int pCard2);
void win(ofstream &output,int dScore, int pScore, int who, int &bal, int &wins, int &ties, int &pWin, int &dWin, int &pTie);
int bet(ofstream &output,int &who, int &bal);


int main()
{
    ofstream output; 
    output.open("baccaratHands.txt");
    
    srand(time(NULL));
    int pCard1, pCard2, pCard3, dCard1, dCard2, dCard3, dScore, pScore, who, bal = 1000;
    int wins = 0, ties = 0, netWin, netLoss, temp=1000, pWin = 0, dWin = 0, pTie = 0;
    for(int x =0; x < 1000; x++)
    {
    play(output, pCard1, pCard2, pCard3, dCard1, dCard2, dCard3, dScore, pScore, bal ,who, wins, ties, pWin, dWin, pTie);
    if(bal<0)
    {
        temp = x;
        x=1000;
        cout<<"You played "<<temp<<" hands, unfortunately you are out of money and can no longer continue."<<endl;
    }
    }
    
    netWin = 10 * wins + ties * 80;
    netLoss = (temp-(wins+ties))*10;
    cout<<"Starting Balance was $1000"<<endl;
    cout<<"Net Wins: $"<<netWin<<" ||  Net loss: $"<<netLoss<<" || Net Earnings: $"<<netWin-netLoss<<endl;
    cout<<"Bets Won: "<<wins<<" || Tie Bets Won: "<<ties<<" || Bets Loss: "<<temp-(wins+ties)<<endl;
    cout<<"Overall hands won by PLAYER: "<<pWin<<"\nOverall hands won by DEALER: "<<dWin<<"\nOverall TIES: "<<pTie<<endl;
    cout<<"\nRuns outputed to baccaratHands.txt"<<endl;
    output.close();
    return 0;
}
void play(ofstream &output,int &pCard1,int &pCard2,int &pCard3,int &dCard1,int &dCard2,int &dCard3,int &dScore,int &pScore,int &bal ,int &who, int &wins, int &ties, int &pWin, int &dWin, int &pTie)
{ 
    pCard1 = deal(), pCard2 = deal(), pCard3 = 0,
        dCard1 = deal(), dCard2 = deal(), dCard3 = 0,
    pScore = Total(pCard1, pCard2);
    dScore = Total(dCard1, dCard2);
    output<<"\n\nPlayer's Current Balance: "<<bal<<endl;
    bet(output, who, bal); //outputs who the bet was placed on
    Decide(output, dScore, pScore, dCard3, pCard3, dCard1, dCard2, pCard1, pCard2);
    output<<"Player's Total: "<<pScore<<endl;
    output<<"Dealer's Total: "<<dScore<<endl;
    win(output, dScore, pScore, who, bal, wins, ties, pWin, dWin, pTie );   
}

 int deal() //randomly deals a card
{
    int card;
    card = rand()%14;
    
    if(card > 9)
        card = 0;
    
    return card;
}
 
int Total(int Card1,int Card2) //totals two cards
{
    int Total;
    Total = Card1 + Card2;
    
    if(Total > 9)
        Total = Total % 10;
    
    return Total;
}

void win(ofstream &output,int dTotal, int pTotal, int who, int &bal, int &wins, int &ties, int &pWin, int &dWin, int &pTie) //finds winner
{
     if(dTotal < pTotal){
        output<<"The PLAYER won the hand.\n";
        pWin++;
        if(who == 1)
        {
            wins++;
            bal = bal + 20;
            output<<"The player has won $10!";
        }
    }
    if( dTotal > pTotal){
         output<<"The DEALER won the hand.\n";
         dWin++;
        if(who == 2)
        {
            wins++;
            bal = bal + 20;
            output<<"The player has won $10!";
        }
    }    
    if(dTotal == pTotal){
         output<<"The hand was a TIE!\n";
         pTie++;
         if(who == 3)
        {
            ties++;
            bal = bal + 90;
            output<<"The player has won $80!";
        }
    }

}

//determines if a third card should be dealt 
int Decide(ofstream &output, int &dScore, int &pScore,int &dCard3, int &pCard3, int dCard1, int dCard2, int pCard1, int pCard2) 
{
    if(pScore < 6){
        pCard3 = deal();
        pScore = Total(pScore, pCard3);
        output<<"Player's Hand: "<<pCard1<<", "<<pCard2<<", "<<pCard3<<endl;
    }
    else
        output<<"Player's Hand: "<<pCard1<<", "<<pCard2<<endl;
    
    if(dScore < 7 && dScore <= pScore){
        dCard3 = deal();        
        dScore = Total(dScore, dCard3);
        output<<"Dealer's Hand: "<<dCard1<<", "<<dCard2<<", "<<dCard3<<endl;
    }
    else
        output<<"Dealer's Hand: "<<dCard1<<", "<<dCard2<<endl;
}

int bet(ofstream &output,int &who, int &bal)
{
    who = rand()%3+1;
    bal = bal - 10;
    if(who == 1)
            output<<"Bet placed on PLAYER."<<endl;
           
    if(who == 2)
            output<<"Bet placed on DEALER."<<endl;
    
    if(who == 3)
            output<<"Bet placed on a TIE."<<endl;
        
}