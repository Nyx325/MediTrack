#ifndef LISTV_BAR_H
#define LISTV_BAR_H

#include "general.h"

typedef struct {
  GtkWidget *box;
  GtkWidget *lbl;
  BtnBase base;
} BarBtn;

typedef struct {
  GtkWidget *mainbox;
  BarBtn agregar;
  BarBtn modificar;
  BarBtn eliminar;
  GtkWidget *separador;
  GtkWidget *entrys[2];
  BtnBase backBtn;
  BtnBase searchBtn;
} BarListv;

// extern BarListv bar;

void      free_barlistv      (BarListv *bar);
BarListv  crear_bar          (void);
void      poner_plaholders   (char *phEntry1, char *phEntry2, BarListv *bar);
void      crear_btn_img      (BtnBase *btn, char *imgPath);

#endif
