#include <gtk/gtk.h>   // GTK+ header for GUI functions
#include <stdio.h>     // Standard I/O library for file operations
#include <string.h>    // String library for string operations
#include <openssl/aes.h>  // AES encryption library
#include <openssl/rand.h> // Random number generator for AES key and IV
<<<<<<< Updated upstream
#include <openssl/evp.h>
#include <ctype.h>

#define CREDENTIALS_FILE "credentials.txt" // File to store credentials
#define EN_CREDENTIALS_FILE "credentials.txt.enc" // File to store credentials
=======

#define CREDENTIALS_FILE "credentials.txt" // File to store credentials
>>>>>>> Stashed changes

// AES encryption/decryption key and IV
#define AES_KEY_SIZE 256 // AES key size in bits
#define AES_IV_SIZE 16   // AES IV size in bytes

// Function prototypes
static void on_signup_button_clicked(GtkButton *button, gpointer user_data);
static void on_login_button_clicked(GtkButton *button, gpointer user_data);
static void handle_signup(const char *username, const char *password);
static void validate_login(const char *username, const char *password);
static void on_exit_button_clicked(GtkButton *button, gpointer user_data);
static gboolean username_exists(const char *username);
static void show_file_type_dialog();
static void show_encryption_dialog();
static void show_decryption_dialog();
<<<<<<< Updated upstream
static void encrypt_file(char *filename);
static void decrypt_file(char *filename);
static gboolean validate_password(const char *password);
=======
static void encrypt_file(const char *filename);
static void decrypt_file(const char *filename);
>>>>>>> Stashed changes

// Global variables for GTK widgets
static GtkWidget *entry_username_signup;  // Entry widget for username on signup page
static GtkWidget *entry_password_signup;  // Entry widget for password on signup page
static GtkWidget *entry_username_login;   // Entry widget for username on login page
static GtkWidget *entry_password_login;   // Entry widget for password on login page
static GtkWidget *status_label;           // Label to display status messages
static GtkWidget *notebook;               // Notebook widget to switch between pages

// AES encryption key and IV
static unsigned char aes_key[AES_KEY_SIZE / 8];
static unsigned char aes_iv[AES_IV_SIZE];

int main(int argc, char *argv[]) 
{
    GtkWidget *window;      // Main application window
    GtkWidget *signup_page; // Widget for the signup page
    GtkWidget *login_page;  // Widget for the login page

    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create the main window and setting its properties
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "File Encryption/Decryption"); // Set window title
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);    // Set default window size
    gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
