#include <n7OS/processus.h>
#include <malloc.h>

// J'ai du commenter les réferences à malloc et free car le compilateur ne les trouvait pas 

// Ajouter un processus à la table
void ajoutTable(processus_t process) {
    elementTableP* p = tableProcessus;

    while (p->prochain != NULL) {
        p = p->prochain;
    }

    /* elementTableP* newE = malloc(sizeof(elementTableP));
    newE->processus = process;
    newE->prochain = NULL;

    p->prochain = newE; */
}

// Retirer un processus
int retirerTable(pid_t pid) {

    // Si vide
    if (tableProcessus == NULL) {
        return -1;
    // Si 1 élément
    } else if (tableProcessus->prochain == NULL && pid == 0) {
        //free(tableProcessus);

        return 0;
    }

    elementTableP* tmp = tableProcessus;
    elementTableP* tmpr = tableProcessus;

    while (tmp->prochain != NULL) {
        tmpr = tmp;
        tmp = tmp->prochain;
        // tmpr correspond au pointeur d'avant
        if (tmp->processus.pid == pid) {
            tmpr->prochain = tmp->prochain;
            //free(tmp);
            return pid;
        }
    }
    // Si on arrive ici c'est que le pid n'existe pas 
    return -1;
}

// Chercher un processus
elementTableP* chercherTable(pid_t pid) {

    elementTableP* res = tableProcessus;

    while (res != NULL) {
        if (res->processus.pid == pid) {
            return res;
        }

        res = res->prochain;
    }

    return NULL;
}

// Premier processus
void init_processus() {
    tableProcessus = NULL;
    cpt_p = 0;
    cpt_pid = 0;

    //creerProcessus("idle", );
}

// Créer un processus
pid_t creerProcessus(char* nom, fnptr fonction) {
    processus_t newP;

    newP.nom = nom;
    newP.pid = cpt_pid++;
    newP.sommet = STACK_SIZE - 1;
    newP.pile[newP.sommet--] = (__UINT32_TYPE__) fonction;

    ajoutTable(newP);
    cpt_p++;

    return newP.pid;
}

// Terminer un processus
int terminerProcessus(pid_t pid) {
    if (retirerTable(pid) == -1) {
        return -1;
    } else {
        cpt_p--;
        return pid;
    }
}
