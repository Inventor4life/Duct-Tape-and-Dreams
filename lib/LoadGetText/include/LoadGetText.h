#ifndef LOAD_GETTEXT_H
#define LOAD_GETTEXT_H

// Functions found in the dynamic library
char* bindtextdomain(char* domain_name, char* dir_name);
char* textdomain(char* domain_name);
char* gettext(char* msgid);
char* ngettext(char* msgid1, char* msgid2, unsigned long int n);

//Custom Functions
namespace LoadGettext {
int init(void);
int shutdown(void);
void ChangeLocale(char* locale_ll_CC);
bool isLoaded(void);
}

#endif // !LOAD_GETTEXT_H
