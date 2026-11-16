#pragma once
#include "Player.h"
#include <cstdlib>
// Level 2: four playing strategies. true = hit, false = stand.
class SafePlayer:public Player{public:bool play(int total,int)override{return total<15;}};
class RandomPlayer:public Player{public:bool play(int,int)override{return std::rand()%2==0;}};
class MimicDealerPlayer:public Player{public:bool play(int total,int)override{return total<=16;}};
class CustomPlayer:public Player{public:bool play(int total,int dealerCard)override{return total<17 && dealerCard>=7;}};
// Level 3: two betting/exit types per strategy.
#define MAKE_TYPES(PREFIX,BASE) \
class PREFIX##RedPlayer:public BASE{public:int bet()override{return 5;}bool shouldLeave()override{return redLeave();}}; \
class PREFIX##GreenPlayer:public BASE{public:int bet()override{return 50;}bool shouldLeave()override{return greenLeave();}};
MAKE_TYPES(Safe,SafePlayer)
MAKE_TYPES(Random,RandomPlayer)
MAKE_TYPES(MimicDealer,MimicDealerPlayer)
MAKE_TYPES(Custom,CustomPlayer)
#undef MAKE_TYPES
