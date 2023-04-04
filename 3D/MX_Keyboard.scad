// Cherry MX standard (OEM) measurements
// Measurements and key sizes collected from:
// http://blog.maxkeyboard.com/dwkb/keycap-profile-size-information/
// https://support.wasdkeyboards.com/hc/en-us/articles/115009701328-Keycap-Size-Compatibility
// http://i.imgur.com/K5kui2s.jpg
// Visual information of key text collected from:
// https://www.keychatter.com/wp-content/uploads/2014/07/filco-standard-layout.png
// row number - front and back heights
r1_f = 10.1;
r1_b = 7.9;
r2_f = 9.3;
r2_b = 8;
r3_f = 9.3;
r3_b = 9;
r4_f = 10.8;
r4_b = 11.4;

// width measurement
x1_00 = 18;
x1_25 = 22.8;
x1_50 = 27.5;
x1_75 = 32.3;
x2_00 = 37.1;
x2_25 = 41.8;
x2_75 = 51.4;
space = 118.1;

// spacing measurement
normalSpacing = 12;
spacebarSpacing = 50; // default x6_25
spacebarX6Spacing = 49;
spacebarX6_5Spacing =  52.5;

// other measurements
rounding = 1.5;
postDiam = 5.54;
crossLong = 4.1;
crossWide = 1.35;

// unspecified details
insetX = 5;
insetYfront = 3;
insetYback = 0.6;
wallThick = 1;
postBottomGap = 2;
topCurveDip = 1;

$fn = 36;

// This function borrowed from OpenSCAD Snippet Pad:
// https://openscadsnippetpad.blogspot.com/2017/05/circle-defined-by-three-points.html
// Finding the Center of a Circle from Three Points.
// Points must not be equal or collinear, - lie on a single straight line 
function circle_by_three_points(A, B, C) =
let (
  yD_b = C.y - B.y,  xD_b = C.x - B.x,  yD_a = B.y - A.y,
  xD_a = B.x - A.x,  aS = yD_a / xD_a,  bS = yD_b / xD_b,
  cex = (aS * bS * (A.y - C.y) + 
  bS * (A.x + B.x) -    aS * (B.x + C.x)) / (2 * (bS - aS)),
  cey = -1 * (cex - (A.x + B.x) / 2) / aS + (A.y + B.y) / 2
)
[cex, cey];
    
