#include "consultas.h"
#include "general.h"
#include "reportes.h"
#include "listv.h"
#include "listv_bar.h"
#include <stdio.h>

ListView Consult;
ConsForm cForm;
gchar *curpPac;

void free_tabla_consultas(GtkWidget *widget, gpointer data) {
  gtk_widget_hide(Consult.baseVentana.win);

  if (Consult.tView)
    gtk_widget_destroy(Consult.tView);
  if (Consult.listStore)
    gtk_list_store_clear(Consult.listStore);
  if (Consult.filaActual)
    g_object_unref(Consult.filaActual);

  free_baselistv(&Consult.baseVentana);

  free_barlistv(&Consult.bar);

  Consult.tView = NULL;
  Consult.listStore = NULL;
  Consult.filaActual = NULL;
}

void mostrar_consultas(char *archivoDir) {
  long pos;
  Consultas registro;
  char textoFormato[12];
  GtkTreeIter iter;
  FILE *apArch;

  Consult.listStore =
      gtk_list_store_new(3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_ULONG);

  apArch = fopen(archivoDir, "a+b");
  if (apArch == NULL) {
    g_print("ERROR: Archivo dañado");
    return;
  }

  while (fread(&registro, sizeof(Consultas), 1, apArch)) {
    if (registro.edo) {
      pos = ftell(apArch) - sizeof(Consultas);
      sprintf(textoFormato, "%02d/%02d/%04d", registro.fecha.dia,
              registro.fecha.mes, registro.fecha.anio);

      gtk_list_store_append(Consult.listStore, &iter);
      gtk_list_store_set(Consult.listStore, &iter, 0, textoFormato, 1,
                         registro.Dr, 2, pos, -1);
    }
  }
  fclose(apArch);

  char *titulos[] = {"Fecha", "Doctor"};
  listview_importmodel(&Consult, 2, titulos);
}

void crear_tabla_consultas(GtkTreeView *tree_view, GtkTreePath *path,
                           GtkTreeViewColumn *column, gpointer user_data) {
  GtkTreeIter iter;
  GtkTreeModel *modelo;
  char tituloVentana[28];
  char dirArch[50];

  gtk_tree_selection_get_selected(tabla.filaActual, &modelo, &iter);
  gtk_tree_model_get(modelo, &iter, 0, &curpPac, -1);
  sprintf(dirArch, "../data/consultas/%s.dat", curpPac);

  guint handler_id = crear_ventana_listv(&Consult.baseVentana, 700, 500);
  g_signal_handler_disconnect(G_OBJECT(Consult.baseVentana.win), handler_id);
  g_signal_connect(G_OBJECT(Consult.baseVentana.win), "destroy",
                   G_CALLBACK(free_tabla_consultas), NULL);
  sprintf(tituloVentana, "Consultas %s", curpPac);
  gtk_window_set_title(GTK_WINDOW(Consult.baseVentana.win), tituloVentana);

  Consult.bar = crear_bar(BAR_PACIENTES);
  // Solución cutre xD
  gtk_container_remove(GTK_CONTAINER(Consult.baseVentana.box), Consult.bar.mainbox);
  free_barlistv(&Consult.bar);
  Consult.bar = crear_bar(BAR_PACIENTES);
  gtk_box_pack_start(GTK_BOX(Consult.baseVentana.box), Consult.bar.mainbox, FALSE,
                     FALSE, 0);

  g_signal_connect(G_OBJECT(Consult.bar.agregar.base.btn), "clicked",
                   G_CALLBACK(agregar_consulta_callback), NULL);
  g_signal_connect(G_OBJECT(Consult.bar.modificar.base.btn), "clicked",
                   G_CALLBACK(modificar_consulta_callback), NULL);
  g_signal_connect(G_OBJECT(Consult.bar.eliminar.base.btn), "clicked",
                   G_CALLBACK(eliminar_datos_consulta), NULL);

  gtk_box_pack_start(GTK_BOX(Consult.baseVentana.box), Consult.bar.mainbox,
                     FALSE, FALSE, 0);
  mostrar_consultas(dirArch);

  gtk_widget_show_all(Consult.baseVentana.win);
}

void free_entradatextv(EntradaTextv *entrada) {
  if (entrada->lblTitulo)
    gtk_widget_destroy(entrada->lblTitulo);

  if (entrada->textv)
    gtk_widget_destroy(entrada->textv);

  if (entrada->buffer)
    g_object_unref(entrada->buffer);

  if (entrada->numcEscritos)
    gtk_widget_destroy(entrada->numcEscritos);

  entrada->lblTitulo = NULL;
  entrada->textv = NULL;
  entrada->buffer = NULL;
  entrada->numcEscritos = NULL;
}

