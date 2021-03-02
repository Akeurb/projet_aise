#include <gtk/gtk.h>
#include "sensors.c"
#include "sensors2.c"

GdkPixbuf *create_pixbuf(const gchar * filename) {

   GdkPixbuf *pixbuf;
   GError *error = NULL;
   pixbuf = gdk_pixbuf_new_from_file(filename, &error);

   if (!pixbuf) {

      fprintf(stderr, "%s\n", error->message);
      g_error_free(error);
   }

   return pixbuf;
}

int main(int argc, char *argv[]) {
  char* DATE;
  char* TEMPS;
  char* MEM;
  char* MEM2;
  char* SWAP;
  char* PROC;
  DATE = malloc(100 * sizeof (char));
  TEMPS = malloc(100 * sizeof (char));
  MEM2 = malloc(100 * sizeof (char));
	MEM = malloc(100 * sizeof (char));
  SWAP = malloc(1000 * sizeof (char));
  PROC = malloc(1000 * sizeof (char));
  printf("DATE = %s\n",DATE);
  printf("TEMPS = %s\n",TEMPS);
  printf("MEM = %s\n",MEM);
  printf("MEM2 = %s\n",MEM2);
  printf("SWAP = %s\n",SWAP);
  printf("PROC = %s\n",PROC);
  GtkWidget *window;
  GtkWidget *view;
  GtkWidget *box;
  GdkPixbuf *icon;

  GtkTextBuffer *buffer;
  GtkTextIter start, end;
  GtkTextIter iter;
  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "YATENGAKI");
  int hauteur = 1200;
  int largeur = 600;
  gtk_window_set_default_size(GTK_WINDOW(window), hauteur, largeur);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

  icon = create_pixbuf("index.png");
  gtk_window_set_icon(GTK_WINDOW(window), icon);



  box = gtk_box_new(FALSE, 0);
  view = gtk_text_view_new();
  gtk_box_pack_start(GTK_BOX(box), view, TRUE, TRUE, 0);

  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));

  gtk_text_buffer_create_tag(buffer, "gap", "pixels_above_lines", 0, NULL); // ??
  gtk_text_buffer_create_tag(buffer, "lmarg","left_margin", 100, NULL); // tabulation a gauche
  gtk_text_buffer_create_tag(buffer, "blue_fg", "foreground", "blue", NULL);
  //gtk_text_buffer_create_tag(buffer, "gray_bg", "background", "gray", NULL);
  //gtk_text_buffer_create_tag(buffer, "italic", "style", PANGO_STYLE_ITALIC, NULL);
  gtk_text_buffer_create_tag(buffer, "bold", "weight", PANGO_WEIGHT_BOLD, NULL);

  gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);

  gtk_text_buffer_insert(buffer, &iter, "\n \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tBienvenue dans RETOP\n", -1);

  strcpy(DATE,date2(DATE));
  strcpy(TEMPS,uptime2(TEMPS));

  strcpy(MEM,memory2(MEM,MEM2));
  strcpy(SWAP,swap2(SWAP));
  strcpy(PROC,processinfo2(PROC));

  gtk_text_buffer_insert_with_tags_by_name (buffer, &iter,DATE, -1, "blue_fg", "lmarg",  NULL);
  gtk_text_buffer_insert_with_tags_by_name(buffer, &iter,strcat(TEMPS,"\n"), -1, "blue_fg", "lmarg",  NULL);


  gtk_text_buffer_insert_with_tags_by_name (buffer, &iter,"\nMem info\n"  , -1, "lmarg","bold", NULL);
  gtk_text_buffer_insert_with_tags_by_name (buffer, &iter,MEM, -1, "lmarg", NULL);
  gtk_text_buffer_insert_with_tags_by_name (buffer, &iter,SWAP, -1, "lmarg",  NULL);

  gtk_text_buffer_insert_with_tags_by_name (buffer, &iter,"\nProcess info"  , -1, "lmarg","bold", NULL);
  gtk_text_buffer_insert_with_tags_by_name (buffer, &iter,PROC, -1, "lmarg", NULL);

  gtk_container_add(GTK_CONTAINER(window), box);

  g_signal_connect(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(window);

  g_signal_connect(G_OBJECT(window), "destroy",
      G_CALLBACK(gtk_main_quit), NULL);

  g_object_unref(icon);
  gtk_main();
  return 0;
}
