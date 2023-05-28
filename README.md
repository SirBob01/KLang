# KLang

Compiler for KLang, a simple type-safe language inspired by Rust and C.

## Syntax

* Declaring scalar variables

```
// <var_name>: <type> = <value>
x: u32 = 3
```

* Declaring array variables

```
// Arrays are structures that store both the buffer and its length
array: u32[] = [1, 2, 3, 4, 5]

// Can only use unsigned ints as indices
val: u32 = array[0]
```

* Control flow

```
if (x % 3 == 0) and (x % 5 == 0) {
    writeln("Fizzbuzz")
} elif x % 3 == 0 {
    writeln("Fizz)
} elif x % 5 == 0 {
    writeln("Fizzbuzz")
} else {
    writeln(to_string(x))
}
```

* Loops

```
x: u32 = 0 
while x < 15 {
    x = x + 5
    writeln(to_string(x))
}
```

* Function definitions


```
fn add_numbers(x: u32, y: u32): u32 {
    return x + y
}
```

* Structures

```
struct Person {
    name: char[3]
    age: u32
}
```

## License

Code and documentation Copyright (c) 2023 Keith Leonardo

Code released under the [MIT License](https://choosealicense.com/licenses/mit/).
