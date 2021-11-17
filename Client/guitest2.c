// $ sudo apt-get install libgtk-3-dev
/*
gcc -g guitest2.c -o guitest2 -lpaho-mqtt3c -lpthread -lcurl \
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
#include <stdbool.h>
#include <glib.h>
#include <gdk/gdk.h>
#include "sub_mes.c"


GtkApplication *app;
GtkWidget *window, *pic_window ,*tree_window,*mosq_window,*login_window;
GtkWidget *del_window ;
GtkWidget *headerbar , *tree_headerbar , *del_headerbar;
GtkWidget *head_button1 ;

GtkTreeModel *model = NULL;
GtkWidget *sw;

GMenu *mosqmenu;
GMenu *editmenu;

GtkWidget *gearmenubutton;
GtkWidget *gearicon;
GtkWidget *tree_button, *tree_button2;
GtkWidget *sw, *treeview, *box , *hbox;


GtkWidget *head_label,*sub_label1, *sub_label2, *sub_label3,*sub_label4,*label_topic2,*label_topic;
GtkWidget *sub_entry1, *sub_entry2 , *sub_entry3 , *server_entry , *topic_entry;
GtkWidget *sub_button1;

GtkWidget *grid, *sub_grid , *pic_grid;
GtkWidget *pic_box1,*pic_box2,*pic_box3 ;
GtkWidget *img1, *img2, *img3 ,*img_t ;
GtkWidget *main_label1, *main_label2, *main_label3,*main_label4,*main_label5,*main_label6 ;
GtkWidget *main_status ;
GtkWidget *main_button1, *main_button2 ,*main_button3 ;

GtkWidget *server_button1,*topic_button1;
GtkWidget *user_entry,*pass_entry ;
GtkWidget *login_button1,*label_sever2,*label_sever,*label_login,*label_pass,*back_window;
GtkWidget *label_head_server,*label_head_topic;
GtkWidget *label_head_server2,*label_head_topic2;

GtkWidget *del_box, *del_hbox ;
GtkWidget *del_button1 , *del_button2 ,*del_sw ;
GtkWidget *del_tree ;
GtkWidget *delhead_button1 ,*delhead_button2  ;
GtkTreeModel *del_model = NULL;


static gboolean counter_enabled = FALSE;
static gboolean tree_stat = FALSE;
static gboolean win_stat = FALSE;

/*
bool clean_session = true;
struct mosquitto *mosq = NULL;
*/

char *text_entry1,*text_entry2,*text_entry3;
char *user_text , *pass_text ;
char *sp_cam,temp_str[100],lebel_cam[100] ;
char cam_id1[100], cam_id2[100], cam_id3[100];
char cid1[100],cid2[100],cid3[100] ;
char del_text[100] ;

int i = 0;
int run_line ;

MQTTClient client;
MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;

void head_button1_callback( GtkWidget* , gpointer ) ;
void tree_button_callback( GtkWidget* , gpointer ) ;
void tree_button2_callback( GtkWidget* , gpointer ) ;
gboolean
foreach_func(GtkTreeModel *, GtkTreePath *, GtkTreeIter *,gpointer );
void main_button1_callback( GtkWidget* , gpointer ) ;
void main_full_pic( GtkWidget* , gpointer ) ;
void main_button2_callback( GtkWidget* , gpointer ) ;
void sub_button1_callback( GtkWidget* , gpointer ) ;
void server_button( GtkWidget* , gpointer ) ;
void topic_button( GtkWidget* , gpointer ) ;
void login_button( GtkWidget* , gpointer ) ;
void del_button1_callback( GtkWidget* , gpointer ) ;
void del_button2_callback( GtkWidget* , gpointer ) ;
void remove_item(GSimpleAction *, GVariant *, gpointer ) ;

void login_button1_callback( GtkWidget* , gpointer ) ;
void make_del_tree() ;

void activate( GtkApplication* , gpointer ) ;
void sub_activate( GtkApplication* , gpointer ) ;
void main_activate( GtkApplication*, gpointer ) ;

static gboolean name_pic( gpointer );


void add_columns (GtkTreeView *) ;


typedef struct {

    char inDate[100];
    char iD[100];
    char Time[100];

} student;

GtkTreeModel *create_model (student * ) ;

typedef struct {

    char allText[100];

}text_alldate ;

enum {

  COLUMN_DATE,
  COLUMN_ID,
  COLUMN_TIME,
  NUM_COLUMNS

};


const GActionEntry app_actions[] = {
    { "server", server_button },
    { "topic", topic_button },
    { "login", login_button }

};


int main( int argc,char **argv ) {

    to_connect_mqtt(client,conn_opts);

    //---------------------------------------
    
    int status;
	app = gtk_application_new( NULL, G_APPLICATION_FLAGS_NONE );
    g_timeout_add_seconds( 1 /*sec*/, G_SOURCE_FUNC(name_pic), NULL );

	g_signal_connect( app, "activate", 
		G_CALLBACK(activate), NULL );

	g_signal_connect( app, "activate", 
		G_CALLBACK(sub_activate), NULL );

    g_action_map_add_action_entries(G_ACTION_MAP (app), app_actions,
                                  G_N_ELEMENTS (app_actions), NULL);

	status = g_application_run( G_APPLICATION(app), argc, argv );

	g_object_unref( app );


    FILE *fp;
    fp = fopen("data.txt","w");
    fprintf(fp,"");
    fclose(fp);
    

	return status ;
}


void sub_button1_callback( GtkWidget *widget, gpointer data ) {

    GtkWidget *dialog;
    win_stat = TRUE ;
    char number[10] = "123456789" ;
    text_entry1 = gtk_entry_get_text (GTK_ENTRY (sub_entry1));
    text_entry2 = gtk_entry_get_text (GTK_ENTRY (sub_entry2));
    text_entry3 = gtk_entry_get_text (GTK_ENTRY (sub_entry3));

    bool t1=false,t2=false,t3=false ;

    int i=0;
    if(strlen(text_entry1)== 1 && strlen(text_entry2)== 1 && strlen(text_entry3)== 1)
    {
        for(i=0;i<9;i++)
        {
            if(text_entry1[0]==number[i])
            {
                t1 = true;
            }
            if(text_entry2[0]==number[i])
            {
                t2 = true;
            }
            if(text_entry3[0]==number[i])
            {
                t3 = true;
            }
        }

        if( t1 && t2 && t3 ){
            sprintf(cam_id1,"Cam : %s",gtk_entry_get_text (GTK_ENTRY (sub_entry1)));
            sprintf(cam_id2,"Cam : %s",gtk_entry_get_text (GTK_ENTRY (sub_entry2)));
            sprintf(cam_id3,"Cam : %s",gtk_entry_get_text (GTK_ENTRY (sub_entry3)));
            
            sprintf(cid1,"cam%s",gtk_entry_get_text (GTK_ENTRY (sub_entry1)));
            sprintf(cid2,"cam%s",gtk_entry_get_text (GTK_ENTRY (sub_entry2)));
            sprintf(cid3,"cam%s",gtk_entry_get_text (GTK_ENTRY (sub_entry3)));

            gtk_widget_destroy(sub_grid);
            main_activate(app,NULL);
            counter_enabled = TRUE ;
        }

        else{

        dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "\n-----Try Again-----\n Please enter 1-9");
        gtk_window_set_title(GTK_WINDOW(dialog), "Error");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        }

    }

    else{

        dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "-----Try Again-----\n Please enter 1-9");
        gtk_window_set_title(GTK_WINDOW(dialog), "Error");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }

}

void main_button2_callback( GtkWidget *widget, gpointer data ) {

	gtk_widget_destroy(grid);
	sub_activate(app,NULL);
    counter_enabled = FALSE ;
    win_stat = FALSE ;
	
}

void main_button1_callback( GtkWidget *widget, gpointer data ) {

	counter_enabled = !counter_enabled ;
    gtk_button_set_label( data,
			counter_enabled ? "Stop" : "Continue" );

}

