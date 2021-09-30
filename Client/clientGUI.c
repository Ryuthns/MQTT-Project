// $ sudo apt-get install libgtk-3-dev
/*
 - gcc include flags: `pkg-config --cflags gtk+-3.0`
 - gcc library flags: `pkg-config --libs gtk+-3.0`

 $ gcc -Wall -g new_gui.c -o new_gui -lmosquitto -lpthread  \
    `pkg-config --cflags gtk+-3.0` \
    `pkg-config --libs gtk+-3.0`
*/ 
////////////////////////////////////////////////////////////////
#include <inttypes.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "mosq_sub.c"

GtkWidget *window,*window2;
GtkWidget *box, *grid, *vbox, *vbox2, *hbox1, *hbox2 ,*hbox3 ;
GtkWidget *img1, *img2, *img3 ;
GtkWidget *button1,*button2;
GtkWidget *label1, *label2, *label3,*label4, *label5, *label6 ;

//static uint32_t counter = 0;
static gboolean counter_enabled = FALSE;

bool clean_session = true;
struct mosquitto *mosq = NULL;

char *name_cam1,temp_str[100] ;


static gboolean name_pic( gpointer data ) {
	if(counter_enabled)
	{
		if(strstr(cam1,"cam1"))
        {   
			strcpy(temp_str,cam1);
			name_cam1 = strtok(temp_str," = ");
			name_cam1 = strtok(NULL," = ");
            gtk_widget_override_font(label4,
                                pango_font_description_from_string("Tahoma 20"));
            gtk_label_set_text(GTK_LABEL(label4),name_cam1);
			memset(temp_str,NULL,sizeof(temp_str));
			memset(name_cam1,NULL,sizeof(name_cam1));
			/* cam = 25-09-2021_17-14-49 */

			//g_print("1\n");
			sprintf(temp_str,"negative_images/neg-%.4d.jpg",run_cou1);
			//g_print("name = %s\n",temp_str);
			gtk_image_set_from_file(GTK_IMAGE(img1), temp_str);
			memset(temp_str,NULL,sizeof(temp_str));
			
        }
		if(strstr(cam2,"cam2"))
        {   
			strcpy(temp_str,cam2);
			name_cam1 = strtok(temp_str," = ");
			name_cam1 = strtok(NULL," = ");
            gtk_widget_override_font(label5,
                                pango_font_description_from_string("Tahoma 20"));
            gtk_label_set_text(GTK_LABEL(label5),name_cam1);
			memset(temp_str,NULL,sizeof(temp_str));
			memset(name_cam1,NULL,sizeof(name_cam1));

			//g_print("2\n");
			sprintf(temp_str,"negative_images/neg-%.4d.jpg",run_cou2);
			//g_print("name = %s\n",temp_str);
			gtk_image_set_from_file(GTK_IMAGE(img2), temp_str);
			memset(temp_str,NULL,sizeof(temp_str));
        }
		if(strstr(cam3,"cam3"))
        {   
			strcpy(temp_str,cam3);
			name_cam1 = strtok(temp_str," = ");
			name_cam1 = strtok(NULL," = ");
            gtk_widget_override_font(label6,
                                pango_font_description_from_string("Tahoma 20"));
            gtk_label_set_text(GTK_LABEL(label6),name_cam1);
			memset(temp_str,NULL,sizeof(temp_str));
			memset(name_cam1,NULL,sizeof(name_cam1));

			//g_print("3\n");
			sprintf(temp_str,"negative_images/neg-%.4d.jpg",run_cou3);
			//g_print("name = %s\n",temp_str);
			gtk_image_set_from_file(GTK_IMAGE(img3), temp_str);
			memset(temp_str,NULL,sizeof(temp_str));
        }

	}

	return TRUE; 
}

static void button1_callback( GtkWidget *widget, gpointer data ) {
	counter_enabled = !counter_enabled ;
	gtk_button_set_label( data,
			counter_enabled ? "Stop" : "Start" );

}

