# Workflow de Création et de Test

Ce workflow guide de manière concise et détaillée les étapes nécessaires pour créer, renommer, déplacer, générer des fichiers `.bin`, exécuter des tests et committer les résultats vers un dépôt Git. En suivant ces étapes, vous assurez une gestion cohérente et efficace des fichiers de test et de leurs résultats.

## Étape 1 : Générer des fichiers `.rt` à la racine du dépôt
- **Action** : Exécutez le programme `miniRT` pour générer les fichiers `.rt`.
- **Instructions** :
1. Lancez l'application `miniRT`.
2. Déplacez la caméra dans l'application pour obtenir les vues que vous souhaitez tester.
3. Appuyez sur la touche `m` pour générer un fichier `.rt` à la racine du dépôt.

- **Exemple** :
```plaintext
$ ./miniRT
(Déplacer la caméra dans l'application)
(Appuyer sur la touche 'm')
(Répéter pour chaque vue souhaitée)
```
Les fichiers générés seront nommés file_1.rt, file_2.rt, etc.

## Étape 2 : Renommer et déplacer les fichiers .rt
Utilisez le script `rename_files_and_move_them.sh` pour renommer et déplacer les fichiers `.rt` générés vers le répertoire `tests/rt_files`.

```bash
./rename_files_and_move_them.sh
```
1.	**Action** : Le script demande une valeur de départ pour la numérotation des fichiers `.rt`.
2.	**Entrée utilisateur** : Saisissez la valeur de départ pour la numérotation, par exemple 13.
3.	**Exemple** :
```
À partir de quelle valeur voulez-vous commencer la numérotation des fichiers `.rt` ? 13
file_1.rt a été renommé et déplacé vers tests/rt_files/file_13.rt
file_2.rt a été renommé et déplacé vers tests/rt_files/file_14.rt
```
## Étape 3 : Générer des fichiers .bin à partir des fichiers .rt
Utilisez le script `generate_bin_files.sh` pour générer les fichiers `.bin` en utilisant l'application `miniRT`.
```bash
./generate_bin_files.sh
```
1.	**Action** : Le script demande une valeur de départ pour la numérotation des fichiers `.bin`.
2.	**Entrée utilisateur** : Saisissez la valeur de départ pour la numérotation, par exemple 13.
3.	**Exemple** :
```
À partir de quelle valeur voulez-vous commencer la numérotation des fichiers .bin ? 13
file_13.bin ✅ : bin file created and moved
file_14.bin ✅ : bin file created and moved
```
## Étape 4 : Exécuter les tests
Utilisez le script `test_script.sh` pour exécuter les tests sur les fichiers `.rt` et comparer les fichiers `.bin` générés avec les fichiers de référence.
```bash
./test_script.sh
```
1.	**Action** : Le script exécute `miniRT` sur chaque fichier `.rt`, compare le fichier `.bin` généré avec le fichier de référence, et affiche les résultats.
2.	**Exemple** :
```
file_13 ✅ : no difference found
file_14 ❌ : files are different
```
## Étape 5 : Committer et pousser les changements
Utilisez le script `mygit.sh` pour committer et pousser les changements vers le dépôt Git, à condition que les tests réussissent.
```bash
./mygit.sh
```
1.	**Action** : Le script exécute `test_script.sh`, puis demande un message de commit et confirme l'exécution de la commande Git.
2.	**Entrée utilisateur** : Saisissez un message de commit et confirmez l'exécution de la commande Git.
3.	**Exemple** :
```
Enter commit message: Fixed bugs in RT files
Command to execute: git add . && git commit -m "Fixed bugs in RT files" && git push && git status
Execute this command? (y/n): y
```
