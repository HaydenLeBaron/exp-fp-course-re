let id = x => x;

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
