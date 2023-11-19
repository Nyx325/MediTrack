#include "form_prov.h"
#include "general.h"
#include "listv.h"
#include <stdio.h>

GtkWidget *p_win, *p_grid, *p_entry[9], *p_lbl[10], *p_combox[2], *p_btn[2],
    *p_checkbtn;
GdkPixbuf *p_icon;

// Elimina y libera memoria de todos los objetos
// de la ventana del formulario de proveedores
void free_formprov() {
  short i;
  gtk_widget_hide(p_win);
  // Si el apuntador != NULL, liberar
  if (p_icon) {
    g_object_unref(p_icon);
    p_icon = NULL;
  }
  for (i = 0; i < 9; i++) {
    if (p_entry[i]) {
      gtk_widget_destroy(p_entry[i]);
      p_entry[i] = NULL;
    }
  }
  for (i = 0; i < 10; i++) {
    if (p_lbl[i]) {
      gtk_widget_destroy(p_lbl[i]);
      p_lbl[i] = NULL;
    }
  }
  for (i = 0; i < 2; i++) {
    if (p_combox[i]) {
      gtk_widget_destroy(p_combox[i]);
      p_combox[i] = NULL;
    }
  }
  for (i = 0; i < 2; i++) {
    if (p_btn[i]) {
      gtk_widget_destroy(p_btn[i]);
      p_btn[i] = NULL;
    }
  }
  if (p_checkbtn) {
    gtk_widget_destroy(p_checkbtn);
    p_checkbtn = NULL;
  }
  if (p_grid) {
    gtk_widget_destroy(p_win);
    p_win = NULL;
  }
  if (p_win) {
    gtk_widget_destroy(p_win);
    p_win = NULL;
  }
}

void p_wingrid() {
  // Crear ventana
  p_win = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  // Configurar tamaño, posición, padding y envento de cerrado
  //  gtk_window_set_title(GTK_WINDOW(p_win), "Iniciar sesion");
  gtk_window_set_default_size(GTK_WINDOW(p_win), 611, 220);
  gtk_window_set_position(GTK_WINDOW(p_win), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(p_win), 20);
  g_signal_connect(G_OBJECT(p_win), "destroy", G_CALLBACK(free_formprov), NULL);

  // Crear grid principal
  p_grid = gtk_grid_new();

  // padding del margen del grid
  gtk_grid_set_row_spacing(GTK_GRID(p_grid), 20);    // Espaciado vertical
  gtk_grid_set_column_spacing(GTK_GRID(p_grid), 10); // Espaciado horizontal
  gtk_container_add(GTK_CONTAINER(p_win), p_grid);
  gtk_widget_set_halign(p_grid, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(p_grid, GTK_ALIGN_CENTER);

  // Generar icono
  p_icon = gdk_pixbuf_new_from_file("../images/icon.png", NULL);
  gtk_window_set_icon(GTK_WINDOW(p_win), p_icon);
}

// Crear los apuntadores a los label y les coloca el texto
void p_init_lbl() {
  short i;
  char *titulos[] = {"Nombre comercial",
                     "Nombre de factura",
                     "RFC",
                     "Núm. oficina",
                     "Whatsapp",
                     "Correo",
                     "Representante Comercial",
                     "Vigencia",
                     " ",
                     "Domicilio"};

  for (i = 0; i < 10; i++)
    p_lbl[i] = gtk_label_new(titulos[i]);
}

void p_init_entry() {
  short i;

  for (i = 0; i < 9; i++)
    p_entry[i] = gtk_entry_new();

  // Colocar texto "Año" al entry de fecha
  gtk_entry_set_placeholder_text(GTK_ENTRY(p_entry[7]), "Año");
}

void p_init_combox() {
  short j;

  for (j = 0; j < 2; j++)
    p_combox[j] = gtk_combo_box_text_new();

  // Hacer que el contenido de la box de dias dependa del mes elegido
  g_signal_connect(p_combox[0], "changed", G_CALLBACK(cambio_mes), p_combox[1]);

  // Agregar la opción "Mes"
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(p_combox[0]), "Mes");

  // Llenar el ComboBox con números del 1 al 12
  for (j = 1; j <= 12; j++) {
    char buffer[3];
    snprintf(buffer, sizeof(buffer), "%d", j);
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(p_combox[0]), buffer);
  }

  // Ahora, establecer "Mes" como el valor predeterminado después de llenar
  gtk_combo_box_set_active(GTK_COMBO_BOX(p_combox[0]), 0);
}

