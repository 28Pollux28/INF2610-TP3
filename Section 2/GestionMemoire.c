#include<stdbool.h>
#include "./libs/lib.h"

unsigned int calculerNumeroDePage(unsigned long adresse) {
	// TODO
    return 0;
}

unsigned long calculerDeplacementDansLaPage(unsigned long adresse) {
	// TODO
     return 0;
}

unsigned long calculerAdresseComplete(unsigned int numeroDePage, unsigned long deplacementDansLaPage) {
	// TODO
     return 0;
}

void rechercherTLB(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	// TODO
}

void rechercherTableDesPages(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	// TODO
}

void ajouterDansMemoire(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	//TODO
}

void mettreAJourTLB(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	// TODO
}

// NE PAS MODIFIER
int main() {
    evaluate(
		&calculerNumeroDePage, 
		&calculerDeplacementDansLaPage, 
		&calculerAdresseComplete, 
        &rechercherTLB, 
		&rechercherTableDesPages,
		&mettreAJourTLB,
		&ajouterDansMemoire
    );
    return 0;
}
