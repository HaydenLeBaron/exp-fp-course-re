let rec fac: (int => int, int) => int =
  (f, n) => n == 0 ? 1 : fac(f, f(n - 1));

let id = x => x;
print_endline(Int.to_string(fac(x => x, 4)));
let hello = () => "hola mundo" ++ Int.to_string(fac(x => x, 4));

let assertInt: (string, int, int) => unit =
  (message, a, b) =>
    if (a == b) {
      ();
    } else {
      print_endline(
        "Failed: '"
        ++ message
        ++ "'"
        ++ "Expected: "
        ++ Int.to_string(a)
        ++ "Actual: "
        ++ Int.to_string(b),
      );
      exit(1);
    };

// Create function to print a list
let rec show: ('a => string, Lst.lst('a)) => string =
  showT =>
    fun
    | Cons(a, l) => showT(a) ++ ", " ++ show(showT, l)
    | Nil => "Nil";

let show = (showT, l) => "[" ++ show(showT, l) ++ "]";

let showInt = Int.to_string |> show;
// Why is 'id' used?
let showString = id |> show;