void p_init_btn() {
  GtkStyleContext *context;
  short i;
  char *titulos[] = {"Aceptar", "Cancelar"};
  void (*callbacks[2])(GtkWidget *, gpointer) = {prov_aceptar, free_formprov};

  for (i = 0; i < 2; i++) {
    p_btn[i] = gtk_button_new_with_label(titulos[i]);
    // Agregar nombre de objeto en el CSS
    gtk_widget_set_name(p_btn[i], "button");
    // Agregar clase
    context = gtk_widget_get_style_context(p_btn[i]);
    gtk_style_context_add_class(context, "suggested-action");
    g_signal_connect(G_OBJECT(p_btn[i]), "clicked", G_CALLBACK(callbacks[i]),
                     NULL);
  }
}

void p_init_checkbtn() {
  p_checkbtn =
      gtk_check_button_new_with_label("Permiso de venta\nde narcóticos");
}

void p_set_widgets() {
  // Nombre comercial
  gtk_grid_attach(GTK_GRID(p_grid), p_lbl[0], 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(p_grid), p_entry[0], 1, 0, 4, 1);
  gtk_entry_set_max_length(GTK_ENTRY(p_entry[0]), 100);
  gtk_entry_set_width_chars(GTK_ENTRY(p_entry[0]), 30);

  // Nombre Factura
  gtk_grid_attach(GTK_GRID(p_grid), p_lbl[1], 0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(p_grid), p_entry[1], 1, 1, 4, 1);
  gtk_entry_set_max_length(GTK_ENTRY(p_entry[1]), 100);
  gtk_entry_set_width_chars(GTK_ENTRY(p_entry[1]), 30);

  // RFC
  gtk_grid_attach(GTK_GRID(p_grid), p_lbl[2], 0, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(p_grid), p_entry[2], 1, 2, 1, 1);
  gtk_entry_set_max_length(GTK_ENTRY(p_entry[2]), 13);
  gtk_entry_set_width_chars(GTK_ENTRY(p_entry[2]), 13);

  // Número de oficina
  gtk_grid_attach(GTK_GRID(p_grid), p_lbl[3], 2, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(p_grid), p_entry[3], 3, 3, 2, 1);
  gtk_entry_set_max_length(GTK_ENTRY(p_entry[3]), 10);
  gtk_entry_set_width_chars(GTK_ENTRY(p_entry[3]), 10);

  // Whatsapp
  gtk_grid_attach(GTK_GRID(p_grid), p_lbl[4], 0, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(p_grid), p_entry[4], 1, 3, 1, 1);
  gtk_entry_set_max_length(GTK_ENTRY(p_entry[4]), 10);
  gtk_entry_set_width_chars(GTK_ENTRY(p_entry[4]), 10);

  // Correo
  gtk_grid_attach(GTK_GRID(p_grid), p_lbl[5], 2, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(p_grid), p_entry[5], 3, 2, 2, 1);
  // gtk_entry_set_max_length(GTK_ENTRY(p_entry[4]), 30);
  gtk_entry_set_width_chars(GTK_ENTRY(p_entry[5]), 20);

  // Representante comercial
  gtk_grid_attach(GTK_GRID(p_grid), p_lbl[6], 0, 4, 1, 1);
  gtk_grid_attach(GTK_GRID(p_grid), p_entry[6], 1, 4, 4, 1);
  gtk_entry_set_max_length(GTK_ENTRY(p_entry[6]), 30);
  gtk_entry_set_width_chars(GTK_ENTRY(p_entry[6]), 30);

  // Domicilio
  gtk_grid_attach(GTK_GRID(p_grid), p_lbl[9], 0, 5, 1, 1);
  gtk_grid_attach(GTK_GRID(p_grid), p_entry[8], 1, 5, 4, 1);
  gtk_entry_set_max_length(GTK_ENTRY(p_entry[8]), 30);
  gtk_entry_set_width_chars(GTK_ENTRY(p_entry[8]), 30);

  // Permiso venta narcóticos
  gtk_grid_attach(GTK_GRID(p_grid), p_checkbtn, 0, 6, 1, 1);

  // Vigencia
  gtk_grid_attach(GTK_GRID(p_grid), p_lbl[7], 1, 6, 1, 1);
  gtk_grid_attach(GTK_GRID(p_grid), p_entry[7], 2, 6, 1, 1);
  gtk_grid_attach(GTK_GRID(p_grid), p_combox[0], 3, 6, 1, 1);
  gtk_grid_attach(GTK_GRID(p_grid), p_combox[1], 4, 6, 1, 1);
  gtk_entry_set_width_chars(GTK_ENTRY(p_entry[7]), 4);

  // Warning
  gtk_grid_attach(GTK_GRID(p_grid), p_lbl[8], 0, 7, 5, 1);

  // Botones
  gtk_grid_attach(GTK_GRID(p_grid), p_btn[0], 0, 8, 2, 1);
  gtk_grid_attach(GTK_GRID(p_grid), p_btn[1], 2, 8, 3, 1);
}

