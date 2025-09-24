#ifndef MSEL_INCLUDED
#define MSEL_INCLUDED
#include <stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif
	void* MSEL_Encrypt(const void* data, size_t len, const void* key, size_t* out_len); 	void* MSEL_Decrypt(const void* data, size_t len, const void* key, size_t* out_len);
#ifdef __cplusplus
}
#endif
#endif
