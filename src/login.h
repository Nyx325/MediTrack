#ifndef LOGIN_H
#define LOGIN_H

#include <gtk/gtk.h>
#include "general.h"

void gen_login      (void);
void check_login    (GtkWidget *btn, gpointer data);
void free_login     (void);

#endif