void head_button1_callback( GtkWidget *widget, gpointer data ) {

    if(win_stat){

        if(tree_stat){
        //gtk_widget_destroy(tree_window);
        }

        tree_stat = TRUE;

        tree_window = gtk_application_window_new( app );
        gtk_window_set_title( GTK_WINDOW(tree_window), "List" );
        gtk_window_set_default_size( GTK_WINDOW(tree_window), 320, 480 );
        gtk_window_set_position( GTK_WINDOW(tree_window), GTK_WIN_POS_CENTER );

        tree_headerbar = gtk_header_bar_new ();
        gtk_widget_show(tree_headerbar);
        gtk_window_set_application(GTK_WINDOW(tree_window), GTK_APPLICATION (app));
        gtk_header_bar_set_title(GTK_HEADER_BAR(tree_headerbar), "List ");
        gtk_header_bar_set_subtitle(GTK_HEADER_BAR(tree_headerbar), "Demo Application");
        gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(tree_headerbar), TRUE);
        gtk_window_set_titlebar (GTK_WINDOW(tree_window), tree_headerbar);

        tree_button = gtk_button_new_with_label("Refresh");
        gtk_header_bar_pack_end(GTK_HEADER_BAR(tree_headerbar), tree_button);
        g_signal_connect( tree_button, "clicked", 
            G_CALLBACK(tree_button_callback), NULL );

        box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_container_add(GTK_CONTAINER(tree_window), box);

        tree_button2 = gtk_button_new_with_label("Open");
        gtk_box_pack_end( GTK_BOX(box), tree_button2,FALSE , FALSE , 0 );
        g_signal_connect( tree_button2, "clicked", 
            G_CALLBACK(tree_button2_callback), NULL );

        sw = gtk_scrolled_window_new (NULL, NULL);
        gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (sw),
                                            GTK_SHADOW_ETCHED_IN);
        gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (sw),
                                        GTK_POLICY_NEVER,
                                        GTK_POLICY_AUTOMATIC);
        gtk_box_pack_start (GTK_BOX (box), sw, TRUE, TRUE, 0);

        FILE *fp;
        char * line = NULL;
        size_t len = 0;
        ssize_t read;
        student text_data[1000] ;
        
        run_line=0 ;
        fp = fopen("data.txt","r");
        
        while ((read = getline(&line, &len, fp)) != -1) {

            char cp_text[100] ;
            char *sp_text;
            strcpy(cp_text,line);
            sp_text = strtok(cp_text,"\n");
            strcpy(cp_text,sp_text);
            
            sp_text = strtok(cp_text,"_");
            strcpy(text_data[run_line].iD,sp_text);

            sp_text = strtok(NULL,"_");
            strcpy(text_data[run_line].inDate,sp_text);

            sp_text = strtok(NULL,"_");
            strcpy(text_data[run_line].Time,sp_text);

            run_line++;

        }

        fclose(fp);

        model = create_model (text_data);

        /* create tree view */
        treeview = gtk_tree_view_new_with_model (model);
        gtk_tree_selection_set_mode(gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview)),

                                GTK_SELECTION_SINGLE);
        g_object_unref (model);
        gtk_container_add (GTK_CONTAINER (sw), treeview);

        /* add columns to the tree view */
        add_columns (GTK_TREE_VIEW (treeview));

        g_signal_connect(treeview, "row-activated", 
            G_CALLBACK(tree_button2_callback) , NULL);

        gtk_widget_show_all(tree_window);
    }

}

void tree_button_callback( GtkWidget *widget, gpointer data ) {

    gtk_widget_destroy(treeview);
    gtk_widget_destroy(sw);

    sw = gtk_scrolled_window_new (NULL, NULL);
        gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (sw),
                                            GTK_SHADOW_ETCHED_IN);
        gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (sw),
                                        GTK_POLICY_NEVER,
                                        GTK_POLICY_AUTOMATIC);
        gtk_box_pack_start (GTK_BOX (box), sw, TRUE, TRUE, 0);

    FILE *fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    student temp_data[1000];

    run_line=0 ;
    fp = fopen("data.txt","r");
        
    while ((read = getline(&line, &len, fp)) != -1) {

        char cp_text[100] ;
        char *sp_text;
        strcpy(cp_text,line);
        sp_text = strtok(cp_text,"\n");
        strcpy(cp_text,sp_text);
            
        sp_text = strtok(cp_text,"_");
        strcpy(temp_data[run_line].iD,sp_text);

        sp_text = strtok(NULL,"_");
        strcpy(temp_data[run_line].inDate,sp_text);

        sp_text = strtok(NULL,"_");
        strcpy(temp_data[run_line].Time,sp_text);

        run_line++;

    }

    fclose(fp);

    model = create_model (temp_data);

    
    treeview = gtk_tree_view_new_with_model (model);

    gtk_tree_selection_set_mode(gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview)),
                            GTK_SELECTION_SINGLE);
    g_object_unref (model);
    gtk_container_add (GTK_CONTAINER (sw), treeview);

    add_columns (GTK_TREE_VIEW (treeview));

    g_signal_connect(treeview, "row-activated", 
        G_CALLBACK(tree_button2_callback) , NULL);

    gtk_widget_show_all(tree_window);
}

void tree_button2_callback( GtkWidget *widget, gpointer data ) {

    GtkTreeModel *c_model;
    GtkTreeIter iter;
    GtkTreeSelection *selection;
    GtkWidget *fpic_box ,*f_img ;
    
    gchar *name ;
    gchar *c_time , *c_date ;
    char name_pic[100] ;

    c_model = gtk_tree_view_get_model(treeview);
    
    selection = gtk_tree_view_get_selection (treeview);
    
    if (gtk_tree_selection_get_selected (selection, &c_model, &iter))
    {   
        gtk_tree_model_get(c_model,&iter,
                                COLUMN_DATE, &c_date,
                                COLUMN_ID, &name,
                                COLUMN_TIME, &c_time,
                                -1);

    }
    
    sprintf(name_pic,"%s_%s_%s.jpg",name,c_date,c_time);

    pic_window = gtk_application_window_new( app );
	gtk_window_set_title( GTK_WINDOW(pic_window), name_pic );
	gtk_window_set_default_size( GTK_WINDOW(pic_window), 400, 300 );
	gtk_window_set_position( GTK_WINDOW(pic_window), GTK_POS_RIGHT );
    char temp[100] ;
    sprintf(temp,"sub_img/%s",name_pic);
	
    fpic_box = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    gtk_container_add(GTK_CONTAINER (pic_window), fpic_box);

    f_img = gtk_image_new_from_file(temp);
    
    gtk_container_add(GTK_BOX (fpic_box), f_img);

    gtk_widget_show_all(pic_window);
}

bool serverdoit = false;
bool topicdoit  = false;
bool logindoit  = false;
bool loginnow = false ;

static void show_question_server(GtkWidget *widget, gpointer mosq_window) {
  
    GtkResponseType result;
    GtkWidget *dialog;
    char en_server[100];

    dialog = gtk_message_dialog_new(GTK_WINDOW(mosq_window),
                GTK_DIALOG_DESTROY_WITH_PARENT,
                GTK_MESSAGE_QUESTION,
                GTK_BUTTONS_YES_NO,
                "\n Do You Want Save & Exit ?");
    gtk_window_set_title(GTK_WINDOW(dialog), "   Save & Exit  ");         

    result = gtk_dialog_run(GTK_DIALOG(dialog));
    if (result == GTK_RESPONSE_YES || result == GTK_RESPONSE_APPLY) {
        
        serverdoit = false;

        ser_en = gtk_entry_get_text (GTK_ENTRY (server_entry));
        strcpy(server_name,ser_en);

        to_connect_server(client,conn_opts);

        char temp[50] ;
        sprintf(temp,"%s",server_name);

        gtk_widget_override_font(label_sever2,
                            pango_font_description_from_string("Monospace 9"));
        gtk_label_set_text(GTK_LABEL(label_sever2),temp);
        gtk_widget_set_size_request(label_sever2,0,0);

        gtk_widget_destroy(mosq_window);
        
    } 
    else {
        gtk_widget_destroy(dialog);
    }
  
}

