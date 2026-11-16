#include <drogon/drogon.h>
#include "Round.hpp"
#include <cstdlib>
#include <iomanip>
#include <map>
#include <memory>
#include <mutex>
#include <random>
#include <sstream>
#include <string>
using namespace drogon;
using namespace blackjack;
namespace {
std::mutex sessionsMutex;
std::map<std::string,std::unique_ptr<Round>> sessions;
std::string newId() {
  std::random_device rd;
  std::ostringstream os;
  for(int i=0;i<4;++i) os<<std::hex<<std::setw(8)<<std::setfill('0')<<rd();
  return os.str();
}
Json::Value card(Card c) {
  Json::Value j; j["rank"]=c.rank;
  const char* suits[]={"clubs","diamonds","hearts","spades"};
  j["suit"]=suits[static_cast<int>(c.suit)]; return j;
}
Json::Value snapshot(const Round& game) {
  Json::Value j;
  j["balance"]=Json::Int64(game.balance()); j["wager"]=Json::Int64(game.wager());\n  j["gameOver"]=game.balance()<5 && game.phase()!=Phase::PlayerTurn;
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
  std::lock_guard<std::mutex> lock(sessionsMutex);
  try {
    std::string id=req->getCookie("casino_session");
    bool created=false;
    auto it=sessions.find(id);
    if(id.empty()||it==sessions.end()) {
      if(action!="state") throw std::invalid_argument("Refresh the page to start a session");
      if(sessions.size()>=10000) throw std::runtime_error("Server is at capacity");
      id=newId();it=sessions.emplace(id,std::make_unique<Round>()).first;created=true;
    }
    Round& game=*it->second;
    if(action=="start") {\n      if(game.balance()<5) throw std::invalid_argument("Game over: not enough chips to place the minimum bet");
      auto body=req->getJsonObject();
      if(!body||!body->isMember("bet")||!(*body)["bet"].isInt()) throw std::invalid_argument("Expected integer bet");
      game.start((*body)["bet"].asInt());
    } else if(action=="hit") game.hit();
    else if(action=="stand") game.stand();
    auto res=HttpResponse::newHttpJsonResponse(snapshot(game));
    res->addHeader("Cache-Control","no-store");
    if(created) {
      std::string cookie="casino_session="+id+"; Path=/; HttpOnly; SameSite=Strict";
      if(req->getHeader("x-forwarded-proto")=="https") cookie+="; Secure";
      res->addHeader("Set-Cookie",cookie);
    }
    cb(res);
  } catch(const std::exception& e) {
    Json::Value err;err["error"]=e.what();
    auto res=HttpResponse::newHttpJsonResponse(err);res->setStatusCode(k400BadRequest);cb(res);
  }
}
}
int main() {
  const char* p=std::getenv("PORT");int port=p?std::atoi(p):8844;
  if(port<1||port>65535) port=8844;
  app().registerHandler("/api/state",[](const HttpRequestPtr& r,std::function<void(const HttpResponsePtr&)>&& cb){handle(r,std::move(cb),"state");},{Get});
  app().registerHandler("/api/start",[](const HttpRequestPtr& r,std::function<void(const HttpResponsePtr&)>&& cb){handle(r,std::move(cb),"start");},{Post});
  app().registerHandler("/api/hit",[](const HttpRequestPtr& r,std::function<void(const HttpResponsePtr&)>&& cb){handle(r,std::move(cb),"hit");},{Post});
  app().registerHandler("/api/stand",[](const HttpRequestPtr& r,std::function<void(const HttpResponsePtr&)>&& cb){handle(r,std::move(cb),"stand");},{Post});
  app().setDocumentRoot("./public").addListener("0.0.0.0",port).setThreadNum(2).run();
}
