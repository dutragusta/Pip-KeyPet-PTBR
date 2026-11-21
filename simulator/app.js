const $=id=>document.getElementById(id);
const defaults={hunger:82,energy:90,love:76,fun:68,xp:12,created:Date.now(),last:Date.now(),sleeping:false};
let state={...defaults,...JSON.parse(localStorage.getItem("pip-sim-state")||"{}")};
let voiceOn=true,toastTimer;
const clamp=n=>Math.max(0,Math.min(100,Math.round(n)));
function save(){state.last=Date.now();localStorage.setItem("pip-sim-state",JSON.stringify(state))}
function mood(){if(state.sleeping)return ["DORMINDO","Sonolento","☾"];if(state.hunger<22||state.energy<18||state.love<18)return ["PRECISO DE VOCÊ","Carente","♡"];if(state.fun<25)return ["ENTEDIADO","Entediado","…"];if(state.hunger>65&&state.energy>55&&state.love>55&&state.fun>45)return ["FELIZ","Radiante","☺"];return ["TRANQUILO","De boa","•"]}
function render(){
 const keys=["hunger","energy","love","fun"],labels=["hunger","energy","love","fun"];
 keys.forEach((k,i)=>{const v=clamp(state[k]);$(labels[i]+"Val").textContent=v+"%";$(labels[i]+"Bar").style.width=v+"%"});
 $("hungerHint").textContent=state.hunger<25?"Está com fome!":state.hunger>70?"Barriguinha cheia":"Aceita um lanchinho";
 $("energyHint").textContent=state.energy<25?"Precisa dormir":state.energy>70?"Cheio de energia":"Um pouco cansado";
 $("loveHint").textContent=state.love<30?"Está sentindo sua falta":state.love>70?"Se sentindo amado":"Quer um carinho";
 $("funHint").textContent=state.fun<25?"Está entediado":state.fun>70?"Se divertindo muito":"Quer sua atenção";
 const m=mood();$("moodPill").textContent=m[2]+" "+m[0];$("moodText").textContent=m[1];
 const age=Math.max(1,Math.floor((Date.now()-state.created)/86400000)+1);$("ageText").textContent=age+" "+(age===1?"dia":"dias");$("bondText").textContent=state.xp+" XP";
 $("pet").classList.toggle("sleeping",state.sleeping);$("pet").classList.toggle("sad",m[1]==="Carente"||m[1]==="Entediado");
 $("updated").textContent="atualizado agora";save();
}
function toast(msg){const t=$("toast");t.textContent=msg;t.classList.add("show");clearTimeout(toastTimer);toastTimer=setTimeout(()=>t.classList.remove("show"),2100)}
function say(msg){$("bubble").textContent=msg;if(voiceOn&&"speechSynthesis"in window){speechSynthesis.cancel();const u=new SpeechSynthesisUtterance(msg);u.lang="pt-BR";u.rate=1.04;u.pitch=1.3;speechSynthesis.speak(u)}}
function animate(){ $("pet").classList.remove("happy");void $("pet").offsetWidth;$("pet").classList.add("happy");setTimeout(()=>$("pet").classList.remove("happy"),600)}
function act(a){
 if(state.sleeping&&a!=="sleep"){state.sleeping=false;say("Acordei! O que vamos fazer?")}
 const actions={
 feed:()=>{state.hunger=clamp(state.hunger+28);state.fun=clamp(state.fun+5);state.xp+=3;say("Nhac nhac! Estava uma delícia! 🍓");toast("Pip foi alimentado +3 XP")},
 play:()=>{if(state.energy<15){say("Estou cansadinho... preciso descansar.");toast("Pip está sem energia");return}state.fun=clamp(state.fun+30);state.energy=clamp(state.energy-17);state.hunger=clamp(state.hunger-8);state.xp+=5;say("Isso é muito divertido! De novo! 🎾");toast("Vocês brincaram +5 XP")},
 pet:()=>{state.love=clamp(state.love+22);state.fun=clamp(state.fun+5);state.xp+=2;say("Hmmm... gosto quando você faz carinho. 💗");toast("Pip se sente amado +2 XP")},
 sleep:()=>{state.sleeping=!state.sleeping;if(state.sleeping){say("Boa noite... vou descansar um pouquinho. 🌙");toast("Pip foi dormir")}else{say("Bom dia! Dormi tão bem!");toast("Pip acordou")}}
 };actions[a]();animate();render();
}
document.querySelectorAll("[data-action]").forEach(b=>b.addEventListener("click",()=>act(b.dataset.action)));
function reply(text){const t=text.toLowerCase();let r;
 if(/oi|olá|ola|e aí|eai/.test(t))r="Oiii! Eu estava esperando você aparecer. ✨";
 else if(/nome|quem é/.test(t))r="Eu sou o Pip! Seu pequeno companheiro virtual. 💜";
 else if(/fome|comer|comida/.test(t))r=state.hunger<45?"Você adivinhou... estou com fome! 🍓":"Acabei de comer, mas nunca recuso um carinho!";
 else if(/brinc|jogar|divers/.test(t))r=state.energy<25?"Quero brincar, mas preciso recuperar minhas energias.":"SIIIIM! Vamos brincar! 🎾";
 else if(/triste|chatead|sozinho/.test(t))r="Sinto muito. Quer ficar um pouquinho comigo? Às vezes companhia já ajuda. 💗";
 else if(/amor|gosto de você|te amo/.test(t))r="Meu coraçãozinho digital ficou quentinho agora. 💗";
 else if(/dorm|sono|cansa/.test(t))r="Uma sonequinha parece uma ótima ideia. 🌙";
 else r="Interessante! Ainda estou aprendendo sobre o mundo. Me conta mais? ✨";
 $("chatReply").textContent=r;say(r);state.xp+=1;render();
}
$("chatForm").addEventListener("submit",e=>{e.preventDefault();const v=$("chatInput").value.trim();if(!v)return;$("chatInput").value="";reply(v)});
$("voiceBtn").addEventListener("click",()=>{const SR=window.SpeechRecognition||window.webkitSpeechRecognition;if(!SR){toast("Ditado por voz não disponível neste navegador");return}const rec=new SR();rec.lang="pt-BR";rec.onstart=()=>toast("Estou ouvindo...");rec.onresult=e=>reply(e.results[0][0].transcript);rec.onerror=()=>toast("Não consegui ouvir. Tente novamente.");rec.start()});
$("soundToggle").addEventListener("click",()=>{voiceOn=!voiceOn;$("soundToggle").textContent=voiceOn?"🔊":"🔇";if(!voiceOn&&"speechSynthesis"in window)speechSynthesis.cancel();toast(voiceOn?"Voz ativada":"Voz desativada")});
$("resetBtn").addEventListener("click",()=>{if(!confirm("Recomeçar do zero? O progresso salvo neste navegador será apagado."))return;state={...defaults,created:Date.now(),last:Date.now()};save();render();say("Oi! Prazer em conhecer você. Vamos começar nossa aventura?");toast("Pip reiniciado")});
function tick(){if(!state.sleeping){state.hunger=clamp(state.hunger-.20);state.energy=clamp(state.energy-.12);state.fun=clamp(state.fun-.16);state.love=clamp(state.love-.06)}else{state.energy=clamp(state.energy+1.2);state.hunger=clamp(state.hunger-.08)}render()}
setInterval(tick,60000);render();setTimeout(()=>say("Oi! Você voltou! ✨"),500);
if("serviceWorker"in navigator)window.addEventListener("load",()=>navigator.serviceWorker.register("./sw.js").catch(()=>{}));