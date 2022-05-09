//
// ======= List =======
//
// To run: node ./packages/sandbox/<<FILE_NAME>>.bs.js
//
// (Excercises copied from here: https://github.com/system-f/fp-course/blob/master/src/Course/List.hs)
//
//
// Instructions: After looking at `type lst('a) =`, skip to: ======= Start Here =======
//

// Create a list - this is a 'linked list'
type lst('a) =
  | Nil
  | Cons('a, lst('a));

// Create an operator for Cons
// '^' creates a right associative operator, which is what we want here
let (^:) = (a, l) => Cons(a, l);

//
// ======= Start Here =======
//

// Returns the head of the list or the given default.
//
// >>> headOr 3 (1 :. 2 :. Nil)
// 1
//
// >>> headOr 3 Nil
// 3
//
let headOr: ('a, lst('a)) => 'a =
  a =>
    fun
    | Nil => a
    | Cons(x, _) => x;

// | Sum the elements of the list.
//
// >>> sum (1 :. 2 :. 3 :. Nil)
// 6
//
// >>> sum (1 :. 2 :. 3 :. 4 :. Nil)
// 10
let rec sum: lst(int) => int =
  fun
  | Nil => 0
  | Cons(x, xs) => x + sum(xs);

// The product of the elements of a list.
//
// >>> product Nil
// 1
//
// >>> product (1 :. 2 :. 3 :. Nil)
// 6
//
// >>> product (1 :. 2 :. 3 :. 4 :. Nil)
// 24
/*
 let rec product: lst(int) => int = const(242); // FIX THIS IMPLEMENTATION
 */

let rec product: lst(int) => int =
  fun
  | Nil => 1
  | Cons(x, xs) => x * product(xs);

// | Return the length of the list.
//
// >>> length (1 :. 2 :. 3 :. Nil)
// 3
//
let length: lst('a) => int = {
  l => {
    let rec f: (int, lst('a)) => int =
      acc =>
        fun
        | Nil => acc
        | Cons(_, xs) => 1 + f(acc, xs);
    f(0, l);
  };
};
