#pragma once

#define LEN_MEM_NAME 40
#define LEN_BAN_ENTRA 100
#define LEN_BAN_ENTRA_ENTRY 50

struct Header {
    int i;
    int ie;
    int oe;
    char n[LEN_MEM_NAME];
    int b;
    int d;
    int s;
    int q;
};

struct Examen {
    int id;
    char reactivo;
    int cantidad;
};

struct BandejaEntrada {
    int entra;
    int sale;
    int cantidad;
//   int tamano;
    struct Examen buffer[LEN_BAN_ENTRA];
};

struct BandejaEntradaEntry {
    struct BandejaEntrada bandejas[LEN_BAN_ENTRA_ENTRY];
};

struct Evaluador {
    struct Header hdr;
    struct BandejaEntradaEntry bee;
};