// Primary entry point for this library
// keyname is a string, as seen in the else-if chain below
module key(keyname) 
{
         if (keyname == "Escape") makeKey(r4_f, r4_b, x1_00, x1_00, "Esc");
    else if (keyname == "F1") makeKey(r4_f, r4_b, x1_00, x1_00, "F1");
    else if (keyname == "F2") makeKey(r4_f, r4_b, x1_00, x1_00, "F2");
    else if (keyname == "F3") makeKey(r4_f, r4_b, x1_00, x1_00, "F3");
    else if (keyname == "F4") makeKey(r4_f, r4_b, x1_00, x1_00, "F4");
    else if (keyname == "F5") makeKey(r4_f, r4_b, x1_00, x1_00, "F5");
    else if (keyname == "F6") makeKey(r4_f, r4_b, x1_00, x1_00, "F6");
    else if (keyname == "F7") makeKey(r4_f, r4_b, x1_00, x1_00, "F7");
    else if (keyname == "F8") makeKey(r4_f, r4_b, x1_00, x1_00, "F8");
    else if (keyname == "F9") makeKey(r4_f, r4_b, x1_00, x1_00, "F9");
    else if (keyname == "F10") makeKey(r4_f, r4_b, x1_00, x1_00, "F10");
    else if (keyname == "F11") makeKey(r4_f, r4_b, x1_00, x1_00, "F11");
    else if (keyname == "F12") makeKey(r4_f, r4_b, x1_00, x1_00, "F12");
    else if (keyname == "Print Screen") makeKey(r4_f, r4_b, x1_00, x1_00, "Print", "Screen");
    else if (keyname == "Scroll Lock") makeKey(r4_f, r4_b, x1_00, x1_00, "Scroll", "Lock");
    else if (keyname == "Pause") makeKey(r4_f, r4_b, x1_00, x1_00, "Pause", "Break");
    else if (keyname == "`") makeKey(r4_f, r4_b, x1_00, x1_00, "~", "`");
    else if (keyname == "1") makeKey(r4_f, r4_b, x1_00, x1_00, "!", "1");
    else if (keyname == "2") makeKey(r4_f, r4_b, x1_00, x1_00, "@", "2");
    else if (keyname == "3") makeKey(r4_f, r4_b, x1_00, x1_00, "#", "3");
    else if (keyname == "4") makeKey(r4_f, r4_b, x1_00, x1_00, "$", "4");
    else if (keyname == "5") makeKey(r4_f, r4_b, x1_00, x1_00, "%", "5");
    else if (keyname == "6") makeKey(r4_f, r4_b, x1_00, x1_00, "^", "6");
    else if (keyname == "7") makeKey(r4_f, r4_b, x1_00, x1_00, "&", "7");
    else if (keyname == "8") makeKey(r4_f, r4_b, x1_00, x1_00, "*", "8");
    else if (keyname == "9") makeKey(r4_f, r4_b, x1_00, x1_00, "(", "9");
    else if (keyname == "0") makeKey(r4_f, r4_b, x1_00, x1_00, ")", "0");
    else if (keyname == "-") makeKey(r4_f, r4_b, x1_00, x1_00, "_", "-");
    else if (keyname == "=") makeKey(r4_f, r4_b, x1_00, x1_00, "+", "=");
    else if (keyname == "Backspace") makeKey(r4_f, r4_b, x1_00, x2_00, "◄ Backspace", "", normalSpacing);
    else if (keyname == "Insert") makeKey(r4_f, r4_b, x1_00, x1_00, "Insert");
    else if (keyname == "Home") makeKey(r4_f, r4_b, x1_00, x1_00, "Home");
    else if (keyname == "Page Up") makeKey(r4_f, r4_b, x1_00, x1_00, "Page", "Up");
    else if (keyname == "Num Lock") makeKey(r4_f, r4_b, x1_00, x1_00, "Num", "Lock");
    else if (keyname == "Num /") makeKey(r4_f, r4_b, x1_00, x1_00, "/");
    else if (keyname == "Num *") makeKey(r4_f, r4_b, x1_00, x1_00, "*");
    else if (keyname == "Num -") makeKey(r4_f, r4_b, x1_00, x1_00, "-");
    else if (keyname == "Tab") makeKey(r3_f, r3_b, x1_00, x1_50, "Tab");
    else if (keyname == "Q") makeKey(r3_f, r3_b, x1_00, x1_00, "Q", " ");
    else if (keyname == "W") makeKey(r3_f, r3_b, x1_00, x1_00, "W", " ");
    else if (keyname == "E") makeKey(r3_f, r3_b, x1_00, x1_00, "E", " ");
    else if (keyname == "R") makeKey(r3_f, r3_b, x1_00, x1_00, "R", " ");
    else if (keyname == "T") makeKey(r3_f, r3_b, x1_00, x1_00, "T", " ");
    else if (keyname == "Y") makeKey(r3_f, r3_b, x1_00, x1_00, "Y", " ");
    else if (keyname == "U") makeKey(r3_f, r3_b, x1_00, x1_00, "U", " ");
    else if (keyname == "I") makeKey(r3_f, r3_b, x1_00, x1_00, "I", " ");
    else if (keyname == "O") makeKey(r3_f, r3_b, x1_00, x1_00, "O", " ");
    else if (keyname == "P") makeKey(r3_f, r3_b, x1_00, x1_00, "P", " ");
    else if (keyname == "[") makeKey(r3_f, r3_b, x1_00, x1_00, "{", "[");
    else if (keyname == "]") makeKey(r3_f, r3_b, x1_00, x1_00, "}", "]");
    else if (keyname == "\\") makeKey(r3_f, r3_b, x1_00, x1_50, "|", "\\");
    else if (keyname == "Delete") makeKey(r3_f, r3_b, x1_00, x1_00, "Delete");
    else if (keyname == "End") makeKey(r3_f, r3_b, x1_00, x1_00, "End");
    else if (keyname == "Page Down") makeKey(r3_f, r3_b, x1_00, x1_00, "Page", "Down");
    else if (keyname == "Num 7") makeKey(r3_f, r3_b, x1_00, x1_00, "7", "Home");
    else if (keyname == "Num 8") makeKey(r3_f, r3_b, x1_00, x1_00, "8", "▲");
    else if (keyname == "Num 9") makeKey(r3_f, r3_b, x1_00, x1_00, "9", "Pg Up");
    else if (keyname == "Num +") makeKey(r2_f, r3_b, x2_00, x1_00, "+", "", normalSpacing, "vertical");
    else if (keyname == "Caps Lock") makeKey(r2_f, r2_b, x1_00, x1_50, "CapsLock");
    else if (keyname == "A") makeKey(r2_f, r2_b, x1_00, x1_00, "A", " ");
    else if (keyname == "S") makeKey(r2_f, r2_b, x1_00, x1_00, "S", " ");
    else if (keyname == "D") makeKey(r2_f, r2_b, x1_00, x1_00, "D", " ");
    else if (keyname == "F") makeKey(r2_f, r2_b, x1_00, x1_00, "F", "     _");
    else if (keyname == "G") makeKey(r2_f, r2_b, x1_00, x1_00, "G", " ");
    else if (keyname == "H") makeKey(r2_f, r2_b, x1_00, x1_00, "H", " ");
    else if (keyname == "J") makeKey(r2_f, r2_b, x1_00, x1_00, "J", "     _");
    else if (keyname == "K") makeKey(r2_f, r2_b, x1_00, x1_00, "K", " ");
    else if (keyname == "L") makeKey(r2_f, r2_b, x1_00, x1_00, "L", " ");
    else if (keyname == ";") makeKey(r2_f, r2_b, x1_00, x1_00, ":", ";");
    else if (keyname == "'") makeKey(r2_f, r2_b, x1_00, x1_00, "'", "\"");
    else if (keyname == "Enter") makeKey(r2_f, r2_b, x1_00, x2_25, "Enter", "", normalSpacing);
    else if (keyname == "Num 4") makeKey(r2_f, r2_b, x1_00, x1_00, "4", "◄");
    else if (keyname == "Num 5") makeKey(r2_f, r2_b, x1_00, x1_00, "5", "     _");
    else if (keyname == "Num 6") makeKey(r2_f, r2_b, x1_00, x1_00, "6", "►");
    else if (keyname == "Left Shift") makeKey(r1_f, r1_b, x1_00, x2_25, "Shift", "", normalSpacing);
    else if (keyname == "Z") makeKey(r1_f, r1_b, x1_00, x1_00, "Z", " ");
    else if (keyname == "X") makeKey(r1_f, r1_b, x1_00, x1_00, "X", " ");
    else if (keyname == "C") makeKey(r1_f, r1_b, x1_00, x1_00, "C", " ");
    else if (keyname == "V") makeKey(r1_f, r1_b, x1_00, x1_00, "V", " ");
    else if (keyname == "B") makeKey(r1_f, r1_b, x1_00, x1_00, "B", " ");
    else if (keyname == "N") makeKey(r1_f, r1_b, x1_00, x1_00, "N", " ");
    else if (keyname == "M") makeKey(r1_f, r1_b, x1_00, x1_00, "M", " ");
    else if (keyname == ",") makeKey(r1_f, r1_b, x1_00, x1_00, "<", ",");
    else if (keyname == ".") makeKey(r1_f, r1_b, x1_00, x1_00, ">", ".");
    else if (keyname == "/") makeKey(r1_f, r1_b, x1_00, x1_00, "?", "/");
    else if (keyname == "Right Shift") makeKey(r1_f, r1_b, x1_00, x2_75, "Shift", "", normalSpacing);
    else if (keyname == "Up") makeKey(r1_f, r1_b, x1_00, x1_00, "▲");
    else if (keyname == "Num 1") makeKey(r1_f, r1_b, x1_00, x1_00, "1", "End");
    else if (keyname == "Num 2") makeKey(r1_f, r1_b, x1_00, x1_00, "2", "▼");
    else if (keyname == "Num 3") makeKey(r1_f, r1_b, x1_00, x1_00, "3", "Pg Dn");
    else if (keyname == "Num Enter") makeKey(r1_f, r1_b, x2_00, x1_00, "Enter", "", normalSpacing, "vertical");
    else if (keyname == "Ctrl") makeKey(r1_f, r1_b, x1_00, x1_25, "Ctrl");
    else if (keyname == "Win") makeKey(r1_f, r1_b, x1_00, x1_25, "Win");
    else if (keyname == "Alt") makeKey(r1_f, r1_b, x1_00, x1_25, "Alt");
    else if (keyname == "Space") makeKey(r1_f, r1_b, x1_00, space, "", "", spacebarSpacing);
    else if (keyname == "Menu") makeKey(r1_f, r1_b, x1_00, x1_25, "Menu");
    else if (keyname == "Left") makeKey(r1_f, r1_b, x1_00, x1_00, "◄");
    else if (keyname == "Down") makeKey(r1_f, r1_b, x1_00, x1_00, "▼");
    else if (keyname == "Right") makeKey(r1_f, r1_b, x1_00, x1_00, "►");
    else if (keyname == "Num 0") makeKey(r1_f, r1_b, x1_00, x2_00, "0", "Ins");
    else if (keyname == "Num .") makeKey(r1_f, r1_b, x1_00, x1_00, ".", "Del");
} // end key

