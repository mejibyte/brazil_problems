
R := 3cm;
r := 0.5cm;
s := 0.75cm;
d := 1cm;
l := 2cm;
L := 5cm;

beginfig(1)
  pair p;
  transform t;
  t := identity xscaled 0.8;
  for i := 0 upto 5:
    p := (0,d) rotated (i*60);
    if i <= 2: 
      draw fullcircle scaled r shifted p transformed t;
    else:
      fill fullcircle scaled r shifted p transformed t;
      fill fullcircle scaled .7r shifted p transformed t withcolor white;
      fill fullcircle scaled .6r shifted p transformed t;
    fi
  endfor;
  draw fullcircle scaled 3pt transformed t;
  draw fullcircle scaled R transformed t;
  path c;
  c := halfcircle rotated -90 scaled R transformed t shifted (l,0);
  draw c;
  draw (0,R/2)--(l,R/2);
  draw (0,-R/2)--(l,-R/2);

  
  draw (0,d+r/2)--(l,d+r/2) dashed evenly;
  draw (0,d-r/2)--(l,d-r/2) dashed evenly;
  draw fullcircle scaled r transformed t shifted (l,d) dashed evenly;


  draw (l,d+s/2)--(l+L,d+s/2) cutbefore c;
  draw (l,d-s/2)--(l+L,d-s/2) cutbefore c;
  draw halfcircle rotated -90 scaled s transformed t shifted (l+L,d);
  draw ((0,0)--(0,2mm)--(5mm,2mm)--(5mm,0)) shifted (l+L-7mm,d+s/2);

  draw (l,d+r/2)--(l+L,d+r/2) dashed evenly;
  draw (l,d-r/2)--(l+L,d-r/2) dashed evenly;
  draw fullcircle scaled r transformed t shifted (l+L,d) dashed evenly;

endfig;

end.