#pragma once
#include "Blackjack.hpp"
#include <cstdint>
#include <stdexcept>
namespace blackjack {
enum class Phase { Betting, PlayerTurn, Finished };
class Round {
  Shoe shoe_;
  Hand player_, dealer_;
  Phase phase_ = Phase::Betting;
  Tier tier_;
  std::int64_t balance_ = 1000, wager_ = 0;
  Outcome outcome_ = Outcome::Push;
public:
  explicit Round(Tier tier=Tier::Red, std::uint32_t seed=std::random_device{}()) : shoe_(6,seed), tier_(tier) {}
  Phase phase() const { return phase_; }
  const Hand& player() const { return player_; }
  const Hand& dealer() const { return dealer_; }
  std::int64_t balance() const { return balance_; }
  std::int64_t wager() const { return wager_; }
  Outcome outcome() const { if(phase_!=Phase::Finished) throw std::logic_error("Round not finished"); return outcome_; }
  bool dealerHidden() const { return phase_==Phase::PlayerTurn; }
  void start(int bet) {
    if(phase_==Phase::PlayerTurn) throw std::logic_error("Round already active");
    if(!validBet(tier_,bet)||bet>balance_) throw std::invalid_argument("Invalid bet or insufficient chips");
    if(shoe_.remaining()<20) shoe_=Shoe(6);
    player_.clear(); dealer_.clear(); wager_=bet; balance_-=bet;
    player_.add(shoe_.draw());dealer_.add(shoe_.draw());player_.add(shoe_.draw());dealer_.add(shoe_.draw());
    phase_=Phase::PlayerTurn;
    if(player_.natural()||dealer_.natural()) settle();
  }
  void hit() {
    if(phase_!=Phase::PlayerTurn) throw std::logic_error("Cannot hit now");
    player_.add(shoe_.draw());
    if(player_.bust()||player_.total()==21) standOrSettle();
  }
  void stand() {
    if(phase_!=Phase::PlayerTurn) throw std::logic_error("Cannot stand now");
    standOrSettle();
  }
private:
  void standOrSettle() {
    if(!player_.bust()) while(dealerShouldHit(dealer_)) dealer_.add(shoe_.draw());
    settle();
  }
  void settle() {
    outcome_=judge(player_,dealer_);
    balance_+=payout(wager_,outcome_);
    phase_=Phase::Finished;
  }
};
}