static void show_question_topic(GtkWidget *widget, gpointer mosq_window) {
  
    GtkResponseType result;
    GtkWidget *dialog;
    char en_topic[100] ;

    dialog = gtk_message_dialog_new(GTK_WINDOW(mosq_window),
                GTK_DIALOG_DESTROY_WITH_PARENT,
                GTK_MESSAGE_QUESTION,
                GTK_BUTTONS_YES_NO,
                "\n Do You Want Save & Exit ?");
    gtk_window_set_title(GTK_WINDOW(dialog), "   Save & Exit  ");         

    result = gtk_dialog_run(GTK_DIALOG(dialog));
    if (result == GTK_RESPONSE_YES || result == GTK_RESPONSE_APPLY) {
        
        topicdoit = false;

        top_en = gtk_entry_get_text (GTK_ENTRY (topic_entry));
        strcpy(topic_name,top_en);

        to_connect_topic(client,conn_opts);

        char temp[50] ;
        sprintf(temp,"%s",topic_name);

        gtk_widget_override_font(label_topic2,
                            pango_font_description_from_string("Monospace 9"));
        gtk_label_set_text(GTK_LABEL(label_topic2),temp);

        gtk_widget_destroy(mosq_window);
        
    } else {
        gtk_widget_destroy(dialog);
    }

  
}

static void show_question_login(GtkWidget *widget, gpointer login_window) {
  
    GtkResponseType result;
    GtkWidget *dialog;

    dialog = gtk_message_dialog_new(GTK_WINDOW(login_window),
                GTK_DIALOG_DESTROY_WITH_PARENT,
                GTK_MESSAGE_QUESTION,
                GTK_BUTTONS_YES_NO,
                "\n Do You Want Exit ?");
    gtk_window_set_title(GTK_WINDOW(dialog), "  Exit  ");         

    result = gtk_dialog_run(GTK_DIALOG(dialog));
    if (result == GTK_RESPONSE_YES || result == GTK_RESPONSE_APPLY) {

        logindoit = false;
        gtk_widget_destroy(login_window);

    } else {
        gtk_widget_destroy(dialog);
    }
  

  
}

static void check_false_server(GtkWidget *widget, gpointer mosq_window) {
    serverdoit = false;
    gtk_widget_destroy(mosq_window);
}

static void check_false_topic(GtkWidget *widget, gpointer mosq_window) {
    topicdoit = false;
}

static void check_false_login(GtkWidget *widget, gpointer mosq_window) {
    logindoit = false;
}

void server_button( GtkWidget *widget, gpointer data ) {
    
    GtkWidget *grid_dlc ;

    if (!serverdoit){
    
        serverdoit = true;
        
        mosq_window = gtk_application_window_new( app );
	
	    gtk_window_set_title( GTK_WINDOW(mosq_window), "Server" );
	    gtk_window_set_default_size( GTK_WINDOW(mosq_window), 300, 200 );
        gtk_window_set_resizable (GTK_WINDOW(mosq_window), FALSE);
        
	    gtk_window_set_position( GTK_WINDOW(mosq_window), GTK_WIN_POS_CENTER);

        headerbar = gtk_header_bar_new ();
        gtk_widget_show(headerbar);
        gtk_window_set_application(GTK_WINDOW(mosq_window), GTK_APPLICATION (app));
        gtk_header_bar_set_title(GTK_HEADER_BAR(headerbar), "SMK ");
        gtk_header_bar_set_subtitle(GTK_HEADER_BAR(headerbar), "Server");
        gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(headerbar), false);
        gtk_window_set_titlebar (GTK_WINDOW(mosq_window), headerbar);


        grid_dlc = gtk_grid_new ();
        gtk_container_add (GTK_CONTAINER (mosq_window), grid_dlc);
        gtk_grid_set_column_spacing ( GTK_GRID ( grid_dlc ), 4 );
        gtk_grid_set_row_spacing ( GTK_GRID ( grid_dlc ), 4 );


        label_sever = gtk_label_new("Server");
        gtk_widget_override_font(label_sever,
                            pango_font_description_from_string("FreeSerif 20"));
        gtk_grid_attach (GTK_GRID (grid_dlc), label_sever, 0, 0, 1, 1);
        gtk_widget_set_margin_top ( label_sever, 20 );
        gtk_widget_set_margin_start ( label_sever, 70 );
        gtk_widget_set_margin_end ( label_sever, 40 );


        server_entry = gtk_entry_new();
        gtk_entry_set_placeholder_text(GTK_ENTRY(server_entry),"Server");
        gtk_widget_set_margin_top ( server_entry, 20 );
        gtk_grid_attach (GTK_GRID (grid_dlc), server_entry, 0, 1, 1, 1);
        gtk_widget_set_margin_start ( server_entry, 70 );
        gtk_widget_set_margin_end ( server_entry, 40 );
        
        server_button1 =  gtk_button_new_with_label( "Save" );
        gtk_grid_attach (GTK_GRID (grid_dlc), server_button1, 0, 2, 1, 1);

        g_signal_connect(server_button1, "clicked", 
            G_CALLBACK(show_question_server),mosq_window); 
            
        gtk_widget_set_margin_start ( server_button1, 63 );
        gtk_widget_set_margin_end ( server_button1, 85 );
        gtk_widget_set_margin_top ( server_button1, 20 );
        
        back_window = gtk_button_new_with_label( "Back" );
        gtk_grid_attach (GTK_GRID (grid_dlc), back_window, 0, 2, 2, 1);
        
        g_signal_connect(back_window, "clicked", 
                    G_CALLBACK(check_false_server),mosq_window); 

        gtk_widget_set_margin_start ( back_window, 193 );
        gtk_widget_set_margin_end ( back_window, 40 );
        gtk_widget_set_margin_top ( back_window, 20 );

        gtk_widget_show_all(mosq_window);

        
    }
    else {
        gtk_widget_destroy(mosq_window);
        serverdoit = false;
        server_button(mosq_window,NULL);

        }

}

void topic_button( GtkWidget *widget, gpointer data ) {
    
    GtkWidget *grid_dlc ;
    if (!topicdoit){
        topicdoit = true;
        
        mosq_window = gtk_application_window_new( app );
	
	    gtk_window_set_title( GTK_WINDOW(mosq_window), "Topic" );
	    gtk_window_set_default_size( GTK_WINDOW(mosq_window), 300, 200 );
        gtk_window_set_resizable (GTK_WINDOW(mosq_window), FALSE);
        
	    gtk_window_set_position( GTK_WINDOW(mosq_window), GTK_WIN_POS_NONE);

        headerbar = gtk_header_bar_new ();
        gtk_widget_show(headerbar);
        gtk_window_set_application(GTK_WINDOW(mosq_window), GTK_APPLICATION (app));
        gtk_header_bar_set_title(GTK_HEADER_BAR(headerbar), "SMK ");
        gtk_header_bar_set_subtitle(GTK_HEADER_BAR(headerbar), "Topic");
        gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(headerbar), false);
        gtk_window_set_titlebar (GTK_WINDOW(mosq_window), headerbar);


        grid_dlc = gtk_grid_new ();
        gtk_container_add (GTK_CONTAINER (mosq_window), grid_dlc);
        gtk_grid_set_column_spacing ( GTK_GRID ( grid_dlc ), 4 );
        gtk_grid_set_row_spacing ( GTK_GRID ( grid_dlc ), 4 );


        label_topic = gtk_label_new("Topic");
        gtk_widget_override_font(label_topic,
                            pango_font_description_from_string("FreeSerif 20"));
        gtk_grid_attach (GTK_GRID (grid_dlc), label_topic, 0, 0, 1, 1);
        gtk_widget_set_margin_top ( label_topic, 20 );
        gtk_widget_set_margin_start ( label_topic, 70 );
        gtk_widget_set_margin_end ( label_topic, 40 );



        topic_entry = gtk_entry_new();
        gtk_entry_set_placeholder_text(GTK_ENTRY(topic_entry),"Topic");
        gtk_widget_set_margin_top ( topic_entry, 20 );
        gtk_grid_attach (GTK_GRID (grid_dlc), topic_entry, 0, 1, 1, 1);
        gtk_widget_set_margin_start ( topic_entry, 70 );
        gtk_widget_set_margin_end ( topic_entry, 40 );
        

        topic_button1 =  gtk_button_new_with_label( "Save" );
        gtk_grid_attach (GTK_GRID (grid_dlc), topic_button1, 0, 2, 1, 1);
        g_signal_connect(topic_button1, "clicked", G_CALLBACK(show_question_topic),mosq_window); 
        gtk_widget_set_margin_start ( topic_button1, 63 );
        gtk_widget_set_margin_end ( topic_button1, 85 );
        gtk_widget_set_margin_top ( topic_button1, 20 );

        back_window = gtk_button_new_with_label( "Back" );
        gtk_grid_attach (GTK_GRID (grid_dlc), back_window, 0, 2, 2, 1);
        g_signal_connect(back_window, "clicked", 
        G_CALLBACK(check_false_topic),mosq_window); 
        g_signal_connect_swapped( back_window, "clicked", 
		G_CALLBACK( gtk_widget_destroy), mosq_window );        
        gtk_widget_set_margin_start ( back_window, 193 );
        gtk_widget_set_margin_end ( back_window, 40 );
        gtk_widget_set_margin_top ( back_window, 20 );
        
        gtk_widget_show_all(mosq_window);

        
    }

    else {
        topicdoit = false;
        gtk_widget_destroy(mosq_window);
        topic_button(mosq_window,NULL);

    }

}

