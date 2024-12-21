#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <stdbool.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "parking.h"

Parking p;
char types[30];
char state_text[30];
GtkWidget *radio_covered, *radio_uncovered;
GtkWidget *check_cars, *check_moto, *check_trucks;
void
on_button_modifyp_welcome_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
GtkNotebook *notebook; 
    notebook = GTK_NOTEBOOK(lookup_widget(GTK_WIDGET(button), "notebook1"));
    gtk_notebook_set_current_page(notebook, 3);
}


void
on_button_deletep_welcome_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
GtkNotebook *notebook; 
    notebook = GTK_NOTEBOOK(lookup_widget(GTK_WIDGET(button), "notebook1"));
    gtk_notebook_set_current_page(notebook, 4);
}


void
on_button_addp_welcome_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
GtkNotebook *notebook; 
    notebook = GTK_NOTEBOOK(lookup_widget(GTK_WIDGET(button), "notebook1"));
    gtk_notebook_set_current_page(notebook, 1);
}


void
on_button_wiewp_welcome_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
GtkNotebook *notebook; 
    notebook = GTK_NOTEBOOK(lookup_widget(GTK_WIDGET(button), "notebook1"));
    gtk_notebook_set_current_page(notebook, 2);
}


void
on_button_affectp_welcome_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
GtkNotebook *notebook; 
    notebook = GTK_NOTEBOOK(lookup_widget(GTK_WIDGET(button), "notebook1"));
    gtk_notebook_set_current_page(notebook, 5);
}


void
on_button_returnp_welcome_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_radio_covered_add_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) {
p.state = 1;
strcpy(p.state_text, "Covered");
}
}


void
on_radio_uncovered_add_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) {
p.state = 0;
strcpy(p.state_text, "Uncovered");
}
}


void
on_check_moto_add_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)) {
strcat(types, "Motorcycle");
}
}


void
on_check_trucks_add_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)) {
strcat(types, "Trucks");
}
}


void
on_check_cars_add_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)) {
strcat(types, "Cars");
}
}


void
on_button_savep_add_clicked(GtkWidget *button, gpointer user_data) {
    Parking p;

    GtkWidget *entry_idp = lookup_widget(button, "entry_idp_add");
    GtkWidget *entry_locationp = lookup_widget(button, "entry_locationp_add");
    GtkWidget *spin_total_spaces = lookup_widget(button, "spin_tsp_add");
    GtkWidget *spin_available_spaces = lookup_widget(button, "spin_asp_add");
    GtkWidget *entry_pricep = lookup_widget(button, "entry_pricep_add");
    GtkWidget *radio_covered = lookup_widget(button, "radio_covered_add");
    GtkWidget *radio_uncovered = lookup_widget(button, "radio_uncovered_add");
    GtkWidget *calendaryosr = lookup_widget(button, "calendaryosr1");
    GtkWidget *check_cars = lookup_widget(button, "check_cars_add");
    GtkWidget *check_moto = lookup_widget(button, "check_moto_add");
    GtkWidget *check_trucks = lookup_widget(button, "check_trucks_add");

    strcpy(p.id_parking, gtk_entry_get_text(GTK_ENTRY(entry_idp)));
    strcpy(p.location, gtk_entry_get_text(GTK_ENTRY(entry_locationp)));
    p.totalSpaces = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_total_spaces));
    p.availableSpaces = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_available_spaces));
    p.price = atof(gtk_entry_get_text(GTK_ENTRY(entry_pricep)));

    guint day, month, year;
    gtk_calendar_get_date(GTK_CALENDAR(calendaryosr), &year, &month, &day);
    p.openingDate.day = day;
    p.openingDate.month = month + 1;
    p.openingDate.year = year;

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_covered))) {
        p.state = 1;
        strcpy(p.state_text, "Covered");
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_uncovered))) {
        p.state = 0;
        strcpy(p.state_text, "Uncovered");
    }

    FILE *f = fopen("parking.txt", "a");
    GtkWidget *dialog;
    if (f != NULL) {
        fprintf(f, "%s %s %d %d %.2f %s %d %d %d %s\n", p.id_parking, p.location, p.totalSpaces, p.availableSpaces, p.price, p.state_text, p.openingDate.day, p.openingDate.month, p.openingDate.year, types);
        fclose(f);
        printf("Parking added successfully\n");

        dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_INFO,
                                        GTK_BUTTONS_OK,
                                        "Parking added successfully !");
    } else {
        printf("ERROR: COULD NOT OPEN THE FILE\n");

        dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_ERROR,
                                        GTK_BUTTONS_OK,
                                        "ERROR: COULD NOT OPEN THE FILE.");
    }

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}


