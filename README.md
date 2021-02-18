# Projeto Final de Engenharia - Indago

## Sumário
* [Integrantes](#integrantes)
* [Professor Mentor](#professor-mentor)
* [Introdução](#introdução)
* [Instalando CCS no Ubuntu 20.04](#instalando-ccs-no-ubuntu-20.04)

### Integrantes
* [André Ejzenmesser](https://github.com/decoejz)
* [Francisco Ciol Rodrigues Aveiro](https://github.com/franciol)
* [Gustavo Gobetti Bertocco](https://github.com/GustavoGB)
* [Manoela Cirne Lima de Campos](https://github.com/manucirne)

### Professor Mentor
* [Rafael Corsi](https://github.com/rafaelcorsi)

### Introdução
Para o desenvolvimento do projeto, foi utilizado o projeto do WISP 5. A documentação pode ser encontrada [aqui](https://sites.google.com/uw.edu/wisp-wiki/wisp5).

Para programar o WISP 5 é necessário a utilização Code Composer Studio ([CCS](https://software-dl.ti.com/ccs/esd/documents/ccs_downloads.html)), cuja instalação no ubuntu 20.04 esta descrita em [Instalando CCS no Ubuntu 20.04](#instalando-ccs-no-ubuntu-20.04).

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

Ao finalizar, abra o aplicativo e na aba superior clique em `Help` > `Install New Software...`

Em `Work with:` Selecione `--All Available Sites--` e na barra de seleção desça até encontrar `TI Compiler Tools` e marque a opção `MSP430 Compiler Tools` cuja versão for equivalente a `4.3.8`. Aguarde a instalação e ao finalizar, reinicie o programa.

Agora ele esta pronto para usar e compilar o WISP 5.