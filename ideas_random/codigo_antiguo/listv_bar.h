#ifndef LISTV_BAR_H
#define LISTV_BAR_H

#include "general.h"
#include "form_pac.h"
#include "listv.h"
#include "menu.h"

void    gen_bar                 (void);
void    set_entry_placeholders  (char *ph1, char *ph2);
void    free_bar                (void);

// Potencial mala práctica
extern GtkWidget *bar_box, *bar_entry[2], *bar_btn[5];

#endif
