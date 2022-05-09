type lst('a) =
  | Nil
  | Cons('a, lst('a));

let (^:): ('a, lst('a)) => lst('a);

let headOr: ('a, lst('a)) => 'a;

let sum: lst(int) => int;

let product: lst(int) => int;

let length: lst('a) => int;
let map: ('a => 'b, lst('a)) => lst('b);
let filter: ('a => bool, lst('a)) => lst('a);
let (++^): (lst('a), lst('a)) => lst('a);
let flatten: lst(lst('a)) => lst('a);
let flatMap: ('a => lst('b), lst('a)) => lst('b);
let flattenAgain: lst(lst('a)) => lst('a);
let seqOptional: lst(option('a)) => option(lst('a));
let find: ('a => bool, lst('a)) => option('a);
let lengthGT4: lst('a) => bool;
let reverse: lst('a) => lst('a);
let produce: ('a => 'a, 'a) => lst('a);
let notReverse: lst('a) => lst('a);