void free_entradapresion(EntradaPresion *entrada) {
  if (entrada->lbl)
    gtk_widget_destroy(entrada->lbl);
  if (entrada->diastEntry)
    gtk_widget_destroy(entrada->diastEntry);
  if (entrada->sistEntry)
    gtk_widget_destroy(entrada->sistEntry);

  entrada->lbl = NULL;
  entrada->diastEntry = NULL;
  entrada->sistEntry = NULL;
}

void free_formcons(GtkWidget *widget, gpointer data) {
  gtk_widget_hide(cForm.baseForm.win);
  if (cForm.warningLbl)
    gtk_widget_destroy(cForm.warningLbl);
}

void contador_chars(GtkWidget *widget, gpointer data) {
  EntradaTextv *entrada = (EntradaTextv *)data;
  GtkTextIter start, end;
  gtk_text_buffer_get_start_iter(entrada->buffer, &start);
  gtk_text_buffer_get_end_iter(entrada->buffer, &end);
  gchar *text = gtk_text_buffer_get_text(entrada->buffer, &start, &end, FALSE);
  long cEscritos = g_utf8_strlen(text, -1);
  g_free(text);

  char cuentaLbl[50 + 36];

  if (cEscritos < entrada->maxChars) {
    snprintf(cuentaLbl, sizeof(cuentaLbl), "%ld/%d", cEscritos,
             entrada->maxChars);
    gtk_label_set_text(GTK_LABEL(entrada->numcEscritos), cuentaLbl);
  } else {
    snprintf(
        cuentaLbl, sizeof(cuentaLbl),
        "%ld/%d Texto demasiado largo, NO serán\nguardados todos los datos",
        cEscritos, entrada->maxChars);
    gtk_label_set_text(GTK_LABEL(entrada->numcEscritos), cuentaLbl);
  }
}

void crear_entradatextv(EntradaTextv *entrada, char *titulo, int maxChars,
                        int xTam, int yTam) {
  entrada->buffer = gtk_text_buffer_new(NULL);
  entrada->textv = gtk_text_view_new_with_buffer(entrada->buffer);
  entrada->lblTitulo = gtk_label_new(titulo);
  entrada->numcEscritos = gtk_label_new("");
  entrada->maxChars = maxChars;
  entrada->scrollW = gtk_scrolled_window_new(NULL, NULL);
  entrada->frame = gtk_frame_new("");

  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(entrada->scrollW),
                                 GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_container_add(GTK_CONTAINER(entrada->frame), entrada->textv);

  gtk_widget_set_size_request(entrada->scrollW, xTam, yTam);
  gtk_container_add(GTK_CONTAINER(entrada->scrollW), entrada->frame);
  gtk_container_set_border_width(GTK_CONTAINER(entrada->scrollW), 10);

  g_signal_connect(G_OBJECT(entrada->buffer), "changed",
                   G_CALLBACK(contador_chars), entrada);
}

EntradaPresion crear_entradapresion() {
  EntradaPresion p;
  p.lbl = gtk_label_new("Presión");
  p.sistEntry = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(p.sistEntry), "Sisto");
  gtk_entry_set_width_chars(GTK_ENTRY(p.sistEntry), 5);
  gtk_entry_set_max_length(GTK_ENTRY(p.sistEntry), 4);
  p.diastEntry = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(p.diastEntry), "Diast");
  gtk_entry_set_width_chars(GTK_ENTRY(p.diastEntry), 5);
  gtk_entry_set_max_length(GTK_ENTRY(p.diastEntry), 4);

  return p;
}

