#include "login.h"
#include "menu.h"
#include "widl.h"

GtkWidget *log_win, *log_grid, *log_entry[2], *log_btn, *log_img, *log_warning;
GdkPixbuf *log_icon;

void log_wingrid() {
  log_win = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  gtk_window_set_title(GTK_WINDOW(log_win), "Iniciar sesion");
  gtk_window_set_default_size(GTK_WINDOW(log_win), 750, 400);
  gtk_window_set_position(GTK_WINDOW(log_win), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(log_win), 20);
  g_signal_connect(G_OBJECT(log_win), "destroy", G_CALLBACK(gtk_main_quit),
                   NULL);

  log_grid = gtk_grid_new();

  // padding del margen del grid
  gtk_grid_set_row_spacing(GTK_GRID(log_grid), 20);    // Espaciado vertical
  gtk_grid_set_column_spacing(GTK_GRID(log_grid), 10); // Espaciado horizontal
  gtk_container_add(GTK_CONTAINER(log_win), log_grid);
  gtk_widget_set_halign(log_grid, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(log_grid, GTK_ALIGN_CENTER);

  log_icon = gdk_pixbuf_new_from_file("../images/icon.png", NULL);
  gtk_window_set_icon(GTK_WINDOW(log_win), log_icon);
}

void gen_img() {
  GtkStyleContext *context;
  log_img = gtk_image_new_from_file("../images/MT2(2).png");
  gtk_grid_attach(GTK_GRID(log_grid), log_img, 0, 0, 3, 1);

  log_warning = gtk_label_new(NULL);
  gtk_grid_attach(GTK_GRID(log_grid), log_warning, 0, 1, 3, 1);

  log_btn = gtk_button_new_with_label("Aceptar");
  gtk_grid_attach(GTK_GRID(log_grid), log_btn, 1, 4, 1, 1);
  g_signal_connect(G_OBJECT(log_btn), "clicked", G_CALLBACK(check_login), NULL);
  gtk_widget_set_name(log_btn, "button");
  context = gtk_widget_get_style_context(log_btn);
  gtk_style_context_add_class(context, "suggested-action");
}

void gen_entrys() {
  char *placeholder[2] = {"Usuario", "Contraseña"};
  int i;
  for (i = 0; i < 2; i++) {
    log_entry[i] = gtk_entry_new();

    gtk_grid_attach(GTK_GRID(log_grid), log_entry[i], 1, i + 2, 1, 1);
    gtk_entry_set_placeholder_text(GTK_ENTRY(log_entry[i]), placeholder[i]);

    // gtk_entry_set_max_length(GTK_ENTRY(log_entry), 18);
    gtk_entry_set_width_chars(GTK_ENTRY(log_entry[i]), 30);

    g_signal_connect(G_OBJECT(log_entry[i]), "button-press-event",
                     G_CALLBACK(reset_warning), log_warning);
  }

  gtk_entry_set_visibility(GTK_ENTRY(log_entry[1]), FALSE);
}

void check_login(GtkWidget *btn, gpointer data) {
  const gchar *usr_input = gtk_entry_get_text(GTK_ENTRY(log_entry[0]));
  const gchar *passwd_input = gtk_entry_get_text(GTK_ENTRY(log_entry[1]));

  char usr_read[30];
  char passwd_read[30];

  FILE *arch = fopen("../data/usr", "rt");
  if (arch == NULL) {
    g_print("archivo usr no encontrado\n");
    gtk_main_quit();
  }

  fscanf(arch, "%[^;]%*c%[^;]", usr_read, passwd_read);
  fclose(arch);

  if (strcmp(usr_input, usr_read) == 0 &&
      strcmp(passwd_input, passwd_read) == 0) {
    free_login();
    g_print("a");
    gen_menu();
    g_print("a");
  } else {
    gtk_label_set_markup(
        GTK_LABEL(log_warning),
        "<span foreground='red'>Usuario o contraseña incorrectos</span>");
  }

  g_print("a");
}

void gen_login() {
  log_wingrid();
  gen_img();
  gen_entrys();

  gtk_widget_show_all(log_win);
}

void free_login() {
  gtk_widget_hide(log_win);

  // llamar aqui al menu de inicio para que no se cierre

  gtk_widget_destroy(log_btn);
  gtk_widget_destroy(log_warning);
  gtk_widget_destroy(log_img);
  gtk_widget_destroy(log_entry[0]);
  gtk_widget_destroy(log_entry[1]);
  gtk_widget_destroy(log_grid);
  gtk_widget_destroy(log_win);
  g_object_unref(log_icon);
}
