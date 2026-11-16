#include <iostream>
#include <cstdlib>
#include <cassert>
#include "PlayerTypes.h"
#include "Dealer.h"
using namespace std;
int main(){
 srand(7); // repeatable demo
 Player* players[8]={new SafeRedPlayer(),new SafeGreenPlayer(),new RandomRedPlayer(),new RandomGreenPlayer(),new MimicDealerRedPlayer(),new MimicDealerGreenPlayer(),new CustomRedPlayer(),new CustomGreenPlayer()};
 const char* names[8]={"Safe Red","Safe Green","Random Red","Random Green","Mimic Dealer Red","Mimic Dealer Green","Custom Red","Custom Green"};
 cout<<"BLACKJACK CASINO - PART 1\n";
 cout<<"Player hierarchy: 8 types\n";
 for(int i=0;i<8;i++){
   players[i]->setup(i+1,1,200);
   cout<<"ID "<<players[i]->id()<<" | "<<names[i]<<" | bet $"<<players[i]->bet()<<" | "<<(players[i]->play(15,10)?"HIT":"STAND")<<"\n";
   assert(!players[i]->shouldLeave());
 }
 Dealer dealer(101,1,500);
 assert(dealer.shouldHit(16));assert(!dealer.shouldHit(17));
 dealer.recordRound(true);dealer.recordRound(false);
 dealer.collectLosingBet(10);dealer.payWinningBet(5);
 cout<<"Dealer hits at 16: "<<dealer.shouldHit(16)<<"\n";
 cout<<"Dealer stands at 17: "<<!dealer.shouldHit(17)<<"\n";
 cout<<"Dealer win percentage: "<<dealer.winPercentage()<<"%\n";
 cout<<"Dealer joins lounge at 50% threshold: "<<dealer.shouldJoinLounge(50)<<"\n";
 cout<<"Dealer salary at $2/round: $"<<dealer.salary(2)<<"\n";
 for(Player* p:players)delete p;
 cout<<"Tests passed.\n";
}
