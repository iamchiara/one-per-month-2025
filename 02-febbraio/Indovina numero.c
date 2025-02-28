#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <bcrypt.h>
#include <setjmp.h>

struct pair{
    char g;
    char p;
    char c;
};
const unsigned long long ran[] = {100, 1000, 1000000, 1000000000, ULLONG_MAX};
const int ten[] = {-1, 100, 50, 20, 5};
const struct pair ind[] = {{'g', 'p', 'c'}, {'>', '<', '='}, {'M', 'm', 'u'}};
void new();
void parametri(int *r, int *t);
unsigned long long random(int diff);
int tentativo(unsigned long long n, int i, int r, int ra);
void inverted();
void parametriInv(int *r, int *i);
int tentativoInv(int i, unsigned long long *min, unsigned long long *max, int in, int r);
int check(char a, int i);
void rules();
int menu();
jmp_buf err;
int main(void) {
    if (setjmp(err) == 0) {
        printf("----------Indovina numero----------\n\n");
        while (menu()==1);
    }
    else{
        printf("\n\nClicca invio per uscire");
        while (getchar() != '\n');
        getchar();
        return 0;
    }
    printf("\n\nClicca invio per uscire");
    getchar();
    return 0;
}
int menu() {
    int s;
    printf("Men%c\n"
       "1. Nuova partita (indovina)\n"
       "2. Nuova partita (scegli)\n"
       "3. Regole\n"
       "4. Esci\n", 151);
    scanf("%d", &s);
    switch (s) {
        case 1:
            new();
            return 0;
        case 2:
            inverted();
            return 0;
        case 3:
            rules();
            return 1;
        default:
            printf("Alla prossima!");
            return 0;
    }
}

void new(){
    int range, tent;
    parametri(&range, &tent);
    //printf("Range : %d\nTentativi : %d", range, tent);
    const unsigned long long n = random(range);
    int r = -1; //risultato
    if (ten[tent]>0) {
        for (int i = 0; i < ten[tent]; i++) {
            r = tentativo(n, i+1, tent, range);
            //printf("\n\n%d\n\n", r);
            if (r == 0)
                continue;
            if (r== 1) {
                printf("Errore!");
                break;
            }
            if (r==2){
                printf("Corretto!");
                break;
            }
            else{
                printf("Errore non identificato");
                break;
            }
        }
        //printf("\n\nSei uscito dal ciclo\n\n");
    }
    else {
        int i = 1;
        r = tentativo(n, i, tent, range);
        while (r==0) {
            i++;
            r = tentativo(n, i, 0, range);
            if (r == 0)
                continue;
            if (r == 1) {
                printf("Errore!");
                break;
            }
            if (r==2){
                printf("Corretto!");
                break;
            }
            else{
                printf("Errore non identificato");
                break;
            }
        }
    }
    //printf("%llu", n);
}
void parametri(int *r, int *t) {
    printf("Imposta i parametri di gioco\n"
           "Range:\n"
           "1. 0-%llu (semplice)\n"
           "2. 0-%llu (medio)\n"
           "3. 0-%llu (difficile)\n"
           "4. 0-%llu (difficilissimo)\n"
           "5. 0-%llu (extra)\n", ran[0], ran[1], ran[2], ran[3], ran[4]);
    scanf("%d", r);
    if (*r>5)
        *r = 5;
    if (*r<1)
        *r=1;
    *r = *r-1;
    printf("Tentativi a disposizione\n"
           "1. Illimitati (semplice)\n"
           "2. %d (medio)\n"
           "3. %d (difficile)\n"
           "4. %d (difficilissimo)\n"
           "5. %d (extra)\n", ten[1], ten[2], ten[3], ten[4]);
    scanf("%d", t);
    if (*t>5)
        *t = 5;
    if (*t<1)
        *t=1;
    *t = *t-1;
}
void rules() {
    printf("Regole versione 1 (utente indovina)\n"
           " 1. Impostare i parametri di gioco con range e numero di tentativi disponibili\n"
           " 2. Cercare di indovinare il numero random che il programma ha scelto facendosi guidare dalle istruzioni del programma (troppo grande/piccolo)\n"
           " 3. Si consiglia di procedere seguendo una strategia, specialmente se i tentativi a disposizione sono pochi e il range %c ampio\n\n"
           "Regole versione 2 (computer indovina)\n"
           " 1. Impostare i parametri di gioco con range e indicatori\n"
           " 2. Scegliere un numero (e non cambiarlo!)\n"
           " 3. Rispondere al programma in base alla proposta che fa indicando la relazione di grandezza tra il numero proposto e quello scelto\n\n"
           "Buon divertimento\n", 138);
}

