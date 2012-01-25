u := 0.45cm;

beginfig(1)
  draw (0,6.5u)--(4u,10.5u)--(6u,8.5u)--(7u,9.5u)--(10u,6.5u);
  z1 = (4u,9u);
  z2 = (7u,8u);
  z3 = (4u,7u);
  z4 = (2.5u,5u);
  z5 = (6u,4u);
  z6 = (9u,4u);
  z7 = (7.5u,6u);
  z8 = (4.5u,2u);
  for i := 1 upto 8:
    fill fullcircle scaled 2pt shifted z[i];
    label.lft(decimal i, z[i]);
  endfor
  drawarrow z1--z3;
  drawarrow z3--z4;
  drawarrow z3--z5;
  drawarrow z5--z8;
  drawarrow z2--z7;
  drawarrow z7--z5;
  drawarrow z4--z8;
  drawarrow z7--z6;
endfig;

end.