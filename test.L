func lazy_test(lazy y) 

	y = y+y;
	ret y;
cnuf

lazy y = 4;
y = lazy_test(y);
print(y);