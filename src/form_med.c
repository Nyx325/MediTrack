#include "form_med.h"
#include "general.h"
#include "listv.h"

typedef struct {
  BaseForm baseVentana;
  EntradaTexto id;
  EntradaTexto substancia;
  EntradaTexto gramaje;
  EntradaTexto unidadesC;
  EntradaTexto presentacion;
  EntradaTexto lab;
  EntradaTexto costo;
  EntradaTexto lote;
  EntradaFecha caducidad;
  EntradaTexto unidadesI;
  EntradaTexto marca;
  GtkWidget *warningLbl;
  GtkWidget *aceptBtn;
  GtkWidget *cancelBtn;
} MedForm;

MedForm mForm;

void ordenar_medicamentos() {
  FILE *archivo = fopen("../data/medicamentos.dat", "rb+");

  if (archivo == NULL) {
    perror("Error al abrir el archivo");
    return;
  }

  int tamRegistro = sizeof(Medicamento);
  fseek(archivo, 0, SEEK_END);
  long tamArchivo = ftell(archivo);
  fseek(archivo, 0, SEEK_SET);

  int totalRegistros = tamArchivo / tamRegistro;

  for (int i = 1; i < totalRegistros; i++) {
    fseek(archivo, i * tamRegistro, SEEK_SET);

    int j;
    Medicamento tmp;
    fread(&tmp, sizeof(Medicamento), 1, archivo);

    j = i - 1;
    while (j >= 0) {
      Medicamento actual;
      fseek(archivo, j * tamRegistro, SEEK_SET);
      fread(&actual, sizeof(Medicamento), 1, archivo);

      if (actual.id < tmp.id)
        break;

      fseek(archivo, (j + 1) * tamRegistro, SEEK_SET);
      fwrite(&actual, sizeof(Medicamento), 1, archivo);

      j--;
    }

    fseek(archivo, (j + 1) * tamRegistro, SEEK_SET);
    fwrite(&tmp, sizeof(Medicamento), 1, archivo);
  }

  fclose(archivo);
}

void free_medform(GtkWidget *widget, gpointer data) {
  gtk_widget_hide(mForm.baseVentana.win);
  if (mForm.warningLbl)
    gtk_widget_destroy(mForm.warningLbl);
  if (mForm.aceptBtn)
    gtk_widget_destroy(mForm.aceptBtn);
  if (mForm.cancelBtn)
    gtk_widget_destroy(mForm.cancelBtn);

  free_entradatexto(&mForm.id);
  free_entradatexto(&mForm.substancia);
  free_entradatexto(&mForm.gramaje);
  free_entradatexto(&mForm.unidadesC);
  free_entradatexto(&mForm.presentacion);
  free_entradatexto(&mForm.lab);
  free_entradatexto(&mForm.costo);
  free_entradatexto(&mForm.lote);
  free_entradatexto(&mForm.unidadesI);
  free_entradatexto(&mForm.marca);

  free_entradafecha(&mForm.caducidad);

  free_baseform(&mForm.baseVentana);

  mForm.warningLbl = NULL;
  mForm.aceptBtn = NULL;
  mForm.cancelBtn = NULL;

  gtk_widget_hide(mForm.baseVentana.win);
}