void
on_button_cancelp_add_clicked          (GtkWidget       *button,
                                        gpointer         user_data)
{
GtkNotebook *notebook; 
    notebook = GTK_NOTEBOOK(lookup_widget(GTK_WIDGET(button), "notebook1"));
    gtk_notebook_set_current_page(notebook, 0);
}


void
on_button_refreshp_view_clicked        (GtkWidget      *button,
                                        gpointer         user_data)
{
GtkWidget *treeview;
    GtkListStore *store;
    GtkTreeIter iter;
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    FILE *f;

    treeview = lookup_widget(GTK_WIDGET(button), "treeview_parkingsyosr");

    // Vider le modèle actuel du treeview avant de le remplir à nouveau
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));
    if (store != NULL) {
        gtk_list_store_clear(store);  // Effacer les anciennes données du treeview
    }

    // Re-créer un store pour insérer les nouvelles données
    store = gtk_list_store_new(10, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_FLOAT, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING);

    // Lire les données depuis le fichier parking.txt
    Parking p;
    f = fopen("parking.txt", "r");
    if (f != NULL) {
        while (fscanf(f, "%s %s %d %d %f %s %d %d %d %s",
                      p.id_parking, p.location, &p.totalSpaces, &p.availableSpaces,
                      &p.price, p.state_text, &p.openingDate.day, &p.openingDate.month, 
                      &p.openingDate.year, p.types) != EOF) {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                               0, p.id_parking,
                               1, p.location,
                               2, p.totalSpaces,
                               3, p.availableSpaces,
                               4, p.price,
                               5, p.state_text,
                               6, p.openingDate.day,
                               7, p.openingDate.month,
                               8, p.openingDate.year,
                               9, p.types,
                               -1);
        }
        fclose(f);
    }

    // Appliquer le modèle de données au treeview
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
    g_object_unref(store);  // Libérer le modèle lorsque vous avez terminé
}



void
on_button_cancelp_view_clicked         (GtkWidget       *button,
                                        gpointer         user_data)
{
GtkNotebook *notebook; 
    notebook = GTK_NOTEBOOK(lookup_widget(GTK_WIDGET(button), "notebook1"));
    gtk_notebook_set_current_page(notebook, 0);
}


void
on_button_cancelp_modif_clicked        (GtkWidget       *button,
                                        gpointer         user_data)
{ 
  GtkNotebook *notebook; 
    notebook = GTK_NOTEBOOK(lookup_widget(GTK_WIDGET(button), "notebook1"));
    gtk_notebook_set_current_page(notebook, 0);
}

void
on_button_affect_affect_clicked        (GtkWidget       *button,
                                        gpointer         user_data)
{
    GtkWidget *parent = gtk_widget_get_parent(GTK_WIDGET(button));
    GtkComboBox *combo_agent = GTK_COMBO_BOX(lookup_widget(parent, "combo_yosr_agent"));
    GtkComboBox *combo_parking = GTK_COMBO_BOX(lookup_widget(parent, "combo_yosr_parking"));

    if (!GTK_IS_COMBO_BOX(combo_agent) || !GTK_IS_COMBO_BOX(combo_parking)) {
        g_print("Erreur : Les widgets ComboBox sont invalides.\n");
        return;
    }

    gchar *id_agent = NULL;
    gchar *id_parking = NULL;
    GtkTreeIter iter;

    if (gtk_combo_box_get_active_iter(combo_agent, &iter)) {
        GtkTreeModel *model = gtk_combo_box_get_model(combo_agent);
        gtk_tree_model_get(model, &iter, 0, &id_agent, -1);
    }

    if (gtk_combo_box_get_active_iter(combo_parking, &iter)) {
        GtkTreeModel *model = gtk_combo_box_get_model(combo_parking);
        gtk_tree_model_get(model, &iter, 0, &id_parking, -1);
    }

    if (id_agent == NULL || id_parking == NULL) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "You have to select an agent and a parking");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    FILE *file = fopen("affectations.txt", "a");
    if (file == NULL) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Erreur lors de l'ouverture du fichier.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    fprintf(file, "Agent %s affected to parking %s\n", id_agent, id_parking);
    fclose(file);  

    g_free(id_agent);
    g_free(id_parking);

    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                               GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_INFO,
                                               GTK_BUTTONS_OK,
                                               "Successfull Affectation !");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}


