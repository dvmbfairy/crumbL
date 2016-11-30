
func factorial(x)
	print(x);
	if(x == 0) then
		y = 1;
	else
		y = x*factorial(x-1);
	fi
	ret y;
cnuf


z = factorial(3);


print("factorial of 3: "::z);

