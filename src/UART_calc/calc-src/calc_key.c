//
// perform action on key press
//
// keyboard mapping table

typedef struct {
  char key;
  int action_group;
  int action_code;
} a_key;

// note: digits 0-9 and A-F handled outside this table

// 'A'-64

define ctl(c) (toupper(c)-64)

static a_key keys[] = {
  { ctl('s'), KG_MODE, M_SIG },	/* toggle SIGNED display */
  { ctl('h'), KG_MODE, M_HEX },	/* set HEX mode */
  { ctl('d'), KG_MODE, M_DEC },	/* set DEC mode */
  { ctl('n'), KG_MODE, M_BIN },	/* set BIN mode */
  { ctl('o'), KG_MODE, M_64 },	/* set 64-bit word size */
  { ctl('q'), KG_MODE, M_32 },	/* set 32-bit word size */
  { ctl('w'), KG_MODE, M_16 },	/* set 16-bit word size */
  { ctl('b'), KG_MODE, M_8 },	/* set 8-bit word size */

  // not done

  { 'X', KG_ARITH, M_CLR },	/* Clear x */
  { '-', KG_ARITH, M_SUB },	/* subtract */
  { '+', KG_ARITH, M_ADD },	/* add */
  { '*', KG_ARITH, M_MUL },	/* multiply */
  { '/', KG_ARITH, M_DIV },	/* divide */
  { '=', KG_ARITH, M_CHS },	/* change sign*/

  { '\', KG_STACK, M_DROP },	/* roll down */
  { ctl('M'), KG_STACK, M_PUSH },	/* push (Enter) */
  { , KG_STACK, M_SWAP },	/* swap x, y */
}

void calc_key( char *k) {

  switch( k) {
    case 
  }

}
