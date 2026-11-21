# Voz e IA: caminhos de integração

## O que já vem do Muse

A Waveshare ESP32-S3-Touch-AMOLED-1.75C já é suportada pelo Muse SDK. A base fornece captura de áudio, conexão à sessão do Muse, tela para captions e gerenciamento de conexão. O Pip recebe os estados do dispositivo e os transforma em eventos de personalidade.

## Dois modos diferentes

### 1. Voice notes (perfil padrão)

É o modo habilitado no primeiro build:

- pressionar e segurar o botão de fala grava uma mensagem;
- ao soltar, o áudio é enviado ao serviço;
- a resposta textual aparece como legenda na tela;
- o modo de voice note não é uma conversa contínua e o código upstream indica que a reprodução de respostas exige uma integração TTS própria.

Esse perfil serve para validar a base e a captura/envio de áudio, mas não entrega sozinho a experiência de conversa natural contínua.

### 2. Chamadas em tempo real (experimental)

O Muse SDK oferece `CONFIG_MUSE_REALTIME_VOICE`:

- um toque no botão de fala inicia a chamada;
- outro toque encerra;
- manter o botão pressionado continua sendo voice note;
- a chamada depende de a VM/serviço da conta aceitar chamadas desse dispositivo;
- na Waveshare 1.75C, sem AEC de hardware declarado pelo board, o áudio opera em half-duplex: o microfone fecha enquanto o alto-falante reproduz a fala.

O perfil de compilação experimental está em `firmware/sdkconfig.pip-realtime` e já compilou com sucesso em CI, separadamente do perfil padrão. Isso valida o firmware, mas não comprova que a conta/VM aceite a chamada; isso exige teste de execução.

## Credenciais

A compilação atual alerta que não há `CONFIG_GADGET_SDK_TOKEN`. O token de dispositivo precisa ser obtido pelo fluxo oficial em gadgets.muse.ai e configurado fora do repositório. Não colocar tokens, senhas ou chaves em arquivos versionados.

## Próximos passos técnicos

1. Compilar o perfil experimental de chamadas em tempo real.
2. Conferir o comportamento da sessão e os estados de voz que chegam à ponte Pip.
3. Decidir como o conteúdo da conversa afeta humor, carinho e expressões sem gerar eventos repetidos a cada frame.
4. Adicionar gestos do acelerômetro como eventos de sacudir/pegar o Pip.
5. Só então preparar uma imagem de firmware e validar áudio, touch, sensor e persistência no hardware.

Nenhuma validação física foi feita até agora.
