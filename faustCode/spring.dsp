import("stdfaust.lib");

//in = (1-1'); // test impulse
in = _;
stiffness = nentry("stiffness", 100, 0.1, 1000, 0.001)*ma.SR;
damping = nentry("damping", 0.0, 0.0001, 1000, 0.001);
step = 1/ma.SR;

dV = ((_*step)*(damping*-1)-(_*step)*(stiffness):(+~_))~_;
process = (in):(+<:(_+(dV*step)))~_;
