#include "menu.h"
#include "form_pac.h"
#include "form_prov.h"
#include "listv.h"
#include "listv_bar.h"

GtkWidget *m_win, *m_grid, *m_btn[3], *m_lbl[4], *m_banner, *m_btn_img[3];
GdkPixbuf *m_icon;

void free_menu() {
  ushort i;

  gtk_widget_hide(m_win);

  for (int i = 0; i < 3; i++) {
    if (m_btn[i]) {
      gtk_widget_destroy(m_btn[i]);
      m_btn[i] = NULL;
    }
    if (m_lbl[i]) {
      gtk_widget_destroy(m_lbl[i]);
      m_lbl[i] = NULL;
    }
  }
  /*
  for (int i = 0; i < 3; i++) {
    if (m_btn_img[i]) {
      gtk_widget_destroy(m_btn_img[i]);
      m_btn_img[i] = NULL;
    }
  }*/
  if (m_banner) {
    gtk_widget_destroy(m_banner);
    m_banner = NULL;
  }
  if (m_icon) {
    g_object_unref(m_icon);
    m_icon = NULL;
  }
  if (m_grid) {
    gtk_widget_destroy(m_grid);
    m_grid = NULL;
  }
  /*
  if (m_win) {
    gtk_widget_destroy(m_win);
    m_win = NULL;
  }*/
}

void gen_menu() {
  ushort i;
  char *img_btn_path[] = {"../images/medicinas_menu2.jpeg",
                          "../images/pacientes_menu2.png",
                          "../images/proveedores_menu2.jpg"};
  char *btn_titles[] = {"Medicamentos", "Pacientes", "Proveedores"};
  // Array de punteros a funciones para los callbacks de la creacion
  // de botones
  void (*callbacks[3])(GtkWidget *, gpointer) = {medicamento, pacientes, proveedores};

  m_win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(m_win), 1280, 720);
  gtk_window_set_title(GTK_WINDOW(m_win), "MediTrack");
  gtk_window_set_position(GTK_WINDOW(m_win), GTK_WIN_POS_CENTER);
  g_signal_connect(G_OBJECT(m_win), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  m_grid = gtk_grid_new();
  // padding del margen del grid
  gtk_grid_set_row_spacing(GTK_GRID(m_grid), 20);    // Espaciado vertical
  gtk_grid_set_column_spacing(GTK_GRID(m_grid), 10); // Espaciado horizontal
  gtk_widget_set_halign(m_grid, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(m_grid, GTK_ALIGN_CENTER);

  m_icon = gdk_pixbuf_new_from_file("../images/icon.png", NULL);
  gtk_window_set_icon(GTK_WINDOW(m_win), m_icon);

  m_banner = gtk_image_new_from_file("../images/MT2(2).png");

  for (i = 0; i < 3; i++) {
    m_lbl[i] = gtk_label_new(btn_titles[i]);
    m_btn[i] = gtk_button_new();
    m_btn_img[i] = gtk_image_new_from_file(img_btn_path[i]);
    gtk_widget_set_size_request(m_btn[i], 90, 90);
    gtk_button_set_image(GTK_BUTTON(m_btn[i]), m_btn_img[i]);
    g_signal_connect(G_OBJECT(m_btn[i]), "clicked", G_CALLBACK(callbacks[i]),
                     NULL);
  }

  gtk_grid_attach(GTK_GRID(m_grid), m_banner, 0, 0, 5, 1);
  // Opc medicamentos
  gtk_grid_attach(GTK_GRID(m_grid), m_btn[0], 2, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(m_grid), m_lbl[0], 0, 2, 5, 1);
  // Opc pacientes
  gtk_grid_attach(GTK_GRID(m_grid), m_btn[1], 2, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(m_grid), m_lbl[1], 0, 4, 5, 1);
  // Opc proveedores
  gtk_grid_attach(GTK_GRID(m_grid), m_btn[2], 2, 5, 1, 1);
  gtk_grid_attach(GTK_GRID(m_grid), m_lbl[2], 0, 6, 5, 1);

  gtk_container_add(GTK_CONTAINER(m_win), m_grid);
  gtk_widget_show_all(m_win);
}

void pacientes(GtkWidget *widget, gpointer data) {
  init_listv("Gestión de Pacientes");
  mostrarPaci("../data/pacientes.dat");
  g_signal_connect(G_OBJECT(bar_btn[0]), "clicked", G_CALLBACK(gen_formpac),
                   NULL);
  gtk_widget_hide(m_win);
}

void medicamento(GtkWidget *widget, gpointer data) {
  init_listv("Gestión de Medicamentos");
  mostrarMed("../data/medicamentos.dat");
  g_signal_connect(G_OBJECT(bar_btn[0]), "clicked", G_CALLBACK(gen_formed),
                   NULL);
  gtk_widget_hide(m_win);
}

void proveedores(GtkWidget *widget, gpointer data) {
  init_listv("Gestión de Proveedores");
  mostrarProv("../data/proveedores.dat");
  g_signal_connect(G_OBJECT(bar_btn[0]), "clicked", G_CALLBACK(gen_formprov),
                   NULL);
  gtk_widget_hide(m_win);
}