// front and back are heights, defined by row number
// deep and wide are measurements defined by keysize multiples
// keyText1 and keyText2 are the literal lines of text to be displayed on top of the key
// spacing is the measure from center to center of middle and offset stems, if applicable
// spaceAlign specifies the orientation for support posts, "vertical" for num+ and numEnter
module makeKey(front, back, deep, wide, keyText1, keyText2="", spacing=0, spaceAlign="horizontal")
{
    // find the lower height to base the inside roof on
    lowerHeight = (front < back ? front : back);
    union()
    {
        difference()
        {
            // outter shell
            hull()
            {
              // bottom
               // right
                // back
                translate([ (wide/2 - rounding/2),  (deep/2 - rounding/2), 0])
                    cylinder(h=0.001, d=rounding);
                // front
                translate([ (wide/2 - rounding/2), -(deep/2 - rounding/2), 0])
                    cylinder(h=0.001, d=rounding);
               // left
                // back
                translate([-(wide/2 - rounding/2),  (deep/2 - rounding/2), 0])
                    cylinder(h=0.001, d=rounding);
                // front
                translate([-(wide/2 - rounding/2), -(deep/2 - rounding/2), 0])
                    cylinder(h=0.001, d=rounding);
              // top
               // right
                // back
                translate([ (wide/2 - rounding/2 - insetX/2),  (deep/2 - rounding/2 - insetYback), back - rounding/2])
                    sphere(d=rounding);
                // front
                translate([ (wide/2 - rounding/2 - insetX/2), -(deep/2 - rounding/2 - insetYfront), front - rounding/2])
                    sphere(d=rounding);
               // left
                // back
                translate([-(wide/2 - rounding/2 - insetX/2),  (deep/2 - rounding/2 - insetYback), back - rounding/2])
                    sphere(d=rounding);
                // front
                translate([-(wide/2 - rounding/2 - insetX/2), -(deep/2 - rounding/2 - insetYfront), front - rounding/2])
                    sphere(d=rounding);
            } // end hull
            
            // inner cavity
            hull()
            {
              // bottom
               // right
                // back
                translate([ (wide/2 - rounding/2 - wallThick),  (deep/2 - rounding/2 - wallThick), -0.001])
                    cylinder(h=0.001, d=rounding);
                // front
                translate([ (wide/2 - rounding/2 - wallThick), -(deep/2 - rounding/2 - wallThick), -0.001])
                    cylinder(h=0.001, d=rounding);
               // left
                // back
                translate([-(wide/2 - rounding/2 - wallThick),  (deep/2 - rounding/2 - wallThick), -0.001])
                    cylinder(h=0.001, d=rounding);
                // front
                translate([-(wide/2 - rounding/2 - wallThick), -(deep/2 - rounding/2 - wallThick), -0.001])
                    cylinder(h=0.001, d=rounding);
              // top
               // right
                // back
                translate([ (wide/2 - rounding/2 - insetX/2 - wallThick),  (deep/2 - rounding/2 - insetYback - wallThick), lowerHeight - wallThick - rounding/2])
                    sphere(d=rounding);
                // front
                translate([ (wide/2 - rounding/2 - insetX/2 - wallThick), -(deep/2 - rounding/2 - insetYfront - wallThick), lowerHeight - wallThick - rounding/2])
                    sphere(d=rounding);
               // left
                // back
                translate([-(wide/2 - rounding/2 - insetX/2 - wallThick),  (deep/2 - rounding/2 - insetYback - wallThick), lowerHeight - wallThick - rounding/2])
                    sphere(d=rounding);
                // front
                translate([-(wide/2 - rounding/2 - insetX/2 - wallThick), -(deep/2 - rounding/2 - insetYfront - wallThick), lowerHeight - wallThick - rounding/2])
                    sphere(d=rounding);
            } // end hull
            
            // if only one line of text
            if (keyText2 == "")
            {
                translate([-wide/2 + insetX/2 + rounding*0.75, 0, lowerHeight - wallThick/2])
                    linear_extrude(abs(front - back) + wallThick/2)
                        text(text=keyText1, size=2.5, font="Arial", halign="left", valign="center");
            }
            // if two lines of text
            else
            {
                translate([-wide/2 + insetX/2 + rounding*0.75, 2, lowerHeight - wallThick/2])
                    linear_extrude(abs(front - back) + wallThick/2)
                        text(text=keyText1, size=2.5, font="Arial", halign="left", valign="center");
                translate([-wide/2 + insetX/2 + rounding*0.75, -1.5, lowerHeight - wallThick/2])
                    linear_extrude(abs(front - back) + wallThick/2)
                        text(text=keyText2, size=2.5, font="Arial", halign="left", valign="center");
            }
        } // end difference
        
