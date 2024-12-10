#include<stdio.h>
#include<stdlib.h>

struct proc
{
    int nb, ta, tx, rt, ct, wt, tat, pri;
};

struct proc read(int i)
{
    struct proc p;
    printf("\nNum�ro de processus : %d\n", i);
    p.nb = i;
    printf("Entrer le temps d'arriv�e : ");
    scanf("%d", &p.ta);
    printf("Entrer le temps d'ex�cution : ");
    scanf("%d", &p.tx);
    printf("Entrer la priorit� : ");
    scanf("%d", &p.pri);
    p.rt = p.tx;
    return p;
}

void main()
{
    int i, j, n, c, remaining, min_val, min_index;
    struct proc p[10], temp;
    float avgtat = 0, avgwt = 0;
    printf("<-- Algorithme de planification par Priorit� la plus basse (Pr�emptif) -->\n");
    printf("Entrer le nombre de processus : ");
    scanf("%d", &n);
    for(i = 0; i < n; i++)
        p[i] = read(i + 1);
    remaining = n;
    for(i = 0; i < n - 1; i++)
        for(j = 0; j < n - i - 1; j++)
            if(p[j].ta > p[j + 1].ta)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
    printf("\nNum�ro de processus\tTemps d'arriv�e\tTemps d'ex�cution\tPriorit�\tTemps de fin\tTemps de retour\tTemps d'attente\n");
    c = 0;
    while(remaining > 0)
    {
        min_val = 9999;
        for(i = 0; i < n; i++)
        {
            if(p[i].rt > 0 && p[i].ta <= c && p[i].pri < min_val)
            {
                min_val = p[i].pri;
                min_index = i;
            }
        }
        i = min_index;
        c++;
        p[i].rt--;
        if(p[i].rt == 0)
        {
            p[i].ct = c;
            remaining--;
        }
    }
    for(i = 0; i < n; i++)
    {
        p[i].tat = p[i].ct - p[i].ta;
        avgtat += p[i].tat;
        p[i].wt = p[i].tat - p[i].tx;
        avgwt += p[i].wt;
        printf("P%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\n", p[i].nb, p[i].ta, p[i].tx, p[i].pri, p[i].ct, p[i].tat, p[i].wt);
    }
    avgtat /= n, avgwt /= n;
    printf("\nTemps moyen de retour = %f\nTemps moyen d'attente = %f", avgtat, avgwt);
}
