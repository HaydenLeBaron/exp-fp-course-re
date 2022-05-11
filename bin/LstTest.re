print_endline("Running Test Program:");
open Lib.LstUtil;
open Lib.CoreUtil;
open Lib.Lst;

let showExamples = () => {
  print_endline("== Examples");
  print_endline("Lst(Nil)        -> " ++ (Nil |> showLstofInt));
  print_endline("Lst(Nil, 1):    -> " ++ (Cons(1, Nil) |> showLstofInt));
  print_endline(
    "Lst(Nil, 1, 2)  -> " ++ (Cons(2, Cons(1, Nil)) |> showLstofInt),
  );

  print_endline("== Examples");
  print_endline("");
};

let headOrTest = () => {
  assertInt("headOr #1.", 1, headOr(3, 1 ^: 2 ^: Nil));
  assertInt("headOr #2.", 3, headOr(3, Nil));
};

let sumTest = () => {
  assertInt("sum 1..3", 6, sum(1 ^: 2 ^: 3 ^: Nil));
  assertInt("sum 1..4.", 10, sum(1 ^: 2 ^: 3 ^: 4 ^: Nil));

  // TODO: convert to property based test (see fp-course)
  assertInt(
    "subtracting each element in a list from its sum is always 0",
    0,
    foldLeft(Int.sub, sum(1 ^: 2 ^: 3 ^: 4 ^: Nil), 1 ^: 2 ^: 3 ^: 4 ^: Nil),
  );
};

let productTest = () => {
  assertInt("product of empty list", 1, product(Nil));
  assertInt("product of 1..3", 6, product(1 ^: 2 ^: 3 ^: Nil));
  assertInt("product of 1..4", 24, product(1 ^: 2 ^: 3 ^: 4 ^: Nil));
};

let lengthTest = () => {
  assertInt("length 1..3.", 3, length(1 ^: 2 ^: 3 ^: Nil));
  assertInt("length of Nil.", 0, length(Nil));
  // TODO: convert to property based test (see fp-course)
  assertInt(
    "summing a list of 1s equal to its length",
    4,
    length(1 ^: 1 ^: 1 ^: 1 ^: Nil),
  );
};

let mapTest = () => {
  assertLstofInt(
    "add 10 on list",
    11 ^: 12 ^: 13 ^: Nil,
    map(x => x + 10, 1 ^: 2 ^: 3 ^: Nil),
  );
  assertInt(
    "headOr after map",
    2,
    headOr(-1, map(x => x + 1, 1 ^: 2 ^: 3 ^: Nil)),
  );
  assertLstofInt(
    "map id is id",
    1 ^: 2 ^: 3 ^: Nil,
    map(id, 1 ^: 2 ^: 3 ^: Nil),
  );
  assertLstofInt("map id is id (Nil)", Nil, map(id, Nil));
};

let filterTest = () => {
  assertLstofInt(
    "filter even",
    2 ^: 4 ^: Nil,
    filter(even, 1 ^: 2 ^: 3 ^: 4 ^: 5 ^: Nil),
  );

  assertLstofInt(
    "filter (const True) is identity",
    1 ^: 2 ^: Nil,
    filter(const(true), 1 ^: 2 ^: Nil),
  );

  assertLstofInt(
    "filter (const False) is the empty list",
    Nil,
    filter(const(false), 1 ^: 2 ^: Nil),
  );
};

