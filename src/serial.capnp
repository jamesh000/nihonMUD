@0xa44026b503cc347b;

struct Command {
  enum Action {
    go @0;
    talk @1;
    attack @2;
    buy @3;
    sell @4;
  }
  
  amount @0 :UInt32;
  
  union {
    empty @1 :Void;
    weapon @2 :Text;
  }
}
