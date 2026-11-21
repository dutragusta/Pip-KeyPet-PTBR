# Pip-KeyPet — um bichinho de estimação no chaveiro

Pip é um bichinho virtual que vive em um chaveiro redondo com tela. Ele olha para você, fica feliz, emburrado ou com sono, pede para passear e comer, e reage ao que acontece ao redor.

Além disso, ele exibe notificações do iPhone, controla músicas e pode funcionar como crachá, cartão de visita com QR Code, controle para apresentações, medidor de ruído e plataforma para minijogos.

## O que você precisa

- **Chaveiro Waveshare ESP32-S3-Touch-AMOLED-1.75C** (disponível na AliExpress, Amazon e na loja da Waveshare).
- **Cabo USB-C com transferência de dados** (não pode ser um cabo exclusivo para carregamento).
- **Computador** com Windows, macOS ou Linux e navegador **Google Chrome** ou **Microsoft Edge**.

## Como instalar o firmware no seu Pip

**Método mais simples:** abra https://novikovvisuals.github.io/Pip-KeyPet/ no Chrome ou Edge, conecte o chaveiro ao computador pelo cabo USB e clique em **“Conectar via cabo”**. Depois, acesse a aba **“Gravar / atualizar”** e clique em **“Gravar”**. Não é necessário baixar nenhum arquivo.

### Instalação sem internet

1. **Baixe o projeto.** Nesta página do GitHub, clique no botão verde **Code → Download ZIP** e extraia o arquivo baixado.
2. **Abra o painel.** Na pasta extraída, execute o arquivo correspondente ao seu sistema:
   - Windows: **`Pip-Windows.bat`**
   - macOS: **`Pip-Mac.command`** (se o Mac impedir a abertura, clique com o botão direito no arquivo e escolha “Abrir”; confirme novamente em “Abrir”).
   - Linux: **`Pip-Linux.sh`**

   O painel do Pip será aberto no navegador.
3. **Grave o firmware.** Conecte o chaveiro ao computador, abra a aba **“Gravar / atualizar”**, clique em **“Gravar”** e selecione **USB JTAG/serial** na lista. Depois de aproximadamente um minuto, o Pip deverá iniciar.

Na aba **“Configurações”**, você pode definir o nome exibido no crachá, adicionar seus links para o QR Code, escolher quando o Pip entrará em repouso e ativar ou desativar os recursos disponíveis. As configurações ficam salvas no próprio chaveiro.

### Conectar ao iPhone

No iPhone, acesse **Ajustes → Bluetooth → Pip** e confirme o código usando o botão superior do chaveiro. Quando o iPhone solicitar, autorize a exibição de notificações.

## Solução de problemas

- **O chaveiro não aparece na lista:** experimente outro cabo USB ou outra porta do computador. No Linux, execute uma vez `sudo usermod -aG dialout $USER` e entre novamente na sua sessão.
- **O processo de gravação não começa:** mantenha pressionado o botão inferior do chaveiro, pressione rapidamente o botão superior e, em seguida, solte o botão inferior. O chaveiro entrará no modo de gravação. Depois, clique em **“Gravar”** novamente.
- **A página informa que o navegador não é compatível:** abra o painel no Chrome ou Edge. Safari e Firefox não oferecem suporte aos recursos USB utilizados pelo projeto.
- **A bateria descarrega rapidamente:** nas configurações, defina o tempo para entrar em repouso como **15 a 30 segundos**. A tela e a animação do rosto são responsáveis por grande parte do consumo de energia.

## O que o Pip pode fazer

- **Personalidade:** cerca de 45 emoções. O humor muda de acordo com alimentação, sono, brincadeiras, atenção, passeios, horário do dia e acontecimentos. Você pode acariciá-lo, sacudi-lo, virá-lo com a tela para baixo, soprar nele e apresentá-lo a outras pessoas usando o botão inferior.
- **Aplicativos e ferramentas:** relógio, cuidados com o Pip, Quick QR, medidor de ruído, crachá, temporizador, cronômetro, lanterna, personalização de estilo, Bluetooth, notificações, música, câmera (botão de disparo para iPhone) e controle de apresentações (avançar slides, ponteiro, rolagem e arrastar). Também inclui jogos: bolinha, jogo da velha infinito, bola 8, cara ou coroa, dado e labirinto.
- **Economia de energia:** entra em repouso automaticamente e pode despertar com um toque, pelo botão, ao ser segurado na mão ou quando recebe uma notificação.
- **Privacidade:** as notificações ficam ocultas por padrão até serem abertas. Códigos, senhas e dados bancários não são armazenados.

## Para desenvolvedores

O diretório `ui/` contém uma interface portátil em C com LVGL 9.5, compartilhada por três compilações: firmware (ESP-IDF 5.5), simulador no navegador e gravador de console com verificações. Consulte [CLAUDE.md](CLAUDE.md) para obter mais detalhes.

```bash
git submodule update --init                                     # LVGL
cmake -S sim -B build -G Ninja && cmake --build build && python3 sim/check.py   # simulador e testes
emcmake cmake -S sim -B build-web -G Ninja && cmake --build build-web && python3 sim/serve.py   # simulador web
. ~/esp/esp-idf/export.sh && firmware/flash.sh                  # compilação própria para a placa, com registro de log
tools/release.sh                                                # firmware para o painel: docs/firmware/firmware.js
```

O painel é composto por `docs/index.html` (configurações e gravação do firmware, com Web Serial e Web Bluetooth diretamente no navegador) e `docs/debug.html` (árvore de emoções, histórico, demonstração de emoções, controles de regras e modo de desenvolvedor).

## Licença

MIT. Consulte o arquivo [LICENSE](LICENSE).

## Créditos

- [LVGL](https://lvgl.io) (MIT)
- [esptool-js](https://github.com/espressif/esptool-js) (Apache-2.0)
- Fontes JetBrains Mono e IBM Plex Mono (SIL OFL)
- Ícones [Font Awesome Free](https://fontawesome.com) (SIL OFL / CC BY 4.0)

---

**Projeto original:** [NovikovVisuals/Pip-KeyPet](https://github.com/NovikovVisuals/Pip-KeyPet)

Esta tradução do README foi preparada em português brasileiro. Os nomes de arquivos, comandos, APIs, protocolos e identificadores técnicos foram mantidos no idioma original para preservar a compatibilidade com o projeto.
