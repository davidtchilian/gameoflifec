#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#define N 60

enum Case
{
    MORT,
    VIVANT
};
typedef enum Case Case;
typedef Case Grille[N][N];

/**
 * @brief Permet de verifier si une case est dans les limites de la grille (Pour eviter les erreurs de segmentations)
 * 
 * @param i 
 * @param j 
 * @return int 
 */
int inBounds(int i, int j)
{
    return i >= 0 && i < N && j >= 0 && j < N;
}

/**
 * @brief Modifie une case et lui donne la valeur MORT ou VIVANT
 * 
 * @param x 
 * @param y 
 * @param tab 
 * @param state 
 */
void set_case(int x, int y, Grille tab, Case state)
{
    if (inBounds(y, x))
    {
        tab[y][x] = state;
    }
}

/**
 * @brief Renvoie l'etat de la case donnee dans la grille
 * 
 * @param x 
 * @param y 
 * @param tab 
 * @return Case 
 */
Case get_case(int x, int y, Grille tab)
{
    if (inBounds(y, x))
    {
        return tab[y][x];
    }
    else
    {
        return MORT;
    }
}

/**
 * @brief Renvoie le nombre de voisins d'une case donnee
 * 
 * @param x 
 * @param y 
 * @param tab 
 * @return int 
 */
int compter_voisins(int x, int y, Grille tab)
{
    int count = 0;
    count += get_case(x, y - 1, tab);
    count += get_case(x - 1, y, tab);
    count += get_case(x + 1, y, tab);
    count += get_case(x, y + 1, tab);
    count += get_case(x - 1, y - 1, tab);
    count += get_case(x + 1, y + 1, tab);
    count += get_case(x + 1, y - 1, tab);
    count += get_case(x - 1, y + 1, tab);
    return count;
}

/**
 * @brief Initialise la grille avec des cellules mortes, puis insere le U inverse au centre de la grille
 * 
 * @param tab 
 */
void init_jeu_u(Grille tab)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            set_case(i, j, tab, MORT);
        }
    }
    // tab[y][x] = 1;
    // initialisation du U inverse au centre
    int posCenterX = N / 2;
    int posCenterY = N / 2;
    set_case(posCenterX + 1, posCenterY, tab, VIVANT);
    set_case(posCenterX - 1, posCenterY, tab, VIVANT);
    set_case(posCenterX, posCenterY - 1, tab, VIVANT);
    set_case(posCenterX + 1, posCenterY + 1, tab, VIVANT);
    set_case(posCenterX - 1, posCenterY - 1, tab, VIVANT);
    set_case(posCenterX - 1, posCenterY + 1, tab, VIVANT);
    set_case(posCenterX + 1, posCenterY - 1, tab, VIVANT);
}

/**
 * @brief Affiche la grille de jeu
 * 
 * @param tab Grille de jeu a afficher
 */
void afficher_jeu(Grille tab)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (get_case(j, i, tab) == VIVANT)
            {
                printf("O ");
            }
            else
            {
                printf(". ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * @brief Initialise la grille avec des cellules mortes dans toutes les cases
 * 
 * @param tab grille de jeu
 */
void init_jeu(Grille tab)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            set_case(i, j, tab, MORT);
        }
    }
}

/**
 * @brief Permet d'appliquer les regles du jeu de la vie à une grille un nombre de fois donnee
 * 
 * @param tab grille de jeu
 * @param nb_iterations nombre d'iterations pour l'application des regles
 * @param afficher afficher ou non la grille a chaque iteration
 */
void iterer_jeu(Grille tab, int nb_iterations, int afficher)
{
    for (unsigned int k = 0; k < nb_iterations; k++)
    {
        Grille tab2;
        init_jeu(tab2);
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                int count = compter_voisins(i, j, tab);
                if (get_case(i, j, tab) == VIVANT)
                {
                    if (count == 2 || count == 3)
                    {
                        set_case(i, j, tab2, VIVANT);
                    }
                    else
                    {
                        set_case(i, j, tab2, MORT);
                    }
                }
                else
                {
                    if (count == 3)
                    {
                        set_case(i, j, tab2, VIVANT);
                    }
                }
            }
        }
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                tab[i][j] = tab2[i][j];
            }
        }
        if (afficher)
        {
            afficher_jeu(tab);
            usleep(100000);
        }
    }
}

/**
 * @brief Prend en argument un motif et le place au centre de la Grille de Jeu
 * 
 * @param size taille du motif
 * @param motif tableau a deux dimensions contenant le motif
 * @param tab grille de jeu
 */
void init_jeu_motif(int size, int motif[size][size], Grille tab)
{
    init_jeu(tab);
    int posCenterX = (N / 2) - (size / 2);
    int posCenterY = (N / 2) - (size / 2);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (motif[i][j] == VIVANT)
            {
                set_case(posCenterX + j, posCenterY + i, tab, VIVANT);
            }
        }
    }
}

int main()
{
    Grille tab;
    init_jeu_u(tab);
    // afficher_jeu(tab);

    // Glider
    int glider[3][3] = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 1, 1}
    };

    // Spaceship
    int spaceship[5][5] = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {0, 0, 0, 0, 1},
        {1, 0, 0, 1, 0}
    };

    // Callahan
    int callahan[5][5] = {
        {1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1},
        {0, 1, 1, 0, 1},
        {1, 0, 1, 0, 1}
    };

    // Pentadecathlon
    int pentadecathlon[8][8] = {
        {0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 0}
    };

    // Pulsar
    int pulsar[14][14] = {
        {0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0},
        {1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0},
        {1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0},
        {1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0},
        {1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    // init_jeu_motif(14, pulsar, tab);
    iterer_jeu(tab, 110, 1);
    afficher_jeu(tab);
    return 0;
}
