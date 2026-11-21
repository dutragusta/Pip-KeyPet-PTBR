# Integração Muse + Pip

Esta branch prepara a integração do Pip-KeyPet com o Muse Gadget SDK para a placa **Waveshare ESP32-S3-Touch-AMOLED-1.75C**.

## Fontes fixadas

- `vendor/muse-gadget-sdk`: `facebookincubator/muse-gadget-sdk`, commit `8d32b7fa8d6d9b600ea65fc956e9418f5c778a28` (Apache-2.0).
- `vendor/pip-keypet`: `NovikovVisuals/Pip-KeyPet`, commit `b505d9393bd9b8c0b076c0ef7a4d46921db69071` (MIT).

Os dois projetos são mantidos como submódulos para preservar a origem, o histórico e as licenças. A interface web PT-BR existente permanece na raiz do repositório e não é substituída.

## Arquitetura

O Muse SDK continua responsável por hardware, display, touch, LVGL, áudio, Wi-Fi, Bluetooth e sessão de voz. O Pip fornece o personagem, as necessidades, o humor, os eventos e as animações.

O firmware não copia o entry point do Pip e não inicializa periféricos duplicados.

## Integração de runtime adicionada

O adaptador `firmware/muse-overlay/pip_muse_bridge.c` liga o motor de personalidade aos pontos existentes do Muse:

- `MUSE_MODE_LISTENING`: altera a expressão visual de escuta, sem disparar um evento de Tamagotchi (gravar voz não deve ser confundido com conquistar um novo recorde);
- mudança para `MUSE_MODE_SPEAKING`: evento de interação/companhia (`PIP_SEEN`);
- mudança para `MUSE_MODE_ERROR`: evento de susto;
- toque no rosto do avatar: evento de carinho;
- levantar o dispositivo, quando o recurso de lift-wake do Muse estiver habilitado: evento `PIP_WAKE` para acordar o Tamagotchi;
- sacudir o dispositivo: quatro variações fortes de aceleração em uma janela de 900 ms disparam `PIP_SHAKE`; o limiar é inicial e deverá ser calibrado com dados da placa;
- humor, valência, energia e sono do Pip influenciam o sorriso, o cansaço e as pálpebras do avatar;
- consulta do estado visual: atualiza as necessidades no máximo uma vez por minuto.

O relógio do Tamagotchi só começa quando o relógio de parede está sincronizado e apresenta um timestamp plausível. Isso evita que o bichinho envelheça usando apenas o tempo desde que o ESP32 foi ligado. O fuso inicial está definido como UTC-3 (São Paulo).

O adaptador usa um namespace NVS próprio (pip_pet), separado das configurações do Muse. O snapshot contém identificador e versão de esquema, tamanho do payload e passa pela validação de versão/integridade estrutural do motor antes de ser restaurado. O estado é salvo após eventos e atualizações periódicas. Se o registro estiver ausente ou incompatível, o pet é inicializado novamente quando o relógio estiver sincronizado.

## Toolchain e limitações

- Pip original: firmware baseado em ESP-IDF 5.5.
- Muse SDK fixado: ESP-IDF 6.0.3.
- O overlay altera somente a cópia de trabalho do submódulo Muse, sem reescrever commits upstream.
- A CI verifica os patches e executa testes portáteis do motor de personalidade.
- Ainda falta compilar o firmware completo com ESP-IDF 6.0.3 e validar a integração no hardware.

**Este projeto ainda não é um firmware pronto para gravação.** O build aprovado é uma validação de compilação; não comprova áudio, tela, touch, sensor ou persistência em uma placa física.
