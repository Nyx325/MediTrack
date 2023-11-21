#include "consultas.h"
#include "general.h"
#include "listv.h"
#include <stdio.h>

ListView Consult;
ConsForm cForm;

void free_tabla_consultas(GtkWidget *widget, gpointer data) {
  gtk_widget_hide(Consult.baseVentana.win);

  if (!Consult.tView)
    gtk_widget_destroy(Consult.tView);
  if (!Consult.listStore)
    gtk_list_store_clear(Consult.listStore);
  if (!Consult.filaActual)
    g_object_unref(Consult.filaActual);

  free_baselistv(&Consult.baseVentana);

  free_barlistv(&Consult.bar);

  Consult.tView = NULL;
  Consult.listStore = NULL;
  Consult.filaActual = NULL;
}

void cargar_consultas() {
  long pos;
  gchar *curp;
  FILE *apArch;
  GtkTreeIter iter;
  Consultas consulta;
  GtkTreeModel *modelo;
  char fechaFormato[12];
  char archPaciente[18 + 23];

  if (gtk_tree_selection_get_selected(tabla.filaActual, &modelo, &iter) ==
      FALSE)
    return;

  gtk_tree_model_get(modelo, &iter, 0, &curp, -1);
  sprintf(archPaciente, "../data/consultas/%s.dat", curp);

  Consult.listStore =
      gtk_list_store_new(3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_ULONG);

  apArch = fopen(archPaciente, "a+b");
  if (apArch == NULL) {
    g_print("ERROR: Archivo dañado\n");
    return;
  }

  while (fread(&consulta, sizeof(Consultas), 1, apArch)) {
    if (consulta.edo) {
      sprintf(fechaFormato, "%02d/%02d/%04d", consulta.fecha.dia,
              consulta.fecha.mes, consulta.fecha.anio);
      pos = ftell(apArch) - sizeof(Consultas);

      gtk_list_store_append(Consult.listStore, &iter); // agregar fila nueva
      // Agregar datos al modelo
      gtk_list_store_set(Consult.listStore, &iter, 0, consulta.Dr, 1,
                         fechaFormato, 2, pos, -1);
    }
  }
  fclose(apArch);

  char *titulos[] = {"Doctor", "Fecha"};
  listview_importmodel(&Consult, 2, titulos);
}

void crear_tabla_consultas(GtkTreeView *tree_view, GtkTreePath *path,
                           GtkTreeViewColumn *column, gpointer user_data) {
  guint handler_id = crear_ventana_listv(&Consult.baseVentana, 700, 500);
  g_signal_handler_disconnect(G_OBJECT(Consult.baseVentana.win), handler_id);
  g_signal_connect(G_OBJECT(Consult.baseVentana.win), "destroy",
                   G_CALLBACK(free_tabla_consultas), NULL);

  Consult.bar = crear_bar();
  gtk_box_pack_start(GTK_BOX(Consult.baseVentana.box), Consult.bar.mainbox,
                     FALSE, FALSE, 0);
  cargar_consultas();

  gtk_widget_show_all(Consult.baseVentana.win);
}

void free_entradatextv(EntradaTextv *entrada) {
  if (entrada->lbl)
    gtk_widget_destroy(entrada->lbl);
  if (entrada->textV)
    gtk_widget_destroy(entrada->textV);

  entrada->lbl = NULL;
  entrada->textV = NULL;
}

void free_entradapresion(EntradaPresion *entrada){
    if(entrada->lbl)
        gtk_widget_destroy(entrada->lbl);
    if(entrada->diastEntry)
        gtk_widget_destroy(entrada->diastEntry);
    if(entrada->sistEntry)
        gtk_widget_destroy(entrada->sistEntry);

    entrada->lbl = NULL;
    entrada->diastEntry = NULL;
    entrada->sistEntry = NULL;
}

