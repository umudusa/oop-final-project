import React, { useEffect, useRef, useState } from 'react';
import { createRoot } from 'react-dom/client';
import './style.css';
type Card = {rank?:number;suit?:string;hidden?:boolean};
type State = {balance:number;wager:number;phase:'betting'|'playing'|'finished';player:Card[];dealer:Card[];playerTotal:number;dealerTotal:number|null;outcome?:string;gameOver?:boolean};
const faces:Record<number,string>={1:'A',11:'J',12:'Q',13:'K'};
const symbols:Record<string,string>={hearts:'♥',diamonds:'♦',clubs:'♣',spades:'♠'};
function PlayingCard({card}:{card:Card}) {
  if(card.hidden) return <div className="playing-card back">✦</div>;
  const red=card.suit==='hearts'||card.suit==='diamonds';
  return <div className={'playing-card '+(red?'red':'black')}><span>{faces[card.rank!]||card.rank}{symbols[card.suit!]}</span><strong>{symbols[card.suit!]}</strong></div>;
}
function App() {
  const [music,setMusic]=useState(false);
  const audio=useRef<AudioContext|null>(null);
  const timer=useRef<number|null>(null);
  const step=useRef(0);
  function toggleMusic(){
    if(music){if(timer.current!==null)clearInterval(timer.current);timer.current=null;setMusic(false);return;}
    try{
      audio.current??=new AudioContext();void audio.current.resume();
      const notes=[261.63,329.63,392,329.63,293.66,349.23,440,349.23,246.94,293.66,392,293.66,220,261.63,329.63,261.63];
      const tick=()=>{const ctx=audio.current!;const o=ctx.createOscillator(),g=ctx.createGain();o.type='sine';o.frequency.value=notes[step.current++%notes.length];g.gain.setValueAtTime(.0001,ctx.currentTime);g.gain.exponentialRampToValueAtTime(.014,ctx.currentTime+.04);g.gain.exponentialRampToValueAtTime(.0001,ctx.currentTime+.43);o.connect(g).connect(ctx.destination);o.start();o.stop(ctx.currentTime+.45);};
      tick();timer.current=window.setInterval(tick,530);setMusic(true);
    }catch{setMusic(false);}
  }
  useEffect(()=>()=>{if(timer.current!==null)clearInterval(timer.current);void audio.current?.close();},[]);
  const [game,setGame]=useState<State|null>(null),[bet,setBet]=useState(10),[error,setError]=useState(''),[busy,setBusy]=useState(false);
  const gameOver=!!game&&(game.gameOver===true||(game.balance<5&&game.phase!=='playing'));
  useEffect(()=>{if(game&&bet>game.balance){const valid=[5,10,15,20,25,30,35,40,45].filter(n=>n<=game.balance);if(valid.length)setBet(valid[valid.length-1]);}},[game?.balance]);
  async function request(path:string,body?:object) {
    setBusy(true);setError('');
    try {
      const res=await fetch('/api/'+path,{method:body||path!=='state'?'POST':'GET',headers:{'Content-Type':'application/json'},body:body?JSON.stringify(body):undefined});
      const json=await res.json();if(!res.ok) throw new Error(json.error||'Request failed');setGame(json);
    } catch(e) {setError(e instanceof Error?e.message:'Connection failed');}finally{setBusy(false);}
  }
  useEffect(()=>{void request('state');},[]);
  return <div className="app"><header><div className="brand"><span className="brand-suit">♠</span> ROYAL <span>BLACKJACK</span><small>PRIVATE CASINO TABLE</small></div><button className="music-toggle" onClick={toggleMusic} aria-pressed={music}>{music?"♫ MUSIC ON":"♪ MUSIC OFF"}</button><div className="balance">VIRTUAL CHIPS <strong>{game?.balance??'—'}</strong></div></header>
    <main><div className="eyebrow">✦ TABLE 01 · RED ROOM ✦</div><h1>Fortune favors the bold.</h1><p className="sub">C++ powered blackjack · An elegant private casino experience</p>
      <section className="table"><div className="hand-label">DEALER {game?.dealerTotal===null?'':'· '+(game?.dealerTotal??'')}</div><div className="cards">{game?.dealer.map((c,i)=><PlayingCard key={i} card={c}/>)}</div>
      <div className="table-center">♛ BLACKJACK <small>PAYS 3 TO 2 · DEALER STANDS ON 17</small></div><div className="hand-label">YOUR HAND · {game?.playerTotal??0}</div><div className="cards">{game?.player.map((c,i)=><PlayingCard key={i} card={c}/>)}</div></section>
      <div className="panel"><div><div className="eyebrow">CURRENT WAGER</div><div className="wager">{game?.wager||bet} <small>CHIPS</small></div></div>
      <div className="actions">{gameOver?<div className="game-over" role="status"><strong>GAME OVER</strong><span>Not enough virtual chips to continue.</span><small>This session has ended. Refreshing will not restore chips.</small></div>:game?.phase!=='playing'?<><select aria-label="Bet amount" value={bet} onChange={e=>setBet(Number(e.target.value))}>{[5,10,15,20,25,30,35,40,45].map(n=><option key={n} value={n} disabled={!!game&&n>game.balance}>{n} chips</option>)}</select><button disabled={busy||!game||bet>game.balance} onClick={()=>request('start',{bet})}>DEAL CARDS</button></>:<><button disabled={busy} onClick={()=>request('hit')}>HIT</button><button disabled={busy} onClick={()=>request('stand')}>STAND</button></>}</div></div>
      {game?.phase==='finished'&&!gameOver&&<div className="result">{({blackjack:'BLACKJACK! YOU WIN',win:'YOU WIN',lose:'DEALER WINS',push:'PUSH · BET RETURNED'} as Record<string,string>)[game.outcome||'']}</div>}
      {error&&<div className="error" role="alert">{error}</div>}
      <footer>DEVELOPMENT PREVIEW · VIRTUAL CHIPS ONLY · NO REAL-MONEY GAMBLING</footer>
    </main></div>;
}
createRoot(document.getElementById('root')!).render(<React.StrictMode><App/></React.StrictMode>);
