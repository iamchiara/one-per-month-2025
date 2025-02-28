#include <stdio.h>
#include <stdlib.h>

typedef enum {umano, computer} tipoGiocatore;
typedef struct {
    tipoGiocatore giocatore;
    char nome[20];
    int nscelto;
    int ppartita;
    int ptotale;
} giocatore;
void nuovaPartita();
void impostazioni(int *p, int *d, int *i, int *a);
void giocatori(int p, giocatore *giocatori);
int dadorand(int i);
void assegnaDadi(int dadi, int *d, int in);
void assegnaDadiWait(int dadi, int *d, int in);
void regole();
void confronta(int dadi, int *d, int players, giocatore *g);
void risultati(int players, giocatore *g, int *f);
void spostaSette(int d[], int dadi);
void pulisciBuffer();
int main(void) {
    int s = 0;
    printf(" VINCI SE NON C'%c\n------------------\n\n", 212);
    do {
        printf("Menu\n1. Nuova partita\n2. Regole\n3. Esci\n");
        scanf("%d", &s);
        if (s==1)
            nuovaPartita();
        if (s==2) {
            regole();
            continue;
        }
        if (s>2)
            while (getchar() != '\n');
        printf("Alla prossima :D");
        printf("\n\nClicca invio per uscire");
        getchar();
        return 0;

    } while (s==2);
}
void nuovaPartita() {
    int players, dadi;
    int ind, a;
    impostazioni(&players, &dadi, &ind, &a);
    giocatore g[players];
    giocatori(players, g);
    /*printf("A\n\n%d\n%d\n%c", players, dadi, ind);
    for (int i = 0; i < players; i++) {
        printf("Giocatore %d:\nTipo:%d\nNome:%s\n", i+1, g[i].giocatore, g[i].nome);
    }*/
    int f = 0;
    while (f ==0) {
        for (int i = 0; i < players; i++) {
            if (g[i].giocatore == 0) {
                do {
                    printf("Turno di %s!\nScegli un numero tra 1 e 6\n", g[i].nome);
                    scanf("%d", &g[i].nscelto);
                    pulisciBuffer();
                } while (g[i].nscelto<1 || g[i].nscelto>6);
            }
            else {
                g[i].nscelto = dadorand(0);
                printf("Turno di %s!\n%s ha scelto %d\n", g[i].nome, g[i].nome, g[i].nscelto);
            }
        }
        int d[dadi];
        if (a == 1) {
            printf("In attesa di autorizzazione per il lancio dei dadi...");
            getchar();
            assegnaDadiWait(dadi, d, ind);
        }
        else {
            assegnaDadi(dadi, d, ind);
        }
        confronta(dadi, d, players, g);
        risultati(players, g, &f);
    }
}
void regole() {
    printf("Regole tradizionali\nMentre si mischiano i dadi ogni giocatore sceglie un numero da 1 a 6.\n"
            "Si lanciano i dadi. Se il numero scelto non c'%c si vince un punto.\n"
            "Se %c presente in numero maggiore o uguale alla met%c dei dadi si perde un punto. Altrimenti si procede a giocare.\n"
            "Se il dado %c indeciso si tira di nuovo.\n"
            "Chi arriva prima a 5 punti vince la partita\n\n"
            "Regole digitali\nDopo aver impostato i parametri di gioco, la partita si svolge esattamente come si svolgerebbe nella realt%c.\n"
            "Se nelle impostazioni iniziali %c stato deciso che il dado pu%c essere indeciso, sar%c tirato di nuovo anche digitalmente.\n\n", 138, 138, 133, 138, 133, 138, 149, 133);
}
void impostazioni(int *p, int *d, int *i, int *a) {
    printf("Nuova partita!\nIniziamo impostando i parametri di gioco\n");
    do {
        printf("Numero giocatori:\n");
        scanf("%d", p);
    } while (*p<1);
    do {
        printf("Numero dadi (almeno 3):\n");
        scanf("%d", d);
    } while (*d<3);
    printf("Dadi indecisi (1 per s%c, 0 per no):\n", 141);
    scanf(" %d", i);
    if (*i!=0)
        *i = 1;
    printf("Attendere autorizzazione per il lancio dei dadi? (1 per s%c, 0 per no)\n", 141);
    scanf(" %d", a);
    if (*a!=0)
        *a = 1;
}
void giocatori(int p, giocatore *giocatori) {
    for (int i = 0; i<p; i++) {
        char t;
        printf("Inserire tipo %d%c giocatore (u per umano, c per computer):\n", i+1, 248);
        scanf(" %c", &t);
        if (t != 'u')
            giocatori[i].giocatore = computer;
        else
            giocatori[i].giocatore = umano;
        printf("Inserire nome %d%c giocatore:\n", i+1, 248);
        scanf("%s", giocatori[i].nome);
        pulisciBuffer();
        giocatori[i].nscelto = 0;
        giocatori[i].ppartita = 0;
        giocatori[i].ptotale = 0;
    }
}
int dadorand(int i) {
    if (i==0)
        return rand()%6+1;
    return rand()%7+1;
}
void assegnaDadi(int dadi, int *d, int in) {
    for (int i = 0; i < dadi; i++) {
        d[i]=dadorand(in);
    }
    int ind = 0;
    printf("I dadi sono stati lanciati. Ecco i risultati:\t");
    for (int i = 0; i<dadi; i++) {
        if (d[i]==7) {
            ind++;
            printf("indeciso ");
            continue;
        }
        printf("%d ", d[i]);
    }
    while (ind>0) {
        spostaSette(d, dadi);
        printf("\nSi tirano nuovamente i dadi indecisi\n");
        for (int i = dadi - ind; i<dadi; i++) {
            d[i]=dadorand(1);
        }
        ind = 0;
        printf("Nuovi risultati dei dadi\n");
        for (int i = 0; i<dadi; i++) {
            if (d[i]==7) {
                ind++;
                printf("indeciso ");
                continue;
            }
            printf("%d ", d[i]);
        }
    }
    printf("\n\n");
}
void assegnaDadiWait(int dadi, int *d, int in) {
    for (int i = 0; i < dadi; i++) {
        d[i]=dadorand(in);
    }
    int ind = 0;
    printf("\nI dadi sono stati lanciati. Ecco i risultati:\t");
    for (int i = 0; i<dadi; i++) {
        if (d[i]==7) {
            ind++;
            printf("indeciso ");
            continue;
        }
        printf("%d ", d[i]);
    }
    while (ind>0) {
        spostaSette(d, dadi);
        printf("\nSi tirano nuovamente i dadi indecisi\nIn attesa di autorizzazione per il lancio dei dadi...");
        getchar();
        for (int i = dadi - ind; i<dadi; i++) {
            d[i]=dadorand(1);
        }
        ind = 0;
        printf("\nNuovi risultati dei dadi\n");
        for (int i = 0; i<dadi; i++) {
            if (d[i]==7) {
                ind++;
                printf("indeciso ");
                continue;
            }
            printf("%d ", d[i]);
        }
    }
    printf("\n\n");
}
void confronta(int dadi, int *d, int players, giocatore *g) {
    for (int i = 0; i < players; i++) {
        int c = 0;
        for (int j = 0; j < dadi; j++) {
            if (d[j]==g[i].nscelto)
                c++;
        }
        if (c==0) {
            g[i].ppartita=1;
            g[i].ptotale+=1;
            continue;
        }
        if (c>=dadi/2){
            g[i].ppartita=-1;
            g[i].ptotale-=1;
        }
    }
}
void risultati(int players, giocatore *g, int *f) {
    for (int i = 0; i < players; i ++) {
        printf("%s ha ottenuto %d punti! Al momento ha %d punti.\n", g[i].nome, g[i].ppartita, g[i].ptotale);
        g[i].ppartita=0;
    }
    giocatore classifica[players], buffer;
    for (int i = 0; i < players; i++) {
        classifica[i] = g[i];
    }

    for (int i = 1; i < players; i++) {
        buffer = classifica[i];
        int j = i - 1;

        while (j >= 0 && classifica[j].ptotale < buffer.ptotale) {
            classifica[j + 1] = classifica[j];
            j--;
        }
        classifica[j + 1] = buffer;
    }

    printf("\nClassifica aggiornata:\n");
    for (int i = 0; i < players; i++) {
        printf("%d%c %s --- %d punti\n", i + 1, 248, classifica[i].nome, classifica[i].ptotale);
    }
    if (classifica[0].ptotale >= 5) {
        *f = 1;
        printf("Il vincitore %c %s con %d punti!\n", 138, classifica[0].nome, classifica[0].ptotale);
    }
}
void spostaSette(int d[], int dadi) {
    int k = 0;
    for (int i = 0; i < dadi; i++) {
        if (d[i] != 7) {
            d[k] = d[i];
            k++;
        }
    }
    while (k < dadi) {
        d[k] = 7;
        k++;
    }
}
void pulisciBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}