#ifndef LOAD_GETTEXT_INTERNAL
#define LOAD_GETTEXT_INTERNAL

// Begin platform-specific header includes

// All platform internal functions
namespace {
char* internal_bindtextdomain(char* domain_name, char* dir_name);
char* internal_textdomain(char* domain_name);
char* internal_gettext(char* msgid);
char* internal_ngettext(char* msgid1, char* msgid2, unsigned long int n);

int internal_init(void);
int internal_shutdown(void);
void internal_ChangeLocale(char* locale_ll_CC);
bool internal_isLoaded(void);

// Default functions, these are used if library doesn't load properly
char* default_bindtextdomain(char* domain_name, char* dir_name);
char* default_textdomain(char* domain_name);
char* default_gettext(char* msgid);
char* default_ngettext(char* msgid1, char* msgid2, unsigned long int n);
}

// Linux
#ifdef LINUX
//TODO: Create these instructions

// Mac OS
#elif MACOS

//TODO: Create these instructions

// Windows
#elif _WIN32
#include <Windows.h>

// Others
#else
	// If you encounter this error and one of the above platforms has a suitable
	//  dynamic link method: 
	//   At the top of this file, #define the macro
	//   At the bottom of LoadGetText.cpp, #undef the macro
	#error Unknown OS, cannot link to gettext library.
	// Otherwise, comment out this error and add your own suitable functions.
#endif // !Platform-specific-includes
#endif // !LOAD_GETTEXT_INTERNAL
