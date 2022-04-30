# TEMA 2 ASC

Se dă următoarea operație cu matrice:
```
C = B × A × At + Bt × B
```
unde:

```
A  si B sunt matrice patratice de double de dimensiune N x N
A este o matrice superior triunghiulara
At este transpusa lui A si Bt este transpusa lui B
× este operația de înmulțire
+ este operatia de adunare
```

## Descriere Tema
Tema consta in implementarea a 3 metode diferite de calculare a formulei de mai sus
1. Calculul formulei cu ajutorul bibliotecii *cblas.h*
2. Calculul formulei "de mana", o varianta *neoptimizata*
3. Calcului formulei prin *optimizarea* calculului "de mana"

## Descriere metode
1. Calculul formulei cu ajutorul bibliotecii *cblas.h*
  Prin aceasta metoda se cere implementarea calculului formulei cu ajutorul functiilor ce se gasesc in biblioteca *cblas.h*.
  Pentru implementare am folosit urmatoarele functii:
  ```
  void cblas_dgemm(const enum CBLAS_ORDER Order, const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_TRANSPOSE TransB, const int M, const int N,
                 const int K, const double alpha, const double *A,
                 const int lda, const double *B, const int ldb,
                 const double beta, double *C, const int ldc);
  ```
  ```
  void cblas_dtrmm(const enum CBLAS_ORDER Order, const enum CBLAS_SIDE Side,
                 const enum CBLAS_UPLO Uplo, const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_DIAG Diag, const int M, const int N,
                 const double alpha, const double *A, const int lda,
                 double *B, const int ldb);
  ```
   Pentru inceput am copiat matricea *B* in care am salvat rezultatul primei operatii *B * A*.
   
   Am creat si o matrice unitate pentru a putea calcula suma finala cu ajutorul functiei *cblas_dgemm*.
   
   Prima operatie efectuata este *B * A* rezultatul fiind salvat in copia matricii *B* si este efectuata cu ajutorul functiei *cblas_dtrmm* deoarece matricea *A* este superior triunghiulara si am putut folosi flag-ul *CblasUpper* pentru a specifica asta in functia *cblas_trmm*.
   
   A doua operatie efectuata este "B_trans * B", aceasta operatie a fost efectuata folosind functia *cblas_dgemm* ce efectuaza o calcului formulei *C = alpha * A * B + beta * C*, asadar in parametri functiei am setat ca *A = B_trans*, acest lucru realizandu-se cu flag-ul "CblasTrans" dat ca parametru, *B = B*, *alpha = 1*, iar *beta = 0* deoaece ne intereseaza doar inmultirea dintre *B_trans* si *B*.
   
   A treia operatie este inmultirea rezultatului obtinut din *B * A* cu *A_trans*, aceasta operatie a fost efectuata cu ajutorul functiei *cblas_dtrmm* in care am dat ca parametru de data aceasta si flag-ul *CblasTrans*, lucru ce va realiza ca matricea *A* data ca parametru sa fie folosita ca *A_trans*.
   
   Ultima operatie este adunarea rezultatelor obtinute din a doua operatie si a treia operatie, acest lucru a fost realizat cu ajutorul functiei *cblas_dgemm* ce va calcula formula *C = alpha * A * B + beta * C*, de data aceasta *A = rezultatul din a treia op*, *B = matricea unitate creata la inceput*, *alpha = 1*, *beta = 1*, *C = rezultatul din a doua op*.

2. Calculul formulei "de mana", o varianta *neoptimizata*
  Prin aceasta metoda se doreste calcularea formulei date prin metoda clasica de inmultire a doua matrici.
  
  Pentru inceput am format transpusele matricilor *A* si *B* si le-am salvat in *A_trans* respectiv *B_trans*.
  
  Prima operatie efectuata este *B * A*, lucru ce a fost realizat prin inmultirea clasica a doua matrici folosind 3 bucle *for* de forma *i-j-k*, dar deoarece matricea *A* este superior triunghiulara bucla *k* incepe de la *0* si se termina la *j*.
  
  A doua operatie efectuata este inmultirea rezultatului din operatia anterioara cu *A_trans*, acest lucru a fost realizat print 3 bucle *for* de forma *i-j-k*, dar deoarece *A_trans* este o matrice inferior triunghiulara bucla *k* incepede de la *j* si se termina la *N*.
  
  A treia operatie efectuata este *B_trans * B*, aceasta operatie a fost realizata prin 3 bucle *for* de forma *i-j-k*.
  
  Ultima operatie este cea de adunare a rezultatului din a doua operatie cu rezultatul din a treia operatie, lucru ce s-a realizat prin 2 bucle *for* de for *i-j*.
  
