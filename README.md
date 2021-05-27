# Projeto Final de Engenharia - Indago

## Sumário
* [Integrantes](#integrantes)
* [Professor Mentor](#professor-mentor)
* [Introdução](#introdução)
* [Instalando CCS no Ubuntu 20.04](#instalando-ccs-no-ubuntu-20.04)
* [Instalando CCS no Windows 10](#instalando-ccs-no-windows-10)
* [Importando Projetos para o CCS](#importando-projetos-para-o-ccs)
* [Compilando e Programando a Placa](#compilando-e-programando-a-placa)

### Integrantes
* [André Ejzenmesser](https://github.com/decoejz)
* [Francisco Ciol Rodrigues Aveiro](https://github.com/franciol)
* [Gustavo Gobetti Bertocco](https://github.com/GustavoGB)
* [Manoela Cirne Lima de Campos](https://github.com/manucirne)

### Professor Mentor
* [Rafael Corsi](https://github.com/rafaelcorsi)

### Introdução
Para o desenvolvimento do projeto, foi utilizado o projeto do WISP 5. A documentação pode ser encontrada [aqui](https://sites.google.com/uw.edu/wisp-wiki/wisp5).

Para programar o WISP 5 é necessário a utilização Code Composer Studio ([CCS](https://software-dl.ti.com/ccs/esd/documents/ccs_downloads.html)), cuja instalação no ubuntu 20.04 esta descrita em [Instalando CCS no Ubuntu 20.04](#instalando-ccs-no-ubuntu-20.04). Para instalar em windows, clique em [Instalando CCS no Windows 10](#instalando-ccs-no-windows-10).

### Instalando CCS no Ubuntu 20.04

Antes de instalar o programa, é necessário ter o sistema atualizado, como esta descrito no [site oficial](https://software-dl.ti.com/ccs/esd/documents/ccsv10_linux_host_support.html).

```BASH
sudo apt update
```

Com o S.O. atualizado, algumas dependencias devem ser instaladas.

```BASH
sudo apt install libc6:i386 libusb-0.1-4 libgconf-2-4 libncurses5 libpython2.7 libtinfo5
```

Instaladas as dependências, o [CCS 10.2.0](https://software-dl.ti.com/ccs/esd/documents/ccs_downloads.html) deve ser instalado. Para isso, descompacte o arquivo baixado da internet, e abra o arquivo `ccs_setup_10.2.0.00009.run` que ira te guiar pela instalação.

Feito isso, abra a pasta que o aplicativo foi instalado e vá em `<REPO_CCS>/ccs/install_scripts` e execute o comando

```BASH
sudo ./install_drivers.sh
```

Ao finalizar, abra o aplicativo e na aba superior clique em `Help` > `Install New Software...`

Em `Work with:` Selecione `--All Available Sites--` e na barra de seleção desça até encontrar `TI Compiler Tools` e marque a opção `MSP430 Compiler Tools` cuja versão for equivalente a `4.3.8`. Aguarde a instalação e ao finalizar, reinicie o programa.

Agora ele esta pronto para usar e compilar o WISP 5.

### Instalando CCS no Windows 10

Antes de instalar, confirme que seu Windows 10 está atualizado, e também verifique se a arquitetura dele é x86_64(amd64). Caso seu sistema seja 32bit, use uma versão anterior ao CCS9. 
Baixe o [CCS 10.2.0](https://software-dl.ti.com/ccs/esd/documents/ccs_downloads.html) para windows 10 e execute-o. O instalador ira te guiar pela instalação.

Ao finalizar, abra o aplicativo e na aba superior clique em `Help` > `Install New Software...`

Em `Work with:` Selecione `--All Available Sites--` e na barra de seleção desça até encontrar `TI Compiler Tools` e marque a opção `MSP430 Compiler Tools` cuja versão for equivalente a `4.3.8`. Aguarde a instalação e ao finalizar, reinicie o programa.

### Importando Projetos para o CCS

Com o CCS aberto, clique com o botão direito dentro do `Project Explorer` e selecione `Import > CCS Projects`, conforme a figura abaixo.

![Indisponível](https://github.com/Insper/21a-PFE-INDAGO/blob/master/images/importCCS.png)

Uma nova janela se abrirá. Clique em `Browse...` e selecione o projeto que deseja abrir. Verifique ainda nessa janela que o projeto correto esta selecionado. Deixe marcado a opção para importar juntos projetos dependentes para evitar problemas de compilação e escrita. O nome dessa opção é `Automatically import referenced projects found in same search-directory`. Por fim clique em `Finish`.

![Indisponível](https://github.com/insper/21a-PFE-INDAGO/blob/master/images/importWindowCCS.png)

O projeto esta importado! Agora basta compilar e programar sua placa.

### Compilando e Programando a Placa

Para programar a placa é muito simples. Por padrão, na barra de ferramentas na parte superior do CCS deve ter um desenho em formato de martelo. Basta abrir algum arquivo do projeto que deseja compilar e clicar neste simbolo.

![Indisponível](https://github.com/insper/21a-PFE-INDAGO/blob/master/images/martelo.png)

Caso tenho algum erro ou aviso de compilação eles aparecerão na aba `Problems` do CCS.

![Indisponível](https://github.com/insper/21a-PFE-INDAGO/blob/master/images/problemsCCS.png)

Uma vez que o projeto esta compilado e sem erros (avisos não impedem a programação), basta programar a placa. Para isso, no mesmo local do martelo de compilação haverá um desenho de uma pasta com arquivo, que ao passar o mouse em cima aparecerá `Flash`. Com a placa ja conectada em seu computador, basta clicar nele que deve reconhecer a placa imediantamente e em seguida programá-la.

![Indisponível](https://github.com/insper/21a-PFE-INDAGO/blob/master/imagens/programando.png)
