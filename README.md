[![Build Status](https://travis-ci.org/jbytecode/rcaller.svg?branch=master)](https://travis-ci.org/jbytecode/fuzuli)

# fuzuli (a general purpose interpreter)
http://stdioe.blogspot.com/search/label/fuzuli

* fuzuli is a Lispy programming language

Since it is not a real Lisp clone, the syntax is highly barrowed from Lisp:

```fuzuli
(print "Hello world!")
```

* The current implementation is running on the Java Virtual Machine (JVM)

```bash
$ java -jar dist/JFuzuli.jar 
Usage:
java -jar JFuzuli.jar fzlfile
java -jar JFuzuli.jar --repl
java -jar JFuzuli.jar --editor
```

Besides the syntax, fuzuli is not a Lisp!

```fuzuli
(let i 10)
(inc i)
(print i)
```

```fuzuli
11.0
```

* C/C++/Java style for loops

```fuzuli
(let i 0)
  
(for (let i 0) (< i 10) (inc i)
    (if (= i 5)
        (break)
    )
)

(print "i is " i)
```

* JVM integration

```fuzuli
(let cos0 (javastatic "java.lang.Math.cos" 0.0))
(let s (javanew "java.lang.String" "Hello JFuzuli!"))
```


* User-defined functions

```fuzuli
(function fibonacci (params x)
    (block
    (if (<= x 2)
        (return 1)
        (return (+ (fibonacci (- x 1)) (fibonacci (- x 2))))
    )
    )
)
```

(block) runs like Lisp's (progn), but in fuzuli (block) defines a local variable context wherever in the code:

```fuzuli
# x is global
(let x 4)

(block
    # a is local
    (let a 10)
)
```


* Runs with Javascript using the java's scripting interface

```fuzuli
(function square (params x)
    <?javascript
        var i = x * x;
    ?>
    (return i)
)
(print (square 5))
# result is 25
```


* Uses its own packaging system:

```fuzuli
(require "io.nfl")

(let f (fopen "testio.txt" "w"))
(let mylist (list 1 2 3 4 5 6 7 8 9 10 11 12 13 14))
(fwrite f mylist)
(fclose f)
```

* Any Java library can be wrapped using the nfl packaging system

* Where to start?

You can start by browsing the .fzl files included in the tests folder.
