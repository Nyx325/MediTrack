#include "form_prov.h"

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

  if (!prForm.narcoticosCheckBtn)
    gtk_widget_destroy(prForm.narcoticosCheckBtn);
  if (!prForm.warningLbl)
    gtk_widget_destroy(prForm.warningLbl);
  if (!prForm.aceptBtn)
    gtk_widget_destroy(prForm.aceptBtn);
  if (!prForm.cancelBtn)
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

void cargar_proveedor_registro(){
    long posArch;
    char anioPermiso[5];
    
}

void prov_crear_form() {
  crear_ventana(&prForm.baseVentana, 611, 220, free_provform);

  crear_entradatexto(&prForm.nomComercial, "Nombre Comercial", 30, 100);
  crear_entradatexto(&prForm.nomFactura, "Nombre Factura", 30, 100);
  crear_entradatexto(&prForm.rfc, "RFC", 13, 13);
  crear_entradatexto(&prForm.numOficina, "Num. Oficina", 10, 10);
  crear_entradatexto(&prForm.wsp, "Whatsapp", 10, 10);
  crear_entradatexto(&prForm.correo, "Correo", 20, 100);
  crear_entradatexto(&prForm.repComercial, "Representante Comercial", 30, 30);

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

  // Apartado de carga de datos según sea el caso(?)

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

  listview_importmodel(10, titulos);
}