void login_button( GtkWidget *widget, gpointer data ) {
    
    GtkWidget *grid_dlc ;
    if ( logindoit == false && loginnow == false ){
        logindoit = true;
        
        login_window = gtk_application_window_new( app );
	
	    gtk_window_set_title( GTK_WINDOW(login_window), "Login" );
	    gtk_window_set_default_size( GTK_WINDOW(login_window), 500, 300 );
        gtk_window_set_resizable (GTK_WINDOW(login_window), FALSE);
        
	    gtk_window_set_position( GTK_WINDOW(login_window), GTK_WIN_POS_NONE);

        headerbar = gtk_header_bar_new ();
        gtk_widget_show(headerbar);
        gtk_window_set_application(GTK_WINDOW(login_window), GTK_APPLICATION (app));
        gtk_header_bar_set_title(GTK_HEADER_BAR(headerbar), "SMK ");
        gtk_header_bar_set_subtitle(GTK_HEADER_BAR(headerbar), "login");
        gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(headerbar), false);
        gtk_window_set_titlebar (GTK_WINDOW(login_window), headerbar);


        grid_dlc = gtk_grid_new ();
        gtk_container_add (GTK_CONTAINER (login_window), grid_dlc);
        gtk_grid_set_column_spacing ( GTK_GRID ( grid_dlc ), 5 );
        gtk_grid_set_row_spacing ( GTK_GRID ( grid_dlc ), 5 );


        label_login = gtk_label_new("Login");
        gtk_widget_override_font(label_login,
                            pango_font_description_from_string("FreeSerif 20"));
        gtk_grid_attach (GTK_GRID (grid_dlc), label_login, 0, 0, 3, 1);
        gtk_widget_set_margin_top ( label_login, 20 );
        gtk_widget_set_margin_start ( label_login, 125 );
        

        label_login = gtk_label_new("User");
        gtk_widget_override_font(label_login,
                            pango_font_description_from_string("FreeSerif 14"));
        gtk_grid_attach (GTK_GRID (grid_dlc), label_login, 0, 1, 1, 1);
        gtk_widget_set_margin_top ( label_login, 20 );
        gtk_widget_set_margin_start ( label_login, 100 );
        
        user_entry = gtk_entry_new();
        gtk_entry_set_placeholder_text(GTK_ENTRY(user_entry),"User");
        gtk_widget_set_margin_top ( user_entry, 20 );
        gtk_grid_attach (GTK_GRID (grid_dlc), user_entry, 1, 1, 1, 1);
        gtk_widget_set_margin_start ( user_entry, 10 );

        label_pass = gtk_label_new("Password");
        gtk_widget_override_font(label_pass,
                            pango_font_description_from_string("FreeSerif 14"));
        gtk_grid_attach (GTK_GRID (grid_dlc), label_pass, 0, 2, 1, 1);
        gtk_widget_set_margin_top ( label_pass, 20 );
        gtk_widget_set_margin_start ( label_pass, 130 );

        pass_entry = gtk_entry_new();
        gtk_entry_set_placeholder_text(GTK_ENTRY(pass_entry),"Password");
        gtk_entry_set_visibility(GTK_ENTRY(pass_entry),FALSE);
        gtk_widget_set_margin_top ( pass_entry, 20 );
        gtk_grid_attach (GTK_GRID (grid_dlc), pass_entry, 1, 2, 1, 1);
        gtk_widget_set_margin_start ( pass_entry, 10 );

        login_button1 = gtk_button_new_with_label( "login" );
        gtk_grid_attach (GTK_GRID (grid_dlc), login_button1, 0, 3, 3, 1);

        g_signal_connect(login_button1, "clicked", 
                    G_CALLBACK(login_button1_callback),login_window); 
        
        g_signal_connect(pass_entry, "activate", 
                    G_CALLBACK(login_button1_callback),pass_entry);

        gtk_widget_set_margin_start ( login_button1, 180 );
        gtk_widget_set_margin_end ( login_button1, 60 );
        gtk_widget_set_margin_top ( login_button1, 20 );

        server_button1 =  gtk_button_new_with_label( "Back" );
        gtk_grid_attach (GTK_GRID (grid_dlc), server_button1, 0, 4, 4, 1);
        
        g_signal_connect(server_button1, "clicked", 
                    G_CALLBACK(check_false_login),login_window); 
        
        g_signal_connect_swapped( server_button1, "clicked", 
		            G_CALLBACK( gtk_widget_destroy), login_window );

        gtk_widget_set_margin_top ( server_button1, 20 );
        gtk_widget_set_margin_start ( server_button1, 200 );
        gtk_widget_set_margin_end ( server_button1, 90 );
        
        
        gtk_widget_show_all(login_window);

    }

    else if( logindoit == true && loginnow == false ) {
        logindoit = false;
        gtk_widget_destroy(login_window);
        login_button(login_window,NULL);
        
    } else if( logindoit == true && loginnow == true ) {
        gtk_widget_destroy(del_window);
        make_del_tree();

    }

}

void login_button1_callback( GtkWidget *widget, gpointer data ) {
    user_text = gtk_entry_get_text (GTK_ENTRY (user_entry));
    pass_text = gtk_entry_get_text (GTK_ENTRY (pass_entry));
    
    if( !(strcmp(user_text,"admin")) && !(strcmp(pass_text,"12345")) ){

        gtk_widget_destroy(login_window);
        loginnow = true;
        make_del_tree();

    }
    else{

        GtkWidget *dialog;

        dialog = gtk_message_dialog_new(GTK_WINDOW(login_window),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_INFO,
                                        GTK_BUTTONS_CLOSE,
                                        "\nInvalid username or password" );

        gtk_window_set_title(GTK_WINDOW(dialog), "Error");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}


void delhead_button2_callback(GtkWidget *widget, gpointer data) {

    logindoit  = false;
    loginnow = false ;
    gtk_widget_destroy(del_window) ;
}

void refresh_tree() {
    
    gtk_widget_destroy(del_sw);


    del_sw = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (del_sw),
                                            GTK_SHADOW_ETCHED_IN);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (del_sw),
                                        GTK_POLICY_NEVER,
                                        GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start (GTK_BOX (del_box), del_sw, TRUE, TRUE, 0);

    FILE *fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    student text_data[1000] ;

    run_line = 0 ;
    fp = fopen("all_data.txt","r");
        
    while ((read = getline(&line, &len, fp)) != -1) {

        char cp_text[100] ;
        char *sp_text;
        strcpy(cp_text,line);
        sp_text = strtok(cp_text,"\n");
        strcpy(cp_text,sp_text);
            
        sp_text = strtok(cp_text,"_");
        strcpy(text_data[run_line].iD,sp_text);

        sp_text = strtok(NULL,"_");
        strcpy(text_data[run_line].inDate,sp_text);

        sp_text = strtok(NULL,"_");
        strcpy(text_data[run_line].Time,sp_text);

        run_line++;

    }

    fclose(fp);

    del_model = create_model (text_data);

    /* create tree view */
    del_tree = gtk_tree_view_new_with_model (del_model);
    gtk_tree_selection_set_mode(gtk_tree_view_get_selection(GTK_TREE_VIEW(del_tree)),
                            GTK_SELECTION_SINGLE);

    g_object_unref (del_model);
    gtk_container_add (GTK_CONTAINER (del_sw), del_tree);

        /* add columns to the tree view */
    add_columns (GTK_TREE_VIEW (del_tree));
    gtk_widget_show_all(del_window);

}