void cargar_medicamento_reguistro() {
  long posArch;
  char cualquierDatoNumerico[11];
  Medicamento registro;
  GtkTreeModel *model;
  GtkTreeIter iter;
  FILE *apArch;

  if (gtk_tree_selection_get_selected(tabla.filaActual, &model, &iter) ==
      FALSE) {
    free_medform(NULL, NULL);
    return;
  }

  gtk_tree_model_get(model, &iter, 11, &posArch, -1);

  apArch = fopen("../data/medicamentos.dat", "rb");
  if (apArch == NULL) {
    g_print("ERROR: Archivo dañado");
    return;
  }
  fseek(apArch, posArch, SEEK_SET);
  fread(&registro, sizeof(Medicamento), 1, apArch);
  fclose(apArch);

  sprintf(cualquierDatoNumerico, "%d", registro.id);
  gtk_entry_set_text(GTK_ENTRY(mForm.id.entry), cualquierDatoNumerico);

  gtk_entry_set_text(GTK_ENTRY(mForm.substancia.entry), registro.sustancia);

  gtk_entry_set_text(GTK_ENTRY(mForm.marca.entry), registro.marca);

  sprintf(cualquierDatoNumerico, "%.2f", registro.gramaje);
  gtk_entry_set_text(GTK_ENTRY(mForm.gramaje.entry), cualquierDatoNumerico);

  sprintf(cualquierDatoNumerico, "%d", registro.unidadesCaja);
  gtk_entry_set_text(GTK_ENTRY(mForm.unidadesC.entry), cualquierDatoNumerico);

  gtk_entry_set_text(GTK_ENTRY(mForm.presentacion.entry),
                     registro.presentacion);

  sprintf(cualquierDatoNumerico, "%d", registro.unidadesInventario);
  gtk_entry_set_text(GTK_ENTRY(mForm.unidadesI.entry), cualquierDatoNumerico);

  sprintf(cualquierDatoNumerico, "%.2f", registro.costo);
  gtk_entry_set_text(GTK_ENTRY(mForm.costo.entry), cualquierDatoNumerico);

  gtk_entry_set_text(GTK_ENTRY(mForm.lote.entry), registro.lote);

  sprintf(cualquierDatoNumerico, "%d", registro.fecha.anio);
  gtk_entry_set_text(GTK_ENTRY(mForm.caducidad.anioEntry),
                     cualquierDatoNumerico);

  gtk_combo_box_set_active(GTK_COMBO_BOX(mForm.caducidad.mesCombox),
                           registro.fecha.mes);
  gtk_combo_box_set_active(GTK_COMBO_BOX(mForm.caducidad.diaCombox),
                           registro.fecha.dia);

  gtk_entry_set_text(GTK_ENTRY(mForm.lab.entry), registro.laboratorio);
}

void med_crear_form(Opc modo) {
  crear_ventana(&mForm.baseVentana, 611, 220, free_medform);

  crear_entradatexto(&mForm.id, "Clave", 10, 11);
  crear_entradatexto(&mForm.substancia, "Substancia", 10, 49);
  crear_entradatexto(&mForm.gramaje, "Gramaje", 7, 8);
  crear_entradatexto(&mForm.unidadesC, "Unidades\nCaja", 10, 10);
  crear_entradatexto(&mForm.presentacion, "Presentacion", 10, 49);
  crear_entradatexto(&mForm.lab, "Laboratorio", 10, 49);
  crear_entradatexto(&mForm.costo, "Costo", 7, 9);
  crear_entradatexto(&mForm.lote, "Lote", 5, 20);
  crear_entradatexto(&mForm.unidadesI, "Unidades\nInventario", 5, 10);
  crear_entradatexto(&mForm.marca, "Marca", 5, 49);

  crear_entradafecha(&mForm.caducidad, "Caducidad");

  mForm.warningLbl = gtk_label_new("");

  crear_boton(&mForm.aceptBtn, "Aceptar", no_callback);
  crear_boton(&mForm.cancelBtn, "Cancelar", free_medform);

  // Clave
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.id.lbl, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.id.entry, 1, 0, 2, 1);

  // Substancia
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.substancia.lbl, 3, 0,
                  1, 1);
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.substancia.entry, 4,
                  0, 3, 1);

  // Gramaje
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.gramaje.lbl, 0, 1, 1,
                  1);
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.gramaje.entry, 1, 1,
                  1, 1);

  // Cantidad / Unidades por caja
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.unidadesC.lbl, 2, 1,
                  1, 1);
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.unidadesC.entry, 3, 1,
                  1, 1);

  // Presentación
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.presentacion.lbl, 4,
                  1, 1, 1);
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.presentacion.entry, 5,
                  1, 3, 1);

  // Laboratorio
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.lab.lbl, 3, 4, 1, 1);
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.lab.entry, 4, 4, 4,
                  1);

  // Costo
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.costo.lbl, 0, 3, 1,
                  1);
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.costo.entry, 1, 3, 1,
                  1);

  // Lote
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.lote.lbl, 2, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.lote.entry, 3, 3, 4,
                  1);

  // Caducidad
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.caducidad.titulo, 7,
                  3, 1, 1);
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.caducidad.anioEntry,
                  8, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.caducidad.mesCombox,
                  9, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.caducidad.diaCombox,
                  10, 3, 1, 1);

  // Unidades en inventario
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.unidadesI.lbl, 8, 1,
                  1, 1);
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.unidadesI.entry, 9, 1,
                  2, 1);

  // Marca
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.marca.lbl, 7, 0, 1,
                  1);
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.marca.entry, 8, 0, 3,
                  1);

  // Warning
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.warningLbl, 1, 5, 9,
                  1);

  // Botones
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.aceptBtn, 1, 6, 4, 1);
  gtk_grid_attach(GTK_GRID(mForm.baseVentana.grid), mForm.cancelBtn, 6, 6, 4,
                  1);

  if (modo)
    cargar_medicamento_reguistro();

  gtk_widget_show_all(mForm.baseVentana.win);
}

