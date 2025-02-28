# One per month 2025 - "Indovina numero"
>Progetto di febbraio


*Read this in other languages: [English](README.EN.md)*

---

## Il progetto
L'idea creativa di febbraio è un gioco di numeri, in versione classica (l'utente indovina quello scelto dal programma) e inversa (l'utente sceglie il numero che il programma indovina).

---

## Regole del gioco
### Regole versione 1 (utente indovina)
- ⚙ Impostare i parametri di gioco con range e numero di tentativi disponibili
- 🔢 Cercare di indovinare il numero random che il programma ha scelto facendosi guidare dalle istruzioni del programma (troppo grande/piccolo)
- 🧠 Si consiglia di procedere seguendo una strategia, specialmente se i tentativi a disposizione sono pochi e il range è ampio

### Regole versione 2 (programma indovina)
- ⚙ Impostare i parametri di gioco con range e indicatori
- 🔢 Scegliere un numero (e non cambiarlo!)
- ✍ Rispondere al programma in base alla proposta che fa indicando la relazione di grandezza tra il numero proposto e quello scelto

---

## Parametri di gioco
### Versione 1 (utente indovina)
I parametri di gioco da impostare sono:

- Range:
    1. 0-100 (semplice)
    2. 0-1000 (medio)
    3. 0-1000000 (difficile)
    4. 0-1000000000 (difficilissimo)
    5. 0-18446744073709551615 (extra)
    >Se il valore inserito è minore di 1 gli viene assegnato 1 e se è maggiore di 5 viene assegnato 5. Dopodiché viene ridotto di 1 per essere utilizzato come indice

- Tentativi a disposizione:
    1. Illimitati (semplice)
    2. 100 (medio)
    3. 50 (difficile)
    4. 20 (difficilissimo)
    5. 5 (extra)
    >Se il valore inserito è minore di 1 gli viene assegnato 1 e se è maggiore di 5 viene assegnato 5. Dopodiché viene ridotto di 1 per essere utilizzato come indice

### Versione 2 (programma indovina)
- Range:
    1. 0-100 (semplice)
    2. 0-1000 (medio)
    3. 0-1000000 (difficile)
    4. 0-1000000000 (difficilissimo)
    5. 0-18446744073709551615 (extra)
    >Se il valore inserito è minore di 1 gli viene assegnato 1 e se è maggiore di 5 viene assegnato 5. Dopodiché viene ridotto di 1 per essere utilizzato come indice

- Indicatori (ATTENZIONE! Il primo si utilizza quando il numero proposto dal programma è MAGGIORE del numero scelto, il secondo quando è minore, mentre il terzo quando la risposta è corretta):
    1. g - p - c
    2. > - < - =
    3. M - m - u
    >Se il valore inserito è minore di 1 gli viene assegnato 1 e se è maggiore di 3 viene assegnato 3. Dopodiché viene ridotto di 1 per essere utilizzato come indice

---

## Sfide
Nella prima versione, in cui il programma sceglie un numero random in base al range impostato, trovare una funzione che fosse uniformemente randomica anche per un numero delle dimensioni di un unsigned long long è stato particolarmente complesso. Con la libreria bcrypt.h, con la funzione BCryptGenRandom, è stata l'opzione più adatta tra quelle che ho trovato.
Nella seconda versione, invece, una problematica evidente sin da subito è stata quella del valore massimo del range. Infatti, proponendo sempre (max+min)/2, nel caso in cui il numero scelto sia uguale a max non si arriva mai al numero. La prima soluzione che avevo adottato era quella di partire dal tentativo del valore massimo e poi procedere con i tentativi successivi, ma era ridondante e inutile. Invece, ho ampliato il range di uno affinché anche il massimo fosse incluso.
Inoltre, attraverso la libreria setjmp.h, una volta terminato il gioco si torna al main, per evitare l'interruzione improvvisa del programma.

## Contributi e Feedback
Questo progetto è un percorso personale, ma ogni suggerimento o feedback è ben accetto! Se hai idee o commenti, apri una issue o contattami direttamente.

---

## Licenza
Questo progetto è rilasciato sotto licenza MIT. Vedi il file [LICENSE](LICENSE) per i dettagli.