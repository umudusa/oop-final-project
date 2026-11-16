import React, { useEffect, useState } from 'react';
import { createRoot } from 'react-dom/client';
import './style.css';
type Card = {rank?:number;suit?:string;hidden?:boolean};
type State = {balance:number;wager:number;phase:'betting'|'playing'|'finished';player:Card[];dealer:Card[];playerTotal:number;dealerTotal:number|null;outcome?:string};
const faces:Record<number,string>={1:'A',11:'J',12:'Q',13:'K'};
const symbols:Record<string,string>={hearts:'♥',diamonds:'♦',clubs:'♣',spades:'♠'};
function PlayingCard({card}:{card:Card}) {
  if(card.hidden) return <div className="playing-card back">✦</div>;
  const red=card.suit==='hearts'||card.suit==='diamonds';
  return <div className={'playing-card '+(red?'red':'black')}><span>{faces[card.rank!]||card.rank}{symbols[card.suit!]}</span><strong>{symbols[card.suit!]}</strong></div>;
}
function App() {
  const [game,setGame]=useState<State|null>(null),[bet,setBet]=useState(10),[error,setError]=useState(''),[busy,setBusy]=useState(false);
  async function request(path:string,body?:object) {
    setBusy(true);setError('');
    try {
      const res=await fetch('/api/'+path,{method:body||path!=='state'?'POST':'GET',headers:{'Content-Type':'application/json'},body:body?JSON.stringify(body):undefined});
      const json=await res.json();if(!res.ok) throw new Error(json.error||'Request failed');setGame(json);
    } catch(e) {setError(e instanceof Error?e.message:'Connection failed');}finally{setBusy(false);}
  }
  useEffect(()=>{void request('state');},[]);
  return <div className="app"><header><div className="brand">♠ BLACKJACK <span>CASINO</span></div><div className="balance">VIRTUAL CHIPS <strong>{game?.balance??'—'}</strong></div></header>
    <main><div className="eyebrow">PRIVATE TABLE · RED ROOM</div><h1>Play your hand.</h1><p className="sub">C++ powered blackjack · Local single-player preview</p>
      <section className="table"><div className="hand-label">DEALER {game?.dealerTotal===null?'':'· '+(game?.dealerTotal??'')}</div><div className="cards">{game?.dealer.map((c,i)=><PlayingCard key={i} card={c}/>)}</div>
      <div className="table-center">BLACKJACK <small>PAYS 3 TO 2</small></div><div className="hand-label">YOUR HAND · {game?.playerTotal??0}</div><div className="cards">{game?.player.map((c,i)=><PlayingCard key={i} card={c}/>)}</div></section>
      <div className="panel"><div><div className="eyebrow">CURRENT WAGER</div><div className="wager">{game?.wager||bet} <small>CHIPS</small></div></div>
      <div className="actions">{game?.phase!=='playing'?<><select aria-label="Bet amount" value={bet} onChange={e=>setBet(Number(e.target.value))}>{[5,10,15,20,25,30,35,40,45].map(n=><option key={n} value={n}>{n} chips</option>)}</select><button disabled={busy||!game} onClick={()=>request('start',{bet})}>DEAL CARDS</button></>:<><button disabled={busy} onClick={()=>request('hit')}>HIT</button><button disabled={busy} onClick={()=>request('stand')}>STAND</button></>}</div></div>
      {game?.phase==='finished'&&<div className="result">{({blackjack:'BLACKJACK! YOU WIN',win:'YOU WIN',lose:'DEALER WINS',push:'PUSH · BET RETURNED'} as Record<string,string>)[game.outcome||'']}</div>}
      {error&&<div className="error" role="alert">{error}</div>}
      <footer>DEVELOPMENT PREVIEW · VIRTUAL CHIPS ONLY · NO REAL-MONEY GAMBLING</footer>
    </main></div>;
}
createRoot(document.getElementById('root')!).render(<React.StrictMode><App/></React.StrictMode>);
