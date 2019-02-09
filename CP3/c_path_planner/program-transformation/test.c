int foo(int x)
{
  printf("test");
  int y;
  int z[2];

  y = z[0];

  while(x < y) {
    x++;
  }

  for(int i = y; i < y; i++) {
    x++;
  }

  if(x < y) {
    return x;
  }

  return 1 + x;
}
