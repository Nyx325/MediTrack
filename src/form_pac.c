#include "form_pac.h"
#include "general.h"
#include "listv.h"
#include <stdio.h>
#include <string.h>

typedef struct {
  BaseForm basesVentana;
  EntradaTexto curp;
  EntradaTexto nombre;
  EntradaFecha fechaN;
  EntradaTexto telf;
  EntradaCombox tSangre;
  EntradaCombox sexo;
  EntradaFecha primCons;
  GtkWidget *warningLbl;
  GtkWidget *acepBtn;
  GtkWidget *cancelBtn;
} PacForm;

PacForm pForm;

// Opc modo; //1 para modificar, 0 para agregar

void free_PacForm(GtkWidget *widget, gpointer data) {
  gtk_widget_hide(pForm.basesVentana.win);

  if (pForm.acepBtn != NULL)
    gtk_widget_destroy(pForm.acepBtn);
  if (pForm.cancelBtn != NULL)
    gtk_widget_destroy(pForm.cancelBtn);

  free_entradatexto(&pForm.curp);
  free_entradatexto(&pForm.nombre);
  free_entradatexto(&pForm.telf);

  free_entradafecha(&pForm.primCons);
  free_entradafecha(&pForm.fechaN);

  free_entradacombox(&pForm.tSangre);
  free_entradacombox(&pForm.sexo);

  free_baseform(&pForm.basesVentana);

  pForm.warningLbl = NULL;
  pForm.acepBtn = NULL;
  pForm.cancelBtn = NULL;
}

void cargar_de_registro() {
  long posArch;
  char anio[5];
  Pacientes registro;
  GtkTreeModel *model;
  GtkTreeIter iter;
  FILE *apArch = fopen("../data/pacientes.dat", "rb");
  if (apArch == NULL) {
    g_print("ERROR: Archivo dañado");
    return;
  }

  if (gtk_tree_selection_get_selected(tabla.filaActual, &model, &iter) ==
      FALSE) {
    free_PacForm(NULL, NULL);
    return;
  }

  gtk_tree_model_get(model, &iter, 7, &posArch, -1);

  fseek(apArch, posArch, SEEK_SET);
  fread(&registro, sizeof(Pacientes), 1, apArch);
  fclose(apArch);

  gtk_entry_set_text(GTK_ENTRY(pForm.nombre.entry), registro.nombre);
  gtk_entry_set_text(GTK_ENTRY(pForm.curp.entry), registro.CURP);
  gtk_entry_set_text(GTK_ENTRY(pForm.telf.entry), registro.telf);

  // Fecha de nacimiento
  sprintf(anio, "%4d", registro.fechas.anio);
  gtk_entry_set_text(GTK_ENTRY(pForm.fechaN.anioEntry), anio);
  gtk_combo_box_set_active(GTK_COMBO_BOX(pForm.fechaN.mesCombox),
                           registro.fechas.mes);
  gtk_combo_box_set_active(GTK_COMBO_BOX(pForm.fechaN.diaCombox),
                           registro.fechas.dia);

  // Fecha primer consulta
  sprintf(anio, "%4d", registro.fechasC.anio);
  gtk_entry_set_text(GTK_ENTRY(pForm.primCons.anioEntry), anio);

  gtk_combo_box_set_active(GTK_COMBO_BOX(pForm.tSangre.combox),
                           formatear_tsangre_num(registro.tpSangre));

  if (registro.sexo == 'H')
    gtk_combo_box_set_active(GTK_COMBO_BOX(pForm.sexo.combox), 1);
}

