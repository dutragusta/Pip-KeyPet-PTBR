# Integração Muse + Pip

Esta branch prepara a integração do Pip-KeyPet com o Muse Gadget SDK para a **Waveshare ESP32-S3-Touch-AMOLED-1.75C**.

## Fontes fixadas
- `vendor/muse-gadget-sdk`: `facebookincubator/muse-gadget-sdk`, commit `8d32b7fa8d6d9b600ea65fc956e9418f5c778a28` (Apache-2.0).
- `vendor/pip-keypet`: `NovikovVisuals/Pip-KeyPet`, commit `b505d9393bd9b8c0b076c0ef7a4d46921db69071` (MIT).

Os projetos permanecem como submódulos para preservar origem, histórico e licenças. A interface web PT-BR na raiz continua separada do firmware.

## Arquitetura
Muse é responsável por hardware, display, touch, LVGL, áudio, Wi-Fi, Bluetooth e sessões de voz. Pip fornece personalidade, necessidades, humor, eventos e renderizador de expressões. Não há inicialização duplicada de periféricos nem cópia do entry point upstream.

## Integração de runtime
- Estados do Muse alteram o estado visual do avatar.
- Primeira transcrição válida do usuário por turno gera `PIP_SEEN`, sem duplicar em transcrições parciais.
- Primeira resposta textual por turno gera um evento de carinho, sem repetir em fragmentos.
- Áudio de fala controla apenas animação; não duplica recompensas.
- Erro de sessão, toque no rosto, lift-wake e gesto de sacudir estão conectados à ponte.
- O gesto de sacudir usa um limiar inicial de quatro impulsos em 900 ms, ainda não calibrado fisicamente.
- Humor, valência, energia e sono influenciam expressões.
- Atualização de necessidades ocorre no máximo uma vez por minuto.
- Persistência em NVS usa namespace separado (`pip_pet`) e snapshot versionado, validado antes de restauração.

O relógio do pet depende de sincronização de relógio de parede plausível. Fuso configurado: UTC-3, São Paulo.

## Validação automatizada
A CI já aprovou testes portáteis do motor, verificações de overlay e builds dos perfis padrão e voz em tempo real para ESP32-S3/Waveshare 1.75C, usando ESP-IDF 6.0.3. Isso é validação de compilação, não teste de funcionamento físico.

## Pendências prioritárias fora da interface Tamagotchi
Consulte `docs/REMAINING_WORK.md` para o roteiro de voz/IA, credenciais, coexistência BLE, testes de hardware e preparação de release.

**Ainda não é firmware pronto para gravação.** Não foram verificados fisicamente áudio, display, touch, sensor, persistência ou pareamento. A configuração do token oficial do dispositivo continua necessária.

## Identidade visual: somente os olhos do Pip

O avatar integrado deve renderizar **apenas os dois olhos originais do Pip**, usando o renderizador upstream `ui/face.c` para formato, pupilas, pálpebras, olhar e animações. Elementos faciais externos aos olhos (bochechas/blush) ficam desativados. Não desenhar boca, nariz nem rosto completo; o avatar padrão do Muse não deve substituir os olhos do Pip. Efeitos dentro dos olhos, como pupilas em coração, permanecem permitidos quando usados como expressão.
