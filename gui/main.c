#include <gtk/gtk.h>
#include <X11/Xlib.h>

void	destroy(void)
{
  gtk_main_quit();
}

int		main(int argc, char *argv[])
{
  GtkWidget	*window;
  GtkWidget	*button;
  GtkWidget	*frame;

  gtk_init (&argc, &argv);
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(window), "ARDrone2.0 API");
  /* gtk_window_set_decorated(GTK_WINDOW(window), FALSE); */
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
  frame = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), frame);

  gtk_widget_show(window);
  gtk_signal_connect (GTK_OBJECT (window), "destroy",
		      GTK_SIGNAL_FUNC (destroy), NULL);
  gtk_main();
  return (0);
}