void pac_crear_form(Opc modo) {
  crear_ventana(&pForm.basesVentana, 611, 220, free_PacForm);

  crear_entradatexto(&pForm.nombre, "Nombre", 49, 49);
  crear_entradatexto(&pForm.curp, "CURP", 18, 18);
  crear_entradatexto(&pForm.telf, "Teléfono", 10, 10);

  crear_entradafecha(&pForm.fechaN, "Fecha Nacimiento");
  crear_entradafecha(&pForm.primCons, "Primer Consulta");

  const gchar *sexoOpc[] = {"M", "H"};
  crear_entradacombox(&pForm.sexo, "Sexo", sexoOpc, G_N_ELEMENTS(sexoOpc));
  const gchar *tipos[] = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};
  crear_entradacombox(&pForm.tSangre, "T. Sangre", tipos, G_N_ELEMENTS(tipos));

  pForm.warningLbl = gtk_label_new("");
  crear_boton(&pForm.acepBtn, "Aceptar", NULL);
  crear_boton(&pForm.cancelBtn, "Cancelar", free_PacForm);

  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.nombre.lbl, 0, 0, 2,
                  1);
  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.nombre.entry, 2, 0,
                  3, 1);

  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.curp.lbl, 5, 0, 1,
                  1);
  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.curp.entry, 6, 0, 2,
                  1);

  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.fechaN.titulo, 0, 1,
                  2, 1);
  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.fechaN.anioEntry, 2,
                  1, 1, 1);
  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.fechaN.mesCombox, 3,
                  1, 1, 1);
  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.fechaN.diaCombox, 4,
                  1, 1, 1);

  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.telf.lbl, 5, 1, 1,
                  1);
  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.telf.entry, 6, 1, 2,
                  1);

  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.tSangre.lbl, 0, 2, 1,
                  1);
  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.tSangre.combox, 1, 2,
                  1, 1);

  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.sexo.lbl, 2, 2, 1,
                  1);
  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.sexo.combox, 3, 2, 1,
                  1);

  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.primCons.titulo, 4,
                  2, 1, 1);
  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.primCons.anioEntry,
                  5, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.primCons.mesCombox,
                  6, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.primCons.diaCombox,
                  7, 2, 1, 1);

  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.warningLbl, 0, 3, 8,
                  3);

  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.acepBtn, 0, 4, 4, 3);
  gtk_grid_attach(GTK_GRID(pForm.basesVentana.grid), pForm.cancelBtn, 5, 4, 3,
                  3);

  if (modo)
    cargar_de_registro();

  gtk_widget_show_all(pForm.basesVentana.win);
}

void mostrar_pacientes(char *archivoDir) {
  char fechaFormato[2][12];
  GtkTreeIter iter; // estructura para identificar fila en modelo

  // apuntador definido en listv.c para el modelo de la tabla
  tabla.listStore = gtk_list_store_new(
      8, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
      G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_ULONG);

  FILE *apPaci;
  Pacientes paciente;

  apPaci = fopen(archivoDir, "a+b");
  if (apPaci == NULL) {
    g_print("Archivo danaño\n");
    return;
  }

  long pos;

  while (fread(&paciente, sizeof(Pacientes), 1, apPaci)) {
    if (paciente.estado) {
      // Crear cadenas para fechas
      sprintf(fechaFormato[0], "%02d/%02d/%04d", paciente.fechas.dia,
              paciente.fechas.mes, paciente.fechas.anio);
      sprintf(fechaFormato[1], "%02d/%02d/%04d", paciente.fechasC.dia,
              paciente.fechasC.mes, paciente.fechasC.anio);
      // Formatear el sexo de igual forma
      char sexo[2] = {paciente.sexo, '\0'};

      // Obtener posición en archivo del registro
      pos = ftell(apPaci) - sizeof(Pacientes);

      gtk_list_store_append(tabla.listStore, &iter); // agregar fila nueva
      // Agregar datos al modelo
      gtk_list_store_set(tabla.listStore, &iter, 0, paciente.CURP, 1,
                         paciente.nombre, 2, fechaFormato[0], 3, sexo, 4,
                         paciente.telf, 5, paciente.tpSangre, 6,
                         fechaFormato[1], 7, pos, -1);
    }
  }
  fclose(apPaci);

  char *titulos[] = {
      "CURP",     "Nombre",         "Fecha de nacimineto",  "Sexo",
      "Teléfono", "Tipo sanguineo", "Fecha primer consulta"};

  listview_importmodel(7, titulos);
}

char *formatear_curp(const char *input) {
  gsize i, tam = g_utf8_strlen(input, -1);
  gchar *formateo = g_strdup(input); // Copia la cadena de entrada
  gunichar character;

  if (tam != 18)
    return NULL;

  for (i = 0; i < 4; i++) {
    character = g_utf8_get_char(&formateo[i]);
    if (!g_unichar_isalpha(character))
      return NULL;
    else
      formateo[i] = g_unichar_totitle(character);
  }

  for (i = 4; i < 10; i++) {
    character = g_utf8_get_char(&formateo[i]);
    if (!g_unichar_isdigit(character))
      return NULL;
    else
      formateo[i] = character;
  }

  for (i = 10; i < tam; i++) {
    character = g_utf8_get_char(&formateo[i]);
    if (!g_unichar_isalnum(character))
      return NULL;

    if (g_unichar_isalpha(character))
      formateo[i] = g_unichar_totitle(character);
    else
      formateo[i] = character;
  }

  return g_strdup(formateo);
}

