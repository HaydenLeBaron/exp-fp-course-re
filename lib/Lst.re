/*
 ===== Lst ==============================================
   To run test suite: esy test:Lst
   (Exercises adapted from
   https://github.com/system-f/fp-course/blob/master/src/Course/List.hs)*/

/** | Create a list - this is a 'linked list' */
type lst('a) =
  | Nil
  | Cons('a, lst('a));

/** | Create an operator for Cons
  '^' creates a right associative operator, which is what we want here
*/
let (^:) = (a, l) => Cons(a, l);

/** | Returns the head of the list or the given default.
  >>> headOr 3 (1 :. 2 :. Nil)
  1
  >>> headOr 3 Nil
  3
*/
let headOr: ('a, lst('a)) => 'a = (a, _) => a;

/** | Sum the elements of the list.
  >>> sum (1 :. 2 :. 3 :. Nil)
  6
  >>> sum (1 :. 2 :. 3 :. 4 :. Nil)
  10
*/
let rec sum: lst(int) => int = _ => (-1);

/** | The product of the elements of a list.
  >>> product Nil
  1
  >>> product (1 :. 2 :. 3 :. Nil)
  6
  >>> product (1 :. 2 :. 3 :. 4 :. Nil)
  24
*/
let rec product: lst(int) => int = _ => (-1);

/** | Return the length of the list.
  >>> length (1 :. 2 :. 3 :. Nil)
  3
*/
let length: lst('a) => int = _ => (-1);

/** | Map the given function on each element of the list.
>>> map (+10) (1 :. 2 :. 3 :. Nil)
[11,12,13]
prop> \x -> headOr x (map (+1) infinity) == 1
prop> \x -> map id x == x
*/
let map: ('a => 'b, lst('a)) => lst('b) = (_, _) => Nil;

/** | Return elements satisfying the given predicate.
 >>> filter even (1 :. 2 :. 3 :. 4 :. 5 :. Nil)
 [2,4]
 prop> \x -> headOr x (filter (const True) infinity) == 0
 prop> \x -> filter (const True) x == x
 prop> \x -> filter (const False) x == Nil
*/
let filter: ('a => bool, lst('a)) => lst('a) = (_, _) => Nil;

/** | Append two lists to a new list.
-- >>> (1 :. 2 :. 3 :. Nil) ++ (4 :. 5 :. 6 :. Nil)
-- [1,2,3,4,5,6]
-- prop> \x -> headOr x (Nil ++ infinity) == 0
-- prop> \x -> headOr x (y ++ infinity) == headOr 0 y
-- prop> \x -> (x ++ y) ++ z == x ++ (y ++ z)
-- prop> \x -> x ++ Nil == x
*/
let (++^): (lst('a), lst('a)) => lst('a) = (_, _) => Nil;

/** | Flatten a list of lists to a list.
-- >>> flatten ((1 :. 2 :. 3 :. Nil) :. (4 :. 5 :. 6 :. Nil) :. (7 :. 8 :. 9 :. Nil) :. Nil)
-- [1,2,3,4,5,6,7,8,9]
-- prop> \x -> headOr x (flatten (infinity :. y :. Nil)) == 0
-- prop> \x -> headOr x (flatten (y :. infinity :. Nil)) == headOr 0 y
-- prop> \x -> sum (map length x) == length (flatten x)
*/
let flatten: lst(lst('a)) => lst('a) = _ => Nil;

/** | Map a function then flatten to a list.
-- >>> flatMap (\x -> x :. x + 1 :. x + 2 :. Nil) (1 :. 2 :. 3 :. Nil)
-- [1,2,3,2,3,4,3,4,5]
-- prop> \x -> headOr x (flatMap id (infinity :. y :. Nil)) == 0
-- prop> \x -> headOr x (flatMap id (y :. infinity :. Nil)) == headOr 0 y
-- prop> \x -> flatMap id (x :: List (List Int)) == flatten x
*/
let flatMap: ('a => lst('b), lst('a)) => lst('b) = (_, _) => Nil;

/** | Flatten a list of lists to a list (again).
-- HOWEVER, this time use the /flatMap/ function that you just wrote.
--
-- prop> \x -> let types = x :: List (List Int) in flatten x == flattenAgain x
*/
let flattenAgain: lst(lst('a)) => lst('a) = _ => Nil;

/** | Convert a list of optional values to an optional list of values.
-- * If the list contains all `Full` values,
-- then return `Full` list of values.
-- * If the list contains one or more `Empty` values,
-- then return `Empty`.
-- >>> seqOptional (Full 1 :. Full 10 :. Nil)
-- Full [1, 10]
-- >>> seqOptional Nil
-- Full []
-- >>> seqOptional (Full 1 :. Full 10 :. Empty :. Nil)
-- Empty
-- >>> seqOptional (Empty :. map Full infinity)
-- Empty
*/
let seqOptional: lst(option('a)) => option(lst('a)) = _ => None;

/** | Find the first element in the list matching the predicate.
-- >>> find even (1 :. 3 :. 5 :. Nil)
-- Empty
-- >>> find even Nil
-- Empty
-- >>> find even (1 :. 2 :. 3 :. 5 :. Nil)
-- Full 2
-- >>> find even (1 :. 2 :. 3 :. 4 :. 5 :. Nil)
-- Full 2
-- >>> find (const True) infinity
-- Full 0
*/
let find: ('a => bool, lst('a)) => option('a) = (_, _) => None;

/** | Determine if the length of the given list is greater than 4.
-- >>> lengthGT4 (1 :. 3 :. 5 :. Nil)
-- False
-- >>> lengthGT4 Nil
-- False
-- >>> lengthGT4 (1 :. 2 :. 3 :. 4 :. 5 :. Nil)
-- True
-- >>> lengthGT4 infinity
-- True
*/
let lengthGT4: lst('a) => bool = _ => false;

/** >>> reverse Nil
-- []
-- >>> take 1 (reverse (reverse largeList))
-- [1]
-- prop> \x -> let types = x :: List Int in reverse x ++ reverse y == reverse (y ++ x)
-- prop> \x -> let types = x :: Int in reverse (x :. Nil) == x :. Nil
*/
let reverse: lst('a) => lst('a) = _ => Nil;

/** | Produce an infinite `List` that seeds with the given value at its head,
-- then runs the given function for subsequent elements
--
-- >>> let (x:.y:.z:.w:._) = produce (+1) 0 in [x,y,z,w]
-- [0,1,2,3]
--
-- >>> let (x:.y:.z:.w:._) = produce (*2) 1 in [x,y,z,w]
-- [1,2,4,8]
*/
let produce: ('a => 'a, 'a) => lst('a) = (_, _) => Nil;

/** | Do anything other than reverse a list.
-- Is it even possible?
-- >>> notReverse Nil
-- []
-- prop> \x y -> let types = x :: List Int in notReverse x ++ notReverse y == notReverse (y ++ x)
-- prop> \x -> let types = x :: Int in notReverse (x :. Nil) == x :. Nil
*/
let notReverse: lst('a) => lst('a) = _ => Nil;
