let showLst: ('a => string, Lst.lst('a)) => string;

let showLst: ('a => string, Lst.lst('a)) => string;

let showLstofInt: Lst.lst(int) => string;

let showLstofString: Lst.lst(string) => string;

let foldLeft: (('a, 'b) => 'a, 'a, Lst.lst('b)) => 'a;

let foldRight: (('a, 'b) => 'b, 'b, Lst.lst('a)) => 'b;

let zipWith: (('a, 'b) => 'c, Lst.lst('a), Lst.lst('b)) => Lst.lst('c);

let zip: (Lst.lst('a), Lst.lst('b)) => Lst.lst(('a, 'b));

let equal: (('a, 'a) => bool, Lst.lst('a), Lst.lst('a)) => bool;

let assertLstofInt: (string, Lst.lst(int), Lst.lst(int)) => unit;