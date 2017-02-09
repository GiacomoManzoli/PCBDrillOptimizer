# PCBDrillOptimizer

Il Makefile contiene le regole per compilare i vari eseguibili:

- `make`: compila il `main.cpp` che contiene una demo d'uso delle due parti
- `make cplex_rand`: compila il benchmark di CPEX sulle istanze casuali
- - `make cplex_pseudo`: compila il benchmark di CPEX sulle istanze pseudo-casuali
- `make ga_rand`: compila il benchmark dell'algoritmo genetico sulle istanze casuali
- `make ga_pseudo`: compila il benchmark dell'algoritmo genetico sulle istanze pseudo-casuali
- `make ga_test`: compila il test runner per l'ottimizzazione dell'algoritmo genetico
- `make all`: esegue tutti i `make` sopra riportati
- `make clean`: pulisce tutto
