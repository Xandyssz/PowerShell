# Sistema de Arquivos em C - Shell

![C](https://img.shields.io/badge/language-C-blue) ![Status](https://img.shields.io/badge/status-em%20desenvolvimento-yellow)

Este projeto implementa um **interpretador de comandos (shell) em C** para manipulação de um sistema de arquivos customizado, conforme proposto na disciplina de **Sistemas Operacionais 2**.

---

## Descrição do Projeto

O shell simula um **sistema de arquivos simples**, utilizando o filesystem do SO como base, mas garantindo que todos os dados fiquem contidos dentro do diretório `fs/`.

### Estrutura do filesystem

```
fs/
 ├─ blocks/            # Blocos de dados (arquivos .dat)
 ├─ inodes.dat         # I-nodes sequenciais
 ├─ freespace.dat      # Gerenciamento de blocos livres
 ├─ superblock.dat     # Metadados do sistema de arquivos
 └─ .mickey.txt        # Arquivo de teste com o conteúdo "Disney"
```

**Regras do sistema de arquivos:**

* Cada diretório deve possuir os diretórios `.` (atual) e `..` (pai).
* Todos os i-nodes são criados como livres antes do uso.
* O gerenciamento de blocos livres é armazenado em `freespace.dat`.
* Todos os arquivos e diretórios permanecem entre execuções.
* Limite de nomes de arquivos: 14 bytes.
* Blocos de dados têm tamanho definido no `superblock.dat`.

---

## Comandos Suportados

| Comando           | Descrição                                          | Exemplo                                     |
| ----------------- | -------------------------------------------------- | ------------------------------------------- |
| `mkdir <nome>`    | Cria um diretório no diretório atual               | `$ mkdir usuarios`                          |
| `cd <caminho>`    | Muda o diretório atual                             | `$ cd /usuarios`                            |
| `pwd`             | Mostra o diretório atual                           | `$ pwd` → `/usuarios`                       |
| `touch <arquivo>` | Cria um arquivo com conteúdo digitado pelo usuário | `$ touch teste.txt` + conteúdo + `<CTRL+D>` |
| `cat <arquivo>`   | Exibe o conteúdo de um arquivo                     | `$ cat teste.txt`                           |
| `ls`              | Lista arquivos e diretórios do diretório atual     | `$ ls`                                      |
| `rm <nome>`       | Remove arquivo ou diretório                        | `$ rm arquivo.txt`                          |
| `stat`            | Exibe informações do filesystem                    | `$ stat`                                    |

---

## Features Implementadas ✅

* [x] **Função `command_execute()`**

  * Interpreta comandos digitados pelo usuário.
  * Converte o nome do comando para maiúsculas e identifica o código correspondente.
  * Suporta: `MKDIR`, `CD`, `PWD`, `TOUCH`, `CAT`, `DIR`, `RM`, `STAT`.
  * Valida parâmetros e exibe mensagens de erro quando necessário.
  * Retorna `true` em sucesso e `false` caso contrário.

* [ ] **Comando `MKDIR` (`mkdir_execute()`)**
      
* [ ] **Comando `CD` (`cd_execute()`)**

* [x] **Comando `PWD` (Windows) (`pwd_execute()`)**

  * Exibe diretório atual usando `_getcwd()` da biblioteca `<direct.h>`.
  * Retorna `true` em caso de sucesso, `false` em caso de erro.

* [ ] **Comando `TOUCH` (`touch_execute()`)**

* [x] **Comando `CAT` (`cat_execute()`)**

  * Abre arquivo com `fopen()` e lê caractere por caractere (`fgetc()`).
  * Exibe conteúdo no terminal (`putchar()`).
  * Retorna `true` se leitura bem-sucedida, `false` em caso de erro.
  * Fecha arquivo com `fclose()`.
  * Exibe mensagem de erro caso o arquivo não possa ser aberto.

* [ ] **Comando `LS` (`ls_execute()`)**

* [ ] **Comando `RM` (`rm_execute()`)**

* [ ] **Comando `STAT` (`stat_execute()`)**

> Esta seção será atualizada conforme novos comandos forem implementados.

---

## Estrutura de Dados

* **Blocos de dados:** Arquivos dentro de `fs/blocks` com tamanho definido em `superblock.dat`.
* **I-nodes:** Armazenados em `inodes.dat` sequencialmente, todos livres inicialmente.
* **Gerenciamento de espaço livre:** Arquivo `freespace.dat`.
* **Diretórios:** Devem ter `.` (atual) e `..` (pai).
* **Persistência:** Arquivos e diretórios permanecem entre execuções.

---

## Instalação

1. Clone o repositório:

```bash
git clone https://github.com/seu-usuario/shell-c.git
cd shell-c
```

2. Compile o projeto:

```bash
gcc -o shell main.c filesystem.c commands.c
```

3. Execute o shell:

```bash
./shell
```

---

## Atualizações Futuras

* Implementação dos comandos `MKDIR`, `CD`, `TOUCH`, `LS`, `RM`, `STAT`.
* Melhorias na persistência e performance da busca por arquivos.
* Validação avançada de parâmetros e tratamento de erros.
* Suporte multiplataforma (Linux/Windows).

---

## Estrutura do Repositório

```
shell-c/
 ├─ fs/                 # Diretório do filesystem
 ├─ main.c              # Loop principal do shell
 ├─ filesystem.c        # Funções de manipulação do FS
 ├─ commands.c          # Implementação dos comandos
 ├─ commands.h
 ├─ filesystem.h
 └─ README.md
```
