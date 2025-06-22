#include "InternalLoadGetText.h"
#include "../include/LoadGetText.h"

// Functions found in the dynamic library
char* bindtextdomain(char* domain_name, char* dir_name){
	return ::internal_bindtextdomain(domain_name, dir_name);
}

char* textdomain(char* domain_name){
	return ::internal_textdomain(domain_name);
}

char* gettext(char* msgid) {
	return ::internal_gettext(msgid);
}

char* ngettext(char* msgid1, char* msgid2, unsigned long int n) {
	return ::internal_ngettext(msgid1, msgid1, n);
}

// Custom functions for working with library
namespace LoadGettext {
int init(void) {
	return ::internal_init();
}

int shutdown(void) {
	return ::internal_shutdown();
}

void ChangeLocale(char* locale_ll_CC) {
	::internal_ChangeLocale(locale_ll_CC);
}

bool isLoaded(void) {
	return ::internal_isLoaded();
}
} // !LoadGetText

namespace {
	
// Default functions, in case library doesn't load properly
char* default_bindtextdomain(char* domain_name, char* dir_name) {
	return nullptr;
}

char* default_textdomain(char* domain_name){
	return nullptr;
}
char* default_gettext(char* msgid) {
	return msgid;
}
char* default_ngettext(char* msgid1, char* msgid2, unsigned long int n) {
	return (n == 1) ? msgid1 : msgid2;
}


// Platform-specific function definitions

//##////       ///////////////////////////////////
//##///  LINUX                                ///
//##//       ///////////////////////////////////
#ifdef LINUX
//TODO: Create these instructions

//##////       ///////////////////////////////////
//##///  MACOS                                ///
//##//       ///////////////////////////////////
#elif MACOS

//TODO: Create these instructions

//##////       ///////////////////////////////////
//##///  WINDOWS                              ///
//##//       ///////////////////////////////////
#elif _WIN32

// TODO, figure out if existing functions can be redefined, rather than creating a type for each.
typedef char* (__stdcall* f_gettext)(const char* msgid);
f_gettext i_gettext = nullptr;

typedef char* (__stdcall* f_ngettext)(const char* msgid1, const char* msgid2, unsigned long int n);
f_ngettext i_ngettext = nullptr;

typedef char* (__stdcall* f_textdomain)(const char* domain_name);
f_textdomain i_textdomain = nullptr;

typedef char* (__stdcall* f_bindtextdomain)(const char* domain_name, const char* dir_name);
f_bindtextdomain i_bindtextdomain = nullptr;

HMODULE gettextDLL = nullptr;

int internal_init(void){
	gettextDLL = LoadLibraryA("libintl-8.dll");
	
	// Library failed to load. Return failed_to_load_library error code
	if(gettextDLL == nullptr) {
		return 1;
	}
	//else
	
	// Load functions from library
	i_gettext = (f_gettext)GetProcAddress(gettextDLL, "gettext");
	i_ngettext = (f_ngettext)GetProcAddress(gettextDLL, "ngettext");
	i_textdomain = (f_textdomain)GetProcAddress(gettextDLL, "textdomain");
	i_bindtextdomain = (f_bindtextdomain)GetProcAddress(gettextDLL, "bindtextdomain");
	
	// Verify that functions were loaded
	if(i_gettext == nullptr 
	 || i_ngettext == nullptr 
	 || i_textdomain == nullptr
	 || i_bindtextdomain == nullptr) {
		
		// Set all functions to nullptr
		i_gettext = nullptr;
		i_ngettext = nullptr;
		i_textdomain = nullptr;
		i_bindtextdomain = nullptr;
		
		::internal_shutdown(); // Unload library
		
		return 2; // Return failed_to_load_functions error code
	}

	return 0;
}


char* internal_bindtextdomain(char* domain_name, char* dir_name) {
	if(gettextDLL == nullptr) {
		return ::default_bindtextdomain(domain_name, dir_name);
	}
	//else
	return i_bindtextdomain(domain_name, dir_name);
}

char* internal_textdomain(char* domain_name) {
	if(gettextDLL == nullptr) {
		return ::default_textdomain(domain_name);
	}
	//else
	return i_textdomain(domain_name);
}

char* internal_gettext(char* msgid) {
	if(gettextDLL == nullptr) {
		return ::default_gettext(msgid);
	}
	//else
	return i_gettext(msgid);
}

char* internal_ngettext(char* msgid1, char* msgid2, unsigned long int n) {
	if(gettextDLL == nullptr) {
		return ::default_ngettext(msgid1, msgid1, n);
	}
	//else
	return i_ngettext(msgid1, msgid1, n);
}

void internal_ChangeLocale(char* locale_ll_CC) {
	//convert locale_ll_CC to wide char
	wchar_t tempWstr[50] = { '\0' };
	MultiByteToWideChar(CP_ACP, 0, locale_ll_CC, -1, tempWstr, 50);
	SetThreadLocale(LocaleNameToLCID(tempWstr, 0));
	
	textdomain(textdomain(nullptr)); // Refresh textdomain
}
	
int internal_shutdown(void) {
	bool return_value = 	FreeLibrary(gettextDLL);
	
	i_gettext = nullptr;
	i_ngettext = nullptr;
	i_textdomain = nullptr;
	i_bindtextdomain = nullptr;
	
	gettextDLL = nullptr;

	return !return_value; // FreeLibrary returns nonzero on success
}

bool internal_isLoaded(void) {
	return gettextDLL != nullptr;
}

//##////       ///////////////////////////////////
//##///  OTHERS                               ///
//##//       ///////////////////////////////////
#else
	// If you encounter this error and one of the above platforms has a suitable
	//  dynamic link method: 
	//   At the top of InternalLoadGetText.h, #define the macro
	//   At the bottom of this file, #undef the macro
	#error Unknown OS, cannot link to gettext library.
	// Otherwise, comment out this error and add your own suitable functions.

#endif // !Platform-specific definitions
} // !namespace