<<<<<<< Updated upstream
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);							       //
=======
>>>>>>> Stashed changes
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL); // Connect destroy signal to exit GTK main loop

    // Create a notebook widget to allow switching between signup and login pages
    notebook = gtk_notebook_new();
    gtk_container_add(GTK_CONTAINER(window), notebook); // Add notebook to the main window

    // Signup Page
    signup_page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5); // Create a vertical box for layout
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), signup_page, gtk_label_new("Signup")); // Add signup page to notebook

    // Create and add widgets for signup page
    GtkWidget *label_username_signup = gtk_label_new("Username:"); // Create a label for username
    gtk_box_pack_start(GTK_BOX(signup_page), label_username_signup, FALSE, FALSE, 5); // Add label to vertical box

    entry_username_signup = gtk_entry_new(); // Create an entry widget for username
    gtk_box_pack_start(GTK_BOX(signup_page), entry_username_signup, FALSE, FALSE, 5); // Add entry to vertical box

    GtkWidget *label_password_signup = gtk_label_new("Password:"); // Create a label for password
    gtk_box_pack_start(GTK_BOX(signup_page), label_password_signup, FALSE, FALSE, 5); // Add label to vertical box

    entry_password_signup = gtk_entry_new(); // Create an entry widget for password
    gtk_entry_set_visibility(GTK_ENTRY(entry_password_signup), FALSE); // Hide password text
    gtk_box_pack_start(GTK_BOX(signup_page), entry_password_signup, FALSE, FALSE, 5); // Add entry to vertical box

    GtkWidget *button_signup = gtk_button_new_with_label("Signup"); // Create a signup button
    gtk_box_pack_start(GTK_BOX(signup_page), button_signup, FALSE, FALSE, 5); // Add button to vertical box
    g_signal_connect(button_signup, "clicked", G_CALLBACK(on_signup_button_clicked), NULL); // Connect button click signal to handler

    // Add Exit Button on Signup Page
    GtkWidget *button_exit_signup = gtk_button_new_with_label("Exit"); // Create an exit button
    gtk_box_pack_start(GTK_BOX(signup_page), button_exit_signup, FALSE, FALSE, 5); // Add exit button to vertical box
    g_signal_connect(button_exit_signup, "clicked", G_CALLBACK(on_exit_button_clicked), NULL); // Connect exit button to handler

    // Login Page
    login_page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5); // Create a vertical box for layout
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), login_page, gtk_label_new("Login")); // Add login page to notebook

    // Create and add widgets for login page
    GtkWidget *label_username_login = gtk_label_new("Username:"); // Create a label for username
    gtk_box_pack_start(GTK_BOX(login_page), label_username_login, FALSE, FALSE, 5); // Add label to vertical box

    entry_username_login = gtk_entry_new(); // Create an entry widget for username
    gtk_box_pack_start(GTK_BOX(login_page), entry_username_login, FALSE, FALSE, 5); // Add entry to vertical box

    GtkWidget *label_password_login = gtk_label_new("Password:"); // Create a label for password
    gtk_box_pack_start(GTK_BOX(login_page), label_password_login, FALSE, FALSE, 5); // Add label to vertical box

    entry_password_login = gtk_entry_new(); // Create an entry widget for password
    gtk_entry_set_visibility(GTK_ENTRY(entry_password_login), FALSE); // Hide password text
    gtk_box_pack_start(GTK_BOX(login_page), entry_password_login, FALSE, FALSE, 5); // Add entry to vertical box

    GtkWidget *button_login = gtk_button_new_with_label("Login"); // Create a login button
    gtk_box_pack_start(GTK_BOX(login_page), button_login, FALSE, FALSE, 5); // Add button to vertical box
    g_signal_connect(button_login, "clicked", G_CALLBACK(on_login_button_clicked), NULL); // Connect button click signal to handler

    GtkWidget *button_exit_login = gtk_button_new_with_label("Exit"); // Create an exit button
    gtk_box_pack_start(GTK_BOX(login_page), button_exit_login, FALSE, FALSE, 5); // Add exit button to vertical box
    g_signal_connect(button_exit_login, "clicked", G_CALLBACK(on_exit_button_clicked), NULL); // Connect exit button to handler

    status_label = gtk_label_new(""); // Create a status label for displaying messages
    gtk_box_pack_start(GTK_BOX(login_page), status_label, FALSE, FALSE, 5); // Add status label to vertical box

    gtk_widget_show_all(window); // Show all widgets
    gtk_main(); // Enter the GTK main loop

    return 0; // Return from main
}

// Callback function for signup button click
static void on_signup_button_clicked(GtkButton *button, gpointer user_data) {
    const gchar *username = gtk_entry_get_text(GTK_ENTRY(entry_username_signup)); // Get username from entry
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(entry_password_signup)); // Get password from entry

    handle_signup(username, password); // Handle signup
}

// Callback function for login button click
static void on_login_button_clicked(GtkButton *button, gpointer user_data) {
    const gchar *username = gtk_entry_get_text(GTK_ENTRY(entry_username_login)); // Get username from entry
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(entry_password_login)); // Get password from entry

    validate_login(username, password); // Validate login
}

// Function to handle user signup
static void handle_signup(const char *username, const char *password) 
{
    // Check if the username already exists
    if (username_exists(username)) 
    {
        // Display success dialog
        GtkWidget *dialog = gtk_message_dialog_new
        (
            GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(status_label))),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "Username already exists. Try another username."
        );
    
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
<<<<<<< Updated upstream
    
    if (!validate_password(password)) 
    {
        // Display error dialog for invalid password
        GtkWidget *dialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(status_label))),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Password must be 8-12 characters long, contain at least one uppercase letter, one lowercase letter, one number, and one special character, and must not start with a special character."
        );
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    decrypt_file(EN_CREDENTIALS_FILE);
=======
>>>>>>> Stashed changes

    FILE *file = fopen(CREDENTIALS_FILE, "a"); // Open credentials file in append mode
    
    if (file == NULL) 
    {
        gtk_label_set_text(GTK_LABEL(status_label), "Error: Unable to open credentials file."); // Display error if file cannot be opened
        return;
    }

    fprintf(file, "%s %s\n", username, password); // Write username and password to file
    fclose(file); // Close the file

