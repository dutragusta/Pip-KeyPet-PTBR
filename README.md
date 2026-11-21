# Pip-KeyPet PT-BR + Muse Gadget 🤖

Integração em desenvolvimento do **Pip-KeyPet** com o **Muse Gadget SDK**, com objetivo de criar um companheiro portátil com personalidade e interação por voz/IA.

## Projeto
- **Pip:** personagem, expressões, humor, necessidades, animações e comportamento.
- **Muse Gadget SDK:** firmware, hardware, LVGL, áudio e conectividade.
- **Placa-alvo:** Waveshare ESP32-S3-Touch-AMOLED-1.75C.

## Referências visuais
As imagens abaixo são referências do projeto Pip-KeyPet original e ajudam a preservar o estilo do personagem.

| Expressões do Pip | Reações do Pip |
|---|---|
| ![Expressões base](docs/references/pip-expressoes-base.png) | ![Reações](docs/references/pip-expressoes-reacao.png) |

| Sim e não | Painel de expressões |
|---|---|
| ![Sim e não](docs/references/pip-expressoes-sim-nao.png) | ![Painel](docs/references/pip-painel-expressoes.png) |

Créditos: [NovikovVisuals/Pip-KeyPet](https://github.com/NovikovVisuals/Pip-KeyPet). Imagens adicionadas como referência, sem reivindicar autoria do personagem.

## Status
**Firmware: integração em andamento.** O Muse é a base de hardware e sessões; o Pip está conectado ao avatar, personalidade e eventos de conversa.

- [x] Submódulos upstream pinados.
- [x] Motor de personalidade integrado e testes portáveis.
- [x] Avatar adaptado e compilado.
- [x] Eventos de transcrição/resposta, toque, lift-wake e shake conectados.
- [x] Build automatizado padrão e perfil experimental realtime voice aprovados.
- [x] Procedimento seguro de credenciais/token e build local documentado.
- [ ] Configurar token real e validar sessão/pareamento com serviço e conta.
- [ ] Validar coexistência Bluetooth/Wi-Fi e conexão com iPhone na placa.
- [ ] Testes físicos de áudio, display, touch, acelerômetro, NVS e bateria.
- [ ] Aplicativos e navegação do Pip (planejado para uma etapa posterior).

## Documentação técnica
- [Integração e arquitetura](INTEGRATION.md)
- [Voz e IA](docs/VOICE_INTEGRATION.md)
- [Preparação e testes da Waveshare](docs/DEVICE_READINESS.md)
- [Pendências técnicas prioritárias](docs/REMAINING_WORK.md)

## Repositórios upstream
- [Pip-KeyPet](https://github.com/NovikovVisuals/Pip-KeyPet)
- [Muse Gadget SDK](https://github.com/facebookincubator/muse-gadget-sdk)

## Interface web PT-BR
[Abrir versão web](https://dutragusta.github.io/Pip-KeyPet-PTBR/)

## Licenças
Consulte as licenças e avisos dos projetos upstream antes de redistribuir binários ou versões derivadas.