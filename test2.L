y = 1;

func testFunc(x)
  y = 2;
  ret x + 1;
cnuf

z = lazy testFunc(1)
print(y);
print(z);
print(y);
