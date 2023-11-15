#include <gtk/gtk.h>
#include <pango/pangocairo.h>

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Ruta al archivo TTF local
    const char *fontFilePath = "/ruta/a/tu/archivo/Digital-7.ttf";

    // Crear un widget GtkLabel
    GtkWidget *label = gtk_label_new("Hora actual: 12:34:56");

    // Cargar la fuente desde el archivo TTF
    PangoFontDescription *font_desc = pango_font_description_from_string("Digital-7 16");
    PangoFontMap *fontmap = pango_cairo_font_map_new_for_font_type(CAIRO_FONT_TYPE_FT);
    
    // Configurar la fuente TTF local
    PangoFontFace *font_face = pango_cairo_font_map_create_context_for_family(PANGO_CAIRO_FONT_MAP(fontmap), pango_font_description_get_family(font_desc));

    // Aplicar la fuente al GtkLabel
    PangoLayout *layout = gtk_label_get_layout(GTK_LABEL(label));
    pango_layout_set_font_description(layout, font_desc);

    // Agregar el widget al contenedor de la ventana
    gtk_container_add(GTK_CONTAINER(window), label);

    // Mostrar todo y entrar en el bucle principal
    gtk_widget_show_all(window);
    gtk_main();

    // Liberar recursos después de su uso
    g_object_unref(font_face);
    pango_font_description_free(font_desc);

    return 0;
}
