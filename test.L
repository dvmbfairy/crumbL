(* Test lazy evaluation of expression assignment to id *)
lazy y = 1 + "duck";
print(1);

(* Test lazy evaluation on the result of a function call *)
func test1()
  y = 2 + "duck";
  ret 1;
cnuf
lazy y = test1(1);
print(2);

(* Test that variables have separate scope in functions *)
y = 3;
func test2()
  y = 2;
  ret 1;
cnuf
temp = test2();
print(y);

(* Test modulo *)
print(4 % 5);

(* Test while loop *)
i = 5;
while(i < 7) do
  print(i);
  i = i + 1;
ob

(* Test multi arg functions *)
func add(x, y)
  bleh = 3;
  ret x + y;
cnuf
print(add(3, 4));

(* Test truthiness of expressions *)
if(0) then
  print("wrong");
else
  if(1) then
	if("true string") then
	  if("") then
	    print("wrong");
	  else
	    print(8);
	  fi
	else
	  print("wrong");
	fi
  else
	print("wrong");
  fi
fi

(* Test lazy function parameters *)
func testLazyFuncParams(lazy x, y)
  temp = 9;
  ret y + 1;
cnuf
print(testLazyFuncParams(7 + "duck", 8));

(* Test repurposing lazy identifiers *)
x = 9;
lazy x = 7 + "duck";
x = 10;
print(x);

(* Test lazy in new scope with unevaluated values from outside scope *)
func testLazyScope(x)
  temp = 9;
  ret x + 5;
cnuf
x = 3;
lazy y = x + x;
print(testLazyScope(y));

(* Test recursion *)
func recur(x)
  if(x == 0) then
	val = 0;
  else
	val = recur(x - 1);
  fi
  ret x + val;
cnuf
print(recur(4) + 2);

print(-4);