void make_del_tree() {

    del_window = gtk_application_window_new( app );
    gtk_window_set_title( GTK_WINDOW(del_window), "Del" );
    gtk_window_set_default_size( GTK_WINDOW(del_window), 320, 480 );
    gtk_window_set_resizable (GTK_WINDOW(del_window), FALSE);
    gtk_window_set_position( GTK_WINDOW(del_window), GTK_WIN_POS_CENTER );

    del_headerbar = gtk_header_bar_new ();
    gtk_widget_show(del_headerbar);
    gtk_window_set_application(GTK_WINDOW(del_window), GTK_APPLICATION (app));
    gtk_header_bar_set_title(GTK_HEADER_BAR(del_headerbar), "ADMIN ");
    gtk_header_bar_set_subtitle(GTK_HEADER_BAR(del_headerbar), "Demo Application");
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(del_headerbar), FALSE);
    gtk_window_set_titlebar (GTK_WINDOW(del_window), del_headerbar);

    delhead_button2 = gtk_button_new_with_label("Exit");
    gtk_header_bar_pack_end(GTK_HEADER_BAR(del_headerbar), delhead_button2);
    g_signal_connect( delhead_button2, "clicked", 
		G_CALLBACK(delhead_button2_callback), NULL );


    del_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(del_window), del_box);

    del_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_end(GTK_BOX(del_box), del_hbox,FALSE , TRUE , 0);

    delhead_button1 = gtk_button_new_with_label("Refresh");
    gtk_box_pack_end( GTK_BOX(del_box), delhead_button1,FALSE , TRUE , 0 );


    del_button2 = gtk_button_new_with_label("DELETE ALL");
    gtk_box_pack_end( GTK_BOX(del_hbox), del_button2,TRUE , TRUE , 0 );
    g_signal_connect( del_button2, "clicked", 
        G_CALLBACK(del_button2_callback), NULL );

    del_button1 = gtk_button_new_with_label("Delete");
    gtk_box_pack_start( GTK_BOX(del_hbox), del_button1,TRUE , TRUE , 0 );
    

    del_sw = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (del_sw),
                                            GTK_SHADOW_ETCHED_IN);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (del_sw),
                                        GTK_POLICY_NEVER,
                                        GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start (GTK_BOX (del_box), del_sw, TRUE, TRUE, 0);

    g_signal_connect( delhead_button1, "clicked", 
		G_CALLBACK(refresh_tree), del_sw );

    FILE *fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    student text_data[1000] ;

    run_line=0 ;
    fp = fopen("all_data.txt","r");
        
    while ((read = getline(&line, &len, fp)) != -1) {

        char cp_text[100] ;
        char *sp_text;
        strcpy(cp_text,line);
        sp_text = strtok(cp_text,"\n");
        strcpy(cp_text,sp_text);
            
        sp_text = strtok(cp_text,"_");
        strcpy(text_data[run_line].iD,sp_text);

        sp_text = strtok(NULL,"_");
        strcpy(text_data[run_line].inDate,sp_text);

        sp_text = strtok(NULL,"_");
        strcpy(text_data[run_line].Time,sp_text);

        run_line++;

    }

    fclose(fp);

    del_model = create_model (text_data);

    /* create tree view */
    del_tree = gtk_tree_view_new_with_model (del_model);
    gtk_tree_selection_set_mode(gtk_tree_view_get_selection(GTK_TREE_VIEW(del_tree)),
                            GTK_SELECTION_SINGLE);

    g_object_unref (del_model);
    gtk_container_add (GTK_CONTAINER (del_sw), del_tree);

        /* add columns to the tree view */
    add_columns (GTK_TREE_VIEW (del_tree));

    g_signal_connect( del_button1, "clicked", 
        G_CALLBACK(del_button1_callback), del_tree );





    gtk_widget_show_all(del_window);

}

void del_button1_callback( GtkWidget *widget, gpointer data ) {
    
    remove_item(NULL,NULL,del_tree);
    
    char *temp,t_text[100],d_texl[100];
    strcpy(t_text,del_text);
    temp = strtok(t_text,"\n");
    strcpy(t_text,temp);

    sprintf(d_texl,"sub_img/%s.jpg",t_text);

    GtkWidget *dialog;

    if (remove(d_texl) == 0) {

        dialog = gtk_message_dialog_new(GTK_WINDOW(del_window),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_INFO,
                                        GTK_BUTTONS_CLOSE,
                                        "\nThe file is deleted successfully" );

        gtk_window_set_title(GTK_WINDOW(dialog), "Warning");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

    } else {

        dialog = gtk_message_dialog_new(GTK_WINDOW(del_window),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_INFO,
                                        GTK_BUTTONS_CLOSE,
                                        "\nNo file to deleted" );

        gtk_window_set_title(GTK_WINDOW(dialog), "Error");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

    }


    text_alldate all_data[1000] ;
    
    int run = 0 ;
    FILE *fp , *new_fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("all_data.txt","r");

    while ((read = getline(&line, &len, fp)) != -1) {
        
        char text[100];
        strcpy(text,line);
        if( strcmp(text,del_text) )
        {

            strcpy(all_data[run].allText,text);

            run++;
        }
        
    }
    fclose(fp);

    new_fp = fopen("all_data.txt","w");
    
    for(int i =0 ;i<run;i++)
    {

        fprintf(new_fp,"%s",all_data[i].allText);

    }

    fclose(new_fp);

    text_alldate A_data[1000] ;
    
    int run1 = 0 ;
    FILE *nfp, *dfp ;
    char * line1 = NULL;
    size_t len1 = 0;
    ssize_t read1;

    nfp = fopen("data.txt","r");
    
    while ((read1 = getline(&line1, &len1, nfp)) != -1) {
        
        char text[100];
        strcpy(text,line1);
        if( strcmp(text,del_text) )
        {
            strcpy(A_data[run1].allText,text);
            run1++;
        }
        
    }
    fclose(nfp);

    dfp = fopen("data.txt","w");
    
    for(int i =0 ;i<run1;i++)
    {
        fprintf(dfp,"%s",A_data[i].allText);
    }

    fclose(dfp);

    /*
cam1_10-10-2021_14-13-12
cam1_10-10-2021_14-14-12
cam1_10-10-2021_14-15-12
cam1_10-10-2021_14-16-12
cam1_10-10-2021_14-17-12
cam1_25-09-2021_17-14-49
    */

}

void del_button2_callback( GtkWidget *widget, gpointer data ) {

    GtkWidget *dialog, *dialog2;
    GtkResponseType result;

    dialog2 = gtk_message_dialog_new(GTK_WINDOW(del_window),
                GTK_DIALOG_DESTROY_WITH_PARENT,
                GTK_MESSAGE_QUESTION,
                GTK_BUTTONS_YES_NO,
                "\n Do You want delete all file ?");
    gtk_window_set_title(GTK_WINDOW(dialog2), "  Warning  ");         

    result = gtk_dialog_run(GTK_DIALOG(dialog2));

    if (result == GTK_RESPONSE_YES || result == GTK_RESPONSE_APPLY) {

        gtk_widget_destroy(dialog2);
        int run = 0 ;
        FILE *fp , *new_fp ,*new_fp2;
        char * line = NULL;
        size_t len = 0;
        ssize_t read;

        fp = fopen("all_data.txt","r");
        while ((read = getline(&line, &len, fp)) != -1) {
            
            char text[100];
            char *temptext ;
            char d_text[100] ;
            strcpy(text,line);
            temptext = strtok(text,"\n");
            sprintf(d_text,"sub_img/%s.jpg",temptext);
            remove(d_text);
            
        }

        fclose(fp);

        new_fp = fopen("all_data.txt","w");
        fprintf(new_fp,"");
        fclose(new_fp);

        new_fp2 = fopen("data.txt","w");
        fprintf(new_fp2,"");
        fclose(new_fp2);

        refresh_tree();
        dialog = gtk_message_dialog_new(GTK_WINDOW(del_window),
                                            GTK_DIALOG_DESTROY_WITH_PARENT,
                                            GTK_MESSAGE_INFO,
                                            GTK_BUTTONS_CLOSE,
                                            "\nAll file is deleted successfully!!!" );

        gtk_window_set_title(GTK_WINDOW(dialog), "Warning");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    } 
    else {
        gtk_widget_destroy(dialog2);
    }

/*
cam1_10-10-2021_14-13-12
cam1_10-10-2021_14-14-12
cam1_10-10-2021_14-15-12
cam1_10-10-2021_14-16-12
cam1_10-10-2021_14-17-12
cam1_25-09-2021_17-14-49
*/
}

