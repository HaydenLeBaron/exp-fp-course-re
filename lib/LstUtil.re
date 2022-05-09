open CoreUtil;
open Lst;

// BKMRK: TESTME: is this a correct implementation of foldLeft?
let rec foldLeft: (('a, 'b) => 'a, 'a, lst('b)) => 'a =
  (f, acc) =>
    fun
    | Nil => acc
    | Cons(h, t) => foldLeft(f, f(acc, h), t);

// BKMRK: TESTME: is this a correct implementation of foldRight?
let rec foldRight: (('a, 'b) => 'b, 'b, lst('a)) => 'b =
  (f, acc) =>
    fun
    | Nil => acc
    | Cons(h, t) => f(h, foldRight(f, acc, t));

// Create function to print a list
let rec showList: ('a => string, lst('a)) => string =
  showT =>
    fun
    | Cons(a, l) => showT(a) ++ ", " ++ showList(showT, l)
    | Nil => "Nil";

let showList = (showT, l) => "[" ++ showList(showT, l) ++ "]";

let showListofInt = Int.to_string |> showList;
// Why is 'id' used?
let showListofString = id |> showList;