        // center post
        difference()
        {
            translate([0, 0, postBottomGap])
                cylinder(h=lowerHeight - wallThick - postBottomGap, d=postDiam);
            cube([crossWide, crossLong, (lowerHeight - wallThick)*2], center=true);
            cube([crossLong, crossWide, (lowerHeight - wallThick)*2], center=true);
        } // end difference
        
        // if this key has extra support posts
        if (spacing != 0)
        {
            translate([spaceAlign == "horizontal" ? spacing : 0, spaceAlign == "vertical" ? spacing : 0, 0])
                difference()
                {
                    translate([0, 0, postBottomGap])
                        cylinder(h=lowerHeight - wallThick - postBottomGap, d=postDiam);
                    cube([crossWide, crossLong, (lowerHeight - wallThick)*2], center=true);
                    cube([crossLong, crossWide, (lowerHeight - wallThick)*2], center=true);
                } // end difference
            
            translate([spaceAlign == "horizontal" ? -spacing : 0, spaceAlign == "vertical" ? -spacing : 0, 0])
                difference()
                {
                    translate([0, 0, postBottomGap])
                        cylinder(h=lowerHeight - wallThick - postBottomGap, d=postDiam);
                    cube([crossWide, crossLong, (lowerHeight - wallThick)*2], center=true);
                    cube([crossLong, crossWide, (lowerHeight - wallThick)*2], center=true);
                } // end difference
        }
    } // end union
} // end makeKey

// key("Space");
// translate([-50, 20, 0])   
// {
//     key("Escape");
//     translate([35, 0, 0])
//         key("Enter");
//     translate([70, 0, 0])
//         key("U");
//     translate([90, 0, 0])
//         key("J");
//     translate([110, 0, 0])
//         key("N");
//     translate([130, -10, 0])
//         key("Num Enter");
// }
// translate([-50, 40, 0])   
// {
//     key("W");
//     translate([20, 0, 0])
//         key("A");
//     translate([40, 0, 0])
//         key("S");
//     translate([60, 0, 0])
//         key("D");
//     translate([80, 0, 0])
//         key("7");
//     translate([100, 0, 0])
//         key("Print Screen");
//     translate([125, 0, 0])
//         key("Tab");
// }

