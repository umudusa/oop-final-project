#include "Blackjack.hpp"
#include <cassert>
#include <iostream>
using namespace blackjack;
int main() {
  Hand soft; soft.add({1,Suit::Spades});soft.add({9,Suit::Hearts});
  assert(soft.total()==20);
  soft.add({5,Suit::Clubs});assert(soft.total()==15&&!soft.bust());
  Hand player;player.add({1,Suit::Hearts});player.add({13,Suit::Spades});
  assert(player.natural());
  Hand dealer;dealer.add({10,Suit::Clubs});dealer.add({7,Suit::Hearts});
  assert(!dealerShouldHit(dealer));
  assert(judge(player,dealer)==Outcome::PlayerBlackjack);
  assert(payout(10,Outcome::PlayerBlackjack)==25);
  assert(payout(10,Outcome::PlayerWin)==20);
  assert(payout(10,Outcome::Push)==10);
  assert(payout(10,Outcome::DealerWin)==0);
  assert(validBet(Tier::Red,45)&&!validBet(Tier::Red,50));
  assert(validBet(Tier::Blue,1000)&&!validBet(Tier::Blue,995));
  Shoe shoe(6,123);assert(shoe.remaining()==312);
  for(int i=0;i<312;++i) shoe.draw();
  assert(shoe.remaining()==0);
  bool threw=false;try{shoe.draw();}catch(const std::out_of_range&){threw=true;}
  assert(threw);
  std::cout<<"Blackjack engine tests passed\n";
}
