#include "listv_bar.h"
#include "menu.h"
#include "general.h"

// BarListv bar;

void free_barbtn_con_texto(BarBtn *bBtn) {
  if (!bBtn->box)
    gtk_widget_destroy(bBtn->box);
  if (!bBtn->lbl)
    gtk_widget_destroy(bBtn->lbl);

  free_basebtn(&(bBtn->base));

  bBtn->box = NULL;
  bBtn->lbl = NULL;
}

void free_barlistv(BarListv *bar) {
  ushort i;
  if (!bar->mainbox)
    gtk_widget_destroy(bar->mainbox);
  if (!bar->separador)
    gtk_widget_destroy(bar->separador);

  for (i = 0; i < 2; i++)
    if (!bar->entrys[i])
      gtk_widget_destroy(bar->entrys[i]);

  free_barbtn_con_texto(&bar->agregar);
  free_barbtn_con_texto(&bar->modificar);
  free_barbtn_con_texto(&bar->eliminar);

  free_basebtn(&bar->backBtn);
  free_basebtn(&bar->searchBtn);

  bar->mainbox = NULL;
  bar->separador = NULL;
}

void crear_btn_imglbl(BarBtn *btn, char *imgPath, char *titulo) {
  btn->base.img = gtk_image_new_from_file(imgPath);
  btn->lbl = gtk_label_new(titulo);
  btn->box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
  gtk_box_pack_start(GTK_BOX(btn->box), btn->base.img, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(btn->box), btn->lbl, FALSE, FALSE, 0);
  btn->base.btn = gtk_button_new();
  gtk_container_add(GTK_CONTAINER(btn->base.btn), btn->box);
}

void volver_menu(GtkWidget *btn, gpointer data) {
  crear_menu();
  free_listview(NULL, NULL);
}

void poner_plaholders(char *phEntry1, char *phEntry2, BarListv *bar) {
  gtk_entry_set_placeholder_text(GTK_ENTRY(bar->entrys[0]), phEntry1);
  gtk_entry_set_placeholder_text(GTK_ENTRY(bar->entrys[1]), phEntry2);
}

BarListv crear_bar() {
  BarListv bar;
  bar.mainbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  bar.separador = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);

  crear_btn_imglbl(&bar.agregar, "../images/add.png", "Agregar");
  crear_btn_imglbl(&bar.modificar, "../images/edit.png", "Modificar");
  crear_btn_imglbl(&bar.eliminar, "../images/delete.png", "Eliminar");

  crear_btn_img(&bar.backBtn, "../images/back.png");
  g_signal_connect(G_OBJECT(bar.backBtn.btn), "clicked",
                   G_CALLBACK(volver_menu), NULL);

  crear_btn_img(&bar.searchBtn, "../images/search.png");

  bar.entrys[0] = gtk_entry_new();
  bar.entrys[1] = gtk_entry_new();

  gtk_box_pack_start(GTK_BOX(bar.mainbox), bar.backBtn.btn, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(bar.mainbox), bar.agregar.base.btn, FALSE, FALSE,
                     0);
  gtk_box_pack_start(GTK_BOX(bar.mainbox), bar.modificar.base.btn, FALSE, FALSE,
                     0);
  gtk_box_pack_start(GTK_BOX(bar.mainbox), bar.eliminar.base.btn, FALSE, FALSE,
                     0);
  gtk_box_pack_start(GTK_BOX(bar.mainbox), bar.separador, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(bar.mainbox), bar.entrys[0], TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(bar.mainbox), bar.entrys[1], TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(bar.mainbox), bar.searchBtn.btn, FALSE, FALSE, 0);

  return bar;
}
