#ifndef LISTV_H
#define LISTV_H

#include "listv_bar.h"
#include "general.h"

extern GtkWidget *lv_win, *lv_box, *lv_tview, *lv_scrollw;
extern GtkListStore *lv_lstore;

void    free_listv          (void);
void    lv_importmodel      (unsigned short numCols, char *titulos[]);
void    init_listv          (char *titulo);

#endif
