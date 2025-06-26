# Minishell

## 🚀 Installation & Lancement

### Prérequis

Assure-toi d’avoir les éléments suivants installés sur ton système :

* **Unix/Linux ou macOS**
* **Make**
* **GCC (ou Clang)**
* **`readline`** (librairie nécessaire à la compilation)

  ```bash
  # Sur Debian/Ubuntu
  sudo apt-get install libreadline-dev

  # Sur macOS (avec Homebrew)
  brew install readline
  ```

### Compilation du projet

Clone le dépôt et compile avec `make` :

```bash
git clone https://github.com/nevadeon/minishell.git
cd minishell
make
```

Cela génère un exécutable appelé `minishell`.

### Lancer Minishell

Pour exécuter le shell :

```bash
./minishell
```

Tu peux maintenant taper des commandes comme dans un shell classique. Le shell gère les commandes internes (`cd`, `export`, etc.), les redirections, les pipes, les variables d’environnement, etc.

### Nettoyage

* Supprimer les fichiers objets :

  ```bash
  make clean
  ```

* Supprimer les fichiers objets **et** l’exécutable :

  ```bash
  make fclean
  ```

* Recompiler depuis zéro :

  ```bash
  make re
  ```

### Tests

Le projet inclut également un binaire de tests (si fourni) :

```bash
make test
./tests
```

### Debug & Analyse mémoire

* **Mode debug** avec symboles :

  ```bash
  make g
  ```

* **Valgrind** (analyse mémoire) :

  ```bash
  make valgrind
  ```

* **GDB** (debug interactif) :

  ```bash
  make gdb
  ```

## 📌 Project Overview

**Minishell** is a group project developed as part of the curriculum at **42 Le Havre**, by two students: [nevadeon](https://github.com/nevadeon) and [Weldd2](https://github.com/Weldd2). This project aims to recreate a simplified version of a Unix shell, providing us with an opportunity to delve deep into the fundamentals of process handling, input parsing, and command execution at the core of operating systems.

Inspired by the early days of computing, this shell replicates a time when user interfaces were minimal, and interaction with machines was entirely command-line based. By building Minishell, we revisit these foundational challenges and recreate a crucial layer of abstraction between the user and the kernel.

## 🧠 Context and Objectives

The objective is to write a robust shell in **C**, adhering strictly to the rules of memory management, process control, and command parsing. The program must:

* Display a dynamic prompt and read user commands interactively.
* Parse and execute both built-in commands and external binaries.
* Support redirections (`<`, `>`, `<<`, `>>`), pipes, and environment variable expansions.
* Handle Unix signals correctly (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`) in interactive mode.
* Implement shell-specific behaviors for quotes, history, and error management.

The shell must closely mimic **bash** behavior for all the required features, without adding unnecessary or unsupported functionality.

## 🧾 Constraints and Technical Requirements

* Language: **C**
* Coding style: **42 Norm** (zero tolerance for norm errors, including in bonus files).
* Error handling: No crashes, segmentation faults, or undefined behavior.
* Memory: All dynamically allocated memory must be properly freed — **no leaks allowed**.
* Compilation: A Makefile must be provided, supporting standard rules (`all`, `clean`, `fclean`, `re`, and `bonus` if applicable), with flags `-Wall -Wextra -Werror`.
* Libraries allowed: Only standard system calls and `readline`, along with the custom `libft`.

## 📂 Project Structure

The mandatory part includes:

* Custom prompt
* Built-in command support
* Execution of external programs with `PATH` resolution
* Redirection and piping
* Environment variable expansion
* Signal handling
* History management

Any bonus features (such as wildcard expansion or advanced parsing) must be explicitly separated and included only via the `bonus` rule in the Makefile.

## 🫀 Commit Types

* **feat**
  Used to introduce a brand‑new feature.
  *Example:* `feat(auth): add OAuth login support`

* **fix**
  For correcting a bug or unexpected behaviour.
  *Example:* `fix(form): fix validation error`

* **docs**
  Documentation‑only changes—updating or adding docs without touching source code.
  *Example:* `docs(readme): update installation steps`

* **style**
  Code‑style changes (indentation, spacing, punctuation, etc.) that do **not** affect logic or behaviour.
  *Example:* `style: reformat code to satisfy linter`

* **refactor**
  Code changes that neither add features nor fix bugs but improve structure or readability.
  *Example:* `refactor: simplify authentication flow`

* **perf**
  Changes aimed at improving performance without altering observable behaviour.
  *Example:* `perf: optimise data‑processing algorithm`

* **test**
  Adding or modifying tests—unit, integration, or other.
  *Example:* `test: add tests for calculation function`

* **build**
  Changes that affect the build system or external dependencies (Maven, Gradle, npm, etc.).
  *Example:* `build: update Node.js version in package.json`

* **ci**
  Changes to continuous‑integration configuration or deployment scripts.
  *Example:* `ci: fix deployment script for staging server`

* **chore**
  Routine tasks, configuration tweaks, or other maintenance work that doesn’t directly change source code (tool upgrades, automation tasks, etc.).
  *Example:* `chore: clean up temporary files after build`

* **revert**
  Reverts a previous commit.
  *Example:* `revert: roll back commit [hash] due to performance issues`

### Commit‑message format

A commit following this convention is structured as:

**Header**
Starts with the *type*, optionally followed by a *scope* in parentheses, then a colon.
*Example:* `feat(auth): add two‑factor authentication`

## 🧠 Header File (`.h`) Structure

To keep project headers consistent and readable, follow this order:

1. **Standard‑library includes**
   Include C standard headers first.
   *Example:* `#include <stdlib.h>`

2. **Project header includes**
   Then include your project’s internal headers.
   *Example:* `#include "my_module.h"`

3. **Constant (macro) definitions**
   Place `#define` constants, buffer sizes, etc. here.
   *Example:* `#define MY_CONSTANT 42`

4. **Forward declarations**
   Minimal type declarations to avoid circular includes.
   *Example:* `typedef enum e_type t_type;`

5. **Type declarations (structs, enums, typedefs)**
   Define all structs, enums, and type aliases used by the module.
   *Example:*

   ```c
   typedef struct s_node {
       int value;
       struct s_node *next;
   } t_node;
   ```

6. **Function‑pointer typedefs**
   Declare function‑pointer typedefs, if any.
   *Example:* `typedef void (*t_delete_function)(void *);`

7. **Function prototypes**
   Finally, list the module’s public function prototypes.
   *Example:* `void delete_node(t_node *node, t_delete_function del);`