void on_button_cancelp_cancel_clicked(GtkWidget *button, gpointer user_data) {
   GtkNotebook *notebook; 
    notebook = GTK_NOTEBOOK(lookup_widget(GTK_WIDGET(button), "notebook1"));
    gtk_notebook_set_current_page(notebook, 0);
}


void
on_button_cancelp_delete_clicked       (GtkWidget       *button,
                                        gpointer         user_data)
{
GtkNotebook *notebook; 
    notebook = GTK_NOTEBOOK(lookup_widget(GTK_WIDGET(button), "notebook1"));
    gtk_notebook_set_current_page(notebook, 0);
}


void
on_ok_yosr_delete_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_radio_covered_motify_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) {
        p.state = 1;
        strcpy(p.state_text, "Covered");
    }
}

void
on_radio_uncovered_modify_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton))) {
        p.state = 0;
        strcpy(p.state_text, "Uncovered");
    }
}

void
on_check_cars_modify_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if(gtk_toggle_button_get_active(togglebutton)) {
        strcat(types, "Cars ");
    }
}

void
on_check_moto_modify_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if(gtk_toggle_button_get_active(togglebutton)) {
        strcat(types, "Motorcycle ");
    }
}

void
on_check_trucks_modify_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if(gtk_toggle_button_get_active(togglebutton)) {
        strcat(types, "Trucks ");
    }
}

void
on_button_modif_modif_clicked          (GtkWidget       *button,
                                        gpointer         user_data)
{

    Parking p;
    char types[256] = ""; 
    GtkWidget *entry_idp = lookup_widget(GTK_WIDGET(button), "entry_idp_modify");
    GtkWidget *entry_locationp = lookup_widget(GTK_WIDGET(button), "entry_locationp_modify");
    GtkWidget *spin_total_spaces = lookup_widget(GTK_WIDGET(button), "spin_tsp_modify");
    GtkWidget *spin_available_spaces = lookup_widget(GTK_WIDGET(button), "spin_asp_modify");
    GtkWidget *entry_pricep = lookup_widget(GTK_WIDGET(button), "entry_pricep_modify");
    GtkWidget *radio_covered = lookup_widget(GTK_WIDGET(button), "radio_covered_modify");
    GtkWidget *radio_uncovered = lookup_widget(GTK_WIDGET(button), "radio_uncovered_modify");
    GtkWidget *calendaryosr = lookup_widget(GTK_WIDGET(button), "calendaryosr1_modify");
    GtkWidget *check_cars = lookup_widget(GTK_WIDGET(button), "check_cars_modify");
    GtkWidget *check_moto = lookup_widget(GTK_WIDGET(button), "check_moto_modify");
    GtkWidget *check_trucks = lookup_widget(GTK_WIDGET(button), "check_trucks_modify");

    if (!entry_idp || !entry_locationp || !spin_total_spaces || !spin_available_spaces || 
        !entry_pricep || !radio_covered || !radio_uncovered || !calendaryosr || 
        !check_cars || !check_moto || !check_trucks) {
        printf("ERROR: Could not find all necessary widgets\n");
        return;
    }

    strcpy(p.id_parking, gtk_entry_get_text(GTK_ENTRY(entry_idp)));
    strcpy(p.location, gtk_entry_get_text(GTK_ENTRY(entry_locationp)));
    p.totalSpaces = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_total_spaces));
    p.availableSpaces = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_available_spaces));
    p.price = atof(gtk_entry_get_text(GTK_ENTRY(entry_pricep)));

    guint day, month, year;
    gtk_calendar_get_date(GTK_CALENDAR(calendaryosr), &year, &month, &day);
    p.openingDate.day = day;
    p.openingDate.month = month + 1;
    p.openingDate.year = year;

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_covered))) {
        p.state = 1;
        strcpy(p.state_text, "Covered");
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_uncovered))) {
        p.state = 0;
        strcpy(p.state_text, "Uncovered");
    }

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_cars))) {
        strcat(types, "Cars ");
    }
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_moto))) {
        strcat(types, "Motorcycle ");
    }
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_trucks))) {
        strcat(types, "Trucks ");
    }

GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_YES_NO,
        "Do you really want to modify this parking?"
    );

    int response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    // Si l'utilisateur clique sur "No", quitter la fonction
    if (response != GTK_RESPONSE_YES) {
        return;
    }

    FILE *f = fopen("parking.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    Parking temp_p;
    int found = 0;

    if (f != NULL && temp != NULL) {
        while (fscanf(f, " %s %s %d %d %f %s %d %d %d %[^\n]s \n", temp_p.id_parking, temp_p.location, &temp_p.totalSpaces, &temp_p.availableSpaces, &temp_p.price, temp_p.state_text, &temp_p.openingDate.day, &temp_p.openingDate.month, &temp_p.openingDate.year, types) != EOF) {
            if (strcmp(temp_p.id_parking, p.id_parking) == 0) {
                found = 1;
                fprintf(temp, " %s %s %d %d %.2f %s %d %d %d %s \n", p.id_parking, p.location, p.totalSpaces, p.availableSpaces, p.price, p.state_text, p.openingDate.day, p.openingDate.month, p.openingDate.year, types);
            } else {
                fprintf(temp, " %s %s %d %d %.2f %s %d %d %d %s \n", temp_p.id_parking, temp_p.location, temp_p.totalSpaces, temp_p.availableSpaces, temp_p.price, temp_p.state_text, temp_p.openingDate.day, temp_p.openingDate.month, temp_p.openingDate.year, types);
            }
        }
        fclose(f);
        fclose(temp);
        remove("parking.txt");
        rename("temp.txt", "parking.txt");
       dialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            found ? "Parking modified successfully!" : "Parking not found!"
        );
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    } else {
        printf("ERROR: COULD NOT OPEN THE FILE\n");
    }
}
void on_button_searchpyosr_clicked(GtkWidget *button, gpointer user_data) {
{
    char id_to_findp[20];
    char line[256];
    FILE *f;
    GtkWidget *entry_idp = lookup_widget(GTK_WIDGET(button), "entry_idp_modify");
    strcpy(id_to_findp, gtk_entry_get_text(GTK_ENTRY(entry_idp)));


    bool found = false;

    f = fopen("parking.txt", "r");
    if (f == NULL) {
        printf("ERROR: FILE NOT FOUND\n");
        return;
    }

    while (fgets(line, sizeof(line), f)) {
        Parking p;
        sscanf(line, " %s %s %d %d %f %s %d %d %d %[^\n]s \n",
               p.id_parking, p.location, &p.totalSpaces, &p.availableSpaces, &p.price,
               p.state_text, &p.openingDate.day, &p.openingDate.month, &p.openingDate.year, p.types);

        if (strcmp(id_to_findp, p.id_parking) == 0) {
            found = true;

            GtkWidget *entry_locationp = lookup_widget(GTK_WIDGET(button), "entry_locationp_modify");
            GtkWidget *spin_total_spaces = lookup_widget(GTK_WIDGET(button), "spin_tsp_modify");
            GtkWidget *spin_available_spaces = lookup_widget(GTK_WIDGET(button), "spin_asp_modify");
            GtkWidget *entry_pricep = lookup_widget(GTK_WIDGET(button), "entry_pricep_modify");
            GtkWidget *radio_covered = lookup_widget(GTK_WIDGET(button), "radio_covered_modify");
            GtkWidget *radio_uncovered = lookup_widget(GTK_WIDGET(button), "radio_uncovered_modify");
            GtkWidget *calendaryosr = lookup_widget(GTK_WIDGET(button), "calendaryosr1_modify");
            GtkWidget *check_cars = lookup_widget(GTK_WIDGET(button), "check_cars_modify");
            GtkWidget *check_moto = lookup_widget(GTK_WIDGET(button), "check_moto_modify");
            GtkWidget *check_trucks = lookup_widget(GTK_WIDGET(button), "check_trucks_modify");

            gtk_entry_set_text(GTK_ENTRY(entry_locationp), p.location);
            gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_total_spaces), p.totalSpaces);
            gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_available_spaces), p.availableSpaces);
            gtk_entry_set_text(GTK_ENTRY(entry_pricep), g_strdup_printf("%.2f", p.price));

            if (strcmp(p.state_text, "Covered") == 0)
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_covered), TRUE);
            else
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_uncovered), TRUE);

            gtk_calendar_select_month(GTK_CALENDAR(calendaryosr), p.openingDate.month - 1, p.openingDate.year);
            gtk_calendar_select_day(GTK_CALENDAR(calendaryosr), p.openingDate.day);

            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_cars), strstr(p.types, "Cars") != NULL);
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_moto), strstr(p.types, "Motorcycle") != NULL);
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_trucks), strstr(p.types, "Trucks") != NULL);
            break;
        }
    }
    fclose(f);

