# Voz e IA: integração e validação

## O que o Muse fornece
O SDK Muse inclui suporte à placa Waveshare ESP32-S3-Touch-AMOLED-1.75C, captura de áudio, sessão com o serviço, tela de captions e gestão de conexão. A ponte Pip reage a eventos da sessão, sem duplicar hardware ou eventos por fragmentos de texto.

## Perfis de voz

### Voice notes (perfil padrão)
- Pressionar e segurar grava uma mensagem; soltar envia.
- Resposta textual pode aparecer como legenda.
- O modo de nota de voz não é conversa contínua.
- A reprodução de resposta nesse caminho pode exigir integração TTS, conforme o fluxo upstream.

### Realtime voice (experimental)
- Um toque inicia a chamada e outro encerra.
- Pressionar e segurar mantém o comportamento de voice note.
- O perfil experimental está em `firmware/sdkconfig.pip-realtime`.
- A compilação deste perfil passou na CI, mas o funcionamento depende do serviço/VM e da conta.
- A Waveshare 1.75C não tem AEC de hardware confirmada neste projeto; o caminho previsto é half-duplex, alternando microfone e alto-falante.

## Estado de integração
Os hooks de transcrição e resposta estão ligados à ponte de personalidade e limitados a uma ocorrência por turno. O modo speaking altera a expressão visual, sem pontuação adicional. Os perfis padrão e realtime voice já foram compilados em CI. Ainda não foram testados em dispositivo real nem com conta/VM.

## Token de dispositivo
O build alerta que `CONFIG_GADGET_SDK_TOKEN` não está configurado. O token deve ser gerado/obtido pelo fluxo oficial em [gadget.muse.ai](https://gadget.muse.ai/) (verifique o endereço oficial vigente antes de autenticar) e fornecido somente localmente ao build. Nunca comitar token, segredo, arquivo de configuração pessoal ou credencial em Git.

## Próximas validações
1. Configurar token localmente, sem versioná-lo.
2. Confirmar pareamento e sessão com serviço/VM.
3. Testar voice note e realtime voice separadamente.
4. Confirmar captions, resposta de voz, transcrição e troca de modos.
5. Verificar half-duplex e comportamento de botão/toque.
6. Depois da chegada da placa, validar áudio e microfone em hardware.

**Build verde significa que o código compila. Não comprova conexão, conversa, qualidade de áudio ou funcionamento físico.**
