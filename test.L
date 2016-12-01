func t1(x)
	print("t1: "::x);
	x = x+1;
	func t2(y)
		print("t2: "::y);
		func t3(z)
			print("t3: "::z);


			ret 0;
		cnuf

		y = y + 1;
		_ = t3(y);
		ret 0;
	cnuf
	

	_ = t2(x);
	ret 0;
cnuf


y = t1(3);

