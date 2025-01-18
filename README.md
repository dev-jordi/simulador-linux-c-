# Simulador de Sistema de Arquivos Virtual

Este projeto é um simulador de sistema de arquivos desenvolvido em C++. Ele permite criar e gerenciar um sistema de arquivos virtual, incluindo pastas e arquivos, além de salvar e carregar o estado do sistema.

---

## **Funcionalidades**

- **Criar Arquivos**: Crie arquivos no diretório atual com conteúdo personalizado.
- **Criar Pastas**: Adicione pastas para organizar seus arquivos.
- **Navegar entre Diretórios**: Use comandos como `cd` para acessar pastas e `ls` para listar o conteúdo.
- **Excluir Arquivos ou Pastas**: Remova arquivos ou pastas do sistema.
- **Salvar Estado**: Salve o sistema de arquivos em um arquivo para recuperação futura.
- **Carregar Estado**: Restaure o sistema de arquivos de um arquivo salvo.

---

## **Como Usar**

### **1. Compilação**
Certifique-se de ter um compilador C++ instalado, como `g++`. Para compilar o código, use o comando:

```bash
g++ -o filesystem main.cpp
```
### **2. Execução
Após a compilação, execute o programa com:

```bash
./filesystem
```
---
### **3. Comandos Disponíveis
Durante a execução, você terá acesso às seguintes opções:

- Criar Arquivo: Adicione um novo arquivo com nome e conteúdo.
- Criar Pasta: Adicione uma nova pasta no diretório atual.
- Listar Conteúdo: Exiba o conteúdo do diretório atual.
- Mudar Diretório: Navegue entre pastas usando o comando `cd`.
- Remover Arquivo/Pasta: Exclua itens do sistema de arquivos.
- Salvar Estado: Salve o estado atual do sistema no arquivo `filesystem.dat`.
- Carregar Estado: Restaure o sistema de arquivos a partir de um arquivo salvo.
- Sair: Finalize o programa.


### Estrutura do Sistema de Arquivos

O sistema utiliza uma estrutura de árvore para organizar arquivos e pastas. Cada nó pode ser:

- Um arquivo, contendo um nome e conteúdo.
- Uma pasta, contendo um nome e outros nós (arquivos ou pastas).

### Exemplo de Uso
Criar Arquivos e Pastas:

```text
1. Criar Arquivo
Nome do arquivo: exemplo.txt
Conteúdo: Este é um arquivo de exemplo.

2. Criar Pasta
Nome da pasta: documentos
```
## Navegar e Listar Conteúdo

```text
3. Listar Conteúdo
- [F] exemplo.txt
- [D] documentos

4. Mudar Diretório
Nome do diretório: documentos
```

##Salvar e Carregar Estado
```text
6. Salvar Estado 💾				``	
Sistema salvo em filesystem.dat

7.  Carregar Estado 💽
Sistema carregado de filesystem.dat
```

### Requisitos
- Compilador C++ compatível com C++11 ou superior.
- Sistema operacional Linux, macOS ou Windows.

---

### Possíveis Melhorias
-Adicionar comandos avançados, como mover (mv) e copiar (cp) arquivos/pastas.
-Implementar permissões de arquivo.
-Criar uma interface gráfica com bibliotecas como Qt ou SFML.

### Contribuindo
Contribuições são bem-vindas! Sinta-se à vontade para abrir um pull request ou relatar problemas na seção de issues.

---

## 📜 Licença
Este projeto está licenciado sob a **licença MIT**.