void free_formcons(GtkWidget *widget, gpointer data) {
  gtk_widget_hide(cForm.baseForm.win);
  if(cForm.warningLbl)
      gtk_widget_destroy(cForm.warningLbl);
}
/*
static void caracteres_restantes(GtkTextBuffer *buffer, const GtkTextIter *location, const char *text, int len, gpointer data) {
    EntradaTextv *textV = (EntradaTextv*)data;

    GtkTextIter end_iter;
    gtk_text_buffer_get_end_iter(buffer, &end_iter);

    int charsEscritos = gtk_text_iter_get_offset(&end_iter);

    // Update the label with the character count information
    char label_text[100];
    snprintf(label_text, sizeof(label_text), "Characters: %d / %d", charsEscritos, textV->maxChars);
    gtk_label_set_text(GTK_LABEL(textV->cEscritos), label_text);
}

void crear_entradatextv(EntradaTextv *info, char *titulo, int maxChars) {
  char buffer[10];
  info->lbl = gtk_label_new(titulo);
  info->buffer = gtk_text_buffer_new(NULL);
  gtk_text_buffer_set_max_length(info->buffer, maxChars);
  info->textV = gtk_text_view_new_with_buffer(info->buffer);
  sprintf(buffer, "0/%d", info->maxChars);
  info->cEscritos = gtk_label_new(buffer);
  info->maxChars = maxChars;
}*/

EntradaPresion crear_entradapresion() {
  EntradaPresion p;
  p.lbl = gtk_label_new("Presión");
  p.sistEntry = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(p.sistEntry), "Sist");
  gtk_entry_set_width_chars(GTK_ENTRY(p.sistEntry), 5);
  gtk_entry_set_max_length(GTK_ENTRY(p.sistEntry), 4);
  p.diastEntry = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(p.diastEntry), "Diast");
  gtk_entry_set_width_chars(GTK_ENTRY(p.diastEntry), 5);
  gtk_entry_set_max_length(GTK_ENTRY(p.diastEntry), 4);

  return p;
}

void cargar_consulta_registro(){
  long posArch;
  Consultas registro;
  GtkTreeModel *mode;
  GtkTreeIter iter;
  FILE *apArch;



}

void crear_formulario_consulta(Opc modo) {
  crear_ventana(&cForm.baseForm, 1000, 400, free_formcons);

  crear_entradatexto(&cForm.nomPac, "Nombre Paciente", 10, 50);
  crear_entradatexto(&cForm.edad, "Edad", 3, 3);
  crear_entradatexto(&cForm.peso, "Peso", 3, 4);
  crear_entradatexto(&cForm.altura, "Altura", 4, 4);
  crear_entradatexto(&cForm.nomDr, "Doctor", 10, 50);
  crear_entradatexto(&cForm.nomDr, "Doctor", 10, 50);

  crear_entradafecha(&cForm.fConsulta, "Fecha Consulta");

  //crear_entradatextv(&cForm.sintomas, "Síntomas", 5);

  cForm.presion = crear_entradapresion();

  cForm.warningLbl = gtk_label_new("");

  crear_boton(&cForm.aceptBtn, "Aceptar", no_callback);
  crear_boton(&cForm.aceptBtn, "Cancelar", free_formcons);

  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.nomPac.lbl, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.nomPac.entry, 1, 0, 4, 1);

  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.edad.lbl, 0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.edad.entry, 1, 1, 1, 1);

  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.peso.lbl, 2, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.peso.entry, 3, 1, 1, 1);

  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.altura.lbl, 4, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.altura.entry, 5, 1, 1, 1);

  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.presion.lbl, 0, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.presion.sistEntry, 1, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.presion.diastEntry, 2, 2, 1, 1);

  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.temp.lbl, 3, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.temp.entry, 4, 2, 1, 1);

  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.sintomas.lbl, 0, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(cForm.baseForm.grid), cForm.sintomas.textV, 0, 4, 10, 6);

  gtk_widget_show_all(cForm.baseForm.win);
}

void agregar_consulta(){}