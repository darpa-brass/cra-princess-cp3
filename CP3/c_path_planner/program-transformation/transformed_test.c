
int foo(double ctrlCmp0,double ctrlLoop1,double ctrlLoop0,double ctrlConst0,int x)
{
  printf("test");
  int y;
  int z[2];
  y = z[0];
  while(x < y + ctrlLoop1){
    x++;
  }
  for (int i = y; i < y + ctrlLoop0; i++) {
    x++;
  }
  if (x < y + ctrlCmp0) {
    return x;
  }
  return ctrlConst0 + x;
}
