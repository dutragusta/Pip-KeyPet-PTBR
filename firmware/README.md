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
| Renderizador dos olhos do Pip | Ainda precisa ser integrado à tela LVGL do Muse |
| Navegação e aplicativos Pip | Ainda precisam ser portados |
| Eventos de voz Muse → reações Pip | Próxima etapa |
| BLE do iPhone + BLE Muse | Requer desenho de coexistência; não iniciar hosts independentes |
| Build integrado | Ainda não configurado nem validado |

## Organização

- `components/pip_personality/`: componente que reutiliza o núcleo de necessidades do Pip.
- `../vendor/pip-keypet/ui/`: origem upstream dos módulos C portáveis.
- `../vendor/muse-gadget-sdk/esp32/`: projeto ESP-IDF e drivers da Muse.

## Próxima implementação

1. Conectar este componente ao projeto ESP-IDF da Muse por meio de `EXTRA_COMPONENT_DIRS` ou overlay CMake, sem editar o submódulo upstream.
2. Criar o adaptador LVGL do rosto do Pip usando o display já inicializado pelo Muse.
3. Portar o loop de atualização e a persistência do pet.
4. Mapear os estados da sessão de voz para expressões do Pip.
5. Portar shell/apps por grupos, evitando inicialização duplicada de tela, touch, áudio, energia ou Bluetooth.

**Este diretório é uma base de desenvolvimento, não um firmware pronto para flash.**
