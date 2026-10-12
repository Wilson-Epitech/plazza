<div align="center">

# The Plazza

**Une pizzeria simulée avec des processus, des threads et des files de messages.**

<img alt="C++" src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=cplusplus&logoColor=white"/> <img alt="Make" src="https://img.shields.io/badge/Make-427819?style=for-the-badge&logo=gnu&logoColor=white"/> <img alt="Unix" src="https://img.shields.io/badge/Unix-333333?style=for-the-badge&logo=linux&logoColor=white"/> <img alt="GitHub Actions" src="https://img.shields.io/badge/GitHub%20Actions-2088FF?style=for-the-badge&logo=githubactions&logoColor=white"/>

<sub>Projet à 3 · 2024</sub>

</div>

<br/>

<p align="center"><img src=".github/assets/term-plazza.png" alt="The Plazza" width="820"/></p>

## En deux mots

Une réception prend les commandes en ligne de commande et les envoie à des cuisines. Chaque cuisine est un **processus**, chaque cuisinier un **thread**. Quand toutes les cuisines sont pleines, on en ouvre une nouvelle, et quand une cuisine ne fait plus rien pendant 5 secondes, elle ferme.

## Ce que ça fait

- Prise de commandes interactive : `regina XXL x2; margarita S x1`
- **Une cuisine = un processus** (`fork`), créé à la demande selon la charge
- **Un cuisinier = un thread**, avec un stock d'ingrédients qui se régénère
- Communication réception ↔ cuisines par **files de messages** System V (`msgsnd` / `msgrcv`)
- Fermeture automatique des cuisines inactives
- Temps de cuisson et nombre de cuisiniers configurables

## Sous le capot

La réception parse les commandes, cherche une cuisine qui a de la place et lui envoie les pizzas par file de messages. S'il n'y en a pas, elle fork une nouvelle cuisine. Dans chaque cuisine, un pool de threads se partage les commandes, et chaque cuisson dure un temps multiplié par le facteur passé en argument.

```mermaid
flowchart LR
    U[Utilisateur] --> R[Réception]
    R -- msgsnd --> K1[Cuisine 1<br/>processus]
    R -- msgsnd --> K2[Cuisine 2<br/>processus]
    K1 --> T1[cuisinier] & T2[cuisinier]
    K2 --> T3[cuisinier] & T4[cuisinier]
```

## Lancer le projet

```bash
make
./plazza <multiplicateur_cuisson> <cuisiniers_par_cuisine> <régénération_ms>
./plazza 1 2 1000
```

## L'équipe

<a href="https://github.com/Wilson-Epitech/plazza/graphs/contributors"><img src="https://contrib.rocks/image?repo=Wilson-Epitech/plazza" alt="Contributeurs"/></a>

Yassine Majdoul, Wilson Bordichon, Josué Ménager

**Ma part :** J'ai mis en place la **communication entre processus** (files de messages entre la réception et les cuisines), la **création des cuisines** dans des processus fils, le parsing des commandes de la réception et la CI GitHub Actions.
