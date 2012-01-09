u:=1.5cm;
f:=0.2*u;

def drawDancefloor =
  pair A,B;
  A:=(0,0);
  B:=(10u,0);

  drawarrow A--B;
  drawarrow B--A;

  for i=1 upto 9:
    draw (i*u, -u/10) -- (i*u, 0);
    label (decimal(i), (i*u, -0.35u) );
  endfor;
enddef;

def drawGuy(expr x) =
  path body;
  body := (0, 0) -- (1f, 1f) -- (1f, 3f) -- (1f, 2f) -- (0f, 2f) -- (2f, 2f) -- (1f, 2f) -- (1f, 1f) -- (2f, 0f);
  path head;
  head := fullcircle scaled f shifted (1f, 3.5f);

  draw body shifted (x*u - 1f, 0.3f);
  draw head shifted (x*u - 1f, 0.3f);
enddef;


beginfig(1)
  drawDancefloor;
  
  drawGuy(2);
  drawGuy(4);
  drawGuy(5);
  drawGuy(8);
endfig;

beginfig(2)
  drawDancefloor;
  
  drawGuy(3);
  drawGuy(4);
  drawGuy(5);
  drawGuy(6);
endfig;


end.
