#ifndef USR_H
#define USR_H

#include <gtk/gtk.h>

typedef struct{
    gchar usrname[31];
    gchar pwd[31];
}Usr;

Usr* usr_new(const gchar* usr, const gchar* pwd);
void usr_destroy(Usr** usr);

#endif // !USR_H
