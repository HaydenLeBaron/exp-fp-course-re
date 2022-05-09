open CoreUtil;

// Create function to print a list
let rec showList: ('a => string, Lst.lst('a)) => string =
  showT =>
    fun
    | Cons(a, l) => showT(a) ++ ", " ++ showList(showT, l)
    | Nil => "Nil";

let showList = (showT, l) => "[" ++ showList(showT, l) ++ "]";

let showListofInt = Int.to_string |> showList;
// Why is 'id' used?
let showListofString = id |> showList;
