# Pendências técnicas prioritárias (fora da interface Tamagotchi)

A interface, navegação e minigames do Pip ficam para uma etapa posterior. Neste momento, a prioridade é deixar a base Muse + avatar + voz/conectividade bem documentada e pronta para validação quando a placa chegar.

## 1. Credencial do dispositivo
- [ ] Obter o token oficial do dispositivo pelo fluxo Muse.
- [ ] Configurar token somente no ambiente local de build.
- [ ] Confirmar que tokens e arquivos pessoais não são rastreados pelo Git.

## 2. Sessão, pareamento e IA
- [ ] Validar pareamento do ESP32 com a conta/VM.
- [ ] Testar envio de voice note, captions e resposta.
- [ ] Testar chamada realtime experimental, se a conta/VM permitir.
- [ ] Confirmar transições de estados (idle/listening/thinking/speaking/error).
- [ ] Confirmar em hardware que as respostas de áudio do perfil padrão reproduzem corretamente pelo alto-falante (o guia upstream descreve esse recurso).

## 3. Bluetooth e iPhone
- [ ] Auditar coexistência entre BLE do Muse e conectividade Bluetooth do iPhone.
- [ ] Evitar inicializar um segundo host BLE ou stack concorrente.
- [ ] Definir qual fluxo é responsável por pairing, descoberta e conexão.
- [ ] Verificar consumo, reconexão e comportamento após perda de sinal.

## 4. Build e distribuição
- [x] Build CI padrão.
- [x] Build CI experimental realtime voice.
- [ ] Criar procedimento reproduzível para builds locais.
- [ ] Registrar versão dos submódulos e SDK, flags e configurações usadas.
- [ ] Definir artefato e política de release somente após testes físicos.

## 5. Testes físicos (quando houver placa)
- [ ] Display e renderizador: escala, taxa de atualização, tearing e brilho.
- [ ] Touch: toque, gesto, áreas e latência.
- [ ] Microfone, alto-falante e volume.
- [ ] Realtime voice: half-duplex, cortes e interrupção.
- [ ] Acelerômetro: wake/shake e calibrar thresholds.
- [ ] NVS: salvar, reiniciar, restaurar e testar estado inválido.
- [ ] Wi-Fi/Bluetooth: pareamento, reconexão e coexistência.
- [ ] Bateria: consumo, aquecimento e autonomia.
- [ ] Testar comportamento em falha de rede, serviço indisponível e reinicialização.

## 6. Interface Pip (adiada)
- [ ] Portar aplicativos e interações do Pip.
- [ ] Navegação de pet e ações feed/play/poke.
- [ ] Contexto visual/expressões adicionais.

## Critério para firmware de teste
Só preparar um release de teste para flash quando: token e pareamento estiverem resolvidos, builds estiverem reproduzíveis, revisão de segurança de credenciais concluída e documentação de risco/limitações estiver atualizada. Mesmo então, o firmware será experimental até passar pelo checklist físico.
