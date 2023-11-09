// #include "guia.h"
#include "login.h"
#include "form_pac.h"
#include "form_med.h"
#include "form_prov.h"

int main() {
  gtk_init(NULL, NULL);

  //gen_login();
  //gen_formpac();
  //gen_formed();
  gen_formprov();

  gtk_main();
  return 0;
}
