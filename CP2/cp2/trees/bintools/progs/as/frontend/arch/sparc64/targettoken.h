/* Automatically generated; do not edit */

#ifndef TARGETTOKEN_H
#define TARGETTOKEN_H


enum targettoktypes{
   /* Invalid */
   TTOK_NIL,
   TTOK_ASIREG,
   TTOK_REGCLASS_ASR,
   TTOK_REGCLASS_FCC,
   TTOK_REGCLASS_FREG,
   TTOK_REGCLASS_FSR,
   TTOK_REGCLASS_ICC,
   TTOK_REGCLASS_PR,
   TTOK_REGCLASS_RREG,
};

int is_letter(int ch);
int is_subletter(int ch);


#endif /* TARGETTOKEN_H */