void cargar_consulta_registro() {
  long posArch;
  Consultas registro;
  GtkTreeModel *modelo;
  GtkTreeIter iter;
  FILE *apArch;
  char dirArch[30];

  char numFormateado[15];

  if (gtk_tree_selection_get_selected(Consult.filaActual, &modelo, &iter) ==
      FALSE) {
    free_formcons(NULL, NULL);
    return;
  }

  gtk_tree_model_get(modelo, &iter, 2, &posArch, -1);

  sprintf(dirArch, "../data/consultas/%s.dat", curpPac);
  apArch = fopen(dirArch, "rb");
  if (apArch == NULL) {
    g_print("ERROR: archivo dañado");
    return;
  }

  fseek(apArch, posArch, SEEK_SET);
  fread(&registro, sizeof(Consultas), 1, apArch);
  g_print("%s\n\n", registro.nombre);
  fclose(apArch);

  gtk_entry_set_text(GTK_ENTRY(cForm.nomPac.entry), registro.nombre);
  gtk_entry_set_text(GTK_ENTRY(cForm.nomDr.entry), registro.Dr);

  sprintf(numFormateado, "%d", registro.edad);
  gtk_entry_set_text(GTK_ENTRY(cForm.edad.entry), numFormateado);

  sprintf(numFormateado, "%.2f", registro.peso);
  gtk_entry_set_text(GTK_ENTRY(cForm.peso.entry), numFormateado);

  sprintf(numFormateado, "%.2f", registro.altura);
  gtk_entry_set_text(GTK_ENTRY(cForm.altura.entry), numFormateado);

  sprintf(numFormateado, "%.2f", registro.temp);
  gtk_entry_set_text(GTK_ENTRY(cForm.temp.entry), numFormateado);

  sprintf(numFormateado, "%hd", registro.presion.sist);
  gtk_entry_set_text(GTK_ENTRY(cForm.presion.sistEntry), numFormateado);

  sprintf(numFormateado, "%hd", registro.presion.diasto);
  gtk_entry_set_text(GTK_ENTRY(cForm.presion.diastEntry), numFormateado);

  sprintf(numFormateado, "%d", registro.fecha.anio);
  gtk_entry_set_text(GTK_ENTRY(cForm.fConsulta.anioEntry), numFormateado);
  gtk_combo_box_set_active(GTK_COMBO_BOX(cForm.fConsulta.mesCombox),
                           registro.fecha.mes);
  gtk_combo_box_set_active(GTK_COMBO_BOX(cForm.fConsulta.diaCombox),
                           registro.fecha.dia);

  gtk_text_buffer_set_text(cForm.sintomas.buffer, registro.sintomas, -1);
  gtk_text_buffer_set_text(cForm.alergias.buffer, registro.alergias, -1);
  gtk_text_buffer_set_text(cForm.enfCron.buffer, registro.enfermedades, -1);
}

void crear_formulario_consulta(Opc modo) {
  crear_ventana(&cForm.baseForm, 700, 400, free_formcons);

  crear_entradatexto(&cForm.nomPac, "Nombre\nPaciente", 10, 50);
  crear_entradatexto(&cForm.edad, "Edad", 4, 3);
  crear_entradatexto(&cForm.peso, "Peso", 4, 4);
  crear_entradatexto(&cForm.altura, "Altura", 4, 4);
  crear_entradatexto(&cForm.nomDr, "Doctor", 10, 50);
  crear_entradatexto(&cForm.nomDr, "Doctor", 10, 50);
  crear_entradatexto(&cForm.temp, "Temp.", 6, 7);

  crear_entradafecha(&cForm.fConsulta, "Fecha Consulta");

  crear_entradatextv(&cForm.sintomas, "Síntomas", 500, 100, 210);
  crear_entradatextv(&cForm.alergias, "Alergias", 200, 100, 100);
  crear_entradatextv(&cForm.enfCron, "Enfermedades Crónicas", 200, 100, 100);

  cForm.presion = crear_entradapresion();

  cForm.warningLbl = gtk_label_new("");

  crear_boton(&cForm.aceptBtn, "Aceptar", no_callback);
  crear_boton(&cForm.cancelBtn, "Cancelar", free_formcons);

  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.nomPac.lbl, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.nomPac.entry, 1, 0, 4,
                  1);

  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.fConsulta.titulo, 8, 0,
                  1, 1);
  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.fConsulta.anioEntry, 9,
                  0, 1, 1);
  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.fConsulta.mesCombox, 10,
                  0, 1, 1);
  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.fConsulta.diaCombox, 11,
                  0, 1, 1);

  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.edad.lbl, 0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.edad.entry, 1, 1, 1, 1);

  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.peso.lbl, 2, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.peso.entry, 3, 1, 1, 1);

  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.altura.lbl, 4, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.altura.entry, 5, 1, 1,
                  1);

  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.nomDr.lbl, 8, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.nomDr.entry, 9, 1, 3, 1);

  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.presion.lbl, 0, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.presion.sistEntry, 1, 2,
                  1, 1);
  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.presion.diastEntry, 2, 2,
                  1, 1);

  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.temp.lbl, 3, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.temp.entry, 4, 2, 1, 1);

  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.sintomas.lblTitulo, 1, 4,
                  1, 1);
  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.sintomas.scrollW, 0, 4,
                  7, 11);
  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.sintomas.numcEscritos, 0,
                  15, 6, 1);

  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.alergias.lblTitulo, 8, 4,
                  1, 1);
  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.alergias.scrollW, 8, 4,
                  4, 5);
  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.alergias.numcEscritos, 8,
                  9, 6, 1);

  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.enfCron.lblTitulo, 9, 10,
                  1, 1);
  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.enfCron.scrollW, 8, 10,
                  4, 5);
  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.enfCron.numcEscritos, 8,
                  15, 6, 1);

  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.aceptBtn, 0, 16, 7, 1);
  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.cancelBtn, 8, 16, 6, 1);

  if (modo)
    cargar_consulta_registro();

  gtk_widget_show_all(cForm.baseForm.win);
}

