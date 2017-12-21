Structuri de date - Tema 3
Maftei Stefan - Radu
314 CD

=== Intro ===

	Pentru implementarea temei am folosit fisiere implementate la laborator
pentru lucrul cu grafuri (Graph.h, Graph.c) si pentru folosirea heap-ului (heap.h).

=== Task 1 ===

	Dupa ce s-a citit din fisier se aplica functia dijkstra() fiecarui nod.
Functia este o implementare a algoritmului Dijkstra in care se retin si parintii
nodurilor pentru a se salva calea parcursa pentru distanta minima.
	Avem doua functii ajutatoare:
	-> printArr_Dijkstra() - scrie in fisier distanta si nodul de unde incepe
				calea de cost minim;
	-> printParentPath() - scrie in fisier calea parcursa pentru costul minim,
				fara a include nodul de inceput (aceasta cale
				reprezinta parintii nodurilor).

	Afisarea se facea pana la un nod negru, iar in cazul in care nu se putea
ajunge la un nod negru, se afisa -1.

=== Task 2 ===

	Dupa ce s-au citit din fisier numarul de secvente si secventele am aplicat
metoda Backtracking pentru produsul cartezian, unde avem n = numarul de culori din
secventa si multimile sunt identice si anume multimea de noduri din graf.
	Astfel am apelat functiile BK1() pentru a alfa numarul de solutii si
BK2() pentru a afisa toate solutiile. Am folosit functiile ajutatoare:
	-> solution() - verifica daca array-ul gasit e solutie; in cadrul
			acestei functii se verifica daca culorile coincid
			si daca nodurile consecutive sunt adiacente;
	-> printSolution() - afiseaza costul caii gasite si calea (vectorul solutie).

=== Outro ===

	La final se dezaloca memoria alocata structurii de graf si memoria alocata
vectorilor de culori, de secvente de culori, solutie si multimea de noduri.
