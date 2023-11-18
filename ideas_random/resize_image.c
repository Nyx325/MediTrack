#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

GtkWidget *window;
GtkWidget *image_widget;
GdkPixbuf *originalImage;
GdkPixbuf *resizedImage = NULL;

// Function to resize the image
GdkPixbuf *resizeImage(GdkPixbuf *inputImage, int newWidth, int newHeight) {
    return gdk_pixbuf_scale_simple(inputImage, newWidth, newHeight, GDK_INTERP_BILINEAR);
}

// Callback to draw the image
gboolean drawImage(GtkWidget *widget, cairo_t *cr, gpointer data) {
    if (resizedImage != NULL) {
        gdk_cairo_set_source_pixbuf(cr, resizedImage, 0, 0);
        cairo_paint(cr);
    }

    return FALSE;
}

// Callback to handle window size changes
void onSizeAllocate(GtkWidget *widget, GdkRectangle *allocation, gpointer data) {
    // Get the new window size
    int newWidth = allocation->width;
    int newHeight = allocation->height;

    // Resize the image based on the new window size
    if (originalImage != NULL) {
        if (resizedImage != NULL) {
            g_object_unref(resizedImage); // Free the previous resized image
        }
        resizedImage = resizeImage(originalImage, newWidth, newHeight);
        gtk_widget_queue_draw(image_widget); // Redraw the image widget
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    image_widget = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), image_widget);

    // Load the original image
    originalImage = gdk_pixbuf_new_from_file("../images/banner.jpg", NULL);

    // Connect the drawImage callback
    g_signal_connect(G_OBJECT(image_widget), "draw", G_CALLBACK(drawImage), NULL);

    // Connect the size-allocate signal to handle window size changes
    g_signal_connect(G_OBJECT(window), "size-allocate", G_CALLBACK(onSizeAllocate), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    if (originalImage != NULL) {
        g_object_unref(originalImage); // Free the original image
    }
    if (resizedImage != NULL) {
        g_object_unref(resizedImage); // Free the resized image
    }

    return 0;
}
