#include "reportes.h"

ListView reporte;
rDatosPaciente paciente;

void crear_bar_reportes(BarReportes *bar) {
  char buffer[61];
  bar->grid = gtk_grid_new();
  sprintf(buffer, "Paciente: %s", paciente.nombre);
  bar->pNomLbl = gtk_label_new(buffer);
  crear_entradafecha(&bar->rangoIn, "Fecha inico");
  crear_entradafecha(&bar->rangoFin, "Fecha fin");
  bar->promLbl = gtk_label_new("Promedios\n");
  crear_boton(&bar->btn, "Generar", no_callback);

  gtk_grid_attach(GTK_GRID(bar->grid), bar->pNomLbl, 0, 0, 1, 1);

  gtk_grid_attach(GTK_GRID(bar->grid), bar->rangoIn.titulo, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(bar->grid), bar->rangoIn.anioEntry, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(bar->grid), bar->rangoIn.mesCombox, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(bar->grid), bar->rangoIn.diaCombox, 0, 0, 1, 1);

  gtk_grid_attach(GTK_GRID(bar->grid), bar->rangoFin.titulo, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(bar->grid), bar->rangoFin.anioEntry, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(bar->grid), bar->rangoFin.mesCombox, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(bar->grid), bar->rangoFin.diaCombox, 0, 0, 1, 1);

  gtk_grid_attach(GTK_GRID(bar->grid), bar->promLbl, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(bar->grid), bar->btn, 0, 0, 1, 1);
}

void crear_reporte(GtkWidget *btn, gpointer data) {
  long pos;
  FILE *apArch;
  Buffer buffer;
  GtkTreeIter iter;
  Consultas datosReporte;
  Criterios conteo = {{0, 0}, {0, 0}, {0, 0}};
  guint handler_id = crear_ventana_listv(&reporte.baseVentana, 400, 800);
  g_signal_handler_disconnect(G_OBJECT(reporte.baseVentana.win), handler_id);

  crear_bar_reportes(&reporte.barR);
  gtk_box_pack_start(GTK_BOX(reporte.baseVentana.box), reporte.barR.grid, TRUE,
                     TRUE, 0);

  reporte.listStore = gtk_list_store_new(
      6, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
      G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

  sprintf(buffer.dirArch, "../data/consultas/%s.dat", paciente.curp);
  apArch = fopen(buffer.dirArch, "rb");
  if (apArch == NULL) {
    g_print("ERROR: No se pudo abrir archivo");
    return;
  }

  while (fread(&datosReporte, sizeof(Consultas), 1, apArch)) {
    if (datosReporte.edo) {
      conteo.imc.prom += (datosReporte.peso / datosReporte.altura);
      conteo.imc.numD++;
      conteo.peso.prom += datosReporte.peso;
      conteo.peso.numD++;
      conteo.temp.prom += datosReporte.temp;
      conteo.temp.numD++;

      sprintf(buffer.fecha, "%02d/%02d/%04d", datosReporte.fecha.dia,
              datosReporte.fecha.mes, datosReporte.fecha.anio);
      sprintf(buffer.presion, "%d/%d", datosReporte.presion.diasto,
              datosReporte.presion.sist);
      sprintf(buffer.temp, "%02.1f °C", datosReporte.temp);
      sprintf(buffer.imc, "%02.1f", datosReporte.peso / datosReporte.altura);
      sprintf(buffer.altura, "%.1f m", datosReporte.altura);
      sprintf(buffer.peso, "%.1f kg", datosReporte.peso);

      gtk_list_store_append(reporte.listStore, &iter);
      gtk_list_store_set(reporte.listStore, &iter, 0, buffer.fecha, 1,
                         buffer.presion, 2, buffer.temp, 3, buffer.imc, 4,
                         buffer.altura, 5, buffer.peso, -1);
    }
  }
  fclose(apArch);

  conteo.imc.prom /= conteo.imc.numD;
  conteo.peso.prom /= conteo.peso.numD;
  conteo.temp.prom /= conteo.temp.numD;

  // Se usa dirArch pero es formato para el lbl de los promedios
  sprintf(buffer.dirArch, "Primerdios\nTemperatura: %.2f IMC: %.2f Peso: %.2f",
          conteo.temp.prom, conteo.imc.prom, conteo.peso.prom);
  gtk_label_set_text(GTK_LABEL(reporte.barR.promLbl), buffer.dirArch);
}