GtkWidget *dialog;
    if (found) {
        dialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(button)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "Parking found!"
        );
    } else {
        dialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(button)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Parking not found!"
        );
    }

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
}

/*void
on_button1_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
 {
    
}*/

void
on_button_deletep_delete_clicked       (GtkWidget       *button,
                                        gpointer         user_data)
{

char id_to_delete[20];
    GtkWidget *entry_idp_delete = lookup_widget(GTK_WIDGET(button), "entry_idp_delete");
    strcpy(id_to_delete, gtk_entry_get_text(GTK_ENTRY(entry_idp_delete)));

    // Récupérer le label pour afficher les résultats
    GtkWidget *label_yosr_pdelete = lookup_widget(GTK_WIDGET(button), "label_yosr_pdelete");
    bool found = false;

    // Ouvrir le fichier parking.txt pour lecture
    FILE *f = fopen("parking.txt", "r");
    if (f == NULL) {
        printf("ERROR: FILE NOT FOUND\n");
       GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                                         GTK_DIALOG_MODAL,
                                                         GTK_MESSAGE_ERROR,
                                                         GTK_BUTTONS_OK,
                                                         "Error opening file.");
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);
        return;
    }

    // Fichier temporaire pour stocker les parkings restants
    FILE *temp_file = fopen("temp_parking.txt", "w");
    if (temp_file == NULL) {
        printf("ERROR: CREATING TEMP FILE\n");
          GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                                         GTK_DIALOG_MODAL,
                                                         GTK_MESSAGE_ERROR,
                                                         GTK_BUTTONS_OK,
                                                         "Error creating temporary file.");
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);
        fclose(f);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        Parking p;
        sscanf(line, " %s %s %d %d %f %s %d %d %d %[^\n]s \n",
               p.id_parking, p.location, &p.totalSpaces, &p.availableSpaces, &p.price,
               p.state_text, &p.openingDate.day, &p.openingDate.month, &p.openingDate.year, p.types);


        if (strcmp(id_to_delete, p.id_parking) == 0) {
            found = true;  
        } else {
           
            fprintf(temp_file, "%s %s %d %d %.2f %s %d %d %d %s\n",
                    p.id_parking, p.location, p.totalSpaces, p.availableSpaces, p.price,
                    p.state_text, p.openingDate.day, p.openingDate.month, p.openingDate.year, p.types);
        }
    }

    fclose(f);
    fclose(temp_file);


    if (found) {
 GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_QUESTION,
                                                   GTK_BUTTONS_YES_NO,
                                                   "Are you sure you want to delete this parking?");
        gint response = gtk_dialog_run(GTK_DIALOG(dialog));



        if (response == GTK_RESPONSE_YES) {


        remove("parking.txt"); 
        rename("temp_parking.txt", "parking.txt");  
   
 GtkWidget *success_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                                               GTK_DIALOG_MODAL,
                                                               GTK_MESSAGE_INFO,
                                                               GTK_BUTTONS_OK,
                                                               "Parking deleted successfully.");
            gtk_dialog_run(GTK_DIALOG(success_dialog));
            gtk_widget_destroy(success_dialog);
        } else {
            // Si l'utilisateur annule, supprimer le fichier temporaire
            remove("temp_parking.txt");
            GtkWidget *cancel_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                                              GTK_DIALOG_MODAL,
                                                              GTK_MESSAGE_INFO,
                                                              GTK_BUTTONS_OK,
                                                              "Parking deletion canceled.");
            gtk_dialog_run(GTK_DIALOG(cancel_dialog));
            gtk_widget_destroy(cancel_dialog);
        }
        gtk_widget_destroy(dialog);
    } else {
        // Si le parking n'est pas trouvé, supprimer le fichier temporaire
        remove("temp_parking.txt");
        GtkWidget *not_found_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(button)),
                                                             GTK_DIALOG_MODAL,
                                                             GTK_MESSAGE_ERROR,
                                                             GTK_BUTTONS_OK,
                                                             "Parking not found.");
        gtk_dialog_run(GTK_DIALOG(not_found_dialog));
        gtk_widget_destroy(not_found_dialog);
    }
}



