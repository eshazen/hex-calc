//
//

mm = 25.4;
e = 0.1;
$fn=32;

pcb_wid = 3.4*mm;
pcb_len = 7.0*mm;
pcb_thk = 1.6;

case_spc = 1.0;			/* pcb edge clearance */
case_up = 0.5*mm;		/* space below PCB (battery hgt) */

dpy_dx = 0.0933*mm;		/* offset to edge of display */
dpy_dy = 0.0506*mm;		/* offset to edge of display */



module pcb() {
  color("darkgreen")
    cube( [pcb_wid, pcb_len, pcb_thk]);
}