void inverted() {
    int range, indic;
    parametriInv(&range, &indic);
    int a;
    //definisco range
    unsigned long long min = 0, max = ran[range]+1;
    int i = 1;
    while (tentativoInv(i, &min, &max, indic, range) == 1)
        i++;
    longjmp(err, 1);
}
void parametriInv(int *r, int *i) {
    printf("Imposta i parametri di gioco\n"
           "Range:\n"
           "1. 0-%llu (semplice)\n"
           "2. 0-%llu (medio)\n"
           "3. 0-%llu (difficile)\n"
           "4. 0-%llu (difficilissimo)\n"
           "5. 0-%llu (extra)\n", ran[0], ran[1], ran[2], ran[3], ran[4]);
    scanf("%d", r);
    if (*r>5)
        *r = 5;
    if (*r<1)
        *r=1;
    *r = *r-1;
    printf("Indicatori (ATTENZIONE! Il primo si utilizza quando il numero proposto dal programma %c MAGGIORE del numero scelto, il secondo quando %c minore, mentre il terzo quando la risposta %c corretta):\n"
           " 1. %c - %c - %c\n"
           " 2. %c - %c - %c\n"
           " 3. %c - %c - %c\n", 138, 138, 138, ind[0].g, ind[0].p, ind[0].c, ind[1].g, ind[1].p, ind[1].c, ind[2].g, ind[2].p, ind[2].c);
    scanf("%d", i);
    if (*i>3)
        *i = 3;
    if (*i<1)
        *i=1;
    *i = *i-1;
}

unsigned long long random(int diff) {
    unsigned long long randomNumber = 0;
    if (!BCRYPT_SUCCESS(BCryptGenRandom(NULL, (PUCHAR)&randomNumber, sizeof(randomNumber), BCRYPT_USE_SYSTEM_PREFERRED_RNG))) {
        printf("Errore: impossibile generare un numero casuale.\n");
        longjmp(err, 1);
    }
    if (ran[diff]<ULLONG_MAX)
        randomNumber = randomNumber % (ran[diff] + 1);
    return randomNumber;
}

int tentativo(unsigned long long n, int i, int r, int ra) {
    unsigned long long g=0;//guess
    char buf[22];
    printf("%d%c tentativo", i, 248);
    if (r==0)
        printf(":\n");
    else
        printf(" (%d rimanenti):\n", ten[r]-i);
    if (i==1)
        while (getchar() != '\n');
    if (fgets(buf, sizeof(buf), stdin) != NULL) {
        char *endptr;

        buf[strcspn(buf, "\n")] = '\0';

        g = strtoull(buf, &endptr, 10);

        if (*endptr != '\0') {
            printf("Input non valido!\n");
            return 1;
        }

        //printf("Hai inserito: %llu\n", g);
    }
    else {
        printf("Errore nella lettura dell'input!\n");
        return 1;
    }
    if (g == n) {
        return 2;
    }
    if (g<n)
        printf("%llu %c troppo piccolo\n", g, 138);
    else if(g>ran[ra])
        printf("%llu %c fuori dal range scelto, per cui %c troppo grande\n", g, 138, 138);
    else
        printf("%llu %c troppo grande\n", g, 138);
    return 0;
}

int tentativoInv(int i, unsigned long long *min, unsigned long long *max, int in, int r) {
    if (*max-*min==1 && *min!=0) {
        if(*min == ran[r])
            printf("Errore! %llu %c il massimo del range che hai scelto, non pu%c essere minore del numero da indovinare.\nPurtroppo %c necessario ricominciare la partita :(", *min, 138, 149, 138);
        else
            printf("Errore! Non ci sono numeri interi tra %llu e %llu", *min, *max);
        return 2;
    }
    unsigned long long t = (*max+*min)/2;
    printf("%d%c tentativo:\t%llu\n", i, 248, t);
    while (getchar() != '\n');
    int a = check(getchar(), in);
    if (a==0) {
        printf("Ho indovinato!");
        return 0;
    }
    if (a==1) {
        *max = t;
        return 1;
    }
    *min = t;
    return 1;
}

int check(char a, int i) {
    if (a == ind[i].g)
        return 1;
    if (a == ind[i].p)
        return 2;
    return 0;
}