void
remove_item(GSimpleAction *action, GVariant *parameter, gpointer data) {

    GtkTreeIter iter;
    GtkTreePath* path;
    GtkTreeModel *model1;
    GtkTreeSelection *selection;
    GtkTreeView *treeview1 = GTK_TREE_VIEW(data);
    char *c_name,*c_date,*c_time ;
    char c_text[100] ;

    model1 = gtk_tree_view_get_model(treeview1);
    selection = gtk_tree_view_get_selection (treeview1);
    if (gtk_tree_selection_get_selected (selection, NULL, &iter))
    {
        gtk_tree_model_get(model1,&iter,
                                COLUMN_DATE, &c_date,
                                COLUMN_ID, &c_name,
                                COLUMN_TIME, &c_time,
                                -1);

        sprintf(del_text,"%s_%s_%s\n",c_name,c_date,c_time);

        path = gtk_tree_model_get_path (model1, &iter);
        gtk_list_store_remove (GTK_LIST_STORE (model1), &iter);
        gtk_tree_path_free (path);
    }

}

///////////////////////////////////////////////////////////////////

void activate( GtkApplication *app, gpointer user_data ){

    window = gtk_application_window_new( app );
	
	gtk_window_set_title( GTK_WINDOW(window), "smk" );
	gtk_window_set_default_size( GTK_WINDOW(window), 1750, 800 );
    gtk_window_set_resizable (GTK_WINDOW(window), FALSE);
	gtk_window_set_position( GTK_WINDOW(window), GTK_WIN_POS_CENTER );
	
    
    headerbar = gtk_header_bar_new ();
    gtk_widget_show(headerbar);
    gtk_window_set_application(GTK_WINDOW(window), GTK_APPLICATION (app));
    gtk_header_bar_set_title(GTK_HEADER_BAR(headerbar), "SMK ");
    gtk_header_bar_set_subtitle(GTK_HEADER_BAR(headerbar), "Demo Application");
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(headerbar), TRUE);
    gtk_window_set_titlebar (GTK_WINDOW(window), headerbar);

    gearmenubutton = gtk_menu_button_new();
    gearicon = gtk_image_new_from_icon_name("emblem-system-symbolic",
                                          GTK_ICON_SIZE_SMALL_TOOLBAR);
    gtk_button_set_image(GTK_BUTTON(gearmenubutton), gearicon);
    gtk_header_bar_pack_end(GTK_HEADER_BAR(headerbar), gearmenubutton);

    mosqmenu = g_menu_new();
    g_menu_append(mosqmenu, "Server","app.server");
    g_menu_append(mosqmenu, "Topic", "app.topic");
    editmenu = g_menu_new();
    g_menu_append(editmenu, "Login","app.login");

    g_menu_append_section(mosqmenu, NULL, G_MENU_MODEL(editmenu));
    gtk_menu_button_set_menu_model(GTK_MENU_BUTTON(gearmenubutton),
                                    G_MENU_MODEL(mosqmenu));
    g_object_unref(editmenu);
    g_object_unref(mosqmenu);

    head_button1 = gtk_button_new_with_label("LIST");
    gtk_header_bar_pack_end(GTK_HEADER_BAR(headerbar), head_button1);
    g_signal_connect( head_button1, "clicked", 
		G_CALLBACK(head_button1_callback), NULL );
    
}

void sub_activate( GtkApplication *app, gpointer user_data ) {

	sub_grid = gtk_grid_new();
    gtk_container_add (GTK_CONTAINER(window), sub_grid);
    gtk_grid_set_column_spacing ( GTK_GRID ( sub_grid ), 9 );
    gtk_grid_set_row_spacing ( GTK_GRID ( sub_grid ), 9 );

    gtk_widget_set_margin_top ( sub_grid, 50 );
    gtk_widget_set_margin_start ( sub_grid, 0 );

/////////////////////////////////////////////////////////////////////////////

    head_label = gtk_label_new("Smoke Detection");
    gtk_widget_override_font(head_label,
                            pango_font_description_from_string("FreeSerif 50"));
    gtk_grid_attach (GTK_GRID (sub_grid), head_label, 0, 0, 1, 1);
    gtk_widget_set_margin_top ( head_label, 0 );
    gtk_widget_set_margin_start ( head_label, 650 );
    gtk_widget_set_margin_end ( head_label, 0 );

//////////////////////////////////////////////////////////////////////////////

    img1 = gtk_image_new_from_file("main_pic.jpg");
    gtk_grid_attach (GTK_GRID (sub_grid), img1, 0, 1, 1, 1);
    gtk_widget_set_size_request(img1,400,300);
    gtk_widget_set_margin_start ( img1, 650 );
    gtk_widget_set_margin_end ( img1, 0 );
    gtk_widget_set_margin_top ( img1, 20 );

    sub_label1 = gtk_label_new("CAM ID:");
    gtk_widget_override_font(sub_label1,
                            pango_font_description_from_string("Monospace 12"));
    gtk_grid_attach (GTK_GRID (sub_grid), sub_label1, 0, 2, 1, 1);
    gtk_widget_set_margin_start ( sub_label1, 470 );
    gtk_widget_set_margin_end ( sub_label1, 0 );
    gtk_widget_set_margin_top ( sub_label1, 30 );

    sub_label2 = gtk_label_new("CAM ID:");
    gtk_widget_override_font(sub_label2,
                            pango_font_description_from_string("Monospace 12"));
    gtk_grid_attach (GTK_GRID (sub_grid), sub_label2, 0, 3, 1, 1);
    gtk_widget_set_margin_start ( sub_label2, 470 );
    gtk_widget_set_margin_end ( sub_label2, 0 );

    sub_label3 = gtk_label_new("CAM ID:");
    gtk_widget_override_font(sub_label3,
                            pango_font_description_from_string("Monospace 12"));
    gtk_grid_attach (GTK_GRID (sub_grid), sub_label3, 0, 4, 1, 1);
    gtk_widget_set_margin_start ( sub_label3, 470 );
    gtk_widget_set_margin_end ( sub_label3, 0 );

    sub_entry1 = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(sub_entry1),"1");
    gtk_grid_attach (GTK_GRID (sub_grid), sub_entry1, 0, 2, 1, 1);
    gtk_widget_set_margin_top ( sub_entry1, 30 );
    gtk_widget_set_margin_start ( sub_entry1, 835);
    gtk_widget_set_margin_end ( sub_entry1, 100 );

    sub_entry2 = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(sub_entry2),"2");
    gtk_grid_attach (GTK_GRID (sub_grid), sub_entry2, 0, 3, 1, 1);
    gtk_widget_set_margin_start ( sub_entry2, 835 );
    gtk_widget_set_margin_end ( sub_entry2, 100 );

    sub_entry3 = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(sub_entry3),"3");
    gtk_grid_attach (GTK_GRID (sub_grid), sub_entry3, 0, 4, 1, 1);
    gtk_widget_set_margin_start ( sub_entry3, 835 );
    gtk_widget_set_margin_end ( sub_entry3, 100 );

    sub_button1 = gtk_button_new_with_label( "Start" );
    g_signal_connect( sub_button1, "clicked",
		G_CALLBACK(sub_button1_callback), sub_button1 );
    gtk_grid_attach (GTK_GRID (sub_grid), sub_button1, 0, 5, 1, 1);
    gtk_widget_override_font(sub_button1,
                            pango_font_description_from_string("FreeSans,Bold 12"));
    gtk_widget_set_margin_start ( sub_button1, 760 );
    gtk_widget_set_margin_end ( sub_button1, 120 );
    gtk_widget_set_margin_top ( sub_button1, 20 );

    label_head_server = gtk_label_new("Server : ");
    gtk_widget_override_font(label_head_server,
                            pango_font_description_from_string("Monospace 9"));
    gtk_grid_attach (GTK_GRID (sub_grid), label_head_server, 0, 6, 1, 1);
    gtk_widget_set_margin_start ( label_head_server, 0 );
    gtk_widget_set_margin_end ( label_head_server, 980 );
    gtk_widget_set_margin_top ( label_head_server, 75 );

    char temp[50];
    sprintf(temp,"%s ",server_name);

    label_sever2 = gtk_label_new(temp);
    gtk_widget_override_font(label_sever2,
                            pango_font_description_from_string("Monospace 9"));
    gtk_grid_attach (GTK_GRID (sub_grid), label_sever2, 0, 6, 1, 1);
    
    gtk_widget_set_margin_start ( label_sever2, 0 );
    gtk_widget_set_margin_end ( label_sever2, 780 );
    gtk_widget_set_margin_top ( label_sever2, 75 );
    /*
    gtk_grid_attach (GTK_GRID (box1), label_sever2, 0, 6, 1, 1);
    gtk_window_get_resizable(label_sever2);
    gtk_widget_set_margin_start ( label_sever2, 0 );
    gtk_widget_set_margin_end ( label_sever2, 780 );
    gtk_widget_set_margin_top ( label_sever2, 75 );
    */


    label_head_topic = gtk_label_new("Topic  : ");
    gtk_widget_override_font(label_head_topic,
                            pango_font_description_from_string("Monospace 9"));
    gtk_grid_attach (GTK_GRID (sub_grid), label_head_topic, 0, 7, 1, 1);
    gtk_widget_set_margin_start ( label_head_topic, 0 );
    gtk_widget_set_margin_end ( label_head_topic, 980 );
    gtk_widget_set_margin_top ( label_head_topic, 0 );


    sprintf(temp," %s",topic_name);

    label_topic2 = gtk_label_new(temp);
    gtk_widget_override_font(label_topic2,
                            pango_font_description_from_string("Monospace 9"));
    gtk_grid_attach (GTK_GRID (sub_grid), label_topic2, 0, 7, 1, 1);
    gtk_widget_set_margin_start ( label_topic2, 0 );
    gtk_widget_set_margin_end ( label_topic2, 800 );
    gtk_widget_set_margin_top ( label_topic2, 0 );

    main_status = gtk_label_new_with_mnemonic("");
    gtk_grid_attach (GTK_GRID (sub_grid), main_status, 3, 6, 1, 1);
    gtk_widget_set_margin_start ( main_status, 530 );
    gtk_widget_set_margin_top ( main_status, 75 );

    if(!is_connected){

        gtk_label_set_text(GTK_LABEL(main_status),"• Connect");
        gtk_widget_override_font(main_status,
                            pango_font_description_from_string("Monospace 9"));

    }
    else{

        gtk_label_set_text(GTK_LABEL(main_status),"• Disconnect");
        gtk_widget_override_font(main_status,
                            pango_font_description_from_string("Monospace 10"));

    }

    gtk_widget_show_all(window);

}

