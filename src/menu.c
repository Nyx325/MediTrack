#include "menu.h"
#include "form_med.h"
#include "listv.h"

WinMenu menu;

void free_menu(GtkWidget *widget, gpointer data) {
  ushort i;
  gtk_widget_hide(menu.baseVentana.win);

  if (!menu.banner)
    gtk_widget_destroy(menu.banner);

  for (i = 0; i < 2; i++)
    if (!menu.titulos[i]) {
      gtk_widget_destroy(menu.titulos[i]);
      menu.titulos[i] = NULL;
    }

  free_basebtn(&menu.medicamentos);
  free_basebtn(&menu.pacientes);
  free_basebtn(&menu.proveedores);

  free_baseform(&menu.baseVentana);

  menu.banner = NULL;
}

void pacientes(GtkWidget *widget, gpointer data) {
  desconectar_señal_btn(&bar.agregar.base.btn);
  desconectar_señal_btn(&bar.modificar.base.btn);
  desconectar_señal_btn(&bar.eliminar.base.btn);

  listv_gen_table();
  mostrar_pacientes("../data/pacientes.dat");
  free_menu(NULL, NULL);

  g_signal_connect(G_OBJECT(bar.agregar.base.btn), "clicked",
                   G_CALLBACK(pac_agregar_callback), NULL);
  g_signal_connect(G_OBJECT(bar.modificar.base.btn), "clicked",
                   G_CALLBACK(pac_mod_callback), NULL);
  g_signal_connect(G_OBJECT(bar.eliminar.base.btn), "clicked",
                   G_CALLBACK(eliminar_datos_paciente), NULL);
}

void medicamentos(GtkWidget *widget, gpointer data) {
  desconectar_señal_btn(&bar.agregar.base.btn);
  desconectar_señal_btn(&bar.modificar.base.btn);
  desconectar_señal_btn(&bar.eliminar.base.btn);

  listv_gen_table();
  mostrar_medicamentos("../data/medicamentos.dat");
  free_menu(NULL, NULL);

  g_signal_connect(G_OBJECT(bar.agregar.base.btn), "clicked",
                   G_CALLBACK(agregar_medicamentos_callback), NULL);
  g_signal_connect(G_OBJECT(bar.modificar.base.btn), "clicked",
                   G_CALLBACK(modificar_medicamentos_callback), NULL);
  // g_signal_connect(G_OBJECT(bar.eliminar.base.btn), "clicked",
  //                  G_CALLBACK(eliminar_datos_paciente), NULL);
}

void proveedores(GtkWidget *widget, gpointer data) {
  desconectar_señal_btn(&bar.agregar.base.btn);
  desconectar_señal_btn(&bar.modificar.base.btn);
  desconectar_señal_btn(&bar.eliminar.base.btn);

  listv_gen_table();
  mostrar_proveedores("../data/proveedores.dat");
  free_menu(NULL, NULL);
}

void crear_menu() {
  crear_ventana(&menu.baseVentana, 1280, 720, NULL);
  g_signal_connect(G_OBJECT(menu.baseVentana.win), "destroy",
                   G_CALLBACK(gtk_main_quit), NULL);

  crear_btn_img(&menu.proveedores, "../images/proveedores_menu.jpg");
  g_signal_connect(G_OBJECT(menu.proveedores.btn), "clicked",
                   G_CALLBACK(proveedores), NULL);
  crear_btn_img(&menu.pacientes, "../images/pacientes_menu.png");
  g_signal_connect(G_OBJECT(menu.pacientes.btn), "clicked",
                   G_CALLBACK(pacientes), NULL);
  crear_btn_img(&menu.medicamentos, "../images/medicinas_menu.jpg");
  g_signal_connect(G_OBJECT(menu.medicamentos.btn), "clicked",
                   G_CALLBACK(medicamentos), NULL);

  menu.banner = gtk_image_new_from_file("../images/banner_login.png");

  char *titulos[] = {"Medicamentos", "Pacientes", "Proveedores"};
  ushort i;
  for (i = 0; i < 3; i++)
    menu.titulos[i] = gtk_label_new(titulos[i]);

  gtk_grid_attach(GTK_GRID(menu.baseVentana.grid), menu.banner, 0, 0, 6, 1);
  // Opc medicamentos
  gtk_grid_attach(GTK_GRID(menu.baseVentana.grid), menu.medicamentos.btn, 0, 1,
                  1, 2);
  gtk_grid_attach(GTK_GRID(menu.baseVentana.grid), menu.titulos[0], 0, 3, 2, 1);
  // Opc pacientes
  gtk_grid_attach(GTK_GRID(menu.baseVentana.grid), menu.pacientes.btn, 5, 1, 1,
                  2);
  gtk_grid_attach(GTK_GRID(menu.baseVentana.grid), menu.titulos[1], 5, 3, 2, 1);
  // Opc proveedores
  gtk_grid_attach(GTK_GRID(menu.baseVentana.grid), menu.proveedores.btn, 2, 1,
                  1, 2);
  gtk_grid_attach(GTK_GRID(menu.baseVentana.grid), menu.titulos[2], 2, 3, 2, 1);

  gtk_widget_show_all(menu.baseVentana.win);
}