void mostrar_medicamentos(char *archivoDir) {
  long pos;
  Medicamento med;
  char fechaFormato[12];
  GtkTreeIter iter;
  FILE *apArch;

  // apuntador definido en listv.c para el modelo de la tabla
  tabla.listStore = gtk_list_store_new(
      12, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_FLOAT, G_TYPE_UINT,
      G_TYPE_STRING, G_TYPE_UINT, G_TYPE_FLOAT, G_TYPE_STRING, G_TYPE_STRING,
      G_TYPE_STRING, G_TYPE_ULONG);

  apArch = fopen(archivoDir, "a+b");
  if (apArch == NULL) {
    g_print("ERROR: Archivo dañado");
    return;
  }

  while (fread(&med, sizeof(Medicamento), 1, apArch)) {
    if (med.estado) {
      pos = ftell(apArch) - sizeof(Medicamento);
      // Formatear fecha como cadena
      sprintf(fechaFormato, "%02d/%02d/%04d", med.fecha.dia, med.fecha.mes,
              med.fecha.anio);
      // Agregar fila
      gtk_list_store_append(tabla.listStore, &iter);
      // Agregar datos al modelo
      gtk_list_store_set(tabla.listStore, &iter, 0, med.id, 1, med.sustancia, 2,
                         med.marca, 3, med.gramaje, 4, med.unidadesCaja, 5,
                         med.presentacion, 6, med.unidadesInventario, 7,
                         med.costo, 8, med.lote, 9, fechaFormato, 10,
                         med.laboratorio, 11, pos, -1);
    }
  }
  fclose(apArch);

  char *titulos[] = {"Clave",
                     "Substancia",
                     "Marca",
                     "Gramaje (g)",
                     "Cantidad",
                     "Presentacion",
                     "Unidades de inventario",
                     "Costo",
                     "Lote",
                     "Caducidad",
                     "Laboratorio"};

  listview_importmodel(&tabla, 10, titulos);
}

typedef struct {
  TextoIngresado id;
  TextoIngresado marca;
  TextoIngresado substancia;
  TextoIngresado gramaje;
  TextoIngresado presentacion;
  TextoIngresado laboratorio;
  TextoIngresado unidadesCaja;
  TextoIngresado costo;
  TextoIngresado lote;
  FechaIngresada caducidad;
  TextoIngresado unidadesInventario;
} DatosFormularioMedicamento;

// Datos que se capturan y convierten a char deben tener formato
// numérico (int, float, etc)
typedef struct {
  char idSF[11];
  char gramajeSF[9];
  char unidadesCaja[11];
  char costo[10];
  char unidadesInventario[11];
} MedNumsSinFormato;