void gen_formprov() {
  // Generar ventana
  p_wingrid();
  // Incializar widgets
  p_init_lbl();
  p_init_entry();
  p_init_checkbtn();
  p_init_combox();
  p_init_btn();
  // Distribuir en la ventana
  p_set_widgets();

  gtk_widget_show_all(p_win);
}

void agregarProveedor(char *dirArchivo, Proveedor proveedor) {
  FILE *apArch = fopen(dirArchivo, "ab");
  if (apArch == NULL) {
    g_print("Archivo dañado");
    return;
  }
  fwrite(&proveedor, sizeof(Proveedor), 1, apArch);
  fclose(apArch);
}

char *formatear_rfc(const gchar *input) {
  char *formateo = g_strdup(input);
  unsigned int i, max_letras;
  const gchar tam = g_utf8_strlen(input, -1);

  if (tam != 12 && tam != 13) {
    g_free(formateo);
    return NULL;
  }

  // Si persona física
  if (tam == 13) {
    // Verificar caracteres de nombre
    for (i = 0; i < 4; i++) {
      if (!isalpha(formateo[i])) {
        g_free(formateo);
        return NULL;
      }

      formateo[i] = toupper(formateo[i]);
    }

    // Verificar caracteres de nombre
    for (i = 4; i < 8; i++) {
      if (!isdigit(formateo[i])) {
        g_free(formateo);
        return NULL;
      }
    }

    // Validar homoclave
    for (i = 8; i < 13; i++) {
      if (isalpha(formateo[i]))
        formateo[i] = toupper(formateo[i]);
    }
  }
  // Si persona moral
  else {
    // Validar denominación
    for (i = 0; i < 3; i++) {
      if (!isalpha(formateo[i])) {
        g_free(formateo);
        return NULL;
      }

      formateo[i] = toupper(formateo[i]);
    }

    // Validar fecha de creación
    for (i = 3; i < 9; i++) {
      if (!isdigit(formateo[i])) {
        g_free(formateo);
        return NULL;
      }
    }

    // Validar homoclave
    for (i = 9; i < 12; i++) {
      if (isalpha(formateo[i]))
        formateo[i] = toupper(formateo[i]);
    }
  }

  return formateo;
}

