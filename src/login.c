#include "login.h"

LoginWindow login;

void check_login(GtkWidget *btn, gpointer data) {
  Usuario usrLeido;
  const gchar *usuario = gtk_entry_get_text(GTK_ENTRY(login.usuario));
  const gchar *contrasenia = gtk_entry_get_text(GTK_ENTRY(login.contrasenia));

  FILE *arch = fopen("../data/usr", "rb");
  if (arch == NULL) {
    g_print("archivo usr no encontrado\n");
    gtk_main_quit();
    return;
  }

  while (fread(&usrLeido, sizeof(Usuario), 1, arch)) {
    if (strcmp(usuario, usrLeido.nombreUsr) == 0 &&
        strcmp(contrasenia, usrLeido.contrasenia) == 0) {
      fclose(arch);
      crear_menu(usrLeido.tipo);
      gtk_widget_hide(login.baseLog.win);
      return;
    }
  }
  fclose(arch);

  gtk_label_set_markup(
      GTK_LABEL(login.warning),
      "<span foreground='red'>Usuario o contraseña incorrectos</span>");
}

void crear_entry(GtkWidget **entrada, char *titulo) {
  *entrada = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(*entrada), titulo);
  g_signal_connect(G_OBJECT(*entrada), "button-press-event",
                   G_CALLBACK(reset_warning), login.warning);
}

void gen_login() {
  crear_ventana(&login.baseLog, 750, 400, check_login);
  g_signal_connect(G_OBJECT(login.baseLog.win), "destroy",
                   G_CALLBACK(gtk_main_quit), NULL);

  login.banner = gtk_image_new_from_file("../images/banner_login.png");
  login.warning = gtk_label_new("");
  crear_boton(&login.aceptBtn, "Aceptar", check_login);
  crear_entry(&login.usuario, "Usuario");
  crear_entry(&login.contrasenia, "Contraseña");
  // Hacer invisible el texto ingresado
  gtk_entry_set_visibility(GTK_ENTRY(login.contrasenia), FALSE);

  gtk_grid_attach(GTK_GRID(login.baseLog.grid), login.banner, 0, 0, 4, 1);
  gtk_grid_attach(GTK_GRID(login.baseLog.grid), login.usuario, 1, 1, 2, 1);
  gtk_grid_attach(GTK_GRID(login.baseLog.grid), login.contrasenia, 1, 2, 2, 1);
  gtk_grid_attach(GTK_GRID(login.baseLog.grid), login.warning, 0, 3, 4, 1);
  gtk_grid_attach(GTK_GRID(login.baseLog.grid), login.aceptBtn, 1, 4, 2, 1);

  gtk_widget_show_all(login.baseLog.win);
}