char *formatear_id(const gchar *input) {
  const gsize tam = g_utf8_strlen(input, -1);
  gchar *formateo = g_strdup(input);

  if (tam == 0) {
    g_free(formateo);
    return NULL;
  }

  if (is_full_nums(input, -1, -1) == FALSE) {
    g_free(formateo);
    return NULL;
  }

  return g_strdup(formateo);
}

Medicamento validar_formulario_medicamento() {
  GString *err = g_string_new("");
  Medicamento registro;
  DatosFormularioMedicamento cap;
  WidgetsFecha widFecha;
  MedNumsSinFormato reg;

  registro.estado = 0;

  capturar_formatear_texto(&cap.id, reg.idSF, formatear_num, mForm.id.entry,
                           &err, "Clave");
  capturar_formatear_texto(&cap.marca, registro.marca, formatear_palabra,
                           mForm.marca.entry, &err, "Marca");
  capturar_formatear_texto(&cap.substancia, registro.sustancia,
                           formatear_nombre, mForm.substancia.entry, &err,
                           "Substancia");
  capturar_formatear_texto(&cap.gramaje, reg.gramajeSF, formatear_num,
                           mForm.gramaje.entry, &err, "Gramaje");
  capturar_formatear_texto(&cap.presentacion, registro.presentacion,
                           formatear_nombre, mForm.presentacion.entry, &err,
                           "Presentacion");
  capturar_formatear_texto(&cap.laboratorio, registro.laboratorio,
                           formatear_palabra, mForm.lab.entry, &err,
                           "Laboratorio");
  capturar_formatear_texto(&cap.unidadesCaja, reg.unidadesCaja, formatear_num,
                           mForm.unidadesC.entry, &err, "Unidades Caja");
  capturar_formatear_texto(&cap.costo, reg.costo, formatear_num,
                           mForm.costo.entry, &err, "Costo");
  capturar_formatear_texto(&cap.lote, registro.lote, formatear_palabra,
                           mForm.lote.entry, &err, "Lote");
  capturar_formatear_texto(&cap.unidadesInventario, reg.unidadesInventario,
                           formatear_num, mForm.unidadesI.entry, &err,
                           "Unidades Inventario");

  registro.id = atoi(reg.idSF);
  registro.gramaje = atof(reg.gramajeSF);
  registro.costo = atof(reg.costo);
  registro.unidadesInventario = atoi(reg.unidadesInventario);
  registro.unidadesCaja = atoi(reg.unidadesCaja);

  widFecha.anioEntry = GTK_ENTRY(mForm.caducidad.anioEntry);
  widFecha.mesCombox = GTK_COMBO_BOX(mForm.caducidad.mesCombox);
  widFecha.diaCombox = GTK_COMBO_BOX(mForm.caducidad.diaCombox);
  capturar_formatear_fecha(&cap.caducidad, &widFecha, &registro.fecha, &err,
                           "Caducidad");

  if (err->len != 0) {
    g_string_append(err, " no válido(s)");
    gtk_label_set_markup(GTK_LABEL(mForm.warningLbl), err->str);
  } else
    registro.estado = 1;

  return registro;
}

gboolean registrar_datos_medicamento(GtkWidget *btn, gpointer data) {
  FILE *apArch;
  Medicamento registro = validar_formulario_medicamento();

  if (registro.estado == 0)
    return FALSE;

  free_medform(NULL, NULL);

  apArch = fopen("../data/medicamentos.dat", "ab");
  if (apArch == NULL) {
    g_print("ERROR: Archivo dañado");
    return FALSE;
  }

  fwrite(&registro, sizeof(Medicamento), 1, apArch);
  fclose(apArch);

  ordenar_medicamentos();
  gtk_list_store_clear(tabla.listStore);
  mostrar_medicamentos("../data/medicamentos.dat");

  return TRUE;
}

