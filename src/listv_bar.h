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
  BarBtn reportes;
  GtkWidget *separador;
  GtkWidget *entrys[2];
  BtnBase backBtn;
  BtnBase searchBtn;
} BarListv;

// extern BarListv bar;
#define BAR_GENERICA 0
#define BAR_PACIENTES 1

void      free_barlistv      (BarListv *bar);
BarListv  crear_bar          (Opc modo);
void      poner_plaholders   (char *phEntry1, char *phEntry2, BarListv *bar);
void      crear_btn_img      (BtnBase *btn, char *imgPath);

#endif