void prov_aceptar(GtkWidget *Wid, gpointer data) {
  short i;
  char *output[8];
  Proveedor registroP;
  const gchar *input[9];
  GString *err = g_string_new("");

  registroP.estado = 0;
  registroP.vigencia.dia = 0;
  registroP.vigencia.mes = 0;
  registroP.vigencia.anio = 0;

  // Nombre comercial
  input[0] = gtk_entry_get_text(GTK_ENTRY(p_entry[0]));
  output[6] = g_strdup(input[0]);
  if (g_utf8_strlen(input[0], -1) > 0)
    strcpy(registroP.nombreComercial, output[6]);
  else
    agregar_err("Nombre comercial", &err);

  // Nombre factura
  input[1] = gtk_entry_get_text(GTK_ENTRY(p_entry[1]));
  output[7] = g_strdup(input[0]);
  if (g_utf8_strlen(input[1], -1) > 0)
    strcpy(registroP.nombreFactura, output[7]);
  else
    agregar_err("Nombre de factura", &err);

  // RFC
  input[2] = gtk_entry_get_text(GTK_ENTRY(p_entry[2]));
  output[0] = formatear_rfc(input[2]);
  g_print("%s\n", input[2]);
  g_print("%s\n", output[0]);
  if (output[0])
    strcpy(registroP.rfc, input[2]);
  else
    agregar_err("RFC", &err);

  // Correo
  input[3] = gtk_entry_get_text(GTK_ENTRY(p_entry[5]));
  output[1] = g_strdup(input[3]);
  if (strstr(output[1], "@") && strlen(output[1]) > 4) {
    strcpy(registroP.correoElectronico, output[1]);
  } else
    agregar_err("Correo", &err);

  // Validar whatsapp y num de oficina
  char *titulosErr[2] = {"Num de oficina", "Whatsapp"};
  for (i = 4; i < 6; i++) {
    input[i] = gtk_entry_get_text(GTK_ENTRY(p_entry[i - 1]));
    output[i - 2] = g_strdup(input[i]);
    if (is_full_nums(input[i], 10, 10) || strlen(output[i - 2]) == 0) {
      if (i == 4)
        strcpy(registroP.numeroOficina, output[i - 2]);
      else
        strcpy(registroP.whatsappEmpresarial, output[i - 2]);
    } else
      agregar_err(titulosErr[i - 4], &err);
  }

  // Representante Comercial
  input[6] = gtk_entry_get_text(GTK_ENTRY(p_entry[6]));
  output[4] = formatear_nombre(input[6]);
  if (output[4] || g_utf8_strlen(input[6], -1) == 0)
    if (output[4] == NULL)
      registroP.representanteComercial[0] = '\0';
    else
      strcpy(registroP.representanteComercial, output[4]);
  else
    agregar_err("Representante comercial", &err);

  // Domicilio
  input[7] = gtk_entry_get_text(GTK_ENTRY(p_entry[8]));
  output[5] = g_strdup(input[7]);
  if (g_utf8_strlen(input[7], -1) != 0)
    strcpy(registroP.domicilio, output[5]);
  else
    agregar_err("Domicilio", &err);

  // Permiso de venta de narcóticos
  registroP.permisoNarcoticos =
      gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(p_checkbtn));

  if (registroP.permisoNarcoticos == 1) {
    // Año
    input[7] = gtk_entry_get_text(GTK_ENTRY(p_entry[7]));
    if (is_full_nums(input[7], -1, 1) == FALSE)
      agregar_err("Año de vigencia", &err);
    else
      registroP.vigencia.anio = atoi(input[7]);

    // Mes
    registroP.vigencia.mes =
        gtk_combo_box_get_active(GTK_COMBO_BOX(p_combox[0]));
    if (registroP.vigencia.mes == 0)
      agregar_err("Mes de vigencia", &err);

    // Obtener dia
    registroP.vigencia.dia =
        gtk_combo_box_get_active(GTK_COMBO_BOX(p_combox[1]));
    if (registroP.vigencia.dia == 0)
      agregar_err("Dia de vigencia", &err);
  }

  if (err->len != 0)
    agregar_err("no valido(s)", &err);

  if (strlen(registroP.numeroOficina) == 0 &&
      strlen(registroP.whatsappEmpresarial) == 0) {
    agregar_err("\nSe necesita al menos un número de contacto", &err);
  } else if (err->len == 0) {
    registroP.estado = 1;
    agregarProveedor("../data/proveedores.dat", registroP);
    free_formprov();
    gtk_list_store_clear(lv_lstore);
    mostrarProv("../data/proveedores.dat");
  }
  gtk_label_set_text(GTK_LABEL(p_lbl[8]), err->str);

  for (i = 0; i < 6; i++)
    if (output[i])
      g_free(output[i]);
}

void mostrarProv(char *archivoDir) {
  unsigned long pos;
  char fechaFormato[13];
  GtkTreeIter iter; // Fila del modelo

  // Apuntador definido en listv.c para modelo de tabla
  lv_lstore = gtk_list_store_new(11, G_TYPE_STRING, G_TYPE_STRING,
                                 G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                                 G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                                 G_TYPE_BOOLEAN, G_TYPE_STRING, G_TYPE_ULONG);

  FILE *apProv;
  Proveedor prov;
  ushort a;

  apProv = fopen(archivoDir, "a+b");
  if (apProv == NULL) {
    g_print("Archivo dañado\n");
    return;
  }

  while (fread(&prov, sizeof(Proveedor), 1, apProv)) {
    if (prov.estado == 1) {
      // Crear cadena para fecha
      sprintf(fechaFormato, "%02d/%02d/%04d", prov.vigencia.dia,
              prov.vigencia.mes, prov.vigencia.anio);

      // Obtener posición en archivo
      pos = (unsigned long)ftell(apProv) - sizeof(Proveedor);

      gtk_list_store_append(lv_lstore, &iter); // Fila nueva
      gtk_list_store_set(lv_lstore, &iter, 0, prov.rfc, 1, prov.nombreComercial,
                         2, prov.nombreFactura, 3, prov.correoElectronico, 4,
                         prov.numeroOficina, 5, prov.whatsappEmpresarial, 6,
                         prov.domicilio, 7, prov.representanteComercial, 8,
                         prov.permisoNarcoticos, 9, fechaFormato, 10, pos, -1);
    }
  }
  fclose(apProv);
  char *titulos[] = {"RFC",
                     "Nombre Comercial",
                     "Nombre Factura",
                     "Correo",
                     "Num. Oficina",
                     "Num. Whatsapp",
                     "Domicilio",
                     "Representante Comercial",
                     "Venta de narcóticos",
                     "Vigencia Permiso"};

  lv_importmodel(10, titulos);
}
