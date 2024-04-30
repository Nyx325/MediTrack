#include "usr.h"
#include <stdlib.h>
#include <string.h>

Usr* usr_new(const gchar* usr, const gchar* pwd){
    Usr* new = (Usr*)malloc(sizeof(Usr));
    if(new==NULL){
        g_print("No se pudo instanciar usuario");
        return NULL;
    }
    
    strcpy(new->usrname, usr);
    strcpy(new->pwd, pwd);
    return new;
}

void usr_destroy(Usr** usr){
    if(usr == NULL) return;
    if(*usr == NULL) return;

    free(*usr);
    *usr = NULL;
}
