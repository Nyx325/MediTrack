#include <gtk/gtk.h>

typedef struct wl_node {
  void *data;
  char desc[31];
  char id;
  struct wl_node *prev;
  struct wl_node *next;
} WlNode;

void add_wlnode(WlNode **list, void *data, char desc[30], char id) {
  WlNode *new = (WlNode *)malloc(sizeof(WlNode));
  if (new == NULL) {
    g_print("No se pudo asignar memoria\n");
    return;
  }

  new->data = data;
  strcpy(new->desc, desc);
  new->id = id;

  if (*list == NULL) {
    new->next = NULL;
    new->prev = NULL;
  } else {
    new->prev = *list;
    new->next = NULL;
    (*list)->next = new;
  }

  *list = new;
}

WlNode *find_node(char desc[11], char id, WlNode **list) {
  WlNode *recorrido = *list;

  if (*list == NULL || ((*list)->prev != NULL && (*list)->next != NULL))
    return NULL;

  if ((*list)->prev == NULL) {
    while (recorrido != NULL) {
      if (strcmp(recorrido->desc, desc) == 0 && recorrido->id == id)
        return recorrido;
      recorrido = recorrido->next;
    }
  } else if ((*list)->next == NULL) {
    while (recorrido != NULL) {
      if (strcmp(recorrido->desc, desc) == 0 && recorrido->id == id)
        return recorrido;
      recorrido = recorrido->prev;
    }
  }

  return NULL;
}

void a(GtkWidget *widget, gpointer data) {
  WlNode **list = (WlNode **)data;
  WlNode *recorrido = *list, *tmp;
  WlNode *win = find_node("win", -1, list);

  gtk_widget_hide (GTK_WIDGET(win->data));
  
  while (recorrido != NULL) {
    tmp = recorrido; // Mover esta línea al comienzo del bucle

    if (GTK_IS_WIDGET(recorrido->data)) {
      gtk_widget_destroy(GTK_WIDGET(recorrido->data));
    } else if (GDK_IS_PIXBUF(recorrido->data)) {
      g_object_unref(GDK_PIXBUF(recorrido->data));
    }

    recorrido = recorrido->next;

    free(tmp); // Mover esta línea al final del bucle
  }
}

int main() {
  gtk_init(NULL, NULL);
  WlNode *list = NULL;
  GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  GtkWidget *btn = gtk_button_new_with_label("Clickea");
  GdkPixbuf *icon =
      gdk_pixbuf_new_from_file("/ruta/completa/al/icono.png", NULL);

  g_signal_connect(G_OBJECT(btn), "clicked", G_CALLBACK(a), &list);

  gtk_container_add(GTK_CONTAINER(win), btn);

  add_wlnode(&list, win, "win", -1);
  add_wlnode(&list, icon, "icon", -1);

  gtk_widget_show_all(win);
  gtk_main();
}
