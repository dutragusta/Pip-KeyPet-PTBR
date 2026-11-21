# Voz e IA: integração e validação

## Hardware e suporte upstream
O Muse SDK contém suporte específico para a Waveshare ESP32-S3-Touch-AMOLED-1.75C. O guia upstream descreve voice notes, respostas exibidas como captions e reproduzidas pelo alto-falante, além de controles de tela e volume. Nesta integração, esses recursos ainda precisam ser validados fisicamente.

## Voice notes (perfil padrão)
- Segurar o botão superior grava; soltar envia a mensagem.
- O SDK da placa descreve resposta textual na tela e resposta de áudio pelo alto-falante.
- Swipe entre tela principal, última resposta e configurações; controle de volume por gesto no avatar.
- Este comportamento é documentado upstream; a integração local ainda não foi testada na placa.

## Realtime voice (experimental)
- O perfil experimental está em `firmware/sdkconfig.pip-realtime`.
- O fluxo usa chamadas em tempo real, com toque para iniciar/encerrar e push-to-talk conforme o SDK.
- A compilação deste perfil passou na CI, mas o funcionamento depende do serviço/VM e da conta.
- A Waveshare 1.75C não tem AEC de hardware confirmada neste projeto; a configuração prevê half-duplex, alternando microfone e alto-falante.

## Estado da integração
Hooks de transcrição e resposta estão conectados à ponte de personalidade, limitados a uma ocorrência por turno. O estado speaking altera apenas a expressão visual. Os perfis padrão e realtime voice já foram compilados em CI. Não houve teste em dispositivo real nem validação de conta/VM.

## Token de dispositivo
O build alerta que `CONFIG_GADGET_SDK_TOKEN` não está configurado. O token deve ser obtido pelo fluxo oficial do Muse e fornecido somente localmente ao build. Nunca comitar tokens, segredos, arquivos de configuração pessoais ou credenciais em Git.

## Próximas validações
1. Configurar token local, sem versioná-lo.
2. Confirmar pareamento e sessão com serviço/VM.
3. Testar voice note e captions; confirmar áudio de resposta.
4. Testar realtime voice, se a conta/VM permitir.
5. Confirmar interrupções, transições de modo e comportamento half-duplex.
6. Quando houver placa, validar áudio, microfone, controles por toque e qualidade de chamada.

**Build verde significa que o código compila. Não comprova conexão, sessão, qualidade de áudio ou funcionamento físico.**
