#include "form_prov.h"
#include "general.h"

typedef struct {
  BaseForm baseVentana;
  EntradaTexto nomComercial;
  EntradaTexto nomFactura;
  EntradaTexto rfc;
  EntradaTexto numOficina;
  EntradaTexto wsp;
  EntradaTexto correo;
  EntradaTexto repComercial;
  EntradaTexto domicilio;
  GtkWidget *narcoticosCheckBtn;
  EntradaFecha vigenciaPersmiso;
  GtkWidget *warningLbl;
  GtkWidget *aceptBtn;
  GtkWidget *cancelBtn;
} FormProv;

FormProv prForm;

void free_provform(GtkWidget *widget, gpointer data) {
  gtk_widget_hide(prForm.baseVentana.win);

  if (prForm.narcoticosCheckBtn)
    gtk_widget_destroy(prForm.narcoticosCheckBtn);
  if (prForm.warningLbl)
    gtk_widget_destroy(prForm.warningLbl);
  if (prForm.aceptBtn)
    gtk_widget_destroy(prForm.aceptBtn);
  if (prForm.cancelBtn)
    gtk_widget_destroy(prForm.cancelBtn);

  free_entradatexto(&prForm.nomComercial);
  free_entradatexto(&prForm.nomFactura);
  free_entradatexto(&prForm.rfc);
  free_entradatexto(&prForm.numOficina);
  free_entradatexto(&prForm.wsp);
  free_entradatexto(&prForm.correo);
  free_entradatexto(&prForm.repComercial);
  free_entradatexto(&prForm.domicilio);

  free_entradafecha(&prForm.vigenciaPersmiso);

  free_baseform(&prForm.baseVentana);

  prForm.narcoticosCheckBtn = NULL;
  prForm.warningLbl = NULL;
  prForm.aceptBtn = NULL;
  prForm.cancelBtn = NULL;
}

void cargar_proveedor_registro() {
  long posArch;
  char anioPermiso[5];
  Proveedor registro;
  GtkTreeModel *model;
  GtkTreeIter iter;
  FILE *apArch;

  if (gtk_tree_selection_get_selected(tabla.filaActual, &model, &iter) ==
      FALSE) {
    free_provform(NULL, NULL);
    return;
  }

  gtk_tree_model_get(model, &iter, 10, &posArch, -1);
  apArch = fopen("../data/proveedores.dat", "rb");
  if (apArch == NULL) {
    g_print("ERROR: Archivo dañado");
    return;
  }
  fseek(apArch, posArch, SEEK_SET);
  fread(&registro, sizeof(Proveedor), 1, apArch);
  fclose(apArch);

  gtk_entry_set_text(GTK_ENTRY(prForm.nomComercial.entry),
                     registro.nombreComercial);
  gtk_entry_set_text(GTK_ENTRY(prForm.nomFactura.entry),
                     registro.nombreFactura);
  gtk_entry_set_text(GTK_ENTRY(prForm.rfc.entry), registro.rfc);
  gtk_entry_set_text(GTK_ENTRY(prForm.domicilio.entry), registro.domicilio);
  gtk_entry_set_text(GTK_ENTRY(prForm.numOficina.entry),
                     registro.numeroOficina);
  gtk_entry_set_text(GTK_ENTRY(prForm.wsp.entry), registro.whatsappEmpresarial);
  gtk_entry_set_text(GTK_ENTRY(prForm.correo.entry),
                     registro.correoElectronico);
  gtk_entry_set_text(GTK_ENTRY(prForm.repComercial.entry),
                     registro.representanteComercial);

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(prForm.narcoticosCheckBtn),
                               registro.permisoNarcoticos);

  sprintf(anioPermiso, "%d", registro.vigencia.anio);
  gtk_entry_set_text(GTK_ENTRY(prForm.vigenciaPersmiso.anioEntry), anioPermiso);
  gtk_combo_box_set_active(GTK_COMBO_BOX(prForm.vigenciaPersmiso.mesCombox),
                           registro.vigencia.mes);
  gtk_combo_box_set_active(GTK_COMBO_BOX(prForm.vigenciaPersmiso.diaCombox),
                           registro.vigencia.dia);
}