void main_activate( GtkApplication *app, gpointer user_data ) {

    gtk_widget_show(head_button1);

	grid = gtk_grid_new();
    gtk_container_add (GTK_CONTAINER(window), grid);
    gtk_grid_set_column_spacing ( GTK_GRID ( grid ), 3 );
    gtk_grid_set_row_spacing ( GTK_GRID ( grid ), 3 );

    head_label = gtk_label_new(" Server Cam");
    gtk_widget_override_font(head_label,
                            pango_font_description_from_string("FreeSerif 30"));
    gtk_grid_attach (GTK_GRID (grid), head_label, 3, 0, 3, 1);
    gtk_widget_set_margin_top ( head_label, 5 );
    gtk_widget_set_margin_start ( head_label, 0 );
    gtk_widget_set_margin_end ( head_label, 0 );

	pic_box1 = gtk_event_box_new();
    gtk_widget_set_size_request(pic_box1,576,432);

	img1 = gtk_image_new_from_file("noimage.jpg");
	gtk_container_add(GTK_CONTAINER(pic_box1), img1);
  	gtk_grid_attach (GTK_GRID (grid), pic_box1, 0, 1, 3, 1);
    gtk_widget_set_margin_top ( pic_box1, 10 );
    gtk_widget_set_margin_start ( pic_box1, 8 );
    gtk_widget_set_margin_end ( pic_box1, 0 );

	pic_box2 = gtk_event_box_new();
    gtk_widget_set_size_request(pic_box2,576,432);

	img2 = gtk_image_new_from_file("noimage.jpg");
	gtk_container_add(GTK_CONTAINER(pic_box2), img2);
    gtk_grid_attach (GTK_GRID (grid), pic_box2, 3, 1, 3, 1);
    gtk_widget_set_margin_top ( pic_box2 , 10 );

	pic_box3 = gtk_event_box_new();
    gtk_widget_set_size_request(pic_box3,576,432);

	img3 = gtk_image_new_from_file("noimage.jpg");
	gtk_container_add(GTK_CONTAINER(pic_box3), img3);
    gtk_grid_attach (GTK_GRID (grid), pic_box3, 6, 1, 3, 1);
    gtk_widget_set_margin_top ( pic_box3 , 10 );

	main_label1 = gtk_label_new_with_mnemonic( cam_id1 );
    gtk_widget_override_font(main_label1,
                            pango_font_description_from_string("FreeSans 22"));

    gtk_grid_attach (GTK_GRID (grid), main_label1, 0, 2, 1, 1);
    gtk_widget_set_margin_top ( main_label1 , 20 );
    gtk_widget_set_margin_start ( main_label1 , 105 );


	main_label2 = gtk_label_new_with_mnemonic( cam_id2 );
    gtk_widget_override_font(main_label2,
                            pango_font_description_from_string("FreeSans 22"));
    gtk_widget_set_size_request(main_label2,260,40);
    gtk_grid_attach (GTK_GRID (grid), main_label2, 4, 2, 1, 1);
    gtk_widget_set_margin_top ( main_label2 , 20 );

	main_label3 = gtk_label_new_with_mnemonic( cam_id3 );
    gtk_widget_override_font(main_label3,
                            pango_font_description_from_string("FreeSans 22"));
    gtk_widget_set_size_request(main_label3,260,40);
    gtk_grid_attach (GTK_GRID (grid), main_label3, 7, 2, 1, 1);
    gtk_widget_set_margin_top ( main_label3 , 20 );
    gtk_widget_set_margin_start ( main_label3 , 30 );

	main_label4 = gtk_label_new_with_mnemonic("00-00-00");
    gtk_widget_override_font(main_label4,
                            pango_font_description_from_string("FreeSans 18"));
    gtk_widget_set_size_request(main_label4,260,40);
    gtk_grid_attach (GTK_GRID (grid), main_label4, 0, 3, 1, 1);
    gtk_widget_set_margin_top ( main_label4 , 10 );
    gtk_widget_set_margin_start ( main_label4 , 105 );
    
	main_label5 = gtk_label_new_with_mnemonic("00-00-00");
    gtk_widget_override_font(main_label5,
                            pango_font_description_from_string("FreeSans 18"));
    gtk_widget_set_size_request(main_label5,260,40);
    gtk_grid_attach (GTK_GRID (grid), main_label5, 4, 3, 1, 1);
    gtk_widget_set_margin_top ( main_label5 , 10 );

	main_label6 = gtk_label_new_with_mnemonic("00-00-00");
    gtk_widget_override_font(main_label6,
                            pango_font_description_from_string("FreeSans 18"));
    gtk_widget_set_size_request(main_label6,260,40);
    gtk_grid_attach (GTK_GRID (grid), main_label6, 7, 3, 1, 1);
    gtk_widget_set_margin_top ( main_label6 , 10 );
    gtk_widget_set_margin_start ( main_label6 , 30 );
    
    main_button1 = gtk_button_new_with_label( "Stop" );
    g_signal_connect( main_button1, "clicked",
		G_CALLBACK(main_button1_callback), main_button1 );
    gtk_widget_override_font(main_button1,
                            pango_font_description_from_string("FreeSans,Bold 12"));
    gtk_grid_attach (GTK_GRID (grid), main_button1, 4, 5, 1, 1);
    gtk_widget_set_margin_top ( main_button1, 40 );
    gtk_widget_set_margin_start ( main_button1, 0 );
    gtk_widget_set_margin_end ( main_button1, 0 );


    main_button3 = gtk_button_new_with_label( "Back" );
    g_signal_connect( main_button3, "clicked",
		G_CALLBACK(main_button2_callback), main_button3 );
    gtk_widget_override_font(main_button3,
                            pango_font_description_from_string("FreeSans,Bold 12"));
    gtk_grid_attach (GTK_GRID (grid), main_button3, 5, 5, 1, 1);
    gtk_widget_set_margin_top ( main_button3, 40 );
    gtk_widget_set_margin_start ( main_button3, 0 );
    gtk_widget_set_margin_end ( main_button3, 0 );

    label_head_server2 = gtk_label_new("Server : ");
    gtk_widget_override_font(label_head_server2,
                            pango_font_description_from_string("Monospace 9"));
    gtk_grid_attach (GTK_GRID (grid), label_head_server2, 0, 6, 1, 1);
    gtk_widget_set_margin_start ( label_head_server2, 0 );
    gtk_widget_set_margin_end ( label_head_server2, 345 );
    gtk_widget_set_margin_top ( label_head_server2, 57 );
    
    char temp[50];
    sprintf(temp,"%s ",server_name);

    label_sever2 = gtk_label_new(temp);
    gtk_widget_override_font(label_sever2,
                            pango_font_description_from_string("Monospace 9"));
    gtk_grid_attach (GTK_GRID (grid), label_sever2, 0, 6, 1, 1);
    gtk_widget_set_margin_start ( label_sever2, 0 );
    gtk_widget_set_margin_end ( label_sever2, 145 );
    gtk_widget_set_margin_top ( label_sever2, 57 );
    
    sprintf(temp,"%s",topic_name);

    label_head_topic2 = gtk_label_new("Topic  : ");
    gtk_widget_override_font(label_head_topic2,
                            pango_font_description_from_string("Monospace 9"));
    gtk_grid_attach (GTK_GRID (grid), label_head_topic2, 0, 7, 1, 1);
    gtk_widget_set_margin_start ( label_head_topic2, 0 );
    gtk_widget_set_margin_end ( label_head_topic2, 345 );
    gtk_widget_set_margin_top ( label_head_topic2, 5 );

    label_topic2 = gtk_label_new(temp);
    gtk_widget_override_font(label_topic2,
                            pango_font_description_from_string("Monospace 9"));
    gtk_grid_attach (GTK_GRID (grid), label_topic2, 0, 7, 1, 1);
    gtk_widget_set_margin_start ( label_topic2, 0 );
    gtk_widget_set_margin_end ( label_topic2, 155 );
    gtk_widget_set_margin_top ( label_topic2, 5 );


    main_status = gtk_label_new_with_mnemonic("");
    gtk_grid_attach (GTK_GRID (grid), main_status, 8, 6, 1, 1);
    gtk_widget_set_margin_start ( main_status, 0 );
    gtk_widget_set_margin_end ( main_status, 0 );
    gtk_widget_set_margin_top ( main_status, 55 );

    if(!is_connected){
        gtk_label_set_text(GTK_LABEL(main_status),"• Connect");
        gtk_widget_override_font(main_status,
                            pango_font_description_from_string("Monospace 9"));
    }
    else{
        gtk_label_set_text(GTK_LABEL(main_status),"• Disconnect");
        gtk_widget_override_font(main_status,
                            pango_font_description_from_string("Monospace 9"));
    }

	gtk_widget_show_all(window);

}



