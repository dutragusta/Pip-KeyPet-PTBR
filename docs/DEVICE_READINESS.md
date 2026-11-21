# Preparação e validação da Waveshare 1.75C

Este documento fecha a preparação de software e define o roteiro de bancada. Ele não declara testes físicos concluídos: a placa ainda precisa estar disponível.

## 1. Credencial Muse (SDK token)

O firmware upstream valida o token no formato `mgst_` seguido de 43 caracteres base64url canônicos (48 caracteres no total). O token é emitido em **[gadgets.muse.ai](https://gadgets.muse.ai/) → Account → SDK tokens**.

### Procedimento seguro no Windows

1. Abra o terminal **ESP-IDF v6.0.3**.
2. Entre no diretório `vendor/muse-gadget-sdk/esp32` do repositório integrado.
3. Aplique o overlay do Pip a partir da raiz do repositório antes de compilar:

```powershell
cd <caminho-do-repositorio>
sh firmware/scripts/apply_muse_overlay.sh
cd vendor/muse-gadget-sdk/esp32
```

Se o ambiente Windows não tiver `sh`, execute o script em Git Bash ou WSL, mantendo o ESP-IDF configurado no ambiente que fará o build.

4. Crie uma configuração isolada para a placa:

```powershell
$args = @(
  '-B', 'build-muse-waveshare-s3-175c',
  '-DIDF_TARGET=esp32s3',
  '-DSDKCONFIG=build-muse-waveshare-s3-175c/sdkconfig',
  '-DSDKCONFIG_DEFAULTS=sdkconfig.defaults;devices/sdkconfig.muse;devices/sdkconfig.muse-waveshare-s3-175c'
)
idf.py @args menuconfig
```

5. No menu, abra **ESP32 Device SDK** e preencha `CONFIG_GADGET_SDK_TOKEN` com o token. Salve e saia.
6. Compile com os mesmos argumentos:

```powershell
idf.py @args build
```

O perfil de placa define ESP32-S3, 32 MB flash, 8 MB octal PSRAM, AMOLED 466×466, touch, áudio e gestos QMI8658. O SDK ignora `build-*/` e o `sdkconfig` fica dentro de `build-muse-waveshare-s3-175c`, fora dos arquivos versionados.

**Não cole o token em código, README, issue, chat, linha de comando, variável rastreada ou workflow.** Não envie o token para este chat. Se ele for exposto, revogue-o e gere outro. O build de CI sem token só valida compilação; não conclui o provisionamento.

## 2. Pareamento, conta e sessão

A placa usa o fluxo de configuração Muse: BLE para descoberta/provisionamento pelo aplicativo e Wi-Fi para a conexão de rede e sessão. O guia do modelo indica dois toques rápidos no botão inferior para alternar a configuração Bluetooth do telefone; o pareamento também pode ser reiniciado em Settings → Reset pairing.

Checklist:
- [ ] Firmware inicializa e anuncia o dispositivo Muse esperado.
- [ ] Aplicativo Muse encontra o dispositivo por BLE.
- [ ] Pareamento/autenticação é concluído no iPhone.
- [ ] Credenciais Wi-Fi são provisionadas e a placa obtém IP.
- [ ] Conta/VM é alcançada e a sessão Hatch/Muse fica conectada.
- [ ] Enviar uma voice note, receber texto e ouvir resposta.
- [ ] Reiniciar placa e confirmar reconexão sem repetir setup.
- [ ] Remover pareamento e refazer o onboarding.

Não assumir que token válido equivale a conta/VM ativa: token, provisionamento Wi-Fi, vínculo de conta e sessão são etapas distintas.

## 3. Bluetooth e iPhone

A integração **não deve iniciar um segundo host BLE**. O Muse SDK já controla NimBLE, GATT, pareamento seguro, serviço de configuração e persistência das chaves. O iPhone usa o fluxo BLE do Muse para setup; a sessão de IA trafega pela conexão de rede. Não tratar a placa como fone Bluetooth nem adicionar um perfil de áudio Bluetooth sem requisito explícito.

Testes de coexistência:
- [ ] BLE setup ligado enquanto Wi-Fi está conectado.
- [ ] iPhone consegue descobrir/conectar e enviar configuração.
- [ ] Encerrar setup BLE não derruba a sessão Wi-Fi.
- [ ] Reconectar iPhone após sair/voltar do alcance.
- [ ] Alternar BLE setup durante uma sessão e observar reconexão.
- [ ] Repetir com roteador 2,4 GHz congestionado e a placa em bateria.
- [ ] Verificar logs por desconexões, falta de heap e reinicializações.

O ESP32-S3 compartilha o rádio entre Wi-Fi 2,4 GHz e BLE. A configuração do SDK já inclui modem sleep e parâmetros de coexistência; não alterar prioridades, número de conexões NimBLE ou modos de sleep sem evidência obtida na bancada.

## 4. Matriz de teste físico

Registrar data, revisão da placa, versão do firmware, resultado e observações para cada item.

| Subsistema | Procedimento | Aprovação |
|---|---|---|
| Boot/PSRAM | Ligar, observar logs e reiniciar 10 vezes | Sem panic/reset loop; PSRAM reconhecida |
| Display | Testar orientação, cores, brilho, animação e tela em repouso | Sem artefatos persistentes, tearing grave ou travamento |
| Olhos Pip | Rodar idle, blink e cada grupo de humor | Somente dois olhos; sem boca, nariz ou blush |
| Touch | Tocar centro/bordas, swipe e seleção de opção | Eventos corretos, sem zonas mortas relevantes |
| Microfone | Gravar voz normal e baixa, em ambiente silencioso | Voz inteligível, sem clipping constante |
| Alto-falante | Ouvir resposta em níveis baixo/médio/alto | Áudio inteligível, sem cortes ou distorção anormal |
| Realtime voice | Conversar em half-duplex e interromper resposta | Alternância mic/alto-falante sem deadlock |
| Acelerômetro | Lift, shake leve/forte e repouso | Wake/shake detectados sem falsos positivos; calibrar limiar |
| NVS | Criar estado, reiniciar, restaurar e testar blob inválido | Estado persiste; blob inválido é rejeitado sem crash |
| Wi-Fi/BLE | Provisionar, perder rede, voltar e reconectar | Reconexão previsível, sem travamento |
| Bateria/PMU | Testar USB, bateria, carga e leitura percentual | Telemetria coerente; sem aquecimento anormal |
| Sono/energia | Deixar em idle, apagar tela, acordar por botão/lift | Consumo e wake coerentes; sem perda de estado |

**NVS:** validar separadamente a namespace `pip_pet` e o namespace/configuração do SDK Muse. Não apagar a NVS inteira como primeiro recurso: isso também pode remover pareamento e Wi-Fi.

**Bateria:** o driver usa AXP2101. Registrar percentual e estado de carga em 100%, ~50% e nível baixo, se possível, e medir autonomia real. Não inferir autonomia a partir de corrente nominal.

## 5. Critério de conclusão desta fase

Esta fase fica concluída somente quando:
1. Token configurado localmente e não versionado.
2. Pareamento no iPhone e vínculo com conta/VM confirmados.
3. Voice note, resposta em texto e áudio confirmados.
4. Coexistência BLE/Wi-Fi validada.
5. Todos os itens da matriz física aprovados ou registrados como falha conhecida com correção planejada.

Os builds de CI já aprovados não substituem nenhum desses testes físicos. Navegação, aplicativos e minigames do Pip continuam fora do escopo desta fase.
