
$fn=32;
mm=25.4;
e=0.1;

b_len = 8;
b_wid = 12.7;
b_hgt = 6.86;

stem_len = 10;
stem_dia = 6.35;

pin_dia = 1.7;
pin_len = 3.18;

module pin_at(x,y) {
  translate( [x, y, -pin_len])
    cylinder( d=pin_dia, h=pin_len+b_hgt/2);
}

cube( [b_len, b_wid, b_hgt]);
translate( [-stem_len-e, b_wid/2, b_hgt/2])
rotate( [0, 90, 0])
cylinder( d=6, h=10);

pin_at( b_wid, b_wid/2);
pin_at( b_wid, b_wid/2+4.7);
pin_at( b_wid, b_wid/2-4.7);