<<<<<<< Updated upstream
    encrypt_file(CREDENTIALS_FILE);
    
=======
>>>>>>> Stashed changes
    // Display success dialog
    GtkWidget *dialog = gtk_message_dialog_new
    (
        GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(status_label))),
        GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
<<<<<<< Updated upstream
        "Signup successful! You can now login."
    );
    
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

// Function to validate the password based on specified rules
static gboolean validate_password(const char *password) 
{
    int length = strlen(password);
    if (length < 8 || length > 12) 
    {
        return FALSE;
    }

    if (!isalnum(password[0])) 
    {
        return FALSE;
    }

    gboolean has_upper = FALSE, has_lower = FALSE, has_digit = FALSE, has_special = FALSE;

    for (int i = 0; i < length; i++) 
    {
        if (isupper(password[i])) has_upper = TRUE;
        if (islower(password[i])) has_lower = TRUE;
        if (isdigit(password[i])) has_digit = TRUE;
        if (ispunct(password[i])) has_special = TRUE;
    }

    return has_upper && has_lower && has_digit && has_special;
=======
        "Signup successful! Redirecting to login..."
    );

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook), 1); // Switch to login page
>>>>>>> Stashed changes
}

// Function to validate user login
static void validate_login(const char *username, const char *password) 
{
<<<<<<< Updated upstream
    decrypt_file(EN_CREDENTIALS_FILE);

    FILE *file = fopen(CREDENTIALS_FILE, "r"); // Open credentials file in read mode

    if (file == NULL) 
    {
        gtk_label_set_text(GTK_LABEL(status_label), "Error: Unable to open credentials file."); // Display error if file cannot be opened
        return;
    }

    char stored_username[256], stored_password[256]; // Buffers for storing username and password
    gboolean login_successful = FALSE; // Flag to track login success

    // Read credentials from file and check if username and password match
    while (fscanf(file, "%255s %255s", stored_username, stored_password) == 2) 
    {
        if (strcmp(username, stored_username) == 0 && strcmp(password, stored_password) == 0) 
        {
            login_successful = TRUE; // Set flag if credentials match
            break;
=======
    FILE *file = fopen(CREDENTIALS_FILE, "r"); // Opening file in read mode
    
    if (file == NULL) 
    {
        gtk_label_set_text(GTK_LABEL(status_label), "Error: Unable to open credentials file."); // Display error if file not opened
        return;
    }

    char stored_username[256]; // Buffer to store usernames read from the file
    char stored_password[256]; // Buffer to store passwords read from the file
    int valid = 0; // Flag to indicate if the login is valid

    while (fscanf(file, "%255s %255s", stored_username, stored_password) == 2) 
    { // Read username and password from file
        if (strcmp(username, stored_username) == 0 && strcmp(password, stored_password) == 0) 
        { // Check if credentials match
            valid = 1; // Set valid flag
            break; // Exit loop if match found
>>>>>>> Stashed changes
        }
    }

    fclose(file); // Close the file

<<<<<<< Updated upstream
    encrypt_file(CREDENTIALS_FILE);

    if (login_successful) 
    {
        show_file_type_dialog(); // Show options for encryption or decryption
    } 
    else 
    {
        // Display error dialog for incorrect username or password
=======
    if (valid) 
    {
        // Display success dialog
>>>>>>> Stashed changes
        GtkWidget *dialog = gtk_message_dialog_new
        (
            GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(status_label))),
            GTK_DIALOG_DESTROY_WITH_PARENT,
<<<<<<< Updated upstream
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Invalid username or password."
        );
        
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

// Function to check if a username already exists
static gboolean username_exists(const char *username) 
{

    decrypt_file(EN_CREDENTIALS_FILE);
    
    FILE *file = fopen(CREDENTIALS_FILE, "r"); // Open credentials file in read mode

=======
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            "Successfully logged in!"
        );
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        // Close login window
        gtk_widget_destroy(GTK_WIDGET(gtk_widget_get_toplevel(GTK_WIDGET(status_label))));

        // Show options for encryption or decryption
        show_file_type_dialog();
    } 
    else 
    {
        gtk_label_set_text(GTK_LABEL(status_label), "Invalid username or password."); // Display error message
    }
}

// Function to show file type selection dialog for encryption
static void show_file_type_dialog() 
{
    GtkWidget *dialog_options = gtk_message_dialog_new
    (
        GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(status_label))),
        GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_NONE,
        "Choose an option:"
    );
    gtk_dialog_add_buttons(GTK_DIALOG(dialog_options),
                           "Encryption", GTK_RESPONSE_YES,
                           "Decryption", GTK_RESPONSE_NO,
                           NULL);

    gint result = gtk_dialog_run(GTK_DIALOG(dialog_options));
    gtk_widget_destroy(dialog_options);

    if (result == GTK_RESPONSE_YES) {
        show_encryption_dialog();
    } else if (result == GTK_RESPONSE_NO) {
        show_decryption_dialog();
    }
}

