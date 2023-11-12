#ifndef BAR_H
#define BAR_H

#include "widl.h"

void create_bar(WlNode **widl);
GtkWidget *create_btn(WlNode **widl, const char *lbl_txt,
                      const char *icon_path);

#endif
