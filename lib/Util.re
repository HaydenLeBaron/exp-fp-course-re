let rec fac: (int => int, int) => int =
  (f, n) => n == 0 ? 1 : fac(f, f(n - 1));

print_endline(Int.to_string(fac(x => x, 4)));
let hello = () => "hola mundo" ++ Int.to_string(fac(x => x, 4));