@0xa44026b503cc347b;

struct Command {
  predicate @0 :Type;
  
  enum Type {
    go @0;
    talk @1;
    attack @2;
    buy @3;
    sell @4;
  }

  subject @1 :UInt32;
  
  amount :union {
   none @2 :Void;
   num @3 :UInt32;
  }
  
  preposition :union {
    none @4 :Void;
    weapon @5 :Text;
  }
}
