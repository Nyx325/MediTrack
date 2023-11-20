#include <gtk/gtk.h>

void button_clicked(GtkWidget *widget, gpointer data) {
  g_print("El botón con icono ha sido clicado.\n");
}

int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv);

  // Crear una ventana principal
  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Botón con Icono");
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);
  gtk_widget_set_size_request(window, 300, 200);

  // Crear un botón con un icono
  GtkWidget *add = gtk_button_new();
  GtkWidget *add_icon = gtk_image_new_from_file("../images/add2.png");
  gtk_button_set_image(GTK_BUTTON(add), add_icon);

  GtkWidget *add_lbl = gtk_label_new("Agregar");


  GtkWidget *modify = gtk_button_new();
  GtkWidget *modify_icon = gtk_image_new_from_file("../images/modify2.png");
  gtk_button_set_image(GTK_BUTTON(modify), modify_icon);

  GtkWidget *modify_lbl = gtk_label_new("Modificar");

  GtkWidget *delete = gtk_button_new();
  GtkWidget *delete_icon = gtk_image_new_from_file("../images/delete2.png");
  gtk_button_set_image(GTK_BUTTON(delete), delete_icon);

  GtkWidget *del_lbl = gtk_label_new("Eliminar");

  GtkWidget *search = gtk_button_new();
  //GtkWidget *search_icon = gtk_image_new_from_file("../images/delete2.png");
  //gtk_button_set_image(GTK_BUTTON(search), search_icon);

  // Conectar una función de callback al botón (opcional)
  g_signal_connect(G_OBJECT(add), "clicked", G_CALLBACK(button_clicked),
                   NULL);
  g_signal_connect(G_OBJECT(modify), "clicked", G_CALLBACK(button_clicked),
                   NULL);
  g_signal_connect(G_OBJECT(delete), "clicked", G_CALLBACK(button_clicked),
                   NULL);
  g_signal_connect(G_OBJECT(search), "clicked", G_CALLBACK(button_clicked),
                   NULL);

  // Agregar el botón a la ventana
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

  // Crear un separador horizontal
  GtkWidget *separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);

  // Crear un cuadro de texto
  GtkWidget *curp_entry = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(curp_entry), "CURP");

  GtkWidget *name_entry = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(name_entry), "Nombre");

  //limitar tamanio
  gtk_widget_set_size_request(box, -1, 200);

  //Agregar widgets
  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_box_pack_start(GTK_BOX(box), add, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), add_lbl, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), modify, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), modify_lbl, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), delete, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), del_lbl, FALSE, FALSE, 0);
  // Agregar el separador al contenedor de la caja
  gtk_box_pack_start(GTK_BOX(box), separator, TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(box), curp_entry, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), name_entry, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), search, FALSE, FALSE, 0);

  // Mostrar todo y entrar en el bucle principal
  gtk_widget_show_all(window);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_main();

  return 0;
}