const gchar *formatear_tsangre(GtkComboBox *combox) {
  int ind = gtk_combo_box_get_active(GTK_COMBO_BOX(combox));
  switch (ind) {
  case 0:
    return NULL;
  case 1:
    return "A+";
  case 2:
    return "A-";
  case 3:
    return "B+";
  case 4:
    return "B-";
  case 5:
    return "AB+";
  case 6:
    return "AB-";
  case 7:
    return "O+";
  case 8:
    return "O-";
  default:
    return NULL;
  }
}

gunichar formatear_sexo(GtkComboBoxText *combox) {
  gchar *formateo = gtk_combo_box_text_get_active_text(combox);
  gunichar sexo = g_utf8_get_char(&formateo[0]);
  return sexo;
}

typedef struct {
  TextoIngresado nombre;
  TextoIngresado curp;
  TextoIngresado telefono;
  FechaIngresada fechaN;
  FechaIngresada primerCons;
  const gchar *tpSangre;
} DatosFormulario;

Pacientes validar_formulario_pacientes() {
  GString *err = g_string_new("");
  Pacientes registro;
  DatosFormulario captura;
  WidgetsFecha widFecha;

  registro.estado = 0;

  capturar_formatear_texto(&captura.nombre, registro.nombre, formatear_nombre,
                           pForm.nombre.entry, &err, "Nombre");
  capturar_formatear_texto(&captura.curp, registro.CURP, formatear_curp,
                           pForm.curp.entry, &err, "CURP");
  capturar_formatear_texto(&captura.telefono, registro.telf, formatear_telf,
                           pForm.telf.entry, &err, "Teléfono");

  captura.fechaN.anio = gtk_entry_get_text(GTK_ENTRY(pForm.fechaN.anioEntry));
  if (is_full_nums(captura.fechaN.anio, 4, 4) == FALSE)
    agregar_err("Fecha", &err);
  else
    registro.fechas.anio = atoi(captura.fechaN.anio);

  widFecha.anioEntry = GTK_ENTRY(pForm.fechaN.anioEntry);
  widFecha.mesCombox = GTK_COMBO_BOX(pForm.fechaN.mesCombox);
  widFecha.diaCombox = GTK_COMBO_BOX(pForm.fechaN.diaCombox);
  capturar_formatear_fecha(&captura.fechaN, &widFecha, &registro.fechas, &err,
                          "de nacimiento");

  widFecha.anioEntry = GTK_ENTRY(pForm.primCons.anioEntry);
  widFecha.mesCombox = GTK_COMBO_BOX(pForm.primCons.mesCombox);
  widFecha.diaCombox = GTK_COMBO_BOX(pForm.primCons.diaCombox);
  capturar_formatear_fecha(&captura.fechaN, &widFecha, &registro.fechasC, &err,
                          "de nacimiento");

  captura.tpSangre = formatear_tsangre(GTK_COMBO_BOX(pForm.tSangre.combox));
  if (captura.tpSangre == NULL)
    agregar_err("Tipo de sangre", &err);
  else
    strcpy(registro.tpSangre, captura.tpSangre);

  //registro.sexo = formatear_sexo(GTK_COMBO_BOX_TEXT(pForm.sexo.combox));

  if (err->len != 0) {
    g_string_append(err, " no válido(s)");
    gtk_label_set_markup(GTK_LABEL(pForm.warningLbl), err->str);
  } else
    registro.estado = 1;

  return registro;
}

void registrar_datos_paciente(GtkWidget *btn, gpointer data) {
  Pacientes registro = validar_formulario_pacientes();

  g_print("Nom: %s\nCurp: %s\n", registro.nombre, registro.CURP);
  g_print("FechaN %d/%d/%d\n", registro.fechasC.dia, registro.fechasC.mes,
          registro.fechasC.anio);
  g_print("Sexo: %c Tel: %s\n", registro.sexo, registro.telf);
  g_print("TSangre: %s ", registro.tpSangre);
  g_print("Fecha1C: %d/%d/%d\n\n", registro.fechasC.dia, registro.fechasC.mes,
          registro.fechasC.anio);
}

void pac_agregar_callback(GtkWidget *btn, gpointer data) {
  desconectar_señal_btn(&pForm.acepBtn);
  pac_crear_form(0);
  g_signal_connect(G_OBJECT(pForm.acepBtn), "clicked",
                   G_CALLBACK(registrar_datos_paciente), NULL);
}

void pac_mod_callback(GtkWidget *btn, gpointer data) { pac_crear_form(1); }
