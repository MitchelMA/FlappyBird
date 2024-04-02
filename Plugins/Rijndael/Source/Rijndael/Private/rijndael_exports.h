#ifndef RIJNDAEL_RIJNDAEL_EXPORTS_H
#define RIJNDAEL_RIJNDAEL_EXPORTS_H

#if defined(DLL_BUILD)
#define DLL_SPEC __declspec(dllexport)
#else
#define DLL_SPEC __declspec(dllimport)
#endif // DLL_BUILD

#define DLL_ENTRY extern "C" DLL_SPEC
#define STD_DLL_ENTRY(RET_TYPE) DLL_ENTRY RET_TYPE __stdcall

// `_in_` and `_out_` are used to signify if a pointer is used as input, output or a combination of the two

#if !defined(_in_)
    #define _in_
#else
    #pragma message("WARN: _in_ was already defined!")
#endif // !_in_
#if !defined(_out_)
    #define _out_
#else
    #pragma message("WARN: _out_ was already defined!")
#endif // !_out_

STD_DLL_ENTRY(void*)
rijndael_ctor();

STD_DLL_ENTRY(void*)
rijndael_ctor_key(int key_size);

STD_DLL_ENTRY(int)
rijndael_dtor(
    _in_ void* rijndael
);

STD_DLL_ENTRY(int)
rijndael_get_key_size(
    _in_ const void* rijndael
);

STD_DLL_ENTRY(int)
rijndael_set_key_size(
    _in_ void* rijndael,
         int   key_size
);

STD_DLL_ENTRY(unsigned long long)
rijndael_get_mem_size();

STD_DLL_ENTRY(void)
rijndael_encrypt(
    _in_       const void*          rijndael,
    _in_       const unsigned char* plain_bytes,
    _in_ _out_ int*                 length,
    _in_       const unsigned char* iv_bytes,
    _in_       const unsigned char* key_bytes,
               int                  key_len,
    _out_      unsigned char*       cipher_bytes
);

STD_DLL_ENTRY(void)
rijndael_decrypt(
    _in_       const void*          rijndael,
    _in_       const unsigned char* cipher_bytes,
    _in_ _out_ int*                 length,
    _in_       const unsigned char* iv_bytes,
    _in_       const unsigned char* key_bytes,
               int                  key_len,
    _out_      unsigned char*       plain_bytes
);

STD_DLL_ENTRY(void)
rijndael_gen_iv(
    _out_ unsigned char* out_iv
);

STD_DLL_ENTRY(void)
rijndael_gen_key(
    _out_ unsigned char* out_key
);

#endif //RIJNDAEL_RIJNDAEL_EXPORTS_H
