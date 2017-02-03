# Note ed Indice

Inidice:


1. CPLEX
    1. Definizione del modello
    2. Problemi implementativi e riduzione del numero di variabili
2. Algoritmo genetico
    1. Scelte progettuali:
        - Codifica delle soluzioni (la stessa di CPLEX)
        - Generazione della popolazione iniziale: ogni soluzione viene costruita effettuando delle scelte greedy random
        - Funzione di fitness -> funzione obiettivo
        - Opertaori di selezione: k-tournament
        - Crossover uniforme: viene evitata la selezione di caratteristiche unfeasible in modo da avere dei figli sempre corretti
        - Mutazione: casuale, facendo lo shuffle della codifica del vettore in modo che la soluzione rimanga feasible
        - Sostituzione della popolazione: dimensione fissa, ridimensionata utilizzando monte-carlo
        - Criterio di stop: numero stabilito di iterazioni, che varia rispetto alla dimensione del problema. (Per via di come
        sarà confrontato con CPLEX)
    2. Parametri:
        1. Lista dei parametri
            - Dimensione della popolazione
            - Numero di nuove soluzioni generate
            - Mutation rate
            - Parametro che controlla il numero di iterazioni
        2. Esperimenti per la ricerca della configurazione migliore:
            - Schema a griglia: provo pochi valori in tutte le possibili combinazioni su problemi per i quali so la soluzione ottima.
            Per ogni combinazione ed istanza faccio 10 run e tengo i valori medi.
            Traccio:
                - Tempo d'esecuzione medio
                - Valore migliore trovato mediamente e gap dall'ottimo
                - Numero di volte in cui è stata trovata una soluzione ottima
            
            Ho provato POPSIZE 100, 250 , 500, Mutation rate = 0.01, 0.05, 0.1 e NEWGENRATIO su 1.1, 1.5, 2
3. Contronto tra CPLEX e GA.
    1. Generazione delle istanze in modo pseudo-random
    2. Test: 1 run di CPEX, contro la media di 5 run di GA.
    Provo vari timelimit: 0.1 Secondi, 1 secondo, 10 secondi, 1 minuto, 5 minuti.
    Per ogni timelimit incremento a step di 10, partendo da 10 la dimensione dell'istanza. Per ogni dimensione
    dell'istsanza provo 5 istanze diverse
    3. Comportamento sull'esecuzione di istanze realistiche. Ci sono solo due istanze. Provo a risolverle sia con
    CPLEX che con 5 run dell'algoritmo Genetico.
4. Appendice: Commenti sul codice. Cosa fa il main.
