#include <gtk/gtk.h>
#include <unistd.h>

typedef struct ventana1 {
  GtkWidget *win;
  GtkWidget *grid;
} Ventana1;

typedef struct ventana2 {
  GtkWidget *win;
  GtkWidget *grid;
} Ventana2;

int main() {
  gtk_init(NULL, NULL);
  Ventana1 v1;
  v1.win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  v1.grid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(v1.win), v1.grid);

  gtk_widget_show(v1.win);

  gtk_widget_destroy(v1.grid);
  gtk_widget_destroy(v1.win);

  sleep(10);

  Ventana2 v2;
  v2.win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  v2.grid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(v2.win), v2.grid);

  gtk_widget_show(v2.win);

  gtk_widget_destroy(v2.grid);
  gtk_widget_destroy(v2.win);

  sleep(100);

  gtk_main();
}
