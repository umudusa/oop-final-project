#pragma once
#include <algorithm>
#include <cstdint>
#include <random>
#include <stdexcept>
#include <vector>
namespace blackjack {
enum class Suit { Clubs, Diamonds, Hearts, Spades };
struct Card { int rank; Suit suit; };
inline int value(Card c) { return c.rank == 1 ? 11 : std::min(c.rank,10); }
class Hand {
  std::vector<Card> cards_;
public:
  void add(Card c) { if(c.rank<1||c.rank>13) throw std::invalid_argument("Invalid card rank"); cards_.push_back(c); }
  const std::vector<Card>& cards() const { return cards_; }
  int total() const {
    int sum=0, aces=0;
    for(auto c:cards_) { sum+=value(c); if(c.rank==1) ++aces; }
    while(sum>21 && aces>0) { sum-=10; --aces; }
    return sum;
  }
  bool bust() const { return total()>21; }
  bool natural() const { return cards_.size()==2 && total()==21; }
  void clear() { cards_.clear(); }
};
class Shoe {
  std::vector<Card> cards_;
  std::mt19937 rng_;
public:
  explicit Shoe(int decks=6, std::uint32_t seed=std::random_device{}()):rng_(seed) {
    if(decks<1||decks>6) throw std::invalid_argument("Deck count must be 1..6");
    for(int d=0;d<decks;++d) for(int s=0;s<4;++s) for(int r=1;r<=13;++r)
      cards_.push_back({r,static_cast<Suit>(s)});
    std::shuffle(cards_.begin(),cards_.end(),rng_);
  }
  Card draw() { if(cards_.empty()) throw std::out_of_range("Shoe exhausted"); auto c=cards_.back();cards_.pop_back();return c; }
  std::size_t remaining() const { return cards_.size(); }
};
enum class Outcome { PlayerBlackjack, PlayerWin, DealerWin, Push };
inline Outcome judge(const Hand& p,const Hand& d) {
  if(p.bust()) return Outcome::DealerWin;
  if(p.natural()&&!d.natural()) return Outcome::PlayerBlackjack;
  if(d.natural()&&!p.natural()) return Outcome::DealerWin;
  if(d.bust()||p.total()>d.total()) return Outcome::PlayerWin;
  if(p.total()<d.total()) return Outcome::DealerWin;
  return Outcome::Push;
}
// Credited chips including returned stake, after stake was deducted.
inline std::int64_t payout(std::int64_t bet,Outcome o) {
  if(bet<=0) throw std::invalid_argument("Invalid wager");
  switch(o) {
    case Outcome::PlayerBlackjack:return bet*5/2;
    case Outcome::PlayerWin:return bet*2;
    case Outcome::Push:return bet;
    case Outcome::DealerWin:return 0;
  }
  throw std::logic_error("Invalid outcome");
}
inline bool dealerShouldHit(const Hand& h) { return h.total()<=16; }
enum class Tier { Red, Green, Black, Blue };
inline bool validBet(Tier t,int b) {
  switch(t) {
    case Tier::Red:return b>=5&&b<=45&&b%5==0;
    case Tier::Green:return b>=50&&b<=95&&b%5==0;
    case Tier::Black:return b>=100&&b<=490&&b%10==0;
    case Tier::Blue:return b>=500&&b<=1000&&b%10==0;
  }
  return false;
}
} // namespace blackjack