void prov_crear_form(Opc modo) {
  crear_ventana(&prForm.baseVentana, 611, 220, free_provform);

  crear_entradatexto(&prForm.nomComercial, "Nombre Comercial", 30, 100);
  crear_entradatexto(&prForm.nomFactura, "Nombre Factura", 30, 100);
  crear_entradatexto(&prForm.rfc, "RFC", 13, 13);
  crear_entradatexto(&prForm.numOficina, "Num. Oficina", 10, 10);
  crear_entradatexto(&prForm.wsp, "Whatsapp", 10, 10);
  crear_entradatexto(&prForm.correo, "Correo", 20, 100);
  crear_entradatexto(&prForm.repComercial, "Representante Comercial", 30, 30);
  crear_entradatexto(&prForm.domicilio, "Domicilio", 30, 99);

  crear_entradafecha(&prForm.vigenciaPersmiso, "Vigencia");

  prForm.warningLbl = gtk_label_new("");

  crear_boton(&prForm.aceptBtn, "Aceptar", NULL);
  crear_boton(&prForm.cancelBtn, "Cancelar", free_provform);

  prForm.narcoticosCheckBtn =
      gtk_check_button_new_with_label("Permiso de venta\nde narcóticos");

  gtk_grid_attach(GTK_GRID(prForm.baseVentana.grid), prForm.nomComercial.lbl, 0,
                  0, 1, 1);
  gtk_grid_attach(GTK_GRID(prForm.baseVentana.grid), prForm.nomComercial.entry,
                  1, 0, 4, 1);

  gtk_grid_attach(GTK_GRID(prForm.baseVentana.grid), prForm.nomFactura.lbl, 0,
                  1, 1, 1);
  gtk_grid_attach(GTK_GRID(prForm.baseVentana.grid), prForm.nomFactura.entry, 1,
                  1, 4, 1);

  gtk_grid_attach(GTK_GRID(prForm.baseVentana.grid), prForm.rfc.lbl, 0, 2, 1,
                  1);
  gtk_grid_attach(GTK_GRID(prForm.baseVentana.grid), prForm.rfc.entry, 1, 2, 1,
                  1);

  gtk_grid_attach(GTK_GRID(prForm.baseVentana.grid), prForm.numOficina.lbl, 2,
                  3, 1, 1);
  gtk_grid_attach(GTK_GRID(prForm.baseVentana.grid), prForm.numOficina.entry, 3,
                  3, 2, 1);

  gtk_grid_attach(GTK_GRID(prForm.baseVentana.grid), prForm.wsp.lbl, 0, 3, 1,
                  1);
  gtk_grid_attach(GTK_GRID(prForm.baseVentana.grid), prForm.wsp.entry, 1, 3, 1,
                  1);

  gtk_grid_attach(GTK_GRID(prForm.baseVentana.grid), prForm.correo.lbl, 2, 2, 1,
                  1);
  gtk_grid_attach(GTK_GRID(prForm.baseVentana.grid), prForm.correo.entry, 3, 2,
                  2, 1);

  gtk_grid_attach(GTK_GRID(prForm.baseVentana.grid), prForm.repComercial.lbl, 0,
                  4, 1, 1);
  gtk_grid_attach(GTK_GRID(prForm.baseVentana.grid), prForm.repComercial.entry,
                  1, 4, 4, 1);

  gtk_grid_attach(GTK_GRID(prForm.baseVentana.grid), prForm.domicilio.lbl, 0, 5,
                  1, 1);
  gtk_grid_attach(GTK_GRID(prForm.baseVentana.grid), prForm.domicilio.entry, 1,
                  5, 4, 1);

  gtk_grid_attach(GTK_GRID(prForm.baseVentana.grid), prForm.narcoticosCheckBtn,
                  0, 6, 1, 1);

  gtk_grid_attach(GTK_GRID(prForm.baseVentana.grid),
                  prForm.vigenciaPersmiso.titulo, 1, 6, 1, 1);
  gtk_grid_attach(GTK_GRID(prForm.baseVentana.grid),
                  prForm.vigenciaPersmiso.anioEntry, 2, 6, 1, 1);
  gtk_grid_attach(GTK_GRID(prForm.baseVentana.grid),
                  prForm.vigenciaPersmiso.mesCombox, 3, 6, 1, 1);
  gtk_grid_attach(GTK_GRID(prForm.baseVentana.grid),
                  prForm.vigenciaPersmiso.diaCombox, 4, 6, 1, 1);

  gtk_grid_attach(GTK_GRID(prForm.baseVentana.grid), prForm.warningLbl, 0, 7, 5,
                  1);

  gtk_grid_attach(GTK_GRID(prForm.baseVentana.grid), prForm.aceptBtn, 0, 8, 2,
                  1);
  gtk_grid_attach(GTK_GRID(prForm.baseVentana.grid), prForm.cancelBtn, 2, 8, 3,
                  1);

  if (modo)
    cargar_proveedor_registro();

  gtk_widget_show_all(prForm.baseVentana.win);
}

