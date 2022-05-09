type lst('a) =
  | Nil
  | Cons('a, lst('a));

let (^:): ('a, lst('a)) => lst('a);

let headOr: ('a, lst('a)) => 'a;

let sum: lst(int) => int;

let product: lst(int) => int;

let length: lst('a) => int;