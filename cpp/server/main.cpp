#include <drogon/drogon.h>
#include "Round.hpp"
#include <mutex>
using namespace drogon;
using namespace blackjack;
namespace {
std::mutex mutex_;
Round game; // LOCAL DEVELOPMENT ONLY: shared state, never expose publicly
Json::Value card(Card c) {
  Json::Value j; j["rank"]=c.rank;
  const char* suits[]={"clubs","diamonds","hearts","spades"};
  j["suit"]=suits[static_cast<int>(c.suit)]; return j;
}
Json::Value snapshot() {
  Json::Value j;
  j["balance"]=Json::Int64(game.balance()); j["wager"]=Json::Int64(game.wager());
  j["phase"]=game.phase()==Phase::Betting?"betting":game.phase()==Phase::PlayerTurn?"playing":"finished";
  j["playerTotal"]=game.player().total();
  if(game.dealerHidden()) j["dealerTotal"]=Json::nullValue;
  else j["dealerTotal"]=game.dealer().total();
  j["player"]=Json::arrayValue;j["dealer"]=Json::arrayValue;
  for(auto c:game.player().cards()) j["player"].append(card(c));
  int i=0;for(auto c:game.dealer().cards()) {
    if(game.dealerHidden()&&i++==1){Json::Value h;h["hidden"]=true;j["dealer"].append(h);}
    else j["dealer"].append(card(c));
  }
  if(game.phase()==Phase::Finished) {
    switch(game.outcome()) {
      case Outcome::PlayerBlackjack:j["outcome"]="blackjack";break;
      case Outcome::PlayerWin:j["outcome"]="win";break;
      case Outcome::DealerWin:j["outcome"]="lose";break;
      case Outcome::Push:j["outcome"]="push";break;
    }
  }
  return j;
}
void handle(const HttpRequestPtr& req,std::function<void(const HttpResponsePtr&)>&& cb,const std::string& action) {
  std::lock_guard<std::mutex> lock(mutex_);
  try {
    if(action=="start") {
      auto body=req->getJsonObject();
      if(!body||!body->isMember("bet")||!(*body)["bet"].isInt()) throw std::invalid_argument("Expected integer bet");
      game.start((*body)["bet"].asInt());
    } else if(action=="hit") game.hit();
    else if(action=="stand") game.stand();
    cb(HttpResponse::newHttpJsonResponse(snapshot()));
  } catch(const std::exception& e) {
    Json::Value err;err["error"]=e.what();
    auto res=HttpResponse::newHttpJsonResponse(err);res->setStatusCode(k400BadRequest);cb(res);
  }
}
}
int main() {
  app().registerHandler("/api/state",[](const HttpRequestPtr& r,auto&& cb){handle(r,std::move(cb),"state");},{Get});
  app().registerHandler("/api/start",[](const HttpRequestPtr& r,auto&& cb){handle(r,std::move(cb),"start");},{Post});
  app().registerHandler("/api/hit",[](const HttpRequestPtr& r,auto&& cb){handle(r,std::move(cb),"hit");},{Post});
  app().registerHandler("/api/stand",[](const HttpRequestPtr& r,auto&& cb){handle(r,std::move(cb),"stand");},{Post});
  app().addListener("127.0.0.1",8844).setThreadNum(2).run();
}
