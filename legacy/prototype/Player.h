#pragma once
#include <algorithm>
class Player {
protected:
 int playerId=0,tableNumber=0,rounds=0,losses=0;
 double money=100,initialMoney=100;
public:
 virtual ~Player()=default;
 virtual bool play(int total,int dealerCard)=0;
 virtual int bet()=0;
 virtual bool shouldLeave()=0;
 void setup(int id,int table,double cash){playerId=id;tableNumber=table;money=initialMoney=cash;rounds=losses=0;}
 void recordRound(bool won,int stake){++rounds;if(won)money+=stake;else{++losses;money-=stake;}}
 int id()const{return playerId;}
 double balance()const{return money;}
 bool cannotBet(int minimum)const{return money<minimum;}
 bool redLeave()const{return cannotBet(5)||(rounds>0 && losses*100>=rounds*60);}
 bool greenLeave()const{return cannotBet(50)||money<=initialMoney*0.10;}
};