typedef struct {
  FechaIngresada fCons;
  TextoIngresado nomP;
  TextoIngresado nomDr;
  TextoIngresado edad;
  TextoIngresado peso;
  TextoIngresado altura;
  TextoIngresado psisto;
  TextoIngresado pdiasto;
  TextoIngresado temp;
} DatosFormularioConsulta;

// Datos que se capturan y convierten a char deben tener formato
// numérico (int, float, etc)
typedef struct {
  char edadSF[4];
  char pesoSF[4];
  char alturaSF[5];
  char pSistSF[4];
  char pDiastSF[4];
  char tempSF[5];
} ConsNumsSinFormato;

void capturar_formatear_textv(EntradaTextv *entrada, char *destino) {
  GtkTextIter start, end;
  gtk_text_buffer_get_start_iter(entrada->buffer, &start);
  gtk_text_buffer_get_end_iter(entrada->buffer, &end);
  char *text = gtk_text_buffer_get_text(entrada->buffer, &start, &end, FALSE);

  strcpy(destino, text);
  destino[entrada->maxChars] = '\0';
}

Consultas validar_formulario_consultas() {
  GString *err = g_string_new("");
  Consultas registro;
  WidgetsFecha widFecha;
  DatosFormularioConsulta form;
  ConsNumsSinFormato numSF;

  registro.edo = 0;

  widFecha.anioEntry = GTK_ENTRY(cForm.fConsulta.anioEntry);
  widFecha.mesCombox = GTK_COMBO_BOX(cForm.fConsulta.mesCombox);
  widFecha.diaCombox = GTK_COMBO_BOX(cForm.fConsulta.diaCombox);
  capturar_formatear_fecha(&form.fCons, &widFecha, &registro.fecha, &err,
                           "Consulta");

  capturar_formatear_texto(&form.nomP, registro.nombre, formatear_nombre,
                           cForm.nomPac.entry, &err, "nombre");
  capturar_formatear_texto(&form.nomDr, registro.Dr, formatear_nombre,
                           cForm.nomDr.entry, &err, "Nombre doctor");
  capturar_formatear_texto(&form.edad, numSF.edadSF, formatear_num,
                           cForm.edad.entry, &err, "Edad");
  capturar_formatear_texto(&form.peso, numSF.pesoSF, formatear_num,
                           cForm.peso.entry, &err, "Peso");
  capturar_formatear_texto(&form.altura, numSF.alturaSF, formatear_num,
                           cForm.altura.entry, &err, "Altura");
  capturar_formatear_texto(&form.psisto, numSF.pSistSF, formatear_num,
                           cForm.presion.sistEntry, &err, "Presión sistólica");
  capturar_formatear_texto(&form.pdiasto, numSF.pDiastSF, formatear_num,
                           cForm.presion.diastEntry, &err,
                           "Presión diastólica");
  capturar_formatear_texto(&form.temp, numSF.tempSF, formatear_num,
                           cForm.temp.entry, &err, "Temperatura");

  registro.edad = atoi(numSF.edadSF);
  registro.peso = atoi(numSF.pesoSF);
  registro.temp = atoi(numSF.tempSF);
  registro.altura = atof(numSF.alturaSF);
  registro.presion.sist = atoi(numSF.pSistSF);
  registro.presion.diasto = atoi(numSF.pDiastSF);

  capturar_formatear_textv(&cForm.sintomas, registro.sintomas);
  capturar_formatear_textv(&cForm.alergias, registro.alergias);
  capturar_formatear_textv(&cForm.enfCron, registro.enfermedades);

  if (registro.presion.sist > registro.presion.diasto)
    agregar_err("Presión", &err);

  if (err->len != 0) {
    g_string_append(err, " no válido(s)");
    gtk_label_set_markup(GTK_LABEL(cForm.warningLbl), err->str);
  } else
    registro.edo = 1;

  return registro;
}

