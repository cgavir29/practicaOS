#pragma once

#define LEN_MEM_NAME 40
#define LEN_BAN_ENTRA_ENTRY 50
#define LEN_BAN_ENTRA 100
#define NUM_TIPO_REACTS 3
#define LEN_BAN_INTERNA 100
#define LEN_BAN_SALIDA 100

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
    struct Examen buffer[LEN_BAN_ENTRA];
};

struct BandejaEntradaEntry {
    struct BandejaEntrada bandejas[LEN_BAN_ENTRA_ENTRY];
};

struct BandejaInterna {
    int entra;
    int sale;
    int cantidad;
    // int total_reactivo; // Si hace parte
    struct Examen buffer[LEN_BAN_INTERNA];
};

struct BandejaInternaEntry {
    struct BandejaInterna bandejas[NUM_TIPO_REACTS];
};

struct BandejaSalida {
    int entra;
    int sale;
    int cantidad;
    struct Examen buffer[LEN_BAN_SALIDA];
};

struct Evaluador {
    struct Header hdr;
    struct BandejaEntradaEntry ban_en;
    struct BandejaInternaEntry ban_in;
    struct BandejaSalida ban_out;
};
