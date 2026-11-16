#include "Round.hpp"
#include <cassert>
#include <iostream>
using namespace blackjack;
int main() {
  Round round(Tier::Red,42);
  assert(round.balance()==1000);
  bool invalid=false; try {round.start(50);} catch(const std::invalid_argument&) {invalid=true;}
  assert(invalid);
  round.start(10);
  assert(round.wager()==10);
  if(round.phase()==Phase::PlayerTurn) {
    assert(round.dealerHidden());
    round.stand();
  }
  assert(round.phase()==Phase::Finished);
  assert(!round.dealerHidden());
  assert(round.balance()>=990);
  round.start(5);
  if(round.phase()==Phase::PlayerTurn) round.hit();
  if(round.phase()==Phase::PlayerTurn) round.stand();
  assert(round.phase()==Phase::Finished);
  std::cout<<"Round lifecycle tests passed\n";
}
