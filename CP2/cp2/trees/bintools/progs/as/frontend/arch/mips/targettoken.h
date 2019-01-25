/* Automatically generated; do not edit */

#ifndef TARGETTOKEN_H
#define TARGETTOKEN_H


enum targettoktypes{
   /* Invalid */
   TTOK_NIL,
   TTOK_ANYREGISTER,
   TTOK_REGCLASS_COP0REG,
   TTOK_REGCLASS_COP2REG,
   TTOK_REGCLASS_COP3REG,
   TTOK_REGCLASS_FPCC,
   TTOK_REGCLASS_FPREG,
   TTOK_REGCLASS_GENERALREG,
};

int is_letter(int ch);
int is_subletter(int ch);


#endif /* TARGETTOKEN_H */