static void activate( GtkApplication *app, gpointer user_data ) {

    window = gtk_application_window_new( app );
	// set the title of the application window
	gtk_window_set_title( GTK_WINDOW(window), "smk Demo" );
	// set the default window size (width x height) in pixels
	gtk_window_set_default_size( GTK_WINDOW(window), 200, 160 );
	// set window position
	gtk_window_set_position( GTK_WINDOW(window), GTK_WIN_POS_CENTER );
	// set window border width
	gtk_container_set_border_width( GTK_CONTAINER(window), 4 );


	vbox = gtk_vbox_new( 
		FALSE, 5 /*spacing*/ );
	// add the box to the application window
	gtk_container_add( GTK_CONTAINER(window), vbox );

	hbox1 = gtk_hbox_new(TRUE,2);
	gtk_box_pack_start(GTK_BOX(vbox),hbox1,TRUE,TRUE,0);

	hbox2 = gtk_hbox_new(TRUE,2);
	gtk_box_pack_start(GTK_BOX(vbox),hbox2,TRUE,TRUE,0);

	hbox3 = gtk_hbox_new(TRUE,2);
	gtk_box_pack_start(GTK_BOX(vbox),hbox3,TRUE,TRUE,0);

	{// GTK img
	img1 = gtk_image_new_from_file("1negative_images/neg-0002.jpg");
    gtk_container_add(GTK_CONTAINER(hbox1), img1);
    gtk_box_pack_start(GTK_BOX(hbox1), img1, FALSE, TRUE, 2);

	img2 = gtk_image_new_from_file("1negative_images/neg-0003.jpg");
    gtk_container_add(GTK_CONTAINER(hbox1), img2);
    gtk_box_pack_start(GTK_BOX(hbox1), img2, FALSE, TRUE, 2);

	img3 = gtk_image_new_from_file("1negative_images/neg-0002.jpg");
    gtk_container_add(GTK_CONTAINER(hbox1), img3);
    gtk_box_pack_start(GTK_BOX(hbox1), img3, FALSE, TRUE, 2);
	}
	
	{// GTK label
	label1 = gtk_label_new_with_mnemonic("cam1");
    gtk_widget_override_font(label1,
                            pango_font_description_from_string("Tahoma 20"));
    gtk_widget_set_size_request(label1,260,40);
    gtk_box_pack_start( GTK_BOX(hbox2),label1 , 
		FALSE /*exapnd*/, TRUE /*fill*/, 1 /*padding*/ );

	label4 = gtk_label_new_with_mnemonic("00-00-00");
    gtk_widget_override_font(label4,
                            pango_font_description_from_string("Tahoma 20"));
    gtk_widget_set_size_request(label4,260,40);
    gtk_box_pack_start( GTK_BOX(hbox3),label4 , 
		FALSE /*exapnd*/, TRUE /*fill*/, 1 /*padding*/ );

	label2 = gtk_label_new_with_mnemonic("cam2");
    gtk_widget_override_font(label2,
                            pango_font_description_from_string("Tahoma 20"));
    gtk_widget_set_size_request(label2,260,40);
    gtk_box_pack_start( GTK_BOX(hbox2),label2 , 
		FALSE /*exapnd*/, TRUE /*fill*/, 2 /*padding*/ );

	label5 = gtk_label_new_with_mnemonic("00-00-00");
    gtk_widget_override_font(label5,
                            pango_font_description_from_string("Tahoma 20"));
    gtk_widget_set_size_request(label5,260,40);
    gtk_box_pack_start( GTK_BOX(hbox3),label5 , 
		FALSE /*exapnd*/, TRUE /*fill*/, 1 /*padding*/ );

	label3 = gtk_label_new_with_mnemonic("cam3");
    gtk_widget_override_font(label3,
                            pango_font_description_from_string("Tahoma 20"));
    gtk_widget_set_size_request(label3,260,40);
    gtk_box_pack_start( GTK_BOX(hbox2),label3 , 
		FALSE /*exapnd*/, TRUE /*fill*/, 3 /*padding*/ );

	label6 = gtk_label_new_with_mnemonic("00-00-00");
    gtk_widget_override_font(label6,
                            pango_font_description_from_string("Tahoma 20"));
    gtk_widget_set_size_request(label6,260,40);
    gtk_box_pack_start( GTK_BOX(hbox3),label6 , 
		FALSE /*exapnd*/, TRUE /*fill*/, 1 /*padding*/ );
	}

	button1 = gtk_button_new_with_label( "Start" );
	g_signal_connect( button1, "clicked",
		G_CALLBACK(button1_callback), button1 );
    gtk_box_pack_start( GTK_BOX(vbox), button1, 
		FALSE /*exapnd*/, FALSE /*fill*/, 4 /*padding*/ );

    gtk_widget_show_all( window );
}

int main( int argc,char **argv ) {

    mosq = mosquitto_new( NULL, clean_session, NULL );
    to_connect_mqtt( mosq , clean_session);

    //---------------------------------------

    GtkApplication *app;
	app = gtk_application_new( NULL, G_APPLICATION_FLAGS_NONE );

	g_timeout_add_seconds( 1 /*sec*/, G_SOURCE_FUNC(name_pic), NULL );
  
	g_signal_connect( app, "activate", 
		G_CALLBACK(activate), NULL );
	// start the application main loop (blocking call)
    
	g_application_run( G_APPLICATION(app), argc, argv );

	// decrease the reference count to the object
	g_object_unref( app );

    
	return 0;
}