void mostrar_proveedores(char *archivoDir) {
  long pos;
  char fechaFormato[13];
  GtkTreeIter iter; // Fila del modelo

  // Apuntador definido en listv.c para modelo de tabla
  tabla.listStore = gtk_list_store_new(
      11, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
      G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
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
      pos = ftell(apProv) - sizeof(Proveedor);

      gtk_list_store_append(tabla.listStore, &iter); // Fila nueva
      gtk_list_store_set(tabla.listStore, &iter, 0, prov.rfc, 1,
                         prov.nombreComercial, 2, prov.nombreFactura, 3,
                         prov.correoElectronico, 4, prov.numeroOficina, 5,
                         prov.whatsappEmpresarial, 6, prov.domicilio, 7,
                         prov.representanteComercial, 8, prov.permisoNarcoticos,
                         9, fechaFormato, 10, pos, -1);
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

  listview_importmodel(&tabla, 10, titulos);
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

char *formatear_correo(const gchar *input) {
  char *output = g_strdup(input);
  if (strstr(output, "@") && strlen(output) > 6) {
    return output;
  } else
    return NULL;
}

typedef struct {
  TextoIngresado nomComercial;
  TextoIngresado nomFactura;
  TextoIngresado rfc;
  TextoIngresado correo;
  TextoIngresado wsp;
  TextoIngresado numOficina;
  TextoIngresado representante;
  TextoIngresado domicilio;
  FechaIngresada vigenciaPermiso;
} DatosFormularioProveedor;

Proveedor validar_formulario_proveedor() {
  GString *err = g_string_new("");
  Proveedor registro;
  DatosFormularioProveedor cap;
  WidgetsFecha widFecha;

  registro.estado = 0;

  capturar_formatear_texto(&cap.nomComercial, registro.nombreComercial,
                           formatear_palabra, prForm.nomComercial.entry, &err,
                           "Nombre comercial");
  capturar_formatear_texto(&cap.nomFactura, registro.nombreFactura,
                           formatear_nombre, prForm.nomFactura.entry, &err,
                           "Nombre factura");
  capturar_formatear_texto(&cap.rfc, registro.rfc, formatear_rfc,
                           prForm.rfc.entry, &err, "RFC");
  capturar_formatear_texto(&cap.domicilio, registro.domicilio,
                           formatear_palabra, prForm.domicilio.entry, &err,
                           "Domicilio");
  capturar_formatear_texto(&cap.numOficina, registro.numeroOficina,
                           formatear_telf, prForm.numOficina.entry, &err,
                           "Num. Oficina");
  capturar_formatear_texto(&cap.wsp, registro.whatsappEmpresarial,
                           formatear_telf, prForm.wsp.entry, &err, "Whatsapp");
  capturar_formatear_texto(&cap.correo, registro.correoElectronico,
                           formatear_correo, prForm.correo.entry, &err,
                           "Correo");
  capturar_formatear_texto(&cap.representante, registro.representanteComercial,
                           formatear_nombre, prForm.repComercial.entry, &err,
                           "Representante");
  registro.permisoNarcoticos = gtk_toggle_button_get_active(
      GTK_TOGGLE_BUTTON(prForm.narcoticosCheckBtn));

  if (registro.permisoNarcoticos == 0) {
    registro.vigencia.dia = 0;
    registro.vigencia.mes = 0;
    registro.vigencia.anio = 0;
  } else {

    widFecha.anioEntry = GTK_ENTRY(prForm.vigenciaPersmiso.anioEntry);
    widFecha.mesCombox = GTK_COMBO_BOX(prForm.vigenciaPersmiso.mesCombox);
    widFecha.diaCombox = GTK_COMBO_BOX(prForm.vigenciaPersmiso.diaCombox);
    capturar_formatear_fecha(&cap.vigenciaPermiso, &widFecha,
                             &registro.vigencia, &err, "Vigencia");
  }

  if (err->len != 0) {
    g_string_append(err, " no válido(s)");
    gtk_label_set_markup(GTK_LABEL(prForm.warningLbl), err->str);
  } else
    registro.estado = 1;

  return registro;
}

gboolean registrar_datos_proveedor(GtkWidget *btn, gpointer data) {
  FILE *apArch;
  Proveedor registro = validar_formulario_proveedor();

  if (registro.estado == 0)
    return FALSE;

  free_provform(NULL, NULL);

  apArch = fopen("../data/proveedores.dat", "ab");
  if (apArch == NULL) {
    g_print("ERROR: Archivo dañado");
    return FALSE;
  }

  fwrite(&registro, sizeof(Proveedor), 1, apArch);
  fclose(apArch);

  gtk_list_store_clear(tabla.listStore);
  mostrar_proveedores("../data/proveedores.dat");

  return TRUE;
}

void agregar_proveedor_callback(GtkWidget *btn, gpointer data) {
  desconectar_señal_btn(&prForm.aceptBtn);
  prov_crear_form(0);
  gtk_window_set_title(GTK_WINDOW(prForm.baseVentana.win), "Agregar Proveedor");
  g_signal_connect(G_OBJECT(prForm.aceptBtn), "clicked",
                   G_CALLBACK(registrar_datos_proveedor), NULL);
}

gboolean modificar_datos_proveedor(GtkWidget *btn, gpointer data) {
  long pos;
  FILE *apArch;
  Proveedor registro = validar_formulario_proveedor();
  GtkTreeModel *modelo;
  GtkTreeIter iter;

  if (registro.estado == 0)
    return FALSE;

  free_provform(NULL, NULL);

  gtk_tree_selection_get_selected(tabla.filaActual, &modelo, &iter);
  gtk_tree_model_get(modelo, &iter, 10, &pos, -1);

  apArch = fopen("../data/proveedores.dat", "r+b");
  if (apArch == NULL) {
    g_print("ERROR: Archivo dañado");
    return FALSE;
  }

  fseek(apArch, pos, SEEK_SET);
  fwrite(&registro, sizeof(Proveedor), 1, apArch);
  fclose(apArch);

  gtk_list_store_clear(tabla.listStore);
  mostrar_proveedores("../data/proveedores.dat");

  return TRUE;
}

void modificar_proveedor_callback(GtkWidget *btn, gpointer data) {
  desconectar_señal_btn(&prForm.aceptBtn);
  prov_crear_form(1);
  gtk_window_set_title(GTK_WINDOW(prForm.baseVentana.win), "Modificar Proveedor");
  g_signal_connect(G_OBJECT(prForm.aceptBtn), "clicked",
                   G_CALLBACK(modificar_datos_proveedor), NULL);
}

typedef struct {
  gchar *nombreC;
  gchar *nombreF;
  gchar *rfc;
  gchar *domicilio;
  gchar *numOficina;
  gchar *wsp;
  gchar *correo;
  gchar *repCom;
  gchar *fechaPermiso;
  long pos;
} ProveedorSinFormato;

/*
typedef struct Proveedor {
  int       estado;
  char      nombreComercial[100];
  char      nombreFactura[100];
  char      rfc[15];
  char      domicilio[100];
  char      numeroOficina[11];
  char      whatsappEmpresarial[11];
  char      correoElectronico[100];
  char      representanteComercial[100];
  ushort    permisoNarcoticos;
  Fecha     vigencia;
}Proveedor;
*/

void eliminar_datos_proveedor(GtkWidget *btn, gpointer data) {
  FILE *apArch;
  GtkTreeIter iter;
  Proveedor proveedor;
  GtkTreeModel *modelo;
  ProveedorSinFormato prov;

  if (gtk_tree_selection_get_selected(tabla.filaActual, &modelo, &iter) ==
      FALSE)
    return;

  gtk_list_store_set(tabla.listStore, &iter, 0, &prov.rfc, 1, &prov.nombreC, 2,
                     &prov.nombreF, 3, &prov.correo, 4, &prov.numOficina, 5,
                     &prov.wsp, 6, &prov.domicilio, 7, &prov.repCom, 8,
                     &proveedor.permisoNarcoticos, 9, &prov.fechaPermiso, 10,
                     &prov.pos, -1);

  if (!fechaGchar_a_int(prov.fechaPermiso, &proveedor.vigencia))
    return;

  gchar_a_char(prov.repCom, proveedor.representanteComercial);
  gchar_a_char(prov.nombreC, proveedor.nombreComercial);
  gchar_a_char(prov.wsp, proveedor.whatsappEmpresarial);
  gchar_a_char(prov.domicilio, proveedor.domicilio);
  gchar_a_char(prov.rfc, proveedor.rfc);
  gchar_a_char(prov.correo, proveedor.correoElectronico);
  gchar_a_char(prov.nombreF, proveedor.nombreFactura);
  gchar_a_char(prov.numOficina, proveedor.numeroOficina);

  proveedor.estado = 0;

  apArch = fopen("../data/proveedores.dat", "r+b");
  if (apArch == NULL) {
    g_print("ERROR: Archivo dañado");
    return;
  }

  fseek(apArch, prov.pos, SEEK_SET);
  // fwrite(&proveedor, sizeof(Proveedor), 1, apArch);
  fclose(apArch);

  gtk_list_store_clear(tabla.listStore);
  mostrar_proveedores("../data/proveedores.dat");
}
