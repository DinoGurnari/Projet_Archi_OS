#ifndef __PROCESSUS_H__
#define __PROCESSUS_H__

#define NB_PROC 512
#define STACK_SIZE 1024

typedef __UINT32_TYPE__ pid_t;

typedef enum {
    ELU,
    PRET,
    BLOQUE
} etatProcessus;

typedef struct {
    char* nom;
    pid_t pid;
    etatProcessus etat;
    //int8_t priorite;
    //ctx?
    __UINT32_TYPE__ pile[STACK_SIZE];
    int sommet;
} processus_t;

// Stockage sous forme de liste chainée
typedef struct elementTableP elementTableP;
struct elementTableP {
    processus_t processus;
    elementTableP* prochain;
};

typedef elementTableP* tableProcessus_t;

typedef void* (*fnptr)();

tableProcessus_t tableProcessus;// Table des processus
int cpt_p;                  // Compteur de processus courant
int cpt_pid;                // Compteur pour attribution des pid

extern void ctx_sw();

// Premier processus
void init_processus();

// Créer un processus
pid_t creerProcessus(char* nom, fnptr fonction);

// Terminer un processus
int terminerProcessus(pid_t pid);

// Bloquer un processus
int bloquerProcessus(pid_t pid, int sec);

#endif