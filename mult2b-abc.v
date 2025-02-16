// Benchmark "Multi2" written by ABC on Mon Mar 16 10:06:41 2015

module Multi2 ( 
    a0, a1, b0, b1,
    m0, m1, m2, m3  );
  input  a0, a1, b0, b1;
  output m0, m1, m2, m3;
  wire n10, n11, n13, n14;
  and2 g0(.a(b0), .b(a0), .O(m0));
  and2 g1(.a(b0), .b(a1), .O(n10));
  and2 g2(.a(b1), .b(a0), .O(n11));
  xor2 g3(.a(n11), .b(n10), .O(m1));
  and2 g4(.a(b1), .b(a1), .O(n13));
  and2 g5(.a(n11), .b(n10), .O(n14));
  xor2 g6(.a(n14), .b(n13), .O(m2));
  and2 g7(.a(n14), .b(n13), .O(m3));
endmodule


