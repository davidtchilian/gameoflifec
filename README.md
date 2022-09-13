# Jeu de la vie (Implementation en C)

## Description

Le jeu de la vie est un automate cellulaire imaginé par John Horton Conway en 1970. Il est composé d'une grille de cellules carrées, qui peuvent être soit vivantes, soit mortes. À chaque étape, l'état de chaque cellule est déterminé en fonction de l'état de ses huit voisines. Le jeu de la vie est un exemple de système dynamique non linéaire.

Les règles de vie ou de survie de chaque case sont appliqués à chaque étape du jeu :

- Une cellule morte avec exactement trois cellules voisines vivantes devient vivante, comme par reproduction.
- Une cellule vivante avec deux ou trois cellules voisines vivantes reste vivante, sinon elle meurt de solitude ou d'envahissement.

## Installation et utilisation

```bash
git clone https://github.com/fredidas/gameoflifec
cd gameoflifec
make
```

Un template est déjà présent dans le code lorsque vous le lancez. Vous pouvez le modifier à votre guise.

Plusieurs motifs sont données comme par exemple le Glider ou encore le Pulsar.