void
on_display_view_yosr_clicked           (GtkWidget       *button,
                                        gpointer         user_data)
{
 GtkWidget *treeview;
    GtkListStore *store;
    GtkTreeIter iter;
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    FILE *f;

    treeview = lookup_widget(GTK_WIDGET(button), "treeview_parkingsyosr");

    if (gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)) == NULL) {
        renderer = gtk_cell_renderer_text_new();

        column = gtk_tree_view_column_new_with_attributes("ID Parking", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        column = gtk_tree_view_column_new_with_attributes("Location", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        column = gtk_tree_view_column_new_with_attributes("Total Spaces", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        column = gtk_tree_view_column_new_with_attributes("Available Spaces", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        column = gtk_tree_view_column_new_with_attributes("Price", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        column = gtk_tree_view_column_new_with_attributes("State", renderer, "text", 5, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        column = gtk_tree_view_column_new_with_attributes("Opening Day", renderer, "text", 6, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        column = gtk_tree_view_column_new_with_attributes("Opening Month", renderer, "text", 7, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        column = gtk_tree_view_column_new_with_attributes("Opening Year", renderer, "text", 8, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
        column = gtk_tree_view_column_new_with_attributes("Type of Spaces", renderer, "text", 9, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    }

    store = gtk_list_store_new(10, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_FLOAT, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT,  G_TYPE_STRING);

    Parking p;
    f = fopen("parking.txt", "r");
    if (f != NULL) {
        while (fscanf(f, "%s %s %d %d %f %s %d %d %d %s",
                      p.id_parking, p.location, &p.totalSpaces, &p.availableSpaces,
                      &p.price, p.state_text, &p.openingDate.day, &p.openingDate.month, 
                      &p.openingDate.year, p.types) != EOF) {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                               0, p.id_parking,
                               1, p.location,
                               2, p.totalSpaces,
                               3, p.availableSpaces,
                               4, p.price,
                               5, p.state_text,
                               6, p.openingDate.day,
                               7, p.openingDate.month,
                               8, p.openingDate.year,
                               9, p.types,
                               -1);
        }
        fclose(f);
        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
        g_object_unref(store);
    }
}


void
on_search_yosr_delete_clicked          (GtkWidget       *button,
                                        gpointer         user_data)
{
char id_to_find[20];
    GtkWidget *entry_idp_delete = lookup_widget(GTK_WIDGET(button), "entry_idp_delete");
    strcpy(id_to_find, gtk_entry_get_text(GTK_ENTRY(entry_idp_delete)));



    bool found = false;


    FILE *f = fopen("parking.txt", "r");
    if (f == NULL) {
        printf("ERROR: FILE NOT FOUND\n");
 GtkWidget *error_dialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Error opening file."
        );
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);


        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        Parking p;
        sscanf(line, " %s %s %d %d %f %s %d %d %d %[^\n]s \n",
               p.id_parking, p.location, &p.totalSpaces, &p.availableSpaces, &p.price,
               p.state_text, &p.openingDate.day, &p.openingDate.month, &p.openingDate.year, p.types);


        if (strcmp(id_to_find, p.id_parking) == 0) {
            found = true;
            break; 
        }
    }

    fclose(f);

    GtkWidget *dialog;
    if (found) {
        dialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "Parking found."
        );
    } else {
        dialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Parking not found."
        );
    }

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
  






void
on_refresh_yosr1_clicked               (GtkWidget       *button,
                                        gpointer         user_data)
{
   GtkWidget *entry_idp, *entry_locationp, *spin_total_spaces, *spin_available_spaces; 
    GtkWidget *entry_pricep, *radio_covered, *radio_uncovered, *calendaryosr ;
    GtkWidget *check_cars, *check_moto, *check_trucks;
 entry_idp = lookup_widget(button, "entry_idp_add");
 entry_locationp = lookup_widget(button, "entry_locationp_add");
 spin_total_spaces = lookup_widget(button, "spin_tsp_add");
 spin_available_spaces = lookup_widget(button, "spin_asp_add");
 entry_pricep = lookup_widget(button, "entry_pricep_add");
 radio_covered = lookup_widget(button, "radio_covered_add");
 radio_uncovered = lookup_widget(button, "radio_uncovered_add");
 calendaryosr = lookup_widget(button, "calendaryosr1");
 check_cars = lookup_widget(button, "check_cars_add");
 check_moto = lookup_widget(button, "check_moto_add");
 check_trucks = lookup_widget(button, "check_trucks_add");

  if (!entry_idp || !entry_locationp || !spin_total_spaces || !spin_available_spaces || 
        !entry_pricep || !radio_covered || !radio_uncovered || !calendaryosr || 
        !check_cars || !check_moto || !check_trucks) {
        g_print("Erreur : Un ou plusieurs widgets n'ont pas été trouvés.\n");
        return;
    }

    gtk_entry_set_text(GTK_ENTRY(entry_idp), "");
    gtk_entry_set_text(GTK_ENTRY(entry_locationp), "");
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_total_spaces), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_available_spaces), 0);
    gtk_entry_set_text(GTK_ENTRY(entry_pricep), "");

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_covered), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_uncovered), FALSE);

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_cars), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_moto), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_trucks), FALSE);

    g_print("Les champs ont été réinitialisés.\n");
}


