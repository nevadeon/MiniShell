### Types de commit

- **feat**
  Utilisé pour introduire une nouvelle fonctionnalité dans le code.
  *Exemple :* `feat(auth): ajout de la connexion via OAuth`.

- **fix**
  Sert à corriger un bug ou un comportement inattendu.
  *Exemple :* `fix(form): correction d'une erreur de validation`.

- **docs**
  Changements liés à la documentation. Cela peut inclure la mise à jour ou l’ajout de documents, sans modification du code source.
  *Exemple :* `docs(readme): mise à jour de la procédure d'installation`.

- **style**
  Modifications relatives à la mise en forme du code (indentation, espaces, ponctuation, etc.) qui n'affectent pas la logique ou le comportement du code.
  *Exemple :* `style: reformattage du code selon les normes de linting`.

- **refactor**
  Modifications du code qui n’ajoutent pas de fonctionnalité ni ne corrigent de bug, mais qui améliorent la structure ou la lisibilité du code.
  *Exemple :* `refactor: simplification de la logique d'authentification`.

- **perf**
  Changements destinés à améliorer les performances du logiciel sans modifier son comportement observable.
  *Exemple :* `perf: optimisation de l'algorithme de traitement des données`.

- **test**
  Tout ajout ou modification dans les tests, qu'il s'agisse de tests unitaires, d'intégration ou autres.
  *Exemple :* `test: ajout de tests pour la fonction de calcul`.

- **build**
  Changements qui affectent le système de build ou les dépendances externes (configuration de Maven, Gradle, npm, etc.).
  *Exemple :* `build: mise à jour de la version de Node.js dans le package.json`.

- **ci**
  Modifications portant sur l'intégration continue ou les scripts de déploiement.
  *Exemple :* `ci: correction du script de déploiement sur le serveur de test`.

- **chore**
  Modifications de tâches de maintenance, de configurations diverses ou d'autres changements qui ne touchent pas directement au code source (mise à jour des outils, tâches d'automatisation, etc.).
  *Exemple :* `chore: nettoyage des fichiers temporaires après build`.

- **revert**
  Utilisé pour annuler un commit précédent.
  *Exemple :* `revert: retour sur le commit [hash] à cause de problèmes de performance`.

### Structure d’un message de commit

Un commit suivant cette convention est structuré de la façon suivante :

**En-tête**
   Commence par le type suivi d’un deux-points et éventuellement d’un scope entre parenthèses.
   *Exemple :* `feat(auth): ajout de la fonctionnalité de double authentification`.

### Structure d'un fichier header `.h`

Pour assurer la cohérence et la lisibilité des headers dans le projet, il est conseillé de respecter l’ordre suivant :

- **Inclusions des bibliothèques standard**
  Inclure d'abord les fichiers headers de la bibliothèque standard C.
  *Exemple :* `#include <stdlib.h>`

- **Inclusions des headers du projet**
  Ajouter ensuite les headers internes de votre projet.
  *Exemple :* `#include "mon_module.h"`

- **Définition de constantes (macros)**
  Placer ici les `#define` servant de constantes, tailles de buffers, etc.
  *Exemple :* `#define MA_CONSTANTE 42`

- **Déclarations anticipées (forward declarations)**
  Déclarations minimales de types pour éviter les inclusions circulaires.
  *Exemple :* `typedef enum e_type t_type;`

- **Déclarations de types (structs, enums, typedefs)**
  Définir ici toutes les structures, énumérations et alias de types utilisés.
  *Exemple :* `typedef struct s_node { int value; t_node *next; } t_node;`

- **Pointeurs de fonctions (typedefs spécifiques)**
  Déclarer ici les typedefs de pointeurs vers fonctions, si besoin.
  *Exemple :* `typedef void (*t_delete_function)(void *);`

- **Prototypes des fonctions**
  Lister enfin les fonctions exposées par ce module.
  *Exemple :* `void delete_node(t_node *node, t_delete_function del);`
