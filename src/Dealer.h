#pragma once
class Dealer {
 int employeeId,tableNumber,rounds=0,wins=0;
 double cash;
public:
 Dealer(int id,int table,double initialCash):employeeId(id),tableNumber(table),cash(initialCash){}
 bool shouldHit(int total)const{return total<=16;}
 void refillCash(double amount){if(amount>0)cash+=amount;}
 void payWinningBet(double amount){if(amount>cash)refillCash(amount-cash);cash-=amount;}
 void collectLosingBet(double amount){cash+=amount;}
 void recordRound(bool won){++rounds;if(won)++wins;}
 double winPercentage()const{return rounds?100.0*wins/rounds:0;}
 bool shouldJoinLounge(double threshold)const{return rounds>0 && winPercentage()<=threshold;}
 double salary(double perRound)const{return rounds*perRound;}
 double balance()const{return cash;}
};
