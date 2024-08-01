@0xa44026b503cc347b;

struct Command {
  amount @0 :UInt32;
  
  enum Action {
    move @0;
    attack @1;
    trade @2;
  }
}
