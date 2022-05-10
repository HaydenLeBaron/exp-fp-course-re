print_endline("Running Test Program:");
open Lib.LstUtil;
open Lib.CoreUtil;
open Lib.Lst;

//let () = print_endline(hello());

// Print
print_endline("== Examples");
print_endline("Lst(Nil)        -> " ++ (Nil |> showListofInt));
print_endline("Lst(Nil, 1):    -> " ++ (Cons(1, Nil) |> showListofInt));
print_endline(
  "Lst(Nil, 1, 2)  -> " ++ (Cons(2, Cons(1, Nil)) |> showListofInt),
);
print_endline("== Examples");
print_endline("");

assertInt("headOr #1.", 1, headOr(3, 1 ^: 2 ^: Nil));
assertInt("headOr #2.", 3, headOr(3, Nil));

assertInt("sum #1.", 6, sum(1 ^: 2 ^: 3 ^: Nil));
assertInt("sum #2.", 10, sum(1 ^: 2 ^: 3 ^: 4 ^: Nil));

assertInt("product #1.", 1, product(Nil));
assertInt("product #2.", 6, product(1 ^: 2 ^: 3 ^: Nil));
assertInt("product #3.", 24, product(1 ^: 2 ^: 3 ^: 4 ^: Nil));

assertInt("length #1.", 3, length(1 ^: 2 ^: 3 ^: Nil));
assertInt("length #2.", 0, length(Nil));

print_endline("Everything looks good!");

/*
 let test =
   QCheck.Test.make ~count:1000 ~name:"list_rev_is_involutive"
    QCheck.(list small_nat)
    (fun l -> List.rev (List.rev l) = l);;

 (* we can check right now the property... *)
 QCheck.Test.check_exn test;;
 */
