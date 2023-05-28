# dynamic_bitset
Dynamic bitset library for  C++ 11/14/17

## Documentation
https://yakupbeyoglu.github.io/dynamic_bitset/html/classdynamic__bitset.html

## Examples
### Constructors
```
  // int to bit
  dynamic_bitset<> a = 10;
  
  // int to bit with padding
  dynamic_bitset<5> b = 11;
  
   // string to bit
  dynamic_bitset<> c = std::string("10101");
  
  // string to bit with padding
  dynamic_bitset<6> c = std::string("10101");
```

### Shift operators
```
  std::vector<bool> expected = {1, 0, 1, 0, 0};

  dynamic_bitset<> y = std::string("10101");
  y <<= 2;
  std::cout << y << std::endl;
  
  y >>= 2;
  std::cout << y << std::endl;
```

### Reverse
```
  dynamic_bitset<5> x = 11;
  std::cout << x.reverse() << std::endl;
```

### Subscript operator
```
  dynamic_bitset<> x = 11;
  x[0] = 0;
  x[2] = 0;
```

### Range operators
```
  dynamic_bitset<> x = 3;
  std::cout << x.all();
  std::cout << x.any();
  std::cout << x.none();
```

### Set & Get
```
  dynamic_bitset<6> x = "10101";
  std::vector<bool> expected = {0, 0, 0, 0, 0, 0};
  x.set(true);
  // response will be 1,1,1,1,1,1
  x.set(false);
  // response will be 0,0,0,0,0,0
  
  // Get return const std::vector<bool> &
  auto z = x.get();
```

### Iterators
```
  dynamic_bitset<6> x = "10101";
  for(const auto &v : x)
  	std::cout << v << ' ';

 for(auto i = x.begin(); i < x.end(); ++x)
 	std::cout << *i << std::endl;
 	
```

### Conversions
```
  dynamic_bitset<6> x = "10101";
  std::cout << x.to_ulong();
  std::cout << x.to_string();
```

### Logic Operators
```
  dynamic_bitset<> x = "10101";
  dynamic_bitset<> y = "10101";
  // And operators
  auto z = x & y;
  x &= y;
  
  // Or operators
  z = x | y;
  x |= y;
  
  // XOR Operators
  z = x ^ y;
  x ^= y;
```

