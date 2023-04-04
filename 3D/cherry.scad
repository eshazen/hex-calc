//
// Cherry MX keyswitch simple model
//

module mx() {
     mx_wid = 15.6;
     mx_hgt = 11.6;
     mx_shaft_len = 3.6;
     mx_shaft_dia = 5;
     mx_cutout = 14;

     translate( [-mx_wid/2, -mx_wid/2, 0])
	  cube( [mx_wid, mx_wid, mx_hgt]);
     translate( [0, 0, mx_hgt])
	  cylinder( d=mx_shaft_dia, h=mx_shaft_len);
}

module mx_cap() {
     cap_w1 = 18.1;
     cap_w2 = 12.37;
     
}

mx();
