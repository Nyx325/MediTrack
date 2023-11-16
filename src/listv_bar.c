#include "listv_bar.h"
#include "form_pac.h"
#include "listv.h"
#include "menu.h"

GtkWidget *bar_btn[5], *bar_img[5], *bar_lbl[3], *bar_separator, *bar_entry[2],
    *bar_btnbox[3], *bar_box;

void volver_a_menu(GtkWidget *widget, gpointer data) {
  gen_menu();
  gtk_widget_hide(lv_win);
}

void gen_bar() {
  short i;
  char *imgPaths[] = {"../images/add2.png", "../images/modify2.png",
                      "../images/delete2.png", "../images/search2.png",
                      "../images/back2.png"};

  char *titulos[] = {"Agregar", "Modificar", "Eliminar"};

  // Crear botones agregar, modificar y eliminar
  for (i = 0; i < 3; i++) {
    // Si se han asociado señales a los botones con anterioridad se eliminan
    g_signal_handlers_disconnect_by_data(bar_btn[i], NULL);
    bar_img[i] = gtk_image_new_from_file(imgPaths[i]);
    bar_lbl[i] = gtk_label_new(titulos[i]);
    bar_btnbox[i] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_box_pack_start(GTK_BOX(bar_btnbox[i]), bar_img[i], FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(bar_btnbox[i]), bar_lbl[i], FALSE, FALSE, 0);
    bar_btn[i] = gtk_button_new();
    gtk_container_add(GTK_CONTAINER(bar_btn[i]), bar_btnbox[i]);
  }

  // Crear botones volever y buscar
  for (i = 3; i < 5; i++) {
    bar_btn[i] = gtk_button_new();
    bar_img[i] = gtk_image_new_from_file(imgPaths[i]);
    gtk_button_set_image(GTK_BUTTON(bar_btn[i]), bar_img[i]);
  }
  g_signal_connect(G_OBJECT(bar_btn[4]), "clicked", G_CALLBACK(volver_a_menu),
                   NULL);

  bar_separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);

  // Generar entrys de busqueda
  for (i = 0; i < 2; i++)
    bar_entry[i] = gtk_entry_new();

  bar_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_set_size_request(bar_box, 10, 10);
  gtk_widget_set_vexpand(bar_box, FALSE);
  gtk_box_pack_start(GTK_BOX(bar_box), bar_btn[4], FALSE, FALSE, 0);

  for (i = 0; i < 3; i++)
    gtk_box_pack_start(GTK_BOX(bar_box), bar_btn[i], FALSE, FALSE, 0);

  gtk_box_pack_start(GTK_BOX(bar_box), bar_separator, TRUE, TRUE, 0);

  for (i = 0; i < 2; i++)
    gtk_box_pack_start(GTK_BOX(bar_box), bar_entry[i], TRUE, TRUE, 0);

  gtk_box_pack_start(GTK_BOX(bar_box), bar_btn[3], FALSE, FALSE, 0);
}

void set_entry_placeholders(char *ph1, char *ph2) {
  gtk_entry_set_placeholder_text(GTK_ENTRY(bar_entry[0]), ph1);
  gtk_entry_set_placeholder_text(GTK_ENTRY(bar_entry[1]), ph2);
}

void free_bar() {
  short i;
  for (i = 0; i < 5; i++) {
    if (bar_btn[i]) {
      gtk_widget_destroy(bar_btn[i]);
      bar_btn[i] = NULL;
    }
    if (bar_img[i]) {
      gtk_widget_destroy(bar_btn[i]);
      bar_btn[i] = NULL;
    }
  }
  for (i = 0; i < 3; i++) {
    if (bar_btn[i]) {
      gtk_widget_destroy(bar_btn[i]);
      bar_lbl[i] = NULL;
    }
    if (bar_img[i]) {
      gtk_widget_destroy(bar_btn[i]);
      bar_btnbox[i] = NULL;
    }
  }
  for (i = 0; i < 2; i++) {
    if (bar_entry[i]) {
      gtk_widget_destroy(bar_entry[i]);
      bar_entry[i] = NULL;
    }
  }
  if (bar_box)
    gtk_widget_destroy(bar_box);
  if (bar_separator)
    gtk_widget_destroy(bar_box);
}