// Function to show file type selection dialog for encryption
static void show_encryption_dialog() 
{
    GtkWidget *dialog;
    GtkFileFilter *filter;

    // Create a file chooser dialog
    dialog = gtk_file_chooser_dialog_new("Select File to Encrypt",
                                         NULL,
                                         GTK_FILE_CHOOSER_ACTION_OPEN,
                                         "_Cancel",
                                         GTK_RESPONSE_CANCEL,
                                         "_Select",
                                         GTK_RESPONSE_ACCEPT,
                                         NULL);

    // Add filters for common file types
    filter = gtk_file_filter_new();
    gtk_file_filter_set_name(filter, "All Files");
    gtk_file_filter_add_pattern(filter, "*");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

    filter = gtk_file_filter_new();
    gtk_file_filter_set_name(filter, "Text Files");
    gtk_file_filter_add_pattern(filter, "*.txt");
    gtk_file_filter_add_pattern(filter, "*.text");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

    filter = gtk_file_filter_new();
    gtk_file_filter_set_name(filter, "Word Files");
    gtk_file_filter_add_pattern(filter, "*.doc");
    gtk_file_filter_add_pattern(filter, "*.docx");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

    filter = gtk_file_filter_new();
    gtk_file_filter_set_name(filter, "Excel Files");
    gtk_file_filter_add_pattern(filter, "*.xls");
    gtk_file_filter_add_pattern(filter, "*.xlsx");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

    // Run the dialog and handle the response
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));
    if (result == GTK_RESPONSE_ACCEPT) 
    {
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        g_print("Selected file for encryption: %s\n", filename);
        encrypt_file(filename);
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

// Function to show file type selection dialog for decryption
static void show_decryption_dialog() 
{
    GtkWidget *dialog;
    GtkFileFilter *filter;

    // Create a file chooser dialog
    dialog = gtk_file_chooser_dialog_new("Select File to Decrypt",
                                         NULL,
                                         GTK_FILE_CHOOSER_ACTION_OPEN,
                                         "_Cancel",
                                         GTK_RESPONSE_CANCEL,
                                         "_Select",
                                         GTK_RESPONSE_ACCEPT,
                                         NULL);

    // Add filter for encrypted files
    filter = gtk_file_filter_new();
    gtk_file_filter_set_name(filter, "Encrypted Files");
    gtk_file_filter_add_pattern(filter, "*.enc");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

    // Run the dialog and handle the response
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));
    if (result == GTK_RESPONSE_ACCEPT) 
    {
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        g_print("Selected file for decryption: %s\n", filename);
        decrypt_file(filename);
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

// Function to encrypt a file using AES encryption
static void encrypt_file(const char *filename) 
{
    // Generate AES key and IV
    RAND_bytes(aes_key, sizeof(aes_key));
    RAND_bytes(aes_iv, sizeof(aes_iv));

    // Open the original file for reading
    FILE *original_file = fopen(filename, "rb");
    if (original_file == NULL) 
    {
        g_print("Error: Unable to open file %s\n", filename);
        return;
    }

    // Create a new filename for encrypted file
    char encrypted_filename[strlen(filename) + 5]; // ".enc" suffix
    strcpy(encrypted_filename, filename);
    strcat(encrypted_filename, ".enc");

    // Open a new file for writing the encrypted content
    FILE *encrypted_file = fopen(encrypted_filename, "wb");
    if (encrypted_file == NULL) 
    {
        g_print("Error: Unable to create encrypted file %s\n", encrypted_filename);
        fclose(original_file);
        return;
    }

    // Initialize AES encryption
    AES_KEY aeskey;
    if (AES_set_encrypt_key(aes_key, AES_KEY_SIZE, &aeskey) != 0) 
    {
        g_print("Error: AES_set_encrypt_key failed\n");
        fclose(original_file);
        fclose(encrypted_file);
        return;
    }

    unsigned char inbuf[AES_BLOCK_SIZE];  // Buffer for input data
    unsigned char outbuf[AES_BLOCK_SIZE]; // Buffer for output data
    int num_bytes_read = 0;               // Number of bytes read from original file
    int outbuf_len = 0;                   // Length of output buffer

    // Encrypt the file chunk by chunk
    while ((num_bytes_read = fread(inbuf, 1, AES_BLOCK_SIZE, original_file)) > 0) 
    {
        AES_encrypt(inbuf, outbuf, &aeskey); // Perform AES encryption

        // Write encrypted data to file
        fwrite(outbuf, 1, num_bytes_read, encrypted_file);
        outbuf_len += num_bytes_read;
    }

    // Clean up
    fclose(original_file);
    fclose(encrypted_file);
    remove(filename); // Delete the original file after encryption

    g_print("Encryption successful. Encrypted file: %s\n", encrypted_filename);

    // Display success dialog
    GtkWidget *dialog = gtk_message_dialog_new
    (
        GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(status_label))),
        GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "Encryption successful! Encrypted file: %s\nOriginal file deleted.",
        encrypted_filename
    );

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

