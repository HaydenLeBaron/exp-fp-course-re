open CoreUtil;

// BKMRK: TESTME: is this a correct implementation of foldLeft?

let rec foldLeft: (('a, 'b) => 'a, 'a, Lst.lst('b)) => 'a =
  (f, acc) =>
    fun
    | Nil => acc
    | Cons(h, t) => foldLeft(f, f(acc, h), t);

// BKMRK: TESTME: is this a correct implementation of foldRight?
let rec foldRight: (('a, 'b) => 'b, 'b, Lst.lst('a)) => 'b =
  (f, acc) =>
    fun
    | Nil => acc
    | Cons(h, t) => f(h, foldRight(f, acc, t));

// Create function to print a list
let rec showLst: ('a => string, Lst.lst('a)) => string =
  showT =>
    fun
    | Cons(a, l) => showT(a) ++ ", " ++ showLst(showT, l)
    | Nil => "Nil";

let showLst = (showT, l) => "[" ++ showLst(showT, l) ++ "]";

let showLstofInt = Int.to_string |> showLst;

let showLstofString = id |> showLst;

let rec zipWith: (('a, 'b) => 'c, Lst.lst('a), Lst.lst('b)) => Lst.lst('c) =
  (f, l1, l2) =>
    switch (f, l1, l2) {
    | (f, Cons(x, xs), Cons(y, ys)) => Cons(f(x, y), zipWith(f, xs, ys))
    | (_, _, _) => Nil
    };

// for some reason the type checker doesn't like the point-free implementation of this.
let zip: (Lst.lst('a), Lst.lst('b)) => Lst.lst(('a, 'b)) =
  (l1, l2) => zipWith((x, y) => (x, y), l1, l2);

let rec equal: (('a, 'a) => bool, Lst.lst('a), Lst.lst('a)) => bool =
  (eq, l1, l2) =>
    Lst.length(l1) == Lst.length(l2)
    && foldLeft((&&), true, zipWith(eq, l1, l2));

let assertLstofInt: (string, Lst.lst(int), Lst.lst(int)) => unit =
  (message, la, lb) =>
    if (equal((==), la, lb)) {
      ();
    } else {
      print_endline(
        "Failed: '"
        ++ message
        ++ "' "
        ++ "Expected: "
        ++ showLstofInt(la)
        ++ " ;; Actual: "
        ++ showLstofInt(lb),
      );
    };