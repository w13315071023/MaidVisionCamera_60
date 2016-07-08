#ifdef SERIALDLL_EXPORTS
#define SERIALDLL_API __declspec(dllexport)
#else
#define SERIALDLL_API __declspec(dllimport)
#endif


SERIALDLL_API bool get_com_port(char** port, int& length); //0:no valid com port
SERIALDLL_API bool open_com_port(const char* port); //TRUE:open successful; FALSE:open failed
SERIALDLL_API bool close_com_port(const char* port); //TRUE:close successful; FALSE:close failed
SERIALDLL_API int fetch_msg();//1:no ball; 2:has ball no hit; 3:has ball hit valid; 4:has ball hit invalid;
SERIALDLL_API void set_threshold(int num);
