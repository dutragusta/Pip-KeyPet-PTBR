# Pendências técnicas prioritárias

A etapa atual é preparar e validar a base Muse + Pip na Waveshare ESP32-S3-Touch-AMOLED-1.75C. Aplicativos, navegação e minigames do Pip ficam para depois.

## Preparação de software já realizada
- [x] Submódulos upstream fixados em commits conhecidos.
- [x] Build CI do firmware para a placa.
- [x] Build CI do perfil experimental realtime voice.
- [x] Testes portáveis da personalidade.
- [x] Hooks de transcrição/resposta, toque, lift e shake compilados.
- [x] Persistência Pip em namespace NVS separado, com schema e validação.
- [x] Procedimento local de token e build documentado.
- [x] Fluxo de pareamento, arquitetura BLE/Wi-Fi e matriz de testes documentados.

## Bloqueadores que exigem conta ou placa
- [ ] Emitir token em gadgets.muse.ai → Account → SDK tokens e configurar localmente.
- [ ] Validar pareamento BLE pelo iPhone.
- [ ] Validar Wi-Fi, vínculo de conta/VM e sessão Hatch/Muse.
- [ ] Confirmar envio de voice note, resposta em captions e áudio no alto-falante.
- [ ] Testar coexistência BLE + Wi-Fi + iPhone, incluindo reconexão.
- [ ] Testar fisicamente display, touch, microfone, alto-falante e controles.
- [ ] Calibrar acelerômetro para lift/shake.
- [ ] Validar NVS em ciclos de reboot e recuperação de estado inválido.
- [ ] Validar bateria, carregamento, consumo e autonomia.
- [ ] Repetir testes de estabilidade e registrar falhas.

## Depois desta etapa
- [ ] Portar aplicativos e navegação do Pip.
- [ ] Integrar ações feed/play/poke à interface.
- [ ] Adicionar jogos e utilitários do Pip.

## Critério de firmware para teste
Não declarar firmware pronto para uso ou release antes de concluir o checklist físico em `docs/DEVICE_READINESS.md`. CI verde comprova compilação e testes automatizados, não pareamento, áudio, tela ou bateria.