// Function to decrypt a file using AES decryption
static void decrypt_file(const char *filename) 
{
    // Generate AES key and IV
    RAND_bytes(aes_key, sizeof(aes_key));
    RAND_bytes(aes_iv, sizeof(aes_iv));

    // Open the encrypted file for reading
    FILE *encrypted_file = fopen(filename, "rb");
    if (encrypted_file == NULL) 
    {
        g_print("Error: Unable to open encrypted file %s\n", filename);
        return;
    }

    // Create a new filename for decrypted file
    char decrypted_filename[strlen(filename) - 4]; // Remove ".enc" suffix
    strncpy(decrypted_filename, filename, strlen(filename) - 4);
    decrypted_filename[strlen(filename) - 4] = '\0';

    // Open a new file for writing the decrypted content
    FILE *decrypted_file = fopen(decrypted_filename, "wb");
    if (decrypted_file == NULL) 
    {
        g_print("Error: Unable to create decrypted file %s\n", decrypted_filename);
        fclose(encrypted_file);
        return;
    }

    // Initialize AES decryption
    AES_KEY aeskey;
    if (AES_set_decrypt_key(aes_key, AES_KEY_SIZE, &aeskey) != 0) 
    {
        g_print("Error: AES_set_decrypt_key failed\n");
        fclose(encrypted_file);
        fclose(decrypted_file);
        return;
    }

    unsigned char inbuf[AES_BLOCK_SIZE];  // Buffer for input data
    unsigned char outbuf[AES_BLOCK_SIZE]; // Buffer for output data
    int num_bytes_read = 0;               // Number of bytes read from encrypted file
    int outbuf_len = 0;                   // Length of output buffer

    // Decrypt the file chunk by chunk
    while ((num_bytes_read = fread(inbuf, 1, AES_BLOCK_SIZE, encrypted_file)) > 0) 
    {
        AES_decrypt(inbuf, outbuf, &aeskey); // Perform AES decryption

        // Write decrypted data to file
        fwrite(outbuf, 1, num_bytes_read, decrypted_file);
        outbuf_len += num_bytes_read;
    }

    // Clean up
    fclose(encrypted_file);
    fclose(decrypted_file);
    remove(filename); // Delete the encrypted file after decryption

    g_print("Decryption successful. Decrypted file: %s\n", decrypted_filename);

    // Display success dialog
    GtkWidget *dialog = gtk_message_dialog_new
    (
        GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(status_label))),
        GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "Decryption successful! Decrypted file: %s\nEncrypted file deleted.",
        decrypted_filename
    );

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