static gboolean name_pic( gpointer data ) {

	if(counter_enabled)
	{

		if(strstr(sub_text,cid1))
        {   
			strcpy(temp_str,sub_text);
			sp_cam = strtok(temp_str,"_");
			sp_cam = strtok(NULL,"_");
            sprintf(lebel_cam,"%s_%s",sp_cam,strtok(NULL,"_"));

            gtk_widget_override_font(main_label4,
                                pango_font_description_from_string("FreeSans 18"));
            gtk_label_set_text(GTK_LABEL(main_label4),lebel_cam);
			/* cam1_25-09-2021_17-14-49 */

            sprintf(temp_str,"sub_img/%s.jpg",sub_text);

			gtk_image_set_from_file(GTK_IMAGE(img1), temp_str);			

        }
		if(strstr(sub_text,cid2))
        {   
			strcpy(temp_str,sub_text);
			sp_cam = strtok(temp_str,"_");
			sp_cam = strtok(NULL,"_");
            sprintf(lebel_cam,"%s_%s",sp_cam,strtok(NULL,"_"));

            gtk_widget_override_font(main_label5,
                                pango_font_description_from_string("FreeSans 18"));
            gtk_label_set_text(GTK_LABEL(main_label5),lebel_cam);
			
            sprintf(temp_str,"sub_img/%s.jpg",sub_text);
			
			gtk_image_set_from_file(GTK_IMAGE(img2), temp_str);
			
        }
		if(strstr(sub_text,cid3))
        {   
			strcpy(temp_str,sub_text);
			sp_cam = strtok(temp_str,"_");
			sp_cam = strtok(NULL,"_");
            sprintf(lebel_cam,"%s_%s",sp_cam,strtok(NULL,"_"));

            gtk_widget_override_font(main_label6,
                                pango_font_description_from_string("FreeSans 18"));
            gtk_label_set_text(GTK_LABEL(main_label6),lebel_cam);

            sprintf(temp_str,"sub_img/%s.jpg",sub_text);
			
			gtk_image_set_from_file(GTK_IMAGE(img3), temp_str);
			
        }

	}
 
    if(!is_connected){

        gtk_label_set_text(GTK_LABEL(main_status),"• Connect");

    }
    else{

        gtk_label_set_text(GTK_LABEL(main_status),"• Disconnect");
        
    }
    


	return TRUE; 
}

GtkTreeModel *create_model(student text_data[1000]) {

    gint i = 0;
    GtkListStore *store;
    GtkTreeIter iter;

    /* create list store */
    store = gtk_list_store_new (NUM_COLUMNS,
                                
                                G_TYPE_STRING,   /* iD */
                                G_TYPE_STRING,    /* inDate */
                                G_TYPE_STRING

                                );    


    /* add data to the list store */
    for (i = 0; i < run_line; i++)
    {
        gtk_list_store_append (store, &iter);
        gtk_list_store_set (store, &iter,
                            
                            COLUMN_ID, text_data[i].iD,
                            COLUMN_DATE, text_data[i].inDate,
                            COLUMN_TIME, text_data[i].Time,
                            
                            -1);
  }

  return GTK_TREE_MODEL (store);
}

void add_columns (GtkTreeView *treeview) {

    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeModel *model = gtk_tree_view_get_model (treeview);

    /* column for iD */
    renderer = gtk_cell_renderer_text_new ();
    column = gtk_tree_view_column_new_with_attributes ("Cam ID",
            renderer,
            "text",
            COLUMN_ID,
            NULL);
    gtk_tree_view_column_set_sort_column_id (column, COLUMN_ID);
    gtk_tree_view_append_column (treeview, column);

    /* column for inscription date */
    renderer = gtk_cell_renderer_text_new ();
    column = gtk_tree_view_column_new_with_attributes ("Date",
            renderer,
            "text",
            COLUMN_DATE,
            NULL);
    gtk_tree_view_column_set_sort_column_id (column, COLUMN_DATE);
    gtk_tree_view_append_column (treeview, column);

    /* column for inscription date */
    renderer = gtk_cell_renderer_text_new ();
    column = gtk_tree_view_column_new_with_attributes ("Time",
            renderer,
            "text",
            COLUMN_TIME,
            NULL);
            
    gtk_tree_view_column_set_sort_column_id (column, COLUMN_TIME);
    gtk_tree_view_append_column (treeview, column);
  
}
