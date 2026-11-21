# Firmware integrado: Muse + Tamagotchi Pip

Este diretório reúne os componentes próprios da integração. O SDK da Muse continua sendo o projeto ESP-IDF principal, versionado em `vendor/muse-gadget-sdk`; o código original do Pip permanece em `vendor/pip-keypet`.

## Alvo inicial

- Placa: Waveshare ESP32-S3-Touch-AMOLED-1.75C.
- MCU: ESP32-S3.
- Tela: AMOLED circular 466 × 466.
- Framework: ESP-IDF 6.0.3, conforme o SDK Muse fixado nesta branch.
- Interface final: LVGL do SDK Muse.

## Estado da implementação

| Camada | Estado |
|---|---|
| Driver da placa | Disponível no SDK Muse |
| Transporte de voz / sessão Muse | Disponível no SDK Muse |
| Núcleo de necessidades do Tamagotchi | Preparado como componente reutilizável |
| Renderizador dos olhos do Pip | Overlay de avatar compilado com o renderizador original do Pip |
| Navegação e aplicativos Pip | Pendentes: próximo bloco de trabalho |
| Eventos de conversa Muse → reações Pip | Hooks para transcrição/resposta integrados e compilados |
| BLE do iPhone + BLE Muse | Requer desenho de coexistência; não iniciar hosts independentes |
| Build integrado | CI passou nos perfis normal e voz em tempo real; sem teste físico |

## Organização

- `components/pip_personality/`: componente que reutiliza o núcleo de necessidades do Pip.
- `../vendor/pip-keypet/ui/`: origem upstream dos módulos C portáveis.
- `../vendor/muse-gadget-sdk/esp32/`: projeto ESP-IDF e drivers da Muse.

## Próxima implementação

1. Portar o conjunto de aplicativos e interações do Pip, preservando o loop de renderização e o controle de hardware do Muse.
2. Definir uma camada de navegação Tamagotchi que não substitua nem duplique a UI de configuração do Muse.
3. Acrescentar interações de pet (feed/play/poke) com eventos de toque e controles da UI, mantendo NVS persistente.
4. Refinar o feedback de conversa com eventos de transcrição e resposta, sem inferir emoções da IA sem uma API explícita.
5. Validar sensor, toque, áudio, tela, relógio e persistência quando houver placa física.

**Este diretório é uma base de desenvolvimento, não um firmware pronto para flash.**
