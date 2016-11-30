
func factorial(x)
	print(x);
	if(x == 0) then
		y = 1;
	else
		y = x*factorial(x-1);
	fi

	ret y;
cnuf


lazy z = factorial(3);
print("assigned z");
lazy p = factorial(123412341234);
print("assigned p");


print("factorial of 3: "::z);

