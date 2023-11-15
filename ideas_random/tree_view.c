#include <gtk/gtk.h>

typedef struct {
  int dia;
  int mes;
  int anio;
} Fecha;

typedef struct {
  char nombre[50];
  char CURP[19];
  Fecha fechas;
  char sexo;
  char telf[11];
  char tpSangre[4];
  Fecha fechasC;
  int estado;
} Pacientes;

GtkWidget *scrollw, *tview, *win, *box;

void import_model(GtkListStore *model, unsigned short numCols,
                  char *titulos[]) {
  unsigned short i;
  tview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(model));

  // Crear, configurar columnas y agregar al treeview
  for (i = 0; i < numCols; i++) {
    GtkTreeViewColumn *column = gtk_tree_view_column_new();
    GtkCellRenderer *render = gtk_cell_renderer_text_new();
    gtk_tree_view_column_set_title(column, titulos[i]);
    gtk_tree_view_column_pack_start(column, render, TRUE);
    gtk_tree_view_column_add_attribute(column, render, "text", i);
    // Configurar el tamaño de las columnas
    gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_FIXED);
    // Ajustar propiedades para expandir
    gtk_tree_view_column_set_expand(column, TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tview), column);
  }

  // Crear la ventana scrolleable
  scrollw = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollw),
                                 GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  gtk_container_add(GTK_CONTAINER(scrollw), tview);
  gtk_box_pack_start(GTK_BOX(box), scrollw, TRUE, TRUE, 0);
}

int main() {
  gtk_init(NULL, NULL);
  Pacientes a = {"Juan",       "rsroads", {1, 2, 3}, 'M',
                 "7774286713", "A+",      {1, 2, 3}, 1};
  win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(win), 1280, 720);
  g_signal_connect(G_OBJECT(win), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);

  GtkListStore *list_store = gtk_list_store_new(
      7, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
      G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
  GtkTreeIter iter; // estructura para identificar fila en modelo
  long i = 0;
  char fechaFormato[2][12];
  sprintf(fechaFormato[0], "%02d/%02d/%04d", a.fechas.dia, a.fechas.mes, a.fechas.anio);
  sprintf(fechaFormato[1], "%02d/%02d/%04d", a.fechasC.dia, a.fechasC.mes, a.fechasC.anio);

  char sexo[2] = {a.sexo, '\0'};

  gtk_list_store_append(list_store, &iter); // agregar fila nueva
  gtk_list_store_set(list_store, &iter, 0, a.CURP, 1, a.nombre , 2, fechaFormato[0], 3, sexo,  4, a.telf, 5, a.tpSangre, 6, fechaFormato[1], -1);
  
  char *titulos[] = {"CURP", "Nombre",   "FechaN",   "Sexo",
                     "Telf", "TpSangre", "Primera C"};
  import_model(list_store, 7, titulos);

  gtk_container_add(GTK_CONTAINER(win), box);
  gtk_widget_show_all(win);
  gtk_main();
}