void registrar_consulta(GtkWidget *btn, gpointer data) {
  FILE *apArch;
  char dirArch[50];
  GtkTreeIter iter;
  GtkTreeModel *model;
  Consultas registro = validar_formulario_consultas();
  g_print("a\n");

  if (registro.edo == 0)
    return;

  free_formcons(NULL, NULL);

  sprintf(dirArch, "../data/consultas/%s.dat", curpPac);
  apArch = fopen(dirArch, "ab");
  if (apArch == NULL) {
    g_print("ERROR: Archivo dañado");
    return;
  }

  g_print("%s\n", registro.nombre);
  fwrite(&registro, sizeof(Consultas), 1, apArch);
  fclose(apArch);

  gtk_list_store_clear(Consult.listStore);
  mostrar_consultas(dirArch);
}

void agregar_consulta_callback(GtkWidget *btn, gpointer data) {
  desconectar_señal_btn(&cForm.aceptBtn);
  crear_formulario_consulta(NUEVO_REGISTRO);
  gtk_window_set_title(GTK_WINDOW(cForm.baseForm.win), "Agregar Consulta");
  g_signal_connect(G_OBJECT(cForm.aceptBtn), "clicked",
                   G_CALLBACK(registrar_consulta), NULL);
}

void modificar_consulta(GtkWidget *btn, gpointer data) {
  long pos;
  FILE *apArch;
  char dirArch[50];
  GtkTreeIter iter;
  GtkTreeModel *modelo;
  Consultas registro = validar_formulario_consultas();

  if (registro.edo == 0)
    return;

  free_formcons(NULL, NULL);

  gtk_tree_selection_get_selected(Consult.filaActual, &modelo, &iter);
  gtk_tree_model_get(modelo, &iter, 2, &pos, -1);

  sprintf(dirArch, "../data/consultas/%s.dat", curpPac);
  apArch = fopen(dirArch, "r+b");
  if (apArch == NULL) {
    g_print("ERROR: Archivo dañado");
    return;
  }

  fseek(apArch, pos, SEEK_SET);
  fwrite(&registro, sizeof(Consultas), 1, apArch);
  fclose(apArch);

  gtk_list_store_clear(Consult.listStore);
  mostrar_consultas(dirArch);
}

void modificar_consulta_callback(GtkWidget *btn, gpointer data) {
  GtkTreeModel *modelo;
  GtkTreeIter iter;

  // Si no se ha seleccionado una fila
  if (gtk_tree_selection_get_selected(tabla.filaActual, &modelo, &iter) ==
      FALSE)
    return;

  desconectar_señal_btn(&cForm.aceptBtn);
  crear_formulario_consulta(MODIFICAR_REGISTRO);

  gtk_window_set_title(GTK_WINDOW(cForm.baseForm.win), "Modificar Consulta");
  g_signal_connect(G_OBJECT(cForm.aceptBtn), "clicked",
                   G_CALLBACK(modificar_consulta), NULL);
}

typedef struct {
  ConsNumsSinFormato numericos;
  gchar *nombre;
  gchar *fecha;
  gchar *Dr;
  gchar *alergias;
  gchar *enfermedades;
  gchar *sintomas;
} ConsultaSinFormato;

void eliminar_datos_consulta(GtkWidget *btn, gpointer data) {
  long pos;
  FILE *apArch;
  char dirArch[50];
  GtkTreeIter iter;
  Consultas registro;
  GtkTreeModel *modelo;
  char numSinFormato[20];

  if (gtk_tree_selection_get_selected(Consult.filaActual, &modelo, &iter) ==
      FALSE)
    return;

  gtk_tree_model_get(modelo, &iter, 2, &pos, -1);

  sprintf(dirArch, "../data/consultas/%s.dat", curpPac);
  apArch = fopen(dirArch, "r+b");
  if (apArch == NULL) {
    g_print("ERROR: Archivo dañado\n");
    return;
  }

  fseek(apArch, pos, SEEK_SET);
  fread(&registro, sizeof(Consultas), 1, apArch);
  registro.edo = 0;
  fseek(apArch, pos, SEEK_SET);
  fwrite(&registro, sizeof(Consultas), 1, apArch);
  fclose(apArch);

  gtk_list_store_clear(Consult.listStore);
  mostrar_consultas(dirArch);
}
