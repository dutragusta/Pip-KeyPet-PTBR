# Integração Muse + Pip

Esta branch prepara a integração do Pip-KeyPet com o Muse Gadget SDK para a placa **Waveshare ESP32-S3-Touch-AMOLED-1.75C**.

## Fontes fixadas

- `vendor/muse-gadget-sdk`: `facebookincubator/muse-gadget-sdk`, commit `8d32b7fa8d6d9b600ea65fc956e9418f5c778a28` (Apache-2.0).
- `vendor/pip-keypet`: `NovikovVisuals/Pip-KeyPet`, commit `b505d9393bd9b8c0b076c0ef7a4d46921db69071` (MIT).

Os dois projetos são mantidos como submódulos para preservar a origem, o histórico e as licenças. A interface web PT-BR existente permanece na raiz do repositório e não é substituída.

## Compatibilidade de hardware

O Muse SDK já possui um perfil específico para a Waveshare ESP32-S3-Touch-AMOLED-1.75C:
- Driver: `esp32/components/muse/boards/board_waveshare_s3_175c.c`
- Configuração: `esp32/devices/sdkconfig.muse-waveshare-s3-175c`
- Guia: `esp32/devices/guides/muse-waveshare-s3-175c.md`

A placa usa painel AMOLED circular de 466 px, touch CST9217, codec ES8311, microfones ES7210 e PMU AXP2101. O SDK já trata esses periféricos.

## Arquitetura pretendida

O Muse SDK será a base do firmware e continuará responsável por:
- inicialização da placa, painel, touch e gerenciamento de energia;
- conexão Wi-Fi, pareamento e sessão com o aplicativo Muse;
- captura e reprodução de áudio e transporte de voz;
- infraestrutura LVGL e tarefas do dispositivo.

O Pip será portado como a camada de personagem e experiência:
- rosto, olhos, expressões e animações;
- estados emocionais e ciclo de vida do Tamagotchi;
- aplicativos, jogos, temas e interação do pet;
- persistência dos dados e configurações próprias do Pip, adaptadas ao armazenamento do Muse.

## Portabilidade: pontos que precisam ser resolvidos

**Não copiar o `firmware/main/main.c` do Pip por cima do Muse.** Os dois firmwares inicializam os mesmos recursos de hardware e mantêm arquiteturas de tarefas diferentes.

1. Comparar a versão efetiva do LVGL e as APIs usadas pelos dois projetos.
2. Portar os módulos reutilizáveis de `ui/` do Pip para um componente próprio dentro do firmware Muse.
3. Substituir o acesso direto do Pip ao display, touch, áudio, microfone, PMU e acelerômetro pelas interfaces já inicializadas pelo Muse.
4. Integrar a máquina de estados do Pip à sessão de voz do Muse, para que o personagem reaja a escuta, pensamento, fala, erro e desconexão.
5. Resolver a coexistência do BLE do Muse com os serviços BLE usados pelo Pip para iPhone. Não iniciar dois hosts BLE independentes.
6. Reconciliar as configurações de memória, partições, PSRAM e energia antes de habilitar todos os recursos.
7. Criar testes de compilação e validação de hardware antes de publicar qualquer firmware para gravação.

## Diferença de toolchain

- Pip original: firmware baseado em ESP-IDF 5.5.
- Muse SDK: firmware baseado em ESP-IDF 6.0.3.

A migração para ESP-IDF 6.0.3 faz parte do trabalho. A compatibilidade não será presumida.

## Estado atual

Esta branch contém a fundação versionada e os dois projetos upstream fixados. **Ainda não é um firmware integrado nem está pronta para gravação.** As próximas alterações devem portar os módulos de UI e criar a camada de adaptação Muse ↔ Pip, mantendo o firmware original e a página web publicados intactos.