void
on_refresh_yosr2_clicked               (GtkWidget       *button,
                                        gpointer         user_data)
{
  GtkWidget *entry_idp, *entry_locationp, *spin_total_spaces, *spin_available_spaces, *entry_pricep;
    GtkWidget *radio_covered, *radio_uncovered, *calendaryosr, *check_cars, *check_moto, *check_trucks;

    entry_idp = lookup_widget(GTK_WIDGET(button), "entry_idp_modify");
    entry_locationp = lookup_widget(GTK_WIDGET(button), "entry_locationp_modify");
    spin_total_spaces = lookup_widget(GTK_WIDGET(button), "spin_tsp_modify");
    spin_available_spaces = lookup_widget(GTK_WIDGET(button), "spin_asp_modify");
    entry_pricep = lookup_widget(GTK_WIDGET(button), "entry_pricep_modify");
    radio_covered = lookup_widget(GTK_WIDGET(button), "radio_covered_modify");
    radio_uncovered = lookup_widget(GTK_WIDGET(button), "radio_uncovered_modify");
    calendaryosr = lookup_widget(GTK_WIDGET(button), "calendaryosr1_modify");
    check_cars = lookup_widget(GTK_WIDGET(button), "check_cars_modify");
    check_moto = lookup_widget(GTK_WIDGET(button), "check_moto_modify");
    check_trucks = lookup_widget(GTK_WIDGET(button), "check_trucks_modify");

    if (!entry_idp || !entry_locationp || !spin_total_spaces || !spin_available_spaces || 
        !entry_pricep || !radio_covered || !radio_uncovered || !calendaryosr || 
        !check_cars || !check_moto || !check_trucks) {
        g_print("Erreur : Un ou plusieurs widgets n'ont pas été trouvés.\n");
        return;
    }

    gtk_entry_set_text(GTK_ENTRY(entry_idp), "");
    gtk_entry_set_text(GTK_ENTRY(entry_locationp), "");
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_total_spaces), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_available_spaces), 0);
    gtk_entry_set_text(GTK_ENTRY(entry_pricep), "");

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_covered), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_uncovered), FALSE);

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_cars), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_moto), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_trucks), FALSE);

    g_print("Les champs ont été réinitialisés.\n");
}


void
on_refresh_yosr3_clicked               (GtkWidget      *button,
                                        gpointer         user_data)
{
    GtkWidget *combo1, *combo2;

    combo1 = lookup_widget(GTK_WIDGET(button), "combo_yosr_agent");
    combo2 = lookup_widget(GTK_WIDGET(button), "combo_yosr_parking");

    if (!combo1 || !combo2) {
        g_print("Erreur : Un ou plusieurs widgets n'ont pas été trouvés.\n");
        return;
    }
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo1), -1);
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo2), -1);

    g_print("Les champs ComboBox ont été réinitialisés.\n");
}

