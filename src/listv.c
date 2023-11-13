#include "listv.h"

GtkWidget *lv_scrollw, *lv_tview, *lv_win, *lv_swin, *lv_grid;
GdkPixbuf *lv_icon;

void import_model(GtkListStore *list_store, char *titulosColum[],
                  short n_colum) {
  short i;
  lv_tview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(list_store));

  // Generar columnas
  for (i = 0; i < n_colum; i++) {
    GtkTreeViewColumn *col = gtk_tree_view_column_new();
    GtkCellRenderer *rend = gtk_cell_renderer_text_new();
    gtk_tree_view_column_set_title(col, titulosColum[i]);
    gtk_tree_view_column_pack_start(col, rend, TRUE);
    gtk_tree_view_column_add_attribute(col, rend, "text", i);
    gtk_tree_view_append_column(GTK_TREE_VIEW(lv_tview), col);
  }

  // Configurar el tamaño de las columnas para que se expandan
  gtk_tree_view_columns_autosize(GTK_TREE_VIEW(lv_tview));

  // Establecer política de tamaño de las columnas
  gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(lv_tview), FALSE);

  // Configurar scrolled window
  lv_scrollw = gtk_scrolled_window_new(NULL, NULL);
  //gtk_container_add(GTK_CONTAINER(lv_scrollw), lv_tview);

  // Crear barra de busqueda (listv_bar.c)

  gtk_grid_attach(GTK_GRID(lv_grid), lv_scrollw, 0, 1, 1, 1);
}

void gen_listv() {
  lv_win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  // Configurar tamaño, posición, padding y envento de cerrado
  //  gtk_window_set_title(GTK_WINDOW(p_win), "Iniciar sesion");
  gtk_window_set_default_size(GTK_WINDOW(lv_win), 611, 220);
  gtk_window_set_position(GTK_WINDOW(lv_win), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(lv_win), 0);
  // g_signal_connect(G_OBJECT(lv_win), "destroy", G_CALLBACK(free_formcons),
  // NULL);

  lv_grid = gtk_grid_new();

  // padding del margen del grid
  gtk_grid_set_row_spacing(GTK_GRID(lv_grid), 20);    // Espaciado vertical
  gtk_grid_set_column_spacing(GTK_GRID(lv_grid), 0); // Espaciado horizontal
  gtk_container_add(GTK_CONTAINER(lv_win), lv_grid);
  gtk_widget_set_halign(lv_grid, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(lv_grid, GTK_ALIGN_CENTER);

  // Generar icono
  lv_icon = gdk_pixbuf_new_from_file("../images/icon.png", NULL);
  gtk_window_set_icon(GTK_WINDOW(lv_win), lv_icon);

  gen_bar();
  gtk_grid_attach(GTK_GRID(lv_grid), bar_box, 0, 0, 1, 1);

  gtk_widget_show_all(lv_win);
}

enum cols {
  CURP,   // CURP = 0
  Nombre, // Nombre = 1
  FechaN, // FechaN = 2
  Sexo,   // Sexo = 3
  NumT,   // NumT = 4
  TipoS,  // TipoS = 5
  Fecha1C // Fecha1C = 6
};

void prueba() {
  // Info de columnas

  char *titulosCol[] = {"CURP",  "Nombre", "Fecha N",        "Sexo",
                        "Num T", "Tipo S", "Primer consulta"};
  GtkListStore *list_store = gtk_list_store_new(
      7, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
      G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
  GtkTreeIter iter; // estructura para identificar fila en modelo
  int i;
  // Llenar modelo
  for (i = 0; i < 20; i++) {
    gtk_list_store_append(list_store, &iter); // agregar fila nueva
    gtk_list_store_set(list_store, &iter, CURP, "RSRO121212qeqe", Nombre,
                       "Juan", FechaN, "2/3/2023", Sexo, "M", NumT, "a", TipoS,
                       "A+", Fecha1C, "2/3/2020", -1);
  }

  import_model(list_store, titulosCol, 7);
  gen_listv();
}
