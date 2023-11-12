#include "bar.h"

void button_clicked(GtkWidget *widget, gpointer data) {
  g_print("El botón con icono ha sido clicado.\n");
}

GtkWidget *create_btn(WlNode **widl, const char *lbl_txt,
                      const char *icon_path) {
  char buffer[30];
  // disenio del boton
  GtkWidget *img = gtk_image_new_from_file(icon_path);
  strcpy(buffer, lbl_txt);
  strcat(buffer, "_img");
  add_wlnode(widl, img, buffer, NO_ID);

  GtkWidget *lbl = gtk_label_new(lbl_txt);
  strcpy(buffer, lbl_txt);
  strcat(buffer, "_lbl");
  add_wlnode(widl, lbl, buffer, NO_ID);

  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
  strcpy(buffer, lbl_txt);
  strcat(buffer, "_box");
  add_wlnode(widl, box, buffer, NO_ID);

  gtk_box_pack_start(GTK_BOX(box), img, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), lbl, FALSE, FALSE, 0);

  GtkWidget *btn = gtk_button_new();
  strcpy(buffer, lbl_txt);
  strcat(buffer, "_btn");
  add_wlnode(widl, btn, buffer, NO_ID);
  gtk_container_add(GTK_CONTAINER(btn), box);

  return btn;
}

void create_bar(WlNode **widl) {
  // obtener main box
  WlNode *mainbox = find_node("main_box", NO_ID, widl);

  GtkWidget *add = create_btn(widl, "agregar", "../images/add2.png");
  GtkWidget *modify = create_btn(widl, "modificar", "../images/modify2.png");
  GtkWidget *delete = create_btn(widl, "eliminar", "../images/delete2.png");
  GtkWidget *search = gtk_button_new();
  add_wlnode(widl, search, "search_btn", NO_ID);
  GtkWidget *search_img = gtk_image_new_from_file("../images/search2.png");
  add_wlnode(widl, search_img, "search_img", NO_ID);
  gtk_button_set_image(GTK_BUTTON(search), search_img);

  // Conectar una función de callback a los botones
  g_signal_connect(G_OBJECT(add), "clicked", G_CALLBACK(button_clicked), NULL);
  g_signal_connect(G_OBJECT(modify), "clicked", G_CALLBACK(button_clicked),
                   NULL);
  g_signal_connect(G_OBJECT(delete), "clicked", G_CALLBACK(button_clicked),
                   NULL);
  g_signal_connect(G_OBJECT(search), "clicked", G_CALLBACK(button_clicked),
                   NULL);

  // Agregar el botón a la ventana
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  add_wlnode(widl, box, "bar_box", NO_ID);

  // Crear un separador horizontal
  GtkWidget *separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
  add_wlnode(widl, separator, "bar_separator", NO_ID);

  // Crear un cuadro de texto
  GtkWidget *curp_entry = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(curp_entry), "CURP");
  add_wlnode(widl, curp_entry, "curp_entry", NO_ID);

  GtkWidget *name_entry = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(name_entry), "Nombre");
  add_wlnode(widl, name_entry, "name_entry", NO_ID);

  // limitar alto de la box
  gtk_widget_set_size_request(box, -1, 30);

  // Agregar widgets a la box de la bar
  gtk_box_pack_start(GTK_BOX(box), add, FALSE, FALSE, 0);
  // gtk_box_pack_start(GTK_BOX(box), add_lbl, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), modify, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), delete, FALSE, FALSE, 0);
  // Agregar el separador al contenedor de la caja
  gtk_box_pack_start(GTK_BOX(box), separator, TRUE, TRUE, 0);
  // agregar entrys y boton de busqueda
  gtk_box_pack_start(GTK_BOX(box), curp_entry, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), name_entry, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), search, FALSE, FALSE, 0);

  // aregar la barra creada a la main box
  gtk_box_pack_start(GTK_BOX(GTK_WIDGET(mainbox->data)), box, FALSE, FALSE, 0);
}
