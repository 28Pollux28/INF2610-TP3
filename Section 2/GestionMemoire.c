#include<stdbool.h>
#include "./libs/lib.h"
#include <stdio.h>

#define DEBUG 1

unsigned int calculerNumeroDePage(unsigned long adresse) {
    return adresse >> 10;
}

unsigned long calculerDeplacementDansLaPage(unsigned long adresse) {
	return adresse & 0x3FF;
}

unsigned long calculerAdresseComplete(unsigned int numeroDePage, unsigned long deplacementDansLaPage) {
     return (numeroDePage << 10) | deplacementDansLaPage;
}

void rechercherTLB(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	if(DEBUG){
		printf("Recherche dans le TLB START\n");
		printf("Adresse Virtuelle: %lu\n", req->adresseVirtuelle);
		printf("Date: %lu\n", req->date);
		printf("Est dans TLB: %d\n", req->estDansTLB);
		printf("Est dans Table des Pages: %d\n", req->estDansTablePages);
		printf("Adresse Physique: %lu\n", req->adressePhysique);
	}
	unsigned int page = calculerNumeroDePage(req->adresseVirtuelle);
	for (int i = 0; i < TAILLE_TLB; i++) {
		if (mem->tlb->entreeValide[i] && mem->tlb->numeroPage[i] == page) {
			req->estDansTLB = 1;
			req->adressePhysique = calculerAdresseComplete(mem->tlb->numeroCadre[i], calculerDeplacementDansLaPage(req->adresseVirtuelle));
			mem->tlb->dernierAcces[i] = req->date;
			if(DEBUG){
				printf("Recherche dans le TLB END\n");
				printf("Adresse Virtuelle: %lu\n", req->adresseVirtuelle);
				printf("Date: %lu\n", req->date);
				printf("Est dans TLB: %d\n", req->estDansTLB);
				printf("Est dans Table des Pages: %d\n", req->estDansTablePages);
				printf("Adresse Physique: %lu\n", req->adressePhysique);
			}
			return;
		}
	}
	req->estDansTLB = 0;
	req->adressePhysique = 0;

	if(DEBUG){
		printf("Recherche dans le TLB END\n");
		printf("Adresse Virtuelle: %lu\n", req->adresseVirtuelle);
		printf("Date: %lu\n", req->date);
		printf("Est dans TLB: %d\n", req->estDansTLB);
		printf("Est dans Table des Pages: %d\n", req->estDansTablePages);
		printf("Adresse Physique: %lu\n", req->adressePhysique);
	}


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
