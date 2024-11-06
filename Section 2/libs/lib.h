#ifndef LIB_H
#define LIB_H

#include <stdlib.h>
#include <sys/types.h>


#define TAILLE_TLB 32
#define TAILLE_TP 128
#define TAILLE_MEMOIRE 256

struct RequeteMemoire {
	u_int8_t estDansTLB;
	u_int8_t estDansTablePages;
	unsigned long adressePhysique;
	unsigned long adresseVirtuelle;
	unsigned long date;
};

struct TLB {
	unsigned int* numeroPage;
	unsigned int* numeroCadre;
	u_int8_t* entreeValide;
	unsigned long* dernierAcces;
	unsigned long* dateCreation;
};

struct TablePages {
	unsigned int* numeroCadre;
	u_int8_t* entreeValide;
};

struct Memoire {
	unsigned int* numeroPage;
	unsigned long* dernierAcces;
	unsigned long* dateCreation;
	u_int8_t* utilisee;
};

struct SystemeMemoire {
	struct TLB* tlb;
	struct TablePages* tp;
	struct Memoire* memoire;
};

#endif

void evaluate(
	unsigned int(*calculerNumeroDePage)(unsigned long),
    unsigned long(*calculerDeplacementDansLaPage)(unsigned long),
    unsigned long(*calculerAdresseComplete)(unsigned int, unsigned long),
    void(*rechercherTLB)(struct RequeteMemoire*, struct SystemeMemoire*),
	void(*rechercherPT)(struct RequeteMemoire*, struct SystemeMemoire*),
	void(*mettreAJourTLB)(struct RequeteMemoire*, struct SystemeMemoire*),
    void(*ajouterDansMemoire)(struct RequeteMemoire*, struct SystemeMemoire*));
