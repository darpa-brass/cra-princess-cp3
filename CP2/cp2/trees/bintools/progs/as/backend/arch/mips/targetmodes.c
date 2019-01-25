/* Automatically generated; do not edit */

#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "common.h"
#include "modeinfo.h"
#include "targetmodes.h"
static void mips16_mode(unsigned int linenum, bool val) {
   if (val) {
      file_warn(linenum, "mips16 not supported");
   }
}
const struct modeinfo modeinfo[NUMMODES] ={
{
.name= "at",
.setfunc= NULL,
.defval= true,
},
{
.name= "macro",
.setfunc= NULL,
.defval= true,
},
{
.name= "reorder",
.setfunc= NULL,
.defval= true,
},
{
.name= "volatile",
.setfunc= NULL,
.defval= false,
},
{
.name= "mips16",
.setfunc= mips16_mode,
.defval= false,
},
{
.name= "mips32",
.setfunc= NULL,
.defval= false,
},
};
