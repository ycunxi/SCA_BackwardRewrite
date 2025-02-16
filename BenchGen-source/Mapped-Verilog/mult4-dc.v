// Benchmark "benchgen" written by ABC on Wed Jan 14 10:15:39 2015

module benchgen ( 
    a0, a1, a2, a3, b0, b1, b2, b3,
    z0, z1, z2, z3, z4, z5, z6, z7  );
  input  a0, a1, a2, a3, b0, b1, b2, b3;
  output z0, z1, z2, z3, z4, z5, z6, z7;
  wire n18, n19, n21, n22, n23, n24, n25, n26, n28, n29, n30, n31, n32, n33,
    n34, n35, n36, n37, n38, n39, n40, n41, n42, n43, n44, n45, n47, n48,
    n49, n50, n51, n52, n53, n54, n55, n56, n57, n58, n59, n60, n61, n62,
    n63, n64, n65, n66, n67, n68, n69, n70, n72, n73, n74, n75, n76, n77,
    n78, n79, n80, n81, n82, n83, n85, n86, n87, n88, n89, n90, n91, n92,
    n93, n94, n96;
  and2 g00(.a(b0), .b(a0), .O(z0));
  xor2 g03(.a(n19), .b(n18), .O(z1));
  inv1 g14(.a(n30), .O(n31));
  or2  g49(.a(n65), .b(n63), .O(n66));
