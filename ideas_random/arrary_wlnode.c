#include "widl.h"
#include <gtk/gtk.h>

void acceder(WlNode **lista) {
  WlNode *btn[2];
  for (int i = 0; i < 2; i++) {
    btn[i] = find_node("btn", i, lista);
    g_print("%s\n\n", btn[i]->desc);
  }
}

int main() {
  gtk_init(NULL, NULL);

  WlNode *lista = NULL;
  GtkWidget *btn[2];

  for (int i = 0; i < 2; i++) {
    btn[i] = gtk_button_new_with_label("a");
    add_wlnode(&lista, btn[i], "btn", i);
  }

  acceder(&lista);

  gtk_main();
}
