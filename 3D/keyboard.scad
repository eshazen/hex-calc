
keys = [ [ ["HEX","64"], ["BIN","32"], ["DEC","16"], ["SIGN","8"]],
	 [ ["f", ""],    ["D", ""],    ["E", ""],    ["F", ""]],
	 [ ["g", ""],    ["A", ""],    ["B", ""],    ["C", ""]],
	 [ ["-", ""],    ["7", ""],    ["8", ""],    ["9", ""]],
	 [ ["+", ""],    ["4", ""],    ["5", ""],    ["6", ""]],
	 [ ["*", ""],    ["1", ""],    ["2", ""],    ["3", ""]],
//	 [ ["/", ""],    ["0", ""],    ["ENT", ""],    ["ER", ""]]
	 ];

module keyboard() {

     dx = 19;
     dy = 19;

     x = 0;
     y = 0;

     for( y=[0:len(keys)-1], x=[0:len(keys[y])-1]) {
	  row = keys[y];
	  key = row[x];
//	  echo( "row =", row, " key=", key);
	  translate( [x*dx,-y*dy,0])
	       makeKey( r4_f, r4_b, x1_00, x1_00, key[0], key[1]);
     }

     // last row by hand
     translate( [0, -6*dx, 0]) {
	  makeKey( r4_f, r4_b, x1_00, x1_00, "/");
	  translate( [dx, 0, 0])
	  makeKey( r4_f, r4_b, x1_00, x1_00, "0");
	  translate( [2.5*dx, 0, 0]) {
	       makeKey( r4_f, r4_b, x1_00, x2_00, "ENTER");
	  }
     }
}