// Function to check if username already exists
static gboolean username_exists(const char *username) 
{
    FILE *file = fopen(CREDENTIALS_FILE, "r"); // Open credentials file in read mode
    
>>>>>>> Stashed changes
    if (file == NULL) 
    {
        return FALSE; // Return false if file cannot be opened
    }

<<<<<<< Updated upstream
    char stored_username[256], stored_password[256]; // Buffers for storing username and password

    // Read credentials from file and check if username exists
    while (fscanf(file, "%255s %255s", stored_username, stored_password) == 2) 
    {
        if (strcmp(username, stored_username) == 0) 
        {
            fclose(file); // Close the file
            return TRUE; // Return true if username exists
=======
    char stored_username[256]; // Buffer to store usernames read from file
    char stored_password[256]; // Buffer to store passwords read from file
    gboolean exists = FALSE;   // Flag to indicate if username exists

    while (fscanf(file, "%255s %255s", stored_username, stored_password) == 2) 
    { // Read username and password from file
        if (strcmp(username, stored_username) == 0) 
        { // Check if username matches
            exists = TRUE; // Set exists flag
            break;         // Exit loop if match found
>>>>>>> Stashed changes
        }
    }

    fclose(file); // Close the file
<<<<<<< Updated upstream
		  
    encrypt_file(CREDENTIALS_FILE);

    return FALSE; // Return false if username does not exist
=======

    return exists; // Return flag indicating if username exists
>>>>>>> Stashed changes
}

// Callback function for exit button click
static void on_exit_button_clicked(GtkButton *button, gpointer user_data) 
{
<<<<<<< Updated upstream
    gtk_main_quit(); // Exit the GTK main loop
}

// Function to show options for encryption or decryption
static void show_file_type_dialog() 
{
    GtkWidget *dialog, *content_area;
    GtkWidget *button_encrypt, *button_decrypt;

    // Create a new dialog with default buttons
    dialog = gtk_dialog_new(); // Use this if you do not want predefined buttons

    gtk_window_set_title(GTK_WINDOW(dialog), "Select Operation"); // Set dialog title
    
    gtk_window_set_default_size(GTK_WINDOW(dialog), 400, 200); // Adjust width and height as needed

    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);							       //
    
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog)); // Get content area of the dialog

    // Create and add buttons for encryption and decryption
    button_encrypt = gtk_button_new_with_label("Encrypt File");
    g_signal_connect(button_encrypt, "clicked", G_CALLBACK(show_encryption_dialog), dialog);
    gtk_box_pack_start(GTK_BOX(content_area), button_encrypt, TRUE, TRUE, 5);

    button_decrypt = gtk_button_new_with_label("Decrypt File");
    g_signal_connect(button_decrypt, "clicked", G_CALLBACK(show_decryption_dialog), dialog);
    gtk_box_pack_start(GTK_BOX(content_area), button_decrypt, TRUE, TRUE, 5);

    gtk_widget_show_all(dialog); // Show all widgets
}

// Function to show file chooser dialog for encryption
static void show_encryption_dialog() 
{
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new
    (
        "Select a file to encrypt", 
        NULL, 
        GTK_FILE_CHOOSER_ACTION_OPEN, 
        "_Cancel", 
        GTK_RESPONSE_CANCEL, 
        "_Open", 
        GTK_RESPONSE_ACCEPT, 
        NULL
    );

    // Add filters for file types (excluding encrypted files)
    GtkFileFilter *filter = gtk_file_filter_new();
    gtk_file_filter_set_name(filter, "Text and Office files");
    gtk_file_filter_add_mime_type(filter, "text/plain");
    gtk_file_filter_add_mime_type(filter, "application/msword");
    gtk_file_filter_add_mime_type(filter, "application/vnd.ms-excel");
    gtk_file_filter_add_mime_type(filter, "application/vnd.openxmlformats-officedocument.wordprocessingml.document");
    gtk_file_filter_add_mime_type(filter, "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) 
    {
        char *filename;
        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        encrypt_file(filename); // Encrypt the selected file
        g_free(filename); // Free the filename
    
	// Display success dialog
	GtkWidget *dialog = gtk_message_dialog_new
	(
        	NULL,
        	GTK_DIALOG_DESTROY_WITH_PARENT,
        	GTK_MESSAGE_INFO,
        	GTK_BUTTONS_OK,
        	"File encrypted successfully."
    	);
    	gtk_dialog_run(GTK_DIALOG(dialog));
    	gtk_widget_destroy(dialog);
    }

    gtk_widget_destroy(dialog); // Destroy the dialog
}

// Function to show file chooser dialog for decryption
static void show_decryption_dialog() 
{
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new
    (
        "Select a file to decrypt", 
        NULL, 
        GTK_FILE_CHOOSER_ACTION_OPEN, 
        "_Cancel", 
        GTK_RESPONSE_CANCEL, 
        "_Open", 
        GTK_RESPONSE_ACCEPT, 
        NULL
    );

    // Add filter for encrypted files
    GtkFileFilter *filter = gtk_file_filter_new();
    gtk_file_filter_set_name(filter, "Encrypted files");
    gtk_file_filter_add_pattern(filter, "*.enc");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) 
    {
        char *filename;
        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        decrypt_file(filename); // Decrypt the selected file
        g_free(filename); // Free the filename
    	
    	// Display success dialog
	GtkWidget *dialog = gtk_message_dialog_new
    	(
        	NULL,
        	GTK_DIALOG_DESTROY_WITH_PARENT,
        	GTK_MESSAGE_INFO,
        	GTK_BUTTONS_OK,
        	"File decrypted successfully."
    	);
    	gtk_dialog_run(GTK_DIALOG(dialog));
    	gtk_widget_destroy(dialog);
    }

    gtk_widget_destroy(dialog); // Destroy the dialog
}

