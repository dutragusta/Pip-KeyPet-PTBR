# Pip-KeyPet PT-BR 🇧🇷

Interface web do **Pip-KeyPet** traduzida para português brasileiro (PT-BR), publicada pelo GitHub Pages.

O Pip é um Tamagotchi virtual em um chaveiro com tela, baseado na placa **Waveshare ESP32-S3-Touch-AMOLED-1.75C**. A interface permite conectar o dispositivo, configurar recursos e atualizar o firmware pelo navegador.

## Acessar a interface

🌐 **[Abrir o painel Pip-KeyPet PT-BR](https://dutragusta.github.io/Pip-KeyPet-PTBR/)**

A interface foi adaptada para português brasileiro, preservando o layout e os identificadores técnicos necessários ao funcionamento do painel.

## Requisitos

- Chaveiro compatível com **Waveshare ESP32-S3-Touch-AMOLED-1.75C**.
- Cabo USB-C com suporte a transferência de dados.
- Computador com **Google Chrome** ou **Microsoft Edge** atualizado.
- Bluetooth habilitado quando utilizar a conexão sem fio.

> O acesso às funções USB e Bluetooth depende do suporte do navegador e das permissões concedidas pelo usuário. Safari e Firefox podem não oferecer as APIs necessárias.

## Como usar

1. Abra o [painel PT-BR](https://dutragusta.github.io/Pip-KeyPet-PTBR/) no Chrome ou Edge.
2. Conecte o chaveiro ao computador usando um cabo USB-C de dados.
3. Clique em **Conectar via cabo** e autorize o acesso ao dispositivo.
4. Acesse **Configurações** para ajustar as opções disponíveis.
5. Para atualizar o dispositivo, abra **Gravar / atualizar**, clique em **Gravar** e siga as instruções exibidas na tela.

A interface também apresenta opções de conexão Bluetooth, configurações do crachá, links para QR Code, economia de energia, notificações e ferramentas de depuração.

## Recursos da interface

- Interface traduzida para português brasileiro.
- Conexão com o chaveiro por USB e Bluetooth, conforme suporte do navegador e do dispositivo.
- Configuração do crachá e dos links de QR Code.
- Ajustes de tela, brilho, tema e economia de energia.
- Preferências para notificações do iPhone.
- Gravação e atualização do firmware pelo navegador.
- Acesso à interface de depuração do projeto original.

## Observações importantes

- Este repositório contém a **interface web traduzida**, não uma cópia completa do firmware e de todos os arquivos do projeto original.
- O painel carrega o arquivo de firmware publicado pelo projeto original: [NovikovVisuals/Pip-KeyPet](https://github.com/NovikovVisuals/Pip-KeyPet).
- A página de depuração ainda utiliza a versão original, que pode estar em outro idioma.
- Para obter instruções completas de compilação, arquivos do firmware e demais componentes, consulte o [repositório original](https://github.com/NovikovVisuals/Pip-KeyPet).
- A gravação de firmware altera o software do dispositivo. Não desconecte o chaveiro durante o processo.

## Desenvolvimento e publicação

O site é publicado automaticamente pelo GitHub Actions sempre que há alterações na branch `main`.

- Arquivo principal da interface: [`index.html`](index.html)
- Workflow do GitHub Pages: [`.github/workflows/pages.yml`](.github/workflows/pages.yml)
- Site publicado: [dutragusta.github.io/Pip-KeyPet-PTBR](https://dutragusta.github.io/Pip-KeyPet-PTBR/)

## Créditos e licença

Este projeto é uma tradução/adaptação da interface do [Pip-KeyPet, de NovikovVisuals](https://github.com/NovikovVisuals/Pip-KeyPet).

O projeto original informa ser distribuído sob a licença **MIT**. Consulte o repositório original e seus avisos de licença para os termos aplicáveis ao código e aos componentes de terceiros. Esta adaptação não reivindica a autoria do projeto original.

---

**Tradução:** português brasileiro (PT-BR)  
**Projeto original:** [NovikovVisuals/Pip-KeyPet](https://github.com/NovikovVisuals/Pip-KeyPet)  
**Versão adaptada:** [dutragusta/Pip-KeyPet-PTBR](https://github.com/dutragusta/Pip-KeyPet-PTBR)
