
include <MX_Keyboard.scad>
include <keyboard.scad>
include <lcd.scad>

pcb_wid = 87;
pcb_len = 175;
pcb_thk = 1.6;

case_thk = 1.6;
case_hgt = 15;

module case() {
     color("green") cube( [pcb_wid, pcb_len, pcb_thk]);
     translate( [-case_thk, -case_thk, -2]) {
	  cube( [case_thk, pcb_len+2*case_thk, case_hgt]);
	  translate( [pcb_wid+case_thk, 0, 0])
	       cube( [case_thk, pcb_len+2*case_thk, case_hgt]);
	  cube( [pcb_wid+2*case_thk, case_thk, case_hgt]);
	  translate( [0, pcb_len+case_thk, 0])
	       cube( [pcb_wid+2*case_thk, case_thk, case_hgt]);
     }
}


module calcu() {

     translate( [0.5*19, 6.5*19, 0]) {
	  color("lightblue")
	       keyboard();
	  translate( [-11, 12, 0])
	       color("grey")
	       lcd();
     }
     translate( [-5, -5, -2]) {
	  case();
     }
}

// projection( cut=true)
calcu();