/*

 appendTest :: TestTree
 appendTest =
   testGroup "(++)" [
     testCase "(1..6)" $
       (1 :. 2 :. 3 :. Nil) ++ (4 :. 5 :. 6 :. Nil) @?= listh [1,2,3,4,5,6]
   , testProperty "append empty to infinite" $
       \x -> headOr x (Nil ++ infinity) == 0
   , testProperty "append anything to infinity" $
       \x y -> headOr x (y ++ infinity) == headOr 0 y
   , testProperty "associativity" $
       \x y z -> (x ++ y) ++ z == (x ++ (y ++ z) :: List Integer)
   , testProperty "append to empty list" $
       \x -> x ++ Nil == (x :: List Integer)
   ]

 flattenTest :: TestTree
 flattenTest =
   testGroup "flatten" [
     testCase "(1..9)" $
       flatten ((1 :. 2 :. 3 :. Nil) :. (4 :. 5 :. 6 :. Nil) :. (7 :. 8 :. 9 :. Nil) :. Nil) @?= listh [1,2,3,4,5,6,7,8,9]
   , testProperty "flatten (infinity :. y)" $ \(x, y) ->
       headOr x (flatten (infinity :. y :. Nil)) == 0
   , testProperty "flatten (y :. infinity)" $ \(x, y) ->
       headOr x (flatten (y :. infinity :. Nil)) == headOr 0 y
   , testProperty "sum of lengths == length of flattened" $ \x ->
       sum (map length x) == length (flatten (x :: List (List Integer)))
   ]

 flatMapTest :: TestTree
 flatMapTest =
   testGroup "flatMap" [
     testCase "lists of Integer" $
       flatMap (\x -> x :. x + 1 :. x + 2 :. Nil) (1 :. 2 :. 3 :. Nil) @?= listh [1,2,3,2,3,4,3,4,5]
   , testProperty "flatMap id flattens a list of lists" $ \x y ->
       headOr x (flatMap id (infinity :. y :. Nil)) == 0
   , testProperty "flatMap id on a list of lists take 2" $ \x y ->
       headOr x (flatMap id (y :. infinity :. Nil)) == headOr 0 y
   , testProperty "flatMap id == flatten" $ \x ->
       flatMap id x == flatten (x :: List (List Integer))
   ]

 flattenAgainTest :: TestTree
 flattenAgainTest =
   testGroup "flattenAgain" [
     testProperty "lists of Integer" $ \x ->
       flatten x == flattenAgain (x :: List (List Integer))
   ]


 seqOptionalTest :: TestTree
 seqOptionalTest =
   testGroup "seqOptional" [
     testCase "all Full" $
       seqOptional (Full 1 :. Full 10 :. Nil) @?= Full (1 :. 10 :. Nil)
   , testCase "empty list" $
       let empty = Nil :: List (Optional Integer)
        in seqOptional empty @?= Full Nil
   , testCase "contains Empty" $
       seqOptional (Full 1 :. Full 10 :. Empty :. Nil) @?= Empty
   , testCase "Empty at head of infinity" $
       seqOptional (Empty :. map Full infinity) @?= Empty
   ]

 findTest :: TestTree
 findTest =
   testGroup "find" [
     testCase "find no matches" $
       find even (1 :. 3 :. 5 :. Nil) @?= Empty
   , testCase "empty list" $ find even Nil @?= Empty
   , testCase "find only even" $
       find even (1 :. 2 :. 3 :. 5 :. Nil) @?= Full 2
   , testCase "find first, not second even" $
       find even (1 :. 2 :. 3 :. 4 :. 5 :. Nil) @?= Full 2
   , testCase "find on infinite list" $
       find (const True) infinity @?= Full 0
   ]

 lengthGT4Test :: TestTree
 lengthGT4Test =
   testGroup "lengthGT4" [
     testCase "list of length 3" $
       lengthGT4 (1 :. 3 :. 5 :. Nil) @?= False
   , testCase "list of length 4" $
       lengthGT4 (1 :. 2 :. 3 :. 4 :. Nil) @?= False
   , testCase "empty list" $
       lengthGT4 Nil @?= False
   , testCase "list of length 5" $
       lengthGT4 (1 :. 2 :. 3 :. 4 :. 5 :. Nil) @?= True
   , testCase "infinite list" $
       lengthGT4 infinity @?= True
   ]

 reverseTest :: TestTree
 reverseTest =
   testGroup "reverse" [
     testCase "empty list" $
       reverse Nil @?= (Nil :: List Integer)
   , testCase "reverse . reverse on largeList" $
       take 1 (reverse (reverse largeList)) @?= (1 :. Nil)
   , testProperty "reverse then append is same as append then reverse" $ \x y ->
       reverse x ++ reverse y == (reverse (y ++ x) :: List Integer)
   , testProperty "reverse single element list is the list" $ \x ->
       reverse (x :. Nil) == (x :. Nil :: List Integer)
   ]

 produceTest :: TestTree
 produceTest =
   testGroup "produce" [
     testCase "increment" $
       let (x:.y:.z:.w:._) = produce (+1) 0
        in (x:.y:.z:.w:.Nil) @?= (0:.1:.2:.3:.Nil)
   , testCase "double" $
       let (x:.y:.z:.w:._) = produce (*2) 1
        in (x:.y:.z:.w:.Nil) @?= (1:.2:.4:.8:.Nil)
   ]

 */

headOrTest();
sumTest();
productTest();
lengthTest();
mapTest();
filterTest();