3. Calcului formulei prin *optimizarea* calculului "de mana"
  Prin aceasta metoda se doreste optimizarea metodei "de mana", asadar operatiile efectuate in aceasta metoda sunt similare cu metoda anterioara, dar *optimizate*, acest lucru fiind posibil prin schimbarea buclelor din *i-j-k* in *i-k-j* si accesarea mai rapida a datelor. Acest lucru a fost realizat prin salvarea constantelor in *registre*. Prin *constante* ma refer la *adresa* unei *coloane* sau *linie* dintr-o matrice. De exemplu pentru operatia *B * A*:

```
	// tmp1 = B * A
	for (i = 0; i < N; i++) {
		register double *indexInitB = &B[i * N];
		register double *indexInitTmp1 = &tmp1[i * N];
		for (k = 0; k < N; k++) {
			register double iB = indexInitB[k];
			register double *iA = &A[k * N]; 
			for (j = k; j < N; j++) {
				indexInitTmp1[j] += iB * iA[j];
			}
		}
	}
```
Am salvat in *indexInitB* adresa unui block *i*N* din matricea *B*, iar in *indexInitTmp1* am salvat un block *i*N* din matricea *tmp1* in care se va pastra rezultatul. In bucla *k* am salvat in *iB* o *linie* din matricea *B*, iar in *iA* am salvat un block *i*N* din matricea *A*, toate aceste varibile fiind de tip *register double*. Pentru ca matricea *A* este superior triunghiulara bucla *j* va incepe de la *k* si se va termina la *N*.

Restul operatiilor au in spate aceeasi logica de salvare/accesare a memoriei ca in operatia descrisa mai sus.

## Descriere Valgrind Memory Output
  Outputurile rezultate prin rularea comenzii
```
valgrind --tool=memcheck --leak-check=full --log-file="metoda.memory" ./tema2_metoda /export/asc/tema2/input_valgrind
```
  Nu prezinta niciun memory leak sau o problema de accesare a memoriei pentru nicio metoda.
  
## Descriere Valgrind Cache Output

1. *I refs - Cache accesses for instruction fetches*
2. *D refs - Cache accesses for data follow*
3. *Branches - Number of executed conditional branches*

4. neopt.cache
  ```
  I   refs:      3,631,167,606
  D   refs:      1,944,509,417  (1,812,164,779 rd   + 132,344,638 wr)
  Branches:        132,394,842  (  132,154,146 cond +     240,696 ind)
  ```
5. opt_m.cache
  ```
    I   refs:      2,857,594,952
    D   refs:      1,172,202,939  (1,040,818,181 rd   + 131,384,758 wr)
    Branches:        132,395,019  (  132,154,311 cond +     240,708 ind)
  ```
6. blas.cache
  ```
  I   refs:      310,694,858
  D   refs:      115,748,787  (109,271,783 rd   + 6,477,004 wr)
  Branches:        4,897,471  (  4,639,833 cond +   257,638 ind)
  ```
  
  Se poate observa ca in cazul metodei *neopt* cele mai mari numere pentru *I refs*, *D refs*, si *Branches*. *I refs* ne arata ca in cazul *neopt* se excuta cele mai multe instructiuni, *D refs* ne arata ca se acceseaza cel mai des memoria pentru a lua/salva datele, iar *Branches* ne arata cate loop-uri de executa. Putem observa ca numarul de loop-uri din metoda *opt_m* este putin mai mare decat mare decat cel din *neopt*.
  Totusi observam ca datorita optimizarilor numarul de instructiuni executate este mai mic, dar si numarul de accesare/salvare a datelor este semnificativ mai mic.
  In concluzie, avand in vedere datele pentru fiecare metoda, putem spune ca metoda *BLAS* este cea mai buna si din punct de vedere a instructiunilor executate, a accesului de memorie, dar si numarul foarte mic de loop-uri ce se vede in valurea *Branches*.

## Descriere Grafic
  Pentru efectuarea graficului de comparare a performantei am rulat pentru fiecare *N* (400, 600, 800, 1000, 1200) fiecare metoda de 5 ori pentru a obtine o medie a timpului de rulare.
  
  Datele se gasesc in *Grafice.pdf*, unde se regaseste un tabel cu timpii pentru fiecare metoda si un grafic in care se vede performanta fiecarei metode.
  
  In concluzie metoda BLAS este cea rapida metoda de calculare a formulei data.
