# Arquitetura do Tamagotchi Muse

## Princípio

A Muse é dona do hardware e da conectividade. O Pip é dono do personagem, das necessidades e da experiência de Tamagotchi. Nenhum módulo portado do Pip deve reinicializar recursos que a Muse já inicializou.

## Fluxo de dados planejado

```text
Microfone / botão
      |
      v
Muse voice session -----> Muse cloud / assistant
      |                           |
      | listening / thinking      | response / playback
      v                           v
Pip event adapter <--------- Muse app events
      |
      v
Pip personality (needs + mood)
      |
      v
Pip face renderer
      |
      v
Muse-owned LVGL display
```

## Dono de cada recurso

| Recurso | Dono |
|---|---|
| Display, painel e touch | Muse BSP |
| Áudio, codec, microfone e alto-falante | Muse BSP / voice stack |
| Wi-Fi, pareamento e túnel | Muse SDK |
| Bluetooth do dispositivo | Muse SDK, com análise antes de adicionar serviços Pip |
| Bateria, PMU e economia de energia | Muse BSP |
| Necessidades, humor e ciclo do pet | Pip |
| Olhos, expressões e animações | Pip, adaptado ao runtime LVGL Muse |
| Menu e miniaplicativos | Pip, portados gradualmente |

## Regras de integração

- Não chamar inicializadores de display, touch, áudio, PMU ou BLE do firmware antigo do Pip.
- Não iniciar um segundo host NimBLE/BT.
- Não bloquear as tarefas de voz, rede ou UI com renderização do personagem.
- Persistir estado do pet em armazenamento versionado e tolerar migrações.
- A IA não controla diretamente os níveis de fome, energia ou afeto. Ela gera eventos semânticos limitados; a simulação do pet decide a reação.
- Respostas da IA podem sugerir reações, mas não devem sobrescrever o estado persistente do Tamagotchi.

## Fases

1. Núcleo de necessidades do Pip como componente independente.
2. Rosto e renderização no LVGL do Muse.
3. Eventos da sessão de voz para animações e reações.
4. Persistência e relógio.
5. Navegação e apps do Pip.
6. Serviços BLE e notificações, após análise de coexistência.
7. Build automatizado e validação de integração.