void agregar_medicamentos_callback(GtkWidget *btn, gpointer data) {
  desconectar_señal_btn(&mForm.aceptBtn);
  med_crear_form(NUEVO_REGISTRO);

  gtk_window_set_title(GTK_WINDOW(mForm.baseVentana.win),
                       "Agregar Medicamento");
  g_signal_connect(G_OBJECT(mForm.aceptBtn), "clicked",
                   G_CALLBACK(registrar_datos_medicamento), NULL);
}

gboolean modificar_datos_medicamento(GtkWidget *btn, gpointer data) {
  long pos;
  FILE *apArch;
  Medicamento registro = validar_formulario_medicamento();
  GtkTreeModel *modelo;
  GtkTreeIter iter;

  if (registro.estado == 0)
    return FALSE;

  free_medform(NULL, NULL);

  gtk_tree_selection_get_selected(tabla.filaActual, &modelo, &iter);
  gtk_tree_model_get(modelo, &iter, 11, &pos, -1);

  apArch = fopen("../data/medicamentos.dat", "r+b");
  if (apArch == NULL) {
    g_print("ERROR: Archivo dañado\n");
    return FALSE;
  }

  fseek(apArch, pos, SEEK_SET);

  fwrite(&registro, sizeof(Medicamento), 1, apArch);
  fclose(apArch);

  ordenar_medicamentos();
  gtk_list_store_clear(tabla.listStore);
  mostrar_medicamentos("../data/medicamentos.dat");

  return TRUE;
}

void modificar_medicamentos_callback(GtkWidget *btn, gpointer data) {
  desconectar_señal_btn(&mForm.aceptBtn);
  med_crear_form(MODIFICAR_REGISTRO);

  gtk_window_set_title(GTK_WINDOW(mForm.baseVentana.win),
                       "Modificar Medicamento");
  g_signal_connect(G_OBJECT(mForm.aceptBtn), "clicked",
                   G_CALLBACK(modificar_datos_medicamento), NULL);
}

typedef struct {
  gchar *id;
  gchar *marca;
  gchar *sustancia;
  gchar *presentacion;
  gchar *laboratorio;
  gchar *lote;
  gchar *fecha;
  long pos;
} MedicamentosSinFormato;

void eliminar_datos_medicamentos(GtkWidget *btn, gpointer data) {
  FILE *apArch;
  GtkTreeIter iter;
  Medicamento medicamento;
  GtkTreeModel *modelo;
  MedicamentosSinFormato med;

  if (gtk_tree_selection_get_selected(tabla.filaActual, &modelo, &iter) ==
      FALSE)
    return;

  gtk_tree_model_get(
      modelo, &iter, 0, &med.id, 1, &med.sustancia, 2, &med.marca, 3,
      &medicamento.gramaje, 4, &medicamento.unidadesCaja, 5, &med.presentacion,
      6, &medicamento.unidadesInventario, 7, &medicamento.costo, 8, &med.lote,
      9, &med.fecha, 10, &med.laboratorio, 11, &med.pos, -1);

  gchar_a_char(med.sustancia, medicamento.sustancia);
  gchar_a_char(med.marca, medicamento.marca);
  gchar_a_char(med.presentacion, medicamento.presentacion);
  gchar_a_char(med.lote, medicamento.lote);
  gchar_a_char(med.laboratorio, medicamento.laboratorio);

  if (!fechaGchar_a_int(med.fecha, &medicamento.fecha))
    return;

  medicamento.estado = 0;

  apArch = fopen("../data/medicamentos.dat", "r+b");
  if (apArch == NULL) {
    g_print("ERROR: Archivo dañado");
    return;
  }

  fseek(apArch, med.pos, SEEK_SET);
  fwrite(&medicamento, sizeof(Medicamento), 1, apArch);
  fclose(apArch);

  gtk_list_store_clear(tabla.listStore);
  mostrar_medicamentos("../data/medicamentos.dat");
}
