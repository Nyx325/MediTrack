#include "listv_bar.h"

GtkWidget *bar_box, *bar_btn[5], *bar_img[5], *bar_lbl[3], *bar_separator,
    *bar_entry[2], *bar_btnbox[3];

void bar_init_btn() {
  short i;
  char *imgPaths[] = {"../images/add2.png", "../images/modify2.png",
                      "../images/delete2.png", "../images/search2.png",
                      "../images/back2.png"};

  char *titulos1[] = {"Agregar", "Modificar", "Eliminar"};

  for (i = 0; i < 3; i++) {
    bar_img[i] = gtk_image_new_from_file(imgPaths[i]);
    bar_lbl[i] = gtk_label_new(titulos1[i]);
    bar_btnbox[i] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_box_pack_start(GTK_BOX(bar_btnbox[i]), bar_img[i], FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(bar_btnbox[i]), bar_lbl[i], FALSE, FALSE, 0);
    bar_btn[i] = gtk_button_new();
    gtk_container_add(GTK_CONTAINER(bar_btn[i]), bar_btnbox[i]);
  }

  for (i = 3; i < 5; i++) {
    bar_btn[i] = gtk_button_new();
    bar_img[i] = gtk_image_new_from_file(imgPaths[i]);
    gtk_button_set_image(GTK_BUTTON(bar_btn[i]), bar_img[i]);
  }
}
