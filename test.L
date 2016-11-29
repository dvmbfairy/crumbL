
func foo()
	x = 1 + 1;
	ret x;
cnuf


y = foo();


print(y);



func abc(x, y, z)
	a = x + y + z;
	ret a;
cnuf



y = abc(1,2,3);
print(y);

print("this will produce a runtime error");
y = abc(1);