// Function to generate a random AES key and IV
static void generate_aes_key_and_iv() 
{
    if (!RAND_bytes(aes_key, sizeof(aes_key))) 
    {
        g_error("Error generating AES key");
    }
    if (!RAND_bytes(aes_iv, sizeof(aes_iv))) 
    {
        g_error("Error generating AES IV");
    }
}

// Function to encrypt a file
static void encrypt_file(char *filename) 
{
    // Open the input file
    FILE *input_file = fopen(filename, "rb");
    if (!input_file) 
    {
        g_error("Error opening input file");
        return;
    }

    // Create the output file
    char output_filename[256];
    snprintf(output_filename, sizeof(output_filename), "%s.enc", filename);
    FILE *output_file = fopen(output_filename, "wb");
    if (!output_file) 
    {
        fclose(input_file);
        g_error("Error creating output file");
        return;
    }

    // Initialize AES encryption
    generate_aes_key_and_iv();
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, aes_key, aes_iv);

    // Write the AES key and IV to the output file
    fwrite(aes_key, 1, sizeof(aes_key), output_file);
    fwrite(aes_iv, 1, sizeof(aes_iv), output_file);

    // Encrypt the input file and write to the output file
    unsigned char buffer[4096];
    unsigned char encrypted_buffer[4096 + EVP_MAX_BLOCK_LENGTH];
    int bytes_read, encrypted_bytes;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), input_file)) > 0) 
    {
        EVP_EncryptUpdate(ctx, encrypted_buffer, &encrypted_bytes, buffer, bytes_read);
        fwrite(encrypted_buffer, 1, encrypted_bytes, output_file);
    }
    EVP_EncryptFinal_ex(ctx, encrypted_buffer, &encrypted_bytes);
    fwrite(encrypted_buffer, 1, encrypted_bytes, output_file);

    // Clean up
    EVP_CIPHER_CTX_free(ctx);
    fclose(input_file);
    fclose(output_file);

    // Delete the original file
    remove(filename);

}

// Function to decrypt a file
static void decrypt_file(char *filename) 
{
    // Open the input file
    FILE *input_file = fopen(filename, "rb");
    if (!input_file) 
    {
        g_error("Error opening input file");
        return;
    }

    // Create the output file
    char output_filename[256];
    strncpy(output_filename, filename, strlen(filename) - 4);
    output_filename[strlen(filename) - 4] = '\0';
    FILE *output_file = fopen(output_filename, "wb");
    if (!output_file) 
    {
        fclose(input_file);
        g_error("Error creating output file");
        return;
    }

    // Read the AES key and IV from the input file
    fread(aes_key, 1, sizeof(aes_key), input_file);
    fread(aes_iv, 1, sizeof(aes_iv), input_file);

    // Initialize AES decryption
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, aes_key, aes_iv);

    // Decrypt the input file and write to the output file
    unsigned char buffer[4096];
    unsigned char decrypted_buffer[4096];
    int bytes_read, decrypted_bytes;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), input_file)) > 0) 
    {
        EVP_DecryptUpdate(ctx, decrypted_buffer, &decrypted_bytes, buffer, bytes_read);
        fwrite(decrypted_buffer, 1, decrypted_bytes, output_file);
    }
    EVP_DecryptFinal_ex(ctx, decrypted_buffer, &decrypted_bytes);
    fwrite(decrypted_buffer, 1, decrypted_bytes, output_file);

    // Clean up
    EVP_CIPHER_CTX_free(ctx);
    fclose(input_file);
    fclose(output_file);

    // Delete the encrypted file
    remove(filename);

=======
    gtk_main_quit(); // Quit the GTK main loop
>>>>>>> Stashed changes
}

