# Rijndael

Dit is de Rijndael encryption die wordt gebruikt in het huidige project
[Inspiratie en voorbeeld van werking](https://github.com/SergeyBel/AES)

## Belangrijke Types
```c++
class enum key_size
{
    AES128 = 128,
    AES192 = 192,
    AES256 = 256
};
```

```c++
class Rijndael {
    ...
};
```

## Belangrijke Aliases
```c++
using byte = unsigned char;
```

## Entry Points

### Constructor methods
```c++
Rijndael* rijndael_ctor();
```
Calling-convention: StdCall.  
Default constructor van de rijndael class.

  
```c++
Rijndael* rijndael_ctor_key(
    key_size size
);
```
Calling-convention: StdCall.  
Constructor van de rijndael class waarbij een key-size wordt meegegeven.

### Destructor methods
```c++
void rijndael_dtor(
    [in] Rijndael* rijndael
);
```
Calling-convention: StdCall.  
Destructor van de rijndael class.

### Utility
```c++
key_size rijndael_get_key_size(
    [in] const Rijndael* rijndael
);
```
Calling-convention: StdCall.  
Returned de key-size van de rijndael instance.

```c++
int rijndael_set_key_size(
    [in] Rijndael* rijndael,
         key_size      size
);
```
Calling-convention: StdCall.  
Sets de key-size van de rijndael-instance.  

#### Aanmerkingen:
 - Returned `0` wanneer rijndael een null-ptr is.
 - Returned de oude key-size wanneer de nieuwe key-size invalid is. Rijndael object blijft onveranderd.
 - Returned de nieuwe key-size wanneer deze valid is, bijvoorbeeld: 128, 192, 256.

```c++
unsigned long long rijndael_get_mem_size();
```
Calling-convention: StdCall.  
Returned de grootte van de Rijndael class in bytes in geheugen.

```c++
void rijndael_encrypt(
    [in]      const Rijndael* rijndael,
    [in]      const byte*     plain_bytes,
    [in, out] int*            length,
    [in]      const byte*     iv_bytes,
    [in]      const byte*     key_bytes,
              int             key_len,
    [out]     byte*           cipher_bytes 
);
```
Calling-convention: StdCall.  
Encrpyt `plain_bytes` met `iv_bytes` en `key_bytes` en stopt de encrypted text in `cipher_bytes`.  
  
#### Aanmerkingen:
 - Aan `length` moet de lengte van de text-bytes array worden doorgepaast, en geeft de lengte van`encrypted` terug.  
 - Van `iv_bytes` array wordt altijd verwacht dat deze een lengte van 16 heeft.
 - `plain_bytes` moet een lengte hebben welke deelbaar is door 16.
 - De verwachte lengte van `cipher_bytes` is hetzelfde als `plain_bytes` en moet geallocate worden door de caller.
 - `length` neemt een waarde van `-1` aan wanneer er iets mis is gegaan.

```c++
void rijndael_decrypt(
    [in]      const Rijndael* rijndael,
    [in]      const byte*     cipher_bytes,
    [in, out] int*            length,
    [in]      const byte*     iv_bytes,
    [in]      const byte*     key_bytes,
              int             key_len,
    [out]     byte*           plain_bytes
);
```
Calling-convention: StdCall.  
Decrypt `cipher_bytes` met `iv_bytes` en `key_bytes` en stop de decrypted plain-text in `plain_bytes`.

#### Aanmerkingen:
 - Aan `length` moet de lengte van de cipher-bytes array worden doorgepaast, en geeft de lengte van `plain_bytes` terug.  
 - Van `iv_bytes` array wordt altijd verwacht dat deze een lengte van 16 heeft.
 - `cipher_bytes` moet een lengte hebben welke deelbaar is door 16.
 - De verwachte lengte van `plain_bytes` is hetzelfde als de lengthe van `cipher_bytes` en moet geallocate worden door de caller.
 - `length` neemt een waarde van `-1` aan wanneer er iets mis is gegaan.

```c++
void rijndael_gen_iv(
    [out] byte* out_iv
);
```
Calling-convention: StdCall.  
Genereert een iv en stopt deze in `out_iv`.
#### Aanmerkingen:
 - De out_iv moet een buffer zijn die is geallocate door de caller.
 - De geallocate buffer moet minstens 16 bytes groot zijn.

```c++
void rijndael_gen_key(
    [out] byte* out_key
);
```
Calling convention: StdCall.  
Genereert een key en stopt deze in `out_key`.
#### Aanmerkingen:
- De out_key moet een buffer zijn die is geallocate door de caller.
- De geallocate buffer moet minstens 32 bytes groot zijn.