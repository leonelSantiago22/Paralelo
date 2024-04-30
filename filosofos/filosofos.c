
/*gcc -o filosofos filosofos.c -Wall  `pkg-config  --cflags --libs  gtk+-3.0` -lm -export-dynamic */
#include <gtk/gtk.h> 
#include <gdk/gdk.h>
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cairo.h>

struct stfilosofos{
    int num;
    int px,py;
    cairo_surface_t *img;
};
typedef struct stfilosofos STFILOSOFOS;

STFILOSOFOS filosofos[5];

int bejecutar = FALSE;

GtkWidget *window; 
GtkWidget *draw1;
GtkWidget *btnEjecutar;
cairo_surface_t *img1, *img2;

// Declare functions before they are used
void on_Salir_clicked();
void on_btnEjecutar_clicked();
gboolean on_draw1_draw(GtkDrawingArea *widget, cairo_t *cr);
void ini_filosofos(void);

int main(int argc, char *argv[])
{
    GtkBuilder *builder;
    
    gtk_init(&argc,&argv);
    
    img1 = cairo_image_surface_create_from_png("dormir.png");
    img2 = cairo_image_surface_create_from_png("comer.png");
    
    builder = gtk_builder_new();
    
    gtk_builder_add_from_file(builder,"filosofos.glade", NULL);
    
    window = GTK_WIDGET(gtk_builder_get_object(builder,"window")); 
    draw1 = GTK_WIDGET(gtk_builder_get_object(builder,"draw1"));
    btnEjecutar = GTK_WIDGET(gtk_builder_get_object(builder,"btnEjecutar"));
    
    
    gtk_builder_connect_signals(builder,NULL);
    
    gtk_widget_show(window);
    
    gtk_main();
    
    cairo_surface_destroy(img1);
    cairo_surface_destroy(img2);
    
    return 0;
}

void on_Salir_clicked(){
    gtk_main_quit();
}

void on_btnEjecutar_clicked()
{
    bejecutar = TRUE;
    ini_filosofos();
    gtk_widget_hide(btnEjecutar);
}

gboolean on_draw1_draw(GtkDrawingArea *widget, cairo_t *cr)
{
    int i;
    
    if(bejecutar)
    {
        for(i=0; i<5; i++)
        {
            cairo_pattern_t *pattern = cairo_pattern_create_for_surface(filosofos[i].img);
            cairo_set_source(cr, pattern);
            cairo_paint(cr);
            cairo_pattern_destroy(pattern);
        }
    }
    
    return FALSE;
}

void ini_filosofos(void)
{
    int i;
    
    for(i=0; i<5; i++)
    {
        filosofos[i].num=i;
        filosofos[i].px = (120 + 80 * sin((72*i)));
        filosofos[i].py = (120 + 80 * cos((72*i)/(180/3.1416)));
        filosofos[i].img = img1;
    }
}
