SpringD : UGen {
  *ar {
    arg in, stiffness = 100, damping = 1.0, mul = 1.0, add = 0.0;
    ^this.multiNew('audio', in, stiffness, damping).madd(mul, add)
  }
}
